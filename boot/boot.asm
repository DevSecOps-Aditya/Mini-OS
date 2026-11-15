BITS 16
ORG 0x7C00

start:
    mov si, msg
    call print_string
    jmp 0x1000        ; jump to kernel

print_string:
    lodsb
    cmp al, 0
    je done
    mov ah, 0x0E
    int 0x10
    jmp print_string
done:
    ret

msg db "Booting Nano OS...",0

times 510-($-$$) db 0
dw 0xAA55
