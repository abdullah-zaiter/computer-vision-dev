#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<iomanip>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


#define MIN_L_B 0
#define MAX_L_B 255

#define MIN_A_B 0
#define MAX_A_B 50

#define MIN_B_B 0
#define MAX_B_B 175


#define MIN_L_G 0
#define MAX_L_G 255

#define MIN_A_G 0
#define MAX_A_G 150

#define MIN_B_G 00
#define MAX_B_G 50


#define MIN_L_R 0
#define MAX_L_R 255

#define MIN_A_R 150
#define MAX_A_R 255

#define MIN_B_R 0 
#define MAX_B_R 75



long long unsigned int  getMicrotime(){
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void show(Mat image, String im)
{
  namedWindow(im, WINDOW_NORMAL);
  imshow(im, image);
  resizeWindow(im, 600, 600);
}

Mat sobelBorder(Mat image)
{
  Mat image_gray, image_src;
  image_src = image;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  cvtColor( image_src, image_gray, CV_BGR2GRAY );

  Mat grad_x, grad_y, grad;
  Mat abs_grad_x, abs_grad_y;

  Sobel( image_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );

  Sobel( image_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_y, abs_grad_y );
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

  show(grad, "imagem 2");
  return grad;
}

Mat masking(char color, vector<Mat> channels)
{
  Mat result1, result2;
  cout << "debugg" << color << endl;  
  
  switch(color)
  {
    case 'r':
      inRange(channels[1], MIN_A_R, MAX_A_R, result1);
      inRange(channels[2], MIN_B_R, MAX_B_R, result2);
      channels[1] = result1;
      channels[2] = result2;
      merge(channels,result1);
      medianBlur(result1, result1, 3);
      show(result1,"imagem 1");
      break;
    case 'b':
      inRange(channels[1], MIN_A_B, MAX_A_B, result1);
      inRange(channels[2], MIN_B_B, MAX_B_B, result2);
      channels[1] = result1;
      channels[2] = result2;
      merge(channels,result1);
      medianBlur(result1, result1, 3);
      show(result1,"imagem 1");
      break;
    case 'g':
      inRange(channels[1], MIN_A_G, MAX_A_G, result1);
      inRange(channels[2], MIN_B_G, MAX_B_G, result2);
      channels[1] = result1;
      channels[2] = result2;
      merge(channels,result1);
      medianBlur(result1, result1, 3);
      show(result1,"imagem 1");
      break;
    default:
      break;
  }

  return result1;
}

int main()
{

  int key;
  Mat image1 ,imgOriginal;
  imgOriginal = imread("calib1.jpg");
  cvtColor(imgOriginal,image1,CV_BGR2Lab);//Converte para Cie L*a*b
  vector<Mat> channels;
  split(image1,channels);//Separa canais da imagem
  Mat result, result2;
  namedWindow("imagem ori", WINDOW_NORMAL);
  imshow("imagem ori", imgOriginal);
  resizeWindow("imagem ori", 600, 600);
  long long unsigned int tempo_atual=0, tempo_aux=0;
  double dt=0,frequencia = 1.234282;
  while (true)
  {  
    key = waitKey(30);
    switch((char)key)
    {
      case 'r':

        tempo_aux = getMicrotime();

        //inicio do agoritmo
        result = masking('r',channels);
        result = sobelBorder(result);

        //isnere o resto do algoritmo aqui
        ///
        //
        //

        tempo_atual = getMicrotime();
        dt = tempo_atual - tempo_aux;
        dt /= 1000000;
        frequencia = (1/dt); 
        cout << "frequencia = " << setprecision(8) <<frequencia << endl;
        cout << "dt = " << dt << endl;
        break;
      case 'b':
        tempo_aux = getMicrotime();

        //inicio do agoritmo

        result = masking('b',channels);
        result = sobelBorder(result);
        //isnere o resto do algoritmo aqui
        ///
        //
        //
        
        tempo_atual = getMicrotime();
        dt = tempo_atual - tempo_aux;
        dt /= 1000000;
        frequencia = (1/dt); 
        cout << "frequencia = " << setprecision(8) <<frequencia << endl;
        cout << "dt = " << dt << endl;
        break;
      case 'g':
        tempo_aux = getMicrotime();

        //inicio do agoritmo

        result = masking('g',channels);
        result = sobelBorder(result);
        //isnere o resto do algoritmo aqui
        ///
        //
        //
        
        tempo_atual = getMicrotime();
        dt = tempo_atual - tempo_aux;
        dt /= 1000000;
        frequencia = (1/dt); 
        cout << "frequencia = " << setprecision(8) <<frequencia << endl;
        cout << "dt = " << dt << endl;
        break;
      default:
        break;
    }
    key = waitKey(30);
    if (key == 27)
    {
      cout << "esc key is pressed by user" << endl;
      break; 
    }
    //waitKey(0);
  }

  return 0;
}