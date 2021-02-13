//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include <SD.h>
#include "SD_Manager.hpp"
#include "UniversalValue.hpp"

//#define __DEBUG

// const char SD_Error_NotMounted[] PROGMEM = "Error: Not mounted";
// const char SD_Error_FileNameTooLong[] PROGMEM = "Err: Long name";
// const char SD_Error_FileNotFound[] PROGMEM = "Err: Not found";
// const char SD_Error_WriteFailed[] PROGMEM = "Err: SD fail";
// const char SD_Error_FileAccessError[] PROGMEM = "Err: Write fail";
// const char SD_Error_OutOfMemory[] PROGMEM = "Err: Out of memory";
// const char SD_Error_DeleteFailed[] PROGMEM = "Err: Delete fail";

const char SD_root[] PROGMEM = "/";

using namespace MK52_Hardware;

//
// Init and status update
//
void SD_Manager::init(){
    SDMounted = SD.begin();
    _buffer = (char *)malloc( DIRECTORY_LIST_SIZE);
    _current_Dir_Name = (char *)malloc( CURRENT_DIR_LEN + CURRENT_FILE_LEN * 2 + 3);
    #ifdef __DEBUG
    if( _buffer == NULL || _current_Dir_Name == NULL){
        Serial.println("File List malloc busted!");
        return;
    }
    #endif
    _clearItems();
    memset( _current_Dir_Name, 0, CURRENT_DIR_LEN + CURRENT_FILE_LEN * 2 + 3);
    _current_File_Name = _current_Dir_Name + CURRENT_DIR_LEN + 1;
    _text = _current_File_Name + CURRENT_FILE_LEN + 1;
    setFolder_P(SD_root);
}

void SD_Manager::checkRootExists(){
    if(!SDMounted) return;
    File root = SD.open( _current_Dir_Name);
    if(!root){
        _resetRoot();
        return;
    }
    if(!root.isDirectory()) _resetRoot();
    root.close();
}

bool SD_Manager::checkEntityExists( const char *name){
    if( !SDMounted ) return false;
    return SD.exists(name);
}

void SD_Manager::nextListingPosition(){
    if( _nItems <= 0){
        listingPosition = -1;
        return;
    }
    listingPosition++;
    if(listingPosition>=_nItems) listingPosition=_nItems-1;
}

void SD_Manager::previousListingPosition(){
    if( _nItems <= 0){
        listingPosition = -1;
        return;
    }
    listingPosition--;
    if(listingPosition<0) listingPosition=0;
}

//
// Lists directory and displays selector
//
void SD_Manager::getFolderListing( char *Lines[], uint8_t nLines, uint8_t lineLen, char *name){
    if( SDMounted)
        strcpy( Lines[0], getFolderNameTruncated( SCREEN_COLS-1));
    else
        strcpy_P( Lines[0], PSTR("Insert SD card and reboot"));
    int startLine = 0;
    int stopLine = nLines-2;
    if( listingPosition > stopLine){
        startLine = listingPosition-stopLine;
        stopLine += startLine;
    }
    for( uint8_t i=1; i<nLines; i++, startLine++){
        char *Ln = Lines[i]; 
        memset( Ln+1, 0, lineLen);
        if( startLine > stopLine) continue;
        Ln[ 0] = (startLine == listingPosition)? (char)172 : ' ';
        Ln[ 1] = ' ';
        strncpy( Ln+2, getItemString(startLine), lineLen-2);
    }
}

