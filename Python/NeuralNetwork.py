import random

#deepcopy serves as a way to instance objects into classes without reference problems
#without, neurones would all point to the same list and so would layers
from copy import deepcopy


class Network:

    def __init__(self, nbInput, nbLayerNeurones, nbOutput):
        layers = []

        nblayers = len(nbLayerNeurones)
        self.nblayers = nblayers

        # creating the layers and their neurones
        for i in range(nblayers):
            for nb in nbLayerNeurones:
                layers.append(deepcopy(self.Layer(nb)))

        self.outputLayer = layers[nblayers - 1]
        self.layers = layers

        for i in range(nblayers + 1):
            for j in range(nbLayerNeurones[0] if i == 0 else (nbOutput if i == nblayers else nbLayerNeurones[i])):
                for k in range(nbInput if i == 0 else nbLayerNeurones[i-1]):
                    self.layers[i].neurones[j].weight.append(random.uniform(-1, 1))
                self.layers[i].neurones[j].bias = random.uniform(-1, 1)



    def display(self):
        res = []
        for layer in self.layers:
            res.append(layer.display())

        return res


    class Layer:

        def __init__(self, nbneurones):
            neurones = []
            for i in range(nbneurones):
                neurones.append(deepcopy(self.Neurones()))

            self.neurones = neurones

        def display(self):
            res = []
            for neurone in self.neurones:
                res.append(neurone.display())
            return res


        class Neurones:

            def __init__(self, weight=[], bias=0.1):
                self.weight = weight
                self.bias = bias

            def display(self):
                res = {}
                res["weight"] = self.weight
                res["bias"] = self.bias
                return res
