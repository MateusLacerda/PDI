#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 5
#define JITTER 3
#define RAIO 3

int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;

  Mat imagem, imagemBorda, imagemPontilhismo;

  int width, height;
  int x, y;

  Vec3b pixel;

  imagem= imread(argv[1],CV_LOAD_IMAGE_COLOR);

  srand(time(0));

  if(!imagem.data){
	cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=imagem.size().width;
  height=imagem.size().height;

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }
  

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }
  
  imagemPontilhismo = Mat(height, width, CV_8UC3, Scalar(255,255,255));

  random_shuffle(xrange.begin(), xrange.end());    

  for(auto i : xrange){    
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      pixel = imagem.at<Vec3b>(x,y);
      circle(imagemPontilhismo,
             cv::Point(y,x),
             RAIO,
             cv::Scalar(pixel[0],pixel[1],pixel[2]),            
             -1,
             CV_AA);
    }
  }

  // acrescentar pontos nas bordas usando o filtro de canny

  int raio2 = 8;
  for (int interacoes = 1; interacoes < 6;interacoes++){
    Canny(imagem, imagemBorda, interacoes*15, interacoes*45);    
    raio2 = raio2 - 1;
    // procurar onde há borda, e, onde encontrar, colocar um
    // ponto na imagem com pontilhismo
    for (int i = 0; i < height; ++i){
      for (int j = 0; i < width; ++i){
        if (imagemBorda.at<uchar>(i,j)>0){
          pixel = imagem.at<Vec3b>(x,y);
          circle(imagemPontilhismo,
             cv::Point(y,x),
             raio2,
             cv::Scalar(pixel[0],pixel[1],pixel[2]),
             -1,
             CV_AA);
        }
      }      
    }    
  }
  imshow("Imagem com pontilhismo e canny", imagemPontilhismo);
  imwrite("cannyPontilhismo.png", imagemPontilhismo);

  char key = (char) waitKey();
  return 0;
}