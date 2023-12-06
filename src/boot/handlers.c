#include "kernel_panic.h"
#include "handlers.h"
#include "vga_funcs.h"

static u32 counter = 0;


void default_handler(u32 edi, u32 esi, u32 ebp, u32 esp, u32 ebx, u32 edx, u32 ecx, u32 eax, u16 gs, u16 fs, \
                     u16 es, u16 ds, u32 vector, u32 errorCode, u32 eip, u16 cs, u32 eflags, u32 process_esp, u16 ss) {
    kernel_panic("Kernel panic: unhadled interrupt %d. Context:\n\
  EAX = %d ECX = %d EDX = %d EBX = %d\n\
  ESP = %d EBP = %d ESI = %d EDI = %d\n\
  DS = %d ES = %d FS = %d GS = %d\n\
  CS = %d SS = %d EIP = %d\n\
  EFLAGS (interrupted) = %d error code = %d", vector, eax, ecx, edx, ebx, esp, ebp, esi, edi, ds, es, fs, gs, cs, ss, eip,\
    eflags, errorCode);
}

void timer_interrupt(u32 edi, u32 esi, u32 ebp, u32 esp, u32 ebx, u32 edx, u32 ecx, u32 eax, u16 gs, u16 fs, u16 es, u16 ds,\
                     u32 vector, u32 errorCode, u32 eip, u16 cs, u32 eflags, u32 process_esp, u16 ss) {
    init_printer();
    print("%d ", counter++);
}