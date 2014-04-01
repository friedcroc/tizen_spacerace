/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 FriedCroc Team (admin@friedcroc.com).
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
#include "math/mat3.h"
#include "math/mat4.h"
#include "cxx-util/fmt.h"
#include "tinyxml/tinyxml.h"
#include "gl-wrappers/gl_vertex_attrib_pointer.h"
#include "gl-wrappers/gl_program_binder.h"
#include "gl-wrappers/gl_texture_binder.h"
#include "game.h"
#include "menu.h"
#include "chain_shape.h"
#include "game_level.h"
#include "obstacle.h"
#include "util.h"
#include <locale.h>

Menu::Menu()
{
	m_LogoTexture = Game::instance()->resourceManager()->getTexture("res/menu_logo.png");
	m_PlayTexture = Game::instance()->resourceManager()->getTexture("res/menu_play.png");
	m_ShipTexture = Game::instance()->resourceManager()->getTexture("res/menu_ship.png");
	m_TitleTexture = Game::instance()->resourceManager()->getTexture("res/menu_title.png");
}

Menu::~Menu()
{
}

void Menu::runFrame()
{
	mat4 projectionMatrix = mat4::ortho(0, 720, 1280, 0, -100, 100);
	mat4 m;

	renderBack(projectionMatrix);

	m = projectionMatrix * mat4::translation(360.0f, 150.0f, 0.0f);
	render(m, m_TitleTexture, 386.0f, 177.0f);

	m = projectionMatrix * mat4::translation(360.0f, 515.0f, 0.0f);
	render(m, m_ShipTexture, 198.0f, 337.0f);

	m = projectionMatrix * mat4::translation(360.0f, 910.0f, 0.0f);
	render(m, m_PlayTexture, 315.0f, 314.0f);

	m = projectionMatrix * mat4::translation(360.0f, 1190.0f, 0.0f);
	render(m, m_LogoTexture, 561.0f, 157.0f);
}

void Menu::onKeyPress(Sys::KeyCode key)
{
}

void Menu::onKeyRelease(Sys::KeyCode key)
{
	Game::instance()->setLevel(std::unique_ptr<Level>(new GameLevel));
}
