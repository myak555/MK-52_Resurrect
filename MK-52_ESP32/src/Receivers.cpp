//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

#include "../functions/functions.h"
#include "../receivers/receivers.h"
#include "Receivers.hpp"

//#define __DEBUG

using namespace MK52_Interpreter;

const char _RN_ButtonConversion[] PROGMEM = "#ffffffffffff7410852.963-fffEffec";
const char _RN_StandardUnity[] PROGMEM =    "1.0E+000";
const char _AR_ButtonConversion[] PROGMEM = "####f########7410852#963#######ec";
const char _RR_ButtonConversion[] PROGMEM = "####f####abcd7410852A963B###C#FED";
const char _RT_LetterConversion[] PROGMEM = "#AIQ#BJRXCKSYDLTZEMU.FNV_GOW HP##";
const char _RT_DigitConversion[] PROGMEM =  "### #<=>!,;:?7410852.963--+^E/*##";
const char _RFN_DigitConversion[] PROGMEM = "### ####!,###7410852.963_-###/###";

const char _FILE_Message_FileName[] PROGMEM = "File name?";
const char _FILE_Message_FolderName[] PROGMEM = "Folder name?";
static char _FILE_Message_Overwrite[] = "Overwrite? (\x18)";

#include "../receivers/Receiver_OFF.h"
#include "../receivers/Receiver_AUTO.h"
#include "../receivers/Receiver_DATA.h"
#include "../receivers/Receiver_PROG.h"
#include "../receivers/Receiver_FILE.h"
#include "../receivers/Receiver_NUMBER.h"
#include "../receivers/Receiver_TEXT.h"
#include "../receivers/Receiver_ADDRESS.h"
#include "../receivers/Receiver_REGISTER.h"
#include "../receivers/Receiver_FILE_Name.h"
#include "../receivers/Receiver_CONFIRM.h"
