// ウェーブレット縮退を利用したノイズ除去

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

#define PI 3.14159265358979323846264338
//乱数
unsigned long xor128(){
  static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
  unsigned long t;
  t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}
//[0,1)の一様乱数
double frand(){
  return xor128()%10000000/static_cast<double>(10000000);
}
//正規乱数
double normal_rand(double mu, double sigma2){
  double sigma = sqrt(sigma2);
  double u1 = frand(), u2 = frand();
  double z1 = sqrt(-2*log(u1)) * cos(2*PI*u2);
  //double z2 = sqrt(-2*log(u1)) * sin(2*PI*u2);
  return mu + sigma*z1;
}



//1次元離散高速ウェーブレット変換・逆変換
class FWT {
  unsigned int L; //1次元信号の長さ
  unsigned int K; //数列p_kの長さ

public:
  
  FWT(int L_,
      int K_){
    L = L_;
    K = K_;
  }

  void fwt1d(const vector<double>& s0,
             const vector<double>& p,
             const vector<double>& q,
             vector<double>& s1,
             vector<double>& w1){

    for(size_t k=0; k<L/2; k++){
      s1[k] = 0.0;
      w1[k] = 0.0;

      for(size_t n=0; n<K; n++){
        size_t idx = (n+2*k)%L;
        s1[k] += p[n] * s0[idx];
        w1[k] += q[n] * s0[idx];
      }
    }

  }

  void ifwt1d(const vector<double>& s1,
              const vector<double>& w1,
              const vector<double>& p,
              const vector<double>& q,
              vector<double>& s0){

    unsigned int ofs = max(static_cast<unsigned int>(1024), L/2);

    for(size_t n=0; n<L/2; n++){
      s0[2*n+1] = 0.0;
      s0[2*n] = 0.0;
      
      for(size_t k=0; k<K/2; k++){
        size_t idx = (n-k+ofs)%(L/2);
        s0[2*n+1] += p[2*k+1] * s1[idx] + q[2*k+1] * w1[idx];
        s0[2*n] += p[2*k] * s1[idx] + q[2*k] * w1[idx];
      }
    }
  }
};


int main(){

  int L = 1024;
  int K = 4;

  vector<double> s0(L); //入力信号
  vector<double> sig(L); //元信号
  vector<double> s1(L);
  vector<double> w1(L);

  vector<double> p(K); //ドベシィの数列
  //K=4
  p[0] = 0.482962913145;
  p[1] = 0.836516303738;
  p[2] = 0.224143868042;
  p[3] = -0.129409522551;
  vector<double> q(K);
  //p_kからq_kを生成
  for(int i=0; i<K; i++){
    q[i] = pow(-1.0, static_cast<double>(i)) * p[K-i-1];
  }

  //ノイズの標準偏差
  double sigma = 1.0;


  //レベルJまで展開(2^J<=M)
  int J = 10;
  vector<double> coef(L); //展開係数
  vector<double> noise(L); //乱数列
  
  //ドップラー信号sigの生成
  for(int i=0; i<L; i++){
    double t = (i+1)/static_cast<double>(L);
    sig[i] = 40.0 * sqrt(t * (1-t)) * sin((2.2*PI) / (t+0.08));
  }

  //ノイズの生成
  for(int i=0; i<L; i++){
    noise[i] = normal_rand(0.0, sigma*sigma);
  }

  //ノイズありドップラー信号s0
  for(int i=0; i<L; i++){
    s0[i] = sig[i] + noise[i];
  }

  //展開係数保持配列
  for(int i=0; i<L; i++){
    coef[i] = s0[i];
  }

  
  unsigned int s_len = L;
  //レベル1からレベルJまで高速wavelet変換
  for(int j=1; j<=J; j++){
    FWT fwt(s_len, K);
    fwt.fwt1d(coef, p, q, s1, w1);

    s_len /= 2;

    for(int i=0; i<s_len; i++){
      coef[i] = s1[i];
      coef[i+s_len] = w1[i];
    }

  }


  //ウェーブレット縮退
  double threshold = sigma * sqrt(2.0 * log(L)); //ノイズ除去のためのしきい値
  for(int i=0; i<L; i++){
    if(fabs(coef[i]) < threshold){
      coef[i] = 0.0;
    }
  }

  //再構成
  for(int j=J; j>0; j--){
    FWT fwt(s_len*2, K);
    vector<double> w;
    for(int i=s_len; i<L; i++) w.push_back(coef[i]);
    fwt.ifwt1d(coef, w, p, q, s1);

    s_len *= 2;

    for(int i=0; i<s_len; i++){
      coef[i] = s1[i];
    }
  }


  //信号の出力
  ofstream fsig("signal.txt");
  ofstream fdenoise("denoise.txt");
  for(int i=0; i<L; i++){
    fsig << s0[i] << endl;
    fdenoise << coef[i] << endl;
  }


  return 0;
}
