from PIL import Image
import os

def RotateImages360(pathimage):
    image = Image.open(pathimage)
    os.chdir(pathimage[0:-5])
    (width, height) = image.size
    for i in range(width):
        for j in range(height):
            (pixelr, pixelg, pixelb) = image.getpixel((i, j))
            if pixelr < 50:
                image.putpixel((i,j), (pixelr+150, pixelg, pixelb, 255))
    for i in range(360):
        rotate1 = image.rotate(1+i)
        for k in range(width):
            for l in range(height):
                (pixelr, pixelg, pixelb) = rotate1.getpixel((k, l))
                if pixelr < 50:
                    rotate1.putpixel((k, l), (255, 255, 255, 255))
                elif pixelr < 200 and pixelb < pixelr:
                    rotate1.putpixel((k,l), (pixelr-150, pixelg, pixelb, 255))
        rotate1.save(pathimage[-5]+str(i)+".png", 'png')



RotateImages360("letters\\A\\a.png")