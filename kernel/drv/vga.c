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
#include <drv/vga.h>
#include <string.h>
#include <system.h>

uint16_t index(uint8_t, uint8_t);
void update_cursor();
void scroll();

uint16_t *VGA = (uint16_t *)0xB8000;
const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

uint8_t colour = 0;

uint8_t cursor_x;
uint8_t cursor_y;

void vga_init()
{
	cursor_x = 0;
	cursor_y = 0;
	colour = (VGA_BLACK << 8) | VGA_LIGHT_GREY;
	vga_clear();
}

void vga_clear()
{
	uint16_t blank = 0x20 | (colour << 8);
	
	for(size_t i = 0; i < VGA_HEIGHT; i++)
	{
		memsetw((void *)(VGA + i * VGA_WIDTH), blank, VGA_WIDTH);
	}
	
	cursor_x = 0;
	cursor_y = 0;
	
	update_cursor();
}

void update_cursor()
{
	unsigned tmp = index(cursor_x, cursor_y);
	
	outportb(0x3D4, 14);
	outportb(0x3D5, tmp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, tmp);
}

void vga_putchar(uint8_t c)
{
	if(c == 0x08)
	{
		if(cursor_x != 0) cursor_x--;
	}
	else if(c == 0x09)
	{
		cursor_x = (cursor_x + 4) & ~3;
	}
	else if(c == '\r')
	{
		cursor_x = 0;
	}
	else if(c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	else if(c >= ' ')
	{
		uint16_t *ptr = VGA + index(cursor_x, cursor_y);
		*ptr = c | (colour << 8);
		cursor_x++;
	}
	
	if(cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y++;
	}
	
	scroll();
	update_cursor();
}

void vga_putstring(const char *str)
{
	size_t len = strlen(str);
	for(size_t i = 0; i < len; i++)
	{
		vga_putchar(str[i]);
	}
}

void vga_set_colour(uint8_t fg, uint8_t bg)
{
	colour = (bg << 4) | (fg & 0x0F);
}

void scroll()
{
	uint16_t blank = 0x20 | (colour << 8);
	
	if(cursor_y >= 25)
	{
		uint16_t tmp = cursor_y - 25 + 1;
		
		memcpy(VGA, VGA + tmp * 80, (25 - tmp) * 80 * 2);
		
		memsetw(VGA + (25 - tmp) * 80, blank, 80);
		
		cursor_y = 25 - 1;
	}
}

uint16_t index(uint8_t x, uint8_t y)
{
	return y * 80 + x;
}

