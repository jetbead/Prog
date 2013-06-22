#include <iostream>
#include <vector>
#include <map>

//Burrows Wheeler変換
class BWT {
public:
  // text -> (bwt_text, F)
  std::pair<std::string,std::string> encode(std::string text){
    std::vector<std::string> ary;

    text += '$'; //終端文字
    size_t sz = text.length();
    
    for(size_t i=0; i<sz; i++){
      ary.push_back(text);
      text = text.substr(1) + text[0];
    }

    sort(ary.begin(), ary.end());

    std::string bwt_text, F;
    for(size_t i=0; i<ary.size(); i++){
      F += ary[i][0];
      bwt_text += ary[i][ary[i].length()-1];
    }
    
    return std::make_pair(bwt_text, F);
  }

  //(bwt_text, F) -> text)
  std::string decode(std::string bwt_text, std::string F){
    std::map<char,int> C;
    for(size_t i=0; i<F.length(); i++){
      if(C.count(F[i]) == 0){
        C[F[i]] = i;
      }
    }

    //bwt_text[i]の文字のFでの位置(LFmapping)
    std::vector<int> LF;
    for(size_t i=0; i<F.length(); i++){
      int ri = 0;
      for(size_t j=0; j<=i; j++){
        if(bwt_text[j] == bwt_text[i]) ri++;
      }
      LF.push_back(C[bwt_text[i]] + ri - 1);
    }
    
    //逆変換
    std::string ret(F.length()-1, '*');
    size_t s = 0;
    for(int i=F.length()-1; i>=0; i--){
      if(i>=1) ret[i-1] = bwt_text[s];
      s = LF[s];
      
      //std::cout << ret << std::endl;
    }
    
    return ret;
  }
  
};


int main(){
  
  BWT bwt;
  
  std::string text = "abracadabra";

  std::pair<std::string,std::string> ret = bwt.encode(text);
  
  std::cout << "[text]" << std::endl;
  std::cout << text << std::endl;
  
  std::cout << "[encode]" << std::endl;
  std::cout << ret.first << std::endl;
  std::cout << ret.second << std::endl;
  
  std::cout << "[decode]" << std::endl;
  std::cout << bwt.decode(ret.first, ret.second) << std::endl;
  
  return 0;
}
