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
if(infilename.Contains("root")==0) {k=-2; continue;}
if(infilename.Contains("end")==1) {k=-2; break;}
TString filename ="cutlep-"+infilename;
TString outname="cutla-"+infilename;

cout<<dir<<infilename<<" -> "<<outname<<endl;

TFile *file1 =new TFile(dir+filename);
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

