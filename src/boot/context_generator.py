with open("context.asm", "w", encoding="UTF-8") as file:
    print("[BITS 32]\n\n", file=file)
    
    for i in range(256):
        
        interupt = hex(i)[2:]
        if len(interupt) == 1:
            interupt = "0" + interupt
        print(f"[GLOBAL _tramplin_{interupt}]", file=file)

    print("[GLOBAL _get_esp]", file=file)

    print("_get_esp:\n", file=file)
    print("\tmov eax, esp\n", file=file)
    print("\tret\n", file=file)

    print("""collect_context:
\tpusha
\tpush gs
\tpush fs
\tpush es
\tpush ds
\textern _panic_handler
\tcall _panic_handler
\tpop ds
\tpop es
\tpop fs
\tpop gs
\tpopa
\tiretd\n\n""", file=file)


    for i in range(256):
        x = hex(i)
        
        interupt = x[2:]
        if len(interupt) == 1:
            interupt = "0" + interupt
        print(f"_tramplin_{interupt}:", file=file)
        if i >= 32:
            print("\tpush 0x0", file=file)
        print(f"\tpush {x}", file=file)
        print("\tjmp collect_context\n", file=file)




