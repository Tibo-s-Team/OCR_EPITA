from PIL import Image

image = Image.open("sample_1.jpg")
(width, height) = image.size
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
nvlleImage = Image.new('RGBA', (width, height), WHITE)
for i in range(0, width):
    for j in range(0, height):
        pixel = image.getpixel((i, j))
        if pixel > 150:
            nvlleImage.putpixel((i, j), WHITE)
        else:
            nvlleImage.putpixel((i,j), BLACK)

nvlleImage.show()



