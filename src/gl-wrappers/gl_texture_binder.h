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
#ifndef __695009233d48e4afc60dfabb116ee572__
#define __695009233d48e4afc60dfabb116ee572__

#include "gl_texture.h"
#include "../gl/gl.h"

namespace GL
{
	/**
	 * RAII-style class for texture binding.
	 * This class allows convenient and exception-safe binding and unbinding of textures.
	 *
	 * It is recommended to create an instance of this class instead of calling GL::bindTexture.
	 * @code
	 * GL::BindTexture textureBinder1(texture);
	 * GL::BindTexture textureBinder2(texture, GL::TEXTURE1);
	 * GL::BindTexture textureBinder2(texture, GL::TEXTURE2, GL::TEXTURE_CUBE_MAP);
	 * // ...
	 * GL::drawArrays(GL::TRIANGLE_STRIP, 0, 4);
	 * @endcode
	 */
	class TextureBinder
	{
	public:
		/**
		 * Constructor.
		 * Calls GL::activeTexture and GL::bindTexture with the specified texture.
		 * @param texture Texture to use.
		 * @param unit Texture unit to use (default is GL::TEXTURE0).
		 * @param target Texture binding target (default is GL::TEXTURE_2D).
		 * @see GL::bindTexture, GL::activeTexture.
		 */
		inline TextureBinder(const GL::TexturePtr & texture, GL::Enum unit = GL::TEXTURE0,
				GL::Enum target = GL::TEXTURE_2D)
			: m_Unit(unit),
			  m_Target(target)
		{
			GL::activeTexture(unit);
			texture->bind(target);
		}

		/** Destructor. Calls GL::bindTexture with texture handle set to zero. */
		inline ~TextureBinder()
		{
			GL::activeTexture(m_Unit);
			GL::bindTexture(m_Target, 0);
		}

	private:
		GL::Enum m_Unit;
		GL::Enum m_Target;

		TextureBinder(const TextureBinder &) = delete;
		TextureBinder & operator=(const TextureBinder &) = delete;
	};
}

#endif
