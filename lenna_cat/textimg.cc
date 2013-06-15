// Usage: ./textimg img_file text_file > output.txt
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


int num_byte(const char& cc){
  unsigned char c = static_cast<unsigned char>(cc);
  if(c <= 0x7f) return 1;
  if(0xc0 <= c && c <= 0xcf) return 2;
  if(0xd0 <= c && c <= 0xdf) return 2;
  if(0xe0 <= c && c <= 0xef) return 3;
  if(0xf0 <= c && c <= 0xf7) return 4;
  if(0xf8 <= c && c <= 0xfb) return 5;
  return 6;
}
bool isHankaku(const string& cc){
  int n = cc.length();
  if(n < 3 || n > 3) return true;

  unsigned char c0 = static_cast<unsigned char>(cc[0]);
  unsigned char c1 = static_cast<unsigned char>(cc[1]);
  unsigned char c2 = static_cast<unsigned char>(cc[2]);

  //半角カタカナ
  if(c0 == 0xef){
    if(c1 == 0xbd){
      if(0xa1 <= c2 && c2 <= 0xbf) return true;
    }
    if(c1 == 0xbe){
      if(0x80 <= c2 && c2 <= 0x9f) return true;
    }
  }
  return false;
}


int main(int argc, char** argv){
  //元画像をグレイスケールで読み込み
  Mat srcImg = imread(argv[1], 0);
  if(srcImg.empty()) return -1;
  Mat dstImg;

  //UTF8テキストを読み込む
  ifstream text(argv[2]);
  if(!text) return -1;

  //1文字ずつに区切ってtext_utf8に入れておく
  vector<string> text_utf8;
  string line;
  while(text >> line){
    for(size_t i=0; i<line.length();){
      int n = num_byte(line[i]);
      text_utf8.push_back(line.substr(i,n));
      i += n;
    }
  }

  //画像の2値化
  threshold(srcImg, dstImg, 0, 255, THRESH_BINARY | THRESH_OTSU);

  //画素ごとにテキストを割り当てる
  int idx = 0;
  int H = dstImg.rows, W = dstImg.cols;
  for(int y=0; y<H; y++){
    for(int x=0; x<W; x++){
      int intensity = dstImg.at<unsigned char>(y, x);

      if(intensity != 0){ //画素が白いとき
        cout << "　";
      }else{ //画素が黒いとき
        if(text_utf8.size() <= idx) idx = 0;

        cout << text_utf8[idx];
        if(isHankaku(text_utf8[idx])){
          cout << " ";
        }
        idx++;
      }
    }
    cout << endl;
  }



  //namedWindow("image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
  //imshow("image", dstImg);
  //waitKey(0);


  return 0;
}
