// keyboard.c
#include <stdint.h>
extern void print_string(const char*);

void keyboard_handler() {
    print_string("Key pressed!\n");
}

void init_drivers() {
    print_string("Drivers initialized.\n");
}
