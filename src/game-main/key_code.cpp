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
#include "key_code.h"
#include <cassert>
#include <unordered_map>

static std::unordered_map<std::string, Sys::KeyCode> g_KeyCodeMap;
static bool g_Initialized;

const char * Sys::keyCodeName(Sys::KeyCode code)
{
	switch (code)
	{
	case Sys::Key_Unknown: return "???";
	case Sys::Key_A: return "A";
	case Sys::Key_B: return "B";
	case Sys::Key_C: return "C";
	case Sys::Key_D: return "D";
	case Sys::Key_E: return "E";
	case Sys::Key_F: return "F";
	case Sys::Key_G: return "G";
	case Sys::Key_H: return "H";
	case Sys::Key_I: return "I";
	case Sys::Key_J: return "J";
	case Sys::Key_K: return "K";
	case Sys::Key_L: return "L";
	case Sys::Key_M: return "M";
	case Sys::Key_N: return "N";
	case Sys::Key_O: return "O";
	case Sys::Key_P: return "P";
	case Sys::Key_Q: return "Q";
	case Sys::Key_R: return "R";
	case Sys::Key_S: return "S";
	case Sys::Key_T: return "T";
	case Sys::Key_U: return "U";
	case Sys::Key_V: return "V";
	case Sys::Key_W: return "W";
	case Sys::Key_X: return "X";
	case Sys::Key_Y: return "Y";
	case Sys::Key_Z: return "Z";
	case Sys::Key_0: return "0";
	case Sys::Key_1: return "1";
	case Sys::Key_2: return "2";
	case Sys::Key_3: return "3";
	case Sys::Key_4: return "4";
	case Sys::Key_5: return "5";
	case Sys::Key_6: return "6";
	case Sys::Key_7: return "7";
	case Sys::Key_8: return "8";
	case Sys::Key_9: return "9";
	case Sys::Key_Apostrophe: return "'";
	case Sys::Key_GraveAccent: return "`";
	case Sys::Key_Comma: return ",";
	case Sys::Key_Period: return ".";
	case Sys::Key_Semicolon: return ";";
	case Sys::Key_Equal: return "=";
	case Sys::Key_Minus: return "-";
	case Sys::Key_Slash: return "/";
	case Sys::Key_Backslash: return "\\";
	case Sys::Key_LeftBracket: return "[";
	case Sys::Key_RightBracket: return "]";
	case Sys::Key_Enter: return "Enter";
	case Sys::Key_Backspace: return "Backspace";
	case Sys::Key_Tab: return "Tab";
	case Sys::Key_Space: return "Space";
	case Sys::Key_Escape: return "Escape";
	case Sys::Key_Insert: return "Insert";
	case Sys::Key_Delete: return "Delete";
	case Sys::Key_Home: return "Home";
	case Sys::Key_End: return "End";
	case Sys::Key_PageUp: return "Page Up";
	case Sys::Key_PageDown: return "Page Down";
	case Sys::Key_Left: return "Left";
	case Sys::Key_Up: return "Up";
	case Sys::Key_Right: return "Right";
	case Sys::Key_Down: return "Down";
	case Sys::Key_LeftAlt: return "Left Alt";
	case Sys::Key_LeftControl: return "Left Ctrl";
	case Sys::Key_LeftShift: return "Left Shift";
	case Sys::Key_RightAlt: return "Right Alt";
	case Sys::Key_RightControl: return "Right Ctrl";
	case Sys::Key_RightShift: return "Right Shift";
	case Sys::Key_NumLock: return "Num Lock";
	case Sys::Key_CapsLock: return "Caps Lock";
	case Sys::Key_F1: return "F1";
	case Sys::Key_F2: return "F2";
	case Sys::Key_F3: return "F3";
	case Sys::Key_F4: return "F4";
	case Sys::Key_F5: return "F5";
	case Sys::Key_F6: return "F6";
	case Sys::Key_F7: return "F7";
	case Sys::Key_F8: return "F8";
	case Sys::Key_F9: return "F9";
	case Sys::Key_F10: return "F10";
	case Sys::Key_F11: return "F11";
	case Sys::Key_F12: return "F12";
	case Sys::Key_F13: return "F13";
	case Sys::Key_F14: return "F14";
	case Sys::Key_F15: return "F15";
	case Sys::Key_F16: return "F16";
	case Sys::Key_F17: return "F17";
	case Sys::Key_F18: return "F18";
	case Sys::Key_F19: return "F19";
	case Sys::Key_F20: return "F20";
	case Sys::Key_Numeric_0: return "Keypad 0";
	case Sys::Key_Numeric_1: return "Keypad 1";
	case Sys::Key_Numeric_2: return "Keypad 2";
	case Sys::Key_Numeric_3: return "Keypad 3";
	case Sys::Key_Numeric_4: return "Keypad 4";
	case Sys::Key_Numeric_5: return "Keypad 5";
	case Sys::Key_Numeric_6: return "Keypad 6";
	case Sys::Key_Numeric_7: return "Keypad 7";
	case Sys::Key_Numeric_8: return "Keypad 8";
	case Sys::Key_Numeric_9: return "Keypad 9";
	case Sys::Key_Numeric_Plus: return "Keypad +";
	case Sys::Key_Numeric_Minus: return "Keypad -";
	case Sys::Key_Numeric_Multiply: return "Keypad *";
	case Sys::Key_Numeric_Divide: return "Keypad /";
	case Sys::Key_Numeric_Equal: return "Keypad =";
	case Sys::Key_Numeric_Decimal: return "Keypad .";
	case Sys::Key_Numeric_Enter: return "Keypad Enter";
	}

	assert(false);
	return "???";
}

