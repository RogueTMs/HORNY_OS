import os
import random
fileSizeInBytes = 392704 - 512
bin_data = b''

with open('src/boot/bin/binary.bin', 'wb') as f:
    for i in range(fileSizeInBytes):
        gen_byte = random.getrandbits(8)
        bin_data += gen_byte.to_bytes()

    f.write(bin_data)

