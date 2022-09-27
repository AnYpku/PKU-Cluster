#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString name) {
	TString dir = "/home/pku/anying/cms/PKU-Cluster/AQGC/2017/ScalSeq/output-slimmed-rootfiles/puID/";
	TFile*file;
	if(name.Contains("plj"))file=new TFile(dir+"optimal_aqgc_"+name+"17"+"_weight.root");
	else file=new TFile(dir+"optimal_aqgc_"+name+"17.root");
	TTree *tree1 = (TTree*) file->Get("outtree");
	xx m1(tree1);
	m1.Loop(name);
}
int main(){
    runxx("ZA");
    runxx("ZA-EWK");
    runxx("plj");
    runxx("bkg");
    return 1;
  }
