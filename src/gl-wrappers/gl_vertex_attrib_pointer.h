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
#ifndef __9c261e9c451bfabcb33bb46b7a14672a__
#define __9c261e9c451bfabcb33bb46b7a14672a__

#include "../gl/gl.h"

namespace GL
{
	/**
	 * RAII-style class for GL::enableVertexAttribArray and GL::disableVertexAttribArray.
	 * This class allows convenient and exception-safe initialization and use of vertex attrib arrays.
	 *
	 * It is recommended to create an instance of this class instead of calling GL::vertexAttribPointer,
	 * GL::enableVertexAttribArray and GL::disableVertexAttribArray:
	 * @code
	 * GL::VertexAttribPointer vertices(verticesIndex, 3, GL::FLOAT, GL::FALSE, 0, vertices);
	 * GL::VertexAttribPointer texCoords(texCoordsIndex, 2, GL::FLOAT, GL::FALSE, 0, texCoords);
	 * GL::drawArrays(GL::TRIANGLE_STRIP, 0, 4);
	 * @endcode
	 */
	class VertexAttribPointer
	{
	public:
		/**
		 * Constructor.
		 * Calls GL::vertexAttribPointer and GL::enableVertexAttribArray.
		 * Parameters are the same as those of GL::vertexAttribPointer.
		 * @param index Index of the generic vertex attribute to be modified.
		 * @param size Number of components per generic vertex attribute. Must be 1, 2, 3 or 4.
		 * @param type Data type of each component in the array. Symbolic constants GL::BYTE, GL::UNSIGNED_BYTE,
		 * GL::SHORT, GL::UNSIGNED_SHORT, GL::FIXED or GL::FLOAT are accepted.
		 * @param normalized Specifies whether fixed-point data values should be normalized (GL::TRUE) or
		 * converted directly as fixed-point values (GL::FALSE) when they are accessed.
		 * @param stride Byte offset between consecutive generic vertex attributes. If *stride* is 0, the generic
		 * vertex attributes are understood to be tightly packed in the array.
		 * @param pointer Specifies a pointer to the first component of the first generic vertex attribute in the
		 * array.
		 * @see GL::vertexAttribPointer, GL::enableVertexAttribArray, GL::disableVertexAttribArray.
		 */
		inline VertexAttribPointer(UInt index, Int size, Enum type, Boolean normalized, Sizei stride,
				const void * pointer)
			: m_Index(index)
		{
			vertexAttribPointer(m_Index, size, type, normalized, stride, pointer);
			enableVertexAttribArray(m_Index);
		}

		/** Destructor. Calls GL::disableVertexAttribArray. */
		inline ~VertexAttribPointer()
		{
			disableVertexAttribArray(m_Index);
		}

	private:
		GL::UInt m_Index;

		VertexAttribPointer(const VertexAttribPointer &) = delete;
		VertexAttribPointer & operator=(const VertexAttribPointer &) = delete;
	};
}

#endif
