from PIL import Image
import os
import BarDeChargement
import DefNeuralNetwork
import random


def matrixImage(image):
    """
       Transform an Image to a matrix of pixels
       Author: Florian Drevet
       Date: 16 october 2020

       Do the average of all rgb pixel of an image and divide it by 255 to have it between 0 and 1 and constitu the
       matrix of an image

       :param image: an Image open with PIL
       :return: The trained Neural Network
       """
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
    """
       Creat a list of all the files in a folder
       Author: Florian Drevet
       Date: 16 october 2020

       Creat a list with the path of all images in a folder and add the name of the folder before the name of the file

       :param folder_path: Folder path from where we want all the names of the file
       :return: list of all the file names
       """
    list = []
    for path, dirs, files in os.walk(folder_path):
        for filename in files:
            list.append(folder_path + "\\" + filename)
    return list


def creatList_folderLetters(folder_path):
    """
       Creat a list of lists of file names in folder
       Author: Florian Drevet
       Date: 16 october 2020

       Use the fonction creatList_images to all the folder who are in the folder specified in param and add the name of
       the folder.

       :param folder_path: Folder path from where we want to use creatList_images to all his folders
       :return: list of list of file name with the name of each folder add before
       """
    list = []
    for path, dirs, files in os.walk(folder_path):
        for directory in dirs:
            list.append(creatList_images(folder_path + directory))
    return list


def creatLsit_matrix(listfolderLetter):
    """
       Creat a list of lists of matrix of images for neural network training
       Author: Florian Drevet
       Date: 16 october 2020

       replace the list of path of images by matrix of this images that will be use to train the neural network

       :param listfolderLetter:folder that contain all the folders of the different images
       :return: return a list of list of matrix
       """
    res = []
    for i in range(len(listfolderLetter)):
        sous_list = []
        for j in range(len(listfolderLetter[i])):
            image = Image.open(listfolderLetter[i][j])
            matrix = matrixImage(image)
            sous_list.append(matrix)
        res.append(sous_list)
    return res


def creatlist_matrixtest(list_image_test):
    """
       Creat a list of lists of matrix of images to test the neural network
       Author: Florian Drevet
       Date: 16 october 2020

       Build a list of matrix of images that are letters to test if our neural network work

       :param list_image_test: list of all the images path that will be use to test
       :return: return a list of test images' matrix
       """
    res = []
    for i in range(len(list_image_test)):
        image = Image.open(list_image_test[i])
        matrix = matrixImage(image)
        res.append(matrix)
    return res


def trainingNetworkImage(times, network):
    """
    trainingNetwork function
    Author: Florian Drevet
    Date: 16 october 2020

    number of times/generation to train network wqith list of matrix images

    :param times: (int:) number of generations
    :param network: The neural network
    :return: The trained Neural Network
    """
    Bar = BarDeChargement.ProgressBar(100, 60, 'Apprentissage')
    for i in range(times):
        for j in range(len(exo)):
            for k in range(15):
                train = random.randint(0, 360)
                network = DefNeuralNetwork.feedforward(network, exo[j][train])
                network = DefNeuralNetwork.backPropagation(network, solution[j])
                network = DefNeuralNetwork.updateWeight(network, exo[j][train], 0.1)
        Bar.update(i / 0.2)
    DefNeuralNetwork.saveNeurones(network)
    return network


