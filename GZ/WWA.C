void WWA(){
TChain*chain=new TChain("Events");
chain->Add("/home/pku/guanz/wwaroot/final/lep/*.root");
TString cut="(nLepton>1&&nLepton<3 && Lepton_pt[0]>0&& Lepton_pt[1]>0 && Photon_pt>0 && nPhoton>0)";
Double mll,drl1a,drl2a;






}
