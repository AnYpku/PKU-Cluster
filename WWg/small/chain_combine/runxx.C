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
	TString dir="/home/pku/anying/cms/rootfiles/WWg/2017/cutlep1-out*_plj.root";
	TString name="cutlep1-outplj17.root";
	TString dir1="/home/pku/anying/cms/rootfiles/WWg/2017/cutlep1-out*_fakeL.root";
	TString name1="cutlep1-outfakeL17.root";
	TString dir2="/home/pku/anying/cms/rootfiles/WWg/2017/cutlep1*_plj.root";
	TString name2="cutlep1-outplj17.root";
//        runxx(dir,name);
	runxx(dir1,name1);
        return 1;
}
