#include "rm.C"
#include <fstream>
void runxx(TString name) {
  TString filename;
  filename = name + ".root";
//  TFile*file = new TFile("/home/pku/anying/cms/file_in_cms/cutla/cutla-out"+filename);
  TChain*chain=new TChain("demo","");
  chain->Add("/eos/user/y/yian/2016cutla/out"+filename);
  chain->Add("/eos/user/y/yian/2017cutla/out"+filename);
  chain->Add("/eos/user/y/yian/2018cutla/out"+filename);
//  TFile*file = new TFile("/eos/user/y/yian/2016cutla/out"+filename);
//  TTree*tree=(TTree*)file->Get("demo");
  TTree*tree;
  tree=chain;
  cout<<"OK"<<endl;

  rm m1(tree);
  cout<<"OK"<<endl;
  cout<<filename<<endl;
  m1.Loop(name);

}

int main(){
//        TString sample[6]={"ZA-EWK","ST","VV","TTA","ZA_total","WA",};
	runxx("ZA-EWK");
//	runxx("ST");
//	runxx("VV");
//	runxx("TTA");
//	runxx("ZA_total");
//	runxx("WA");
//	runxx("plj");
//	runxx("Data");

	return 1;
}

