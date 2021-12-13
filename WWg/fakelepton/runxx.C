#include "WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year) {
	TString dir ="/home/pku/anying/cms/rootfiles/WWg/20"+year+"/";
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
		TString outname="out"+infilename;

		cout<<dir<<infilename<<" -> "<<outname<<endl;

		TFile *file1 =new TFile(dir+infilename);
		TTree *tree1 = (TTree*) file1->Get("Events");
		TH1D*h1=(TH1D*)file1->Get("nEventsGenWeighted");
		double nevents=0;
		nevents=h1->GetSum();
		WWg m1(tree1,outname);
		cout<<outname<<endl;
		m1.Loop(outname,nevents,year);
		m1.endJob();

	}
}

int main(){
	runxx("18");
	return 1;
}

