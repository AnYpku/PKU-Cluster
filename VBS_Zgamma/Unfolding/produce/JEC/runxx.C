#include "rm.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir, TString filename,TString tag) {
TString outname="unfold_"+tag+filename;
TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
rm m1(tree1,outname);
cout<<outname<<endl;
m1.Loop();
m1.endJob();
}

int main(){
	TString dir16="/eos/user/y/yian/2016legacy/";
	TString name16="outJEC_ZA-EWK.root";
	TString dir17="/eos/user/y/yian/2017cutla/";
	TString name17="outJEC_ZA-EWK.root";
	TString dir18="/eos/user/y/yian/2018cutla/";
	TString name18="outJEC_ZA-EWK.root";
	runxx(dir16,name16,"16");
//	runxx(dir17,name17,"17");
//	runxx(dir18,name18,"18");
	return 1;
}

