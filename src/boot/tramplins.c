#include "kernel_alloc.h"
#include "tramplins.h"
#include "handlers.h"

#pragma pack(push, 1)
typedef struct {
    u16 offset_1;
    u16 selector;
    u8 zeros;
    u8 flags;
    u16 offset_2;
} GateDescriptor;

typedef struct {
    u16 idt_size;
    u32 idt_address;
} DIDT;
#pragma pack(pop)

#define IDT_SIZE 256

void tramplin_00();
void tramplin_01();
void tramplin_02();
void tramplin_03();
void tramplin_04();
void tramplin_05();
void tramplin_06();
void tramplin_07();
void tramplin_08();
void tramplin_09();
void tramplin_0a();
void tramplin_0b();
void tramplin_0c();
void tramplin_0d();
void tramplin_0e();
void tramplin_0f();
void tramplin_10();
void tramplin_11();
void tramplin_12();
void tramplin_13();
void tramplin_14();
void tramplin_15();
void tramplin_16();
void tramplin_17();
void tramplin_18();
void tramplin_19();
void tramplin_1a();
void tramplin_1b();
void tramplin_1c();
void tramplin_1d();
void tramplin_1e();
void tramplin_1f();
void tramplin_20();
void tramplin_21();
void tramplin_22();
void tramplin_23();
void tramplin_24();
void tramplin_25();
void tramplin_26();
void tramplin_27();
void tramplin_28();
void tramplin_29();
void tramplin_2a();
void tramplin_2b();
void tramplin_2c();
void tramplin_2d();
void tramplin_2e();
void tramplin_2f();
void tramplin_30();
void tramplin_31();
void tramplin_32();
void tramplin_33();
void tramplin_34();
void tramplin_35();
void tramplin_36();
void tramplin_37();
void tramplin_38();
void tramplin_39();
void tramplin_3a();
void tramplin_3b();
void tramplin_3c();
void tramplin_3d();
void tramplin_3e();
void tramplin_3f();
void tramplin_40();
void tramplin_41();
void tramplin_42();
void tramplin_43();
void tramplin_44();
void tramplin_45();
void tramplin_46();
void tramplin_47();
void tramplin_48();
void tramplin_49();
void tramplin_4a();
void tramplin_4b();
void tramplin_4c();
void tramplin_4d();
void tramplin_4e();
void tramplin_4f();
void tramplin_50();
void tramplin_51();
void tramplin_52();
void tramplin_53();
void tramplin_54();
void tramplin_55();
void tramplin_56();
void tramplin_57();
void tramplin_58();
void tramplin_59();
void tramplin_5a();
void tramplin_5b();
void tramplin_5c();
void tramplin_5d();
void tramplin_5e();
void tramplin_5f();
void tramplin_60();
void tramplin_61();
void tramplin_62();
void tramplin_63();
void tramplin_64();
void tramplin_65();
void tramplin_66();
void tramplin_67();
void tramplin_68();
void tramplin_69();
void tramplin_6a();
void tramplin_6b();
void tramplin_6c();
void tramplin_6d();
void tramplin_6e();
void tramplin_6f();
void tramplin_70();
void tramplin_71();
void tramplin_72();
void tramplin_73();
void tramplin_74();
void tramplin_75();
void tramplin_76();
void tramplin_77();
void tramplin_78();
void tramplin_79();
void tramplin_7a();
void tramplin_7b();
void tramplin_7c();
void tramplin_7d();
void tramplin_7e();
void tramplin_7f();
void tramplin_80();
void tramplin_81();
void tramplin_82();
void tramplin_83();
void tramplin_84();
void tramplin_85();
void tramplin_86();
void tramplin_87();
void tramplin_88();
void tramplin_89();
void tramplin_8a();
void tramplin_8b();
void tramplin_8c();
void tramplin_8d();
void tramplin_8e();
void tramplin_8f();
void tramplin_90();
void tramplin_91();
void tramplin_92();
void tramplin_93();
void tramplin_94();
void tramplin_95();
void tramplin_96();
void tramplin_97();
void tramplin_98();
void tramplin_99();
void tramplin_9a();
void tramplin_9b();
void tramplin_9c();
void tramplin_9d();
void tramplin_9e();
void tramplin_9f();
void tramplin_a0();
void tramplin_a1();
void tramplin_a2();
void tramplin_a3();
void tramplin_a4();
void tramplin_a5();
void tramplin_a6();
void tramplin_a7();
void tramplin_a8();
void tramplin_a9();
void tramplin_aa();
void tramplin_ab();
void tramplin_ac();
void tramplin_ad();
void tramplin_ae();
void tramplin_af();
void tramplin_b0();
void tramplin_b1();
void tramplin_b2();
void tramplin_b3();
void tramplin_b4();
void tramplin_b5();
void tramplin_b6();
void tramplin_b7();
void tramplin_b8();
void tramplin_b9();
void tramplin_ba();
void tramplin_bb();
void tramplin_bc();
void tramplin_bd();
void tramplin_be();
void tramplin_bf();
void tramplin_c0();
void tramplin_c1();
void tramplin_c2();
void tramplin_c3();
void tramplin_c4();
void tramplin_c5();
void tramplin_c6();
void tramplin_c7();
void tramplin_c8();
void tramplin_c9();
void tramplin_ca();
void tramplin_cb();
void tramplin_cc();
void tramplin_cd();
void tramplin_ce();
void tramplin_cf();
void tramplin_d0();
void tramplin_d1();
void tramplin_d2();
void tramplin_d3();
void tramplin_d4();
void tramplin_d5();
void tramplin_d6();
void tramplin_d7();
void tramplin_d8();
void tramplin_d9();
void tramplin_da();
void tramplin_db();
void tramplin_dc();
void tramplin_dd();
void tramplin_de();
void tramplin_df();
void tramplin_e0();
void tramplin_e1();
void tramplin_e2();
void tramplin_e3();
void tramplin_e4();
void tramplin_e5();
void tramplin_e6();
void tramplin_e7();
void tramplin_e8();
void tramplin_e9();
void tramplin_ea();
void tramplin_eb();
void tramplin_ec();
void tramplin_ed();
void tramplin_ee();
void tramplin_ef();
void tramplin_f0();
void tramplin_f1();
void tramplin_f2();
void tramplin_f3();
void tramplin_f4();
void tramplin_f5();
void tramplin_f6();
void tramplin_f7();
void tramplin_f8();
void tramplin_f9();
void tramplin_fa();
void tramplin_fb();
void tramplin_fc();
void tramplin_fd();
void tramplin_fe();
void tramplin_ff();
static void* tramplins[] = {tramplin_00, tramplin_01, tramplin_02, tramplin_03, tramplin_04, tramplin_05, tramplin_06, tramplin_07, tramplin_08, tramplin_09, tramplin_0a, tramplin_0b, tramplin_0c, tramplin_0d, tramplin_0e, tramplin_0f, tramplin_10, tramplin_11, tramplin_12, tramplin_13, tramplin_14, tramplin_15, tramplin_16, tramplin_17, tramplin_18, tramplin_19, tramplin_1a, tramplin_1b, tramplin_1c, tramplin_1d, tramplin_1e, tramplin_1f, tramplin_20, tramplin_21, tramplin_22, tramplin_23, tramplin_24, tramplin_25, tramplin_26, tramplin_27, tramplin_28, tramplin_29, tramplin_2a, tramplin_2b, tramplin_2c, tramplin_2d, tramplin_2e, tramplin_2f, tramplin_30, tramplin_31, tramplin_32, tramplin_33, tramplin_34, tramplin_35, tramplin_36, tramplin_37, tramplin_38, tramplin_39, tramplin_3a, tramplin_3b, tramplin_3c, tramplin_3d, tramplin_3e, tramplin_3f, tramplin_40, tramplin_41, tramplin_42, tramplin_43, tramplin_44, tramplin_45, tramplin_46, tramplin_47, tramplin_48, tramplin_49, tramplin_4a, tramplin_4b, tramplin_4c, tramplin_4d, tramplin_4e, tramplin_4f, tramplin_50, tramplin_51, tramplin_52, tramplin_53, tramplin_54, tramplin_55, tramplin_56, tramplin_57, tramplin_58, tramplin_59, tramplin_5a, tramplin_5b, tramplin_5c, tramplin_5d, tramplin_5e, tramplin_5f, tramplin_60, tramplin_61, tramplin_62, tramplin_63, tramplin_64, tramplin_65, tramplin_66, tramplin_67, tramplin_68, tramplin_69, tramplin_6a, tramplin_6b, tramplin_6c, tramplin_6d, tramplin_6e, tramplin_6f, tramplin_70, tramplin_71, tramplin_72, tramplin_73, tramplin_74, tramplin_75, tramplin_76, tramplin_77, tramplin_78, tramplin_79, tramplin_7a, tramplin_7b, tramplin_7c, tramplin_7d, tramplin_7e, tramplin_7f, tramplin_80, tramplin_81, tramplin_82, tramplin_83, tramplin_84, tramplin_85, tramplin_86, tramplin_87, tramplin_88, tramplin_89, tramplin_8a, tramplin_8b, tramplin_8c, tramplin_8d, tramplin_8e, tramplin_8f, tramplin_90, tramplin_91, tramplin_92, tramplin_93, tramplin_94, tramplin_95, tramplin_96, tramplin_97, tramplin_98, tramplin_99, tramplin_9a, tramplin_9b, tramplin_9c, tramplin_9d, tramplin_9e, tramplin_9f, tramplin_a0, tramplin_a1, tramplin_a2, tramplin_a3, tramplin_a4, tramplin_a5, tramplin_a6, tramplin_a7, tramplin_a8, tramplin_a9, tramplin_aa, tramplin_ab, tramplin_ac, tramplin_ad, tramplin_ae, tramplin_af, tramplin_b0, tramplin_b1, tramplin_b2, tramplin_b3, tramplin_b4, tramplin_b5, tramplin_b6, tramplin_b7, tramplin_b8, tramplin_b9, tramplin_ba, tramplin_bb, tramplin_bc, tramplin_bd, tramplin_be, tramplin_bf, tramplin_c0, tramplin_c1, tramplin_c2, tramplin_c3, tramplin_c4, tramplin_c5, tramplin_c6, tramplin_c7, tramplin_c8, tramplin_c9, tramplin_ca, tramplin_cb, tramplin_cc, tramplin_cd, tramplin_ce, tramplin_cf, tramplin_d0, tramplin_d1, tramplin_d2, tramplin_d3, tramplin_d4, tramplin_d5, tramplin_d6, tramplin_d7, tramplin_d8, tramplin_d9, tramplin_da, tramplin_db, tramplin_dc, tramplin_dd, tramplin_de, tramplin_df, tramplin_e0, tramplin_e1, tramplin_e2, tramplin_e3, tramplin_e4, tramplin_e5, tramplin_e6, tramplin_e7, tramplin_e8, tramplin_e9, tramplin_ea, tramplin_eb, tramplin_ec, tramplin_ed, tramplin_ee, tramplin_ef, tramplin_f0, tramplin_f1, tramplin_f2, tramplin_f3, tramplin_f4, tramplin_f5, tramplin_f6, tramplin_f7, tramplin_f8, tramplin_f9, tramplin_fa, tramplin_fb, tramplin_fc, tramplin_fd, tramplin_fe, tramplin_ff};


static void init_(DIDT* didt, u32 size, void* address) {
    didt->idt_size = size;
    didt->idt_address = (u32) address;
}


void init_IDT(){

    GateDescriptor* idt = (GateDescriptor*) kernel_malloc(sizeof(GateDescriptor) * IDT_SIZE);


    for (u32 vector = 0; vector < IDT_SIZE; vector++) {
        byte* handler = tramplins[vector];
        u16 low_16_bits = (u16) ((u32) handler & 0xFFFF);
        u16 high_16_bits = (u16) ((u32) handler >> 16);
        GateDescriptor tmp;
        tmp.offset_1 = low_16_bits;
        tmp.selector = 0x8;
        if (vector <= 32) {
            tmp.flags = 0b10001111;
        } else {
            tmp.flags = 0b10001110;
        }
        tmp.zeros = 0;
        tmp.offset_2 = high_16_bits;
        idt[vector] = tmp;
    }

    DIDT didt;
    init_(&didt, sizeof(GateDescriptor*) * IDT_SIZE - 1, idt);
    
    asm (
        "lidt %0"
        : 
        : "m" (didt));
}