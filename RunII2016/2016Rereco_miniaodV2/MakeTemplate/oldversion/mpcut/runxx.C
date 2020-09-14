#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(){
TString dir ="/data/pku/home/anying/cms/file_in_cms/";
ifstream infile("file");
string buffer;
TString infilename;

int k=1;

while (k>0){
getline (infile, buffer) ;
infilename = buffer;
if(infilename.Contains(".root")==0) {k=-2; continue;}
TString outname= infilename;

cout<<infilename<<endl;
TFile *file1 =new TFile(dir+infilename);
cout<<"OK1"<<endl;
//TDirectory * dir1 = (TDirectory*)file1->Get("treeDumper");
cout<<"OK2"<<endl;
TTree *tree1 = (TTree*)file1->Get("PKUCandidates");
cout<<"OK3"<<endl;
cout<<outname<<endl;
xx m1(tree1,outname);
m1.Loop(infilename);
cout<<"OK4"<<endl;
m1.endJob(infilename);

  }
}

int main()
   {
    runxx();
    return 1;
  }

