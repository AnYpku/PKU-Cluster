#include "WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year,TString dir,bool flag) {
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
		TString outname="cutlep-out"+infilename;

		TFile *file1 =new TFile(dir+infilename);
		TTree *tree1 = (TTree*) file1->Get("Events");
		WWg m1(tree1,outname);
		cout<<outname<<endl;
		TH1D*h1=(TH1D*)file1->Get("nEventsGenWeighted");
		double nevents=0;
		nevents=h1->GetSum();
		cout<<dir<<infilename<<" -> "<<outname<<endl;
		m1.Loop(outname,nevents,year,flag);
		m1.endJob();

	}
}

int main(){
	TString dir18 ="/home/pku/guanz/cms/allPF/";
	TString dir17 ="/home/pku/anying/cms/rootfiles/WWg/2017/";
	TString dir16 ="/home/pku/anying/cms/rootfiles/WWg/2016/";
	runxx("18",dir18,0);
//	runxx("17",dir17,0);
//	runxx("16",dir16,1);
	return 1;
}

