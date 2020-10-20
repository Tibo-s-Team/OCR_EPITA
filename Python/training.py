from PIL import Image
import os

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

def creatList_images(folder_path):
    list = []
    for path, dirs, files in os.walk(folder_path):
        for filename in files:
            list.append(folder_path+ "\\" + filename)
    return list

def creatList_folderLetters(folder_path):
    list = []
    for path, dirs, files in os.walk(folder_path):
        for directory in dirs:
            list.append(creatList_images(folder_path + directory))
    return list

def creatLsit_matrix(listfolderLetter):
    res = []
    for i in range(len(listfolderLetter)):
        sous_list = []
        for j in range(len(listfolderLetter[i])):
            image = Image.open(listfolderLetter[i][j])
            matrix = matrixImage(image)
            sous_list.append(matrix)
        res.append(sous_list)
    return res

resultA = [1, 0, 0]
resultB = [0, 1, 0]
resultC = [0, 0, 1]

listfolderLetters = creatList_folderLetters("letters\\")
exo = creatLsit_matrix(listfolderLetters)
solution = [resultA, resultB, resultC]