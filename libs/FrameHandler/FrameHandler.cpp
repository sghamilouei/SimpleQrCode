//
// Created by sgham on 5/29/2025.
//

#include "FrameHandler.h"

using namespace cv;
using namespace std;

FrameHandler::FrameHandler() {
    cap.open(0);
    if (!cap.isOpened()) {
        cout<< "Error: Cannot open camera!" << endl;
        return;
    }
    
    current_width = (int)cap.get(CAP_PROP_FRAME_WIDTH);
    current_height = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
    
}

FrameHandler::~FrameHandler() {
    if (cap.isOpened()) {
        cap.release();
    }
}

Mat FrameHandler::getFrame() {
    Mat frame;
    cap >> frame;
    return frame;
}

void FrameHandler::adjustFrameSize(Mat& frame) {
    Rect subject_area = detectSubject(frame);
    
    if (subject_area.width > 0 && subject_area.height > 0) {
       
        rectangle(frame, subject_area, Scalar(0, 255, 0), 2);
        
        String info = "Subject: " + to_string(subject_area.width) + "x" + to_string(subject_area.height);
        putText(frame, info, Point(subject_area.x, subject_area.y - 10), 
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
        
        
        Point center(subject_area.x + subject_area.width / 2, 
                    subject_area.y + subject_area.height / 2);
        circle(frame, center, 5, Scalar(255, 0, 0), -1);
    }
}

Rect FrameHandler::detectSubject(Mat& frame) {
    Mat gray, edges;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    GaussianBlur(gray, gray, Size(5, 5), 0);
   
    Canny(gray, edges, 50, 150);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(edges, edges, MORPH_CLOSE, kernel);
    
    findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    if (contours.empty()) {
        return Rect(0, 0, 0, 0);
    }
   
    double maxArea = 0;
    int maxAreaIdx = 0;
    double minArea = (frame.rows * frame.cols) * 0.01; 
    
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        
        if (area > minArea && area < (frame.rows * frame.cols) * 0.8) {
            if (area > maxArea) {
                maxArea = area;
                maxAreaIdx = i;
            }
        }
    }
    
    if (maxArea > 0) {
      
        Rect boundingRect = cv::boundingRect(contours[maxAreaIdx]);
        
        int marginX = boundingRect.width * 0.1;  
        int marginY = boundingRect.height * 0.1; 
        
        boundingRect.x = max(0, boundingRect.x - marginX);
        boundingRect.y = max(0, boundingRect.y - marginY);
        boundingRect.width = min(frame.cols - boundingRect.x, boundingRect.width + 2 * marginX);
        boundingRect.height = min(frame.rows - boundingRect.y, boundingRect.height + 2 * marginY);
        
        return boundingRect;
    }
    
    return Rect(0, 0, 0, 0);
}

Size FrameHandler::calculateNewSize(Rect subject_area) {
  
    if (subject_area.width <= 0 || subject_area.height <= 0) {
        return Size(current_width, current_height);
    }
    
    double aspect_ratio = (double)subject_area.width / subject_area.height;
    
    int padding_factor = 2; 
    int new_width = subject_area.width * padding_factor;
    int new_height = subject_area.height * padding_factor;
    
    new_width = max(320, min(1920, new_width));
    new_height = max(240, min(1080, new_height));
    
    if ((double)new_width / new_height != aspect_ratio) {
        if (new_width > new_height * aspect_ratio) {
            new_width = (int)(new_height * aspect_ratio);
        } else {
            new_height = (int)(new_width / aspect_ratio);
        }
    }
    
    return Size(new_width, new_height);
}