# Results that are waited to be by the different neuronne for each letters
resultA = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0]
resultB = [0, 1, 0, 0, 0, 0, 0, 0, 0, 0]
resultC = [0, 0, 1, 0, 0, 0, 0, 0, 0, 0]
resultD = [0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
resultE = [0, 0, 0, 0, 1, 0, 0, 0, 0, 0]
resultF = [0, 0, 0, 0, 0, 1, 0, 0, 0, 0]
resultG = [0, 0, 0, 0, 0, 0, 1, 0, 0, 0]
resultH = [0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
resultI = [0, 0, 0, 0, 0, 0, 0, 0, 1, 0]
resultJ = [0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
'''
# Build the list of each path of the differents images that are use to train the neural network in the folder
# tests/imagesletters/
listfolderLetters = creatList_folderLetters("..\\..\\tests\\images\\letters\\")
# Creat the list of the matrix of this images
exo = creatLsit_matrix(listfolderLetters)'''
# Creat a list of the results for the letters in alphabetical order
solution = [resultA, resultB, resultC, resultD, resultE, resultF, resultG, resultH, resultI, resultJ]
# Creat a list of matrix of test images that the neural tnetwork has already seen -> Easy
testLv1 = creatlist_matrixtest(creatList_images("..\\..\\tests\images\\test_letters\\"))
# Creat a list of matrix of test images that the neural network has never seen before -> Difficult
testLv2 = creatlist_matrixtest(creatList_images("..\\..\\tests\images\\test_letters_lv2\\"))


def parsingNeuronne2Letter(number):
    """
    Parse neuronne to letters
    Author: Florian Drevet
    Date: 16 october 2020

    Parse the most activated neurones of the output layer to the letter which is associated

    :param number: The number of the most activated neurone
    :return: The letter associated
    """
    if number == 0:
        return "A"
    if number == 1:
        return "B"
    if number == 2:
        return "C"
    if number == 3:
        return "D"
    if number == 4:
        return "E"
    if number == 5:
        return "F"
    if number == 6:
        return "G"
    if number == 7:
        return "H"
    if number == 8:
        return "I"
    if number == 9:
        return "J"
    return None

'''
# Init a neural network to train
network = DefNeuralNetwork.initNeuralNetwork(625, [16, 16], 10)
# Train the neural network with the different images
trainingNetworkImage(50, network)
'''
network = DefNeuralNetwork.loadNeurones()

# Load a neural network from a json file
# network = loadNeurones()

def test_print(network, numbertest, letter):
    """
    Test the given neural network
    Author: Florian Drevet
    Date: 16 october 2020

    Give a image of letter to the neural netork and the neural network responds the letter it thinks it is.
    The Format of the test is :
    ######A####### -> The Letter given on the image
    LV1 : *a letter* -> The letter that the neural network thinks it is for an image that it has already seen
    LV2 : *a letter* -> The letter that the neural network thinks it is for an image that it has never seen

    :param network: The neural network to test
    :param numbertest: The number of the letter that begin at 0 for A
    :param letter: The tested letter
    :return: void printed result
    """
    print("##########" + letter + "##########")
    resultLv1 = DefNeuralNetwork.feedforward(network, testLv1[numbertest])[-1]
    maxi_val_Lv1 = 0
    maxi_lettre_Lv1 = -1
    maxi_val_Lv2 = 0
    maxi_lettre_Lv2 = -1
    for i in range(len(resultLv1)):
        if resultLv1[i]["output"] > maxi_val_Lv1:
            maxi_val_Lv1 = resultLv1[i]["output"]
            maxi_lettre_Lv1 = i
    resultLv2 = DefNeuralNetwork.feedforward(network, testLv2[numbertest])[-1]
    for i in range(len(resultLv2)):
        if resultLv2[i]["output"] > maxi_val_Lv2:
            maxi_val_Lv2 = resultLv2[i]["output"]
            maxi_lettre_Lv2 = i
    print("LV1 :", parsingNeuronne2Letter(maxi_lettre_Lv1), "=", str(maxi_val_Lv1))
    print("LV2 :", parsingNeuronne2Letter(maxi_lettre_Lv2), "=", str(maxi_val_Lv2))


# Test for each letter
print("\n")
test_print(network, 0, "A")
test_print(network, 1, "B")
test_print(network, 2, "C")
test_print(network, 3, "D")
test_print(network, 4, "E")
test_print(network, 5, "F")
test_print(network, 6, "G")
test_print(network, 7, "H")
test_print(network, 8, "I")
test_print(network, 9, "J")
