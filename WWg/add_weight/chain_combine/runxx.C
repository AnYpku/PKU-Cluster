#include "chain_WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir,TString outname){
	TTree *tree1;
	TChain*chain = new TChain("Events","");
	chain->Add(dir+".root");
	tree1 = chain;
	chain_WWg m1(tree1,outname);
	cout<<dir<<" "<<"-> ./"<<outname<<endl;
	m1.Loop(outname);
	m1.endJob();
}
int main(){
//	TString dir="./rootfiles/";
	TString dir="/home/pku/anying/cms/rootfiles/WWg/tmp/cutla-out*";
	TString name="cutla-outVV18.root";
        runxx(dir,name);
        return 1;
}
