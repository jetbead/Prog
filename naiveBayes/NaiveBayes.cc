#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

//教師情報付きドキュメント
struct Document {
  int class_no; //クラスの番号
  set<string> words; //出現する単語リスト
  void add(string word){
    words.insert(word);
  }
};

//ナイーブベイズ(多変数ベルヌーイモデル、MAP推定、alpha=2)
class NaiveBayes {
  int m_num_of_class;
  set<string> m_all_words;
  vector<int> m_num_docs;
  vector< map<string,int> > m_class;
  int m_num_of_all_docs;
public:
  //コンストラクタ
  NaiveBayes(int num_of_class){
    m_num_of_class = num_of_class;
    m_num_of_all_docs = 0;
    for(int i=0; i<m_num_of_class; i++){
      m_num_docs.push_back(0);
      m_class.push_back(map<string,int>());
    }
  }
  
  //訓練関数
  void train(const Document& docs){
    if(docs.class_no < 0 || docs.class_no >= m_num_of_class){
      cerr << "invalid train-data." << endl;
      return;
    }
    
    m_num_docs[docs.class_no]++;
    m_num_of_all_docs++;
    
    set<string>::const_iterator itr = docs.words.begin();
    for(; itr != docs.words.end(); ++itr){
      m_class[docs.class_no][(*itr)]++;
      m_all_words.insert(*itr);
    }
  }
  
  //予測関数
  int predict(vector<string>& words){
    vector<double> ret(m_num_of_class, 0.0);

    const double m_alpha = 2;
    for(int c=0; c<m_num_of_class; c++){
      double Pc = (m_num_docs[c] + (m_alpha - 1.0))/((double)m_num_of_all_docs + m_num_of_class * (m_alpha - 1.0));
      double Pwc_all = 1.0;
      
      set<string>::iterator itr = m_all_words.begin();
      for(; itr != m_all_words.end(); ++itr){
        double Pwc = (m_class[c][*itr] + (m_alpha - 1.0))/((double)m_num_docs[c] + 2 * (m_alpha - 1.0));
        
        if(find(words.begin(), words.end(), *itr) != words.end()){ //出てきた場合
          Pwc_all *= Pwc;
        }else{ //出てこなかった場合
          Pwc_all *= (1.0-Pwc);
        }
      }
      
      ret[c] = Pc * Pwc_all;
    }
    
    int ret_idx = -1;
    double maxP = -1.0;
    for(int i=0; i<m_num_of_class; i++){
      //cerr << "class " << i << ": " << ret[i] << endl;
      if(maxP<ret[i]){
        maxP = ret[i];
        ret_idx = i;
      }
    }
    return ret_idx;
  }
};


int main(int argc, char** argv){
  
  fstream trainf(argv[1]);
  fstream testf(argv[2]);
  
  NaiveBayes nb(2);
  
  int c_type;
  string str;

  //学習
  while(trainf >> c_type){
    int num;
    trainf >> num;
    Document d;
    d.class_no = c_type;
    for(size_t i=0; i<num; i++){
      trainf >> str;
      d.add(str);
    }
    nb.train(d);
  }

  //予測
  int success = 0, failure = 0, allnum = 0;
  int c_zero_num = 0;
  while(testf >> c_type){
    int num;
    testf >> num;
    vector<string> wrds;
    for(size_t i=0; i<num; i++){
      testf >> str;
      wrds.push_back(str);
    }

    allnum++;
    if(c_type == nb.predict(wrds)){
      success++;
    }else{
      failure++;
    }

    if(c_type == 0){
      c_zero_num++;
    }
  }

  //結果
  cout << "Acc : " << (success*100.0/allnum) << "% ";
  cout << "(0: " << c_zero_num << " / " << allnum << ")" << endl;

  return 0;
}

