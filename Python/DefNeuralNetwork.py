import random
import math
from PIL import Image
random.seed()
hiddenLayer = [16, 16]


def initNeuralNetwork(nbInput, hiddenLayer, nbOutPut):
    network = []
    for i in range(len(hiddenLayer)+1):
        LayerDico = []
        for j in range(hiddenLayer[0] if i == 0 else (nbOutPut if i == len(hiddenLayer) else hiddenLayer[i-1])):
            neuronne = {}
            weight = []
            for k in range(nbInput if i == 0 else (hiddenLayer[i-1] if i == len(hiddenLayer) else hiddenLayer[i])):
                weight.append(random.uniform(-1, 1))
            neuronne["weight"] = weight
            neuronne["biais"] = random.uniform(-1, 1)
            LayerDico.append(neuronne)
        network.append(LayerDico)
    return network
print(initNeuralNetwork(3, hiddenLayer, 3))
