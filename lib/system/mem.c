/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

void *memset(void *bufptr, uint8_t value, size_t size)
{
	uint8_t *buf = (uint8_t *)bufptr;
	for(size_t i = 0; i < size; i++)
		buf[i] = value;
	return bufptr;
}

void *memsetw(void *bufptr, uint16_t value, size_t size)
{
	uint16_t *buf = (uint16_t *)bufptr;
	for(size_t i = 0; i < size; i++)
		buf[i] = value;
	return bufptr;
}

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size)
{
	unsigned char * dst = (unsigned char *)dstptr;
	const unsigned char * src = (const unsigned char *)srcptr;
	for(size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

