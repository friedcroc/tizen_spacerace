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
#ifndef __32269a077ca0af3de2fc3fff927880bb__
#define __32269a077ca0af3de2fc3fff927880bb__

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>

#ifdef _WIN32
 #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
 #endif
 #include <windows.h>
#endif

#ifdef FALSE
 #undef FALSE
#endif

#ifdef TRUE
 #undef TRUE
#endif

#ifdef NO_ERROR
 #undef NO_ERROR
#endif

namespace GL
{
	class ResourceManager;

	enum Enum
	{
		FALSE = 0,
		TRUE = 1,
		ZERO = 0,
		ONE = 1,
		NO_ERROR = 0,
		NONE = 0,
		POINTS = 0x0000,
		LINES = 0x0001,
		#define GL_CONSTANT_(X, Y) X = Y,
		#include "gl_constants.h"
		#undef GL_CONSTANT_
		BLEND_EQUATION = BLEND_EQUATION_RGB
	};

	typedef void Void;
	typedef char Char;
	typedef unsigned char Boolean;
	typedef unsigned int Bitfield;
	typedef int8_t Byte;
	typedef uint8_t UByte;
	typedef short Short;
	typedef int Int;
	typedef int Sizei;
	typedef unsigned short UShort;
	typedef unsigned int UInt;
	typedef int32_t Fixed;
	typedef float Float;
	typedef float Clampf;
	typedef ptrdiff_t Intptr;
	typedef ptrdiff_t Sizeiptr;

	void init();

