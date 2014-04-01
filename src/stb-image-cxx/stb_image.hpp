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
#ifndef __616e90bab7e8b0734da4c1300d61e425__
#define __616e90bab7e8b0734da4c1300d61e425__

#include "../stb-image/stb_image.h"
#include <memory>
#include <iostream>

namespace Stb
{
	class Image;

	/** Strong pointer to the image. */
	typedef std::shared_ptr<Image> ImagePtr;

	/** In-memory representation of an image. */
	class Image
	{
	public:
		/** Format of the image. */
		enum Format
		{
			UNKNOWN = 0,			/**< Format is unknown or should be auto-detected. */
			ALPHA = 1,				/**< Format is GL::ALPHA (8-bit alpha channel). */
			LUMINANCE_ALPHA = 2,	/**< Format is GL::LUMINANCE_ALPHA (8-bit luminance and 8-bit alpha). */
			RGB = 3,				/**< Format is GL::RGB (8-bit per channel). */
			RGBA = 4				/**< Format is GL::RGBA (8-bit per channel). */
		};

		/**
		 * Loads image from the specified input stream.
		 * @param s Stream to load image from.
		 * @param fmt Target format. The image will be converted into the requested format, if needed.
		 * To automatically detect target format, value of UNKNOWN could be used.
		 */
		static ImagePtr loadFromStream(std::istream & s, Format fmt = UNKNOWN);

		/** Destructor. */
		~Image();

		/**
		 * Returns pointer to the image data.
		 * @return Pointer to the image data.
		 */
		inline void * data() { return m_Data; }

		/**
		 * Returns pointer to the image data.
		 * @return Pointer to the image data.
		 */
		inline const void * data() const { return m_Data; }

		/**
		 * Returns width of the image in pixels.
		 * @return Width of the image in pixels.
		 */
		inline int width() const { return m_Width; }

		/**
		 * Returns height of the image in pixels.
		 * @return Height of the image in pixels.
		 */
		inline int height() const { return m_Height; }

		/**
		 * Returns format of the image.
		 * @return Format of the image.
		 */
		inline Format format() const { return m_Format; }

	private:
		struct Wrapper;

		void * m_Data;
		int m_Width;
		int m_Height;
		Format m_Format;

		inline Image(void * data) : m_Data(data), m_Width(0), m_Height(0), m_Format(UNKNOWN) {}

		Image(const Image &) = delete;
		Image & operator=(const Image &) = delete;

		friend struct Wrapper;
	};
}

#endif
