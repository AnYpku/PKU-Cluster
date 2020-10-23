#include "xx.C"
#include <fstream>
void runxx() {
TString dir="/eos/user/y/yian/2018cutla/";

ifstream infile("file");
string buffer; 
TString name;

int k=1;

while (k>0){
	getline (infile, buffer) ;
	name = buffer;
	if(name.Contains("out")==0) {k=-2; continue;}
	TString inname="cutlep-"+name+".root";
	TString outname= "cutlep-"+name+"_plj.root";
	cout<<dir<<inname<<endl;
	cout<<outname<<endl;
	TFile *file1;
	TTree *tree1; 
	file1 =new TFile(dir+inname);
	tree1 = (TTree*) file1->Get("ZPKUCandidates");
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

