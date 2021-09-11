#include "chain_WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir,TString outname){
	cout<<dir<<" "<<"-> ./"<<outname<<endl;
	TTree *tree1;
	TChain*chain = new TChain("Events","");
	chain->Add(dir);
	cout<<"add root"<<endl;
	tree1 = chain;
	cout<<"get tree; "<<tree1->GetEntries()<<endl;
	chain_WWg m1(tree1,outname);
	m1.Loop();
	m1.endJob();
}
int main(){
	TString dir="/home/pku/anying/cms/rootfiles/WWg/2018/cutlep1-outMuonEG_*.root";
	TString name="cutlep1-outMuonEG18.root";
	TString dir1="/home/pku/anying/cms/rootfiles/WWg/2017/cutlep1*_fakeL.root";
	TString name1="cutlep-outfakeL17.root";
	TString dir2="/home/pku/anying/cms/rootfiles/WWg/2018/cutlep1*_fakeL.root";
	TString name2="cutlep-outfakeL18.root";
        runxx(dir1,name1);
	runxx(dir2,name2);
        return 1;
}
