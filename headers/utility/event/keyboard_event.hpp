/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once

#include <bitset>
#include <cstdint>

#include "utility/event/event.hpp"

namespace utility::event {

/**
 * @brief Keyboard event representation.
 *
 * Represents keyboard events, including key codes and modifier states.
 */
class KeyboardEvent : public Event {
public:
  /**
   * @brief Key scan codes.
   */
  enum class ScanCode : const std::uint16_t {
    UNKNOWN = 0, /**< Unknown scan code */

    A = 4,  /**< A key */
    B = 5,  /**< B key */
    C = 6,  /**< C key */
    D = 7,  /**< D key */
    E = 8,  /**< E key */
    F = 9,  /**< F key */
    G = 10, /**< G key */
    H = 11, /**< H key */
    I = 12, /**< I key */
    J = 13, /**< J key */
    K = 14, /**< K key */
    L = 15, /**< L key */
    M = 16, /**< M key */
    N = 17, /**< N key */
    O = 18, /**< O key */
    P = 19, /**< P key */
    Q = 20, /**< Q key */
    R = 21, /**< R key */
    S = 22, /**< S key */
    T = 23, /**< T key */
    U = 24, /**< U key */
    V = 25, /**< V key */
    W = 26, /**< W key */
    X = 27, /**< X key */
    Y = 28, /**< Y key */
    Z = 29, /**< Z key */

    NUM_1 = 30, /**< 1 key */
    NUM_2 = 31, /**< 2 key */
    NUM_3 = 32, /**< 3 key */
    NUM_4 = 33, /**< 4 key */
    NUM_5 = 34, /**< 5 key */
    NUM_6 = 35, /**< 6 key */
    NUM_7 = 36, /**< 7 key */
    NUM_8 = 37, /**< 8 key */
    NUM_9 = 38, /**< 9 key */
    NUM_0 = 39, /**< 0 key */

    RETURN = 40,    /**< Return key */
    ESCAPE = 41,    /**< Escape key */
    BACKSPACE = 42, /**< Backspace key */
    TAB = 43,       /**< Tab key */
    SPACE = 44,     /**< Space key */

    MINUS = 45,        /**< Minus key */
    EQUALS = 46,       /**< Equals key */
    LEFTBRACKET = 47,  /**< Left bracket key */
    RIGHTBRACKET = 48, /**< Right bracket key */
    BACKSLASH =
        49, /**< Backslash key. Located at the lower left of the return key on
               ISO keyboards and at the right end of the QWERTY row on ANSI
               keyboards. Produces REVERSE SOLIDUS (backslash) and VERTICAL LINE
               in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac
               layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN
               and POUND SIGN in a Swiss German layout, NUMBER SIGN and
               APOSTROPHE in a German layout, GRAVE ACCENT and POUND SIGN in a
               French Mac layout, and ASTERISK and MICRO SIGN in a French
               Windows layout. */
    NONUSHASH =
        50, /**< ISO USB keyboards actually use this code instead of 49 for the
               same key, but all OSes I've seen treat the two codes identically.
             */
    SEMICOLON = 51,  /**< Semicolon key */
    APOSTROPHE = 52, /**< Apostrophe key */
    GRAVE =
        53, /**< Grave key. Located in the top left corner (on both ANSI and ISO
               keyboards). Produces GRAVE ACCENT and TILDE in a US Windows
               layout and in US and UK Mac layouts on ANSI keyboards, GRAVE
               ACCENT and NOT SIGN in a UK Windows layout, SECTION SIGN and
               PLUS-MINUS SIGN in US and UK Mac layouts on ISO keyboards,
               SECTION SIGN and DEGREE SIGN in a Swiss German layout (Mac: only
               on ISO keyboards), CIRCUMFLEX ACCENT and DEGREE SIGN in a German
               layout (Mac: only on ISO keyboards), SUPERSCRIPT TWO and TILDE in
               a French Windows layout, COMMERCIAL AT and NUMBER SIGN in a
               French Mac layout on ISO keyboards, and LESS-THAN SIGN and
               GREATER-THAN SIGN in a Swiss German, German, or French Mac layout
               on ANSI keyboards. */
    COMMA = 54,  /**< Comma key */
    PERIOD = 55, /**< Period key */
    SLASH = 56,  /**< Slash key */

    CAPSLOCK = 57, /**< Caps Lock key */

    F1 = 58,  /**< F1 key */
    F2 = 59,  /**< F2 key */
    F3 = 60,  /**< F3 key */
    F4 = 61,  /**< F4 key */
    F5 = 62,  /**< F5 key */
    F6 = 63,  /**< F6 key */
    F7 = 64,  /**< F7 key */
    F8 = 65,  /**< F8 key */
    F9 = 66,  /**< F9 key */
    F10 = 67, /**< F10 key */
    F11 = 68, /**< F11 key */
    F12 = 69, /**< F12 key */

