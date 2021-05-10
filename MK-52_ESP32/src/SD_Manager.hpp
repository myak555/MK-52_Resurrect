//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Pin assignment:
//
// *02 - SD chip select (CS)
// *18 - VSPI CLK - TFT SCK and SD SCK
// *19 - VSPI MISO - TFT SDO/MISO and SD MISO
// *23 - VSPI MOSI - TFT SDI/MOSI and SD MOSI
//
// This TFT board has no SD insert sensor - may be make it later
//

#ifndef SD_MANAGER_HPP
#define SD_MANAGER_HPP

#include "Common.h"
#include <FS.h>

#define SD_CSO             5
#define SD_CLOCK           18
#define SD_MISO            19
#define SD_MOSI            23

#define _LF_               10
#define _CR_               13
#define _BOM1_             0xEF
#define _BOM2_             0xBB
#define _BOM3_             0xBF
#define UNKNOWN_UTF8       '*'

namespace MK52_Hardware{
    class SD_Manager{
      public:
        volatile bool SDMounted = false;
        volatile uint64_t cardSize = 0;
        int16_t listingPosition = -1;
        int16_t _nDirs = 0;
        int16_t _nItems = 0;
        File _current_File;
        bool _current_File_open = false;

        void init();

        inline char *getFolderName(){ return _current_Dir_Name;};
        char *getFolderNameTruncated( int8_t n);
        void nextListingPosition();
        void previousListingPosition();
        inline bool isAtFolder(){ return listingPosition <_nDirs;};
        char *getItemFromListing();

        void checkRootExists();
        bool checkEntityExists( const char *name);
        char *makeEntityName( char *name);
        inline char *getItemString( int16_t n){return _buffer + n*SCREEN_COLS + 2;};
        inline int16_t *getItemPtr( int16_t n){ return (int16_t*)(_buffer + n*SCREEN_COLS);};
        void setFolder( char *name);
        void setFolder_P( const char *name);
        void readFolderItems( char *location = NULL, bool resetListingPosition = false);

        void getFolderListing( char *Lines[], uint8_t nLines, uint8_t lineLen, char *name=NULL);
        inline void setListingPosition( uint16_t pos){
            listingPosition = ( pos>=_nItems)? _nItems-1: pos;};
        bool deleteEntity( const char *name);
        void createFolder( char *name);
        void upFolder();
        bool stepIn(char *name);

        bool openFile( char *path=NULL, bool write=false);
        bool openFile_P( const char *path, bool write=false);
        void closeFile();
        bool print( char * message);
        bool print_P( const char * message);
        bool println( char * message);
        bool println_P( const char * message);
        bool read( char *buffer, int32_t n);
        bool readln( char *buffer, int32_t n);

      private:
        char *_current_Dir_Name = NULL;
        char *_current_File_Name = NULL;
        char *_text = NULL;
        char *_buffer = NULL;

        void _resetRoot();
        File _getCurrentDir();        
        void _clearItems();
        int16_t _locateAlphabetic(const char *name, bool isDir);
        bool _insertItem(const char *name, int16_t pos, int16_t slot, bool isDir); 
        char *_stripFolders( const char *name);
        char *_formEntityName( File f);
        char *_appendFileSize( File f);
        char _convertByteToCP1251( uint8_t b);
        bool _currentPrintToUTF(const char * message);
    };
};

#endif // SD_MANAGER_HPP
