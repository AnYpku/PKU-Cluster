#include "plj.C"
#include <iostream>
#include <fstream>
using namespace std;
void runjet() {
//TString dir="/eos/uscms/store/user/qliphy/andy/2017/cutlep/";
//TString dir = "/uscms_data/d3/qliphy/andy/CMSSW_9_4_9_cand2/small/cutla/";
TString dir = "/eos/user/y/yian/2018cutla/";

ifstream infile("file");
string buffer; 
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(name.Contains("out")==0) {k=-2; continue;}
//TString outname=  "cutla-outplj_muendcap_up.root";
TString outname="cutla-outplj_muendcap.root";
//TString outname="cutla-outplj_muendcap_down.root";
TString inname=name+".root";

cout<<inname<<endl;

TFile *file1 =new TFile(dir+inname);
TTree *tree1 = (TTree*) file1->Get("demo");
plj m1(tree1,outname);
cout<<outname<<endl;
m1.Loop();
m1.endJob();
 
}

}
int main(){
  runjet();
  return 1;
}