    PRINTSCREEN = 70, /**< Print Screen key */
    SCROLLLOCK = 71,  /**< Scroll Lock key */
    PAUSE = 72,       /**< Pause key */
    INSERT = 73,      /**< Insert key (help on some Mac keyboards) */
    HOME = 74,        /**< Home key */
    PAGEUP = 75,      /**< Page Up key */
    DELETE = 76,      /**< Delete key */
    END = 77,         /**< End key */
    PAGEDOWN = 78,    /**< Page Down key */
    RIGHT = 79,       /**< Right arrow key */
    LEFT = 80,        /**< Left arrow key */
    DOWN = 81,        /**< Down arrow key */
    UP = 82,          /**< Up arrow key */

    NUMLOCKCLEAR = 83, /**< Num Lock key (clear on Mac keyboards) */
    KP_DIVIDE = 84,    /**< Keypad divide key */
    KP_MULTIPLY = 85,  /**< Keypad multiply key */
    KP_MINUS = 86,     /**< Keypad minus key */
    KP_PLUS = 87,      /**< Keypad plus key */
    KP_ENTER = 88,     /**< Keypad enter key */
    KP_1 = 89,         /**< Keypad 1 key */
    KP_2 = 90,         /**< Keypad 2 key */
    KP_3 = 91,         /**< Keypad 3 key */
    KP_4 = 92,         /**< Keypad 4 key */
    KP_5 = 93,         /**< Keypad 5 key */
    KP_6 = 94,         /**< Keypad 6 key */
    KP_7 = 95,         /**< Keypad 7 key */
    KP_8 = 96,         /**< Keypad 8 key */
    KP_9 = 97,         /**< Keypad 9 key */
    KP_0 = 98,         /**< Keypad 0 key */
    KP_PERIOD = 99,    /**< Keypad period key */

    NONUSBACKSLASH =
        100, /**< This is the additional key that ISO keyboards have over ANSI
                ones, located between left shift and Z. Produces GRAVE ACCENT
                and TILDE in a US or UK Mac layout, REVERSE SOLIDUS (backslash)
                and VERTICAL LINE in a US or UK Windows layout, and LESS-THAN
                SIGN and GREATER-THAN SIGN in a Swiss German, German, or French
                layout. */
    APPLICATION = 101,    /**< Windows contextual menu, compose */
    POWER = 102,          /**< Power key */
    KP_EQUALS = 103,      /**< Keypad equals key */
    F13 = 104,            /**< F13 key */
    F14 = 105,            /**< F14 key */
    F15 = 106,            /**< F15 key */
    F16 = 107,            /**< F16 key */
    F17 = 108,            /**< F17 key */
    F18 = 109,            /**< F18 key */
    F19 = 110,            /**< F19 key */
    F20 = 111,            /**< F20 key */
    F21 = 112,            /**< F21 key */
    F22 = 113,            /**< F22 key */
    F23 = 114,            /**< F23 key */
    F24 = 115,            /**< F24 key */
    EXECUTE = 116,        /**< Execute key */
    HELP = 117,           /**< Help key (AL Integrated Help Center) */
    MENU = 118,           /**< Menu key */
    SELECT = 119,         /**< Select key */
    STOP = 120,           /**< Stop key (AC Stop) */
    AGAIN = 121,          /**< Again key (AC Redo/Repeat) */
    UNDO = 122,           /**< Undo key (AC Undo) */
    CUT = 123,            /**< Cut key (AC Cut) */
    COPY = 124,           /**< Copy key (AC Copy) */
    PASTE = 125,          /**< Paste key (AC Paste) */
    FIND = 126,           /**< Find key (AC Find) */
    MUTE = 127,           /**< Mute key */
    VOLUMEUP = 128,       /**< Volume up key */
    VOLUMEDOWN = 129,     /**< Volume down key */
    KP_COMMA = 133,       /**< Keypad comma key */
    KP_EQUALSAS400 = 134, /**< Keypad equals (AS400) key */

    INTERNATIONAL1 = 135, /**< Used on Asian keyboards */
    INTERNATIONAL2 = 136, /**< Used on Asian keyboards */
    INTERNATIONAL3 = 137, /**< Yen key */
    INTERNATIONAL4 = 138, /**< Used on Asian keyboards */
    INTERNATIONAL5 = 139, /**< Used on Asian keyboards */
    INTERNATIONAL6 = 140, /**< Used on Asian keyboards */
    INTERNATIONAL7 = 141, /**< Used on Asian keyboards */
    INTERNATIONAL8 = 142, /**< Used on Asian keyboards */
    INTERNATIONAL9 = 143, /**< Used on Asian keyboards */
    LANG1 = 144,          /**< Hangul/English toggle */
    LANG2 = 145,          /**< Hanja conversion */
    LANG3 = 146,          /**< Katakana */
    LANG4 = 147,          /**< Hiragana */
    LANG5 = 148,          /**< Zenkaku/Hankaku */
    LANG6 = 149,          /**< Reserved */
    LANG7 = 150,          /**< Reserved */
    LANG8 = 151,          /**< Reserved */
    LANG9 = 152,          /**< Reserved */

