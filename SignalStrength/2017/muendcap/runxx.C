#include "rm.C"
#include <fstream>
void runxx(TString dir,TString name) {
  TString filename;
  filename = name + ".root";
//  TFile*file = new TFile("/eos/user/y/yian/2018cutla/cutla-out"+filename);
  TFile*file = new TFile(dir+filename);
  TTree*tree=(TTree*)file->Get("demo");
  cout<<"OK"<<endl;

  rm m1(tree);
  cout<<"OK"<<endl;
  cout<<filename<<endl;
  m1.Loop(name);

}

int main(){
//        TString sample[6]={"ZA-EWK","ST","VV","TTA","ZA_total","WA",};
      TString dir1 ="/eos/user/y/yian/2017cutla/cutla-out";
      TString dir2 ="/eos/user/y/yian/2017cutla/out";

	runxx(dir2,"ZA-EWK");
	runxx(dir1,"ST");
	runxx(dir1,"VV");
	runxx(dir1,"TTA");
	runxx(dir1,"ZA");
	runxx(dir1,"WA");
	runxx(dir1,"plj_muendcap");
	runxx(dir1,"DMuon");

	return 1;
}

