#define ee_cxx
#include "ee.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "L1_weight.C"
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
#include <TRandom.h>
#include "TLorentzVector.h"
//#include <gRandom.h>
#include <TH2F.h>
#include <TGraphAsymmErrors.h>
#include <TObject.h>
#define Pi 3.1415926

using namespace std;
void ee::Loop()
{
//   In a ROOT session, you can do:
//      root> .L xx.C
//      root> xx t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   SetValue();
   Long64_t nentries = fChain->GetEntriesFast();
   npp = fChain->GetEntries("theWeight>0.");
   nmm = fChain->GetEntries("theWeight<0.");
   std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;

   input13= new TFile ("./pu_calc/puweight.root");
   input13->GetObject("h2",h13);

   f_BF= new TFile("./muon_SFs/ID_eff_BCDEF.root");
   d_ID_BF =(TDirectoryFile*)f_BF->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta");
   d_ID_BF->GetObject("abseta_pt_ratio", ID_BF);

   f_GH= new TFile("./muon_SFs/ID_eff_GH.root");
   d_ID_GH=(TDirectoryFile*)f_GH->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta");
   d_ID_GH->GetObject("abseta_pt_ratio", ID_GH);

   f_iso_BF= new TFile("./muon_SFs/ISO_eff_BCDEF.root");
   d_ISO_BF=(TDirectoryFile*)f_iso_BF->Get("TightISO_TightID_pt_eta");
   d_ISO_BF->GetObject("abseta_pt_ratio", iso_BF);
   f_iso_GH= new TFile("./muon_SFs/ISO_eff_GH.root");
   d_ISO_GH=(TDirectoryFile*)f_iso_GH->Get("TightISO_TightID_pt_eta");
   d_ISO_GH->GetObject("abseta_pt_ratio", iso_GH);

   Track_eff= new TFile("./muon_SFs/Tracking_EfficienciesAndSF_BCDEFGH.root");
   Track_eff->GetObject("ratio_eff_aeta_dr030e030_corr",track_SF);

   trigger_eff = new TFile("./muon_SFs/di_lep_trigger.root");
   trigger_eff->GetObject("2Dh2",di_lep_trigger);

   f= new TFile("./ele_SFs/mediumID_egamma.root");
   f->GetObject("EGamma_SF2D", ID);

   Reco_egamma= new TFile("./ele_SFs/reco_egamma.root");
   Reco_egamma->GetObject("EGamma_SF2D", Reco);

   ID_photon_file = new TFile("./ele_SFs/photon_ID_SFs.root");
   ID_photon_file->GetObject("EGamma_SF2D", ID_photon);

   int cut0=0,cut1=0,cut2=0,cut3=0,cut4=0;
   bool LEP,JET,PHOTON,SignalRegion,DR;
   Double_t drll,drjj,detajj,ZGmass,delta_phi;
   TLorentzVector Zp4, photonp4, jet1p4, jet2p4, lep1p4, lep2p4;
//  nentries=1000;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cut0++;//total events, cut0=t1->GetEntries()
      addWeight();
      test = gRandom->Gaus(0,1);
if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu1<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;
      //scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight;
      //run_period=8;
      if(drla==10) drla=0;
      if(drla2==10) drla2=0; 
      if(drj1a==10) drj1a=-1;
      if(drj2a==10) drj2a=-1;

      lep1p4.SetPtEtaPhiM(ptlep1, etalep1, philep1, 0.105666);
      lep2p4.SetPtEtaPhiM(ptlep2, etalep2, philep2, 0.105666);
      massVlep=(lep1p4+lep2p4).M();
      yVlep=(lep1p4+lep2p4).Eta();
      phiVlep=(lep1p4+lep2p4).Phi();
      ptVlep=(lep1p4+lep2p4).Pt();
      detajj = fabs(jet1eta - jet2eta);
      if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
      else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

      if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
      else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));
      jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
      jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
      Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
      photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
      delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
      ZGmass=(Zp4+photonp4).M();
      if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;

      LEP = drll>0.3 && l1_weight==1 && lep == 13 && HLT_Mu2 > 0 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110.;   
      SignalRegion= Mjj>500 && deltaeta>2.5 && zepp<1.8;
      PHOTON= photonet>25 &&( /*(fabs(photoneta)<2.5&&fabs(photoneta)>1.566) ||*/ (fabs(photoneta)<1.4442) );
      JET=jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
      DR =drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5;
      //if (drll>0.3 && l1_weight==1&&lep == 13 && HLT_Mu2 > 0 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 25. && fabs(photoneta) < 1.4442 && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 400 && drjj > 0.5 && drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5&& detajj>2.5&& zepp<1.8/* && ZGmass>100*/)
         {
             if(LEP) cut0++;
             if(PHOTON) cut3++; 
             if(LEP&&PHOTON) cut1++;
             if(LEP&&PHOTON&&JET)cut2++;//how many events passing the selection 
             if(LEP&&PHOTON&&JET&&SignalRegion&&DR)
               { cut4++;//how many events passing the selection 
                 ExTree->Fill(); //fill the brach when this entry pass the both selection
	       }
//                 cout<<"jentry = "<<jentry<<"; cut1 = "<<cut1<<endl;
         }

    }
   cout<<"LEP "<<cut0<<endl;
   cout<<"PHOTON "<<cut3<<endl;
   cout<<"LEP&&PHOTON "<<cut1<<endl;
   cout<<"LEP&&PHOTON&&JET "<<cut2<<endl;
   cout<<"LEP&&PHOTON&&JET&&SignalRegion&&DR "<<cut4<<endl;
}
void ee::addWeight(){

		// set lep and photon scale to -1 for default
		ele1_id_scale=-1;
		ele2_id_scale=-1;
		ele1_reco_scale=-1;
		ele2_reco_scale=-1;
		muon1_id_scale=-1;
		muon2_id_scale=-1;
		muon1_iso_scale=-1;
		muon2_iso_scale=-1;
		muon1_track_scale=-1;
		muon2_track_scale=-1;
		muon_hlt_scale=-1;
		photon_id_scale=-1;

		lep1_phi_station2_tmp = lep1_phi_station2;
		lep2_phi_station2_tmp = lep2_phi_station2;

		/*if(m_dataset=="outDMuonB.root"){ scalef=1.0; run_period=1;}
		if(m_dataset=="outDMuonC.root"){ scalef=1.0; run_period=2;}
		if(m_dataset=="outDMuonD.root"){ scalef=1.0; run_period=3;}
		if(m_dataset=="outDMuonE.root"){ scalef=1.0; run_period=4;}
		if(m_dataset=="outDMuonF.root"){ scalef=1.0; run_period=5;}
		if(m_dataset=="outDMuonG.root"){ scalef=1.0; run_period=6;}
		if(m_dataset=="outDMuonH.root"){ scalef=1.0; run_period=7;}

		if(m_dataset=="outDEleB.root"){ scalef=1.0; run_period=1;}
		if(m_dataset=="outDEleC.root"){ scalef=1.0; run_period=2;}
		if(m_dataset=="outDEleD.root"){ scalef=1.0; run_period=3;}
		if(m_dataset=="outDEleE.root"){ scalef=1.0; run_period=4;}
		if(m_dataset=="outDEleF.root"){ scalef=1.0; run_period=5;}
		if(m_dataset=="outDEleG.root"){ scalef=1.0; run_period=6;}
		if(m_dataset=="outDEleH.root"){ scalef=1.0; run_period=7;}

		if(m_dataset=="outWAJ2.root"){ scalef=1000.*405.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWAJ-fxfx.root"){ scalef=1000.*178.6/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWJets.root"){ scalef=1000.*61526.7/float(npp-nmm)*fabs(theWeight)/theWeight;run_period=8; }
		if(m_dataset=="outZJets.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZJets_FX.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outprivate_ZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outofficial_ZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outTTA.root"){ scalef=1000.*3.697/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outTTJets.root"){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTs.root"){ scalef=1000.*3.36/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTtbarw.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTtw.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTt.root"){ scalef=1000.*136.02/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTtbar.root"){ scalef=1000.*80.95/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWW.root"){ scalef=1000.*118.7/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWZ.root"){ scalef=1000.*47.13/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZZ.root"){ scalef=1000.*16.523/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}*/
		if(m_dataset=="outZA-EWK.root"){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("JEC")){ 
                  scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
                //else cout<<"failed"<<endl;
		if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
		if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
		l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
		/*if(m_dataset !="outDMuonB.root" && m_dataset !="outDMuonC.root" && m_dataset !="outDMuonD.root" && m_dataset !="outDMuonE.root" && m_dataset !="outDMuonF.root" && m_dataset !="outDMuonG.root" && m_dataset !="outDMuonH.root"&&m_dataset !="outDEleB.root" && m_dataset !="outDEleC.root" && m_dataset !="outDEleD.root" && m_dataset !="outDEleE.root" && m_dataset !="outDEleF.root" && m_dataset !="outDEleG.root" && m_dataset !="outDEleH.root" ){	
			pileupWeight=h13->GetBinContent(h13->GetXaxis()->FindBin(npT));
			// cout<<pileupWeight<<endl;
		}
		else {pileupWeight=-1;}*/
		pileupWeight=h13->GetBinContent(h13->GetXaxis()->FindBin(npT));
		// cout<<pileupWeight<<endl;
		//////  lep and photon scales
		if(lep==11){
			ele1_id_scale=get_ele_ID(etalep1, ptlep1, ID);
			ele2_id_scale=get_ele_ID(etalep2, ptlep2, ID);
			ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco);
			ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco);
		}
		if(lep==13){
			muon1_id_scale=get_muon_ID(etalep1,ptlep1,ID_BF,ID_GH);
			muon2_id_scale=get_muon_ID(etalep2,ptlep2,ID_BF,ID_GH);
			muon1_iso_scale=get_muon_iso(etalep1,ptlep1,iso_BF,iso_GH);
			muon2_iso_scale=get_muon_iso(etalep2,ptlep2,iso_BF,iso_GH);
			muon1_track_scale=get_muon_track_scale(etalep1,track_SF);
			muon2_track_scale=get_muon_track_scale(etalep2,track_SF);
			muon_hlt_scale=muon_HLT_scale(etalep1,etalep2,di_lep_trigger);
		}

		if(photonet>0) photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);
		//////  lep and photon scacles
