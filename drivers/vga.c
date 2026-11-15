// vga.c
#include <stdint.h>
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
int row = 0, col = 0;

void print_char(char c) {
    vga_buffer[row * 80 + col] = (uint16_t)c | 0x0F00;
    col++;
    if (col >= 80) { col = 0; row++; }
}

void print_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) print_char(str[i]);
}