//
// gets an item from selector
//
char *SD_Manager::getItemFromListing(){
    memset( _current_File_Name, 0, CURRENT_FILE_LEN);
    if( listingPosition<0) return _current_File_Name;
    int16_t loc = *(getItemPtr( listingPosition));
    if( loc < 0 || loc >= _nItems) return _current_File_Name;
    File current_Dir = _getCurrentDir();
    if( !current_Dir) return _current_File_Name;
    File file = current_Dir.openNextFile();
    while( loc>0 && file){ 
        file = current_Dir.openNextFile();
        loc--;
    }
    current_Dir.close();
    if( !file) return _current_File_Name;
    strncpy( _current_File_Name, file.name(), CURRENT_FILE_LEN-1);
    _current_File_Name[CURRENT_FILE_LEN-1] = 0;
    file.close();
    #ifdef __DEBUG
    Serial.print("Selected: ");
    Serial.println(_current_File_Name);
    #endif
    return _current_File_Name;
}

bool SD_Manager::deleteEntity( const char *name){
    if( !SDMounted) return true;
    if( strlen(name) == 1) return false;
    #ifdef __DEBUG
    Serial.print( "Deleting: ");
    Serial.println( name);
    #endif
    if( !SD.exists( name)) return false;
    File root = SD.open( name);
    bool dir = root.isDirectory();
    if( dir){ // delete recursively
        File file = root.openNextFile();
        while(file){
        if( deleteEntity( file.name())) break;
        file = root.openNextFile();
        } // while
    }//if
    root.close();
    return !(dir? SD.rmdir(name): SD.remove( name));
}

char *SD_Manager::makeEntityName( char *name){
    memset( _text, 0, CURRENT_FILE_LEN);
    if(strlen(name) <= 0) return _text; // no name given
    strncpy( _text, _current_Dir_Name, CURRENT_FILE_LEN-3);
    int ln = strlen(_text);
    if( ln>1) _text[ln++] = '/'; // add slash if not at root
    strncpy( _text+ln, name, CURRENT_FILE_LEN-2-ln);
    return _text;
}

//
// returns true if an error
//
bool SD_Manager::openFile( char *path, bool write){
    if( !SDMounted) return true;
    closeFile();
    if( path == NULL){
        if( isAtFolder()) return true;
        path = getItemFromListing();
    }
    if( strlen( path) <= 1 ) return true; // cannot overwrite root!
    if( write)
        _current_File = SD.open( (const char*)path, FILE_WRITE);
    else
        _current_File = SD.open( (const char*)path);
    if( _current_File){
        _current_File_open = true;
        #ifdef __DEBUG
        Serial.print("Opened ");
        Serial.print( path);
        Serial.println( write? " for writing": " for reading");
        #endif
        return false;
    }
    #ifdef __DEBUG
    else{
        Serial.print("Failed to open ");
        Serial.println( path);
    }
    #endif
    return true;
}

bool SD_Manager::openFile_P( const char *path, bool write){
    strncpy_P( _current_File_Name, path, CURRENT_FILE_LEN);
    _current_File_Name[CURRENT_FILE_LEN] = 0;
    return openFile( _current_File_Name, write);
}

void SD_Manager::closeFile(){
    if( !SDMounted) return;
    if( _current_File_open) _current_File.close();
    _current_File_open = false;
}

bool SD_Manager::print( char *message){
    if( !SDMounted) return true;
    if( !_current_File_open) return true;
    if( !_current_File.print((const char*)message)) return true;
    return false;
}

bool SD_Manager::print_P( const char *message){
    strncpy_P( _text, message, CURRENT_FILE_LEN-1);
    _text[CURRENT_FILE_LEN-1] = 0;
    return( print( _text));
}

bool SD_Manager::println( char *message){
    if( !SDMounted) return true;
    if( !_current_File_open) return true;
    if( !_current_File.println((const char*)message)) return true;
    return false;
}

bool SD_Manager::println_P( const char *message){
    strncpy_P( _text, message, CURRENT_FILE_LEN-1);
    _text[CURRENT_FILE_LEN-1] = 0;
    return( println( _text));
}

bool SD_Manager::read( char *buffer, int32_t n){
    if( !SDMounted) return true;
    if( !_current_File_open) return true;
    while( n>0 && _current_File.available()){
        *(buffer++) = (char) _current_File.read();
        n--;
    }
    *buffer = 0; // safety zero
    return n>0; // not all symbols read - file end
}

