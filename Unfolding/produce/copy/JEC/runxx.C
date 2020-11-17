#include "rm.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir, TString filename,TString tag) {
TString outname="unfold_"+tag+filename;
TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("treeDumper/ZPKUCandidates");
rm m1(tree1,outname);
cout<<outname<<endl;
m1.Loop(tag);
m1.endJob();
}

int main(){
	TString dir16="/home/pku/anying/cms/rootfiles/JESR/";
	TString name16="JESR_ZA-EWK16.root";
	TString dir17="/home/pku/anying/cms/rootfiles/JESR/";
	TString name17="JESR_ZA-EWK17.root";
	TString dir18="/home/pku/anying/cms/rootfiles/JESR/";
	TString name18="JESR_ZA-EWK18.root";
	runxx(dir16,name16,"16");
	runxx(dir17,name17,"17");
	runxx(dir18,name18,"18");
	return 1;
}

