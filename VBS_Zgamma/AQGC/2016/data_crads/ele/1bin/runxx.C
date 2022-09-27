#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString name) {
	TString dir = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/ScalSeq/output-slimmed-rootfiles/";
	TFile*file=new TFile(dir+"optimal_aqgc_"+name+".root");
	TTree *tree1 = (TTree*) file->Get("outtree");
	xx m1(tree1);
	m1.Loop(name);
}
int main(){
    runxx("ZA_legacy");
    runxx("ZA-EWK");
    runxx("plj_weight");
    runxx("others");
//    runxx("DMuon16");
    return 1;
  }
