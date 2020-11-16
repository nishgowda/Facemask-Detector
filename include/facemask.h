/**
 * @file facemask.h
 * @author Nish Gowda 
 * facemask headerfile using opencv to detect if a person is
 * wearing a mask.
 */

#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

using namespace cv;
#define WEARING "Thank you for wearing a mask!"
#define NOTWEARING "Please wear a mask!"
#define WEARINGCOLOR Scalar(255, 255, 255)
#define NOTWEARINGCOLOR Scalar(0, 0, 255)

// Cascade struct contains the location of the Cascade Filters
typedef struct cascades {
    String eyeCascade;
    String faceCascade;
    String mouthCascade;
    String upperBodyCascade;
} Cascades;

class Facemask {

    private:
        Cascades cascade;
    public:
        Facemask() {
            cascade.eyeCascade = "";
            cascade.faceCascade = "";
            cascade.mouthCascade = "";
            cascade.upperBodyCascade = "";
        }
        ~Facemask() {
            cascade.eyeCascade = "";
            cascade.faceCascade = "";
            cascade.mouthCascade = "";
            cascade.upperBodyCascade = "";
        }
        void setCascades(Cascades cas);
        int detectMasks(int bwThreshold, Point p, int thickness, 
                        int fontScale, HersheyFonts font);
};

/**
 * sets the cascades fields to the passed in cascades fields
 * @param cas the cascade created in main
 */ 
void Facemask::setCascades(Cascades cas) {
    cascade.eyeCascade = cas.eyeCascade;
    cascade.faceCascade = cas.faceCascade;
    cascade.mouthCascade = cas.mouthCascade;
    cascade.upperBodyCascade = cas.upperBodyCascade;
}
/**
 * uses opencv to detect persons face and determines if the user is wearing
 * a mask.
 * @param bwThreshold the treshold value to create a black and white cascade
 * of a frame
 * @param p point where the message will display on the gui
 * @param thickness line thickness of message
 * @param fontScale the font size
 * @param font type of font
 */ 
int Facemask::detectMasks(int bwThreshold, Point p, int thickness, 
                        int fontScale, HersheyFonts font) {
    double scale = 1;
    VideoCapture capture;
    Mat frame, image;
    Mat img;
    CascadeClassifier cascadeFace, cascadeEye, cascadeMouth, cascadeUpperBody;
    // load all cascade filters from the cascade after set
    cascadeFace.load(cascade.faceCascade);
    cascadeEye.load(cascade.eyeCascade);
    cascadeMouth.load(cascade.mouthCascade);
    cascadeUpperBody.load(cascade.upperBodyCascade);
    capture.open(0);
    Mat gray, blackWhite;
    Scalar color = Scalar(255, 255, 255);
    if (capture.isOpened())
    {
        std::cout << "Face Detection Starting\n Press q or Q to quit" << std::endl;
        while (1)
        {
            capture.read(frame);  // read in the frame and image 
            capture.read(image);
            flip(image, image, 1); // flip the image by 1
            cvtColor(image, gray, COLOR_BGR2GRAY); // filter to a gray scale
            threshold(gray, blackWhite, bwThreshold, 255, THRESH_BINARY); // filter to black and white
            std::vector<Rect> faces, facesBW; 
            cascadeFace.detectMultiScale(gray, faces, 1.1, 4); // face detection
            cascadeFace.detectMultiScale(blackWhite, facesBW, 1.1, 4); // face detection for black and white
            
            if (faces.size() == 0 && facesBW.size() == 0)
                putText(image, "No face found", p, font, fontScale, NOTWEARINGCOLOR, thickness, LINE_AA);
            
            // if a white mask and gray image face can't be predicted
            else if (faces.size() == 0 && facesBW.size() == 1)
                putText(image, WEARING, p, font, fontScale, WEARINGCOLOR, thickness, LINE_AA);
            else {
                // detected a face so now we can iterate through the frame
                for (size_t i = 0; i < faces.size(); i ++) {
                    Rect r = faces[i];
                    std::vector<Rect> mouthRect;
                    Point p1, p2;
                    p1.x = r.x;
                    p1.y = r.y;
                    p2.x = r.x + r.width;
                    p2.y = r.y + r.height;
                    // draws a rectangle around face
                    rectangle(image, p1, p2, color, 2);
                    cascadeMouth.detectMultiScale(gray, mouthRect, 1.5, 5);
                    // mouth was not detected but we already detected a face so person must be wearing a mask
                    if (mouthRect.size() == 0)
                        putText(image, WEARING, p, font, fontScale, WEARINGCOLOR, thickness, LINE_8);
                    else {
                        for (size_t j = 0; j < mouthRect.size(); j ++) {
                            Rect m = mouthRect[j];
                            // mouth was detected therefore person is not wearing a mask
                            if (r.y < m.y < r.y + r.height){
                                putText(image, NOTWEARING, p, font, fontScale, NOTWEARINGCOLOR, thickness, LINE_8);
                                break;
                            }
                        }
                    }
                }
            }
            imshow("Face Mask Detection", image);
            char c = (char)waitKey(30);
            if (c == 27 || c == 'q' || c == 'Q'){
                std::cout << "Quiting" << std::endl;
                break;
            }
        }
        // close windows
        capture.release();
        destroyAllWindows();
    }
    else {
        std::cout << "Could not open camera" << std::endl;
        return 0;
    }
    return 1;
}