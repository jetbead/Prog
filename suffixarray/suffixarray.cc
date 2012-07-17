#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

//Manber and Myers(構築:O(n log^2 n))
// (プログラミングコンテストチャレンジブック第二版)
class SuffixArray;
struct SuffixArrayComp { //比較用
  SuffixArray *sa;
  SuffixArrayComp(SuffixArray *orig_sa);
  bool operator()(const int& i, const int& j) const;
};
class SuffixArray {
  int n, k;
  std::string orig_str;
  std::vector<int> rank;
  std::vector<int> tmp;
  std::vector<int> sa;
  
  void init(const std::string& str){
    orig_str = str;
    n = str.length();
    for(int i=0; i<=n; i++){
      sa[i] = i;
      rank[i] = (i<n)?str[i]:-1; //文字コード
    }
    //k文字についてソートされているところから、2k文字でソート
    for(k=1; k<=n; k*=2){
      SuffixArrayComp comp(this);
      std::sort(sa.begin(), sa.begin()+n+1, comp);

      tmp[sa[0]] = 0;
      for(int i=1; i<=n; i++){
	tmp[sa[i]] = tmp[sa[i-1]] + (_compare(sa[i-1],sa[i])?1:0);
      }
      for(int i=0; i<=n; i++){
	rank[i] = tmp[i];
      }
    }
  }
public:
  bool _compare(const int& i, const int& j) const {
    if(rank[i] != rank[j]){
      return rank[i] < rank[j];
    }else{
      int ri = (i+k<=n)?rank[i+k]:-1;
      int rj = (j+k<=n)?rank[j+k]:-1;
      return ri < rj;
    }
  }

  SuffixArray(const std::string& str):
    rank(str.length()+1),
    tmp(str.length()+1),
    sa(str.length()*2){
    init(str);
  }

  //文字列tを含むかどうか(探索O(log n))
  bool contain(const std::string& t){
    int a = 0, b = n;
    while(b-a>1){
      int c = (a+b)/2;
      if(orig_str.compare(sa[c], t.length(), t)<0){
	a = c;
      }else{
	b = c;
      }
    }
    return orig_str.compare(sa[b], t.length(), t) == 0;
  }

  //文字列tを含む位置を全列挙(探索O(log n)+列挙O(n))
  std::vector<int> indexof(const std::string& t){
    std::vector<int> ret;
    int a = 0, b = n;
    while(b-a>1){
      int c = (a+b)/2;
      if(orig_str.compare(sa[c], t.length(), t)<0){
	a = c;
      }else{
	b = c;
      }
    }
    for(int i=b; i<sa.size(); i++){
      if(orig_str.compare(sa[i], t.length(), t) == 0){
	ret.push_back(sa[i]);
      }else{
	break;
      }
    }
    return ret;
  }


  //sa配列を表示
  void show_sa(){
    for(int i=0; i<sa.size(); i++){
      std::cout << i << " : " << sa[i] << std::endl;
    }
  }

  //rank配列を表示
  void show_rank(){
    for(int i=0; i<rank.size(); i++){
      std::cout << i << " : " << rank[i] << std::endl;
    }
  }
};
SuffixArrayComp::SuffixArrayComp(SuffixArray *orig_sa){ sa = orig_sa; }
bool SuffixArrayComp::operator()(const int& i, const int& j) const { return sa->_compare(i,j); }


std::string showvec(const std::vector<int>& v){
  std::stringstream ss;
  for(int i=0; i<v.size(); i++){
    ss << v[i] << ",";
  }
  return ss.str();
}


int main(){
  //              01234567890
  SuffixArray sa("abracadabra");

  std::cout << sa.contain("a") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("a")) << std::endl;
  std::cout << sa.contain("ab") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("ab")) << std::endl;
  std::cout << sa.contain("racadab") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("racadab")) << std::endl;
  std::cout << sa.contain("abracadabra") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("abracadabra")) << std::endl;
  std::cout << sa.contain("ra") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("ra")) << std::endl;
  std::cout << sa.contain("abracadabrada") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("abracadabrada")) << std::endl;
  std::cout << sa.contain("zzaa") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("zzaa")) << std::endl;
  std::cout << sa.contain("z") << std::endl;
  std::cout << " -> " << showvec(sa.indexof("z")) << std::endl;

  return 0;
}

