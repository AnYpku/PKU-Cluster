#include "ee.C"
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
//		TString outname="cutla-"+ infilename;
		TString outname= infilename;

		getline (infiledir, bufferdir) ;
		dir=bufferdir;

		cout<<outname<<endl;
//                TFile*f1=new TFile(dir+outname);
//                TTree *tree=(TTree*)f1->Get("ZPKUCandidates");
		TTree *tree;
		TChain*chain = new TChain("treeDumper/ZPKUCandidates","");
//		TChain*chain = new TChain("ZPKUCandidates","");
		chain->Add(dir+"*.root");
		tree = chain;
		ee m1(tree,outname);
		cout<<dir<<outname<<endl;
		m1.Loop();
		m1.endJob();
	}
}

int main(){
	runxx();
	return 1;
}

