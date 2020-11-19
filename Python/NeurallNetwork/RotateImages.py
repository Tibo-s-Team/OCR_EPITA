from PIL import Image
import os

def RotateImages360(pathimage):
    """
        Turn an image of a letter of 1 degre and save it (does that 360 times)
        Author: Florian Drevet
        Date: 16 october 2020

        Creat 360 images from a given image of letter but rotated from 1 degre in the same directory of the given image

        :param pathimage: Path of the image to turn
        :return: void, 360 new images
        """
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


#Use the function to rotate the image
RotateImages360("C:\\Users\\flori\\PycharmProjects\\OCR_EPITA\\tests\\images\\letters\\A\\a.png")