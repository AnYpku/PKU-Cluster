#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir="/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/ZAJetfakeohoton/pesudo/";
TString dir = "./";
ifstream infile("file");
string buffer;
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
TString outname="CUT-"+infilename;

cout<<infilename<<endl;
cout<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
TDirectory * dir1 = (TDirectory*)file1->Get("treeDumper");
TTree *tree1 = (TTree*) dir1->Get("PKUCandidates");
xx m1(tree1,outname);
m1.Loop();
m1.endJob();

}
}

int main(){
    runxx();
    return 1;
  }
