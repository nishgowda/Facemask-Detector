# Facemask-Detector

## How?
Mask wearing has become a contigent part of life with the rise of Covid-19. The goal of this program is to detect if a person is wearing a mask in their camera feed. Please note that the results are not quite perfect yet and further testing and experimentation are required.

This project uses OpenCV as the building block to proccess video. It also uses a handful of Cascade filters to detect a person's face and mouth to predict if they are wearing a mask. If you would like to run this code yourself, you can copy git clone this repo and test it out. Make sure you have OpenCV installed as well as the valid Cascade filters.

### Directory Structure
**/src** - Source code files main.cpp exists here

**/include** - Headerfiles are located here. 
Contains Facemask class and following functions.

**/build** - Executables and several CMakeList data to integrate with VSCode

### Running the code
To make life easier just run the python script with the name of a textfile that has the location of the following cascade filters: 

    - haarcascade_frontalface_default.xml
    - haarcascade_eye.xml
    - haarcascade_mcs_mouth.xml
    - haarcascade_upperbody.xml
For example the following would be valid:
```
python3 source.py data.txt
```
Side Note: You must have a working video camera also.