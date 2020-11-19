import DefNeuralNetwork
import BarDeChargement

# Values of training for the neural network that learn XOR
input = [[0, 0], [1, 0], [0, 1], [1, 1]]
# Output waited for the values given by the inputs
expected_output = [[0], [1], [1], [0]]

# Creat a new neural network with 2 inputs, one hiden layer composed of 2 neurones and 1 output
network = DefNeuralNetwork.initNeuralNetwork(2, [2], 1)


def trainingNetworkXOR(times, network):
    """
    trainingNetwork function for XOR
    Author: Florian Drevet
    Date: 25 october 2020

    number of times/generation to train network with list of XOR example

    :param times: (int:) number of generations
    :param network: The neural network
    :return: The trained Neural Network
    """
    Bar = BarDeChargement.ProgressBar(100, 60, 'Apprentissage')
    for i in range(times):
        for j in range(len(input)):
            network = DefNeuralNetwork.feedforward(network, input[j])
            network = DefNeuralNetwork.backPropagation(network, expected_output[j])
            network = DefNeuralNetwork.updateWeight(network, input[j], 0.1)
        Bar.update(i / 100)
    DefNeuralNetwork.saveNeurones(network)
    return network


def XOR_print(network, input, expected_output):
    """
    XOR_print function
    Author: Lowen Desmarais
    Date: 22 October 2020

    prints all output results from the XOR Neural Network
    accept an error of 0.1

    :param network: The neural Network
    :param input: input value
    :param expected_output: expected output value
    """
    result = DefNeuralNetwork.feedforward(network, input)[-1]
    message = "Success!" if expected_output[0] == 1 and result[0]['output'] >= 0.9 else (
        "Success!" if expected_output[0] == 0 and result[0]['output'] <= 0.1 else "Failure...")
    print(f"\n{message} expected: {expected_output[0]} got: {result[0]['output']}")

'''
# Train our neural network to learn Xor
network = trainingNetworkXOR(100000, network)

# Test if the neural network that learned XOR work
for i in range(4):
    XOR_print(network, input[i], expected_output[i])

# Save the neural network
DefNeuralNetwork.saveNeurones(network, "DataSave/XORNeurones.json")
'''