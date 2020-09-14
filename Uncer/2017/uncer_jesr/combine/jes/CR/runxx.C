#include "jesrUncer.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir="/eos/user/y/yian/2017cutla/";
//TString dir = "../../../";
ifstream infile("file");
string buffer;
TString infilename;
TString filename;
TH2D* h2[3];
int k=1;

while (k>0){
getline (infile, buffer) ;
filename = buffer;
if(filename.Contains("Z")==0) {k=-2; continue;}
//TString outname="cutla-"+infilename;
infilename = "JEC_cutla-out"+ filename+".root";

cout<<infilename<<endl;

TFile *file1 =new TFile(dir+infilename);
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
//TTree *tree1 = (TTree*) file1->Get("demo");
jesrUncer m1(tree1);
//m1.Loop(h2);
m1.makefile(filename);
}
}

int main(){
    runxx();
    return 1;
  }
