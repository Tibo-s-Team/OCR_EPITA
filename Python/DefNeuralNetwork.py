import random
import math
from PIL import Image

random.seed()
hiddenLayer = [2, 3, 2]
input = [3, 4]


def sigmoid(x):
    return 1 / (1 + math.exp(-x))

def sigmoidPrime(x):
    return x * (1 - x)

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
        for j in range(len(network[i])):
            somme = 0
            for k in range(len(input) if i==0 else len(network[i - 1])):
                somme += (input[k] if i==0 else  network[i - 1][k]["output"]) * network[i][j]["weight"][k]
            network[i][j]["output"] = sigmoid(somme + network[i][j]["biais"])
    return network

def backforawrd(network, output):
    for i in range(len(network)-1, -1, -1):
        if i == (len(network)-1):
            for j in range(len(network[i])):
                network[i][j]["error"] = (output[j] - network[i][j]["output"]) * sigmoidPrime(network[i][j]["output"])
        else:
            for j in range(len(network[i])):
                for k in range(len(network[i+1])):
                    error = network[i+1][k]["weight"][j] * network[i+1][k]["error"]
                network[i][j]["error"] = error * sigmoidPrime( network[i][j]["output"])
    return network

def updateWeight (network, inputs, coeff):
    for i in range(len(network)):
        for k in range(len(network[i])):
            if i == 0:
                for j in range(len(inputs)):
                    network[i][k]['weight'][j] += coeff * network[i][k]['error'] * inputs[j]
            else:
                for j in range(len(network[i-1])):
                    network[i][k]['weight'][j] += coeff * network[i][k]['error'] * network[i - 1][j]["output"]
            network[i][k]['biais'] += coeff * network[i][k]['error']
    return network

def trainingNetwork(times, network):

    for i in range(times):
        network = feedfoward(network, [1, 0])
        network = backforawrd(network, [0, 1])
        network = updateWeight(network, input, 0.1)
    return network

##Test
network = initNeuralNetwork(2, hiddenLayer, 2)
trainingNetwork(20, network)
print(feedfoward(network,[1,0]))
