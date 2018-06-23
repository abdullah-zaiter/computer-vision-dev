#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define MIN_B_B 0
#define MAX_B_B 255

#define MIN_G_B 0
#define MAX_G_B 50

#define MIN_R_B 24
#define MAX_R_B 46


#define MIN_B_G 41
#define MAX_B_G 57

#define MIN_G_G 0
#define MAX_G_G 255

#define MIN_R_G 00
#define MAX_R_G 65


#define MIN_B_R 38
#define MAX_B_R 61

#define MIN_G_R 35
#define MAX_G_R 56

#define MIN_R_R 0 
#define MAX_R_R 255


using namespace cv;
using namespace std;


Mat image1, imgOriginal;

Mat translateImg(Mat &img, int offsetx, int offsety){
    Mat trans_mat = (Mat_<double>(2,3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img,img,trans_mat,img.size());
    return trans_mat;
}

int main()
{
  
  imgOriginal = imread("calib1.jpg");
  namedWindow("Original", WINDOW_NORMAL);
  imshow("Original", imgOriginal);
  resizeWindow("Original", 600, 600);
  Mat imgThresholded, modified;
  inRange(imgOriginal, Scalar(0, 0, 0), Scalar(0, 0, 0), imgThresholded);
  inRange(imgOriginal, Scalar(0, 0, 0), Scalar(0, 0, 0), modified);
  namedWindow("Thresholded Image", WINDOW_NORMAL);
  resizeWindow("Thresholded Image", 600, 450);
  namedWindow("Modified", WINDOW_NORMAL);
  resizeWindow("Modified", 600, 450);

  while (true)
  {
    switch(waitKey(30)){
      case 'g':
        inRange(imgOriginal, Scalar(MIN_B_G, MIN_G_G, MIN_R_G), Scalar(MAX_B_G, MAX_G_G, MAX_R_G), imgThresholded);
        medianBlur(imgThresholded, imgThresholded, 9);
        break;
      case 'b':
        inRange(imgOriginal, Scalar(MIN_B_B, MIN_G_B, MIN_R_B), Scalar(MAX_B_B, MAX_G_B, MAX_R_B), imgThresholded);
        medianBlur(imgThresholded, imgThresholded, 9);
        break;
      case 'r':
        inRange(imgOriginal, Scalar(MIN_B_R, MIN_G_R, MIN_R_R), Scalar(MAX_B_R, MAX_G_R, MAX_R_R), imgThresholded);
        medianBlur(imgThresholded, imgThresholded, 9);
        break;
      case 't':
      {
        double angle = -90;
         // get rotation matrix for rotating the image around its center in pixel coordinates
        Point2f center((imgThresholded.cols-1)/2.0, (imgThresholded.rows-1)/2.0);
        Mat rot = getRotationMatrix2D(center, angle, 1.0);
        // determine bounding rectangle, center not relevant
        Rect2f bbox = RotatedRect(Point2f(), imgThresholded.size(), angle).boundingRect2f();
         // adjust transformation matrix
        rot.at<double>(0,2) += bbox.width/2.0 - imgThresholded.cols/2.0;
        rot.at<double>(1,2) += bbox.height/2.0 - imgThresholded.rows/2.0;
        warpAffine(imgThresholded, modified, rot, bbox.size());
        break;
      }
      case 'f':
        modified = translateImg(modified, 0, -10);
      default:
        break;
    }


    imshow("Thresholded Image", imgThresholded);   
    imshow("Modified", modified);   
    
    if (waitKey(30) == 27)
    {
      cout << "esc key is pressed by user" << endl;
      break; 
    }
  }

  return 0;
}