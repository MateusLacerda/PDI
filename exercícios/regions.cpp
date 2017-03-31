#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char** ){
	Mat imagem;
	int x,y,x1,y1,x2,y2, temp;
	char continuar = 's';

	while (continuar=='s'){

		imagem = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
		if (!imagem.data){
			cout << "Imagem não abriu\n";
		}

		cout << "Insira os valores da coordenada do ponto 1 (x1,y1): ";
		cin >> x1;
		cout <<"Agora y1: ";
		cin >> y1;
		cout << "Agora insira os valores da coordenada do ponto 2 (x2,y2): ";
		cin >> x2;
		cout << "Agora y2: ";
		cin >> y2;
		cout << "\n";

		// fazer com que o ponto 1 esteja sempre mais a esquerda e mais a cima do ponto 2

		if (x1>x2){
			temp = x1;
			x1 = x2;
			x2 = temp;
		}

		if (y1>y2){
			temp = y1;
			y1 = y2;
			y2 = temp;
		}


		namedWindow("Janela", WINDOW_AUTOSIZE);

		for (x=x1; x<=x2;x++){
			for (y=y1; y<=y2; y++){
				imagem.at<uchar>(x,y) = 255 - imagem.at<uchar>(x,y);
			}
		}
		imshow("Janela", imagem);	
		waitKey();
		destroyWindow("Janela");

		cout << "Quer continuar? (s/n) ";
		cin >> continuar;
	}
	return 0;	
}