#include "ee.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir = "/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/ZAJetfakeohoton/pesudo/";
//TString dir = "/data/pku/home/anying/cms/file_in_cms/files_weighted/";
TString dir = "../../step1_add_weight/jec/";
ifstream infile("file");
string buffer;
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
TString outname="sig-"+infilename;

cout<<infilename<<endl;
cout<<outname<<endl;

TFile *file1 =new TFile(dir+infilename);
TTree *tree1; 
if(outname.Contains("JEC"))
     tree1 = (TTree*) file1->Get("ZPKUCandidates");
else tree1 = (TTree*) file1->Get("demo");
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
