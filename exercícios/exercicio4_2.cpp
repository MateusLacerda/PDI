#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat imagem;
  int largura, altura;
  int n;  
  CvPoint p;

  imagem = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

  largura = imagem.size().width;
  altura = imagem.size().height;

  // pintando a borda de 255 para conectar as bolhas das bordas
  for (int x = 0; x < altura ; x++){
    for (int y = 0; y < largura ; y++){
      if (x == 0 || y == 0 || x == altura-1 || y == largura-1){
        imagem.at<uchar>(x,y) = 255;
      }
    }
  }

  //pintando o fundo de 10
  p.x = 0;
  p.y = 0;
  floodFill(imagem, p, 0);
  floodFill(imagem, p, 10);

  imshow("sem bolhas nas bordas",imagem);

  //rotulando os objetos
  n = 10;
  for (int x = 0; x < altura ; x++){
    for (int y = 0; y < largura ; y++){
      if ( imagem.at<uchar>(x,y) == 255 ){
        //achou objeto
        n = n + 10;
        p.x = y;
        p.y = x;
        floodFill(imagem, p, n);
      }
    }
  }

  printf("Número de objetos=%d\n", (n-10)/10);

  imshow("rotulados", imagem);

  //verificando se há algum 0 (furo) e apagando o objeto com furo
  for (int x = 0; x < altura ; x++){
    for (int y = 0; y < largura ; y++){
      if ( imagem.at<uchar>(x,y) == 0 ){   
        if (imagem.at<uchar>(x,y-1) != 10){
          //imagem.at<uchar>(x,y) = 10;
          p.x = y-1;
          p.y = x;
          floodFill(imagem, p, 10);
          p.x = y;
          p.y = x;
          floodFill(imagem, p, 10);
        }                
      }
    }
  }
  
  imshow("Bolhas sem furo",imagem);
  waitKey();
  return 0;

}
