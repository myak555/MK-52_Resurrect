//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    public class SD_Manager
    {
        private Dictionary<string, DirectoryInfo> _directoryListing
            = new Dictionary<string, DirectoryInfo>();
        private Dictionary<string, FileInfo> _fileListing
            = new Dictionary<string, FileInfo>();
        private List<string> _itemListing = new List<string>();
        private string _current_Dir_Name = "C:/";
        private DateTime _lastDirectoryRead = DateTime.MinValue;

        public const byte _LF_ = 10;
        public const byte _CR_ = 13;

        public bool SDMounted = false; // fake for simulator only
        public UInt64 cardSize = 0L;
        public int listingPosition = -1;
        public int _nDirs = 0;
        public int _nItems = 0;
        public string _current_File = "";
        public bool _current_File_open = false;
        
        public void init()
        {
            _clearItems();
            _current_Dir_Name = Directory.GetParent(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)).FullName;
            //if ( Environment.OSVersion.Version.Major >= 6 )
            //    _current_Dir_Name = Directory.GetParent(_current_Dir_Name).ToString();
            SDMounted = Directory.Exists(_current_Dir_Name);
            if (!SDMounted) return;
            _current_Dir_Name += "\\MK52Simulator";
            if (!Directory.Exists(_current_Dir_Name))
                Directory.CreateDirectory(_current_Dir_Name);
            SDMounted = Directory.Exists(_current_Dir_Name);
            _current_Dir_Name = _current_Dir_Name.Replace('\\', '/');
            setFolder_P(_current_Dir_Name);
        }

        public string getFolderName()
        {
            return _current_Dir_Name;
        }

        public string getWindowsFolderName()
        {
            return _current_Dir_Name.Replace('/', '\\');
        }

        public string getFolderNameTruncated( int n)
        {
            int ln = _current_Dir_Name.Length;
            if( ln >= n-1)
            {
                return _current_Dir_Name.Substring(ln - n + 1) + "/";
            }
            return _current_Dir_Name + "/";
        }


        //abstract public void nextListingPosition();
        //abstract public void previousListingPosition();
        
        public bool isAtFolder()
        {
            return listingPosition <_nDirs;
        }
        
        //abstract public string getItemFromListing();

        //abstract public void checkRootExists();

        public bool checkEntityExists(string name)
        {
            name = name.Replace( '/', '\\');
            return File.Exists(name) || Directory.Exists(name);
        }
        
        public string makeEntityName( string name)
        {
            StringBuilder sb = new StringBuilder();
            if (name.Length <= 0) return sb.ToString(); // no name given
            sb.Append(_current_Dir_Name);
            sb.Append('/');
            sb.Append(name);
            return sb.ToString();
        }

        public string getItemString(int n)
        {
            if (n >= _itemListing.Count) return "";
            return _itemListing[n];
        }

        //public int getItemPtr( int n)
        //{
        //    return (_buffer + n*LCD_Manager.SCREEN_COLS);
        //}

        public void setFolder(string name)
        {
            setFolder_P(name);
        }

        public void setFolder_P(string name)
        {
            _current_Dir_Name = name.Replace('\\', '/');
            readFolderItems();
        }

        public void readFolderItems()
        {
            readFolderItems("");
        }

        public void readFolderItems(string location)
        {
            if( !SDMounted) return;
            _clearItems();
            if( !checkEntityExists(_current_Dir_Name)) return;
            string wdn = getWindowsFolderName();
            if (!Directory.Exists(wdn)) return;
            DirectoryInfo root = new DirectoryInfo(wdn);
            DirectoryInfo[] dis = root.GetDirectories();
            foreach (DirectoryInfo di in dis)
            {
                string en = _formEntityName(di);
                if( _directoryListing.ContainsKey( en)) continue;
                _directoryListing[en] = di;
            }
            FileInfo[] fis = root.GetFiles();
            foreach (FileInfo fi in fis)
            {
                string en = _formEntityName(fi);
                if (_fileListing.ContainsKey(en)) continue;
                _fileListing[en] = fi;
            }
            List<string> tmp = new List<string>();
            foreach (string s in _directoryListing.Keys) tmp.Add(s);
            tmp.Sort();
            foreach (string s in tmp) _itemListing.Add(s);
            _nDirs = _itemListing.Count;
            tmp.Clear();
            foreach (string s in _fileListing.Keys) tmp.Add(s);
            tmp.Sort();
            foreach (string s in tmp) _itemListing.Add(s);
            _nItems = _itemListing.Count;
            if (location.Length == 0)
            {
                if (listingPosition < 0 && _nItems > 0) listingPosition = 0;
                if (listingPosition >= _nItems) listingPosition = _nItems - 1; 
                return;
            }
            for (int i = 0; i < _nDirs; i++)
            {
                if (!_itemListing[i].StartsWith(location)) continue;
                listingPosition = i;
                break;
            }
        }

        public string[] getFolderListing(string[] Lines, int nLines, int lineLen)
        {
            if (DateTime.Now - _lastDirectoryRead > TimeSpan.FromSeconds(10.0))
            {
                // TODO
                readFolderItems("");
                _lastDirectoryRead = DateTime.Now;
            }
            return getFolderListing( Lines, nLines, lineLen, null);
        }

        public string[] getFolderListing(string[] Lines, int nLines, int lineLen, string name)
        {
            if( SDMounted)
                Lines[0] = getFolderNameTruncated( LCD_Manager.SCREEN_COLS-1);
            else
                Lines[0] = "Insert SD card and reboot";
            int startLine = 0;
            int stopLine = nLines - 2;
            if (listingPosition > stopLine)
            {
                startLine = listingPosition - stopLine;
                stopLine += startLine;
            }
            for ( int i = 1; i < nLines; i++, startLine++)
            {
                Lines[i] = (startLine == listingPosition) ? "\u00ac ": "  ";
                Lines[i] += getItemString(startLine);
            }
            return Lines;
        }

        //public void setListingPosition( uint pos)
        //{
        //    listingPosition = ( pos>=_nItems)? _nItems-1: pos;
        //}
        
        //abstract public bool deleteEntity(  string name);
        //abstract public void createFolder( string name);
        //abstract public void upFolder();
        //abstract public bool stepIn(string name);

        //abstract public bool openFile( string path, bool write);
        //abstract public bool openFile_P(  string path, bool write);
        //abstract public void closeFile();
        //abstract public bool print( string  message);
        //abstract public bool print_P(  string  message);
        //abstract public bool println( string  message);
        //abstract public bool println_P(  string  message);
        //abstract public bool read( string buffer, int n);
        //abstract public bool readln( string buffer, int n);

        //private string _current_Dir_Name = "";
        //private string _current_File_Name = "";
        //private string _text = "";
        //private string _buffer = "";

        //private void _resetRoot();
        //private File _getCurrentDir();        
        
        private void _clearItems()
        {
            _nDirs = 0;
            _nItems = 0;
            listingPosition = -1;
            _directoryListing .Clear();
            _fileListing.Clear();
            _itemListing.Clear();
        }

        /// <summary>
        /// C++ dummy
        /// </summary>
        private int _locateAlphabetic(string name, bool isDir)
        {
            return 0;
        }

        /// <summary>
        /// C++ dummy
        /// </summary>
        private bool _insertItem(string name, int pos, int slot, bool isDir)
        {
            return true;
        } 
        
        //private string _stripFolders(  string name);

        private string _formEntityName(DirectoryInfo f)
        {
            StringBuilder sb = new StringBuilder();
            string name = f.Name;
            int nameLen = name.Length;
            if( nameLen > LCD_Manager.SCREEN_COLS - 9) nameLen = LCD_Manager.SCREEN_COLS - 9;
            sb.Append( name.Substring( 0, nameLen));
            while( sb.Length < LCD_Manager.SCREEN_COLS - 9) sb.Append(' ');
            sb.Append( " [DIR]");
            return sb.ToString();
        }

        private string _formEntityName(FileInfo f)
        {
            StringBuilder sb = new StringBuilder();
            string name = f.Name;
            int nameLen = name.Length;
            if (nameLen > LCD_Manager.SCREEN_COLS - 9) nameLen = LCD_Manager.SCREEN_COLS - 9;
            sb.Append(name.Substring(0, nameLen));
            while (sb.Length < LCD_Manager.SCREEN_COLS - 9) sb.Append(' ');
            sb.Append(_appendFileSize(f));
            return sb.ToString();
        }

        private string _appendFileSize(FileInfo f)
        {
            long size = f.Length;
            StringBuilder sb = new StringBuilder();
            sb.Append(' ');
            if (size < 8192L)
            {
                sb.Append( size.ToString("0000"));
                sb.Append('b');
                return sb.ToString();
            }
            size >>= 10;
            if (size < 8192L)
            {
                sb.Append(size.ToString("0000"));
                sb.Append('k');
                return sb.ToString();
            }
            size >>= 10;
            if (size < 8192L)
            {
                sb.Append(size.ToString("0000"));
                sb.Append('M');
                return sb.ToString();
            }
            size >>= 10;
            sb.Append(size.ToString("0000"));
            sb.Append('G');
            return sb.ToString();
        }
    }
}

