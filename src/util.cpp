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
#include "util.h"
#include "game.h"
#include "gl-wrappers/gl_vertex_attrib_pointer.h"
#include "gl-wrappers/gl_program_binder.h"
#include "gl-wrappers/gl_texture_binder.h"
#include "cxx-util/fmt.h"
#include <stdexcept>

static GL::ProgramPtr g_Program;

double parseDouble(const std::string & str)
{
	const char * p = str.c_str();
	const char * e = p + str.length();

	char * end = nullptr;
	double value = strtod(p, &end);
	if (end != e)
		throw std::runtime_error(fmt() << "invalid floating-point number: '" << str << "'.");

	return value;
}

b2Vec2 parseVec2(const std::string & text)
{
	const char * p = text.c_str();

	const char * comma = strchr(p, ',');
	if (!comma)
		throw std::runtime_error("invalid vec2 value.");

	double x = parseDouble(std::string(p, comma - p));
	double y = parseDouble(comma + 1);

	return b2Vec2(static_cast<float32>(x), static_cast<float32>(y));
}

GL::ProgramPtr shaderProgram()
{
	if (!g_Program.get())
		g_Program = Game::instance()->resourceManager()->getProgram("res/shader");
	return g_Program;
}

void render(const mat4 & matrix, const GL::TexturePtr & texture, float w, float h)
{
	GL::enable(GL::BLEND);
	GL::blendFunc(GL::SRC_ALPHA, GL::ONE_MINUS_SRC_ALPHA);

	GL::ProgramBinder programBinder(shaderProgram());
	GL::TextureBinder textureBinder(texture);

	GL::uniformMatrix4fv(GL::getUniformLocation(g_Program->handle(), "u_mvp"), 1, GL::FALSE, &matrix[0]);
	int attrPos = GL::getAttribLocation(g_Program->handle(), "a_position");
	int attrTex = GL::getAttribLocation(g_Program->handle(), "a_texCoord");
	int uniformTex = GL::getUniformLocation(g_Program->handle(), "u_texture");

	float x1 = -0.5f * w;
	float y1 = -0.5f * h;
	float x2 = 0.5f * w;
	float y2 = 0.5f * h;

	const float pos[] = {
		x1, y1,
		x2, y1,
		x1, y2,
		x2, y2
	};

	static const float tex[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};

	GL::VertexAttribPointer a1(attrPos, 2, GL::FLOAT, GL::FALSE, 0, pos);
	GL::VertexAttribPointer a2(attrTex, 2, GL::FLOAT, GL::FALSE, 0, tex);
	GL::uniform1i(uniformTex, 0);
	GL::drawArrays(GL::TRIANGLE_STRIP, 0, 4);
}
