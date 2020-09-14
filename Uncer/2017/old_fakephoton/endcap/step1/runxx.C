#include "findbin.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir="../";
TString filename = "DMuon.root";
TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("demo");
findbin m1(tree1);
cout<<filename<<endl;
m1.Loop();
//file1->Close();
}
int main(){
    runxx();
    return 1;
  }