bool SD_Manager::readln( char *buffer, int32_t n){
    if( !SDMounted) return true;
    if( !_current_File_open) return true;
    uint8_t b = 0;
    while( _current_File.available()){
        uint8_t b = _current_File.read();
        if( b ==_CR_) continue;
        if( b ==_LF_) break;
        if(n>0){
            *(buffer++) = (char)b;
            n--;
        }
    }
    *buffer = 0; // safety zero
    return  !_current_File.available();
}

void SD_Manager::createFolder( char * name){
    if( !SDMounted) return;
    if(strlen(name) <= 0) return; // no name given
    makeEntityName( name);
    #ifdef __DEBUG
    Serial.print( "Creating folder: ");
    Serial.println( _text);
    #endif
    if( !SD.mkdir(_text)) return;
    setFolder( _text);
}

void SD_Manager::upFolder(){
    if( !SDMounted) return;
    int ln = strlen(_current_Dir_Name);
    if( ln <= 1) return; // already at root
    while( ln>0 && _current_Dir_Name[ln] != '/') ln--;
    strcpy( _current_File_Name, _current_Dir_Name+ln+1);
    _current_Dir_Name[ln] = 0;
    #ifdef __DEBUG
    Serial.print("Going up: ");
    Serial.println( _current_Dir_Name);
    Serial.print( "Proposed location: ");
    Serial.println( _current_File_Name);
    #endif
    readFolderItems( _current_File_Name);
}

//
// returns true if a run is required
//
bool SD_Manager::stepIn(char *name){
    if( !SDMounted) return false;
    File tmp = SD.open( (const char*)name);
    if(!tmp) return false;
    if( tmp.isDirectory()){
        tmp.close();
        setFolder( name);
        return false;
    }
    tmp.close();
    return true;
}

void SD_Manager::setFolder( char *name){
    strncpy( _current_Dir_Name, name, CURRENT_DIR_LEN-1);
    _current_Dir_Name[CURRENT_DIR_LEN-1] = 0;
    readFolderItems();
}

void SD_Manager::setFolder_P( const char *name){
    strncpy_P( _current_Dir_Name, name, CURRENT_DIR_LEN-1);
    _current_Dir_Name[CURRENT_DIR_LEN-1] = 0;
    readFolderItems();
}

char *SD_Manager::getFolderNameTruncated( int8_t n){
    int ln = strlen(_current_Dir_Name);
    if( ln > n-1) ln = ln - n + 1;
    else ln = 0;
    strcpy( _text, _current_Dir_Name+ln);
    ln = strlen(_text);
    if( ln>1){
        _text[ln++] = '/';
        _text[ln] = 0;
    }
    return _text;
}

void SD_Manager::readFolderItems(char *location){
    if( !SDMounted) return;
    _clearItems();
    if( !checkEntityExists(_current_Dir_Name)) return;
    File current_Dir = _getCurrentDir();
    if(!current_Dir) return;
    File file = current_Dir.openNextFile();
    int16_t counter = 0;
    int16_t index = 0;
    int16_t pos2 = -1;
    while( file){
        char *name = (char *)_formEntityName( file);
        if( MK52_Interpreter::UniversalValue::_startsWith( name, location))
            pos2 = counter;
        bool isdir = file.isDirectory();
        index = _locateAlphabetic( name, isdir);
        #ifdef __DEBUG
        Serial.print(name);
        Serial.print(" is located at ");
        Serial.println(index);
        #endif
        if( _insertItem( name, counter++, index, isdir)) break; // too many items
        file = current_Dir.openNextFile();
    }
    current_Dir.close();
    if( _nItems > 0) listingPosition = 0;
    if( location == NULL) return;
    Serial.print("Looking for location: ");
    Serial.println(location);
    for( int i=0; i<_nDirs; i++){
        if( *(getItemPtr(i)) != pos2) continue;
        listingPosition = i;
        break;
    }
}

