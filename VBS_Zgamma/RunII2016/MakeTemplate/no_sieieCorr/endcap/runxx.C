#include "MakeTemplate.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir="./rootfiles/";
TString dir="/eos/user/y/yian/2017cutla/";
ifstream infile("file");
string buffer;
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(( name.Contains("A") || name.Contains("Data"))==0) {k=-2; continue;}
TString filename="cutlep-out" + name+".root";
//TString filename= name+".root";
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
