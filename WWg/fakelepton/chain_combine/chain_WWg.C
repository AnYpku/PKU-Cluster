#define chain_WWg_cxx
#include "chain_WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
using namespace std;
void chain_WWg::Loop(TString name,float number,TString year)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   Bool_t BSL_m=0,BSL_e=0,HLT_Mu1,HLT_Mu2,HLT_Ele1,HLT_Ele2;
   double mu_preSF_1=1,mu_preSF_2=1,ele_preSF_1=1,ele_preSF_2=1;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(name.Contains("WJets")) scalef=1000.*61526.7/number*fabs(gen_weight)/gen_weight;
      if(name.Contains("DY")) scalef=1000.*6077.22/number*fabs(gen_weight)/gen_weight;
      if(name.Contains("TTJets")){ scalef=1000.*831.76/number*fabs(gen_weight)/gen_weight;}

      if(year.Contains("18")){
              mu_preSF_1=0.00856; mu_preSF_2=0.04578;
              ele_preSF_1=0.00641;ele_preSF_2=0.03891;
              HLT_Mu1=HLT_Mu8_TrkIsoVVL; HLT_Mu2=HLT_Mu17_TrkIsoVVL;
              HLT_Ele1=HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;
              HLT_Ele2=HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
      }
      if(year.Contains("17")){
              mu_preSF_1=0.00290; mu_preSF_2=0.06594;
              ele_preSF_1=0.00397;ele_preSF_2=0.04347;
              HLT_Mu1=HLT_Mu8_TrkIsoVVL; HLT_Mu2=HLT_Mu17_TrkIsoVVL;
              HLT_Ele1=HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;
              HLT_Ele2=HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
      }
      if(year.Contains("16")){
              mu_preSF_1=0.0078; mu_preSF_2=0.21675;
              ele_preSF_1=0.01485;ele_preSF_2=0.06281;
              HLT_Mu1=HLT_Mu8_TrkIsoVVL; HLT_Mu2=HLT_Mu17_TrkIsoVVL;
              HLT_Ele1=HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;
              HLT_Ele2=HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
      }

      if(fabs(lepton_pid)==13 && lepton_pt<20 && HLT_Mu1)
              scalef=scalef*mu_preSF_1;//HLT_Mu8
      else if(fabs(lepton_pid)==13 && lepton_pt>20 && HLT_Mu2)
              scalef=scalef*mu_preSF_2;//HLT_Mu17
      if(fabs(lepton_pid)==11 && lepton_pt<25 && HLT_Ele1)
              scalef=scalef*ele_preSF_1;//HLT_Ele8 || HLT_Ele12
      else if(fabs(lepton_pid)==11 && lepton_pt>25 && HLT_Ele2)
              scalef=scalef*ele_preSF_2;//HLT_Ele23

      if(name.Contains("Muon")||name.Contains("Ele")||name.Contains("EGamma")) { scalef=1.0;}

      if(name.Contains("Muon") && fabs(lepton_pid)!=13) continue;
      if(name.Contains("Ele") && fabs(lepton_pid)!=11) continue;
      if(name.Contains("EGamma") && fabs(lepton_pid)!=11) continue;
      double pfmet,pfmetphi,pfmT;
      double puppimet,puppimetphi,puppimT;
      if(name.Contains("Jets")){
	      pfmet   =MET_T1Smear_pt;
	      pfmetphi=MET_T1Smear_phi;
	      pfmT=sqrt(2*(lepton_pt*pfmet*(1-cos(lepton_phi-pfmetphi) ) ) );
      }
      else if(name.Contains("Muon")||name.Contains("Ele")||name.Contains("EGamma")){
	      pfmet   =MET_T1_pt;
	      pfmetphi=MET_T1_phi;
	      pfmT=sqrt(2*(lepton_pt*pfmet*(1-cos(lepton_phi-pfmetphi) ) ) );
      }
      puppimet   =PuppiMET_pt;
      puppimetphi=PuppiMET_phi;
      puppimT=sqrt(2*(lepton_pt*puppimet*(1-cos(lepton_phi-puppimetphi) ) ) );
      if(jentry%10000==0){
	      cout<<name<<" "<<jentry<<" "<<nentries<<" "<<" "<<scalef<<" "<<met<<" "<<pfmT<<" "<<puppimT<<endl;
      }
      BSL_m=(fabs(lepton_pid)==13 && lepton_pt>10 && fabs(lepton_eta)<2.4 && (pfmet < 40 || puppimet < 40) && ( pfmT < 40 || puppimT < 40 ) && ( HLT_Mu1 ||HLT_Mu2 ) );
      BSL_e=(fabs(lepton_pid)==11 && lepton_pt>10 && fabs(lepton_eta)<2.5 && (pfmet < 40 || puppimet < 40) && ( pfmT < 40 || puppimT < 40 ) && ( HLT_Ele1 || HLT_Ele2 ) );

      if( ! (BSL_m||BSL_e) )
        continue;
      ExTree->Fill();
   }
   cout<<name<<" run finished"<<endl;
}
