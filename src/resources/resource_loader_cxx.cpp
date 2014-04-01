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
#include "resource_loader.h"
#include <unordered_map>
#include <sstream>
#include <strstream>

extern std::unordered_map<std::string, std::pair<const void *, size_t>> __yip_resources;

std::string Resource::Loader::loadResource(const std::string & name)
{
	return loadResourceFromStream(openResource(name), name);
}

Resource::StreamPtr Resource::Loader::openResource(const std::string & name)
{
	auto it = __yip_resources.find(name);
	if (it == __yip_resources.end())
	{
		std::stringstream ss;
		ss << "there is no resource named '" << name << "'.";
		throw std::runtime_error(ss.str());
	}

	const char * ptr = reinterpret_cast<const char *>(it->second.first);
	std::streamsize size = static_cast<std::streamsize>(it->second.second);

	return std::make_shared<std::istrstream>(ptr, size);
}