void SD_Manager::_resetRoot(){
    #ifdef __DEBUG
    Serial.println("Reset to root");
    #endif
    strncpy_P( _current_Dir_Name, SD_root, CURRENT_DIR_LEN);
}

File SD_Manager::_getCurrentDir(){
    checkRootExists();
    return SD.open( _current_Dir_Name);
}

void SD_Manager::_clearItems(){
    _nDirs = 0;
    _nItems = 0;
    listingPosition = -1;
    memset( _buffer, 0, DIRECTORY_LIST_SIZE);
}

//
// Scans items and locates the added item alphabetically:
// Directories are sorted first
// Returns the slot number for insertion
//
int16_t SD_Manager::_locateAlphabetic(const char *name, bool isDir){
    if( _nItems <= 0) return 0;
    int16_t slot = 0;
    char *ptr = (char *)name;
    if( isDir){
        while( slot < _nDirs){
            if( strncmp( ptr, getItemString(slot), 21) <= 0)
                return slot;
            slot++;
        }
        return _nDirs;
    }
    else{
        slot = _nDirs;
    }
    while( slot < _nItems){
        if( strncmp( ptr, getItemString(slot), 21) <= 0)
            return slot;
        slot++;
    }
    return _nItems;
}

//
// Returns true if the maximum directory length is exceeded
//
bool SD_Manager::_insertItem(const char *name, int16_t pos, int16_t slot, bool isDir){
    if( slot>=DIRECTORY_LIST_NITEMS-1) return true;
    if( slot>=_nItems) slot = _nItems;
    int16_t toMove = _nItems - slot;
    char *ptr = _buffer + slot * SCREEN_COLS;
    if( toMove > 0) memmove( ptr+SCREEN_COLS, ptr, toMove*SCREEN_COLS);
    int16_t toCopy = strlen( name);
    if( toCopy > SCREEN_COLS-3) toCopy = SCREEN_COLS-3;
    memcpy( ptr, &pos, 2);
    memset( ptr+2, 0, SCREEN_COLS-2);
    memcpy( ptr+2, name, toCopy);
    if( isDir) _nDirs++;
    _nItems++;
    return false;
}

char *SD_Manager::_stripFolders( const char *name){
  int16_t lastHash = strlen( (char*) name) - 1;
  while( lastHash>0 && name[lastHash] != '/') lastHash--;
  return (char *)name+lastHash+1; 
}

char *SD_Manager::_formEntityName( File f){
    memset( _text, 0, SCREEN_COLS-3);
    const char *name = f.name();
    char *namePtr = _stripFolders( name);
    uint8_t nameLen = strlen( namePtr);
    if( nameLen > SCREEN_COLS - 9) nameLen = SCREEN_COLS - 9;
    if( nameLen>0) memcpy( _text, namePtr, nameLen);
    for( uint16_t i=strlen(_text); i<SCREEN_COLS-9; i++) _text[i] = ' ';
    return _appendFileSize(f);
}

char *SD_Manager::_appendFileSize( File f){
    char *str = _text + SCREEN_COLS - 9;
    if( f.isDirectory()){
        strcpy_P( str, PSTR(" [DIR]"));
        return _text;
    }
    size_t size = f.size();
    if( size < 8192){
        sprintf_P( str, PSTR(" %04db"), (int)size);
        return _text;
    }
    size >>= 10;
    if( size < 8192){
        sprintf_P( str, PSTR(" %04dk"), (int)size);
        return _text;
    }
    size >>= 10;
    if( size < 8192){
        sprintf_P( str, PSTR(" %04dM"), (int)size);
        return _text;
    }
    size >>= 10;
    sprintf_P( str, PSTR(" %04dG"), (int)size);
}

// //
// // Locates an existing BASIC file on disk
// //
// bool SD_Manager::_locateBASICFile( const char *name){
//   size_t len = strlen( name);
//   if( _nameLengthCheckMantra( len)) return true;

