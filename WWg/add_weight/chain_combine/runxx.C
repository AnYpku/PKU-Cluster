#include "chain_WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year,bool flag,double n){
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
		chain_WWg m1(tree1,outname);
		m1.Loop(outname,n,year,flag);
		m1.endJob();
	}
}
int main(){
//	runxx("18",false,3907000);
//	runxx("16",true,1);
//	runxx("17",false,1);
	runxx("18",false,1);
	return 1;
}
