#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//logsumexp
// 参考：http://cl.aist-nara.ac.jp/index.php?plugin=attach&refer=DMLA%2F2005%C7%AF%C5%D9&openfile=2005-06-07.pdf

// log( exp(x) + exp(y) )のオーバーフロー回避計算テクニック
double logsumexp2(const double& x, const double& y){
  double mx = x, mn = y;
  if(x<y) swap(mx, mn);
  if(mx-mn > 50.0) return mx;
  return mn + log(1.0 + exp(mx-mn));
}
// log( exp(x1) + ... + exp(xn) )のオーバーフロー回避計算テクニック
double logsumexp(const vector<double>& v){
  if(v.size() == 0) return 0;
  double ret = v[0];
  for(size_t i=1; i<v.size(); i++){
    ret = logsumexp2(ret, v[i]);
  }
  return ret;
}




int main(){

  vector<double> v;
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(20);
  v.push_back(300);
  v.push_back(4000);
  v.push_back(50000);

  printf("%.10lf\n", logsumexp(v)); //50000.0000000000
  printf("%.10lf\n", log(exp(2)+exp(3)+exp(4)+exp(5)+exp(20)+exp(300)+exp(4000)+exp(50000))); //inf

  return 0;
}
