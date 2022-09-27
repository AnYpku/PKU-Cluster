#include "chain.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir,TString outname){
	TTree *tree1;
	TChain*chain1 = new TChain("Events","");
	chain1->Add(dir+"ZA16_1.root");
	chain1->Add(dir+"ZA16_ex.root");
	tree1 = chain1;
	chain m1(tree1,outname);
	cout<<dir<<" "<<"-> ./"<<outname<<endl;
	m1.Loop();
	m1.endJob();
}
int main(){
//	TString dir="./rootfiles/";
	TString dir="/home/pku/anying/cms/rootfiles/2016/";
	TString name="ZA.root";
        runxx(dir,name);
        return 1;
}
