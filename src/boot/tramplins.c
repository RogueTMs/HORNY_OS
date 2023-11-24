#include "kernel_alloc.h"
#include "kernel_panic.h"
#include "tramplins.h"
#include "vga_funcs.h"

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


static void panic_handler(int vector) {
    kernel_panic("Unhandled interrupt %x", vector);
}

static void tramplin_00(){panic_handler(0x00);}
static void tramplin_01(){panic_handler(0x01);}
static void tramplin_02(){panic_handler(0x02);}
static void tramplin_03(){panic_handler(0x03);}
static void tramplin_04(){panic_handler(0x04);}
static void tramplin_05(){panic_handler(0x05);}
static void tramplin_06(){panic_handler(0x06);}
static void tramplin_07(){panic_handler(0x07);}
static void tramplin_08(){panic_handler(0x08);}
static void tramplin_09(){panic_handler(0x09);}
static void tramplin_0a(){panic_handler(0x0a);}
static void tramplin_0b(){panic_handler(0x0b);}
static void tramplin_0c(){panic_handler(0x0c);}
static void tramplin_0d(){panic_handler(0x0d);}
static void tramplin_0e(){panic_handler(0x0e);}
static void tramplin_0f(){panic_handler(0x0f);}
static void tramplin_10(){panic_handler(0x10);}
static void tramplin_11(){panic_handler(0x11);}
static void tramplin_12(){panic_handler(0x12);}
static void tramplin_13(){panic_handler(0x13);}
static void tramplin_14(){panic_handler(0x14);}
static void tramplin_15(){panic_handler(0x15);}
static void tramplin_16(){panic_handler(0x16);}
static void tramplin_17(){panic_handler(0x17);}
static void tramplin_18(){panic_handler(0x18);}
static void tramplin_19(){panic_handler(0x19);}
static void tramplin_1a(){panic_handler(0x1a);}
static void tramplin_1b(){panic_handler(0x1b);}
static void tramplin_1c(){panic_handler(0x1c);}
static void tramplin_1d(){panic_handler(0x1d);}
static void tramplin_1e(){panic_handler(0x1e);}
static void tramplin_1f(){panic_handler(0x1f);}
static void tramplin_20(){panic_handler(0x20);}
static void tramplin_21(){panic_handler(0x21);}
static void tramplin_22(){panic_handler(0x22);}
static void tramplin_23(){panic_handler(0x23);}
static void tramplin_24(){panic_handler(0x24);}
static void tramplin_25(){panic_handler(0x25);}
static void tramplin_26(){panic_handler(0x26);}
static void tramplin_27(){panic_handler(0x27);}
static void tramplin_28(){panic_handler(0x28);}
static void tramplin_29(){panic_handler(0x29);}
static void tramplin_2a(){panic_handler(0x2a);}
static void tramplin_2b(){panic_handler(0x2b);}
static void tramplin_2c(){panic_handler(0x2c);}
static void tramplin_2d(){panic_handler(0x2d);}
static void tramplin_2e(){panic_handler(0x2e);}
static void tramplin_2f(){panic_handler(0x2f);}
static void tramplin_30(){panic_handler(0x30);}
static void tramplin_31(){panic_handler(0x31);}
static void tramplin_32(){panic_handler(0x32);}
static void tramplin_33(){panic_handler(0x33);}
static void tramplin_34(){panic_handler(0x34);}
static void tramplin_35(){panic_handler(0x35);}
static void tramplin_36(){panic_handler(0x36);}
static void tramplin_37(){panic_handler(0x37);}
static void tramplin_38(){panic_handler(0x38);}
static void tramplin_39(){panic_handler(0x39);}
static void tramplin_3a(){panic_handler(0x3a);}
static void tramplin_3b(){panic_handler(0x3b);}
static void tramplin_3c(){panic_handler(0x3c);}
static void tramplin_3d(){panic_handler(0x3d);}
static void tramplin_3e(){panic_handler(0x3e);}
static void tramplin_3f(){panic_handler(0x3f);}
static void tramplin_40(){panic_handler(0x40);}
static void tramplin_41(){panic_handler(0x41);}
static void tramplin_42(){panic_handler(0x42);}
static void tramplin_43(){panic_handler(0x43);}
static void tramplin_44(){panic_handler(0x44);}
static void tramplin_45(){panic_handler(0x45);}
static void tramplin_46(){panic_handler(0x46);}
static void tramplin_47(){panic_handler(0x47);}
static void tramplin_48(){panic_handler(0x48);}
static void tramplin_49(){panic_handler(0x49);}
static void tramplin_4a(){panic_handler(0x4a);}
static void tramplin_4b(){panic_handler(0x4b);}
static void tramplin_4c(){panic_handler(0x4c);}
static void tramplin_4d(){panic_handler(0x4d);}
static void tramplin_4e(){panic_handler(0x4e);}
static void tramplin_4f(){panic_handler(0x4f);}
static void tramplin_50(){panic_handler(0x50);}
static void tramplin_51(){panic_handler(0x51);}
static void tramplin_52(){panic_handler(0x52);}
static void tramplin_53(){panic_handler(0x53);}
static void tramplin_54(){panic_handler(0x54);}
static void tramplin_55(){panic_handler(0x55);}
static void tramplin_56(){panic_handler(0x56);}
static void tramplin_57(){panic_handler(0x57);}
static void tramplin_58(){panic_handler(0x58);}
static void tramplin_59(){panic_handler(0x59);}
static void tramplin_5a(){panic_handler(0x5a);}
static void tramplin_5b(){panic_handler(0x5b);}
static void tramplin_5c(){panic_handler(0x5c);}
static void tramplin_5d(){panic_handler(0x5d);}
static void tramplin_5e(){panic_handler(0x5e);}
static void tramplin_5f(){panic_handler(0x5f);}
static void tramplin_60(){panic_handler(0x60);}
static void tramplin_61(){panic_handler(0x61);}
static void tramplin_62(){panic_handler(0x62);}
static void tramplin_63(){panic_handler(0x63);}
static void tramplin_64(){panic_handler(0x64);}
static void tramplin_65(){panic_handler(0x65);}
static void tramplin_66(){panic_handler(0x66);}
static void tramplin_67(){panic_handler(0x67);}
static void tramplin_68(){panic_handler(0x68);}
static void tramplin_69(){panic_handler(0x69);}
static void tramplin_6a(){panic_handler(0x6a);}
static void tramplin_6b(){panic_handler(0x6b);}
static void tramplin_6c(){panic_handler(0x6c);}
static void tramplin_6d(){panic_handler(0x6d);}
static void tramplin_6e(){panic_handler(0x6e);}
static void tramplin_6f(){panic_handler(0x6f);}
static void tramplin_70(){panic_handler(0x70);}
static void tramplin_71(){panic_handler(0x71);}
static void tramplin_72(){panic_handler(0x72);}
static void tramplin_73(){panic_handler(0x73);}
static void tramplin_74(){panic_handler(0x74);}
static void tramplin_75(){panic_handler(0x75);}
static void tramplin_76(){panic_handler(0x76);}
static void tramplin_77(){panic_handler(0x77);}
static void tramplin_78(){panic_handler(0x78);}
static void tramplin_79(){panic_handler(0x79);}
static void tramplin_7a(){panic_handler(0x7a);}
static void tramplin_7b(){panic_handler(0x7b);}
static void tramplin_7c(){panic_handler(0x7c);}
static void tramplin_7d(){panic_handler(0x7d);}
static void tramplin_7e(){panic_handler(0x7e);}
static void tramplin_7f(){panic_handler(0x7f);}
static void tramplin_80(){panic_handler(0x80);}
static void tramplin_81(){panic_handler(0x81);}
static void tramplin_82(){panic_handler(0x82);}
static void tramplin_83(){panic_handler(0x83);}
static void tramplin_84(){panic_handler(0x84);}
static void tramplin_85(){panic_handler(0x85);}
static void tramplin_86(){panic_handler(0x86);}
static void tramplin_87(){panic_handler(0x87);}
static void tramplin_88(){panic_handler(0x88);}
static void tramplin_89(){panic_handler(0x89);}
static void tramplin_8a(){panic_handler(0x8a);}
static void tramplin_8b(){panic_handler(0x8b);}
static void tramplin_8c(){panic_handler(0x8c);}
static void tramplin_8d(){panic_handler(0x8d);}
static void tramplin_8e(){panic_handler(0x8e);}
static void tramplin_8f(){panic_handler(0x8f);}
static void tramplin_90(){panic_handler(0x90);}
static void tramplin_91(){panic_handler(0x91);}
static void tramplin_92(){panic_handler(0x92);}
static void tramplin_93(){panic_handler(0x93);}
static void tramplin_94(){panic_handler(0x94);}
static void tramplin_95(){panic_handler(0x95);}
static void tramplin_96(){panic_handler(0x96);}
static void tramplin_97(){panic_handler(0x97);}
static void tramplin_98(){panic_handler(0x98);}
static void tramplin_99(){panic_handler(0x99);}
static void tramplin_9a(){panic_handler(0x9a);}
static void tramplin_9b(){panic_handler(0x9b);}
static void tramplin_9c(){panic_handler(0x9c);}
static void tramplin_9d(){panic_handler(0x9d);}
static void tramplin_9e(){panic_handler(0x9e);}
static void tramplin_9f(){panic_handler(0x9f);}
static void tramplin_a0(){panic_handler(0xa0);}
static void tramplin_a1(){panic_handler(0xa1);}
static void tramplin_a2(){panic_handler(0xa2);}
static void tramplin_a3(){panic_handler(0xa3);}
static void tramplin_a4(){panic_handler(0xa4);}
static void tramplin_a5(){panic_handler(0xa5);}
static void tramplin_a6(){panic_handler(0xa6);}
static void tramplin_a7(){panic_handler(0xa7);}
static void tramplin_a8(){panic_handler(0xa8);}
static void tramplin_a9(){panic_handler(0xa9);}
static void tramplin_aa(){panic_handler(0xaa);}
static void tramplin_ab(){panic_handler(0xab);}
static void tramplin_ac(){panic_handler(0xac);}
static void tramplin_ad(){panic_handler(0xad);}
static void tramplin_ae(){panic_handler(0xae);}
static void tramplin_af(){panic_handler(0xaf);}
static void tramplin_b0(){panic_handler(0xb0);}
static void tramplin_b1(){panic_handler(0xb1);}
static void tramplin_b2(){panic_handler(0xb2);}
static void tramplin_b3(){panic_handler(0xb3);}
static void tramplin_b4(){panic_handler(0xb4);}
static void tramplin_b5(){panic_handler(0xb5);}
static void tramplin_b6(){panic_handler(0xb6);}
static void tramplin_b7(){panic_handler(0xb7);}
static void tramplin_b8(){panic_handler(0xb8);}
static void tramplin_b9(){panic_handler(0xb9);}
static void tramplin_ba(){panic_handler(0xba);}
static void tramplin_bb(){panic_handler(0xbb);}
static void tramplin_bc(){panic_handler(0xbc);}
static void tramplin_bd(){panic_handler(0xbd);}
static void tramplin_be(){panic_handler(0xbe);}
static void tramplin_bf(){panic_handler(0xbf);}
static void tramplin_c0(){panic_handler(0xc0);}
static void tramplin_c1(){panic_handler(0xc1);}
static void tramplin_c2(){panic_handler(0xc2);}
static void tramplin_c3(){panic_handler(0xc3);}
static void tramplin_c4(){panic_handler(0xc4);}
static void tramplin_c5(){panic_handler(0xc5);}
static void tramplin_c6(){panic_handler(0xc6);}
static void tramplin_c7(){panic_handler(0xc7);}
static void tramplin_c8(){panic_handler(0xc8);}
static void tramplin_c9(){panic_handler(0xc9);}
static void tramplin_ca(){panic_handler(0xca);}
static void tramplin_cb(){panic_handler(0xcb);}
static void tramplin_cc(){panic_handler(0xcc);}
static void tramplin_cd(){panic_handler(0xcd);}
static void tramplin_ce(){panic_handler(0xce);}
static void tramplin_cf(){panic_handler(0xcf);}
static void tramplin_d0(){panic_handler(0xd0);}
static void tramplin_d1(){panic_handler(0xd1);}
static void tramplin_d2(){panic_handler(0xd2);}
static void tramplin_d3(){panic_handler(0xd3);}
static void tramplin_d4(){panic_handler(0xd4);}
static void tramplin_d5(){panic_handler(0xd5);}
static void tramplin_d6(){panic_handler(0xd6);}
static void tramplin_d7(){panic_handler(0xd7);}
static void tramplin_d8(){panic_handler(0xd8);}
static void tramplin_d9(){panic_handler(0xd9);}
static void tramplin_da(){panic_handler(0xda);}
static void tramplin_db(){panic_handler(0xdb);}
static void tramplin_dc(){panic_handler(0xdc);}
static void tramplin_dd(){panic_handler(0xdd);}
static void tramplin_de(){panic_handler(0xde);}
static void tramplin_df(){panic_handler(0xdf);}
static void tramplin_e0(){panic_handler(0xe0);}
static void tramplin_e1(){panic_handler(0xe1);}
static void tramplin_e2(){panic_handler(0xe2);}
static void tramplin_e3(){panic_handler(0xe3);}
static void tramplin_e4(){panic_handler(0xe4);}
static void tramplin_e5(){panic_handler(0xe5);}
static void tramplin_e6(){panic_handler(0xe6);}
static void tramplin_e7(){panic_handler(0xe7);}
static void tramplin_e8(){panic_handler(0xe8);}
static void tramplin_e9(){panic_handler(0xe9);}
static void tramplin_ea(){panic_handler(0xea);}
static void tramplin_eb(){panic_handler(0xeb);}
static void tramplin_ec(){panic_handler(0xec);}
static void tramplin_ed(){panic_handler(0xed);}
static void tramplin_ee(){panic_handler(0xee);}
static void tramplin_ef(){panic_handler(0xef);}
static void tramplin_f0(){panic_handler(0xf0);}
static void tramplin_f1(){panic_handler(0xf1);}
static void tramplin_f2(){panic_handler(0xf2);}
static void tramplin_f3(){panic_handler(0xf3);}
static void tramplin_f4(){panic_handler(0xf4);}
static void tramplin_f5(){panic_handler(0xf5);}
static void tramplin_f6(){panic_handler(0xf6);}
static void tramplin_f7(){panic_handler(0xf7);}
static void tramplin_f8(){panic_handler(0xf8);}
static void tramplin_f9(){panic_handler(0xf9);}
static void tramplin_fa(){panic_handler(0xfa);}
static void tramplin_fb(){panic_handler(0xfb);}
static void tramplin_fc(){panic_handler(0xfc);}
static void tramplin_fd(){panic_handler(0xfd);}
static void tramplin_fe(){panic_handler(0xfe);}
static void tramplin_ff(){panic_handler(0xff);}
static void* tramplins[] = {tramplin_00, tramplin_01, tramplin_02, tramplin_03, tramplin_04, tramplin_05, tramplin_06, tramplin_07, tramplin_08, tramplin_09, tramplin_0a, tramplin_0b, tramplin_0c, tramplin_0d, tramplin_0e, tramplin_0f, tramplin_10, tramplin_11, tramplin_12, tramplin_13, tramplin_14, tramplin_15, tramplin_16, tramplin_17, tramplin_18, tramplin_19, tramplin_1a, tramplin_1b, tramplin_1c, tramplin_1d, tramplin_1e, tramplin_1f, tramplin_20, tramplin_21, tramplin_22, tramplin_23, tramplin_24, tramplin_25, tramplin_26, tramplin_27, tramplin_28, tramplin_29, tramplin_2a, tramplin_2b, tramplin_2c, tramplin_2d, tramplin_2e, tramplin_2f, tramplin_30, tramplin_31, tramplin_32, tramplin_33, tramplin_34, tramplin_35, tramplin_36, tramplin_37, tramplin_38, tramplin_39, tramplin_3a, tramplin_3b, tramplin_3c, tramplin_3d, tramplin_3e, tramplin_3f, tramplin_40, tramplin_41, tramplin_42, tramplin_43, tramplin_44, tramplin_45, tramplin_46, tramplin_47, tramplin_48, tramplin_49, tramplin_4a, tramplin_4b, tramplin_4c, tramplin_4d, tramplin_4e, tramplin_4f, tramplin_50, tramplin_51, tramplin_52, tramplin_53, tramplin_54, tramplin_55, tramplin_56, tramplin_57, tramplin_58, tramplin_59, tramplin_5a, tramplin_5b, tramplin_5c, tramplin_5d, tramplin_5e, tramplin_5f, tramplin_60, tramplin_61, tramplin_62, tramplin_63, tramplin_64, tramplin_65, tramplin_66, tramplin_67, tramplin_68, tramplin_69, tramplin_6a, tramplin_6b, tramplin_6c, tramplin_6d, tramplin_6e, tramplin_6f, tramplin_70, tramplin_71, tramplin_72, tramplin_73, tramplin_74, tramplin_75, tramplin_76, tramplin_77, tramplin_78, tramplin_79, tramplin_7a, tramplin_7b, tramplin_7c, tramplin_7d, tramplin_7e, tramplin_7f, tramplin_80, tramplin_81, tramplin_82, tramplin_83, tramplin_84, tramplin_85, tramplin_86, tramplin_87, tramplin_88, tramplin_89, tramplin_8a, tramplin_8b, tramplin_8c, tramplin_8d, tramplin_8e, tramplin_8f, tramplin_90, tramplin_91, tramplin_92, tramplin_93, tramplin_94, tramplin_95, tramplin_96, tramplin_97, tramplin_98, tramplin_99, tramplin_9a, tramplin_9b, tramplin_9c, tramplin_9d, tramplin_9e, tramplin_9f, tramplin_a0, tramplin_a1, tramplin_a2, tramplin_a3, tramplin_a4, tramplin_a5, tramplin_a6, tramplin_a7, tramplin_a8, tramplin_a9, tramplin_aa, tramplin_ab, tramplin_ac, tramplin_ad, tramplin_ae, tramplin_af, tramplin_b0, tramplin_b1, tramplin_b2, tramplin_b3, tramplin_b4, tramplin_b5, tramplin_b6, tramplin_b7, tramplin_b8, tramplin_b9, tramplin_ba, tramplin_bb, tramplin_bc, tramplin_bd, tramplin_be, tramplin_bf, tramplin_c0, tramplin_c1, tramplin_c2, tramplin_c3, tramplin_c4, tramplin_c5, tramplin_c6, tramplin_c7, tramplin_c8, tramplin_c9, tramplin_ca, tramplin_cb, tramplin_cc, tramplin_cd, tramplin_ce, tramplin_cf, tramplin_d0, tramplin_d1, tramplin_d2, tramplin_d3, tramplin_d4, tramplin_d5, tramplin_d6, tramplin_d7, tramplin_d8, tramplin_d9, tramplin_da, tramplin_db, tramplin_dc, tramplin_dd, tramplin_de, tramplin_df, tramplin_e0, tramplin_e1, tramplin_e2, tramplin_e3, tramplin_e4, tramplin_e5, tramplin_e6, tramplin_e7, tramplin_e8, tramplin_e9, tramplin_ea, tramplin_eb, tramplin_ec, tramplin_ed, tramplin_ee, tramplin_ef, tramplin_f0, tramplin_f1, tramplin_f2, tramplin_f3, tramplin_f4, tramplin_f5, tramplin_f6, tramplin_f7, tramplin_f8, tramplin_f9, tramplin_fa, tramplin_fb, tramplin_fc, tramplin_fd, tramplin_fe, tramplin_ff};


static void init_(DIDT* didt, int size, void* address) {
    didt->idt_size = size;
    didt->idt_address = (u32) address;
}


void init_IDT(){

    GateDescriptor* idt = (GateDescriptor*) kernel_malloc(sizeof(GateDescriptor) * IDT_SIZE);


    for (int vector = 0; vector < IDT_SIZE; vector++) {
        byte* handler = tramplins[vector];
        u16 low_16_bits = (u16) ((u32) handler & 0xFFFF);
        u16 high_16_bits = (u16) (((u32) handler) >> 16);
        GateDescriptor tmp;
        tmp.offset_1 = low_16_bits;
        tmp.selector = 0x8;
        tmp.flags = 0b10001111;
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