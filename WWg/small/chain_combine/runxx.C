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
//	TString dir="./rootfiles/";
	TString dir="/home/pku/anying/cms/rootfiles/WWg/cutlep-out*fakeL.root";
	TString name="cutlep-outfakeL18.root";
	TString dir1="/home/pku/anying/cms/PKU-Cluster/WWg/Significance/Uncer/fakephoton/root/cutlep-out*plj_down.root";
	TString dir2="/home/pku/anying/cms/PKU-Cluster/WWg/Significance/Uncer/fakephoton/root/cutlep-out*plj_up.root";
	TString name1="cutlep-outplj_down18.root";
	TString name2="cutlep-outplj_up18.root";
	runxx(dir2,name2);
	runxx(dir1,name1);
        return 1;
}
