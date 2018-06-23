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

Mat image1, imgOriginal;

long long unsigned int  getMicrotime(){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main()
{


  long long unsigned int tempo_atual=0, tempo_aux=0;
  double dt=0,frequencia = 1.234282;

  imgOriginal = imread("calib1.jpg");
  while (true)
  {
    tempo_atual = getMicrotime();
    dt = tempo_atual - tempo_aux;
    dt /= 1000000;
    frequencia = (1/dt); 
    cout << "frequencia = " << setprecision(8) <<frequencia << endl;
    cout << "dt = " << dt << endl;
    cvtColor(imgOriginal,image1,CV_BGR2Lab);
    medianBlur(image1, image1, 3);
    tempo_aux = tempo_atual;
  }

  return 0;
}