//void SD_Manager::checkRootExists(){
//    if(!SDMounted) return;
//    File root = SD.open( _current_Dir_Name);
//    if(!root){
//        _resetRoot();
//        return;
//    }
//    if(!root.isDirectory()) _resetRoot();
//    root.close();
//}

//bool SD_Manager::checkEntityExists( const char *name){
//    if( !SDMounted ) return false;
//    return SD.exists(name);
//}

//void SD_Manager::nextListingPosition(){
//    if( _nItems <= 0){
//        listingPosition = -1;
//        return;
//    }
//    listingPosition++;
//    if(listingPosition>=_nItems) listingPosition=_nItems-1;
//}

//void SD_Manager::previousListingPosition(){
//    if( _nItems <= 0){
//        listingPosition = -1;
//        return;
//    }
//    listingPosition--;
//    if(listingPosition<0) listingPosition=0;
//}


////
//// gets an item from selector
////
//char *SD_Manager::getItemFromListing(){
//    memset( _current_File_Name, 0, CURRENT_FILE_LEN);
//    if( listingPosition<0) return _current_File_Name;
//    int16_t loc = *(getItemPtr( listingPosition));
//    if( loc < 0 || loc >= _nItems) return _current_File_Name;
//    File current_Dir = _getCurrentDir();
//    if( !current_Dir) return _current_File_Name;
//    File file = current_Dir.openNextFile();
//    while( loc>0 && file){ 
//        file = current_Dir.openNextFile();
//        loc--;
//    }
//    current_Dir.close();
//    if( !file) return _current_File_Name;
//    strncpy( _current_File_Name, file.name(), CURRENT_FILE_LEN-1);
//    _current_File_Name[CURRENT_FILE_LEN-1] = 0;
//    file.close();
//    #ifdef __DEBUG
//    Serial.print("Selected: ");
//    Serial.println(_current_File_Name);
//    #endif
//    return _current_File_Name;
//}