	void activeTexture(Enum texture);
	void attachShader(UInt program, UInt shader);
	void bindAttribLocation(UInt program, UInt index, const Char * name);
	void bindBuffer(Enum target, UInt buffer);
	void bindFramebuffer(Enum target, UInt framebuffer);
	void bindRenderbuffer(Enum target, UInt renderbuffer);
	void bindTexture(Enum target, UInt texture);
	void blendColor(Clampf red, Clampf green, Clampf blue, Clampf alpha);
	void blendEquation(Enum mode);
	void blendEquationSeparate(Enum modeRGB, Enum modeAlpha);
	void blendFunc(Enum sfactor, Enum dfactor);
	void blendFuncSeparate(Enum srcRGB, Enum dstRGB, Enum srcAlpha, Enum dstAlpha);
	void bufferData(Enum target, Sizeiptr size, const void * data, Enum usage);
	void bufferSubData(Enum target, Intptr offset, Sizeiptr size, const void * data);
	Enum checkFramebufferStatus(Enum target);
	void clear(Bitfield mask);
	void clearColor(Clampf red, Clampf green, Clampf blue, Clampf alpha);
	void clearDepthf(Clampf depth);
	void clearStencil(Int s);
	void colorMask(Boolean red, Boolean green, Boolean blue, Boolean alpha);
	void compileShader(UInt shader);
	void compressedTexImage2D(Enum target, Int level, Enum internalformat, Sizei width, Sizei height,
		Int border, Sizei imageSize, const void * data);
	void compressedTexSubImage2D(Enum target, Int level, Int xoffset, Int yoffset, Sizei width,
		Sizei height, Enum format, Sizei imageSize, const void * data);
	void copyTexImage2D(Enum target, Int level, Enum intfmt, Int x, Int y, Sizei w, Sizei h, Int border);
	void copyTexSubImage2D(Enum target, Int level, Int xoff, Int yoff, Int x, Int y, Sizei w, Sizei h);
	UInt createProgram();
	UInt createShader(Enum type);
	void cullFace(Enum mode);
	void deleteBuffers(Sizei n, const UInt * buffers);
	void deleteFramebuffers(Sizei n, const UInt * framebuffers);
	void deleteProgram(UInt program);
	void deleteRenderbuffers(Sizei n, const UInt * renderbuffers);
	void deleteShader(UInt shader);
	void deleteTextures(Sizei n, const UInt * textures);
	void depthFunc(Enum func);
	void depthMask(Boolean flag);
	void depthRangef(Clampf zNear, Clampf zFar);
	void detachShader(UInt program, UInt shader);
	void disable(Enum cap);
	void disableVertexAttribArray(UInt index);
	void drawArrays(Enum mode, Int first, Sizei count);
	void drawElements(Enum mode, Sizei count, Enum type, const void * indices);
	void enable(Enum cap);
	void enableVertexAttribArray(UInt index);
	void finish();
	void flush();
	void framebufferRenderbuffer(Enum target, Enum attachment, Enum renderbuffertarget, UInt renderbuffer);
	void framebufferTexture2D(Enum target, Enum attachment, Enum textarget, UInt texture, Int level);
	void frontFace(Enum mode);
	void genBuffers(Sizei n, UInt * buffers);
	void generateMipmap(Enum target);
	void genFramebuffers(Sizei n, UInt * framebuffers);
	void genRenderbuffers(Sizei n, UInt * renderbuffers);
	void genTextures(Sizei n, UInt * textures);
	void getActiveAttrib(UInt prog, UInt idx, Sizei bufsz, Sizei * len, Int * sz, Enum * type, Char * name);
	void getActiveUniform(UInt prog, UInt idx, Sizei bufsz, Sizei * len, Int * sz, Enum * type, Char * name);
	void getAttachedShaders(UInt program, Sizei maxcount, Sizei * count, UInt * shaders);
	int getAttribLocation(UInt program, const Char * name);
	void getBooleanv(Enum pname, Boolean * params);
	void getBufferParameteriv(Enum target, Enum pname, Int * params);
	Enum getError();
	void getFloatv(Enum pname, Float * params);
	void getFramebufferAttachmentParameteriv(Enum target, Enum attachment, Enum pname, Int * params);
	void getIntegerv(Enum pname, Int * params);
	void getProgramiv(UInt program, Enum pname, Int * params);
	void getProgramInfoLog(UInt program, Sizei bufsize, Sizei * length, Char * infolog);
	void getRenderbufferParameteriv(Enum target, Enum pname, Int * params);
	void getShaderiv(UInt shader, Enum pname, Int * params);
	void getShaderInfoLog(UInt shader, Sizei bufsize, Sizei * length, Char * infolog);
	void getShaderPrecisionFormat(Enum shadertype, Enum precisiontype, Int * range, Int * precision);
	void getShaderSource(UInt shader, Sizei bufsize, Sizei * length, Char * source);
	const Char * getString(Enum name);
	void getTexParameterfv(Enum target, Enum pname, Float * params);
	void getTexParameteriv(Enum target, Enum pname, Int * params);
	void getUniformfv(UInt program, Int location, Float * params);
	void getUniformiv(UInt program, Int location, Int * params);
	int getUniformLocation(UInt program, const Char * name);
	void getVertexAttribfv(UInt index, Enum pname, Float * params);
	void getVertexAttribiv(UInt index, Enum pname, Int * params);
	void getVertexAttribPointerv(UInt index, Enum pname, void ** pointer);
	void hint(Enum target, Enum mode);
	Boolean isBuffer(UInt buffer);
	Boolean isEnabled(Enum cap);
	Boolean isFramebuffer(UInt framebuffer);
	Boolean isProgram(UInt program);
	Boolean isRenderbuffer(UInt renderbuffer);
	Boolean isShader(UInt shader);
	Boolean isTexture(UInt texture);
	void lineWidth(Float width);
	void linkProgram(UInt program);
	void pixelStorei(Enum pname, Int param);
	void polygonOffset(Float factor, Float units);
	void readPixels(Int x, Int y, Sizei width, Sizei height, Enum format, Enum type, void * pixels);
	void releaseShaderCompiler();
	void renderbufferStorage(Enum target, Enum internalformat, Sizei width, Sizei height);
	void sampleCoverage(Clampf value, Boolean invert);
	void scissor(Int x, Int y, Sizei width, Sizei height);
	void shaderBinary(Sizei n, const UInt * shaders, Enum binaryformat, const void * binary, Sizei length);
	void shaderSource(UInt shader, Sizei count, const Char ** string, const Int * lenth);
	void stencilFunc(Enum func, Int ref, UInt mask);
	void stencilFuncSeparate(Enum face, Enum func, Int ref, UInt mask);
	void stencilMask(UInt mask);
	void stencilMaskSeparate(Enum face, UInt mask);
	void stencilOp(Enum fail, Enum zfail, Enum zpass);
	void stencilOpSeparate(Enum face, Enum fail, Enum zfail, Enum zpass);
	void texImage2D(Enum target, Int level, Int internalformat, Sizei width, Sizei height, Int border,
		Enum format, Enum type, const void * pixels);
	void texParameterf(Enum target, Enum pname, Float param);
	void texParameterfv(Enum target, Enum pname, const Float * params);
	void texParameteri(Enum target, Enum pname, Int param);
	void texParameteriv(Enum target, Enum pname, const Int * params);
	void texSubImage2D(Enum target, Int level, Int xoffset, Int yoffset, Sizei width, Sizei height,
		Enum format, Enum type, const void * pixels);
	void uniform1f(Int location, Float x);
	void uniform1fv(Int location, Sizei count, const Float * v);
	void uniform1i(Int location, Int x);
	void uniform1iv(Int location, Sizei count, const Int * v);
	void uniform2f(Int location, Float x, Float y);
	void uniform2fv(Int location, Sizei count, const Float * v);
	void uniform2i(Int location, Int x, Int y);
	void uniform2iv(Int location, Sizei count, const Int * v);
	void uniform3f(Int location, Float x, Float y, Float z);
	void uniform3fv(Int location, Sizei count, const Float * v);
	void uniform3i(Int location, Int x, Int y, Int z);
	void uniform3iv(Int location, Sizei count, const Int * v);
	void uniform4f(Int location, Float x, Float y, Float z, Float w);
	void uniform4fv(Int location, Sizei count, const Float * v);
	void uniform4i(Int location, Int x, Int y, Int z, Int w);
	void uniform4iv(Int location, Sizei count, const Int * v);
	void uniformMatrix2fv(Int location, Sizei count, Boolean transpose, const Float * value);
	void uniformMatrix3fv(Int location, Sizei count, Boolean transpose, const Float * value);
	void uniformMatrix4fv(Int location, Sizei count, Boolean transpose, const Float * value);
	void useProgram(UInt program);
	void validateProgram(UInt program);
	void vertexAttrib1f(UInt indx, Float x);
	void vertexAttrib1fv(UInt indx, const Float * values);
	void vertexAttrib2f(UInt indx, Float x, Float y);
	void vertexAttrib2fv(UInt indx, const Float * values);
	void vertexAttrib3f(UInt indx, Float x, Float y, Float z);
	void vertexAttrib3fv(UInt indx, const Float * values);
	void vertexAttrib4f(UInt indx, Float x, Float y, Float z, Float w);
	void vertexAttrib4fv(UInt indx, const Float * values);
	void vertexAttribPointer(UInt indx, Int size, Enum type, Boolean norm, Sizei stride, const void * ptr);
	void viewport(Int x, Int y, Sizei width, Sizei height);

	Int getInteger(Enum param);
}

#endif
