import DefNeuralNetwork

input = [[0,0], [1,0], [0, 1], [1, 1]]
expected_output = [0, 1, 1, 0]

network = DefNeuralNetwork.initNeuralNetwork(2, [2], 1)
DefNeuralNetwork.trainingNetwork(1000, network, input)


def XOR_print(network, input, expected_output):
    result = DefNeuralNetwork.feedfoward(network, input)[-1]
    message = "Success!" if result[0] == expected_output else "Failure..."
    print(f"\n{message} expected: {expected_output} got: {result[0]['output']}")

for i in range(4):
    XOR_print(network, input[i], expected_output[i])

DefNeuralNetwork.saveNeurones(network, "DataSave/XORNeurones.json")


