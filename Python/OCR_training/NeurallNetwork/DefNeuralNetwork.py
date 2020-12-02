import random
import math
import json
from PIL import Image
import BarDeChargement
import NeuralNetwork
#import training

random.seed()

def sigmoid(x):
    """
    sigmoid function
    Author: Florian Drevet
    Date: 13 october 2020

    smoothes the neurones weight and bias for an output different than 1 and 0
    this allows for sigmoid neurones

    :param x: (float:) the value to sigmoid
    :return: (float:) the new value != 1 or 0
    """
    return 1 / (1 + math.exp(-x))

def sigmoidPrime(x):
    """
    sigmoidPrime function
    Author: Florian Drevet
    Date: 16 october 2020

    For Backpropagation (smoothes again weight and bias)

    :param x: (float:) value to sigmoidPrime
    :return: (float:) the new value
    """
    return x * (1 - x)

def initNeuralNetwork(nbInput, hiddenLayer, nbOutPut):
    """
    initNeuralNetwork function
    Author: FLorian Drevet
    Date: 12 October 2020

    Creates the Neural Network with the number of in put neurones, a list of layers and number of neurones, and
    the number of output neurones

    :param nbInput: (int:) number of input neurones
    :param hiddenLayer: (list:int:) a list with the number of neurones for each layer
    :param nbOutPut: (int:) number of output neurones
    :return: (list:list:dictionary(list, float):) The Neural Network
    """
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
    loadNeurones function
    Author: Lowen Desmarais
    Date: 22 october 2020

    loads the Network from the json file

    :param path: (str:) path we want to load for network
    :return: (Network:) the new reconstructed network from a json file
    """
    with open(path) as Network_json:
        network = json.load(Network_json)
    return network


def saveNeurones(network, path="DataSave/TrainedNeurones.json"):
    """
    saveNeurones function
    Author: Lowen Desmarais
    Date: 22 October 2020

    Saves the network (essentially weights and biases) into a json file

    :param network: (Network:) the Neural Network we want to save
    :param path: (str:) the path where we want to save the network
    :return: a json file with the network
    """
    with open(path, 'w') as Network_json:
        json.dump(network, Network_json, indent=4)



def feedforward(network, input):
    """
    feedforward function
    Author: Florian Drevet
    Date: 12 october 2020

    Feeds weights and bias to the next layer through input
    uses the sigmoid function to feed to the output of the neurone

    :param network: (Network:) network to feed
    :param input: input value to be tested
    :return: the Neural Network
    """
    for i in range(len(network)):
        for j in range(len(network[i])):
            somme = 0
            for k in range(len(input) if i==0 else len(network[i - 1])):
                somme += (input[k] if i==0 else  network[i - 1][k]["output"]) * network[i][j]["weight"][k]
            network[i][j]["output"] = sigmoid(somme + network[i][j]["biais"])
    return network

def backPropagation(network, output):
    """
    backPropagation function
    Author: Florian Drevet
    Date: 16 october 2020

    Updates the error value in the Network backwards, meaning the weights, bias and output are taken in account
    to produce an error value for the neurones of the last layer

    :param network: The neural network
    :param output: (float:) output value
    :return: The neural network with error values
    """
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
    """
    updateWeight function
    Author: Florian Drevet
    Date: 16 october 2020

    Updates (adds) the weights of the Neurones, using the error value from backpropagation and the predetermined coeff
    also changes the bias
    this is where the Neural Network will "evolve", continuing to learn after the forward feed and the backpropagation

    :param network: The Neural Network
    :param inputs: (float) input values
    :param coeff: (float:) coefficient to update the weight (we chose 0.1)
    :return: Updated Neural Network
    """
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


