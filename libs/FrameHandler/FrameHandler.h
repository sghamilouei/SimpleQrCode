//
// Created by sgham on 5/29/2025.
//

#ifndef FRAMEHANDLER_H
#define FRAMEHANDLER_H

// header file is written by alireza jahani 

#include <opencv2/opencv.hpp>

class FrameHandler {
public:
 
    FrameHandler();
    
    
    ~FrameHandler();
    
    cv::Mat getFrame();
    
    void adjustFrameSize(cv::Mat& frame);

private:
    cv::VideoCapture cap; 
    int current_width;    
    int current_height;   
    
    cv::Rect detectSubject(cv::Mat& frame);
    
    cv::Size calculateNewSize(cv::Rect subject_area);
};




#endif //FRAMEHANDLER_H
