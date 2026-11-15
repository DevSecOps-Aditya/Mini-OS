all: nanoos.img

# --- Bootloader ---
boot.bin: boot/boot.asm
    nasm -f bin boot/boot.asm -o boot.bin

# --- Kernel ---
kernel.o: kernel/kernel.c
    gcc -ffreestanding -c kernel/kernel.c -o kernel.o

# --- Drivers ---
drivers.o: drivers/keyboard.c drivers/vga.c
    gcc -ffreestanding -c drivers/keyboard.c -o keyboard.o
    gcc -ffreestanding -c drivers/vga.c -o vga.o

# --- File System ---
fs.o: fs/nano_fs.c
    gcc -ffreestanding -c fs/nano_fs.c -o fs.o

# --- GUI ---
gui.o: gui/window.c
    gcc -ffreestanding -c gui/window.c -o gui.o

# --- Programs (Browser in C) ---
browser.o: programs/browser.c
    gcc -ffreestanding -c programs/browser.c -o browser.o

# --- Programs (NanoBrowser with V8 in C++) ---
nano_browser.o: programs/nano_browser.cpp
    g++ -std=c++17 -ffreestanding -c programs/nano_browser.cpp -o nano_browser.o \
        -I/path/to/v8/include -L/path/to/v8/lib -lv8 -lv8_libplatform

# --- Link everything into kernel.bin ---
kernel.bin: kernel.o keyboard.o vga.o fs.o gui.o browser.o nano_browser.o
    ld -Ttext 0x1000 --oformat binary \
       kernel.o keyboard.o vga.o fs.o gui.o browser.o nano_browser.o -o kernel.bin

# --- Build OS image ---
nanoos.img: boot.bin kernel.bin
    cat boot.bin kernel.bin > nanoos.img

# --- Run in QEMU ---
run: nanoos.img
    qemu-system-x86_64 -drive format=raw,file=nanoos.img
