#include "chain_ajj.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year,float nevents,float xs){
        ifstream file("file"+year);
        if(!file.is_open()){cout<<"can not open the file, break the code."<<endl;abort();}
        while(!file.eof()){ 
		TString dir;TString outname;
		file>>dir>>outname;
		if(dir.Contains("end")) break;
		cout<<dir<<"*.root "<<"-> ./"<<outname<<endl;
		TTree *tree1;
		TChain*chain = new TChain("Events","");
		chain->Add(dir+"*.root");
		cout<<"add root"<<endl;
		tree1 = chain;
		cout<<"get tree; "<<tree1->GetEntries()<<endl;
		chain_ajj m1(tree1,outname);
		m1.Loop(outname,nevents,xs,year);
		m1.endJob();
	}
}
int main(){
	runxx("18",1,1);
	return 1;
}
