#include "rm.C"
#include <fstream>
void runxx(TString name) {
  TString filename;
  filename = name + ".root";
  TFile*file = new TFile("/eos/user/y/yian/2018cutla/cutla-out"+filename);
//  TFile*file = new TFile("/eos/user/y/yian/2018cutla/out"+filename);
  TTree*tree=(TTree*)file->Get("demo");
  cout<<"OK"<<endl;

  rm m1(tree);
  cout<<"OK"<<endl;
  cout<<filename<<endl;
  m1.Loop(name);

}

int main(){
//        TString sample[6]={"ZA-EWK","ST","VV","TTA","ZA_total","WA",};
//	runxx("ZA-EWK");
//	runxx("plj");
//	runxx("ST");
//	runxx("VV");
//	runxx("TTA");
//	runxx("ZA");
//	runxx("WA");
	runxx("Data18");

	return 1;
}

