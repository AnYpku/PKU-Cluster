#include "MakeTemplate.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir="/home/pku/anying/cms/file_in_cms/cutLEP/";
//TString dir = "./rootfiles/";
ifstream infile("file");
string buffer;
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(name.Contains("Z")==0 && name.Contains("Muon")==0) {k=-2; continue;}
//TString filename="T-cutlep-out"+ name+".root";
TString filename="cutlep-out"+ name+".root";
cout<<name<<endl;

TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("demo");
MakeTemplate m1(tree1);
cout<<filename<<endl;
m1.Loop(name);
m1.endJob();
  }
}
int main(){
    runxx();
    return 1;
  }
