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
#include "util.h"

bool projectPointToLine(vec2 * pResult, const vec2 & lineStart, const vec2 & lineEnd, const vec2 & point)
{
	float x = point.x();
	float y = point.y();

	float x1 = lineStart.x();
	float y1 = lineStart.y();

	float x2 = lineEnd.x();
	float y2 = lineEnd.y();

	float dx = x2 - x1;
	float dy = y2 - y1;

	float t = ((x - x1) * dx + (y - y1) * dy) / (dx * dx + dy * dy);
	if (t < 0.0f || t > 1.0f)
		return false;

	x = x1 + t * dx;
	y = y1 + t * dy;
	*pResult = vec2(x, y);

	return true;
}

bool pointIsOnRay(const vec2 & point, const vec2 & rayStart, const vec2 & rayDirection)
{
	float x = point.x();
	float y = point.y();

	float x1 = rayStart.x();
	float y1 = rayStart.y();

	vec2 rayEnd = rayStart + rayDirection;
	float x2 = rayEnd.x();
	float y2 = rayEnd.y();

	float dx = x2 - x1;
	float dy = y2 - y1;

	float t = ((x - x1) * dx + (y - y1) * dy) / (dx * dx + dy * dy);
	return t >= 0.0f;
}

float pointPositionOnSegment(const vec2 & segmentStart, const vec2 & segmentEnd, const vec2 & point)
{
	float x = point.x();
	float y = point.y();

	float x1 = segmentStart.x();
	float y1 = segmentStart.y();

	float x2 = segmentEnd.x();
	float y2 = segmentEnd.y();

	float dx = x2 - x1;
	float dy = y2 - y1;

	return ((x - x1) * dx + (y - y1) * dy) / (dx * dx + dy * dy);
}
