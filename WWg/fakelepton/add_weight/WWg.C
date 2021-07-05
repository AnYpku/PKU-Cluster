#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
using namespace std;
void WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   Long64_t npp = fChain->GetEntries("gen_weight>0.");
   Long64_t nmm = fChain->GetEntries("gen_weight<0.");
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   Bool_t BSL=0,LEP=0,PHOTON=0;
   TFile*fele=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/fakelepton/fakerate/test_ele18.root");
   TH2D*hele=(TH2D*)fele->Get("TtoL");
   TFile*fmu=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/fakelepton/fakerate/test_mu18.root");
   TH2D*hmu=(TH2D*)fmu->Get("TtoL");
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cout<<jentry<<" "<<nentries<<endl;
      if(name.Contains("Ele")||name.Contains("Muon")) scalef=1;
      LEP = pass_selection>0 && lep1pt > 20. && lep2pt > 20. && fabs(lep1eta) < 2.5 && fabs(lep2eta) < 2.5 && (n_loose_ele+n_loose_mu)==2 ; 
      PHOTON = n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) );
      if( !( LEP /*&& PHOTON*/ ) )
	      continue;
      double lep1pt_tmp,lep2pt_tmp;
      if(lep1pt>200) lep1pt_tmp=199;
      else           lep1pt_tmp=lep1pt;
      if(lep2pt>200) lep2pt_tmp=199;
      else           lep2pt_tmp=lep2pt;       
      if(lep1_is_tight==0 && lep2_is_tight==0){
	      scalef=hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) * (-1);
      }
      else if(lep1_is_tight==0 && lep2_is_tight==1){
	      scalef=hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp)));
      }
      else if(lep1_is_tight==1 && lep2_is_tight==0){
	      scalef=hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp)));
      }
      else scalef=0;
      if(jentry%100==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;

      ExTree->Fill();
      // if (Cut(ientry) < 0) continue;
   }
}
