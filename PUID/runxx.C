#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString tag,TString infilename) {
	TString dir ="/home/pku/anying/cms/rootfiles/20"+tag+"/no_pu/";

	TString outname="cutla-out"+infilename+tag+".root";
	TString inname= "cutla-out"+infilename+tag+".root";

	cout<<dir<<inname<<"->"<<dir<<outname<<endl;

	TFile *file1 =new TFile(dir+inname);
	TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
	xx m1(tree1,outname);
	cout<<outname<<endl;
	m1.Loop(outname,tag);
	m1.endJob();

}

int main(){
//	vector<TString> sample={"ZA","ZA-EWK","TTA","ST","VV","ZA_interf","ZA_aQGC"};
	vector<TString> sample={"ZA_interf"};
        vector<TString> tag={"16","18"}; 
//        vector<TString> tag={"16"}; 
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<sample.size();j++){
			runxx(tag[i],sample[j]);
		}
	}
	return 1;
}