    ALTERASE = 153,   /**< Erase-Eaze */
    SYSREQ = 154,     /**< Sysreq key */
    CANCEL = 155,     /**< Cancel key (AC Cancel) */
    CLEAR = 156,      /**< Clear key */
    PRIOR = 157,      /**< Prior key */
    RETURN2 = 158,    /**< Return2 key */
    SEPARATOR = 159,  /**< Separator key */
    OUT = 160,        /**< Out key */
    OPER = 161,       /**< Oper key */
    CLEARAGAIN = 162, /**< Clear again key */
    CRSEL = 163,      /**< Crsel key */
    EXSEL = 164,      /**< Exsel key */

    KP_00 = 176,              /**< Keypad 00 key */
    KP_000 = 177,             /**< Keypad 000 key */
    THOUSANDSSEPARATOR = 178, /**< Thousands separator key */
    DECIMALSEPARATOR = 179,   /**< Decimal separator key */
    CURRENCYUNIT = 180,       /**< Currency unit key */
    CURRENCYSUBUNIT = 181,    /**< Currency subunit key */
    KP_LEFTPAREN = 182,       /**< Keypad left parenthesis key */
    KP_RIGHTPAREN = 183,      /**< Keypad right parenthesis key */
    KP_LEFTBRACE = 184,       /**< Keypad left brace key */
    KP_RIGHTBRACE = 185,      /**< Keypad right brace key */
    KP_TAB = 186,             /**< Keypad tab key */
    KP_BACKSPACE = 187,       /**< Keypad backspace key */
    KP_A = 188,               /**< Keypad A key */
    KP_B = 189,               /**< Keypad B key */
    KP_C = 190,               /**< Keypad C key */
    KP_D = 191,               /**< Keypad D key */
    KP_E = 192,               /**< Keypad E key */
    KP_F = 193,               /**< Keypad F key */
    KP_XOR = 194,             /**< Keypad XOR key */
    KP_POWER = 195,           /**< Keypad power key */
    KP_PERCENT = 196,         /**< Keypad percent key */
    KP_LESS = 197,            /**< Keypad less than key */
    KP_GREATER = 198,         /**< Keypad greater than key */
    KP_AMPERSAND = 199,       /**< Keypad ampersand key */
    KP_DBLAMPERSAND = 200,    /**< Keypad double ampersand key */
    KP_VERTICALBAR = 201,     /**< Keypad vertical bar key */
    KP_DBLVERTICALBAR = 202,  /**< Keypad double vertical bar key */
    KP_COLON = 203,           /**< Keypad colon key */
    KP_HASH = 204,            /**< Keypad hash key */
    KP_SPACE = 205,           /**< Keypad space key */
    KP_AT = 206,              /**< Keypad at key */
    KP_EXCLAM = 207,          /**< Keypad exclamation mark key */
    KP_MEMSTORE = 208,        /**< Keypad memory store key */
    KP_MEMRECALL = 209,       /**< Keypad memory recall key */
    KP_MEMCLEAR = 210,        /**< Keypad memory clear key */
    KP_MEMADD = 211,          /**< Keypad memory add key */
    KP_MEMSUBTRACT = 212,     /**< Keypad memory subtract key */
    KP_MEMMULTIPLY = 213,     /**< Keypad memory multiply key */
    KP_MEMDIVIDE = 214,       /**< Keypad memory divide key */
    KP_PLUSMINUS = 215,       /**< Keypad plus/minus key */
    KP_CLEAR = 216,           /**< Keypad clear key */
    KP_CLEARENTRY = 217,      /**< Keypad clear entry key */
    KP_BINARY = 218,          /**< Keypad binary key */
    KP_OCTAL = 219,           /**< Keypad octal key */
    KP_DECIMAL = 220,         /**< Keypad decimal key */
    KP_HEXADECIMAL = 221,     /**< Keypad hexadecimal key */

    LCTRL = 224,  /**< Left control key */
    LSHIFT = 225, /**< Left shift key */
    LALT = 226,   /**< Left alt key (option) */
    LGUI = 227,   /**< Left GUI key (windows, command, meta) */
    RCTRL = 228,  /**< Right control key */
    RSHIFT = 229, /**< Right shift key */
    RALT = 230,   /**< Right alt key (alt gr, option) */
    RGUI = 231,   /**< Right GUI key (windows, command, meta) */

    MODE = 257, /**< Mode key */

    /* Usage page 0x0C */
    SLEEP = 258, /**< Sleep key */
    WAKE = 259,  /**< Wake key */

    CHANNEL_INCREMENT = 260, /**< Channel increment key */
    CHANNEL_DECREMENT = 261, /**< Channel decrement key */

