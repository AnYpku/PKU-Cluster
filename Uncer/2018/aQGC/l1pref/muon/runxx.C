#include "tree.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2018/aa2/ScalSeq/output-slimmed-rootfiles/optimal_2018_";
ifstream infile("file");
string buffer;
TString infilename;

int k=1;

while (k>0){
	getline (infile, buffer) ;
	infilename = buffer;
	if(infilename.Contains("end")==1) {k=-2; continue;}
	TString outname=infilename;
	infilename =  infilename+".root";

	cout<<dir<<infilename<<endl;
	cout<<outname<<endl;

	TFile *file1 =new TFile(dir+infilename);
	cout<<"open the file"<<endl;
	TTree *tree1 = (TTree*) file1->Get("outtree");
        cout<<"set tree"<<endl;
	tree m1(tree1);
        cout<<"OK"<<endl;
	m1.run(outname);
        cout<<"run"<<endl;
      }
}

int main(){
    runxx();
    return 1;
  }
