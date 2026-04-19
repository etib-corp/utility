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
#include <memory>

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
  enum class ScanCode : std::uint16_t {
    Unknown = 0, /**< Unknown scan code */

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

    Num1 = 30, /**< 1 key */
    Num2 = 31, /**< 2 key */
    Num3 = 32, /**< 3 key */
    Num4 = 33, /**< 4 key */
    Num5 = 34, /**< 5 key */
    Num6 = 35, /**< 6 key */
    Num7 = 36, /**< 7 key */
    Num8 = 37, /**< 8 key */
    Num9 = 38, /**< 9 key */
    Num0 = 39, /**< 0 key */

    Return = 40,    /**< Return key */
    Escape = 41,    /**< Escape key */
    Backspace = 42, /**< Backspace key */
    Tab = 43,       /**< Tab key */
    Space = 44,     /**< Space key */

    Minus = 45,        /**< Minus key */
    Equals = 46,       /**< Equals key */
    LeftBracket = 47,  /**< Left bracket key */
    RightBracket = 48, /**< Right bracket key */
    Backslash =
        49, /**< Backslash key. Located at the lower left of the return key on
               ISO keyboards and at the right end of the QWERTY row on ANSI
               keyboards. Produces REVERSE SOLIDUS (backslash) and VERTICAL LINE
               in a US layout, REVERSE SOLIDUS and VERTICAL LINE in a UK Mac
               layout, NUMBER SIGN and TILDE in a UK Windows layout, DOLLAR SIGN
               and POUND SIGN in a Swiss German layout, NUMBER SIGN and
               APOSTROPHE in a German layout, GRAVE ACCENT and POUND SIGN in a
               French Mac layout, and ASTERISK and MICRO SIGN in a French
               Windows layout. */
    NonUsHash =
        50, /**< ISO USB keyboards actually use this code instead of 49 for the
               same key, but all OSes I've seen treat the two codes identically.
             */
    Semicolon = 51,  /**< Semicolon key */
    Apostrophe = 52, /**< Apostrophe key */
    Grave =
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
    Comma = 54,  /**< Comma key */
    Period = 55, /**< Period key */
    Slash = 56,  /**< Slash key */

    CapsLock = 57, /**< Caps Lock key */

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

    PrintScreen = 70, /**< Print Screen key */
    ScrollLock = 71,  /**< Scroll Lock key */
    Pause = 72,       /**< Pause key */
    Insert = 73,      /**< Insert key (help on some Mac keyboards) */
    Home = 74,        /**< Home key */
    PageUp = 75,      /**< Page Up key */
    Delete = 76,      /**< Delete key */
    End = 77,         /**< End key */
    PageDown = 78,    /**< Page Down key */
    Right = 79,       /**< Right arrow key */
    Left = 80,        /**< Left arrow key */
    Down = 81,        /**< Down arrow key */
    Up = 82,          /**< Up arrow key */

    NumLockClear = 83,   /**< Num Lock key (clear on Mac keyboards) */
    KeyPadDivide = 84,   /**< Keypad divide key */
    KeyPadMultiply = 85, /**< Keypad multiply key */
    KeyPadMinus = 86,    /**< Keypad minus key */
    KeyPadPlus = 87,     /**< Keypad plus key */
    KeyPadEnter = 88,    /**< Keypad enter key */
    KeyPad1 = 89,        /**< Keypad 1 key */
    KeyPad2 = 90,        /**< Keypad 2 key */
    KeyPad3 = 91,        /**< Keypad 3 key */
    KeyPad4 = 92,        /**< Keypad 4 key */
    KeyPad5 = 93,        /**< Keypad 5 key */
    KeyPad6 = 94,        /**< Keypad 6 key */
    KeyPad7 = 95,        /**< Keypad 7 key */
    KeyPad8 = 96,        /**< Keypad 8 key */
    KeyPad9 = 97,        /**< Keypad 9 key */
    KeyPad0 = 98,        /**< Keypad 0 key */
    KeyPadPeriod = 99,   /**< Keypad period key */

    NonUsBackslash =
        100, /**< This is the additional key that ISO keyboards have over ANSI
                ones, located between left shift and Z. Produces GRAVE ACCENT
                and TILDE in a US or UK Mac layout, REVERSE SOLIDUS (backslash)
                and VERTICAL LINE in a US or UK Windows layout, and LESS-THAN
                SIGN and GREATER-THAN SIGN in a Swiss German, German, or French
                layout. */
    Application = 101,       /**< Windows contextual menu, compose */
    Power = 102,             /**< Power key */
    KeyPadEquals = 103,      /**< Keypad equals key */
    F13 = 104,               /**< F13 key */
    F14 = 105,               /**< F14 key */
    F15 = 106,               /**< F15 key */
    F16 = 107,               /**< F16 key */
    F17 = 108,               /**< F17 key */
    F18 = 109,               /**< F18 key */
    F19 = 110,               /**< F19 key */
    F20 = 111,               /**< F20 key */
    F21 = 112,               /**< F21 key */
    F22 = 113,               /**< F22 key */
    F23 = 114,               /**< F23 key */
    F24 = 115,               /**< F24 key */
    Execute = 116,           /**< Execute key */
    Help = 117,              /**< Help key (AL Integrated Help Center) */
    Menu = 118,              /**< Menu key */
    Select = 119,            /**< Select key */
    Stop = 120,              /**< Stop key (AC Stop) */
    Again = 121,             /**< Again key (AC Redo/Repeat) */
    Undo = 122,              /**< Undo key (AC Undo) */
    Cut = 123,               /**< Cut key (AC Cut) */
    Copy = 124,              /**< Copy key (AC Copy) */
    Paste = 125,             /**< Paste key (AC Paste) */
    Find = 126,              /**< Find key (AC Find) */
    Mute = 127,              /**< Mute key */
    VolumeUp = 128,          /**< Volume up key */
    VolumeDown = 129,        /**< Volume down key */
    KeyPadComma = 133,       /**< Keypad comma key */
    KeyPadEqualsAs400 = 134, /**< Keypad equals (AS400) key */

    International1 = 135, /**< Used on Asian keyboards */
    International2 = 136, /**< Used on Asian keyboards */
    International3 = 137, /**< Yen key */
    International4 = 138, /**< Used on Asian keyboards */
    International5 = 139, /**< Used on Asian keyboards */
    International6 = 140, /**< Used on Asian keyboards */
    International7 = 141, /**< Used on Asian keyboards */
    International8 = 142, /**< Used on Asian keyboards */
    International9 = 143, /**< Used on Asian keyboards */
    Lang1 = 144,          /**< Hangul/English toggle */
    Lang2 = 145,          /**< Hanja conversion */
    Lang3 = 146,          /**< Katakana */
    Lang4 = 147,          /**< Hiragana */
    Lang5 = 148,          /**< Zenkaku/Hankaku */
    Lang6 = 149,          /**< Reserved */
    Lang7 = 150,          /**< Reserved */
    Lang8 = 151,          /**< Reserved */
    Lang9 = 152,          /**< Reserved */

    Alterase = 153,   /**< Erase-Eaze */
    Sysreq = 154,     /**< Sysreq key */
    Cancel = 155,     /**< Cancel key (AC Cancel) */
    Clear = 156,      /**< Clear key */
    Prior = 157,      /**< Prior key */
    Return2 = 158,    /**< Return2 key */
    Separator = 159,  /**< Separator key */
    Out = 160,        /**< Out key */
    Oper = 161,       /**< Oper key */
    ClearAgain = 162, /**< Clear again key */
    Crsel = 163,      /**< Crsel key */
    Exsel = 164,      /**< Exsel key */

    KeyPad00 = 176,                /**< Keypad 00 key */
    KeyPad000 = 177,               /**< Keypad 000 key */
    ThousandsSeparator = 178,      /**< Thousands separator key */
    DecimalSeparator = 179,        /**< Decimal separator key */
    CurrencyUnit = 180,            /**< Currency unit key */
    CurrencySubunit = 181,         /**< Currency subunit key */
    KeyPadLeftParen = 182,         /**< Keypad left parenthesis key */
    KeyPadRightParen = 183,        /**< Keypad right parenthesis key */
    KeyPadLeftBrace = 184,         /**< Keypad left brace key */
    KeyPadRightBrace = 185,        /**< Keypad right brace key */
    KeyPadTab = 186,               /**< Keypad tab key */
    KeyPadBackspace = 187,         /**< Keypad backspace key */
    KeyPadA = 188,                 /**< Keypad A key */
    KeyPadB = 189,                 /**< Keypad B key */
    KeyPadC = 190,                 /**< Keypad C key */
    KeyPadD = 191,                 /**< Keypad D key */
    KeyPadE = 192,                 /**< Keypad E key */
    KeyPadF = 193,                 /**< Keypad F key */
    KeyPadXor = 194,               /**< Keypad XOR key */
    KeyPadPower = 195,             /**< Keypad power key */
    KeyPadPercent = 196,           /**< Keypad percent key */
    KeyPadLess = 197,              /**< Keypad less than key */
    KeyPadGreater = 198,           /**< Keypad greater than key */
    KeyPadAmpersand = 199,         /**< Keypad ampersand key */
    KeyPadDoubleAmpersand = 200,   /**< Keypad double ampersand key */
    KeyPadVerticalbar = 201,       /**< Keypad vertical bar key */
    KeyPadDoubleVerticalBar = 202, /**< Keypad double vertical bar key */
    KeyPadColon = 203,             /**< Keypad colon key */
    KeyPadHash = 204,              /**< Keypad hash key */
    KeyPadSpace = 205,             /**< Keypad space key */
    KeyPadAt = 206,                /**< Keypad at key */
    KeyPadExclam = 207,            /**< Keypad exclamation mark key */
    KeyPadMemoryStore = 208,       /**< Keypad memory store key */
    KeyPadMemoryRecall = 209,      /**< Keypad memory recall key */
    KeyPadMemoryClear = 210,       /**< Keypad memory clear key */
    KeyPadMemoryAdd = 211,         /**< Keypad memory add key */
    KeyPadMemorySubtract = 212,    /**< Keypad memory subtract key */
    KeyPadMemoryMultiply = 213,    /**< Keypad memory multiply key */
    KeyPadMemoryDivide = 214,      /**< Keypad memory divide key */
    KeyPadPlusMinus = 215,         /**< Keypad plus/minus key */
    KeyPadClear = 216,             /**< Keypad clear key */
    KeyPadClearEntry = 217,        /**< Keypad clear entry key */
    KeyPadBinary = 218,            /**< Keypad binary key */
    KeyPadOctal = 219,             /**< Keypad octal key */
    KeyPadDecimal = 220,           /**< Keypad decimal key */
    KeyPadHexadecimal = 221,       /**< Keypad hexadecimal key */

    LeftControl = 224,  /**< Left control key */
    LeftShift = 225,    /**< Left shift key */
    LeftAlt = 226,      /**< Left alt key (option) */
    LeftGui = 227,      /**< Left GUI key (windows, command, meta) */
    RightControl = 228, /**< Right control key */
    RightShift = 229,   /**< Right shift key */
    RightAlt = 230,     /**< Right alt key (alt gr, option) */
    RightGui = 231,     /**< Right GUI key (windows, command, meta) */

    Mode = 257, /**< Mode key */

    /* Usage page 0x0C */
    Sleep = 258, /**< Sleep key */
    Wake = 259,  /**< Wake key */

    ChannelIncrement = 260, /**< Channel increment key */
    ChannelDecrement = 261, /**< Channel decrement key */

    MediaPlay = 262,          /**< Media play key */
    MediaPause = 263,         /**< Media pause key */
    MediaRecord = 264,        /**< Media record key */
    MediaFastForward = 265,   /**< Media fast forward key */
    MediaRewind = 266,        /**< Media rewind key */
    MediaNextTrack = 267,     /**< Media next track key */
    MediaPreviousTrack = 268, /**< Media previous track key */
    MediaStop = 269,          /**< Media stop key */
    MediaEject = 270,         /**< Media eject key */
    MediaPlayPause = 271,     /**< Media play/pause key */
    MediaSelect = 272,        /**< Media select key */

    AcNew = 273,        /**< AC new key */
    AcOpen = 274,       /**< AC open key */
    AcClose = 275,      /**< AC close key */
    AcExit = 276,       /**< AC exit key */
    AcSave = 277,       /**< AC save key */
    AcPrint = 278,      /**< AC print key */
    AcProperties = 279, /**< AC properties key */

    AcSearch = 280,    /**< AC search key */
    AcHome = 281,      /**< AC home key */
    AcBack = 282,      /**< AC back key */
    AcForward = 283,   /**< AC forward key */
    AcStop = 284,      /**< AC stop key */
    AcRefresh = 285,   /**< AC refresh key */
    AcBookmarks = 286, /**< AC bookmarks key */

    /* Mobile keys */
    SoftLeft = 287,  /**< Soft left key */
    SoftRight = 288, /**< Soft right key */
    Call = 289,      /**< Call key */
    EndCall = 290,   /**< End call key */

    Reserved = 400, /**< 400-500 reserved for dynamic keycodes */

    Count = 512 /**< Not a key, just marks the number of scancodes
                                for array bounds */

  };

  /**
   * @brief Virtual key codes derived from keyboard scancodes.
   *
   * Virtual key codes represent actual keys pressed on the keyboard,
   * including printable characters and special function keys.
   */
  enum class KeyCode : std::int32_t {
    Unknown = 0x00000000u,               /**< Unknown key */
    Return = 0x0000000du,                /**< Return key ('\\r') */
    Escape = 0x0000001bu,                /**< Escape key ('\\x1B') */
    Backspace = 0x00000008u,             /**< Backspace key ('\\b') */
    Tab = 0x00000009u,                   /**< Tab key ('\\t') */
    Space = 0x00000020u,                 /**< Space key (' ') */
    Exclaim = 0x00000021u,               /**< Exclamation mark key ('!') */
    DoubleApostrophe = 0x00000022u,      /**< Double apostrophe key ('"') */
    Hash = 0x00000023u,                  /**< Hash key ('#') */
    Dollar = 0x00000024u,                /**< Dollar key ('$') */
    Percent = 0x00000025u,               /**< Percent key ('%') */
    Ampersand = 0x00000026u,             /**< Ampersand key ('&') */
    Apostrophe = 0x00000027u,            /**< Apostrophe key ('\\'') */
    LeftParen = 0x00000028u,             /**< Left parenthesis key ('(') */
    RightParen = 0x00000029u,            /**< Right parenthesis key (')') */
    Asterisk = 0x0000002au,              /**< Asterisk key ('*') */
    Plus = 0x0000002bu,                  /**< Plus key ('+') */
    Comma = 0x0000002cu,                 /**< Comma key (',') */
    Minus = 0x0000002du,                 /**< Minus key ('-') */
    Period = 0x0000002eu,                /**< Period key ('.') */
    Slash = 0x0000002fu,                 /**< Slash key ('/') */
    Num0 = 0x00000030u,                  /**< 0 key ('0') */
    Num1 = 0x00000031u,                  /**< 1 key ('1') */
    Num2 = 0x00000032u,                  /**< 2 key ('2') */
    Num3 = 0x00000033u,                  /**< 3 key ('3') */
    Num4 = 0x00000034u,                  /**< 4 key ('4') */
    Num5 = 0x00000035u,                  /**< 5 key ('5') */
    Num6 = 0x00000036u,                  /**< 6 key ('6') */
    Num7 = 0x00000037u,                  /**< 7 key ('7') */
    Num8 = 0x00000038u,                  /**< 8 key ('8') */
    Num9 = 0x00000039u,                  /**< 9 key ('9') */
    Colon = 0x0000003au,                 /**< Colon key (':') */
    Semicolon = 0x0000003bu,             /**< Semicolon key (';') */
    Less = 0x0000003cu,                  /**< Less than key ('<') */
    Equals = 0x0000003du,                /**< Equals key ('=') */
    Greater = 0x0000003eu,               /**< Greater than key ('>') */
    Question = 0x0000003fu,              /**< Question mark key ('?') */
    At = 0x00000040u,                    /**< At key ('@') */
    LeftBracket = 0x0000005bu,           /**< Left bracket key ('[') */
    Backslash = 0x0000005cu,             /**< Backslash key ('\\') */
    RightBracket = 0x0000005du,          /**< Right bracket key (']') */
    Caret = 0x0000005eu,                 /**< Caret key ('^') */
    Underscore = 0x0000005fu,            /**< Underscore key ('_') */
    Grave = 0x00000060u,                 /**< Grave key ('\`') */
    A = 0x00000061u,                     /**< A key ('a') */
    B = 0x00000062u,                     /**< B key ('b') */
    C = 0x00000063u,                     /**< C key ('c') */
    D = 0x00000064u,                     /**< D key ('d') */
    E = 0x00000065u,                     /**< E key ('e') */
    F = 0x00000066u,                     /**< F key ('f') */
    G = 0x00000067u,                     /**< G key ('g') */
    H = 0x00000068u,                     /**< H key ('h') */
    I = 0x00000069u,                     /**< I key ('i') */
    J = 0x0000006au,                     /**< J key ('j') */
    K = 0x0000006bu,                     /**< K key ('k') */
    L = 0x0000006cu,                     /**< L key ('l') */
    M = 0x0000006du,                     /**< M key ('m') */
    N = 0x0000006eu,                     /**< N key ('n') */
    O = 0x0000006fu,                     /**< O key ('o') */
    P = 0x00000070u,                     /**< P key ('p') */
    Q = 0x00000071u,                     /**< Q key ('q') */
    R = 0x00000072u,                     /**< R key ('r') */
    S = 0x00000073u,                     /**< S key ('s') */
    T = 0x00000074u,                     /**< T key ('t') */
    U = 0x00000075u,                     /**< U key ('u') */
    V = 0x00000076u,                     /**< V key ('v') */
    W = 0x00000077u,                     /**< W key ('w') */
    X = 0x00000078u,                     /**< X key ('x') */
    Y = 0x00000079u,                     /**< Y key ('y') */
    Z = 0x0000007au,                     /**< Z key ('z') */
    LeftBrace = 0x0000007bu,             /**< Left brace key ('{') */
    Pipe = 0x0000007cu,                  /**< Pipe key ('|') */
    RightBrace = 0x0000007du,            /**< Right brace key ('}') */
    Tilde = 0x0000007eu,                 /**< Tilde key ('~') */
    Delete = 0x0000007fu,                /**< Delete key ('\\x7F') */
    PlusMinus = 0x000000b1u,             /**< Plus/minus key ('\\xB1') */
    CapsLock = 0x40000039u,              /**< Caps Lock key */
    F1 = 0x4000003au,                    /**< F1 key */
    F2 = 0x4000003bu,                    /**< F2 key */
    F3 = 0x4000003cu,                    /**< F3 key */
    F4 = 0x4000003du,                    /**< F4 key */
    F5 = 0x4000003eu,                    /**< F5 key */
    F6 = 0x4000003fu,                    /**< F6 key */
    F7 = 0x40000040u,                    /**< F7 key */
    F8 = 0x40000041u,                    /**< F8 key */
    F9 = 0x40000042u,                    /**< F9 key */
    F10 = 0x40000043u,                   /**< F10 key */
    F11 = 0x40000044u,                   /**< F11 key */
    F12 = 0x40000045u,                   /**< F12 key */
    PrintScreen = 0x40000046u,           /**< Print Screen key */
    ScrollLock = 0x40000047u,            /**< Scroll Lock key */
    Pause = 0x40000048u,                 /**< Pause key */
    Insert = 0x40000049u,                /**< Insert key */
    Home = 0x4000004au,                  /**< Home key */
    PageUp = 0x4000004bu,                /**< Page Up key */
    End = 0x4000004du,                   /**< End key */
    PageDown = 0x4000004eu,              /**< Page Down key */
    Right = 0x4000004fu,                 /**< Right arrow key */
    Left = 0x40000050u,                  /**< Left arrow key */
    Down = 0x40000051u,                  /**< Down arrow key */
    Up = 0x40000052u,                    /**< Up arrow key */
    NumLockClear = 0x40000053u,          /**< Num Lock key */
    KeyPadDivide = 0x40000054u,          /**< Keypad divide key */
    KeyPadMultiply = 0x40000055u,        /**< Keypad multiply key */
    KeyPadMinus = 0x40000056u,           /**< Keypad minus key */
    KeyPadPlus = 0x40000057u,            /**< Keypad plus key */
    KeyPadEnter = 0x40000058u,           /**< Keypad enter key */
    KeyPad1 = 0x40000059u,               /**< Keypad 1 key */
    KeyPad2 = 0x4000005au,               /**< Keypad 2 key */
    KeyPad3 = 0x4000005bu,               /**< Keypad 3 key */
    KeyPad4 = 0x4000005cu,               /**< Keypad 4 key */
    KeyPad5 = 0x4000005du,               /**< Keypad 5 key */
    KeyPad6 = 0x4000005eu,               /**< Keypad 6 key */
    KeyPad7 = 0x4000005fu,               /**< Keypad 7 key */
    KeyPad8 = 0x40000060u,               /**< Keypad 8 key */
    KeyPad9 = 0x40000061u,               /**< Keypad 9 key */
    KeyPad0 = 0x40000062u,               /**< Keypad 0 key */
    KeyPadPeriod = 0x40000063u,          /**< Keypad period key */
    Application = 0x40000065u,           /**< Application key */
    Power = 0x40000066u,                 /**< Power key */
    KeyPadEquals = 0x40000067u,          /**< Keypad equals key */
    F13 = 0x40000068u,                   /**< F13 key */
    F14 = 0x40000069u,                   /**< F14 key */
    F15 = 0x4000006au,                   /**< F15 key */
    F16 = 0x4000006bu,                   /**< F16 key */
    F17 = 0x4000006cu,                   /**< F17 key */
    F18 = 0x4000006du,                   /**< F18 key */
    F19 = 0x4000006eu,                   /**< F19 key */
    F20 = 0x4000006fu,                   /**< F20 key */
    F21 = 0x40000070u,                   /**< F21 key */
    F22 = 0x40000071u,                   /**< F22 key */
    F23 = 0x40000072u,                   /**< F23 key */
    F24 = 0x40000073u,                   /**< F24 key */
    Execute = 0x40000074u,               /**< Execute key */
    Help = 0x40000075u,                  /**< Help key */
    Menu = 0x40000076u,                  /**< Menu key */
    Select = 0x40000077u,                /**< Select key */
    Stop = 0x40000078u,                  /**< Stop key */
    Again = 0x40000079u,                 /**< Again key */
    Undo = 0x4000007au,                  /**< Undo key */
    Cut = 0x4000007bu,                   /**< Cut key */
    Copy = 0x4000007cu,                  /**< Copy key */
    Paste = 0x4000007du,                 /**< Paste key */
    Find = 0x4000007eu,                  /**< Find key */
    Mute = 0x4000007fu,                  /**< Mute key */
    VolumeUp = 0x40000080u,              /**< Volume up key */
    VolumeDown = 0x40000081u,            /**< Volume down key */
    KeyPadComma = 0x40000085u,           /**< Keypad comma key */
    KeyPadEqualsAs400 = 0x40000086u,     /**< Keypad equals (AS400) key */
    Alterase = 0x40000099u,              /**< Alterase key */
    Sysreq = 0x4000009au,                /**< Sysreq key */
    Cancel = 0x4000009bu,                /**< Cancel key */
    Clear = 0x4000009cu,                 /**< Clear key */
    Prior = 0x4000009du,                 /**< Prior key */
    Return2 = 0x4000009eu,               /**< Return2 key */
    Separator = 0x4000009fu,             /**< Separator key */
    Out = 0x400000a0u,                   /**< Out key */
    Oper = 0x400000a1u,                  /**< Oper key */
    ClearAgain = 0x400000a2u,            /**< Clear again key */
    Crsel = 0x400000a3u,                 /**< Crsel key */
    Exsel = 0x400000a4u,                 /**< Exsel key */
    KeyPad00 = 0x400000b0u,              /**< Keypad 00 key */
    KeyPad000 = 0x400000b1u,             /**< Keypad 000 key */
    ThousandsSeparator = 0x400000b2u,    /**< Thousands separator key */
    DecimalSeparator = 0x400000b3u,      /**< Decimal separator key */
    CurrencyUnit = 0x400000b4u,          /**< Currency unit key */
    CurrencySubunit = 0x400000b5u,       /**< Currency subunit key */
    KeyPadLeftParen = 0x400000b6u,       /**< Keypad left parenthesis key */
    KeyPadRightParen = 0x400000b7u,      /**< Keypad right parenthesis key */
    KeyPadLeftBrace = 0x400000b8u,       /**< Keypad left brace key */
    KeyPadRightBrace = 0x400000b9u,      /**< Keypad right brace key */
    KeyPadTab = 0x400000bau,             /**< Keypad tab key */
    KeyPadBackspace = 0x400000bbu,       /**< Keypad backspace key */
    KeyPadA = 0x400000bcu,               /**< Keypad A key */
    KeyPadB = 0x400000bdu,               /**< Keypad B key */
    KeyPadC = 0x400000beu,               /**< Keypad C key */
    KeyPadD = 0x400000bfu,               /**< Keypad D key */
    KeyPadE = 0x400000c0u,               /**< Keypad E key */
    KeyPadF = 0x400000c1u,               /**< Keypad F key */
    KeyPadXor = 0x400000c2u,             /**< Keypad XOR key */
    KeyPadPower = 0x400000c3u,           /**< Keypad power key */
    KeyPadPercent = 0x400000c4u,         /**< Keypad percent key */
    KeyPadLess = 0x400000c5u,            /**< Keypad less than key */
    KeyPadGreater = 0x400000c6u,         /**< Keypad greater than key */
    KeyPadAmpersand = 0x400000c7u,       /**< Keypad ampersand key */
    KeyPadDoubleAmpersand = 0x400000c8u, /**< Keypad double ampersand key */
    KeyPadVerticalbar = 0x400000c9u,     /**< Keypad vertical bar key */
    KeyPadDoubleVerticalBar =
        0x400000cau,                    /**< Keypad double vertical bar key */
    KeyPadColon = 0x400000cbu,          /**< Keypad colon key */
    KeyPadHash = 0x400000ccu,           /**< Keypad hash key */
    KeyPadSpace = 0x400000cdu,          /**< Keypad space key */
    KeyPadAt = 0x400000ceu,             /**< Keypad at key */
    KeyPadExclam = 0x400000cfu,         /**< Keypad exclamation mark key */
    KeyPadMemoryStore = 0x400000d0u,    /**< Keypad memory store key */
    KeyPadMemoryRecall = 0x400000d1u,   /**< Keypad memory recall key */
    KeyPadMemoryClear = 0x400000d2u,    /**< Keypad memory clear key */
    KeyPadMemoryAdd = 0x400000d3u,      /**< Keypad memory add key */
    KeyPadMemorySubtract = 0x400000d4u, /**< Keypad memory subtract key */
    KeyPadMemoryMultiply = 0x400000d5u, /**< Keypad memory multiply key */
    KeyPadMemoryDivide = 0x400000d6u,   /**< Keypad memory divide key */
    KeyPadPlusMinus = 0x400000d7u,      /**< Keypad plus/minus key */
    KeyPadClear = 0x400000d8u,          /**< Keypad clear key */
    KeyPadClearEntry = 0x400000d9u,     /**< Keypad clear entry key */
    KeyPadBinary = 0x400000dau,         /**< Keypad binary key */
    KeyPadOctal = 0x400000dbu,          /**< Keypad octal key */
    KeyPadDecimal = 0x400000dcu,        /**< Keypad decimal key */
    KeyPadHexadecimal = 0x400000ddu,    /**< Keypad hexadecimal key */
    LeftControl = 0x400000e0u,          /**< Left control key */
    LeftShift = 0x400000e1u,            /**< Left shift key */
    LeftAlt = 0x400000e2u,              /**< Left alt key */
    LeftGui = 0x400000e3u,              /**< Left GUI key */
    RightControl = 0x400000e4u,         /**< Right control key */
    RightShift = 0x400000e5u,           /**< Right shift key */
    RightAlt = 0x400000e6u,             /**< Right alt key */
    RightGui = 0x400000e7u,             /**< Right GUI key */
    Mode = 0x40000101u,                 /**< Mode key */
    Sleep = 0x40000102u,                /**< Sleep key */
    Wake = 0x40000103u,                 /**< Wake key */
    ChannelIncrement = 0x40000104u,     /**< Channel increment key */
    ChannelDecrement = 0x40000105u,     /**< Channel decrement key */
    MediaPlay = 0x40000106u,            /**< Media play key */
    MediaPause = 0x40000107u,           /**< Media pause key */
    MediaRecord = 0x40000108u,          /**< Media record key */
    MediaFastForward = 0x40000109u,     /**< Media fast forward key */
    MediaRewind = 0x4000010au,          /**< Media rewind key */
    MediaNextTrack = 0x4000010bu,       /**< Media next track key */
    MediaPreviousTrack = 0x4000010cu,   /**< Media previous track key */
    MediaStop = 0x4000010du,            /**< Media stop key */
    MediaEject = 0x4000010eu,           /**< Media eject key */
    MediaPlayPause = 0x4000010fu,       /**< Media play/pause key */
    MediaSelect = 0x40000110u,          /**< Media select key */
    AcNew = 0x40000111u,                /**< AC new key */
    AcOpen = 0x40000112u,               /**< AC open key */
    AcClose = 0x40000113u,              /**< AC close key */
    AcExit = 0x40000114u,               /**< AC exit key */
    AcSave = 0x40000115u,               /**< AC save key */
    AcPrint = 0x40000116u,              /**< AC print key */
    AcProperties = 0x40000117u,         /**< AC properties key */
    AcSearch = 0x40000118u,             /**< AC search key */
    AcHome = 0x40000119u,               /**< AC home key */
    AcBack = 0x4000011au,               /**< AC back key */
    AcForward = 0x4000011bu,            /**< AC forward key */
    AcStop = 0x4000011cu,               /**< AC stop key */
    AcRefresh = 0x4000011du,            /**< AC refresh key */
    AcBookmarks = 0x4000011eu,          /**< AC bookmarks key */
    SoftLeft = 0x4000011fu,             /**< Soft left key */
    SoftRight = 0x40000120u,            /**< Soft right key */
    Call = 0x40000121u,                 /**< Call key */
    EndCall = 0x40000122u,              /**< End call key */
    LeftTab = 0x20000001u,              /**< Extended key Left Tab */
    Level5Shift = 0x20000002u,          /**< Extended key Level 5 Shift */
    MultiKeyCompose = 0x20000003u,      /**< Extended key Multi-key Compose */
    LeftMeta = 0x20000004u,             /**< Extended key Left Meta */
    RightMeta = 0x20000005u,            /**< Extended key Right Meta */
    LeftHyper = 0x20000006u,            /**< Extended key Left Hyper */
    RightHyper = 0x20000007u,           /**< Extended key Right Hyper */
  };

  /**
   * @brief Key modifier flags.
   *
   * Key modifiers represent the state of modifier keys (like Shift, Ctrl, Alt)
   * during keyboard events.
   */
  enum class KeyModifiers : std::uint16_t {
    Unknown = 0x0000u,     /**< Unknown modifier state. */
    LeftShift = 0x0001u,   /**< The left Shift key is down. */
    RightShift = 0x0002u,  /**< The right Shift key is down. */
    Level5Shift = 0x0004u, /**< The Level 5 Shift key is down. */
    LeftCtrl = 0x0040u,    /**< The left Ctrl (Control) key is down. */
    RightCtrl = 0x0080u,   /**< The right Ctrl (Control) key is down. */
    LeftAlt = 0x0100u,     /**< The left Alt key is down. */
    RightAlt = 0x0200u,    /**< The right Alt key is down. */
    LeftGUI = 0x0400u, /**< The left GUI key (often the Windows key) is down. */
    RightGUI =
        0x0800u, /**< The right GUI key (often the Windows key) is down. */
    NumLock = 0x1000u,    /**< The Num Lock key (may be located on an
                                  extended keypad) is down. */
    CapsLock = 0x2000u,   /**< The Caps Lock key is down. */
    AltGr = 0x4000u,      /**< The AltGr key is down. */
    ScrollLock = 0x8000u, /**< The Scroll Lock key is down. */

    Ctrl = LeftCtrl | RightCtrl,    /**< Any Ctrl key is down. */
    Shift = LeftShift | RightShift, /**< Any Shift key is down. */
    Alt = LeftAlt | RightAlt,       /**< Any Alt key is down. */
    Gui = LeftGUI | RightGUI        /**< Any GUI key is down. */
  };

  /**
   * @brief Factory for creating KeyboardEvent instances.
   */
  class Factory : public Event::AbstractFactory {
  public:
    ~Factory(void) override;

    /**
     * @brief Create a KeyboardEvent as a base Event pointer.
     * @return Newly created KeyboardEvent as std::unique_ptr<Event>.
     */
    std::unique_ptr<Event> create(void) const override;

    /**
     * @brief Create a strongly-typed KeyboardEvent.
     * @return Newly created KeyboardEvent as std::unique_ptr<KeyboardEvent>.
     */
    std::unique_ptr<KeyboardEvent> createTyped(void) const;
  };

