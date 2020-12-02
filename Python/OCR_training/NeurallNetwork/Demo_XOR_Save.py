import XORNetwork as XOR
import DefNeuralNetwork as NN

print('Veuillez entrer un nombre d\'entrainement pour le réseaux de neurones devant apprendre XOR : ', end="")
nb = input()

print(XOR.input)
print(XOR.expected_output)

network = NN.initNeuralNetwork(2, [2], 1)
XOR.trainingNetworkXOR(int(nb), network)

NN.saveNeurones(network, "DataSave/XOR.json")
