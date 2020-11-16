/**
 * @file main.cpp
 * @author Nish Gowda
 * takes in the locations of Cascade filters and process them through
 * setCascades and detectMasks
 */ 

#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include "../include/facemask.h"
#include <assert.h>

using namespace cv;

int main(int argc, char **argv) {
    // must be 4 locations passed in for each cascade fileter
    if (argc < 5)
    {
        perror("Not enough args specified");
        exit(1);
    }
    else if (argc > 5)
    {
        perror("Too many arguments specified");
        exit(1);
    }
    else
    {
        int bwThreshold = 80;
        HersheyFonts font = FONT_HERSHEY_SIMPLEX;
        Point p1;
        p1.x = 30;
        p1.y = 30;
        Cascades cas;
        // set the cascade date for each command line argument
        cas.faceCascade = argv[1];
        cas.eyeCascade = argv[2];
        cas.mouthCascade = argv[3];
        cas.upperBodyCascade = argv[4];
        int thickness = 2;
        int fontScale = 1;
        Facemask mask;
        // set cascades in mask 
        mask.setCascades(cas);
        // execute detectMasks with filters
        assert(mask.detectMasks(bwThreshold, p1, thickness, fontScale, font));
    }
    return 0;
}

