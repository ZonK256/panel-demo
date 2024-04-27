import os
import cv2

output = []

for img in os.listdir("./"):
    if img.endswith(".png"):
        hex_array = []
        image = cv2.imread(img)
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # loop every pixel
        height, width, _ = image.shape
        for y in range(height):
            for x in range(width):
                # combine rgb to single hex
                hex_array.append("0x" + format(image[y, x][0], "02x") + format(image[y, x][1], "02x") + format(image[y, x][2], "02x"))
        output.append(hex_array)

with open("output.txt", "w") as f:
    # write to file, stripping ', replace [ and ] with { and }
    f.write("{" + str(output).strip("[]").replace("'", "").replace("[", "{").replace("]", "}") + "}")
