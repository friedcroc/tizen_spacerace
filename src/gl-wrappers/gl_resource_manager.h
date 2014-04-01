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
#ifndef __bd60f34af632e5ad2a9b5bb6a5b67443__
#define __bd60f34af632e5ad2a9b5bb6a5b67443__

#include "gl_texture.h"
#include "gl_shader.h"
#include "gl_program.h"
#include "../resources/resource_loader.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace GL
{
	/** @cond */
	namespace Internal
	{
		// Key for unordered_map of shaders
		typedef std::pair<Enum, std::string> ShaderMapKey;
		struct ShaderMapKeyHash {
			inline size_t operator()(const ShaderMapKey & value) const
				{ return std::hash<std::string>()(value.second); }
		};
	}
	/** @endcond */

	/**
	 * Convenient manager of OpenGL resources.
	 *
	 * It is highly recommended that you call collectGarbage() periodically (e.g. once per frame)
	 * so that resource manager could cleanup internal structures. Not calling this method will
	 * result in negligible memory leaks.
	 *
	 * In this implementation resource manager does not cache resources in any way. Resources are
	 * kept "alive" only while there is at least one ResourcePtr pointing to it.
	 *
	 * Custom caching could be implemented on top of this class by subclassing it.
	 */
	class ResourceManager
	{
	public:
		/**
		 * Constructor.
		 * @param loader Custom loader for resources (optional).
		 */
		ResourceManager(::Resource::Loader & loader = ::Resource::Loader::standard());

		/** Destructor. */
		virtual ~ResourceManager();

		/** Destroys all resources managed by the resource manager. */
		void destroyAllResources();

		/**
		 * Cleans up internal storage.
		 * In default implementation this method cleans up internal tables from expired weak pointers.
		 * This method could be overriden in child classes that implement caching of resources.
		 */
		virtual void collectGarbage();

		/**
		 * Creates new texture.
		 * This method always creates a new texture, even if there is one with the same name in the resource
		 * manager. Created texture is not registered within a manager.
		 * @param name Name of the texture (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the texture.
		 */
		TexturePtr createTexture(const std::string & name = m_DefaultTextureName);

		/**
		 * Loads texture with the specified name.
		 * This method does not load a texture if it has already been loaded; in this case it returns
		 * the cached texture.
		 * @param name Name of the texture.
		 * @return Pointer to the texture.
		 */
		TexturePtr getTexture(const std::string & name);

		/**
		 * Creates new shader.
		 * This method always creates a new shader, even if there is one with the same name in the resource
		 * manager. Created shader is not registered within a manager.
		 * @param type Type of the shader. Could be GL::VERTEX_SHADER or GL::FRAGMENT_SHADER.
		 * @param name Name of the shader (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the shader.
		 */
		ShaderPtr createShader(Enum type, const std::string & name = m_DefaultShaderName);

		/**
		 * Loads shader with the specified name.
		 * This method does not load a shader if it has already been loaded; in this case it returns
		 * the cached shader.
		 * @param type Type of the shader. Could be GL::VERTEX_SHADER or GL::FRAGMENT_SHADER.
		 * @param name Name of the shader.
		 * @return Pointer to the shader.
		 */
		ShaderPtr getShader(Enum type, const std::string & name);

		/**
		 * Creates new program.
		 * This method always creates a new program, even if there is one with the same name in the resource
		 * manager. Created program is not registered within a manager.
		 * @param name Name of the program (optional). This is the name that will be returned by
		 * GL::Resource::name().
		 * @return Pointer to the program.
		 */
		ProgramPtr createProgram(const std::string & name = m_DefaultProgramName);

		/**
		 * Loads program with the specified name.
		 * This method does not load a program if it has already been loaded; in this case it returns
		 * the cached program.
		 * @param name Name of the program.
		 * @return Pointer to the program.
		 */
		ProgramPtr getProgram(const std::string & name);

	private:
		static const std::string m_DefaultTextureName;
		static const std::string m_DefaultShaderName;
		static const std::string m_DefaultProgramName;

		::Resource::Loader * m_ResourceLoader;
		std::vector<ResourceWeakPtr> m_AllResources;
		std::unordered_map<std::string, TextureWeakPtr> m_Textures;
		std::unordered_map<Internal::ShaderMapKey, ShaderWeakPtr, Internal::ShaderMapKeyHash> m_Shaders;
		std::unordered_map<std::string, ProgramWeakPtr> m_Programs;

		template <class T> void collectGarbageIn(T & collection);
		template <class T, class P, class M, class K>
			std::shared_ptr<T> getResource(M & map, const K & key, bool * isNew);

		ResourceManager(const ResourceManager &) = delete;
		ResourceManager & operator=(const ResourceManager &) = delete;

		friend class Shader;
		friend class Program;
		friend class GLTexture;
	};

	/** Strong pointer to the resource manager. */
	typedef std::shared_ptr<ResourceManager> ResourceManagerPtr;
}

#endif
