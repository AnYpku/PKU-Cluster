#include "WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year,TString dir) {
	ifstream infile("file"+year);
	string buffer; 
	TString infilename;

	int k=1;

	while (k>0){
		getline (infile, buffer) ;
		infilename = buffer;
		if(infilename.Contains("root")==0) {k=-2; continue;}
		if(infilename.Contains("end")==1) {k=-2; break;}
		infilename = infilename;
		TString outname="Genlep1-out"+infilename;

		TFile *file1 =new TFile(dir+infilename);
		TTree *tree1 = (TTree*) file1->Get("Events");
		WWg m1(tree1,outname);
		cout<<outname<<endl;
		cout<<dir<<infilename<<" -> "<<outname<<endl;
		m1.Loop(outname);
		m1.endJob();

	}
}

int main(){
	TString dir18 ="/home/pku/anying/cms/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/WWG/2018/WWG_selector/";
	TString dir17 ="/home/pku/anying/cms/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/WWG/2017/WWG_selector/";
	runxx("18",dir18);
	runxx("17",dir17);
	return 1;
}

