//////////////////////////////////////////////////////////
//
//  RetroRPN - "Электроника МК-90" reborn
//  Copyright (c) 2019 Pavel Travnik.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

//
// Characters defined as bytes (unsigned 8-bits)
//

#ifndef CP1254MOD_H
#define CP1254MOD_HPP

#define _NUL_        0
#define _BEL_        7
#define _BS_         8
#define _TAB_        9
#define _LF_        10
#define _CR_        13
#define _LEFT_      17
#define _RIGHT_     18
#define _UP_        19
#define _DOWN_      20
#define _HOME_      21
#define _END_       22
#define _PGUP_      23
#define _PGDN_      24
#define _ESC_       27
#define _RPN_       31
#define _SP_        32
#define _HASH_      35
#define _DOLLAR_    36
#define _PERCENT_   37
#define _COMMA_     44
#define _DECIMAL_   46
#define _ZERO_      48
#define _NINER_     57
#define _ALPHA_C_   65
#define _FOXTROT_C_ 70
#define _ZULU_C_    90
#define _UNDSCR_    95
#define _ALPHA_     97
#define _FOXTROT_  102
#define _ZULU_     122
#define _YO_C_     168
#define _YO_       184
#define _ANNA_C_   192
#define _YAKOV_C_  223
#define _ANNA_     224
#define _YAKOV_    255


#define _COLON_     58
#define _DEL_      127
#define _PLSMNS_   177

// Keyboard and mouse 
#define _KBD_INJ_    1
#define _MOUSE_INJ_  2

// Unknown UTF is a star!
#define UNKNOWN_UTF8 '*'

#endif
