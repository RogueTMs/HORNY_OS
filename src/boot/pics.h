#pragma once

typedef char byte;
typedef unsigned short u16;

void init_pics();
byte inb(u16 port);
void outb(u16 port, byte data);