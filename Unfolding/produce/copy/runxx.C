#include "rm.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir, TString filename,TString tag) {
TString outname="GenCutla-"+filename;
TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("treeDumper/ZPKUCandidates");
//TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
rm m1(tree1,outname,tag);
cout<<dir<<filename<<"->"<<outname<<endl;
m1.Loop(tag);
m1.endJob();
}

int main(){
	TString dir16="/home/pku/anying/cms/rootfiles/2016/";
	TString name16="ZA16.root";
	TString dir17="/home/pku/anying/cms/rootfiles/2017/";
	TString name17="ZA17.root";
	TString dir18="/home/pku/anying/cms/rootfiles/2018/";
	TString name18="ZA18.root";
	runxx(dir16,name16,"16");
	runxx(dir17,name17,"17");
	runxx(dir18,name18,"18");
	return 1;
}

