#include "MakeTemplate.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx() {
TString dir="/data/pku/home/anying/cms/file_in_cms/files_weighted/";
ifstream infile("file");
string buffer;
TString name;
TString sss;
/*Double_t lowpt[ptnumber]= {15,20,25,30,35,40,45,50,60,80,120};
Double_t highpt[ptnumber]={20,25,30,35,40,45,50,60,80,120,400};*/

int k=2;

   while(k>0){
      getline (infile, buffer) ;
      name = buffer;
      if(name.Contains("out")){ 
         TString filename= name+".root";
         cout<<name<<endl;
         TString outname = "Twa-"+filename; 
         TFile *file1 =new TFile(dir+filename);
         TTree *tree1 = (TTree*) file1->Get("demo");
         MakeTemplate m1(tree1,outname);
         cout<<filename<<endl;
	 m1.Loop(name);
         m1.endJob(name);
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
