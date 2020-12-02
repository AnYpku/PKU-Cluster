#include "xx.C"
#include <fstream>
void runxx() {
//gROOT->LoadMacro("xx.C");
TString dir="/home/pku/anying/cms/rootfiles/2018/";

ifstream infile("file");
string buffer; 
TString name;

int k=1;

while (k>0){
	getline (infile, buffer) ;
	name = buffer;
	if(name.Contains("D")==0) {k=-2; continue;}
	TString outname= "cutla-out"+name+"_plj.root";
	TString inname=/*"cutlep-"+*/name+".root";
	cout<<dir<<inname<<endl;
	cout<<outname<<endl;
	TFile *file1;
	TTree *tree1; 
	file1 =new TFile(dir+inname);
//	TDirectory *dir1 = (TDirectory*)file1->Get("treeDumper");
	tree1 = (TTree*) file1->Get("treeDumper/ZPKUCandidates");
	xx m1(tree1,outname);
	cout<<outname<<endl;
	m1.Loop();
	m1.endJob();

}
}

int main(){
	runxx();
	return 1;
}

