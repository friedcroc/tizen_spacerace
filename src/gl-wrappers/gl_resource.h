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
#ifndef __f471791f3e0fda4867317dc478eafd4f__
#define __f471791f3e0fda4867317dc478eafd4f__

#include <string>
#include <cassert>
#include <memory>

namespace GL
{
	class ResourceManager;

	/** Base class for resources managed by GL::ResourceManager. */
	class Resource
	{
	public:
		/**
		 * Returns name of the resource.
		 * @return Name of the resource.
		 */
		inline const std::string & name() const noexcept { return m_Name; }

	protected:
		/**
		 * Constructor.
		 * @param resName Name of the resource.
		 */
		Resource(const std::string & resName);

		/** Destructor. */
		virtual ~Resource();

		/**
		 * Releases the associated OpenGL resource.
		 * This method allows to release the associated OpenGL resource without actually destroying
		 * this instance of GL::Resource.
		 */
		virtual void destroy() = 0;

	private:
		std::string m_Name;

		Resource(const Resource &) = delete;
		Resource & operator=(const Resource &) = delete;

		friend class ResourceManager;
	};

	/** Strong pointer to the OpenGL resource. */
	typedef std::shared_ptr<Resource> ResourcePtr;
	/** Weak pointer to the OpenGL resource. */
	typedef std::weak_ptr<Resource> ResourceWeakPtr;
}

#endif
