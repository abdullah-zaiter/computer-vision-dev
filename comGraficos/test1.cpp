#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<iomanip>
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

int thresh = 100;

void thresh_callback(int);
Mat image1, imgOriginal;
RNG rng(12345);

long long unsigned int  getMicrotime(){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void thresh_callback(int)
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( image1, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
  {
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
  }

  /// Show in a window
  namedWindow( "Contours", WINDOW_NORMAL );
  resizeWindow("Contours", 600, 600);
  imshow( "Contours", drawing);

}


int main()
{
  namedWindow("Control", CV_WINDOW_AUTOSIZE);
  int iLowR = 0;
  int iHighR = 255;

  int iLowG = 0; 
  int iHighG = 255;

  int iLowB = 0;
  int iHighB = 255;
  int max_thresh = 255;
  //Create trackbars in "Control" window
  cvCreateTrackbar("LowR", "Control", &iLowR, 255);
  cvCreateTrackbar("HighR", "Control", &iHighR, 255);

  cvCreateTrackbar("LowG", "Control", &iLowG, 255);
  cvCreateTrackbar("HighG", "Control", &iHighG, 255);

  cvCreateTrackbar("LowB", "Control", &iLowB, 255); 
  cvCreateTrackbar("HighB", "Control", &iHighB, 255);
  cvCreateTrackbar("Canny thresh:", "Control", &thresh, max_thresh, thresh_callback );
  
  imgOriginal = imread("calib1.jpg");
  namedWindow("Original", WINDOW_NORMAL);
  imshow("Original", imgOriginal);
  resizeWindow("Original", 600, 600);

  Size size(3,3); 

  long long unsigned int tempo_atual=0, tempo_aux=0;
  double dt=0,frequencia = 1.234282;
  while (true)
  {
    Mat imgThresholded;
    
    tempo_atual = getMicrotime();
    dt = tempo_atual - tempo_aux;
    dt /= 1000000;
    frequencia = (1/dt); 
    cout << "frequencia = " << setprecision(8) <<frequencia << endl;
    cout << "atual = " << tempo_atual << endl;
    cout << "anterior = " << tempo_aux << endl;
    cout << "dt = " << dt << endl;
    inRange(imgOriginal, Scalar(iLowB, iLowG, iLowR), Scalar(iHighB, iHighG, iHighR), imgThresholded);
    GaussianBlur(imgThresholded,image1,size,0);  
    //medianBlur(image1, image1, 3);
    adaptiveThreshold(image1, image1,255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,75,10);  
    bitwise_not(image1, image1);  
    //cvtColor(imgOriginal,image1,CV_BGR2GRAY);
    //Canny(image1,image1, thresh, thresh*2, 3);
    
    thresh_callback( 0);
    //namedWindow("Canny", WINDOW_NORMAL);
    //imshow("Canny", image1);
    //resizeWindow("Canny", 600, 600);

    namedWindow("Thresholded Image", WINDOW_NORMAL);
    imshow("Thresholded Image", imgThresholded);   
    resizeWindow("Thresholded Image", 600, 600);

    
    if (waitKey(30) == 27)
    {
        cout << "esc key is pressed by user" << endl;
      break; 
    }
    tempo_aux = tempo_atual;
  }

  return 0;
}
