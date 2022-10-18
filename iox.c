/* z80ctrl (https://github.com/jblang/z80ctrl)
 * Copyright 2018 J.B. Langston
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * @file iox.c MCP21S17 convenience functions
 */

#include "iox.h"
#include "spi.h"

void iox_init(void) {
	spi_init();
}

void iox_begin(uint8_t mode, uint8_t addr) {
	SPI_PORT &= ~(1 << SS);
	spi_exchange(SPI_ADDR | mode);
	spi_exchange(addr);
}

void iox_end(void) {
	SPI_PORT |= (1 << SS);
}

uint8_t iox_read(uint8_t chipaddr, uint8_t regaddr) {
	uint8_t data;
	iox_begin(READ | (chipaddr << 1), regaddr);
	data = spi_exchange(0);
	iox_end();
	return data;
}

void iox_write(uint8_t chipaddr, uint8_t regaddr, uint8_t data) {
	iox_begin(WRITE | (chipaddr << 1), regaddr);
	spi_exchange(data);
	iox_end();
}