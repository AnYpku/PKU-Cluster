#include "tree.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString dir,TString outname){
	TTree *tree1;
	TChain*chain = new TChain("Events","");
	chain->Add(dir+"*.root");
	tree1 = chain;
	tree m1(tree1,outname);
	cout<<dir<<" "<<"-> ./"<<outname<<endl;
	m1.Loop();
	m1.endJob();
}
int main(){
	TString dir="/home/pku/guanz/wwaroot/final/lep/";
	TString name="WWA.root";
        runxx(dir,name);
        return 1;
}
