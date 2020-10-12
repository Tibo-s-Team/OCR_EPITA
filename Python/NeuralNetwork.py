import random
import math
from PIL import Image

random.seed()


def matrixImage(image):
    (width, height) = image.size
    matrix = []
    r, g, b = image.split()
    for i in range(width):
        for j in range(height):
            pixelR = float(r.getpixel((i, j))) / 255.0
            pixelG = float(g.getpixel((i, j))) / 255.0
            pixelB = float(b.getpixel((i, j))) / 255.0
            matrix.append((pixelR + pixelG + pixelB) / 3.0)
    return matrix


imageA = Image.open("a.png")
matrixA = matrixImage(imageA)
imageB = Image.open("b.png")
matrixB = matrixImage(imageB)

test = [matrixA, matrixB]
result = [[1, 0], [0, 1]]

nbEntryValue = 625
nbHiddenNeurals1 = 16
nbHiddenNeurals2 = 16
nbOutPutNeurals = 2


def matrix_product(A, B):
    res = []
    for i in range(len(A)):
        value = 0
        for k in range(len(B)):
            value += A[i][k] * B[k]
        res.append(value)
    return res


def generate_layer_wight(lengthA, lengthA0):  # Creat the matrix of the wight of layers
    res = []
    for i in range(0, lengthA):
        res.append([])
        for j in range(0, lengthA0):
            alea = random.uniform(-1, 1)
            res[i].append(alea)
    return res


def generate_layer_biais(nb):  # Creat the matrix of the biais of layers
    res = []
    for i in range(0, nb):
        res.append(random.uniform(-1, 1))
    return res


def sigmoid(x):
    return 1 / (1 + math.exp(-x))


# Derive de notre fonction d'activation
def sigmoidPrime(x):
    return x * (1 - x)


def feedforward(A, B, C):
    res = []
    product = matrix_product(A, B)
    for i in range(len(product)):
        res.append(sigmoid(product[i] + C[i]))
    return res


# Initialization of wight and biais of our neuronal network
hiden_layer_1_wight = generate_layer_wight(nbHiddenNeurals1, nbEntryValue)
hiden_layer_1_biais = generate_layer_biais(nbHiddenNeurals1)
hiden_layer_2_wight = generate_layer_wight(nbHiddenNeurals2, nbHiddenNeurals1)
hiden_layer_2_biais = generate_layer_biais(nbHiddenNeurals2)
out_layer_wight = generate_layer_wight(nbOutPutNeurals, nbHiddenNeurals2)
out_layer_biais = generate_layer_biais(nbOutPutNeurals)

learning = 2

for i in range(0, learning):
    # feedforward
    for i in range(len(test)):
        print(test[i])
        hiden_layer1 = feedforward(hiden_layer_1_wight, test[i], hiden_layer_1_biais)
        hiden_layer2 = feedforward(hiden_layer_2_wight, hiden_layer1, hiden_layer_2_biais)
        out_put = feedforward(out_layer_wight, hiden_layer2, out_layer_biais)

    # backpropagation


def back_propagation_output(out_put_values, out_put_weight, out_put_biais):
    for i in range(len(out_put)):
        print("ok")