private:
  ScanCode _scancode{ScanCode::Unknown};
  KeyCode _keycode{KeyCode::Unknown};
  std::bitset<sizeof(KeyModifiers) * 8> _modifiers{
      static_cast<std::size_t>(KeyModifiers::Unknown)};
  bool isDownEvent{true};
  bool isRepeatEvent{false};

public:
  /**
   * @brief Default constructor.
   */
  explicit KeyboardEvent(void);

  /**
   * @brief Default destructor.
   */
  ~KeyboardEvent(void) override;

  /**
   * @brief Get the keyboard scancode.
   *
   * @return The keyboard scancode.
   */
  ScanCode getScancode(void) const noexcept;

  /**
   * @brief Set the keyboard scancode.
   * @param scancode The keyboard scancode to set.
   * @return Reference to this KeyboardEvent for method chaining.
   */
  KeyboardEvent &setScancode(const ScanCode scancode) noexcept;

  /**
   * @brief Set the virtual key code.
   * @param keycode The virtual key code to set.
   * @return Reference to this KeyboardEvent for method chaining.
   */
  KeyboardEvent &setKeycode(const KeyCode keycode) noexcept;

  /**
   * @brief Get the virtual key code.
   * @return The virtual key code.
   */
  KeyCode getKeycode(void) const noexcept;

  /**
   * @brief Set the key modifiers.
   * @param modifiers The key modifiers to set.
   * @return Reference to this KeyboardEvent for method chaining.
   */
  KeyboardEvent &setModifiers(const KeyModifiers modifiers) noexcept;

  /**
   * @brief Check if a specific key modifier is set.
   * @param modifier The key modifier to check.
   * @return True if the specified modifier is set, false otherwise.
   */
  bool isModifierSet(const KeyModifiers modifier) const noexcept;

  /**
   * @brief Set whether the event is a key down event.
   * @param isDown True if the event is a key down event, false otherwise.
   * @return Reference to this KeyboardEvent for method chaining.
   */
  KeyboardEvent &setIsDownEvent(const bool isDown) noexcept;

  /**
   * @brief Check if the event is a key down event.
   * @return True if the event is a key down event, false otherwise.
   */
  bool getIsDownEvent(void) const noexcept;

  /**
   * @brief Set whether the event is a key repeat event.
   * @param isRepeat True if the event is a key repeat event, false otherwise.
   * @return Reference to this KeyboardEvent for method chaining.
   */
  KeyboardEvent &setIsRepeatEvent(const bool isRepeat) noexcept;

  /**
   * @brief Check if the event is a key repeat event.
   * @return True if the event is a key repeat event, false otherwise.
   */
  bool getIsRepeatEvent(void) const noexcept;
};

} // namespace utility::event
