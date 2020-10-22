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
                    error += network[i+1][k]["weight"][j] * network[i+1][k]["error"] #Lowen le GENIE
                network[i][j]["error"] = error * sigmoidPrime(network[i][j]["output"])
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
            for k in range(15):
                train = random.randint(0, 360)
                network = feedfoward(network, training.exo[j][train])
                network = backforawrd(network, training.solution[j])
                network = updateWeight(network, training.exo[j][train], 0.1)
        Bar.update(i/10 )
    saveNeurones(network)
    return network


##Test
def test_print(network, numbertest, letter):
    print("##########"+letter+"##########")
    resultLv1 = feedfoward(network, training.testLv1[numbertest])[-1]
    maxi_val_Lv1 = 0
    maxi_lettre_Lv1 = -1
    maxi_val_Lv2 = 0
    maxi_lettre_Lv2 = -1
    for i in range(len(resultLv1)):
        if resultLv1[i]["output"] > maxi_val_Lv1:
            maxi_val_Lv1 = resultLv1[i]["output"]
            maxi_lettre_Lv1 = i
    resultLv2 = feedfoward(network, training.testLv2[numbertest])[-1]
    for i in range(len(resultLv2)):
        if resultLv2[i]["output"] > maxi_val_Lv2:
            maxi_val_Lv2 = resultLv2[i]["output"]
            maxi_lettre_Lv2 = i
    print("LV1 :", training.parsingNeuronne2Letter(maxi_lettre_Lv1), "=", str(maxi_val_Lv1))
    print("LV2 :", training.parsingNeuronne2Letter(maxi_lettre_Lv2), "=", str(maxi_val_Lv2))

#network = initNeuralNetwork(625, [16, 16], 10)
#trainingNetwork(1000, network)
network = loadNeurones()
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


