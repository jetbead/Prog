#include <iostream>
#include <sstream>
#include <vector>


class utf8_util {
public:
  static std::string getCharFromUnicode(const unsigned int& code){
    std::string ret = "";
    if(0x00 <= code && code <= 0x7F){ //1byte
      ret += static_cast<unsigned char>(code);
    }
    else if(0x80 <= code && code <= 0x7ff){ //2byte
      unsigned int a, b;
      a = (code & 0xF80) >> 6;
      b = (code & 0x3F);
      ret += static_cast<unsigned char>(0xC0 | a);
      ret += static_cast<unsigned char>(0x80 | b);
    }
    else if(0x800 <= code && code <= 0xFFFF){ //3byte
      unsigned int a, b, c;
      a = (code & 0xF000) >> 12;
      b = (code & 0xFC0) >> 6;
      c = (code & 0x3F);
      ret += static_cast<unsigned char>(0xE0 | a);
      ret += static_cast<unsigned char>(0x80 | b);
      ret += static_cast<unsigned char>(0x80 | c);
    }
    else if(0x10000 <= code && code <= 0x1FFFFF){ //4byte
      unsigned int a, b, c, d;
      a = (code & 0x1C0000) >> 18;
      b = (code & 0x3F000) >> 12;
      c = (code & 0xFC0) >> 6;
      d = (code & 0x3F);
      ret += static_cast<unsigned char>(0xF0 | a);
      ret += static_cast<unsigned char>(0x80 | b);
      ret += static_cast<unsigned char>(0x80 | c);
      ret += static_cast<unsigned char>(0x80 | d);
    }
    else if(0x200000 <= code && code <= 0x3FFFFFF){ //5byte
      unsigned int a, b, c, d, e;
      a = (code & 0x3000000) >> 24;
      b = (code & 0xFC0000) >> 18;
      c = (code & 0x3F000) >> 12;
      d = (code & 0xFC0) >> 6;
      e = (code & 0x3F);
      ret += static_cast<unsigned char>(0xF8 | a);
      ret += static_cast<unsigned char>(0x80 | b);
      ret += static_cast<unsigned char>(0x80 | c);
      ret += static_cast<unsigned char>(0x80 | d);
      ret += static_cast<unsigned char>(0x80 | e);
    }
    else if(0x4000000 <= code && code <= 0x7FFFFFFF){ //6byte
      unsigned int a, b, c, d, e, f;
      a = (code & 0x40000000) >> 30;
      b = (code & 0x3F000000) >> 24;
      c = (code & 0xFC0000) >> 18;
      d = (code & 0x3F000) >> 12;
      e = (code & 0xFC0) >> 6;
      f = (code & 0x3F);
      ret += static_cast<unsigned char>(0xFC | a);
      ret += static_cast<unsigned char>(0x80 | b);
      ret += static_cast<unsigned char>(0x80 | c);
      ret += static_cast<unsigned char>(0x80 | d);
      ret += static_cast<unsigned char>(0x80 | e);
      ret += static_cast<unsigned char>(0x80 | f);
    }
    return ret;
  }
  
  static std::string getByteFromUnicode(const unsigned int& code){
    std::stringstream ss;
    ss << "0x";
    if(0x00 <= code && code <= 0x7F){ //1byte
      ss << std::hex << code;
    }
    else if(0x80 <= code && code <= 0x7ff){ //2byte
      unsigned int a, b;
      a = (code & 0xF80) >> 6;
      b = (code & 0x3F);
      ss << std::hex << (0xC0 | a);
      ss << std::hex << (0x80 | b);
    }
    else if(0x800 <= code && code <= 0xFFFF){ //3byte
      unsigned int a, b, c;
      a = (code & 0xF000) >> 12;
      b = (code & 0xFC0) >> 6;
      c = (code & 0x3F);
      ss << std::hex << (0xE0 | a);
      ss << std::hex << (0x80 | b);
      ss << std::hex << (0x80 | c);
    }
    else if(0x10000 <= code && code <= 0x1FFFFF){ //4byte
      unsigned int a, b, c, d;
      a = (code & 0x1C0000) >> 18;
      b = (code & 0x3F000) >> 12;
      c = (code & 0xFC0) >> 6;
      d = (code & 0x3F);
      ss << std::hex << (0xF0 | a);
      ss << std::hex << (0x80 | b);
      ss << std::hex << (0x80 | c);
      ss << std::hex << (0x80 | d);
    }
    else if(0x200000 <= code && code <= 0x3FFFFFF){ //5byte
      unsigned int a, b, c, d, e;
      a = (code & 0x3000000) >> 24;
      b = (code & 0xFC0000) >> 18;
      c = (code & 0x3F000) >> 12;
      d = (code & 0xFC0) >> 6;
      e = (code & 0x3F);
      ss << std::hex << (0xF8 | a);
      ss << std::hex << (0x80 | b);
      ss << std::hex << (0x80 | c);
      ss << std::hex << (0x80 | d);
      ss << std::hex << (0x80 | e);
    }
    else if(0x4000000 <= code && code <= 0x7FFFFFFF){ //6byte
      unsigned int a, b, c, d, e, f;
      a = (code & 0x40000000) >> 30;
      b = (code & 0x3F000000) >> 24;
      c = (code & 0xFC0000) >> 18;
      d = (code & 0x3F000) >> 12;
      e = (code & 0xFC0) >> 6;
      f = (code & 0x3F);
      ss << std::hex << (0xFC | a);
      ss << std::hex << (0x80 | b);
      ss << std::hex << (0x80 | c);
      ss << std::hex << (0x80 | d);
      ss << std::hex << (0x80 | e);
      ss << std::hex << (0x80 | f);
    }
    return ss.str();
  }




};



int main(){
  for(unsigned int i=0x3040,cnt=1; i<=0x309F; i++,cnt++){
    std::cout << utf8_util::getCharFromUnicode(i) << "\t"
	      << utf8_util::getByteFromUnicode(i)
	      << std::endl;;
  }
  return 0;
}
