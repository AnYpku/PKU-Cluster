#include "findbin.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir="../";
TString filename = "DEle16.root";
TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
findbin m1(tree1);
cout<<filename<<endl;
m1.Loop();
//file1->Close();
}
int main(){
    runxx();
    return 1;
  }
