#include "jesrUncer.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir="/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/ZAJetfakeohoton/pesudo/";
TString dir = "../../";
//TString dir = "/home/pku/anying/cms/file_in_cms/files_weighted/";
ifstream infile("file");
string buffer;
TString infilename;
TH2D* h2[3];
int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
//TString outname="cutla-"+infilename;
infilename = "cutla-"+ infilename;
infilename =  infilename;

cout<<infilename<<endl;

TFile *file1 =new TFile(dir+infilename);
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
//TTree *tree1 = (TTree*) file1->Get("demo");
jesrUncer m1(tree1);
//m1.Loop(h2);
m1.makefile();
}
}

int main(){
    runxx();
    return 1;
  }
