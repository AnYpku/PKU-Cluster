#include "ee.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir = "/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/ZAJetfakeohoton/pesudo/";
//TString dir = "/data/pku/home/anying/cms/file_in_cms/files_weighted/";
TString dir = "/eos/user/y/yian/2016legacy/ZA-EWK-JESR/";
ifstream infile("file");
string buffer;
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
TString outname="out"+infilename;

cout<<infilename<<endl;
cout<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
TDirectory * dir1 = (TDirectory*)file1->Get("treeDumper");
TTree *tree1 = (TTree*) dir1->Get("ZPKUCandidates");
ee m1(tree1,outname);
cout<<"OK"<<endl;
m1.Loop();
m1.endJob();

}
}

int main(){
    runxx();
    return 1;
  }
