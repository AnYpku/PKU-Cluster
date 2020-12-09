#include "plj.C"
#include <iostream>
#include <fstream>
using namespace std;
void runjet(TString name) {
TString dir = "/home/pku/anying/cms/rootfiles/2017/";
ifstream infile("file");
string buffer; 
TString fname;
int k=1;
while (k>0){
getline (infile, buffer) ;
fname = buffer;
if(fname.Contains("out")==0) {k=-2; continue;}
TString inname=fname+".root";
TString outname="cutla-outplj17_weight"+name+".root";
cout<<outname<<endl;

TFile *file1 =new TFile(dir+inname);
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
plj m1(tree1,outname);
m1.Loop(name);
m1.endJob();
 
}

}
int main(){
  runjet("");
  runjet("_up");
  runjet("_down");
  
  return 1;
}

