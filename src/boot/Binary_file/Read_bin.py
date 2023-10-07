check_sum = 0

with open('src/boot/boot.img', "rb") as f:
    bin_data = f.read()
    for i in range(0, len(bin_data)):
        byte = bin_data[i]
        check_sum = (check_sum + byte)


print(hex(check_sum%2**8))
