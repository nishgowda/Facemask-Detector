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
    // tests for corerect command line args
    assert(executeCameraMask(argv, argc) == 1);

    // tests for incorrect command line args
    assert(executeCameraMask(argv, 1) == 0);
    return 0;
}
