#include "MakeTemplate.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir="./rootfiles/";
//TString dir="/home/pku/anying/cms/rootfiles/2018/";
ifstream infile("file");
string buffer;
TString name;

int k=1;
TFile* f1 =new TFile("../../../sigmaEtaEta_corr/transformation_endcap.root");
TGraph* gr =(TGraph*)f1->Get("endcap");
while (k>0){
getline (infile, buffer) ;
name = buffer;
if(( name.Contains("A") || name.Contains("D"))==0) {k=-2; continue;}
//TString filename="cutlep-out" + name+".root";
TString filename= name+".root";
cout<<name<<endl;

TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
MakeTemplate m1(tree1);
cout<<filename<<endl;
m1.Loop(name,gr);
m1.endJob();
  }
}
int main(){
    runxx();
    return 1;
  }
