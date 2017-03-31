#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char** ){
	Mat imagem, imagem2;
	int x,y;

	imagem = imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
	imagem2 = imagem.clone();

	// colocando o quarto quadrante no segundo
	for (x = 1; x<=128;x++){
		for (y = 1; y<=128;y++){
			imagem2.at<uchar>(x,y) = imagem.at<uchar>(x + 128,y + 128);
		}
	}
	//colocando o segundo quadrante no quarto
	for (x = 129; x<=256;x++){
		for (y = 129; y<=256;y++){
			imagem2.at<uchar>(x,y) = imagem.at<uchar>(x - 128,y - 128);
		}
	}
	//colocando o primeiro quadrante no terceiro
	for (x = 129; x<256;x++){
		for (y = 1; y<=128;y++){
			imagem2.at<uchar>(x,y) = imagem.at<uchar>(x - 128, y + 128);
		}
	}
	//colocando o terceiro quadrante no primeiro
	for (x = 1; x<=128;x++){
		for (y = 129; y<=256;y++){
			imagem2.at<uchar>(x,y) = imagem.at<uchar>(x + 128,y - 128);
		}
	}

	namedWindow("janela",WINDOW_AUTOSIZE);
	imshow("janela", imagem2);
	waitKey();
	return 0;
}