//bool SD_Manager::deleteEntity( const char *name){
//    if( !SDMounted) return true;
//    if( strlen(name) == 1) return false;
//    #ifdef __DEBUG
//    Serial.print( "Deleting: ");
//    Serial.println( name);
//    #endif
//    if( !SD.exists( name)) return false;
//    File root = SD.open( name);
//    bool dir = root.isDirectory();
//    if( dir){ // delete recursively
//        File file = root.openNextFile();
//        while(file){
//        if( deleteEntity( file.name())) break;
//        file = root.openNextFile();
//        } // while
//    }//if
//    root.close();
//    return !(dir? SD.rmdir(name): SD.remove( name));
//}

//char *SD_Manager::makeEntityName( char *name){
//    memset( _text, 0, CURRENT_FILE_LEN);
//    if(strlen(name) <= 0) return _text; // no name given
//    strncpy( _text, _current_Dir_Name, CURRENT_FILE_LEN-3);
//    int ln = strlen(_text);
//    if( ln>1) _text[ln++] = '/'; // add slash if not at root
//    strncpy( _text+ln, name, CURRENT_FILE_LEN-2-ln);
//    return _text;
//}

////
//// returns true if an error
////
//bool SD_Manager::openFile( char *path, bool write){
//    if( !SDMounted) return true;
//    closeFile();
//    if( path == NULL){
//        if( isAtFolder()) return true;
//        path = getItemFromListing();
//    }
//    if( strlen( path) <= 1 ) return true; // cannot overwrite root!
//    if( write)
//        _current_File = SD.open( (const char*)path, FILE_WRITE);
//    else
//        _current_File = SD.open( (const char*)path);
//    if( _current_File){
//        _current_File_open = true;
//        #ifdef __DEBUG
//        Serial.print("Opened ");
//        Serial.print( path);
//        Serial.println( write? " for writing": " for reading");
//        #endif
//        return false;
//    }
//    #ifdef __DEBUG
//    else{
//        Serial.print("Failed to open ");
//        Serial.println( path);
//    }
//    #endif
//    return true;
//}

