#include "xx.C"
#include <fstream>
void runxx() {
//gROOT->LoadMacro("xx.C");
TString dir="/data/pku/home/anying/cms/file_in_cms/cutLEP/";
ifstream infile("file");
string buffer; 
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(name.Contains("out")==0) {k=-2; continue;}
TString outname= name+"_plj.root";
TString inname=name+".root";
cout<<inname<<endl;
cout<<outname<<endl;

TFile *file1 =new TFile(dir+inname);
TTree *tree1 = (TTree*) file1->Get("demo");
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

