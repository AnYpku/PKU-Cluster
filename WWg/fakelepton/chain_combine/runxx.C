#include "chain_WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year) {
	ifstream file("file"+year);
	while (!file.eof()){
                TString dir;TString outname;
                file>>dir>>outname;
                if(dir.Contains("end")) break;
                cout<<dir<<"*.root "<<"-> ./"<<outname<<endl;

                TTree *tree1;
                TChain*chain = new TChain("Events","");
                chain->Add(dir+"*.root");
                cout<<"add root"<<endl;
                tree1 = chain;
		chain_WWg m1(tree1,outname);

		cout<<outname<<endl;
		TFile*f1=chain->GetFile();
		TH1D*h1=(TH1D*)f1->Get("nEventsGenWeighted");
		double nevents=h1->GetSum();
		m1.Loop(outname,nevents,year);
		m1.endJob();

	}
}

int main(){
//	runxx("18");
	runxx("17");
//	runxx("16");
	return 1;
}

