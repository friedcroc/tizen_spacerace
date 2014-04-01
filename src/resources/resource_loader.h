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
#ifndef __ed1b7a052c06201bc59982b8db7267a4__
#define __ed1b7a052c06201bc59982b8db7267a4__

#include <string>
#include <istream>
#include <memory>

namespace Resource
{
	class Loader;

	/** Strong pointer to the resource loader. */
	typedef std::shared_ptr<Loader> LoaderPtr;

	/** Strong pointer to the instance of *std::istream*. */
	typedef std::shared_ptr<std::istream> StreamPtr;

	/**
	 * Loader for resource files.
	 * This class loads resources from resources of the application using the
	 * *std::ifstream* class.
	 */
	class Loader
	{
	public:
		/** Constructor. */
		inline Loader() {}

		/** Destructor. */
		virtual inline ~Loader() {}

		/**
		 * Loads the specified resource into memory.
		 * @param name Name of the resource.
		 * @return Resource data.
		 * @throws std::runtime_error if resource could not be loaded.
		 */
		virtual std::string loadResource(const std::string & name);

		/**
		 * Opens the specified resource for reading.
		 * @param name Name of the resource.
		 * @return Input stream for the resource.
		 * @throws std::runtime_error if resource could not be opened.
		 */
		virtual StreamPtr openResource(const std::string & name);

		/**
		 * Returns reference to the standard resource loader.
		 * @return Reference to the standard resource loader.
		 */
		static Loader & standard();

	private:
		static std::string loadResourceFromStream(const StreamPtr & stream, const std::string & name);
		static StreamPtr openResourceFromFile(const std::string & path);

		Loader(const Loader &) = delete;
		Loader & operator=(const Loader &) = delete;
	};
}

#endif
