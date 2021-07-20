#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void WWg::Loop(TString name,float number)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   Bool_t BSL_m=0,BSL_e=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000==0)cout<<jentry<<" "<<nentries<<endl;
      // if (Cut(ientry) < 0) continue;
      if(name.Contains("WJets")) scalef=1000.*61526.7/number*fabs(gen_weight)/gen_weight;
      if(name.Contains("DY")) scalef=1000.*6077.22/number*fabs(gen_weight)/gen_weight;
      if(name.Contains("TTJets")){ scalef=1000.*831.76/number*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTWJets")){ scalef=1000.*0.2043/number*fabs(gen_weight)/gen_weight;}

      if(fabs(lepton_pid)==13 && lepton_pt<25 && HLT_Mu8_TrkIsoVVL)
	      scalef=scalef*0.00856;//HLT_Mu8
      else if(fabs(lepton_pid)==13 && lepton_pt>25 && HLT_Mu17_TrkIsoVVL)
	      scalef=scalef*0.04578;//HLT_Mu17
      if(fabs(lepton_pid)==11 && lepton_pt<25 && HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30)
	      scalef=scalef*0.00641;//HLT_Ele8
      else if(fabs(lepton_pid)==11 && lepton_pt>25 && HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30)
	      scalef=scalef*0.03891;//HLT_Ele23

      if(name.Contains("Muon")||name.Contains("Ele")) { scalef=1.0;}

      if(name.Contains("Muon") && fabs(lepton_pid)!=13) continue;
      if(name.Contains("Ele") && fabs(lepton_pid)!=11) continue;

      BSL_m=(fabs(lepton_pid)==13 && lepton_pt>20 && fabs(lepton_eta)<2.4 && puppimet<30 && puppimt<30 && (HLT_Mu17_TrkIsoVVL||HLT_Mu8_TrkIsoVVL));
      BSL_e=(fabs(lepton_pid)==11 && lepton_pt>20 && fabs(lepton_eta)<2.5 && puppimet<30 && puppimt<30 && (HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 || HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30) );
      if( ! (BSL_m||BSL_e) )
        continue;          
      ExTree->Fill();
   }
}
