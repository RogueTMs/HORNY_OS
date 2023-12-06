#include "kernel_panic.h"
#include "handlers.h"
#include "vga_funcs.h"

static u32 counter = 0;




void panic_handler(context* ctx) {
    switch (ctx->vector) {
        case 0x20:
            timer_interrupt(ctx);
            break;
        default:
            default_handler(ctx);
            break;
    }
}


void default_handler(context* ctx) {
    kernel_panic("Kernel panic: unhadled interrupt %x. Context:\n\
  EAX = %x ECX = %x EDX = %x EBX = %x\n\
  ESP = %x EBP = %x ESI = %x EDI = %x\n\
  DS = %x ES = %x FS = %x GS = %x\n\
  CS = %x SS = %x EIP = %x\n\
  EFLAGS (interrupted) = %x error code = %x", ctx->vector, ctx->eax, ctx->ecx, ctx->edx, ctx->ebx, ctx->esp, ctx->ebp, ctx->esi, ctx->edi, ctx->ds, ctx->es, ctx->fs, ctx->gs, ctx->cs,\
   ctx->ss, ctx->eip, ctx->eflags, ctx->errorCode);
}

void timer_interrupt(context* ctx) {
    print("%d ", counter++);
}