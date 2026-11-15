#include <string.h>
extern void print_string(const char*);
extern char* load_file(const char* filename);
extern void render_html(const char* html);

void launch_gui() {
    print_string("[NanoGUI] Loading Desktop...\n");
    char* html = load_file("index.html");
    if (html) {
        render_html(html); // render desktop from HTML
    } else {
        print_string("Desktop file not found!\n");
    }
}
