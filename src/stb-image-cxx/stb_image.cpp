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
#include "stb_image.hpp"
#include <stdexcept>

static char g_DummyData;

struct Stb::Image::Wrapper : public Stb::Image
{
	inline Wrapper() : Image(&g_DummyData) {}
};

static int stb_eof(void * user)
{
	try
	{
		std::istream * stream = reinterpret_cast<std::istream *>(user);
		return stream->eof() || stream->bad() || stream->fail();
	}
	catch (const std::exception & e)
	{
		std::clog << "Error reading image: " << e.what() << std::endl;
		return 1;
	}
}

static int stb_read(void * user, char * data, int size)
{
	if (size < 0)
		size = 0;

	try
	{
		std::istream * stream = reinterpret_cast<std::istream *>(user);
		char * p = data;
		int totalBytesRead = 0;
		do
		{
			if (stream->eof() || stream->bad() || stream->fail())
				break;
			stream->read(p, static_cast<std::streamsize>(size));
			int bytesRead = static_cast<int>(stream->gcount());
			totalBytesRead += bytesRead;
			p += bytesRead;
			size -= bytesRead;
		}
		while (size > 0);
		return totalBytesRead;
	}
	catch (const std::exception & e)
	{
		std::clog << "Error reading image: " << e.what() << std::endl;
		return 0;
	}
}

static void stb_skip(void * user, unsigned n)
{
	try
	{
		std::istream * stream = reinterpret_cast<std::istream *>(user);
		stream->ignore(static_cast<std::streamsize>(n));
	}
	catch (const std::exception & e)
	{
		std::clog << "Error reading image: " << e.what() << std::endl;
	}
}

static const stbi_io_callbacks g_StbCB = {
	stb_read,
	stb_skip,
	stb_eof
};

Stb::Image::~Image()
{
	if (m_Data != &g_DummyData)
		stbi_image_free(m_Data);
}

Stb::ImagePtr Stb::Image::loadFromStream(std::istream & s, Format fmt)
{
	ImagePtr image = std::static_pointer_cast<Image>(std::make_shared<Image::Wrapper>());

	try
	{
		int imageFmt = UNKNOWN;

		image->m_Data = stbi_load_from_callbacks(&g_StbCB, &s, &image->m_Width, &image->m_Height, &imageFmt, fmt);
		if (!image->m_Data)
			throw std::runtime_error(stbi_failure_reason());

		image->m_Format = static_cast<Format>(fmt == UNKNOWN ? imageFmt : fmt);
		if (image->m_Format == UNKNOWN)
			throw std::runtime_error("unable to determine pixel format for the image.");
	}
	catch (const std::exception & e)
	{
		if (image->m_Data)
			stbi_image_free(image->m_Data);

		std::clog << "Error reading image: " << e.what() << std::endl;
		image->m_Data = &g_DummyData;
		image->m_Width = 0;
		image->m_Height = 0;
		image->m_Format = UNKNOWN;
	}

	return image;
}
