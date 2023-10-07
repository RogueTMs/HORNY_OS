import os
import random
fileSizeInBytes = 392704 - 512
bin_data = b''

with open('src/boot/Binary_file/binary.bin', 'wb') as f:
    for i in range(fileSizeInBytes):
        gen_byte = random.getrandbits(8)
        bin_data += gen_byte.to_bytes()

    f.write(bin_data)

# bin_data = b""
#
# for i in range(fileSizeInBytes):
#     gen_byte = random.getrandbits(8)
#
#     bin_data += gen_byte.to_bytes()
#
# with open('src/boot/Binary_file/binary.bin', 'wb') as f:
#     f.write(bin_data)
