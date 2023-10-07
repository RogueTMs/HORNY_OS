#check_sum = 0
#
#with open('src/boot/Binary_file/binary.bin', "rb") as f:
#    bin_data = f.read()
#    for i in range(0, len(bin_data)):
#        byte = bin_data[i]
#        check_sum += byte
#
#
#print(hex(check_sum%2**8))


add = 0
with open('src/boot/Binary_file/binary.bin', 'rb') as f:
    bin_data = f.read()
    print(sum(bin_data)%2**8)
    