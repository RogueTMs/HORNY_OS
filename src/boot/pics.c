#include "pics.h"

#define PIC1 0x20 
#define PIC2 0xA0

#define ICW1 0x11
#define ICW2_MASTER 0x20
#define ICW2_SLAVE 0x28
#define ICW3_MASTER 0b00000100
#define ICW3_SLAVE 0b000000010
#define ICW4 0x01




void init_pics() {
    outb(PIC1, ICW1);
    outb(0x80, 0);
    outb(PIC2, ICW1);
    outb(0x80, 0);

    outb(PIC1 + 1, ICW2_MASTER);
    outb(0x80, 0); 
    outb(PIC2 + 1, ICW2_SLAVE);
    outb(0x80, 0);

    outb(PIC1 + 1, 4);
    outb(0x80, 0);
    outb(PIC2 + 1, 2);
    outb(0x80, 0);

    outb(PIC1 + 1, ICW4);
    outb(0x80, 0);
    outb(PIC2 + 1, ICW4);
    outb(0x80, 0);

    outb(PIC1 + 1, 0b11111011);
    outb(PIC2 + 1, 0xFF);
}