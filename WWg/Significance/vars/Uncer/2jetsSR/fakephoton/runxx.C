#include "WWg.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString year) {
	TString dir ="/home/pku/anying/cms/rootfiles/WWg/20"+year+"/";
	ifstream infile("file");
	string buffer; 
	TString infilename,filename;

	int k=1;

	while (k>0){
		getline (infile, buffer) ;
		infilename = buffer;
		if(infilename.Contains("end")==1) {k=-2; break;}
		filename = infilename+".root";
                TString outname=infilename+"_unc.root";
		TFile *file1 =new TFile(dir+filename);
		TTree *tree1 = (TTree*) file1->Get("Events");
		WWg m1(tree1,outname);
		cout<<dir<<filename<<endl;
		m1.Loop(outname,year);
		m1.endJob(); 
	}
}

int main(){
	runxx("17");
	return 1;
}