    MEDIA_PLAY = 262,           /**< Media play key */
    MEDIA_PAUSE = 263,          /**< Media pause key */
    MEDIA_RECORD = 264,         /**< Media record key */
    MEDIA_FAST_FORWARD = 265,   /**< Media fast forward key */
    MEDIA_REWIND = 266,         /**< Media rewind key */
    MEDIA_NEXT_TRACK = 267,     /**< Media next track key */
    MEDIA_PREVIOUS_TRACK = 268, /**< Media previous track key */
    MEDIA_STOP = 269,           /**< Media stop key */
    MEDIA_EJECT = 270,          /**< Media eject key */
    MEDIA_PLAY_PAUSE = 271,     /**< Media play/pause key */
    MEDIA_SELECT = 272,         /**< Media select key */

    AC_NEW = 273,        /**< AC new key */
    AC_OPEN = 274,       /**< AC open key */
    AC_CLOSE = 275,      /**< AC close key */
    AC_EXIT = 276,       /**< AC exit key */
    AC_SAVE = 277,       /**< AC save key */
    AC_PRINT = 278,      /**< AC print key */
    AC_PROPERTIES = 279, /**< AC properties key */

    AC_SEARCH = 280,    /**< AC search key */
    AC_HOME = 281,      /**< AC home key */
    AC_BACK = 282,      /**< AC back key */
    AC_FORWARD = 283,   /**< AC forward key */
    AC_STOP = 284,      /**< AC stop key */
    AC_REFRESH = 285,   /**< AC refresh key */
    AC_BOOKMARKS = 286, /**< AC bookmarks key */

    /* Mobile keys */
    SOFTLEFT = 287,  /**< Soft left key */
    SOFTRIGHT = 288, /**< Soft right key */
    CALL = 289,      /**< Call key */
    ENDCALL = 290,   /**< End call key */

    RESERVED = 400, /**< 400-500 reserved for dynamic keycodes */

    COUNT = 512 /**< Not a key, just marks the number of scancodes
                                for array bounds */

  };

