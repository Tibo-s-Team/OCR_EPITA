import DefNeuralNetwork as NN

print('Veuillez entrer le nom du fichier à charger: ', end="")
nb = input()
network = NN.loadNeurones("DataSave\\"+nb)

print('-------------------XOR-------------------')
continuer = True
while(continuer):
    print('Veuillez entrer le premier input: ', end="")
    input1 = input()
    print('Veuillez entrer le deuxieme input: ', end="")
    input2 = input()

    result = NN.feedforward(network, [int(input1), int(input2)])[-1]
    print("XOR(", input1, ",", input2, ") = ", result[0]['output'])

    print('Continuer : ', end="")
    continuer = int(input())