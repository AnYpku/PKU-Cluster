#include "xx.C"
#include <iostream>
#include <fstream>
using namespace std;

void runxx(TString name) {
	TString dir = "/eos/user/y/yian/2016cutla/cutla-outplj";
	TFile*file=new TFile(dir+name+".root");
	TTree *tree1 = (TTree*) file->Get("demo");
	xx m1(tree1);
	m1.Loop(name);
}
int main(){
    runxx("ele_down");
    runxx("ele_up");
    runxx("ele");
    return 1;
  }
