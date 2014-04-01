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
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	FILE * f = fopen(argv[1], "rb");
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);

	char * buf = malloc(size);
	fread(buf, 1, size, f);
	fclose(f);

	char str[1024];
	sprintf(str, "%s.cpp", argv[1]);

	f = fopen(str, "w");

	sprintf(str, "%s", argv[1]);
	for (char * p = str; *p; ++p)
	{
		if (*p == '.' || *p == '-')
			*p = '_';
	}

	fprintf(f, "#include <cstddef>\n");
	fprintf(f, "extern const size_t file_%s_size = %u;\n", str, (unsigned)size);
	fprintf(f, "extern const unsigned char file_%s[] = {", str);
	for (long i = 0; i < size; i++)
	{
		if (i % 32 == 0)
			fputc('\n', f);
		fprintf(f, "0x%02X,", (unsigned char)buf[i]);
	}
	fprintf(f, "};\n");
	fclose(f);

	return 0;
}
