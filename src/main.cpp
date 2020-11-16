/**
 * @file main.cpp
 * @author Nish Gowda
 * 
 * takes in the locations of Cascade filters and process them through
 * setCascades and detectMasks
 */ 

#include <iostream>
#include "../include/execute.h"
#include <assert.h>


int main(int argc, char **argv) {
    executeCameraMask(argv, argc);
    return 0;
}

