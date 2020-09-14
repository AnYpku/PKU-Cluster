#include "interf.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir = "/eos/user/y/yian/2018cutla/";
ifstream infile("file");
string buffer;
TString infilename;
TH1D* h2;
int k=1;

while (k>0){
	getline (infile, buffer) ;
	infilename = buffer;
	TString filename;
	if(infilename.Contains("Z")==0) {k=-2; continue;}
	filename="cutla-out"+infilename+".root";
	cout<<filename<<endl;

	TFile *file1 =new TFile(dir+filename);
	//TTree *tree1 = (TTree*) file1->Get("ZPKUCandidates");
	TTree *tree1 = (TTree*) file1->Get("demo");
	interf m1(tree1);
	m1.Loop(h2,infilename);
    }
}

int main(){
    runxx();
    return 1;
  }
