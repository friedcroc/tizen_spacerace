/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#ifndef __ed3363551f7fa946122458a192851bc5__
#define __ed3363551f7fa946122458a192851bc5__

#include <string>

namespace Sys
{
	/** Keyboard key code. */
	enum KeyCode
	{
		Key_Unknown = 0,			/**< Unrecognized key. */
		Key_A,						/**< The english letter "A". */
		Key_B,						/**< The english letter "B". */
		Key_C,						/**< The english letter "C". */
		Key_D,						/**< The english letter "D". */
		Key_E,						/**< The english letter "E". */
		Key_F,						/**< The english letter "F". */
		Key_G,						/**< The english letter "G". */
		Key_H,						/**< The english letter "H". */
		Key_I,						/**< The english letter "I". */
		Key_J,						/**< The english letter "J". */
		Key_K,						/**< The english letter "K". */
		Key_L,						/**< The english letter "L". */
		Key_M,						/**< The english letter "M". */
		Key_N,						/**< The english letter "N". */
		Key_O,						/**< The english letter "O". */
		Key_P,						/**< The english letter "P". */
		Key_Q,						/**< The english letter "Q". */
		Key_R,						/**< The english letter "R". */
		Key_S,						/**< The english letter "S". */
		Key_T,						/**< The english letter "T". */
		Key_U,						/**< The english letter "U". */
		Key_V,						/**< The english letter "V". */
		Key_W,						/**< The english letter "W". */
		Key_X,						/**< The english letter "X". */
		Key_Y,						/**< The english letter "Y". */
		Key_Z,						/**< The english letter "Z". */
		Key_0,						/**< The zero digit ("0"). */
		Key_1,						/**< The one digit ("1"). */
		Key_2,						/**< The two digit ("2"). */
		Key_3,						/**< The three digit ("3"). */
		Key_4,						/**< The four digit ("4"). */
		Key_5,						/**< The five digit ("5"). */
		Key_6,						/**< The six digit ("6"). */
		Key_7,						/**< The seven digit ("7"). */
		Key_8,						/**< The eight digit ("8"). */
		Key_9,						/**< The nine digit ("9"). */
		Key_Apostrophe,				/**< The apostrophe sign ("'"). */
		Key_GraveAccent,			/**< The grave accent sign ("`"). */
		Key_Comma,					/**< The comma sign (","). */
		Key_Period,					/**< The period sign ("."). */
		Key_Semicolon,				/**< The semicolon sign (";"). */
		Key_Equal,					/**< The equal sign ("="). */
		Key_Minus,					/**< The minus sign ("-"). */
		Key_Slash,					/**< The slash sign ("/"). */
		Key_Backslash,				/**< The backslash sign ("\"). */
		Key_LeftBracket,			/**< The left bracket ("["). */
		Key_RightBracket,			/**< The right bracket ("]"). */
		Key_Enter,					/**< The "Enter" key. */
		Key_Backspace,				/**< The "Backspace" key. */
		Key_Tab,					/**< The "Tab" key. */
		Key_Space,					/**< The "Space" key. */
		Key_Escape,					/**< The "Escape" key. */
		Key_Insert,					/**< The "Insert" key. */
		Key_Delete,					/**< The "Delete" key. */
		Key_Home,					/**< The "Home" key. */
		Key_End,					/**< The "End" key. */
		Key_PageUp,					/**< The "Page Up" key. */
		Key_PageDown,				/**< The "Page Down" key. */
		Key_Left,					/**< The left arrow key. */
		Key_Up,						/**< The up arrow key. */
		Key_Right,					/**< The right arrow key. */
		Key_Down,					/**< The down arrow key. */
		Key_LeftAlt,				/**< The left "Alt" key. */
		Key_LeftControl,			/**< The left "Control" key. */
		Key_LeftShift,				/**< The left "Shift" key. */
		Key_RightAlt,				/**< The right "Alt" key. */
		Key_RightControl,			/**< The right "Control" key. */
		Key_RightShift,				/**< The right "Shift" key. */
		Key_NumLock,				/**< The "Num Lock" key. */
		Key_CapsLock,				/**< The "Caps Lock" key. */
		Key_F1,						/**< The "F1" key. */
		Key_F2,						/**< The "F2" key. */
		Key_F3,						/**< The "F3" key. */
		Key_F4,						/**< The "F4" key. */
		Key_F5,						/**< The "F5" key. */
		Key_F6,						/**< The "F6" key. */
		Key_F7,						/**< The "F7" key. */
		Key_F8,						/**< The "F8" key. */
		Key_F9,						/**< The "F9" key. */
		Key_F10,					/**< The "F10" key. */
		Key_F11,					/**< The "F11" key. */
		Key_F12,					/**< The "F12" key. */
		Key_F13,					/**< The "F13" key. */
		Key_F14,					/**< The "F14" key. */
		Key_F15,					/**< The "F15" key. */
		Key_F16,					/**< The "F16" key. */
		Key_F17,					/**< The "F17" key. */
		Key_F18,					/**< The "F18" key. */
		Key_F19,					/**< The "F19" key. */
		Key_F20,					/**< The "F20" key. */
		Key_Numeric_0,				/**< The "0" key on the numeric keypad. */
		Key_Numeric_1,				/**< The "1" key on the numeric keypad. */
		Key_Numeric_2,				/**< The "2" key on the numeric keypad. */
		Key_Numeric_3,				/**< The "3" key on the numeric keypad. */
		Key_Numeric_4,				/**< The "4" key on the numeric keypad. */
		Key_Numeric_5,				/**< The "5" key on the numeric keypad. */
		Key_Numeric_6,				/**< The "6" key on the numeric keypad. */
		Key_Numeric_7,				/**< The "7" key on the numeric keypad. */
		Key_Numeric_8,				/**< The "8" key on the numeric keypad. */
		Key_Numeric_9,				/**< The "9" key on the numeric keypad. */
		Key_Numeric_Plus,			/**< The "+" key on the numeric keypad. */
		Key_Numeric_Minus,			/**< The "-" key on the numeric keypad. */
		Key_Numeric_Multiply,		/**< The "*" key on the numeric keypad. */
		Key_Numeric_Divide,			/**< The "/" key on the numeric keypad. */
		Key_Numeric_Equal,			/**< The "=" key on the numeric keypad. */
		Key_Numeric_Decimal,		/**< The "." key on the numeric keypad. */
		Key_Numeric_Enter,			/**< The "Enter" key on the numeric keypad. */
	};

	/**
	 * Converts keyboard key code into the string representation.
	 * @param code Keyboard key code.
	 * @return String representation of the key code.
	 */
	const char * keyCodeName(KeyCode code);

	/**
	 * Converts string representation into keyboard key.
	 * @param name Name of the keyboard key (the same as returned by the keyCodeName function).
	 * @return Keyboard key code.
	 */
	KeyCode keyCodeFromName(const std::string & name);
}

#endif