Sys::KeyCode Sys::keyCodeFromName(const std::string & name)
{
	if (!g_Initialized)
	{
		g_KeyCodeMap.insert(std::make_pair("A", Sys::Key_A));
		g_KeyCodeMap.insert(std::make_pair("B", Sys::Key_B));
		g_KeyCodeMap.insert(std::make_pair("C", Sys::Key_C));
		g_KeyCodeMap.insert(std::make_pair("D", Sys::Key_D));
		g_KeyCodeMap.insert(std::make_pair("E", Sys::Key_E));
		g_KeyCodeMap.insert(std::make_pair("F", Sys::Key_F));
		g_KeyCodeMap.insert(std::make_pair("G", Sys::Key_G));
		g_KeyCodeMap.insert(std::make_pair("H", Sys::Key_H));
		g_KeyCodeMap.insert(std::make_pair("I", Sys::Key_I));
		g_KeyCodeMap.insert(std::make_pair("J", Sys::Key_J));
		g_KeyCodeMap.insert(std::make_pair("K", Sys::Key_K));
		g_KeyCodeMap.insert(std::make_pair("L", Sys::Key_L));
		g_KeyCodeMap.insert(std::make_pair("M", Sys::Key_M));
		g_KeyCodeMap.insert(std::make_pair("N", Sys::Key_N));
		g_KeyCodeMap.insert(std::make_pair("O", Sys::Key_O));
		g_KeyCodeMap.insert(std::make_pair("P", Sys::Key_P));
		g_KeyCodeMap.insert(std::make_pair("Q", Sys::Key_Q));
		g_KeyCodeMap.insert(std::make_pair("R", Sys::Key_R));
		g_KeyCodeMap.insert(std::make_pair("S", Sys::Key_S));
		g_KeyCodeMap.insert(std::make_pair("T", Sys::Key_T));
		g_KeyCodeMap.insert(std::make_pair("U", Sys::Key_U));
		g_KeyCodeMap.insert(std::make_pair("V", Sys::Key_V));
		g_KeyCodeMap.insert(std::make_pair("W", Sys::Key_W));
		g_KeyCodeMap.insert(std::make_pair("X", Sys::Key_X));
		g_KeyCodeMap.insert(std::make_pair("Y", Sys::Key_Y));
		g_KeyCodeMap.insert(std::make_pair("Z", Sys::Key_Z));
		g_KeyCodeMap.insert(std::make_pair("0", Sys::Key_0));
		g_KeyCodeMap.insert(std::make_pair("1", Sys::Key_1));
		g_KeyCodeMap.insert(std::make_pair("2", Sys::Key_2));
		g_KeyCodeMap.insert(std::make_pair("3", Sys::Key_3));
		g_KeyCodeMap.insert(std::make_pair("4", Sys::Key_4));
		g_KeyCodeMap.insert(std::make_pair("5", Sys::Key_5));
		g_KeyCodeMap.insert(std::make_pair("6", Sys::Key_6));
		g_KeyCodeMap.insert(std::make_pair("7", Sys::Key_7));
		g_KeyCodeMap.insert(std::make_pair("8", Sys::Key_8));
		g_KeyCodeMap.insert(std::make_pair("9", Sys::Key_9));
		g_KeyCodeMap.insert(std::make_pair("0", Sys::Key_0));
		g_KeyCodeMap.insert(std::make_pair("'", Sys::Key_Apostrophe));
		g_KeyCodeMap.insert(std::make_pair("`", Sys::Key_GraveAccent));
		g_KeyCodeMap.insert(std::make_pair(",", Sys::Key_Comma));
		g_KeyCodeMap.insert(std::make_pair(".", Sys::Key_Period));
		g_KeyCodeMap.insert(std::make_pair(";", Sys::Key_Semicolon));
		g_KeyCodeMap.insert(std::make_pair("=", Sys::Key_Equal));
		g_KeyCodeMap.insert(std::make_pair("-", Sys::Key_Minus));
		g_KeyCodeMap.insert(std::make_pair("/", Sys::Key_Slash));
		g_KeyCodeMap.insert(std::make_pair("\\", Sys::Key_Backslash));
		g_KeyCodeMap.insert(std::make_pair("[", Sys::Key_LeftBracket));
		g_KeyCodeMap.insert(std::make_pair("]", Sys::Key_RightBracket));
		g_KeyCodeMap.insert(std::make_pair("Enter", Sys::Key_Enter));
		g_KeyCodeMap.insert(std::make_pair("Backspace", Sys::Key_Backspace));
		g_KeyCodeMap.insert(std::make_pair("Tab", Sys::Key_Tab));
		g_KeyCodeMap.insert(std::make_pair("Space", Sys::Key_Space));
		g_KeyCodeMap.insert(std::make_pair("Escape", Sys::Key_Escape));
		g_KeyCodeMap.insert(std::make_pair("Insert", Sys::Key_Insert));
		g_KeyCodeMap.insert(std::make_pair("Delete", Sys::Key_Delete));
		g_KeyCodeMap.insert(std::make_pair("Home", Sys::Key_Home));
		g_KeyCodeMap.insert(std::make_pair("End", Sys::Key_End));
		g_KeyCodeMap.insert(std::make_pair("Page Up", Sys::Key_PageUp));
		g_KeyCodeMap.insert(std::make_pair("Page Down", Sys::Key_PageDown));
		g_KeyCodeMap.insert(std::make_pair("Left", Sys::Key_Left));
		g_KeyCodeMap.insert(std::make_pair("Up", Sys::Key_Up));
		g_KeyCodeMap.insert(std::make_pair("Right", Sys::Key_Right));
		g_KeyCodeMap.insert(std::make_pair("Down", Sys::Key_Down));
		g_KeyCodeMap.insert(std::make_pair("Left Alt", Sys::Key_LeftAlt));
		g_KeyCodeMap.insert(std::make_pair("Left Ctrl", Sys::Key_LeftControl));
		g_KeyCodeMap.insert(std::make_pair("Left Shift", Sys::Key_LeftShift));
		g_KeyCodeMap.insert(std::make_pair("Right Alt", Sys::Key_RightAlt));
		g_KeyCodeMap.insert(std::make_pair("Right Ctrl", Sys::Key_RightControl));
		g_KeyCodeMap.insert(std::make_pair("Right Shift", Sys::Key_RightShift));
		g_KeyCodeMap.insert(std::make_pair("Num Lock", Sys::Key_NumLock));
		g_KeyCodeMap.insert(std::make_pair("Caps Lock", Sys::Key_CapsLock));
		g_KeyCodeMap.insert(std::make_pair("F1", Sys::Key_F1));
		g_KeyCodeMap.insert(std::make_pair("F2", Sys::Key_F2));
		g_KeyCodeMap.insert(std::make_pair("F3", Sys::Key_F3));
		g_KeyCodeMap.insert(std::make_pair("F4", Sys::Key_F4));
		g_KeyCodeMap.insert(std::make_pair("F5", Sys::Key_F5));
		g_KeyCodeMap.insert(std::make_pair("F6", Sys::Key_F6));
		g_KeyCodeMap.insert(std::make_pair("F7", Sys::Key_F7));
		g_KeyCodeMap.insert(std::make_pair("F8", Sys::Key_F8));
		g_KeyCodeMap.insert(std::make_pair("F9", Sys::Key_F9));
		g_KeyCodeMap.insert(std::make_pair("F10", Sys::Key_F10));
		g_KeyCodeMap.insert(std::make_pair("F11", Sys::Key_F11));
		g_KeyCodeMap.insert(std::make_pair("F12", Sys::Key_F12));
		g_KeyCodeMap.insert(std::make_pair("F13", Sys::Key_F13));
		g_KeyCodeMap.insert(std::make_pair("F14", Sys::Key_F14));
		g_KeyCodeMap.insert(std::make_pair("F15", Sys::Key_F15));
		g_KeyCodeMap.insert(std::make_pair("F16", Sys::Key_F16));
		g_KeyCodeMap.insert(std::make_pair("F17", Sys::Key_F17));
		g_KeyCodeMap.insert(std::make_pair("F18", Sys::Key_F18));
		g_KeyCodeMap.insert(std::make_pair("F19", Sys::Key_F19));
		g_KeyCodeMap.insert(std::make_pair("F20", Sys::Key_F20));
		g_KeyCodeMap.insert(std::make_pair("Keypad 0", Sys::Key_Numeric_0));
		g_KeyCodeMap.insert(std::make_pair("Keypad 1", Sys::Key_Numeric_1));
		g_KeyCodeMap.insert(std::make_pair("Keypad 2", Sys::Key_Numeric_2));
		g_KeyCodeMap.insert(std::make_pair("Keypad 3", Sys::Key_Numeric_3));
		g_KeyCodeMap.insert(std::make_pair("Keypad 4", Sys::Key_Numeric_4));
		g_KeyCodeMap.insert(std::make_pair("Keypad 5", Sys::Key_Numeric_5));
		g_KeyCodeMap.insert(std::make_pair("Keypad 6", Sys::Key_Numeric_6));
		g_KeyCodeMap.insert(std::make_pair("Keypad 7", Sys::Key_Numeric_7));
		g_KeyCodeMap.insert(std::make_pair("Keypad 8", Sys::Key_Numeric_8));
		g_KeyCodeMap.insert(std::make_pair("Keypad 9", Sys::Key_Numeric_9));
		g_KeyCodeMap.insert(std::make_pair("Keypad +", Sys::Key_Numeric_Plus));
		g_KeyCodeMap.insert(std::make_pair("Keypad -", Sys::Key_Numeric_Minus));
		g_KeyCodeMap.insert(std::make_pair("Keypad *", Sys::Key_Numeric_Multiply));
		g_KeyCodeMap.insert(std::make_pair("Keypad /", Sys::Key_Numeric_Divide));
		g_KeyCodeMap.insert(std::make_pair("Keypad =", Sys::Key_Numeric_Equal));
		g_KeyCodeMap.insert(std::make_pair("Keypad .", Sys::Key_Numeric_Decimal));
		g_KeyCodeMap.insert(std::make_pair("Keypad Enter", Sys::Key_Numeric_Enter));
		g_Initialized = true;
	}

	auto it = g_KeyCodeMap.find(name);
	if (it != g_KeyCodeMap.end())
		return it->second;

	return Sys::Key_Unknown;
}
