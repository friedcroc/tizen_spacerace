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
#ifndef __b38e3901acc6d421bef185cb94551820__
#define __b38e3901acc6d421bef185cb94551820__

#include "gl_program.h"
#include "../gl/gl.h"

namespace GL
{
	/**
	 * RAII-style class for shader program binding.
	 * This class allows convenient and exception-safe binding and unbinding of shader programs.
	 *
	 * It is recommended to create an instance of this class instead of calling GL::useProgram.
	 * @code
	 * GL::ProgramBinder programBinder(program);
	 * // ...
	 * GL::drawArrays(GL::TRIANGLE_STRIP, 0, 4);
	 * @endcode
	 */
	class ProgramBinder
	{
	public:
		/**
		 * Constructor.
		 * Calls GL::useProgram with the specified shader program.
		 * @param program Shader program to use.
		 * @see GL::useProgram.
		 */
		inline ProgramBinder(const GL::ProgramPtr & program)
		{
			program->use();
		}

		/** Destructor. Calls GL::useProgram with program handle set to zero. */
		inline ~ProgramBinder()
		{
			GL::useProgram(0);
		}

	private:
		ProgramBinder(const ProgramBinder &) = delete;
		ProgramBinder & operator=(const ProgramBinder &) = delete;
	};
}

#endif
