#include "rm.C"
#include <fstream>
void runxx(TString name,TString dir) {
  TString filename;
  filename = name + ".root";
//  TFile*file = new TFile("/eos/user/y/yian/2017cutla/cutla-out"+filename);
  TFile*file = new TFile(dir+filename);
  TTree*tree=(TTree*)file->Get("demo");
  cout<<"OK"<<endl;

  rm m1(tree);
  cout<<"OK"<<endl;
  cout<<filename<<endl;
  m1.Loop(name);

}

int main(){
  TString dir1="/eos/user/y/yian/2017cutla/cutla-out";
  TString dir2="/eos/user/y/yian/2017cutla/out";
//        TString sample[6]={"ZA-EWK","ST","VV","TTA","ZA_total","WA",};
	runxx("ZA-EWK-pweight",dir2);
//	runxx("ST",dir1);
//	runxx("VV",dir1);
//	runxx("TTA",dir1);
//	runxx("ZA",dir1);
//	runxx("WA",dir1);
//	runxx("plj",dir1);

	return 1;
}

