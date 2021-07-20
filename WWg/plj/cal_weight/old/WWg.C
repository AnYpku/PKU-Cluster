#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;
void WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   Long64_t npp = fChain->GetEntries("gen_weight>0.");
   Long64_t nmm = fChain->GetEntries("gen_weight<0.");
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   Bool_t BSL=0,LEP=0,PHOTON=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(name.Contains("Ele")||name.Contains("Muon")) scalef=1;
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      LEP = lep1pt > 20. && lep2pt > 20. && fabs(lep1eta) < 2.5 && fabs(lep2eta) < 2.5 && (n_loose_ele+n_loose_mu)==2 ; 
      PHOTON = n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) ) && pass_selection1 && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) ;
      if( !( LEP && PHOTON ) )
	      continue;
      ExTree->Fill();
      // if (Cut(ientry) < 0) continue;
   }
}
