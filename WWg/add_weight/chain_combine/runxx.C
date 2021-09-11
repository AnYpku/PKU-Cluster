#include "chain_WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir,TString outname,TString year){
	cout<<dir<<" "<<"-> ./"<<outname<<endl;
	TTree *tree1;
	TChain*chain = new TChain("Events","");
	chain->Add(dir);
	cout<<"add root"<<endl;
	tree1 = chain;
	cout<<"get tree; "<<tree1->GetEntries()<<endl;
	chain_WWg m1(tree1,outname);
	m1.Loop(outname,1,year);
	m1.endJob();
}
int main(){
	TString dir1="/home/pku/anying/cms/rootfiles/WWg/2018/MuonEG_D/0000/*.root";
	TString name1="cutlep-outMuonEG_D18.root";
        runxx(dir1,name1,"18");
        return 1;
}