//bool SD_Manager::openFile_P( const char *path, bool write){
//    strncpy_P( _current_File_Name, path, CURRENT_FILE_LEN);
//    _current_File_Name[CURRENT_FILE_LEN] = 0;
//    return openFile( _current_File_Name, write);
//}

//void SD_Manager::closeFile(){
//    if( !SDMounted) return;
//    if( _current_File_open) _current_File.close();
//    _current_File_open = false;
//}

//bool SD_Manager::print( char *message){
//    if( !SDMounted) return true;
//    if( !_current_File_open) return true;
//    if( !_current_File.print((const char*)message)) return true;
//    return false;
//}

//bool SD_Manager::print_P( const char *message){
//    strncpy_P( _text, message, CURRENT_FILE_LEN-1);
//    _text[CURRENT_FILE_LEN-1] = 0;
//    return( print( _text));
//}

//bool SD_Manager::println( char *message){
//    if( !SDMounted) return true;
//    if( !_current_File_open) return true;
//    if( !_current_File.println((const char*)message)) return true;
//    return false;
//}

//bool SD_Manager::println_P( const char *message){
//    strncpy_P( _text, message, CURRENT_FILE_LEN-1);
//    _text[CURRENT_FILE_LEN-1] = 0;
//    return( println( _text));
//}

//bool SD_Manager::read( char *buffer, int32_t n){
//    if( !SDMounted) return true;
//    if( !_current_File_open) return true;
//    while( n>0 && _current_File.available()){
//        *(buffer++) = (char) _current_File.read();
//        n--;
//    }
//    *buffer = 0; // safety zero
//    return n>0; // not all symbols read - file end
//}

//bool SD_Manager::readln( char *buffer, int32_t n){
//    if( !SDMounted) return true;
//    if( !_current_File_open) return true;
//    uint8_t b = 0;
//    while( _current_File.available()){
//        uint8_t b = _current_File.read();
//        if( b ==_CR_) continue;
//        if( b ==_LF_) break;
//        if(n>0){
//            *(buffer++) = (char)b;
//            n--;
//        }
//    }
//    *buffer = 0; // safety zero
//    return  !_current_File.available();
//}