  /**
   * @brief Virtual key codes derived from keyboard scancodes.
   *
   * Virtual key codes represent actual keys pressed on the keyboard,
   * including printable characters and special function keys.
   */
  enum class KeyCode : const std::int32_t {
    UNKNOWN = 0x00000000u,              /**< Unknown key */
    RETURN = 0x0000000du,               /**< Return key ('\\r') */
    ESCAPE = 0x0000001bu,               /**< Escape key ('\\x1B') */
    BACKSPACE = 0x00000008u,            /**< Backspace key ('\\b') */
    TAB = 0x00000009u,                  /**< Tab key ('\\t') */
    SPACE = 0x00000020u,                /**< Space key (' ') */
    EXCLAIM = 0x00000021u,              /**< Exclamation mark key ('!') */
    DBLAPOSTROPHE = 0x00000022u,        /**< Double apostrophe key ('"') */
    HASH = 0x00000023u,                 /**< Hash key ('#') */
    DOLLAR = 0x00000024u,               /**< Dollar key ('$') */
    PERCENT = 0x00000025u,              /**< Percent key ('%') */
    AMPERSAND = 0x00000026u,            /**< Ampersand key ('&') */
    APOSTROPHE = 0x00000027u,           /**< Apostrophe key ('\\'') */
    LEFTPAREN = 0x00000028u,            /**< Left parenthesis key ('(') */
    RIGHTPAREN = 0x00000029u,           /**< Right parenthesis key (')') */
    ASTERISK = 0x0000002au,             /**< Asterisk key ('*') */
    PLUS = 0x0000002bu,                 /**< Plus key ('+') */
    COMMA = 0x0000002cu,                /**< Comma key (',') */
    MINUS = 0x0000002du,                /**< Minus key ('-') */
    PERIOD = 0x0000002eu,               /**< Period key ('.') */
    SLASH = 0x0000002fu,                /**< Slash key ('/') */
    NUM_0 = 0x00000030u,                /**< 0 key ('0') */
    NUM_1 = 0x00000031u,                /**< 1 key ('1') */
    NUM_2 = 0x00000032u,                /**< 2 key ('2') */
    NUM_3 = 0x00000033u,                /**< 3 key ('3') */
    NUM_4 = 0x00000034u,                /**< 4 key ('4') */
    NUM_5 = 0x00000035u,                /**< 5 key ('5') */
    NUM_6 = 0x00000036u,                /**< 6 key ('6') */
    NUM_7 = 0x00000037u,                /**< 7 key ('7') */
    NUM_8 = 0x00000038u,                /**< 8 key ('8') */
    NUM_9 = 0x00000039u,                /**< 9 key ('9') */
    COLON = 0x0000003au,                /**< Colon key (':') */
    SEMICOLON = 0x0000003bu,            /**< Semicolon key (';') */
    LESS = 0x0000003cu,                 /**< Less than key ('<') */
    EQUALS = 0x0000003du,               /**< Equals key ('=') */
    GREATER = 0x0000003eu,              /**< Greater than key ('>') */
    QUESTION = 0x0000003fu,             /**< Question mark key ('?') */
    AT = 0x00000040u,                   /**< At key ('@') */
    LEFTBRACKET = 0x0000005bu,          /**< Left bracket key ('[') */
    BACKSLASH = 0x0000005cu,            /**< Backslash key ('\\') */
    RIGHTBRACKET = 0x0000005du,         /**< Right bracket key (']') */
    CARET = 0x0000005eu,                /**< Caret key ('^') */
    UNDERSCORE = 0x0000005fu,           /**< Underscore key ('_') */
    GRAVE = 0x00000060u,                /**< Grave key ('\`') */
    A = 0x00000061u,                    /**< A key ('a') */
    B = 0x00000062u,                    /**< B key ('b') */
    C = 0x00000063u,                    /**< C key ('c') */
    D = 0x00000064u,                    /**< D key ('d') */
    E = 0x00000065u,                    /**< E key ('e') */
    F = 0x00000066u,                    /**< F key ('f') */
    G = 0x00000067u,                    /**< G key ('g') */
    H = 0x00000068u,                    /**< H key ('h') */
    I = 0x00000069u,                    /**< I key ('i') */
    J = 0x0000006au,                    /**< J key ('j') */
    K = 0x0000006bu,                    /**< K key ('k') */
    L = 0x0000006cu,                    /**< L key ('l') */
    M = 0x0000006du,                    /**< M key ('m') */
    N = 0x0000006eu,                    /**< N key ('n') */
    O = 0x0000006fu,                    /**< O key ('o') */
    P = 0x00000070u,                    /**< P key ('p') */
    Q = 0x00000071u,                    /**< Q key ('q') */
    R = 0x00000072u,                    /**< R key ('r') */
    S = 0x00000073u,                    /**< S key ('s') */
    T = 0x00000074u,                    /**< T key ('t') */
    U = 0x00000075u,                    /**< U key ('u') */
    V = 0x00000076u,                    /**< V key ('v') */
    W = 0x00000077u,                    /**< W key ('w') */
    X = 0x00000078u,                    /**< X key ('x') */
    Y = 0x00000079u,                    /**< Y key ('y') */
    Z = 0x0000007au,                    /**< Z key ('z') */
    LEFTBRACE = 0x0000007bu,            /**< Left brace key ('{') */
    PIPE = 0x0000007cu,                 /**< Pipe key ('|') */
    RIGHTBRACE = 0x0000007du,           /**< Right brace key ('}') */
    TILDE = 0x0000007eu,                /**< Tilde key ('~') */
    DELETE = 0x0000007fu,               /**< Delete key ('\\x7F') */
    PLUSMINUS = 0x000000b1u,            /**< Plus/minus key ('\\xB1') */
    CAPSLOCK = 0x40000039u,             /**< Caps Lock key */
    F1 = 0x4000003au,                   /**< F1 key */
    F2 = 0x4000003bu,                   /**< F2 key */
    F3 = 0x4000003cu,                   /**< F3 key */
    F4 = 0x4000003du,                   /**< F4 key */
    F5 = 0x4000003eu,                   /**< F5 key */
    F6 = 0x4000003fu,                   /**< F6 key */
    F7 = 0x40000040u,                   /**< F7 key */
    F8 = 0x40000041u,                   /**< F8 key */
    F9 = 0x40000042u,                   /**< F9 key */
    F10 = 0x40000043u,                  /**< F10 key */
    F11 = 0x40000044u,                  /**< F11 key */
    F12 = 0x40000045u,                  /**< F12 key */
    PRINTSCREEN = 0x40000046u,          /**< Print Screen key */
    SCROLLLOCK = 0x40000047u,           /**< Scroll Lock key */
    PAUSE = 0x40000048u,                /**< Pause key */
    INSERT = 0x40000049u,               /**< Insert key */
    HOME = 0x4000004au,                 /**< Home key */
    PAGEUP = 0x4000004bu,               /**< Page Up key */
    END = 0x4000004du,                  /**< End key */
    PAGEDOWN = 0x4000004eu,             /**< Page Down key */
    RIGHT = 0x4000004fu,                /**< Right arrow key */
    LEFT = 0x40000050u,                 /**< Left arrow key */
    DOWN = 0x40000051u,                 /**< Down arrow key */
    UP = 0x40000052u,                   /**< Up arrow key */
    NUMLOCKCLEAR = 0x40000053u,         /**< Num Lock key */
    KP_DIVIDE = 0x40000054u,            /**< Keypad divide key */
    KP_MULTIPLY = 0x40000055u,          /**< Keypad multiply key */
    KP_MINUS = 0x40000056u,             /**< Keypad minus key */
    KP_PLUS = 0x40000057u,              /**< Keypad plus key */
    KP_ENTER = 0x40000058u,             /**< Keypad enter key */
    KP_1 = 0x40000059u,                 /**< Keypad 1 key */
    KP_2 = 0x4000005au,                 /**< Keypad 2 key */
    KP_3 = 0x4000005bu,                 /**< Keypad 3 key */
    KP_4 = 0x4000005cu,                 /**< Keypad 4 key */
    KP_5 = 0x4000005du,                 /**< Keypad 5 key */
    KP_6 = 0x4000005eu,                 /**< Keypad 6 key */
    KP_7 = 0x4000005fu,                 /**< Keypad 7 key */
    KP_8 = 0x40000060u,                 /**< Keypad 8 key */
    KP_9 = 0x40000061u,                 /**< Keypad 9 key */
    KP_0 = 0x40000062u,                 /**< Keypad 0 key */
    KP_PERIOD = 0x40000063u,            /**< Keypad period key */
    APPLICATION = 0x40000065u,          /**< Application key */
    POWER = 0x40000066u,                /**< Power key */
    KP_EQUALS = 0x40000067u,            /**< Keypad equals key */
    F13 = 0x40000068u,                  /**< F13 key */
    F14 = 0x40000069u,                  /**< F14 key */
    F15 = 0x4000006au,                  /**< F15 key */
    F16 = 0x4000006bu,                  /**< F16 key */
    F17 = 0x4000006cu,                  /**< F17 key */
    F18 = 0x4000006du,                  /**< F18 key */
    F19 = 0x4000006eu,                  /**< F19 key */
    F20 = 0x4000006fu,                  /**< F20 key */
    F21 = 0x40000070u,                  /**< F21 key */
    F22 = 0x40000071u,                  /**< F22 key */
    F23 = 0x40000072u,                  /**< F23 key */
    F24 = 0x40000073u,                  /**< F24 key */
    EXECUTE = 0x40000074u,              /**< Execute key */
    HELP = 0x40000075u,                 /**< Help key */
    MENU = 0x40000076u,                 /**< Menu key */
    SELECT = 0x40000077u,               /**< Select key */
    STOP = 0x40000078u,                 /**< Stop key */
    AGAIN = 0x40000079u,                /**< Again key */
    UNDO = 0x4000007au,                 /**< Undo key */
    CUT = 0x4000007bu,                  /**< Cut key */
    COPY = 0x4000007cu,                 /**< Copy key */
    PASTE = 0x4000007du,                /**< Paste key */
    FIND = 0x4000007eu,                 /**< Find key */
    MUTE = 0x4000007fu,                 /**< Mute key */
    VOLUMEUP = 0x40000080u,             /**< Volume up key */
    VOLUMEDOWN = 0x40000081u,           /**< Volume down key */
    KP_COMMA = 0x40000085u,             /**< Keypad comma key */
    KP_EQUALSAS400 = 0x40000086u,       /**< Keypad equals (AS400) key */
    ALTERASE = 0x40000099u,             /**< Alterase key */
    SYSREQ = 0x4000009au,               /**< Sysreq key */
    CANCEL = 0x4000009bu,               /**< Cancel key */
    CLEAR = 0x4000009cu,                /**< Clear key */
    PRIOR = 0x4000009du,                /**< Prior key */
    RETURN2 = 0x4000009eu,              /**< Return2 key */
    SEPARATOR = 0x4000009fu,            /**< Separator key */
    OUT = 0x400000a0u,                  /**< Out key */
    OPER = 0x400000a1u,                 /**< Oper key */
    CLEARAGAIN = 0x400000a2u,           /**< Clear again key */
    CRSEL = 0x400000a3u,                /**< Crsel key */
    EXSEL = 0x400000a4u,                /**< Exsel key */
    KP_00 = 0x400000b0u,                /**< Keypad 00 key */
    KP_000 = 0x400000b1u,               /**< Keypad 000 key */
    THOUSANDSSEPARATOR = 0x400000b2u,   /**< Thousands separator key */
    DECIMALSEPARATOR = 0x400000b3u,     /**< Decimal separator key */
    CURRENCYUNIT = 0x400000b4u,         /**< Currency unit key */
    CURRENCYSUBUNIT = 0x400000b5u,      /**< Currency subunit key */
    KP_LEFTPAREN = 0x400000b6u,         /**< Keypad left parenthesis key */
    KP_RIGHTPAREN = 0x400000b7u,        /**< Keypad right parenthesis key */
    KP_LEFTBRACE = 0x400000b8u,         /**< Keypad left brace key */
    KP_RIGHTBRACE = 0x400000b9u,        /**< Keypad right brace key */
    KP_TAB = 0x400000bau,               /**< Keypad tab key */
    KP_BACKSPACE = 0x400000bbu,         /**< Keypad backspace key */
    KP_A = 0x400000bcu,                 /**< Keypad A key */
    KP_B = 0x400000bdu,                 /**< Keypad B key */
    KP_C = 0x400000beu,                 /**< Keypad C key */
    KP_D = 0x400000bfu,                 /**< Keypad D key */
    KP_E = 0x400000c0u,                 /**< Keypad E key */
    KP_F = 0x400000c1u,                 /**< Keypad F key */
    KP_XOR = 0x400000c2u,               /**< Keypad XOR key */
    KP_POWER = 0x400000c3u,             /**< Keypad power key */
    KP_PERCENT = 0x400000c4u,           /**< Keypad percent key */
    KP_LESS = 0x400000c5u,              /**< Keypad less than key */
    KP_GREATER = 0x400000c6u,           /**< Keypad greater than key */
    KP_AMPERSAND = 0x400000c7u,         /**< Keypad ampersand key */
    KP_DBLAMPERSAND = 0x400000c8u,      /**< Keypad double ampersand key */
    KP_VERTICALBAR = 0x400000c9u,       /**< Keypad vertical bar key */
    KP_DBLVERTICALBAR = 0x400000cau,    /**< Keypad double vertical bar key */
    KP_COLON = 0x400000cbu,             /**< Keypad colon key */
    KP_HASH = 0x400000ccu,              /**< Keypad hash key */
    KP_SPACE = 0x400000cdu,             /**< Keypad space key */
    KP_AT = 0x400000ceu,                /**< Keypad at key */
    KP_EXCLAM = 0x400000cfu,            /**< Keypad exclamation mark key */
    KP_MEMSTORE = 0x400000d0u,          /**< Keypad memory store key */
    KP_MEMRECALL = 0x400000d1u,         /**< Keypad memory recall key */
    KP_MEMCLEAR = 0x400000d2u,          /**< Keypad memory clear key */
    KP_MEMADD = 0x400000d3u,            /**< Keypad memory add key */
    KP_MEMSUBTRACT = 0x400000d4u,       /**< Keypad memory subtract key */
    KP_MEMMULTIPLY = 0x400000d5u,       /**< Keypad memory multiply key */
    KP_MEMDIVIDE = 0x400000d6u,         /**< Keypad memory divide key */
    KP_PLUSMINUS = 0x400000d7u,         /**< Keypad plus/minus key */
    KP_CLEAR = 0x400000d8u,             /**< Keypad clear key */
    KP_CLEARENTRY = 0x400000d9u,        /**< Keypad clear entry key */
    KP_BINARY = 0x400000dau,            /**< Keypad binary key */
    KP_OCTAL = 0x400000dbu,             /**< Keypad octal key */
    KP_DECIMAL = 0x400000dcu,           /**< Keypad decimal key */
    KP_HEXADECIMAL = 0x400000ddu,       /**< Keypad hexadecimal key */
    LCTRL = 0x400000e0u,                /**< Left control key */
    LSHIFT = 0x400000e1u,               /**< Left shift key */
    LALT = 0x400000e2u,                 /**< Left alt key */
    LGUI = 0x400000e3u,                 /**< Left GUI key */
    RCTRL = 0x400000e4u,                /**< Right control key */
    RSHIFT = 0x400000e5u,               /**< Right shift key */
    RALT = 0x400000e6u,                 /**< Right alt key */
    RGUI = 0x400000e7u,                 /**< Right GUI key */
    MODE = 0x40000101u,                 /**< Mode key */
    SLEEP = 0x40000102u,                /**< Sleep key */
    WAKE = 0x40000103u,                 /**< Wake key */
    CHANNEL_INCREMENT = 0x40000104u,    /**< Channel increment key */
    CHANNEL_DECREMENT = 0x40000105u,    /**< Channel decrement key */
    MEDIA_PLAY = 0x40000106u,           /**< Media play key */
    MEDIA_PAUSE = 0x40000107u,          /**< Media pause key */
    MEDIA_RECORD = 0x40000108u,         /**< Media record key */
    MEDIA_FAST_FORWARD = 0x40000109u,   /**< Media fast forward key */
    MEDIA_REWIND = 0x4000010au,         /**< Media rewind key */
    MEDIA_NEXT_TRACK = 0x4000010bu,     /**< Media next track key */
    MEDIA_PREVIOUS_TRACK = 0x4000010cu, /**< Media previous track key */
    MEDIA_STOP = 0x4000010du,           /**< Media stop key */
    MEDIA_EJECT = 0x4000010eu,          /**< Media eject key */
    MEDIA_PLAY_PAUSE = 0x4000010fu,     /**< Media play/pause key */
    MEDIA_SELECT = 0x40000110u,         /**< Media select key */
    AC_NEW = 0x40000111u,               /**< AC new key */
    AC_OPEN = 0x40000112u,              /**< AC open key */
    AC_CLOSE = 0x40000113u,             /**< AC close key */
    AC_EXIT = 0x40000114u,              /**< AC exit key */
    AC_SAVE = 0x40000115u,              /**< AC save key */
    AC_PRINT = 0x40000116u,             /**< AC print key */
    AC_PROPERTIES = 0x40000117u,        /**< AC properties key */
    AC_SEARCH = 0x40000118u,            /**< AC search key */
    AC_HOME = 0x40000119u,              /**< AC home key */
    AC_BACK = 0x4000011au,              /**< AC back key */
    AC_FORWARD = 0x4000011bu,           /**< AC forward key */
    AC_STOP = 0x4000011cu,              /**< AC stop key */
    AC_REFRESH = 0x4000011du,           /**< AC refresh key */
    AC_BOOKMARKS = 0x4000011eu,         /**< AC bookmarks key */
    SOFTLEFT = 0x4000011fu,             /**< Soft left key */
    SOFTRIGHT = 0x40000120u,            /**< Soft right key */
    CALL = 0x40000121u,                 /**< Call key */
    ENDCALL = 0x40000122u,              /**< End call key */
    LEFT_TAB = 0x20000001u,             /**< Extended key Left Tab */
    LEVEL5_SHIFT = 0x20000002u,         /**< Extended key Level 5 Shift */
    MULTI_KEY_COMPOSE = 0x20000003u,    /**< Extended key Multi-key Compose */
    LMETA = 0x20000004u,                /**< Extended key Left Meta */
    RMETA = 0x20000005u,                /**< Extended key Right Meta */
    LHYPER = 0x20000006u,               /**< Extended key Left Hyper */
    RHYPER = 0x20000007u,               /**< Extended key Right Hyper */
  };

