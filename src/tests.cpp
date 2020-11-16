/**
 * @file tests.cpp
 * @author Nish Gowda
 * 
 * tests executeCameraMask to ensure it returns 1
 */

#include <iostream>
#include "../include/execute.h"
#include <assert.h>

int main(int argc, char **argv) {
    assert(executeCameraMask(argv, argc) == 1);
    return 0;
}
