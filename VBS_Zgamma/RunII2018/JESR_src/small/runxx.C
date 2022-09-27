#include "small.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
	ifstream filename("filename");
	ifstream infiledir("filedir");
	string buffername,bufferdir; 
	TString infilename;
	TString dir;

	int k=1;

	while (k>0){
		getline (filename, buffername) ;
		infilename = buffername;
		if(infilename.Contains("root")==0) {k=-2; continue;}
		infilename = "out"+infilename;
		TString outname=/*"cutla-"+*/ infilename;

		getline (infiledir, bufferdir) ;
		dir=bufferdir;

		cout<<outname<<endl;
		TTree *tree;
		TFile*f1=new TFile(dir+outname);
		tree=(TTree*)f1->Get("ZPKUCandidates");
//		TChain*chain = new TChain("treeDumper/ZPKUCandidates","");
//		chain->Add(dir+"*.root");
//		tree = chain;
		small m1(tree);
		cout<<dir<<outname<<endl;
		m1.Loop(infilename);
	}
}

int main(){
	runxx();
	return 1;
}

