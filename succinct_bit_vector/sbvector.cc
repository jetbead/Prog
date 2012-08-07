#include <iostream>
#include <vector>

using namespace std;

//簡潔ビット集合(SBitSet)と簡潔ビットベクトル(SBitVector)
// 参照：http://d.hatena.ne.jp/echizen_tm/20111210/1323541165

class SBitSet {
  typedef unsigned long long ull;
  typedef unsigned char uc;
  std::vector<ull> B_;
  std::vector<uc> r_;
  ull size_;
  bool isbuilt_;

  ull popcount64(ull x){
    x = ((x & 0xaaaaaaaaaaaaaaaaULL) >> 1) + (x & 0x5555555555555555ULL);
    x = ((x & 0xccccccccccccccccULL) >> 2) + (x & 0x3333333333333333ULL);
    x = ((x & 0xf0f0f0f0f0f0f0f0ULL) >> 4) + (x & 0x0f0f0f0f0f0f0f0fULL);
    x = ((x & 0xff00ff00ff00ff00ULL) >> 8) + (x & 0x00ff00ff00ff00ffULL);
    x = ((x & 0xffff0000ffff0000ULL) >> 16) + (x & 0x0000ffff0000ffffULL);
    x = ((x & 0xffffffff00000000ULL) >> 32) + (x & 0x00000000ffffffffULL);
    return x;
  }
  void build(){
    this->r_[0] = 0;
    if(r_.size() == 0) return;
    for(size_t i=0; i<r_.size()-1; i++){
      this->r_[i+1] = this->r_[i] + popcount64(this->B_[i]);
    }
    isbuilt_ = true;
  }
public:
  SBitSet(ull m){
    size_ = m;
    size_t n = size_ / 64;
    B_.assign(n,0x0ULL);
    r_.assign(n,0);
    isbuilt_ = false;
  }
  void set(size_t i){ //iのビットを立てる
    ull b = 0x1ULL << (i % 64);
    this->B_[i/64] |= b;
    isbuilt_ = false;
  }
  bool get(size_t i){ //iのビットが立っているかどうか
    ull m = 0x1ULL << (i % 64);
    return this->B_[i/64] & m;
  }
  int rank(size_t i){ //i以下のインデックスで立っているビット数
    if(!isbuilt_) this->build();
    ull m = -1;
    if(i % 64 < 63){
      m = (0x1ULL << (i%64+1)) - 1;
    }
    return this->r_[i/64] + popcount64(this->B_[i/64] & m);
  }
};

template<typename T>
class SBitVector {
  typedef long long ll;
  SBitSet sbset_;
  std::vector<T> values_;
  ll max_n;

public:
  SBitVector(int n):sbset_(n){
    max_n = -1;
  }
  void set(size_t i, T val){ //インデクスiに値valをセット(インデクスの小さいものからセットすること)
    if(static_cast<ll>(i)<=max_n){
      std::cerr << "error: cannot set [" << i << "] " << val << std::endl;
      return;
    }
    sbset_.set(i);
    values_.push_back(val);
    max_n = static_cast<ll>(i);
  }
  T get(size_t i){ //インデクスiの値を返す(セットされていないときは0を返す)
    if(!sbset_.get(i)){
      return 0;
    }
    return values_[sbset_.rank(i)-1];
  }
};

int main(){
  SBitVector<int> v(256);
  v.set(5,10);
  v.set(100,20);
  v.set(180,30);

  cout << "5:" << v.get(5) << endl;
  cout << "100:" << v.get(100) << endl;
  cout << "180:" << v.get(180) << endl;
  cout << "200:" << v.get(200) << endl;

  /*//出力
     5:10
     100:20
     180:30
     200:0
  */
  return 0;
}

