#include "rm.C"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void runxx(TString dir, TString filename,TString tag) {
TString outname="GenCutla-"+filename;
TFile *file1 =new TFile(dir+filename);
TTree *tree1 = (TTree*) file1->Get("treeDumper/ZPKUCandidates");
rm m1(tree1,outname,tag);
cout<<dir<<filename<<" "<<tag<<"->"<<outname<<endl;
m1.Loop(tag);
m1.endJob();
}

int main(){
	vector<TString> dir={"/home/pku/anying/cms/rootfiles/2016/","/home/pku/anying/cms/rootfiles/2017/","/home/pku/anying/cms/rootfiles/2018/"};
         vector<TString> filename={/*"ZA16.root","ZA-EWK16.root",*/"ZA_interf16.root",/*"ZA-EWK18.root","ZA18.root",*/"ZA_interf18.root"/*,"ZA17.root","ZA-EWK17.root",*/,"ZA_interf17.root"};
	 for(int i=0;i<filename.size();i++){
                 if(filename[i].Contains("16"))
			 runxx(dir[0],filename[i],"16");
                 else if(filename[i].Contains("17"))
			 runxx(dir[1],filename[i],"17");
                 else if(filename[i].Contains("18"))
			 runxx(dir[2],filename[i],"18");
	 }
	 return 1;
}