/*
		// for rochester muon correstion
		if(m_dataset.Contains("DEle")) {mu1_rochester_scale=-1e2;mu2_rochester_scale=-1e2;}
		if(m_dataset.Contains("DMuon")) {
			mu1_rochester_scale=get_rochester_scale(true, lep1_sign, ptlep1,etalep1, philep1, muon1_trackerLayers, matchedgenMu1_pt,r1, r2);
			mu2_rochester_scale=get_rochester_scale(true, lep2_sign, ptlep2,etalep2, philep2, muon2_trackerLayers, matchedgenMu2_pt,r1, r2);
		}
		if(!(m_dataset.Contains("DEle")||m_dataset.Contains("DMuon")) && lep==13){
			mu1_rochester_scale=get_rochester_scale(false, lep1_sign, ptlep1,etalep1, philep1, muon1_trackerLayers, matchedgenMu1_pt,r1, r2);
                        mu2_rochester_scale=get_rochester_scale(false, lep2_sign, ptlep2,etalep2, philep2, muon2_trackerLayers, matchedgenMu2_pt,r1, r2);
		}
		if(!(m_dataset.Contains("DEle")||m_dataset.Contains("DMuon")) && lep!=13){mu1_rochester_scale=-1e2;mu2_rochester_scale=-1e2;}
*/
}
void ee::SetValue(){
	scalef=-10;
        run_period=-10;
	lep1_phi_station2_tmp=0;
	lep2_phi_station2_tmp=0;
	h13 = NULL;
	ID_BF=0;
	ID_GH=0;
	iso_BF=0;
	iso_GH=0;
	track_SF=0;
	di_lep_trigger=0;  
	ID=0;
	Reco=0;
	ID_photon=0;

}
