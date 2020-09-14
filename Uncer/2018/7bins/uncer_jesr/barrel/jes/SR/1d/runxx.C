#include "jesrUncer.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir="/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/ZAJetfakeohoton/pesudo/";
//TString dir = "../../";
TString dir = "/eos/user/y/yian/2018cutla/";
ifstream infile("file");
string buffer;
TString infilename;
TString name;
TH1D* h2[3];
int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(name.Contains("ZA")==0) {k=-2; continue;}
//TString outname="cutla-"+infilename;
//infilename = "cutla-"+ infilename;
infilename = "JEC_cutla-out" + name+".root";

cout<<infilename<<endl;

TFile *file1 =new TFile(dir+infilename);
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
//TTree *tree1 = (TTree*) file1->Get("demo");
jesrUncer m1(tree1);
//m1.Loop(h2);
m1.makefile(name);
}
}

int main(){
    runxx();
    return 1;
  }
