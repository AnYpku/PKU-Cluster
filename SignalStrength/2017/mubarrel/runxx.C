#include "rm.C"
#include <fstream>
void runxx(TString name,TString dir) {
  TString filename;
  filename = name + ".root";
  TFile*file=new TFile(dir+name+".root") ;
  TTree*tree=(TTree*)file->Get("demo");
  cout<<"OK"<<endl;

  rm m1(tree);
  cout<<"OK"<<endl;
  cout<<filename<<endl;
  m1.Loop(name);

}

int main(){
	TString dir =  "/eos/user/y/yian/2017cutla/cutla-out";
	TString dir1 = "/eos/user/y/yian/2017cutla/out";
//	runxx("ZA-EWK",dir1);
//	runxx("ST",dir);
//	runxx("VV",dir);
//	runxx("TTA",dir);
//	runxx("ZA",dir);
//	runxx("WA",dir);
	runxx("plj_mubarrel",dir);
//	runxx("DMuon");

	return 1;
}

