#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//gROOT->LoadMacro("xx.C");
//TString dir = "./";
TString dir = "/home/pku/anying/cms/rootfiles/2018/nohlt/";
ifstream infile("file");
string buffer; 
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains("out")==0) {k=-2; continue;}
TString outname=/*"cutla-"+*/infilename;//+".root";
TString inname=/*"cutlep-"+*/infilename;//+".root";

cout<<dir<<inname<<"->"<<dir<<outname<<endl;

TFile *file1 =new TFile(dir+inname);
//TTree *tree1 = (TTree*) file1->Get("demo");
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
xx m1(tree1,outname);
cout<<outname<<endl;
m1.Loop(inname);
m1.endJob();
 
}
}

int main(){
	runxx();
	return 1;
}

