#include "WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
	TString dir ="/home/pku/anying/cms/rootfiles/WWg/";
	ifstream infile("file");
	string buffer; 
	TString infilename;

	int k=1;

	while (k>0){
		getline (infile, buffer) ;
		infilename = buffer;
		if(infilename.Contains("end")==1) {k=-2; break;}
		infilename = infilename;
		TString outname=infilename+"_fakeL.root";

		cout<<dir<<infilename<<" -> "<<outname<<endl;

		TFile *file1 =new TFile(dir+infilename+".root");
		TTree *tree1 = (TTree*) file1->Get("Events");
		WWg m1(tree1,outname);
		cout<<outname<<endl;
		m1.Loop(outname);
		m1.endJob();

	}
}

int main(){
	runxx();
	return 1;
}

