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
	m1.Loop(outname);
	m1.endJob();
}
int main(){
	TString dir="/home/pku/anying/cms/rootfiles/WWg/2018/fake/WW/cutlep-out*plj*.root";
	TString name="cutlep-outplj_new18.root";
	TString dir1="/home/pku/anying/cms/rootfiles/WWg/2017/fake/WW/cutlep-out*plj*.root";
	TString name1="cutlep-outplj_new17.root";
	TString dir2="/home/pku/anying/cms/rootfiles/WWg/2016/fake/WW/cutlep-out*plj*.root";
	TString name2="cutlep-outplj_new16.root";
	TString dir3="/home/pku/anying/cms/rootfiles/WWg/2016/fake/WW/pre/cutlep-out*plj*.root";
	TString name3="cutlep-outplj_new_pre16.root";
	runxx(dir,name);
	runxx(dir1,name1);
	runxx(dir2,name2);
	runxx(dir3,name3);
        return 1;
}
