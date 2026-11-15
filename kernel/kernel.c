#include <stdint.h>
extern void init_drivers();
extern void launch_gui();

void kernel_main() {
    init_drivers();
    launch_gui(); // desktop manager
}
