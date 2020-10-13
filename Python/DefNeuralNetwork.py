import random
import math
from PIL import Image

random.seed()
hiddenLayer = [2, 3, 2]
input = [3, 4]


def sigmoid(x):
    return 1 / (1 + math.exp(-x))


def initNeuralNetwork(nbInput, hiddenLayer, nbOutPut):
    network = []
    for i in range(len(hiddenLayer) + 1):
        LayerDico = []
        for j in range(hiddenLayer[0] if i == 0 else (nbOutPut if i == len(hiddenLayer) else hiddenLayer[i])):
            neuronne = {}
            weight = []
            for k in range(nbInput if i == 0 else hiddenLayer[i-1]):
                weight.append(random.uniform(-1, 1))
            neuronne["weight"] = weight
            neuronne["biais"] = random.uniform(-1, 1)
            LayerDico.append(neuronne)
        network.append(LayerDico)
    return network


def feedfoward(network, input):
    for i in range(len(network)):
        if i == 0:
            for j in range(len(network[i])):
                somme = 0
                for k in range(len(input)):
                    somme += input[k] * network[i][j]["weight"][k]
                network[i][j]["output"] = sigmoid(somme + network[i][j]["biais"])
        else:
            for j in range(len(network[i])):
                somme = 0
                for k in range(len(network[i - 1])):
                    somme += network[i - 1][k]["output"] * network[i][j]["weight"][k]
                network[i][j]["output"] = sigmoid(somme + network[i][j]["biais"])
    return network

print(feedfoward(initNeuralNetwork(2, hiddenLayer, 2), input))
