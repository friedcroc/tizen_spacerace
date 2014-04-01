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
#ifndef __2266940fc02274d1b0dbb64a279b3fa2__
#define __2266940fc02274d1b0dbb64a279b3fa2__

#include "../gl/gl.h"
#include "../stb-image-cxx/stb_image.hpp"
#include "gl_resource.h"
#include <strstream>

namespace GL
{
	/** OpenGL ES texture. */
	class Texture : public Resource
	{
	public:
		/**
		 * Binds texture into the OpenGL context.
		 * This is equivalent to GL::bindTexture.
		 * @param target Target to bind texture to (default is GL::TEXTURE_2D).
		 */
		inline void bind(Enum target = GL::TEXTURE_2D) { GL::bindTexture(target, m_Handle); }

		/**
		 * Initializes texture from the specified stream.
		 * @note This method binds the texture into the OpenGL context.
		 * @note This method changes GL::UNPACK_ALIGNMENT.
		 * @param stream Stream to initialize from.
		 * @param fmt Desired pixel format of the texture (image will be converted into the specified format).
		 * Use Stb::Image::UNKNOWN to use format of the image.
		 */
		void initFromStream(std::istream & stream, Stb::Image::Format fmt = Stb::Image::UNKNOWN);

		/**
		 * Initializes texture from binary data.
		 * @note This method binds the texture into the OpenGL context.
		 * @note This method changes GL::UNPACK_ALIGNMENT.
		 * @param data Pointer to the data.
		 * @param size Size of the data.
		 * @param fmt Desired pixel format of the texture (image will be converted into the specified format).
		 * Use Stb::Image::UNKNOWN to use format of the image.
		 */
		inline void initFromData(const void * data, size_t size, Stb::Image::Format fmt = Stb::Image::UNKNOWN)
		{
			std::istrstream stream(reinterpret_cast<const char *>(data), static_cast<std::streamsize>(size));
			initFromStream(stream, fmt);
		}

		/**
		 * Initializes texture from binary data.
		 * @note This method binds the texture into the OpenGL context.
		 * @note This method changes GL::UNPACK_ALIGNMENT.
		 * @param data Binary data.
		 * @param fmt Desired pixel format of the texture (image will be converted into the specified format).
		 * Use Stb::Image::UNKNOWN to use format of the image.
		 */
		inline void initFromData(const std::string & data, Stb::Image::Format fmt = Stb::Image::UNKNOWN)
		{
			std::istrstream stream(data.data(), data.size());
			initFromStream(stream, fmt);
		}

		/**
		 * Uploads the specified image into the specified mipmap level of the texture.
		 * @note This method binds the texture into the OpenGL context.
		 * @note This method changes GL::UNPACK_ALIGNMENT.
		 * @param image Image.
		 * @param level Mipmap level to upload image into
		 * @param target Binding target for the texture.
		 */
		inline void uploadImage(const Stb::Image & image, int level = 0, Enum target = GL::TEXTURE_2D);

		/**
		 * Returns width of the texture in pixels.
		 * @return Width of the texture in pixels.
		 */
		int width() const { return m_Width; }

		/**
		 * Returns height of the texture in pixels.
		 * @return Height of the texture in pixels.
		 */
		int height() const { return m_Height; }

		/**
		 * Sets size of the texture in pixels.
		 * @param w Width of the texture in pixels.
		 * @param h Height of the texture in pixels.
		 */
		inline void setSize(int w, int h) { m_Width = w; m_Height = h; }

		/**
		 * Sets width of the texture in pixels.
		 * @param w Width of the texture in pixels.
		 */
		inline void setWidth(int w) { m_Width = w; }

		/**
		 * Sets height of the texture in pixels.
		 * @param h Height of the texture in pixels.
		 */
		inline void setHeight(int h) { m_Height = h; }

	protected:
		/**
		 * Constructor.
		 * @param mgr Pointer to the resource manager.
		 * @param resName Name of the texture resource.
		 */
		Texture(ResourceManager * mgr, const std::string & resName);

		/** Destructor. */
		~Texture();

		/**
		 * Releases the associated OpenGL texture.
		 * This is equivalent to GL::deleteTextures.
		 */
		void destroy() override;

	private:
		UInt m_Handle;
		int m_Width;
		int m_Height;

		Texture(const Texture &) = delete;
		Texture & operator=(const Texture &) = delete;

		friend class ResourceManager;
	};

	/** Strong pointer to the OpenGL ES texture. */
	typedef std::shared_ptr<Texture> TexturePtr;
	/** Weak pointer to the OpenGL ES texture. */
	typedef std::weak_ptr<Texture> TextureWeakPtr;
}

#endif
