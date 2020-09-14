#include "xx.C"
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
		TString outname= infilename;

		getline (infiledir, bufferdir) ;
		dir=bufferdir;

		cout<<dir<<endl;

		TTree *tree;
		TChain*chain = new TChain("treeDumper/ZPKUCandidates","");
		chain->Add(dir+"*.root");
		tree = chain;
		xx m1(tree,outname);
		cout<<dir<<outname<<endl;
		m1.Loop();
		m1.endJob();
	}
}

int main(){
	runxx();
	return 1;
}

