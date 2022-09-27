#include "MakeTemplate.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir="/data/pku/home/anying/cms/file_in_cms/cutLEP/";
//TString dir="/data/pku/home/anying/cms/file_in_cms/files_weighted/";
TString dir = "./rootfiles/";
ifstream infile("file");
string buffer;
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(name.Contains("out")==0) {k=-2; continue;}
//TString filename= name+".root";
TString filename="T-"+ name+".root";
cout<<name<<endl;

TFile *file1 =new TFile(dir+filename);
cout<<" OK "<<endl;
TTree *tree1 = (TTree*) file1->Get("demo");
MakeTemplate m1(tree1);
cout<<" OK "<<endl;
cout<<filename<<endl;
m1.Loop(name);
m1.endJob();
  }
}
int main(){
    runxx();
    return 1;
  }
