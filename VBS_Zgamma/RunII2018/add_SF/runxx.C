#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//gROOT->LoadMacro("xx.C");
//TString dir="/data/pku/home/anying/cms/file_in_cms/files_weighted/";
TString dir ="/eos/user/y/yian/2018cutla/";
ifstream infile("file");
string buffer; 
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
TString infilename = /*"cutlep-out"+*/name;
TString outname=/*"cutlep-*/"out"+name;
if(infilename.Contains("root")==0) {k=-2; continue;}

cout<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
TDirectory * dir1 = (TDirectory*)file1->Get("treeDumper");
TTree *tree1 = (TTree*) dir1->Get("ZPKUCandidates");
//TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
//TTree *tree1 = (TTree*) file1->Get("demo");
xx m1(tree1,outname);
cout<<outname<<endl;
m1.Loop();
m1.endJob();
 
}
}

int main(){
	runxx();
	return 1;
}

