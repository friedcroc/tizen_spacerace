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
#ifndef __9efab2399c7c560b34de477b9aa0a465__
#define __9efab2399c7c560b34de477b9aa0a465__

#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif

#if defined(__GNUC__) || defined(__clang__)
 #define LIKELY(x) (__builtin_expect(!!(x), 1))
 #define UNLIKELY(x) (__builtin_expect(!!(x), 0))
 #define NOTHROW __attribute__((nothrow))
 #define FORCEINLINE __attribute__((always_inline))
 #define NORETURN __attribute__((noreturn))
 #define NOINLINE __attribute__((noinline))
 #define FPURE __attribute__((pure))
 #define FCONST __attribute__((const))
#elif defined(_MSC_VER)
 #define LIKELY(x) (x)
 #define UNLIKELY(x) (x)
 #define NOTHROW __declspec(nothrow)
 #define FORCEINLINE __forceinline
 #define NORETURN __declspec(noreturn)
 #define NOINLINE __declspec(noinline)
 #define FPURE
 #define FCONST
#else
 #define LIKELY(x) (x)
 #define UNLIKELY(x) (x)
 #define NOTHROW
 #define FORCEINLINE
 #define NORETURN
 #define NOINLINE
 #define FPURE
 #define FCONST
#endif

#ifdef _WIN32
 #define DLLIMPORT __declspec(dllimport)
 #define DLLEXPORT __declspec(dllexport)
#elif defined(__GNUC__) || defined(__clang__)
 #define DLLIMPORT __attribute__((visibility("default")))
 #define DLLEXPORT __attribute__((visibility("default")))
#else
 #define DLLIMPORT
 #define DLLEXPORT
#endif

#endif
