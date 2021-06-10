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
   Bool_t BSL=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(name.Contains("Mu")) { scalef=1.0;}
      if(name.Contains("Ele")){ scalef=1.0;}
      if(name.Contains("DY")) { scalef=1000.*6077.22/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WW")) { scalef=1000.*75.8/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WZ")) { scalef=1000.*27.6/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("ZZ")) { scalef=1000.*12.14/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTG")){ scalef=1000.*4.078/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("tZq")){ scalef=1000.*0.0758/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTWJets")){ scalef=1000.*0.2043/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TG")==1 && name.Contains("TTG")==0 ){ scalef=1000.*2.967/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WGJets")){ scalef=1000.*489/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("ZGJets")){ scalef=1000.*55.49/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WJets") && name.Contains("TTW")==0 ){ scalef=1000.*61526.7/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTJets")){ scalef=1000.*831.76/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WWG"))   { scalef=1000*0.402852/float(npp-nmm)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTGJets_f")){ scalef=0.0024552*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TGJets_f") && name.Contains("TTGJets_f")==0){ scalef=0.0079501*fabs(gen_weight)/gen_weight;}
      if(name.Contains("ZGJets_f")) { scalef=0.0032680*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WGJets_f")) { scalef=0.0297882 *fabs(gen_weight)/gen_weight;}
   
      HLT_mm = (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_ee = (HLT_Ele32_WPTight_Gsf) || (HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_emu = (HLT_Ele32_WPTight_Gsf) || (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL); 
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      BSL = (n_loose_ele+n_loose_mu)==2 && (HLT_mm || HLT_ee || HLT_emu);
      if( !( BSL ) )
	      continue;
      ExTree->Fill();
      // if (Cut(ientry) < 0) continue;
   }
}