//void SD_Manager::createFolder( char * name){
//    if( !SDMounted) return;
//    if(strlen(name) <= 0) return; // no name given
//    makeEntityName( name);
//    #ifdef __DEBUG
//    Serial.print( "Creating folder: ");
//    Serial.println( _text);
//    #endif
//    if( !SD.mkdir(_text)) return;
//    setFolder( _text);
//}

//void SD_Manager::upFolder(){
//    if( !SDMounted) return;
//    int ln = strlen(_current_Dir_Name);
//    if( ln <= 1) return; // already at root
//    while( ln>0 && _current_Dir_Name[ln] != '/') ln--;
//    strcpy( _current_File_Name, _current_Dir_Name+ln+1);
//    _current_Dir_Name[ln] = 0;
//    #ifdef __DEBUG
//    Serial.print("Going up: ");
//    Serial.println( _current_Dir_Name);
//    Serial.print( "Proposed location: ");
//    Serial.println( _current_File_Name);
//    #endif
//    readFolderItems( _current_File_Name);
//}

////
//// returns true if a run is required
////
//bool SD_Manager::stepIn(char *name){
//    if( !SDMounted) return false;
//    File tmp = SD.open( (const char*)name);
//    if(!tmp) return false;
//    if( tmp.isDirectory()){
//        tmp.close();
//        setFolder( name);
//        return false;
//    }
//    tmp.close();
//    return true;
//}

//void SD_Manager::_resetRoot(){
//    #ifdef __DEBUG
//    Serial.println("Reset to root");
//    #endif
//    strncpy_P( _current_Dir_Name, SD_root, CURRENT_DIR_LEN);
//}

//File SD_Manager::_getCurrentDir(){
//    checkRootExists();
//    return SD.open( _current_Dir_Name);
//}

//void SD_Manager::_clearItems(){
//    _nDirs = 0;
//    _nItems = 0;
//    listingPosition = -1;
//    memset( _buffer, 0, DIRECTORY_LIST_SIZE);
//}

////
//// Scans items and locates the added item alphabetically:
//// Directories are sorted first
//// Returns the slot number for insertion
////
//int16_t SD_Manager::_locateAlphabetic(const char *name, bool isDir){
//    if( _nItems <= 0) return 0;
//    int16_t slot = 0;
//    char *ptr = (char *)name;
//    if( isDir){
//        while( slot < _nDirs){
//            if( strncmp( ptr, getItemString(slot), 21) <= 0)
//                return slot;
//            slot++;
//        }
//        return _nDirs;
//    }
//    else{
//        slot = _nDirs;
//    }
//    while( slot < _nItems){
//        if( strncmp( ptr, getItemString(slot), 21) <= 0)
//            return slot;
//        slot++;
//    }
//    return _nItems;
//}

////
//// Returns true if the maximum directory length is exceeded
////
//bool SD_Manager::_insertItem(const char *name, int16_t pos, int16_t slot, bool isDir){
//    if( slot>=DIRECTORY_LIST_NITEMS-1) return true;
//    if( slot>=_nItems) slot = _nItems;
//    int16_t toMove = _nItems - slot;
//    char *ptr = _buffer + slot * LCD_Manager.SCREEN_COLS;
//    if( toMove > 0) memmove( ptr+LCD_Manager.SCREEN_COLS, ptr, toMove*LCD_Manager.SCREEN_COLS);
//    int16_t toCopy = strlen( name);
//    if( toCopy > LCD_Manager.SCREEN_COLS-3) toCopy = LCD_Manager.SCREEN_COLS-3;
//    memcpy( ptr, &pos, 2);
//    memset( ptr+2, 0, LCD_Manager.SCREEN_COLS-2);
//    memcpy( ptr+2, name, toCopy);
//    if( isDir) _nDirs++;
//    _nItems++;
//    return false;
//}

//char *SD_Manager::_stripFolders( const char *name){
//  int16_t lastHash = strlen( (char*) name) - 1;
//  while( lastHash>0 && name[lastHash] != '/') lastHash--;
//  return (char *)name+lastHash+1; 
//}

