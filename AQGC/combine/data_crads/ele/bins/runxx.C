#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString name) {
	TString dir18 = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2018/ScalSeq/output-slimmed-rootfiles/";
	TString dir17 = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2017/ScalSeq/output-slimmed-rootfiles/";
	TString dir16 = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/ScalSeq/output-slimmed-rootfiles/";
	TChain*chain=new TChain("outtree");
        chain->Add(dir16+"optimal_aqgc_"+name+".root");
        chain->Add(dir17+"optimal_aqgc_"+name+".root");
        chain->Add(dir18+"optimal_aqgc_"+name+".root");
        TTree*tree1;tree1=chain;
	cout<<name<<endl;
//	TFile*file=new TFile(dir+"optimal_aqgc_"+name+".root");
//	TTree *tree1 = (TTree*) file->Get("outtree");
	vector<double> ZGbin = {150,300,450,600,750,1000,1500,2000};

	xx m1(tree1);
	m1.Loop(name,ZGbin);
}
int main(){
    runxx("ZA");
    runxx("ZA-EWK");
    runxx("plj_weight");
    runxx("bkg");
//    runxx("DMuon16");
    return 1;
  }
