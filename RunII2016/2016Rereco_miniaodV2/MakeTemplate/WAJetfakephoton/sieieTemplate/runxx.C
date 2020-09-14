#include "MakeTemplate.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
//TString dir="/data/pku/home/anying/cms/file_in_cms/files_weighted/";
TString dir = "/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAJetfakephoton/drawSR/";
ifstream infile("file");
string buffer;
TString name;
int k=2;

   while(k>0){
      getline (infile, buffer) ;
      name = buffer;
      if(name.Contains("out")){ 
         TString filename= name+".root";
         cout<<name<<endl;
         TString outname = "T1"+filename; 
         TFile *file1 =new TFile(dir+filename);
         TTree *tree1 = (TTree*) file1->Get("demo");
         MakeTemplate m1(tree1,outname);
         cout<<filename<<endl;
	 m1.Loop(outname);
         m1.endJob(outname);
        }
      if(name.Contains("end")){
         k=-2;continue;
       }
    }
 }
int main(){
    runxx();
    return 1;
  }
