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
#include "chain_shape.h"
#include "util.h"
#include "game.h"
#include "cxx-util/fmt.h"
#include "math/common.h"
#include "gl-wrappers/gl_vertex_attrib_pointer.h"
#include "gl-wrappers/gl_program_binder.h"
#include "gl-wrappers/gl_texture_binder.h"
#include <vector>

ChainShape::ChainShape(b2World * world, TiXmlElement * element)
{
	TiXmlElement * vert = element->FirstChildElement("vertices");
	if (!vert)
		throw std::runtime_error("there is no element 'vertices' in the chain shape.");

	for (TiXmlElement * e = vert->FirstChildElement("item"); e; e = e->NextSiblingElement("item"))
	{
		const char * text = e->GetText();
		if (!text)
			throw std::runtime_error("invalid item in the chain shape.");

		m_Vertices.push_back(parseVec2(text));
	}

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	m_Body = world->CreateBody(&bodyDef);

	b2ChainShape shape;
	shape.CreateChain(m_Vertices.data(), static_cast<int>(m_Vertices.size()));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.5;
	fixtureDef.restitution = 0.3;
	m_Body->CreateFixture(&fixtureDef);
}

ChainShape::~ChainShape()
{
}

void ChainShape::runFrame(const mat4 & m)
{
	const float SIZE = 10.0f;

	std::vector<float> pos;
	std::vector<float> tex;

	for (size_t i = 1; i < m_Vertices.size(); i++)
	{
		const b2Vec2 & start = m_Vertices[i - 1];
		const b2Vec2 & end = m_Vertices[i];

		float length = (end - start).Length();
		size_t count = floor(length / SIZE);

		if (count == 0)
			continue;

		float realLength = count * SIZE;
		float step = (length - realLength) / (count - 1);

		b2Vec2 dir = end - start;
		dir.Normalize();

		b2Vec2 stepDir = dir;
		stepDir *= step;

		b2Vec2 norm = b2Vec2(dir.y, -dir.x);
		norm *= -SIZE * 0.5f;

		dir *= SIZE * 0.5f;
		b2Vec2 p = start + norm + dir;
		for (size_t j = 0; j < count; j++)
		{
			float x1 = p.x + -0.5f * SIZE * 0.9f;
			float y1 = p.y + -0.5f * SIZE * 0.9f;
			float x2 = p.x + 0.5f * SIZE * 0.9f;
			float y2 = p.y + 0.5f * SIZE * 0.9f;

			pos.push_back(x1);
			pos.push_back(y1);
			pos.push_back(x2);
			pos.push_back(y1);
			pos.push_back(x1);
			pos.push_back(y2);

			pos.push_back(x2);
			pos.push_back(y1);
			pos.push_back(x1);
			pos.push_back(y2);
			pos.push_back(x2);
			pos.push_back(y2);

			tex.push_back(0.0f);
			tex.push_back(0.0f);
			tex.push_back(1.0f);
			tex.push_back(0.0f);
			tex.push_back(0.0f);
			tex.push_back(1.0f);

			tex.push_back(1.0f);
			tex.push_back(0.0f);
			tex.push_back(0.0f);
			tex.push_back(1.0f);
			tex.push_back(1.0f);
			tex.push_back(1.0f);

			p = p + dir + dir + stepDir;
		}
	}

	GL::ProgramPtr program = shaderProgram();

	GL::enable(GL::BLEND);
	GL::blendFunc(GL::SRC_ALPHA, GL::ONE_MINUS_SRC_ALPHA);

	GL::ProgramBinder programBinder(program);
	GL::TextureBinder textureBinder(Game::instance()->resourceManager()->getTexture("res/stone.png"));

	GL::uniformMatrix4fv(GL::getUniformLocation(program->handle(), "u_mvp"), 1, GL::FALSE, &m[0]);
	int attrPos = GL::getAttribLocation(program->handle(), "a_position");
	int attrTex = GL::getAttribLocation(program->handle(), "a_texCoord");
	int uniformTex = GL::getUniformLocation(program->handle(), "u_texture");

	GL::VertexAttribPointer a1(attrPos, 2, GL::FLOAT, GL::FALSE, 0, pos.data());
	GL::VertexAttribPointer a2(attrTex, 2, GL::FLOAT, GL::FALSE, 0, tex.data());
	GL::uniform1i(uniformTex, 0);
	GL::drawArrays(GL::TRIANGLES, 0, pos.size() / 2);
}