  /**
   * @brief Key modifier flags.
   *
   * Key modifiers represent the state of modifier keys (like Shift, Ctrl, Alt)
   * during keyboard events.
   */
  enum class KeyModifiers : const std::uint16_t {
    NONE = 0x0000u,   /**< No modifier is applicable. */
    LSHIFT = 0x0001u, /**< The left Shift key is down. */
    RSHIFT = 0x0002u, /**< The right Shift key is down. */
    LEVEL5 = 0x0004u, /**< The Level 5 Shift key is down. */
    LCTRL = 0x0040u,  /**< The left Ctrl (Control) key is down. */
    RCTRL = 0x0080u,  /**< The right Ctrl (Control) key is down. */
    LALT = 0x0100u,   /**< The left Alt key is down. */
    RALT = 0x0200u,   /**< The right Alt key is down. */
    LGUI = 0x0400u,   /**< The left GUI key (often the Windows key) is down. */
    RGUI = 0x0800u,   /**< The right GUI key (often the Windows key) is down. */
    NUM = 0x1000u,    /**< The Num Lock key (may be located on an
                                  extended keypad) is down. */
    CAPS = 0x2000u,   /**< The Caps Lock key is down. */
    MODE = 0x4000u,   /**< The AltGr key is down. */
    SCROLL = 0x8000u, /**< The Scroll Lock key is down. */

