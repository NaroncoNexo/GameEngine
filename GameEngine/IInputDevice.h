//
//  IInputDevice.h
//  GameEngine
//
//  Created by Johannes Roth on 30.01.15.
//  Copyright (c) 2015 Johannes Roth. All rights reserved.
//

#ifndef __GameEngine__IInputDevice__
#define __GameEngine__IInputDevice__

#include "Math3D.h"

enum
{
	eMOUSEBUTTON_LEFT,
	eMOUSEBUTTON_RIGHT,
	eMOUSEBUTTON_MIDDLE
};

enum
{
	eKEY_A = 4,
	eKEY_B = 5,
	eKEY_C = 6,
	eKEY_D = 7,
	eKEY_E = 8,
	eKEY_F = 9,
	eKEY_G = 10,
	eKEY_H = 11,
	eKEY_I = 12,
	eKEY_J = 13,
	eKEY_K = 14,
	eKEY_L = 15,
	eKEY_M = 16,
	eKEY_N = 17,
	eKEY_O = 18,
	eKEY_P = 19,
	eKEY_Q = 20,
	eKEY_R = 21,
	eKEY_S = 22,
	eKEY_T = 23,
	eKEY_U = 24,
	eKEY_V = 25,
	eKEY_W = 26,
	eKEY_X = 27,
	eKEY_Y = 28,
	eKEY_Z = 29,
	eKEY_1 = 30,
	eKEY_2 = 31,
	eKEY_3 = 32,
	eKEY_4 = 33,
	eKEY_5 = 34,
	eKEY_6 = 35,
	eKEY_7 = 36,
	eKEY_8 = 37,
	eKEY_9 = 38,
	eKEY_0 = 39,
	eKEY_RETURN = 40,
	eKEY_ESCAPE = 41,
	eKEY_BACKSPACE = 42,
	eKEY_TAB = 43,
	eKEY_SPACE = 44,
	eKEY_MINUS = 45,
	eKEY_EQUALS = 46,
	eKEY_LEFTBRACKET = 47,
	eKEY_RIGHTBRACKET = 48,
	eKEY_BACKSLASH = 49,
	eKEY_NONUSHASH = 50,
	eKEY_SEMICOLON = 51,
	eKEY_APOSTROPHE = 52,
	eKEY_GRAVE = 53,
	eKEY_COMMA = 54,
	eKEY_PERIOD = 55,
	eKEY_SLASH = 56,
	eKEY_CAPSLOCK = 57,
	eKEY_F1 = 58,
	eKEY_F2 = 59,
	eKEY_F3 = 60,
	eKEY_F4 = 61,
	eKEY_F5 = 62,
	eKEY_F6 = 63,
	eKEY_F7 = 64,
	eKEY_F8 = 65,
	eKEY_F9 = 66,
	eKEY_F10 = 67,
	eKEY_F11 = 68,
	eKEY_F12 = 69,
	eKEY_PRINTSCREEN = 70,
	eKEY_SCROLLLOCK = 71,
	eKEY_PAUSE = 72,
	eKEY_INSERT = 73,
	eKEY_HOME = 74,
	eKEY_PAGEUP = 75,
	eKEY_DELETE = 76,
	eKEY_END = 77,
	eKEY_PAGEDOWN = 78,
	eKEY_RIGHT = 79,
	eKEY_LEFT = 80,
	eKEY_DOWN = 81,
	eKEY_UP = 82,
	eKEY_NUMLOCKCLEAR = 83,
	eKEY_KP_DIVIDE = 84,
	eKEY_KP_MULTIPLY = 85,
	eKEY_KP_MINUS = 86,
	eKEY_KP_PLUS = 87,
	eKEY_KP_ENTER = 88,
	eKEY_KP_1 = 89,
	eKEY_KP_2 = 90,
	eKEY_KP_3 = 91,
	eKEY_KP_4 = 92,
	eKEY_KP_5 = 93,
	eKEY_KP_6 = 94,
	eKEY_KP_7 = 95,
	eKEY_KP_8 = 96,
	eKEY_KP_9 = 97,
	eKEY_KP_0 = 98,
	eKEY_KP_PERIOD = 99,
	eKEY_NONUSBACKSLASH = 100,
	eKEY_APPLICATION = 101,
	eKEY_POWER = 102,
	eKEY_KP_EQUALS = 103,
	eKEY_F13 = 104,
	eKEY_F14 = 105,
	eKEY_F15 = 106,
	eKEY_F16 = 107,
	eKEY_F17 = 108,
	eKEY_F18 = 109,
	eKEY_F19 = 110,
	eKEY_F20 = 111,
	eKEY_F21 = 112,
	eKEY_F22 = 113,
	eKEY_F23 = 114,
	eKEY_F24 = 115,
	eKEY_EXECUTE = 116,
	eKEY_HELP = 117,
	eKEY_MENU = 118,
	eKEY_SELECT = 119,
	eKEY_STOP = 120,
	eKEY_AGAIN = 121,
	eKEY_UNDO = 122,
	eKEY_CUT = 123,
	eKEY_COPY = 124,
	eKEY_PASTE = 125,
	eKEY_FIND = 126,
	eKEY_MUTE = 127,
	eKEY_VOLUMEUP = 128,
	eKEY_VOLUMEDOWN = 129,
	eKEY_KP_COMMA = 133,
	eKEY_KP_EQUALSAS400 = 134,
	eKEY_INTERNATIONAL1 = 135,
	eKEY_INTERNATIONAL2 = 136,
	eKEY_INTERNATIONAL3 = 137,
	eKEY_INTERNATIONAL4 = 138,
	eKEY_INTERNATIONAL5 = 139,
	eKEY_INTERNATIONAL6 = 140,
	eKEY_INTERNATIONAL7 = 141,
	eKEY_INTERNATIONAL8 = 142,
	eKEY_INTERNATIONAL9 = 143,
	eKEY_LANG1 = 144,
	eKEY_LANG2 = 145,
	eKEY_LANG3 = 146,
	eKEY_LANG4 = 147,
	eKEY_LANG5 = 148,
	eKEY_LANG6 = 149,
	eKEY_LANG7 = 150,
	eKEY_LANG8 = 151,
	eKEY_LANG9 = 152,
	eKEY_ALTERASE = 153,
	eKEY_SYSREQ = 154,
	eKEY_CANCEL = 155,
	eKEY_CLEAR = 156,
	eKEY_PRIOR = 157,
	eKEY_RETURN2 = 158,
	eKEY_SEPARATOR = 159,
	eKEY_OUT = 160,
	eKEY_OPER = 161,
	eKEY_CLEARAGAIN = 162,
	eKEY_CRSEL = 163,
	eKEY_EXSEL = 164,
	eKEY_KP_00 = 176,
	eKEY_KP_000 = 177,
	eKEY_THOUSANDSSEPARATOR = 178,
	eKEY_DECIMALSEPARATOR = 179,
	eKEY_CURRENCYUNIT = 180,
	eKEY_CURRENCYSUBUNIT = 181,
	eKEY_KP_LEFTPAREN = 182,
	eKEY_KP_RIGHTPAREN = 183,
	eKEY_KP_LEFTBRACE = 184,
	eKEY_KP_RIGHTBRACE = 185,
	eKEY_KP_TAB = 186,
	eKEY_KP_BACKSPACE = 187,
	eKEY_KP_A = 188,
	eKEY_KP_B = 189,
	eKEY_KP_C = 190,
	eKEY_KP_D = 191,
	eKEY_KP_E = 192,
	eKEY_KP_F = 193,
	eKEY_KP_XOR = 194,
	eKEY_KP_POWER = 195,
	eKEY_KP_PERCENT = 196,
	eKEY_KP_LESS = 197,
	eKEY_KP_GREATER = 198,
	eKEY_KP_AMPERSAND = 199,
	eKEY_KP_DBLAMPERSAND = 200,
	eKEY_KP_VERTICALBAR = 201,
	eKEY_KP_DBLVERTICALBAR = 202,
	eKEY_KP_COLON = 203,
	eKEY_KP_HASH = 204,
	eKEY_KP_SPACE = 205,
	eKEY_KP_AT = 206,
	eKEY_KP_EXCLAM = 207,
	eKEY_KP_MEMSTORE = 208,
	eKEY_KP_MEMRECALL = 209,
	eKEY_KP_MEMCLEAR = 210,
	eKEY_KP_MEMADD = 211,
	eKEY_KP_MEMSUBTRACT = 212,
	eKEY_KP_MEMMULTIPLY = 213,
	eKEY_KP_MEMDIVIDE = 214,
	eKEY_KP_PLUSMINUS = 215,
	eKEY_KP_CLEAR = 216,
	eKEY_KP_CLEARENTRY = 217,
	eKEY_KP_BINARY = 218,
	eKEY_KP_OCTAL = 219,
	eKEY_KP_DECIMAL = 220,
	eKEY_KP_HEXADECIMAL = 221,
	eKEY_LCTRL = 224,
	eKEY_LSHIFT = 225,
	eKEY_LALT = 226,
	eKEY_LGUI = 227,
	eKEY_RCTRL = 228,
	eKEY_RSHIFT = 229,
	eKEY_RALT = 230,
	eKEY_RGUI = 231,
	eKEY_MODE = 257,
	eKEY_AUDIONEXT = 258,
	eKEY_AUDIOPREV = 259,
	eKEY_AUDIOSTOP = 260,
	eKEY_AUDIOPLAY = 261,
	eKEY_AUDIOMUTE = 262,
	eKEY_MEDIASELECT = 263,
	eKEY_WWW = 264,
	eKEY_MAIL = 265,
	eKEY_CALCULATOR = 266,
	eKEY_COMPUTER = 267,
	eKEY_AC_SEARCH = 268,
	eKEY_AC_HOME = 269,
	eKEY_AC_BACK = 270,
	eKEY_AC_FORWARD = 271,
	eKEY_AC_STOP = 272,
	eKEY_AC_REFRESH = 273,
	eKEY_AC_BOOKMARKS = 274,
	eKEY_BRIGHTNESSDOWN = 275,
	eKEY_BRIGHTNESSUP = 276,
	eKEY_DISPLAYSWITCH = 277,
	eKEY_KBDILLUMTOGGLE = 278,
	eKEY_KBDILLUMDOWN = 279,
	eKEY_KBDILLUMUP = 280,
	eKEY_EJECT = 281,
	eKEY_SLEEP = 282,
	eKEY_APP1 = 283,
	eKEY_APP2 = 284,
};

class IInputDevice
{
public:
    IInputDevice() {  }
    virtual ~IInputDevice() {  }
    
    virtual void Update() = 0;

	virtual void SetMouseCurserLocked(bool locked) = 0;

	virtual bool IsKeyDown(int key) const = 0;

	virtual bool IsMouseButtonDown(int mouseButton) const = 0;
    virtual const SVector2_i32 &GetMousePosition() const = 0;
	virtual const SVector2_i32 &GetMouseMotion() const = 0;
};

#endif
