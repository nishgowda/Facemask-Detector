/**
 * @file execute.h
 * @author Nish Gowda 2020
 * 
 * Executes mask detection functions given cascade filters
 */ 


#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include "facemask.h"

using namespace cv;

/**
 * executes camera mask detection, checks if the arguments are correct
 * @param args the command line arguments passed in by the data file
 * @param len the number of arguments
 * @return 1 on success and 0 on failure
 */ 
int executeCameraMask(char **args, int len) {
    // must be 4 locations passed in for each cascade fileter
    if (len < 5) {
        perror("Not enough arguments");
        return 0;
    } else if (len > 5) {
        perror("Too many arguments specified");
        return 0;
    } else {
        int bwThreshold = 80;
        HersheyFonts font = FONT_HERSHEY_SIMPLEX;
        Point p1;
        p1.x = 30;
        p1.y = 30;
        Cascades cas;
        // set the cascade date for each command line argument
        cas.faceCascade = args[1];
        cas.eyeCascade = args[2];
        cas.mouthCascade = args[3];
        cas.upperBodyCascade = args[4];
        int thickness = 2;
        int fontScale = 1;
        Facemask mask;
        // set cascades in mask
        mask.setCascades(cas);
        // execute detectMasks with filters
        mask.detectMasks(bwThreshold, p1, thickness, fontScale, font);
    }
    return 1;
}