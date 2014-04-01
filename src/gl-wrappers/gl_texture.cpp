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
#include "gl_texture.h"
#include "gl_resource_manager.h"
#include "gl_texture_binder.h"
#include <sstream>
#include <stdexcept>

GL::Texture::Texture(GL::ResourceManager * mgr, const std::string & resName)
	: Resource(resName),
	  m_Handle(0),
	  m_Width(0),
	  m_Height(0)
{
	(void)mgr;
	GL::genTextures(1, &m_Handle);
}

GL::Texture::~Texture()
{
	destroy();
}

void GL::Texture::initFromStream(std::istream & stream, Stb::Image::Format fmt)
{
	Stb::ImagePtr image = Stb::Image::loadFromStream(stream, fmt);
	uploadImage(*image, 0, GL::TEXTURE_2D);
	GL::texParameterf(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::CLAMP_TO_EDGE);
	GL::texParameterf(GL::TEXTURE_2D, GL::TEXTURE_WRAP_T, GL::CLAMP_TO_EDGE);
	GL::texParameterf(GL::TEXTURE_2D, GL::TEXTURE_MIN_FILTER, GL::LINEAR);
	GL::texParameterf(GL::TEXTURE_2D, GL::TEXTURE_MAG_FILTER, GL::LINEAR);
}

void GL::Texture::uploadImage(const Stb::Image & image, int level, GL::Enum target)
{
	GL::Enum fmt = GL::NONE;

	switch (image.format())
	{
	case Stb::Image::UNKNOWN: break;
	case Stb::Image::ALPHA: fmt = GL::ALPHA; break;
	case Stb::Image::LUMINANCE_ALPHA: fmt = GL::LUMINANCE_ALPHA; break;
	case Stb::Image::RGB: fmt = GL::RGB; break;
	case Stb::Image::RGBA: fmt = GL::RGBA; break;
	}

	if (fmt == GL::NONE)
		std::clog << "Unable to upload image to OpenGL: " << "image has invalid pixel format." << std::endl;

	if (level == 0 || m_Width == 0 || m_Height == 0)
		setSize(image.width(), image.height());

	bind(target);
	GL::pixelStorei(GL::UNPACK_ALIGNMENT, 1);
	GL::texImage2D(target, level, fmt, image.width(), image.height(), 0, fmt, GL::UNSIGNED_BYTE, image.data());
}

void GL::Texture::destroy()
{
	if (m_Handle != 0)
	{
		GL::deleteTextures(1, &m_Handle);
		m_Handle = 0;
	}
	m_Width = 0;
	m_Height = 0;
}
