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
#include <unordered_map>
#include <string>

#define FILE(name) \
	extern const unsigned char file_##name[]; \
	extern const size_t file_##name##_size;

FILE(bg_jpg)
FILE(carrot_png)
FILE(level_xml)
FILE(menu_logo_png)
FILE(menu_play_png)
FILE(menu_ship_png)
FILE(menu_title_png)
FILE(shader)
FILE(ship1_png)
FILE(ship2_png)
FILE(stone_png)

#undef FILE
#define FILE(name, id) \
	{ name, { file_##id, file_##id##_size } },

std::unordered_map<std::string, std::pair<const void *, size_t>> __yip_resources = {
	FILE("res/bg.jpg", bg_jpg)
	FILE("res/carrot.png", carrot_png)
	FILE("level.xml", level_xml)
	FILE("res/menu_logo.png", menu_logo_png)
	FILE("res/menu_play.png", menu_play_png)
	FILE("res/menu_ship.png", menu_ship_png)
	FILE("res/menu_title.png", menu_title_png)
	FILE("res/shader", shader)
	FILE("res/ship1.png", ship1_png)
	FILE("res/ship2.png", ship2_png)
	FILE("res/stone.png", stone_png)
};
