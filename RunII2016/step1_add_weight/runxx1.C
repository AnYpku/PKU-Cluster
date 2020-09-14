#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//gROOT->LoadMacro("xx.C");
TString dir="/data/pku/home/anying/cms/file_in_cms/files_weighted/";
ifstream infile("file_all");
string buffer; 
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
TString outname=infilename;

cout<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
TTree *tree1 = (TTree*) file1->Get("demo");
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

