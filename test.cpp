#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

double minXYZ(double x, double y, double z){
  if(x < y && x < z){
    return x;
  }else if(y < x && y < z){
    return y;
  }else{
    return z;
  }
}

double dynamic_edit_distance(string str1, string str2){
  double var1 = 0;
  double var2 = 0;
  double var3 = 0;

  //creating a new matrix and initializing it to 0
  double matrix[str1.size() + 1][str2.size() + 1] = {};

  //inserting values into matrix
  for(unsigned int i = 1; i <= str1.size(); i++){
    for(unsigned int j = 1; j <= str2.size(); j++){
      //if nucleotides are the same, otherwise
      //it is either a mismatch or requires
      //insertion or deletion or replacing
      if(str1[i - 1] == str2[i - 1]){
        matrix[i][j] = matrix[i - 1][j - 1];
      }else{
        //delete a nucleotide
        var1 = matrix[i - 1][j] + .50;
        //insert a nucleotide
        var2 = matrix[i][j - 1] + .75;
        //replace a nucleotide (mismatched character)
        var3 = matrix[i - 1][j - 1] + .25;

        //pick whichever one of these values
        //"costs" less
        matrix[i][j] = minXYZ(var1, var2, var3);
      }
    }
  }

  return matrix[str1.size()][str2.size()];
}

int main(void){

  vector<string> data;

  data.push_back("gatcac");
  //"gatcacAGGTCTATCACCCTATTAACCACA";
  data.push_back("gaaaaaggggg");
  //"GTTTATGTAGCTTAcctCCCCAAAGCAATA";
  data.push_back("ggggggg");
  //"TAATCTCCCATATTGTaaCTTACTACTCCG";

  for(unsigned int i = 0; i < data.size(); i++){
    transform(data.at(i).begin(),data.at(i).end(),data.at(i).begin(), ::tolower);
  }

  double best = 0;
  double temp = 0;

  for(unsigned int i = 0; i < data.size(); i++){
    for(unsigned int j = data.size() - 1; j != i ; j--){
      //compare
      best = temp;
      temp = dynamic_edit_distance(data.at(i), data.at(j));
      cout << temp << endl;
      if(temp < best){
        best = temp;
      }
    }
  }

  cout << "the best is " << best << endl;

  for(unsigned int i = 0; i < data.size() - 1; i++){

  }

  return 0;
}
