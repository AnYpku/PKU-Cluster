#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//gROOT->LoadMacro("xx.C");
TString dir ="/eos/user/y/yian/2017cutla/HLT_debug/";
//TString dir = "../";
//TString dir = "../plj/plj-production/";
//TString dir = "/uscms_data/d3/qliphy/andy/CMSSW_9_4_9_cand2/plj/plj-production/";
ifstream infile("file");
string buffer; 
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains("root")==0) {k=-2; continue;}
TString outname="JEC_cutla-out"+ infilename;
TString inname= "JEC_cutla-out"+infilename;

cout<<inname<<endl;

TFile *file1 =new TFile(dir+inname);
//TDirectory * dir1 = (TDirectory*)file1->Get("treeDumper");
//TTree *tree1 = (TTree*) file1->Get("demo");
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
//TTree *tree1 = (TTree*) file1->Get("treeDumper/ZPKUCandidates");
xx m1(tree1,outname);
cout<<outname<<endl;
m1.Loop(outname);
m1.endJob();
 
}
}

int main(){
	runxx();
	return 1;
}

