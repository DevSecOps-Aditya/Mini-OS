#include <string.h>
extern void print_string(const char*);

// Demo: pretend we read index.html from disk
char* load_file(const char* filename) {
    if (strcmp(filename, "index.html") == 0) {
        return "<h1>Welcome to Nano OS Desktop</h1>"
               "<p>Programs: Browser, Editor, Calc</p>";
    }
    return NULL;
}
