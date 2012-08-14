#include <iostream>
#include <string>
#include <vector>

using namespace std;

class utf8_string {
  std::vector<std::string> str;
  int num_byte(const char &cc){
    unsigned char c = static_cast<unsigned char>(cc);
    if(c <= 0x7f) return 1;
    if(0xc0 <= c && c <= 0xcf) return 2;
    if(0xd0 <= c && c <= 0xdf) return 2;
    if(0xe0 <= c && c <= 0xef) return 3;
    if(0xf0 <= c && c <= 0xf7) return 4;
    if(0xf8 <= c && c <= 0xfb) return 5;
    return 6;
  }
  void init_str(const std::string &s){
    for(size_t i=0; i<s.length();){
      int n = num_byte(s[i]);
      str.push_back(s.substr(i,n));
      i += n;
    }
  }
public:
  utf8_string(const std::string &s){ init_str(s); }
  utf8_string(const char *p){
    std::string s(p);
    init_str(s);
  }
  
  size_t length() const { return str.size(); }
  std::string operator[](size_t idx) const {
    return str[idx];
  }
  bool operator==(const utf8_string &s){
    if(length() != s.length()) return false;
    for(size_t i=0; i<length(); i++){
      if(str[i] != s[i]) return false;
    }
    return true;
  }
  std::string substr(size_t begin, size_t len){
    std::string ret;
    for(size_t i=begin; i<begin+len; i++){
      ret += str[i];
    }
    return ret;
  }
};


int main(){

  string str = "今日は1212Hello World\n";
  //cin >> str;
  //getline(cin, str);
  utf8_string utf8str = str;
  cout << utf8str.length() << " / " << str.length() << endl;
  for(size_t i=0; i<utf8str.length(); i++){
    cout << utf8str[i] << endl;
  }
  cout << utf8str.substr(1,2) << endl;
  return 0;
}
