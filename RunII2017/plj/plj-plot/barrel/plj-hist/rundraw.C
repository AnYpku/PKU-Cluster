#include "draw.C"
#include <iostream>
#include <fstream>
using namespace std;
void runjet() {
TString dir="/eos/user/y/yian/2017cutla/";

ifstream infile("file");
string buffer; 
TString name;

int k=1;

while (k>0){
getline (infile, buffer) ;
name = buffer;
if(name.Contains("out")==0) {k=-2; continue;}
TString inname;
//if(name.Contains("plj")) {inname = name +".root";}
//else {inname = "cutla-" + name +".root";}
inname = name +".root";
TString outname = name+"_barrel.root";
cout<<name<<endl;
cout<<outname<<endl;
TFile *file1 =new TFile(dir+inname);
TTree *tree1 = (TTree*) file1->Get("demo");
draw m1(tree1,outname);
m1.Loop(name);
m1.endJob();

 
}

}
int main(){
  runjet();
  return 1;
}

