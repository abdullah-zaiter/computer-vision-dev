#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include<iomanip>

using namespace cv;
using namespace std;

long long unsigned int  getMicrotime(){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(int argc, char** argv ){

	if(argc != 2){
		cout << "Error!!" << endl;
	}

	// It reads initially as BGR
	Mat M = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Mat P(M.rows, M.cols, CV_8UC3);	
	
    if ( !M.data ){
        printf("No image data \n");
        return -1;
    }
	
	long long unsigned int tempo_atual=0, tempo_aux=0;
	double dt=0,frequencia = 1.234282;	
	
	// 3 Channels expected, BGR
	cout << M.channels() << endl;

	// Show initial image
    //namedWindow("Original Image", WINDOW_NORMAL );
    //imshow("Original Image", M); 

	// Does the image conversion from BGR to HSV
	// cvtColor(M, M, CV_BGR2Lab);


	while(1){
	// Does the RGB normalization
		tempo_atual = getMicrotime();
		dt = tempo_atual - tempo_aux;
		dt /= 1000000;
		frequencia = (1/dt); 
		cout << "frequencia = " << setprecision(8) <<frequencia << endl;
		cout << "dt = " << dt << endl;
		for(int i=0;i<M.rows;i++){
			unsigned char* m_ptr = M.ptr<uchar>(i);
			unsigned char* p_ptr = P.ptr<uchar>(i);
			for(int j=0;j<M.cols;j++){
				int sum = m_ptr[3*j] + m_ptr[3*j+1] + m_ptr[3*j+2];
				p_ptr[3*j] = (char)(((float)m_ptr[3*j]/sum)*255);
				p_ptr[3*j+1] = (char)(((float)m_ptr[3*j+1]/sum)*255);
				p_ptr[3*j+2] = (char)(((float)m_ptr[3*j+2]/sum)*255);
			};
		};
		medianBlur(M, M, 3);
		tempo_aux = tempo_atual;
	};

	//namedWindow("normalized", WINDOW_NORMAL);
	//imshow("normalized", P);
	
	
	// Initial range for calibration
   	/*int LowR = 0;
	int HighR = 255;

	int LowG = 0; 
	int HighG = 255;

	int LowB = 0;
	int HighB = 255;

	// create trackbars to make calibration easier
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	
	cvCreateTrackbar("LowR", "Control", &LowR, 255); //Red Value (0 - 255)
 	cvCreateTrackbar("HighR", "Control", &HighR, 255);

 	cvCreateTrackbar("LowG", "Control", &LowG, 255); //Green Value (0 - 255)
 	cvCreateTrackbar("HighG", "Control", &HighG, 255);

 	cvCreateTrackbar("LowB", "Control", &LowB, 255); //Blue Value (0 - 255)
 	cvCreateTrackbar("HighB", "Control", &HighB, 255);
	
	namedWindow("New", WINDOW_NORMAL );
	namedWindow("Newnormal", WINDOW_NORMAL);
	Mat thresholded, thresholdedP;
	while(1){
		inRange(M, Scalar(LowB, LowG, LowR), Scalar(HighB, HighG, HighR), thresholded);
		inRange(P, Scalar(LowB, LowG, LowR), Scalar(HighB, HighG, HighR), thresholdedP);
		imshow("New", thresholded);
		imshow("Newnormal", thresholdedP);
		if(waitKey(30)==27)
			break;
	};
	*/	
    return 0;
}
