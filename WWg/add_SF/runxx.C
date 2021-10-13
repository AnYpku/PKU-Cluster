#include "WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year) {
//TString dir ="/home/pku/anying/cms/rootfiles/WWg/20"+year+"/";
TString dir ="/home/pku/anying/cms/rootfiles/WWg/20"+year+"/v8/no_btag/";
ifstream infile("file");
string buffer; 
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains("root")==0) {k=-2; continue;}
if(infilename.Contains("end")==1) {k=-2; break;}
infilename = /*"cutla-"+*/infilename;
TString outname=infilename;

cout<<dir<<infilename<<" -> "<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
//TDirectory * dir1 = (TDirectory*)file1->Get("treeDumper");
//TTree *tree1 = (TTree*) dir1->Get("ZPKUCandidates");
TTree *tree1 = (TTree*) file1->Get("Events");
WWg m1(tree1,outname);
cout<<outname<<endl;
m1.Loop(outname,year);
m1.endJob();
 
}
}

int main(){
	runxx("18");
	return 1;
}

