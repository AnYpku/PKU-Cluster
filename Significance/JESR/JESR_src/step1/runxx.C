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

		getline (infiledir, bufferdir) ;
		dir=bufferdir;

		cout<<infilename<<endl;

                TFile*file=new TFile(dir+infilename);
		TTree *tree=(TTree*)file->Get("ZPKUCandidates");
		xx m1(tree,infilename);
		cout<<dir<<infilename<<endl;
		m1.Loop();
		m1.endJob();
	}
}

int main(){
	runxx();
	return 1;
}

