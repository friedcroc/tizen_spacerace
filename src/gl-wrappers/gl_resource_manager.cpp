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
#include "gl_resource_manager.h"

const std::string GL::ResourceManager::m_DefaultTextureName = "<texture>";
const std::string GL::ResourceManager::m_DefaultShaderName = "<shader>";
const std::string GL::ResourceManager::m_DefaultProgramName = "<program>";

namespace
{
	struct GLProgram : public GL::Program
	{
		inline GLProgram(GL::ResourceManager * resMgr, const std::string & resName)
			: GL::Program(resMgr, resName) {}
	};

	struct GLShader : public GL::Shader
	{
		inline GLShader(GL::ResourceManager * resMgr, const std::string & resName, GL::Enum shaderType)
			: GL::Shader(resMgr, resName, shaderType) {}
		inline GLShader(GL::ResourceManager * resMgr, const std::pair<GL::Enum, std::string> & pair)
			: GL::Shader(resMgr, pair.second, pair.first) {}
	};

	struct GLTexture : public GL::Texture
	{
		inline GLTexture(GL::ResourceManager * resMgr, const std::string & resName)
			: GL::Texture(resMgr, resName) {}
	};
}

GL::ResourceManager::ResourceManager(::Resource::Loader & loader)
	: m_ResourceLoader(&loader)
{
	GL::init();
}

GL::ResourceManager::~ResourceManager()
{
	destroyAllResources();
}

void GL::ResourceManager::destroyAllResources()
{
	for (const ResourceWeakPtr & resourceWeakPtr : m_AllResources)
	{
		std::shared_ptr<Resource> resource = resourceWeakPtr.lock();
		if (resource)
			resource->destroy();
	}
}

void GL::ResourceManager::collectGarbage()
{
	collectGarbageIn(m_Textures);
	collectGarbageIn(m_Shaders);
	collectGarbageIn(m_Programs);
	collectGarbageIn(m_AllResources);
}

GL::TexturePtr GL::ResourceManager::createTexture(const std::string & name)
{
	TexturePtr texture = std::static_pointer_cast<Texture>(std::make_shared<GLTexture>(this, name));
	m_AllResources.push_back(texture);
	return texture;
}

GL::TexturePtr GL::ResourceManager::getTexture(const std::string & name)
{
	bool isNew = false;
	TexturePtr texture = getResource<Texture, GLTexture>(m_Textures, name, &isNew);
	if (isNew)
		texture->initFromStream(*m_ResourceLoader->openResource(name));
	return texture;
}

GL::ShaderPtr GL::ResourceManager::createShader(Enum type, const std::string & name)
{
	ShaderPtr shader = std::static_pointer_cast<Shader>(std::make_shared<GLShader>(this, name, type));
	m_AllResources.push_back(shader);
	return shader;
}

GL::ShaderPtr GL::ResourceManager::getShader(Enum type, const std::string & name)
{
	bool isNew = false;
	ShaderPtr shader = getResource<Shader, GLShader>(m_Shaders, std::make_pair(type, name), &isNew);
	if (isNew)
		shader->initFromSource(m_ResourceLoader->loadResource(name));
	return shader;
}

GL::ProgramPtr GL::ResourceManager::createProgram(const std::string & name)
{
	ProgramPtr program = std::static_pointer_cast<Program>(std::make_shared<GLProgram>(this, name));
	m_AllResources.push_back(program);
	return program;
}

GL::ProgramPtr GL::ResourceManager::getProgram(const std::string & name)
{
	bool isNew = false;
	ProgramPtr program = getResource<Program, GLProgram>(m_Programs, name, &isNew);
	if (isNew)
		program->initFromSource(m_ResourceLoader->loadResource(name));
	return program;
}

template <class T> static bool expired(const std::weak_ptr<T> & ptr)
{
	return ptr.expired();
}

template <class T1, class T2> static bool expired(const std::pair<T1, T2> & pair)
{
	return pair.second.expired();
}

template <class T> void GL::ResourceManager::collectGarbageIn(T & collection)
{
	for (auto it = collection.begin(); it != collection.end(); )
	{
		if (!expired(*it))
			++it;
		else
			it = collection.erase(it);
	}
}

template <class T, class P, class M, class K>
std::shared_ptr<T> GL::ResourceManager::getResource(M & map, const K & key, bool * isNew)
{
	std::shared_ptr<T> result;
	typename M::iterator it = map.find(key);
	if (it != map.end() && (result = it->second.lock()))
	{
		if (isNew)
			*isNew = false;
		return result;
	}
	else
	{
		if (isNew)
			*isNew = true;

		std::shared_ptr<T> resource = std::static_pointer_cast<T>(std::make_shared<P>(this, key));
		if (it != map.end())
			it->second = resource;
		else
			map.insert(std::make_pair(key, resource));

		return resource;
	}
}
