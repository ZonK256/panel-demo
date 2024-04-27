import os
import cv2

color_array = []
pixel_array = []

for img in os.listdir("./"):
    if img.endswith(".png"):

        image = cv2.imread(img)
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # loop every pixel
        height, width, _ = image.shape
        for y in range(height):
            for x in range(width):
                # get pixel color
                color = image[y, x]
                #convert color list to single value in 565 format
                color_hex = hex((color[0] >> 3) << 11 | (color[1] >> 2) << 5 | (color[2] >> 3))
                
                if color_hex not in color_array:
                    color_array.append(color_hex)
                pixel_array.append(color_array.index(color_hex))

print(f" len color_array: {len(color_array)} -> {color_array[:10]}...")
print(f" len pixel_array: {len(pixel_array)} -> {pixel_array[:10]}...")


with open("../src/frame_data.cpp", "w") as f:
    # write to file, strip ', replace [ and ] with { and }
    f.write(f"""const uint16_t color_array[] = {{{str(color_array)[1:-1].replace("'","")}}};\n""")
    f.write(f"""const uint16_t pixel_array[] = {{{str(pixel_array)[1:-1]}}};\n""")
