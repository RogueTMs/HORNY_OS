
with open("tramplins.c", "w", encoding="ASCII") as file:
    print("#include \"kernel_alloc.h\"\n", file=file)

    for i in range(256):
        interupt = hex(i)[2:]
        if len(interupt) == 1:
            interupt = "0" + interupt
        file.write(f"static void tramplin_{interupt}()" + "{" + f"panic_handler(0x{interupt});" + "}\n")
    file.write("static void* tramplins = {")

    for i in range(256):
        interupt = hex(i)[2:]
        if len(interupt) == 1:
            interupt = "0" + interupt
        if i != 255:
            print(f"tramplin_{interupt}", end=", ", file=file)
        else:
            print(f"tramplin_{interupt}", end="};", file=file)
