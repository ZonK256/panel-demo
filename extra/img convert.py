# load images from this folder and convert them to hex bitmaps for use in C code, output is a list of 0x00 arrays

import os

output = []

for img in os.listdir("./"):
    if img.endswith(".png"):
        with open(img, "rb") as f:
            data = f.read()
            output.append("0x" + ", 0x".join([format(x, "02x") for x in data]))


with open("output.txt", "w") as f:
    f.write(str(output))
