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
	TString dir="/home/pku/anying/cms/rootfiles/WWg/2016/ST/cutlep-outST*16pre.root";
	TString name="cutlep-outST16pre.root";
	TString dir1="/home/pku/anying/cms/rootfiles/WWg/2016/VV/cutlep-out*Z*16pre.root";
	TString name1="cutlep-outVV16pre.root";
//	TString dir2="/home/pku/anying/cms/rootfiles/WWg/2017/ST/cutlep-outST*17.root";
//	TString name2="cutlep-outST17.root";

	TString dir2="/home/pku/anying/cms/rootfiles/WWg/2018/plj/cutla-out*18_plj.root";
	TString name2="cutla-outplj18.root";
	TString dir3="/home/pku/anying/cms/rootfiles/WWg/2017/plj/cutla-out*17_plj.root";
	TString name3="cutla-outplj7.root";
	TString dir4="/home/pku/anying/cms/rootfiles/WWg/2016/plj/cutla-out*16_plj.root";
	TString name4="cutla-outplj16.root";
	TString dir5="/home/pku/anying/cms/rootfiles/WWg/2016/plj/cutla-out*16pre_plj.root";
	TString name5="cutla-outplj16pre.root";

//	runxx(dir,name);
//	runxx(dir1,name1);
	runxx(dir2,name2);
	runxx(dir3,name3);
	runxx(dir4,name4);
	runxx(dir5,name5);

        return 1;
}
