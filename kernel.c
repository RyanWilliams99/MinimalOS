/*
 * Desc: Minimal OS, to show how to boot an x86 machine.
 */
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
/* Hardware text mode color constants. */
enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};
 
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color) {
  uint16_t c16 = c;
  uint16_t color16 = color;
  return c16 | color16 << 8;
}
 
size_t strlen(const char* str) {
  size_t ret = 0;
  while ( str[ret] != 0 )
    ret++;
  return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize() {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = make_vgaentry(' ', terminal_color);
    }
  }
}
 
void terminal_setcolor(uint8_t color) {
  terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c) {
    if(c == 10)
    {
        terminal_row = terminal_row + 1;
        terminal_column = 0;
    }
    else
    {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_row = 0;
            }
        }
    }
}
 
void terminal_writestring(const char* data) {
  size_t datalen = strlen(data);
  for (size_t i = 0; i < datalen; i++){
      terminal_putchar(data[i]);
  }

}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
  /* Initialize terminal interface */
  terminal_initialize();
  
  /* Since there is no support for newlines in terminal_putchar
   * yet, '\n' will produce some VGA specific character instead.
   * This is normal.
   */
    terminal_setcolor(COLOR_RED);
    terminal_writestring("Hello00, kernel World!\n");
    terminal_setcolor(COLOR_WHITE);
    terminal_writestring("Hello01, kernel World!\n");
    terminal_writestring("Hello02, kernel World!\n");
    terminal_writestring("Hello03, kernel World!\n");
    terminal_writestring("Hello04, kernel World!\n");
    terminal_writestring("Hello05, kernel World!\n");
    terminal_writestring("Hello06, kernel World!\n");
    terminal_setcolor(COLOR_BLUE);
    terminal_writestring("Hello07, kernel World!\n");
    terminal_writestring("Hello08, kernel World!\n");
    terminal_writestring("Hello09, kernel World!\n");
    terminal_writestring("Hello10, kernel World!\n");
    terminal_writestring("Hello11, kernel World!\n");
    terminal_writestring("Hello12, kernel World!\n");
    terminal_writestring("Hello13, kernel World!\n");
    terminal_writestring("Hello14, kernel World!\n");
    terminal_writestring("Hello15, kernel World!\n");
    terminal_writestring("Hello16, kernel World!\n");
    terminal_writestring("Hello17, kernel World!\n");
    terminal_writestring("Hello18, kernel World!\n");
    terminal_writestring("Hello19, kernel World!\n");
    terminal_writestring("Hello20, kernel World!\n");
    terminal_writestring("Hello21, kernel World!\n");
    terminal_writestring("Hello22, kernel World!\n");
    terminal_writestring("Hello23, kernel World!\n");
    terminal_writestring("Hello24, kernel World!\n");
    terminal_setcolor(COLOR_GREEN);
    terminal_writestring("Hello25, kernel World!\n");
    terminal_writestring("Hello26, kernel World!\n");
    terminal_writestring("Hello27, kernel World!\n");
    terminal_writestring("Hello28, kernel World!\n");
    terminal_writestring("Hello29, kernel World!\n");

}
