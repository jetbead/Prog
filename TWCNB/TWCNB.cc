#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <cmath>


class TWCNB {
  //クラス数
  int num_class;

  //ドキュメント情報
  std::vector< std::map<std::string,double> > dij;

  //単語集合
  std::set<std::string> wordset;

  //単語の重み
  std::vector< std::map<std::string,double> > weight;

  //Text Transformations
  void text_transformations(){
    //TF transform
    for(int j=0; j<dij.size(); j++){
      std::map<std::string,double>::iterator itr = dij[j].begin();
      while(itr != dij[j].end()){
        itr->second = log(itr->second + 1.0);
        ++itr;
      }
    }

    //IDF transform
    for(int j=0; j<dij.size(); j++){
      std::map<std::string,double>::iterator itr = dij[j].begin();
      while(itr != dij[j].end()){
        int occurs = 0;
        for(int jj=0; jj<dij.size(); jj++){
          if(dij[jj].count(itr->first)>0) occurs++;
        }
        itr->second = itr->second * log( (double)(dij.size()) / occurs );
        ++itr;
      }
    }
    
    //length norm
    for(int j=0; j<dij.size(); j++){
      double sum = 0.0;
      std::map<std::string,double>::iterator itr = dij[j].begin();
      while(itr != dij[j].end()){
        sum += itr->second * itr->second;
        ++itr;
      }
      itr = dij[j].begin();
      while(itr != dij[j].end()){
        itr->second = itr->second / sqrt( sum );
        ++itr;
      }
    }
  }
  
  //単語重みweightの作成
  void calc_weight(const std::vector< std::pair< int, std::vector<std::string> > >& docs){
    for(int c=0; c<num_class; c++){
      weight.push_back(std::map<std::string,double>());
    }

    //complement class
    for(int c=0; c<num_class; c++){
      std::set<std::string>::iterator itr = wordset.begin();
      while(itr != wordset.end()){
        double sum_dij = 0.0;
        double sum_dkj = 0.0;
        for(int j=0; j<docs.size(); j++){
          if(docs[j].first != c){

            std::map<std::string,double>::iterator tmp = dij[j].begin();
            while(tmp != dij[j].end()){
              if(tmp->first == *itr){
                sum_dij += tmp->second;
              }
              sum_dkj += tmp->second;

              ++tmp;
            }
           
          }
        }
        weight[c][*itr] = (sum_dij + 1.0) / (sum_dkj + wordset.size());
        
        ++itr;
      }
    }
    
    //calc weight & normalization
    for(int c=0; c<num_class; c++){
      //std::cout << "class " << c << "=====================" << std::endl;
      double sum = 0.0;
      std::map<std::string,double>::iterator itr = weight[c].begin();
      while(itr != weight[c].end()){
        itr->second = log( itr->second );
        sum += fabs(itr->second);
        ++itr;
      }
      itr = weight[c].begin();
      while(itr != weight[c].end()){
        itr->second = itr->second / sum;
        //std::cout << itr->first << "\t" << itr->second << std::endl;
        ++itr;
      }
    }

  }

  //クラスcの単語wordの重み
  double get_weight(int c, const std::string& word){
    if(weight[c].count(word)==0) return 0.0;
    return weight[c][word];
  }


public:
  
  TWCNB(int num_class):num_class(num_class){}

  //学習
  void train(const std::vector< std::pair< int, std::vector<std::string> > >& docs){
    
    //単語集合wordsetとドキュメント情報dijの作成
    for(int j=0; j<docs.size(); j++){
      std::map<std::string,double> tmp;
      for(int i=0; i<docs[j].second.size(); i++){
        tmp[docs[j].second[i]] += 1.0;
        wordset.insert(docs[j].second[i]);
      }
      dij.push_back(tmp);
    }

    //Text Transformations
    text_transformations();

    //重みの計算
    calc_weight(docs);

  }

  //予測
  int predict(std::vector<std::string>& data){
    int ret = -1;
    double retv = 100000000.0;
    for(int c=0; c<num_class; c++){
      //std::cout << "class " << c << "===========" << std::endl;
      double val = 0.0;
      for(int i=0; i<data.size(); i++){
        //std::cout << data[i] << " " << get_weight(c, data[i]) << std::endl;
        val += get_weight(c, data[i]);
      }
      if(retv > val){
        ret = c;
        retv = val;
      }
      //std::cout << "class " << c << " : " << val << std::endl;
    }
    return ret;
  }

};


std::vector<std::string> split(const std::string &str){
  std::vector<std::string> ret;
  std::string tmp = "";
  for(int i=0; i<str.length(); i++){
    if(tmp != "" && str[i] == ' '){
      ret.push_back(tmp);
      tmp = "";
    }
    else if(str[i] != ' '){
      tmp += str[i];
    }
  }
  if(tmp != "") ret.push_back(tmp);
  return ret;
}


// Usage: ./a.out train_file < test_file
int main(int argc, char** argv){
  if(argc != 2) return 1;

  TWCNB twcnb(8); //クラス数を指定

  int type;
  std::string line;

  //train
  std::ifstream ifs(argv[1]);
  std::vector< std::pair< int, std::vector<std::string> > > docs;

  while(ifs >> type){
    std::getline(ifs, line);
    std::vector<std::string> doc = split(line);
    
    docs.push_back(std::make_pair< int, std::vector<std::string> >(type, doc));
  }
  
  twcnb.train(docs);
  

  //predict
  int num = 0, corr = 0;
  while(std::cin >> type){
    std::getline(std::cin, line);
    std::vector<std::string> doc = split(line);
    
    int res = twcnb.predict(doc);
    std::cout << res << "(correct:" << type << ")" << std::endl;
    if(res == type) corr++;
    num++;
  }

  std::cout << "Acc:" << (corr * 100.0 / num) << "% ";
  std::cout << "(" << corr << " / " << num << ")" << std::endl;


  return 0;
}

