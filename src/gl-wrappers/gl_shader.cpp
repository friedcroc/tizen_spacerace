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
#include "gl_shader.h"
#include "gl_resource_manager.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

GL::Shader::Shader(ResourceManager * manager, const std::string & resName, Enum shaderType)
	: Resource(resName),
	  m_Handle(0),
	  m_Type(shaderType)
{
	(void)manager;
	m_Handle = GL::createShader(m_Type);
}

GL::Shader::~Shader()
{
	destroy();
}

void GL::Shader::initFromSource(const char * data)
{
	const GL::Char * source[1] = { data };
	GL::shaderSource(m_Handle, 1, source, nullptr);
	GL::compileShader(m_Handle);

	GL::Int logLength = 0;
	GL::getShaderiv(m_Handle, GL::INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> log(static_cast<size_t>(logLength + 1), 0);
		GL::getShaderInfoLog(m_Handle, logLength, nullptr, log.data());
		std::clog << log.data() << std::endl;
	}
}

void GL::Shader::initFromSource(const std::vector<const char *> & data)
{
	GL::shaderSource(m_Handle, static_cast<GL::Sizei>(data.size()), (const Char **)data.data(), nullptr);
	GL::compileShader(m_Handle);

	GL::Int logLength = 0;
	GL::getShaderiv(m_Handle, GL::INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> log(static_cast<size_t>(logLength + 1), 0);
		GL::getShaderInfoLog(m_Handle, logLength, nullptr, log.data());
		std::clog << log.data() << std::endl;
	}
}

void GL::Shader::destroy()
{
	if (m_Handle != 0)
	{
		GL::deleteShader(m_Handle);
		m_Handle = 0;
	}
}