    CTRL = LCTRL | RCTRL,    /**< Any Ctrl key is down. */
    SHIFT = LSHIFT | RSHIFT, /**< Any Shift key is down. */
    ALT = LALT | RALT,       /**< Any Alt key is down. */
    GUI = LGUI | RGUI        /**< Any GUI key is down. */
  };

private:
  ScanCode _scancode{ScanCode::UNKNOWN};
  KeyCode _keycode{KeyCode::UNKNOWN};
  std::bitset<sizeof(KeyModifiers) * 8> _modifiers{
      static_cast<std::size_t>(KeyModifiers::NONE)};
  bool isDownEvent{true};
  bool isRepeatEvent{false};

public:
  /**
   * @brief Default constructor.
   */
  explicit KeyboardEvent(void) = default;

  /**
   * @brief Default destructor.
   */
  ~KeyboardEvent(void) override = default;

  /**
   * @brief Get the keyboard scancode.
   *
   * @return The keyboard scancode.
   */
  ScanCode getScancode(void) const noexcept { return _scancode; }

  /**
   * @brief Set the virtual key code.
   * @param keycode The virtual key code to set.
   */
  void setKeycode(const KeyCode keycode) noexcept { _keycode = keycode; }

  /**
   * @brief Get the virtual key code.
   * @return The virtual key code.
   */
  KeyCode getKeycode(void) const noexcept { return _keycode; }

