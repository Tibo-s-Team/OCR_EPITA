from PIL import Image

def paintGray(filename, output):
    """
    paintGray function
    Author: Lowen Desmarais
    Date: 24 October 2020

    Grayscales an image with the specified path, and outputs with the specified output path

    :param filename: Input path image
    :param output: Output path
    """
    image = Image.open(filename)
    (width, height) = image.size
    r, g, b = image.split()
    for i in range(width):
        for j in range(height):
            pixelR = float(r.getpixel((i, j)))
            pixelG = float(g.getpixel((i, j)))
            pixelB = float(b.getpixel((i, j)))
            average = pixelR * 0.3 + pixelG * 0.59 + pixelB * 0.11
            image.putpixel((i, j), (int(average), int(average), int(average)))
    image.save(output)


def matrixPrint(matrix):
    for i in range(len(matrix)):
        print(matrix[i])
        print()


def adaptativeThreshold(image, out, w, h):

    intImage = [[0]*h]*w
    s = 12
    t = 15

    for i in range(w):
        sum = 0
        for j in range(h):
            pixel = int(image.getpixel((i, j))[0])
            sum += pixel
            if i == 0:
                intImage[i][j] = sum
            else:
                intImage[i][j] = intImage[i-1][j] + sum

    for i in range(w):
        for j in range(h):

            x1 = i-s//2 if i < s//2 else 0
            x2 = i+s//2 if i+s//2 < w else w-1
            y1 = j-s//2 if j < s//2 else 0
            y2 = j+s//2 if j+s//2 < h else h-1

            count = (x2-x1) * (y2-y1)
            sum = intImage[x2][y2] - intImage[x2][y1-1] - intImage[x1-1][y2] + \
                  intImage[x1-1][y1-1]

            pixel = int(image.getpixel((i, j))[0])
            #print(f"pixel value: {pixel}")
            #print(f"count value: {count}")
            print(f"sum: {sum}")
            #print(pixel*count)
            #print(sum*(100-t)/100)
            #print("-"*20)
            if pixel * count <= sum*(100-t)/100:
                out[i][j] = 0
            else:
                out[i][j] = 255
    #print(intImage)


def Bradley(filename, output):
    image = Image.open(filename)
    (width, height) = image.size
    out = [[0] * height] * width

    adaptativeThreshold(image, out, width, height)

    for i in range(width):
        for j in range(height):
            image.putpixel((i, j), (out[i][j], out[i][j], out[i][j]))
    image.show()
    image.save(output)

#paintGray('Bradley.jpg', 'Bradley_Gray.jpg')
#Bradley('Bradley_Gray.jpg', 'Bradley_output.jpg')
#paintGray('hh.png', 'hh_Gray.png')
Bradley('hh.png', 'hh_output.png')

