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
#define CURRENT_DIR_LEN    256
#define CURRENT_FILE_LEN   256

namespace MK52_Hardware{
    class SD_Manager{
      public:
        volatile bool SDMounted = false;
        volatile uint64_t cardSize = 0;
        int16_t listingPosition = -1;

        unsigned long init();

    //     size_t loadBinary( const char *name, byte *buff, size_t minSize, size_t maxSize);
    //     bool saveBinary( const char *name, byte *buff, size_t Size);

    //     void readFile( const char * path);
    //     void writeFile( const char * path, const char * message);
    //     const char *SD_Message();
    //     void checkSDStatus();
    //     bool setPrevMounted(){
    //       if( SDPrevMounted == SDMounted) return true;
    //       SDPrevMounted = SDMounted;
    //       return false;
    //     }

        void checkRootExists();
        bool checkEntityExists( const char *name);
        void startFolderListing( char **Lines, uint8_t nLines, uint8_t lineLen, char *name=NULL);
    //     bool deleteEntity( const char *name);
    //     void createFolder( char *name);

    //     bool openProgramFileRead( const char *name);
    //     bool openProgramFileWrite( const char *name);
    //     bool openDataFileRead( const char *name);
    //     bool openDataFileWrite( const char *name);
    //     uint16_t readln( byte *buff);
    //     uint16_t print( char *buff, bool cr=true);
    //     inline void closeFile(){
    //       _currentFile.close();
    //     };
    //     bool readDouble( double *v);
    //     bool writeDouble( double v);
    //     size_t readString( byte *buff, size_t limit);
    //     bool writeString( byte *v);
    //     bool writeSettingNumber( const char *title, double value);
    //     bool writeSettingString( const char *title, byte *value);

      private:
        char *_current_Dir = NULL;
        char *_current_File = NULL;
        void _resetRoot();
        File _getCurrentDir();

    //    byte *_io_buffer;
    //     IOManager *_iom;
    //     Keywords *_kwds;
    //     Variables *_vars;
    //     ProgramCode *_code;
    //     MessageBox *_mbox;
    //     ExpressionParser *_epar;
    //     File _currentFile;

    //     void _checkSDPin();
    //     bool _detectSDCard();

    //     bool _locateBASICFile( const char *name);
    //     bool _locateExistingFile( const char *name);
    //     bool _cardCheckMantra();
        char *_stripFolders( const char *name);
        void _formEntityName( File f, char *str, uint8_t lineLen);
        void _appendFileSize( File f, char *str);

    //     bool _nameLengthCheckMantra( size_t len);
    //     bool _lookForFileMantra1( char *tmpName);
    //     bool _lookForFileMantra2( char *tmpName);
    //     bool _formFileMantra( const char *name, char *dest);
    //     bool _checkFolderStructure( char *name);
    };
};

#endif // SD_MANAGER_HPP