  /**
   * @brief Set the key modifiers.
   * @param modifiers The key modifiers to set.
   */
  void setModifiers(const KeyModifiers modifiers) noexcept {
    _modifiers = std::bitset<sizeof(KeyModifiers) * 8>(
        static_cast<std::size_t>(modifiers));
  }

  /**
   * @brief Check if a specific key modifier is set.
   * @param modifier The key modifier to check.
   * @return True if the specified modifier is set, false otherwise.
   */
  bool isModifierSet(const KeyModifiers modifier) const noexcept {
    return _modifiers.test(static_cast<std::size_t>(modifier));
  }

  /**
   * @brief Set whether the event is a key down event.
   * @param isDown True if the event is a key down event, false otherwise.
   */
  void setIsDownEvent(const bool isDown) noexcept { isDownEvent = isDown; }

  /**
   * @brief Check if the event is a key down event.
   * @return True if the event is a key down event, false otherwise.
   */
  bool getIsDownEvent(void) const noexcept { return isDownEvent; }

  /**
   * @brief Set whether the event is a key repeat event.
   * @param isRepeat True if the event is a key repeat event, false otherwise.
   */
  void setIsRepeatEvent(const bool isRepeat) noexcept {
    isRepeatEvent = isRepeat;
  }

  /**
   * @brief Check if the event is a key repeat event.
   * @return True if the event is a key repeat event, false otherwise.
   */
  bool getIsRepeatEvent(void) const noexcept { return isRepeatEvent; };
};

} // namespace utility::event
