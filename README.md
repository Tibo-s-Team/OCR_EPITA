# OCR_EPITA
This is our OCR school project at EPITA

## Getting Started
After cloning you can launch the Makfile for the main.c code 
or use the Python scripts for the Neural Network

### Prerequisites
- gcc (C99)
- Python 3


## Running the tests
Python: 
- Xor: Use XOR script
- Grayscale: Use the Otsu: PaintGray function


C:
- run `make` and execute the program with the desired arguments using `./TIBO [-args] files`.

### arguments

- -g : grayscaling process only
- -b : binarization process only
- -l : linewise text segmentation only
- -w : wordwise text segmentation only (by default)

## File Architecture

```
.
├── images
├── Python
│   └── Python source files
├── src
│   └── C source files (.c and headers)
└── tests
    ├── images
    │   ├── All the images used to test our algorithms on
    └── scripts
        └── All the scripts used to run certain parts of the algorithm
```


## Project Avancement Recap
*how much have we done? what is left to be done?*

### What have we done 
	-Grayscale
	-Neural Network (Xor and a bit of images)
	-Segmentation
	-Image loading

### What we have to rework
	-Neural Network for Images
	-Segmentation (letters are not yet recognized)
	-Otsu
	-Better CLS

### What we have to do
	-Image Processing 
	-Interface
	-Neural Network
	-Full conversion in C

## Authors

* [**DESMARAIS Lowen**](https://github.com/Epita-work-Lowen)
* [**DREVET FLorian**](https://github.com/FlorianDrevet)
* [**BARBAROUX Jean**](https://github.com/Abrakor)
* [**DUBOIN Léo**](https://github.com/d4ilyrun)
