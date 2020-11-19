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


def histogramGray(filename):
    """
    histogramGray function
    Author: Lowen Desmarais
    Date: 24 October 2024

    Creates a histogram of grey levels of an image from the specified path

    :param filename: path to load image
    """
    histogram = [0] * 256  # les valeurs de gris de pixel
    image = Image.open(filename)
    (width, height) = image.size
    r, g, b = image.split()
    for i in range(width):
        for j in range(height):
            Gray = float(r.getpixel((i, j)))
            histogram[int(Gray)] += 1
    return histogram



def Threshold(histogram):
    """
    Threshold function
    Author: Lowen Desmarais
    Date: 24 October 2020

    calculates the optimal threshold value using the otsu method with the gray histogram

    :param histogram: (list:) histogram of gray levels
    :return: threshold value (between 0 and 255)
    """
    totalPixel = 0
    for i in range(256):
        totalPixel += histogram[i]

    omega = 0
    mu = 0
    muT = 0
    values = []

    for i in range(256):
        muT += i*(histogram[i] / totalPixel)

    thresholdMax = 0
    for i in range(256):
        omega += histogram[i] / totalPixel
        mu += i * (histogram[i] / totalPixel)

        sigma = ((muT*omega) - mu)**2 / (omega * (1-omega))
        values.append(sigma)
        if sigma > thresholdMax:
            thresholdMax = i

    return thresholdMax

def ThresholdTest(histogram):
    totalPixel = 0
    for i in range(256):
        totalPixel += histogram[i]

def Otsu(filename, output):
    """
    Otsu function
    Author: Desmarais Lowen
    Date: 24 October 2020

    contrasts the image using the calculated threshold value for all pixels of the image and saves it

    :param filename: path of image input
    """
    image = Image.open(filename)
    histogram = histogramGray(filename)
    threshold = Threshold(histogram)
    #print(threshold)

    (width, height) = image.size
    r, g, b = image.split()
    for i in range(width):
        for j in range(height):
            Pixel = b.getpixel((i, j))
            if Pixel < threshold:
                image.putpixel((i, j), (0, 0, 0))
            else:
                image.putpixel((i, j), (255, 255, 255))
    image.save(output)


#paintGray("meme.png", "Output/memeGray.png")
#Otsu("memeGray.png", "Output/OtsuOutput")