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
#ifndef __febb0d4d5a85eeec11c8faf83e369998__
#define __febb0d4d5a85eeec11c8faf83e369998__

#include "gl_resource.h"
#include "../gl/gl.h"
#include <utility>
#include <vector>
#include <string>

namespace GL
{
	class Program;
	class ResourceManager;

	/** OpenGL ES shader. */
	class Shader : public Resource
	{
	public:
		/**
		 * Returns type of the shader.
		 * @returns GL::VERTEX_SHADER if this is a vertex shader
		 * or GL::FRAGMENT_SHADER if this is a fragment shader.
		 */
		inline Enum type() const { return m_Type; }

		/**
		 * Returns raw OpenGL ES handle of the shader.
		 * @return Raw handle of the shader.
		 */
		inline UInt handle() const { return m_Handle; }

		/**
		 * Initializes shader from source code.
		 * @param data Source code.
		 */
		void initFromSource(const char * data);

		/**
		 * Initializes shader from source code.
		 * @param data Source code.
		 */
		void initFromSource(const std::vector<const char *> & data);

		/**
		 * Initializes shader from source code.
		 * @param data Source code.
		 */
		inline void initFromSource(const std::string & data) { initFromSource(data.c_str()); }

	protected:
		/**
		 * Constructor.
		 * @param manager Pointer to the resource manager.
		 * @param resName Name of the shader resource.
		 * @param shaderType Type of the shader. Could be GL::VERTEX_SHADER or GL::FRAGMENT_SHADER.
		 */
		Shader(ResourceManager * manager, const std::string & resName, Enum shaderType);

		/** Destructor. */
		~Shader();

		/**
		 * Releases the associated OpenGL shader.
		 * This is equivalent to GL::deleteShader.
		 */
		void destroy() override;

	private:
		UInt m_Handle;
		Enum m_Type;

		Shader(const Shader &) = delete;
		Shader & operator=(const Shader &) = delete;

		friend class Program;
		friend class ResourceManager;
	};

	/** Strong pointer to the OpenGL ES shader. */
	typedef std::shared_ptr<Shader> ShaderPtr;
	/** Weak pointer to the OpenGL ES shader. */
	typedef std::weak_ptr<Shader> ShaderWeakPtr;
}

#endif
