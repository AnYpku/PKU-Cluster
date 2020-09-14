#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//gROOT->LoadMacro("xx.C");
TString dir="/eos/cms/store/user/yian/";
//TString dir ="/home/pku/anying/tmp/";
ifstream infile("file_all");
string buffer; 
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
TString outname=/*"cutlep-"+*/"out"+infilename;

cout<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
TDirectory * dir1 = (TDirectory*)file1->Get("treeDumper");
TTree *tree1 = (TTree*) dir1->Get("ZPKUCandidates");
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

