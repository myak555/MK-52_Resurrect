//////////////////////////////////////////////////////////
//
//  RetroRPN - "Электроника МК-90" reborn
//  Copyright (c) 2019 Pavel Travnik.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Arduino.h"
#include "CP1251_mod.h"

#define UNKNOWN_UTF8 (byte)'*'

//
// Converts message or byte from CP1251 into Unicode
// Returns a pointer to the end of the converted string
// buff must have enough space to acommodate data
// (conversion may double the size!)
//
char *convertToUTF8( char *buff, uint8_t *message, size_t nchar);
char *convertToUTF8( char *buff, uint8_t *message);
char *convertToUTF8( char *buff, uint8_t c);

//
// Converts message from Unicode to CP1251
// Returns a pointer to the end of the converted string
// buff must have enough space to acommodate data
// Note that only CP1251 subset is supported
//
byte *convertToCP1251( uint8_t *buff, const char *message, size_t limit);


#endif // UTILITIES_HPP
