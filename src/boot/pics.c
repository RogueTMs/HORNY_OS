#include "pics.h"

#define PIC1 0x20 
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01




void init_pics() {
    outb(PIC1, ICW1);
    outb(0x80, 0);
    outb(PIC2, ICW1);
    outb(0x80, 0);

    outb(PIC1 + 1, 0x20);
    outb(0x80, 0); 
    outb(PIC2 + 1, 0x28);
    outb(0x80, 0);

    outb(PIC1 + 1, 4);
    outb(0x80, 0);
    outb(PIC2 + 1, 2);
    outb(0x80, 0);

    outb(PIC1 + 1, ICW4);
    outb(0x80, 0);
    outb(PIC2 + 1, ICW4);
    outb(0x80, 0);

    outb(PIC1 + 1, 0b11111001);
    outb(PIC2 + 1, 0xFF);
}