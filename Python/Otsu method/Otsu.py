from PIL import Image


def paintGray(filename, output):
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

def Otsu(filename):
    image = Image.open(filename)
    histogram = histogramGray(filename)
    threshold = Threshold(histogram)
    print(threshold)

    (width, height) = image.size
    r, g, b = image.split()
    for i in range(width):
        for j in range(height):
            Pixel = b.getpixel((i, j))
            if Pixel < threshold:
                image.putpixel((i, j), (0, 0, 0))
            else:
                image.putpixel((i, j), (255, 255, 255))
    image.save("otsuOutput.png")


paintGray("meme.png", "memeGray.png")
Otsu("memeGray.png")