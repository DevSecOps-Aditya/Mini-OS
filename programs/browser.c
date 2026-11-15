#include <string.h>
extern void print_string(const char*);

void render_html(const char* html) {
    if (strstr(html, "<h1")) {
        print_string("[DESKTOP HEADER] ");
    }
    if (strstr(html, "<p")) {
        print_string("[DESKTOP TEXT] ");
    }
    if (strstr(html, "color:red")) {
        print_string("[RED TEXT] ");
    }
}
