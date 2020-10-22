import random
import math
import json
from PIL import Image
import training
import BarDeChargement
import NeuralNetwork

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

def loadNeurones(path = "DataSave/TrainedNeurones.json"):
    """
    :param path: path we want to load for network
    :return: the new reconstructed network from a json file
    """
    with open(path) as Network_json:
        network = json.load(Network_json)
    return network


def saveNeurones(network, path="DataSave/TrainedNeurones.json"):
    with open(path, 'w') as Network_json:
        json.dump(network, Network_json, indent=4)



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
                error = 0
                for k in range(len(network[i+1])):
                    error += network[i+1][k]["weight"][j] * network[i+1][k]["error"]
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
        while times/100 != 1:
            times = times*10 if times/100 < 1 else times/10
        Bar.update(i*times)
    return network


##Test

def test_print(network, numbertest, letter):
    print("##########"+letter+"##########")
    result = feedfoward(network, training.test[numbertest])[-1]
    for i in range(len(result)):
        if i == numbertest:
            print("#", result[i]["output"])
        else:
            print(result[i]["output"])

network = initNeuralNetwork(625, [25, 25], 10)
trainingNetwork(10, network)

print("\n")
test_print(network, 0, "A")
test_print(network, 1, "B")
test_print(network, 2, "C")
test_print(network, 3, "D")
test_print(network, 4, "E")
test_print(network, 5, "F")
test_print(network, 6, "G")
test_print(network, 7, "H")
"""

new_network = NeuralNetwork.Network(3, [16,16], 3)
print(new_network.display())
print(network)
"""
