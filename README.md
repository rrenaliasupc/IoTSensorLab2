# IoTSensorLab2: ESP32 gyroscope gesture Edge AI Project ##
## Authors:
### Pedro Matheus Figueredo Cristaldo ###
### Ricard Renalias Zueras ###

## Description ##
This project uses an ESP32-S3-Touch-LCD-2 development board to read data from a gyroscope sensor (MPU6050) and classify gestures using a pre-trained Edge AI model. The classified gestures are then displayed on the LCD screen of the development board.

For training the model, we used a Jupyter Notebook with TensorFlow and Keras. The trained model was converted to TensorFlow Lite format and then to a C array using the `xxd` tool for deployment on the ESP32.

## Content ##
```
IoTSensorLab2/
├── ESP32Arduino
│   ├── lab2_data_capture      # Sketch for capturing gyroscope data
│   └── lab2_inferencetest     # Sketch for performing inference using the 
├── ModelTraining/
│   └── model_training.ipynb   # Jupyter Notebook for model training and 
└── README.md                  # This file
```

## data capture and Inference##

Implementation of this part has been done in two separate Arduino sketches:

1. `lab2_data_capture.ino`: This sketch captures gyroscope data and sends it over the serial port. It is used to collect data for training the model.
2. `lab2_inferencetest.ino`: This sketch loads the pre-trained model and performs inference on the gyroscope data, displaying the results on the LCD screen.

### Hardware Requirements ###
- ESP32-S3-Touch-LCD-2 development board
- USB-C cable for programming and power

### Software Requirements ###
- Arduino IDE
- ESP32 board support package for Arduino IDE
- Libraries:
  - Adafruit_GFX
  - EloquentTinyML (https://github.com/eloquentarduino/EloquentTinyML)


## Model Training ##
The model training was performed using a Jupyter Notebook (`model_training.ipynb`) located in the `ModelTraining` directory. The notebook includes steps for data preprocessing, model architecture definition, training, evaluation, and conversion to TensorFlow Lite format.

The notebook allows to:
- explore the data
- visualize it
- normalize
- generate the model and understand the model's performance.
- convert the model to TensorFlow Lite format
- convert the TensorFlow Lite model to a C array using the `xxd` tool for deployment on the ESP32.
- Generate a model folder with the contents needed for inference on the ESP32 and test if the model is working properly using TestData.

