import random
import math
from PIL import Image
import training
import BarDeChargement

random.seed()

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
    Bar = BarDeChargement.ProgressBar(100, 60, 'Apprentissage')
    for i in range(times):
        for j in range(len(training.exo)):
            for k in range(len(training.exo[j])):
                network = feedfoward(network, training.exo[j][k])
                network = backforawrd(network, training.solution[j])
                network = updateWeight(network, training.exo[j][k], 0.2)
        Bar.update(i)
    return network

##Test
network = initNeuralNetwork(625, [16, 16], 4)
trainingNetwork(100, network)
testa = feedfoward(network, training.test[0])[-1]

print("\n")
for i in range(len(testa)):
    print(testa[i]["output"])
print("###################")
result = feedfoward(network, training.test[1])[-1]
for i in range(len(result)):
    print(result[i]["output"])
print("###################")
result = feedfoward(network, training.test[2])[-1]
for i in range(len(result)):
    print(result[i]["output"])


