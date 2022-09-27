#include "rm.C"
#include <fstream>
void runxx(TString name) {
  TString filename;
  filename = name + ".root";
//  TFile*file = new TFile("/home/pku/anying/cms/file_in_cms/cutla/cutla-out"+filename);
  TFile*file = new TFile("/home/pku/anying/cms/file_in_cms/files_weighted/out"+filename);
  TTree*tree=(TTree*)file->Get("demo");
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
//	runxx("plj_mu");
//	runxx("Data");

	return 1;
}

