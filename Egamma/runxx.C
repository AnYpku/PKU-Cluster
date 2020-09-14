#include "hltGenTree.C"
//#include "hlt.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir ="./rootfiles/";
ifstream infile("file");
string buffer; 
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(name.Contains("0")==0) {k=-2; continue;}
TString inname="zToEE_M_" +name+"_102X_TrigNtup.root";
TString outname=name+"_endcap.root";
//TString outname=name+"_barrel.root";

cout<<inname<<endl;

TFile *file1 =new TFile(dir+inname);
TTree *tree1 = (TTree*) file1->Get("hltGenTree");
hltGenTree m1(tree1);
cout<<outname<<endl;
m1.Loop(outname);
m1.endJob(inname);
 
}
}

int main(){
	runxx();
	return 1;
}

