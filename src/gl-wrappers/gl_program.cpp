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
#include "gl_program.h"
#include "gl_resource_manager.h"
#include "gl_program_binder.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

static bool iswhite(char ch)
{
	return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}

GL::Program::Program(ResourceManager * resMgr, const std::string & resName)
	: Resource(resName),
	  m_Manager(resMgr)
{
	m_Handle = GL::createProgram();
}

GL::Program::~Program()
{
	destroy();
}

void GL::Program::initFromSource(const char * data)
{
	if (!m_Manager)
		throw std::runtime_error("resource manager is not available.");

	std::vector<std::string> lines;

	for (const char * p = data; ; )
	{
		const char * end = strchr(p, '\n');
		if (end)
		{
			size_t length = end - p;
			while (length > 0 && iswhite(p[length - 1]))
				--length;
			lines.push_back(std::string(p, length) + "\n");
			p = end + 1;
		}
		else
		{
			size_t length = strlen(p);
			while (length > 0 && iswhite(p[length - 1]))
				--length;
			lines.push_back(std::string(p, length) + "\n");
			break;
		}
	}

	std::vector<const char *> vertex;
	std::vector<const char *> fragment;

	vertex.reserve(lines.size());
	fragment.reserve(lines.size());

	bool hasVertex = false, hasFragment = 0;
	Enum type = GL::NONE;
	for (std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end(); ++it)
	{
		if (it->c_str()[0] != '%')
		{
			vertex.push_back(type == GL::NONE || type == GL::VERTEX_SHADER ? it->c_str() : "");
			fragment.push_back(type == GL::NONE || type == GL::FRAGMENT_SHADER ? it->c_str() : "");
		}
		else
		{
			const std::string & str = *it;
			const char * file = nullptr;

			vertex.push_back("");
			fragment.push_back("");

			if (str.length() >= 7 && !memcmp(str.c_str(), "%vertex", 7))
			{
				type = GL::VERTEX_SHADER;
				file = str.c_str() + 7;
			}
			else if (str.length() >= 9 && !memcmp(str.c_str(), "%fragment", 9))
			{
				type = GL::FRAGMENT_SHADER;
				file = str.c_str() + 9;
			}
			else
			{
				std::stringstream ss;
				ss << "invalid directive '" << str << "' in the vertex program.";
				throw std::runtime_error(ss.str());
			}

			if (file)
			{
				while (iswhite(*file))
					++file;
				if (!*file)
					file = nullptr;
			}

			if (!file)
			{
				if (type == GL::VERTEX_SHADER)
					hasVertex = true;
				else if (type == GL::FRAGMENT_SHADER)
					hasFragment = true;
			}
			else
			{
				std::string filename(file);
				if (filename.length() > 0 && filename[filename.length() - 1] == '\n')
					filename.resize(filename.length() - 1);
				attachShader(m_Manager->getShader(type, filename));
			}
		}
	}

	if (hasVertex)
	{
		ShaderPtr shader = m_Manager->createShader(GL::VERTEX_SHADER);
		shader->initFromSource(vertex);
		attachShader(shader);
	}

	if (hasFragment)
	{
		ShaderPtr shader = m_Manager->createShader(GL::FRAGMENT_SHADER);
		shader->initFromSource(fragment);
		attachShader(shader);
	}

	link();
}

void GL::Program::link()
{
	linkProgram(m_Handle);

	GL::Int logLength = 0;
	GL::getProgramiv(m_Handle, GL::INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> log(static_cast<size_t>(logLength + 1), 0);
		GL::getProgramInfoLog(m_Handle, logLength, nullptr, log.data());
		std::clog << "Linking program \"" << name() << "\":\n" << log.data() << std::endl;
	}
}

void GL::Program::validate()
{
	validateProgram(m_Handle);

	GL::Int logLength = 0;
	GL::getProgramiv(m_Handle, GL::INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> log(static_cast<size_t>(logLength + 1), 0);
		GL::getProgramInfoLog(m_Handle, logLength, nullptr, log.data());
		std::clog << "Validating program \"" << name() << "\":\n" << log.data() << std::endl;
	}
}

void GL::Program::destroy()
{
	if (m_Handle != 0)
	{
		GL::deleteProgram(m_Handle);
		m_Handle = 0;
	}
	m_Manager = NULL;
}
