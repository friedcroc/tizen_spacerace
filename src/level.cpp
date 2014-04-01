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
#include "gl-wrappers/gl_vertex_attrib_pointer.h"
#include "gl-wrappers/gl_program_binder.h"
#include "gl-wrappers/gl_texture_binder.h"
#include "game.h"
#include "util.h"
#include "level.h"

Level::Level()
{
	m_BackTexture = Game::instance()->resourceManager()->getTexture("res/bg.jpg");
	GL::texParameteri(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::REPEAT);
	GL::texParameteri(GL::TEXTURE_2D, GL::TEXTURE_WRAP_T, GL::REPEAT);
}

Level::~Level()
{
}

void Level::renderBack(const mat4 & projectionMatrix, float x, float y)
{
	GL::enable(GL::BLEND);
	GL::blendFunc(GL::SRC_ALPHA, GL::ONE_MINUS_SRC_ALPHA);

	GL::ProgramPtr program = shaderProgram();

	GL::ProgramBinder programBinder(program);
	GL::TextureBinder textureBinder(m_BackTexture);

	GL::uniformMatrix4fv(GL::getUniformLocation(program->handle(), "u_mvp"), 1, GL::FALSE, &projectionMatrix[0]);
	int attrPos = GL::getAttribLocation(program->handle(), "a_position");
	int attrTex = GL::getAttribLocation(program->handle(), "a_texCoord");
	int uniformTex = GL::getUniformLocation(program->handle(), "u_texture");

	float x1 = 0.0f;
	float y1 = 0.0f;
	float x2 = 720.0f;
	float y2 = 1280.0f;

	const float pos[] = {
		x1, y1,
		x2, y1,
		x1, y2,
		x2, y2
	};

	float tx1 = x / 1024.0f;
	float ty1 = y / 1024.0f;
	float tx2 = (x + 720.0f ) / 1024.0f;
	float ty2 = (y + 1280.0f) / 1024.0f;

	const float tex[] = {
		tx1, ty1,
		tx2, ty1,
		tx1, ty2,
		tx2, ty2
	};

	GL::VertexAttribPointer a1(attrPos, 2, GL::FLOAT, GL::FALSE, 0, pos);
	GL::VertexAttribPointer a2(attrTex, 2, GL::FLOAT, GL::FALSE, 0, tex);
	GL::uniform1i(uniformTex, 0);
	GL::drawArrays(GL::TRIANGLE_STRIP, 0, 4);
}
