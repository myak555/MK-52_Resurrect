//////////////////////////////////////////////////////////
//
//  RetroRPN - "Электроника МК-90" reborn
//  Copyright (c) 2019 Pavel Travnik.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "Utilities.hpp"

//#define __DEBUG

//
// Converts a string from CP1251 into Unicode (e.g. for printing via UTF8)
//
inline char *_setDuplet( char *buff, byte c){
  *buff++ = c;
  *buff = 0;
  return buff;  
}
inline char *_setTriplet( char *buff, byte prefix, byte c){
  *buff++ = prefix;
  *buff++ = c;
  *buff = 0;
  return buff;  
}
char *_setMacro( char *buff, const char *macro){
  for( byte i=0; macro[i] != _NUL_; i++)
    *buff++ = macro[i];
  *buff = _NUL_;
  return buff; 
}
char *convertToUTF8( char *buff, byte *message, size_t nchar){
  byte c;
  for (size_t i=0; i<nchar; i++) {
    c = message[i];
    if( !c) break;
    buff = convertToUTF8( buff, c);
  }
  return buff;
}
char *convertToUTF8( char *buff, byte *message){
  return convertToUTF8( buff, message, strlen((char *)message));
}
char *convertToUTF8( char *buff, byte c){
  if( c < 128) return _setDuplet(buff, c);
  if( c == _PLSMNS_)
    return _setMacro(buff, "+/-");
  if( c == 0xB8) return _setTriplet(buff, 0xD1, 0x91);
  if( c == 0xA8) return _setTriplet(buff, 0xD0, 0x81);
  if( c >= 0xF0) return _setTriplet(buff, 0xD1, c - 0x70);
  if( c >= 0xC0) return _setTriplet(buff, 0xD0, c - 0x30);
  return _setTriplet(buff, 0xD1, c);
}

//
// Converts message from Unicode to CP1251
//
#ifdef __DEBUG
void _reportUnknownUnicode( byte *ptr){
  ptr--;
  Serial.print( "Unknown unicode: ");
  Serial.print( *ptr++, HEX);        
  Serial.print( " ");        
  Serial.print( *ptr++, HEX);        
  Serial.print( " ");        
  Serial.print( *ptr++, HEX);        
  Serial.print( " ");        
  Serial.println( *ptr++, HEX);        
};
#endif
inline byte *_addCh( byte* ptr, byte* ptr_limit, byte c){
  if( ptr >= ptr_limit) return ptr_limit;
  *ptr++ = c;
  return ptr;
}
byte *convertToCP1251( byte *buff, const char *message, size_t limit){
  byte c;
  byte Unicode_Prefix = 0;
  byte *ptr1 = buff; 
  byte *ptr2 = (byte *)message; 
  byte *ptr_limit = ptr1 + limit - 1; 
  for (byte i=0; i<strlen(message); i++) {
    c = *ptr2++;
    switch(Unicode_Prefix){
      case 0: // No prefix
        if( !c) // safety termination
          return _addCh(ptr1, ++ptr_limit, (byte)0);
        if( c < 128){ // lower chars
          ptr1 = _addCh(ptr1, ptr_limit, c);
          break;
        }
        Unicode_Prefix = c;
        break;
      case 0xD0:
        Unicode_Prefix = 0;
        if( 0x90 <= c && c < 0xD0){
          ptr1 = _addCh(ptr1, ptr_limit, c + 0x30);
          break;
        }
        if( c == 0x81){
          ptr1 = _addCh(ptr1, ptr_limit, 0xA8);
          break;
        }
        ptr1 = _addCh(ptr1, ptr_limit, c);
        break;
      case 0xD1:
        Unicode_Prefix = 0;
        if( 0x80 <= c && c < 0x90){
          ptr1 = _addCh(ptr1, ptr_limit, c + 0x70);
          break;
        }
        if( c == 0x91){
          ptr1 = _addCh(ptr1, ptr_limit, 0xB8);
          break;
        }
        ptr1 = _addCh(ptr1, ptr_limit, c);
        break;
      case 0xC2:
        Unicode_Prefix = 0;
        if( c == 0xAB || c == 0xBB){ // quote
          ptr1 = _addCh(ptr1, ptr_limit, '\"');
          break;
        }
        #ifdef __DEBUG
        _reportUnknownUnicode( ptr2);
        #endif
        ptr1 = _addCh(ptr1, ptr_limit, UNKNOWN_UTF8);
        break;
      case 0xE2:
        Unicode_Prefix = 0;
        if( c == 0x80 && *ptr2 == 0x94){ // EM-dash
          ptr1 = _addCh(ptr1, ptr_limit, '-');
          ptr1 = _addCh(ptr1, ptr_limit, '-');
          ptr2++;
          break;
        }
        if( c == 0x80 && *ptr2 == 0xA6){ // triple dot
          ptr1 = _addCh(ptr1, ptr_limit, '.');
          ptr1 = _addCh(ptr1, ptr_limit, '.');
          ptr1 = _addCh(ptr1, ptr_limit, '.');
          ptr2++;
          break;
        }
        #ifdef __DEBUG
        _reportUnknownUnicode( ptr2);
        #endif
        ptr1 = _addCh(ptr1, ptr_limit, UNKNOWN_UTF8);
        ptr2++;
        break;
      default: // Unknown Unicode is replaced with *
        Unicode_Prefix = 0;
        #ifdef __DEBUG
        _reportUnknownUnicode( ptr2);
        #endif
        ptr1 = _addCh(ptr1, ptr_limit, UNKNOWN_UTF8);
        break;
    }
  } // for
  // safe string termination
  return _addCh(ptr1, ++ptr_limit, (byte)0);
}
