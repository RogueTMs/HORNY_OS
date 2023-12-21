#include "kernel_panic.h"
#include "handlers.h"
#include "vga_funcs.h"
#include "pics.h"
#include "console.h"

static u32 counter = 0;

extern console cons;
extern void* processes[4];
extern u32 stack_ptrs[4];
extern u32 eips[4];
extern console consoles[4];

void create_context(void* ptr, u32 size, u32 eip) {
    context* ctx = ptr + size - sizeof(context);
    ctx->edi = 0;
    ctx->esi = 0;
    ctx->ebp = 0;
    ctx->esp = 0; 
    ctx->ebx = 0;
    ctx->edx = 0;
    ctx->ecx = 0;
    ctx->eax = 0;
    ctx->gs = 0;
    ctx->p1 = 0;
    ctx->fs = 0;
    ctx->p2 = 0;
    ctx->es = 0;
    ctx->p3 = 0;
    ctx->ds = 0;
    ctx->p4 = 0;
    ctx->vector = 0;
    ctx->errorCode = 0;
    ctx->eip = eip;
    ctx->cs = 0;
    ctx->p5 = 0;
    ctx->eflags = 0;
    ctx->esp_1 = 0;
    ctx->ss = 0;
}


void panic_handler(context* ctx) {
    switch (ctx->vector) {
        case 0x20:
            timer_handler(ctx);
            outb(0x20, 0x20);
            break;
        case 0x69:
            print_interrupt(ctx);
            break;
        default:
            default_handler(ctx);
            break;
    }
}


void default_handler(context* ctx) {
    // asm("cli");
    kernel_panic("Kernel panic: unhadled interrupt %x. Context:\n\
    EAX = %x ECX = %x EDX = %x EBX = %x\n\
    ESP = %x EBP = %x ESI = %x EDI = %x\n\
    DS = %x ES = %x FS = %x GS = %x\n\
    CS = %x SS = %x EIP = %x\n\
    EFLAGS (interrupted) = %x error code = %x", ctx->vector, ctx->eax, ctx->ecx, ctx->edx, ctx->ebx, ctx->esp, ctx->ebp, ctx->esi, ctx->edi, ctx->ds, ctx->es, ctx->fs, ctx->gs, ctx->cs,\
    ctx->ss, ctx->eip, ctx->eflags, ctx->errorCode);
//    asm("sti");
}

void print_interrupt(context* ctx) {
    char* s = (char*) ctx->eax;
    console_print(consoles + counter, s);
}

void timer_handler(context* ctx) {
    stack_ptrs[counter] = (u32) ctx;
    eips[counter] = ctx->eip;
    counter = (counter + 1) % 4;
    set_esp(stack_ptrs[counter], eips[counter]);
}