//   // first, try the absolute name; no memory allocation needed
//   if( SD.exists(name)){
//     strncat2( _vars->currentFile, name, CURRENT_FILE_LEN);
//     return false;
//   }
  
//   // next, try directory + name
//   len += strlen( _vars->currentDir) + 5;
//   if( _nameLengthCheckMantra( len)) return true;
//   char *tmpName = (char *) malloc( len);
//   if( tmpName == NULL){
//     LastError = SD_Error_OutOfMemory;
//     return true;
//   }
//   strcpy( tmpName, _vars->currentDir);
//   while( *name == '/') name++;
//   strcat( tmpName, name);
//   if( _lookForFileMantra2( tmpName)) return false; // note it frees tmpName

//   // next, try directory + name + ".bas"
//   size_t eos = strlen( tmpName);
//   strcat( tmpName, SD_DefaultExt1);
//   if( _lookForFileMantra2( tmpName)) return false; // note it frees tmpName

//   // finally, try directory + name + ".BAS"
//   tmpName[eos] = _NUL_;
//   strcat( tmpName, SD_DefaultExt2);
//   if( _lookForFileMantra2( tmpName)) return false; // note it frees tmpName

//   // if we are here, nobody freed the memory
//   free( tmpName);
//   LastError = SD_Error_FileNotFound;
//   return true;
// }

// bool SD_Manager::_lookForFileMantra1( char *tmpName){
//   #ifdef __DEBUG
//   Serial.print( "Looking for file: ");
//   Serial.println( tmpName);
//   #endif
//   if( !SD.exists(tmpName)) return false;
//   _currentFile = SD.open( tmpName);
//   free( tmpName);
//   if( !_currentFile) LastError = NULL;
//   return true;
// }
// bool SD_Manager::_lookForFileMantra2( char *tmpName){
//   #ifdef __DEBUG
//   Serial.print( "Looking for file: ");
//   Serial.println( tmpName);
//   #endif
//   if( !SD.exists(tmpName)) return false;
//   strncat2( _vars->currentFile, tmpName, CURRENT_FILE_LEN);
//   free( tmpName);
//   return true;
// }
// bool SD_Manager::_formFileMantra( const char *name, char *dest){
//   if( name == NULL) return false;
//   int16_t len = strlen( name);
//   if( len<2){
//     LastError = SD_Error_FileAccessError;
//     return true;
//   }
//   if( name[0] != '/') len += strlen( _vars->currentDir) + 1;
//   if( _nameLengthCheckMantra( len)) return true;
//   dest[0] = _NUL_;
//   if( name[0] != '/') strcat( dest, _vars->currentDir);
//   strcat( dest, name);
//   return false;
// }

//
// Checks if directory structure exists, if not - creates
//
// bool SD_Manager::_checkFolderStructure( char *name){
//   if( SD.exists( name)) return false;
//   int16_t lastHash = strlen( name) - 1;
//   while( lastHash>0 && name[lastHash] != '/') lastHash--;
//   if( lastHash <= 0) return false; 
//   for( int i=1; i<=lastHash; i++){
//     if( name[i] != '/') continue;
//     char tmp = name[i];
//     name[i] = _NUL_;
//     if( SD.exists( (const char*)name)){
//       #ifdef __DEBUG
//       Serial.print(name);
//       Serial.println(" is OK");
//       #endif
//       name[i] = tmp;
//       continue;
//     }
//     #ifdef __DEBUG
//     Serial.print("Creating ");
//     Serial.println(name);
//     #endif
//     bool ret = SD.mkdir( (const char*)name);
//     name[i] = tmp;
//     if( !ret){
//       #ifdef __DEBUG
//       Serial.println("Create failed, exiting");
//       #endif
//       LastError = SD_Error_FileAccessError;
//       return true;
//     }
//   }
//   // directory structure checked
//   return false;
// }
