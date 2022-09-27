#define WWg_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "WWg.h"
#include "TLorentzVector.h"
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
#include "TRandom.h"
#define Pi 3.1415926
using namespace std;
void WWg::Loop(TString name,double nevents,TString year,bool flag)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
//   nentries=1000;
   TString VFP;
   if(flag && name.Contains("pre")) 
	   VFP="preVFP";
   else if(flag && year.Contains("16"))
	   VFP="postVFP";
   else
	   VFP="";
   // muon ID
   TFile * f_muonID= TFile::Open("./SFs/20"+year+"/Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ID"+VFP+".root");
   TH2F* muon_ID=0;
   f_muonID->GetObject("NUM_TightID_DEN_TrackerMuons_abseta_pt",muon_ID);
   cout<<"open the muon ID file: Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ID"+VFP+".root; "<<muon_ID->GetSum()<<endl;

   // muon iso
   TFile * f_muonIso= TFile::Open("./SFs/20"+year+"/Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ISO"+VFP+".root");
   TH2F* muon_ISO=0;
   f_muonIso->GetObject("NUM_TightRelIso_DEN_TightIDandIPCut_abseta_pt", muon_ISO);
   cout<<"open the muon ISO file: Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ISO"+VFP+".root"<<endl;

   // ele id
//   TFile * f_eleID= TFile::Open("./SFs/20"+year+"/egammaEffi.txt_Ele_Medium_EGM2D"+VFP+".root");
   TFile * f_eleID= TFile::Open("./SFs/20"+year+"/egammaEffi.txt_Ele_wp80iso_EGM2D_"+VFP+year+".root");
   TH2F* ele_ID=0;
   f_eleID->GetObject("EGamma_SF2D", ele_ID);
//   cout<<"open the ele ID file: egammaEffi.txt_Ele_Medium_EGM2D"+VFP+".root"<<endl;
   cout<<"open the ele ID file: egammaEffi.txt_Ele_wp80iso_EGM2D_"+VFP+year+".root"<<endl;

   //ele reco
   TFile* f_eleReco = TFile::Open("./SFs/20"+year+"/egammaEffi_ptAbove20.txt_EGM2D_UL20"+year+VFP+".root");
   TH2F* ele_Reco=0;
   f_eleReco->GetObject("EGamma_SF2D", ele_Reco);
   cout<<"open the ele RECO file: egammaEffi_ptAbove20.txt_EGM2D_UL20"+year+VFP+".root"<<endl;

   TFile* f_eleReco1 = TFile::Open("./SFs/20"+year+"/egammaEffi_ptBelow20.txt_EGM2D_UL20"+year+VFP+".root");
   TH2F* ele_Reco1=0;
   f_eleReco1->GetObject("EGamma_SF2D", ele_Reco1);
   cout<<"open the ele RECO file: egammaEffi_ptBelow20.txt_EGM2D_UL20"+year+VFP+".root"<<endl;

   //photon id
   TFile* f_photonID = TFile::Open("./SFs/20"+year+"/egammaEffi.txt_EGM2D_Pho_Medium_UL"+year+VFP+".root");
   TH2F* photon_ID=0;
   f_photonID->GetObject("EGamma_SF2D", photon_ID);
   cout<<"open the photon ID file: egammaEffi.txt_EGM2D_Pho_Med_UL"+year+VFP+".root"<<endl;
 
   TFile* f_pix = TFile::Open("./SFs/20"+year+"/HasPix_SummaryPlot_UL"+year+VFP+".root");
   TH1F*photon_pix=(TH1F*)f_pix->Get("MediumID/SF_HasPix_MediumID");
   TH1F*photon_stat=(TH1F*)f_pix->Get("MediumID/Staunc_HasPix_MediumID");
   TH1F*photon_pu=(TH1F*)f_pix->Get("MediumID/PUunc_HasPix_MediumID");
   TH1F*photon_model;
   if(year.Contains("16")==0)
	   photon_model=(TH1F*)f_pix->Get("MediumID/Modelunc_HasPix_MediumID");
   else
	   photon_model=(TH1F*)f_pix->Get("MediumID/PUunc_HasPix_MediumID");

   if(name.Contains("pre") && year.Contains("16"))
	   rc.init("roccor/RoccoR2016aUL.txt"); 
   else if(year.Contains("16")) 
	   rc.init("roccor/RoccoR2016bUL.txt");
   else if(year.Contains("17"))
	   rc.init("roccor/RoccoR2017UL.txt");
   else if(year.Contains("18"))
	   rc.init("roccor/RoccoR2018UL.txt");

   Long64_t nbytes = 0, nb = 0;
   Bool_t BSL=0;
   int tot=0;
   TLorentzVector Zp4, photonp4, jet1p4, jet2p4,lep1p4,lep2p4;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   float r1=gRandom->Rndm(jentry);
	   Init();
           bool isdata=0,isMC=0;
	   if(name.Contains("Muon")==0 && name.Contains("Ele")==0 && name.Contains("MET")==0 && name.Contains("EGamma")==0 ) isMC=1;
	   else isdata=1;
	   if(isdata) { scalef=1.0;}
	   if(name.Contains("WZ")) { scalef=1000.*4.429/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ZZTo2L")) { scalef=1000.*0.9738/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ZZTo4L")) { scalef=1000.*13.74/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WW")) { scalef=1000.*12.178/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TTG")){ scalef=1000.*3.697/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("tZq")){ scalef=1000.*0.0758/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ZGJets")){ scalef=1000.*55.49/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WGJets")){ scalef=1000.*489/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("DYJets")){ scalef=1000.*6077.22/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGC")){ scalef=1000.*0.00288*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGS")){ scalef=1000.*5.875e-06*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGD")){ scalef=1000.*4.371e-08*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGU")){ scalef=1000.*6.409e-08*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WJets")){ scalef=1000.*61526.7/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TTJets"))  { scalef=1000.*831.76/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WWG_emu")) { scalef=1000*0.074721/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ST_tW"))   { scalef=1000.*34.91/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ST_tbarW")){ scalef=1000.*34.91/float(nevents)*fabs(gen_weight)/gen_weight;}

	   if( isMC ){
		   ele_id_scale=get_ele_ID(lep2eta,lep2pt,ele_ID);
		   ele_id_scale_Up=get_ele_ID_up(lep2eta,lep2pt,ele_ID);
		   ele_id_scale_Down=get_ele_ID_down(lep2eta,lep2pt,ele_ID);
		   ele_reco_scale=get_ele_Reco(lep2eta,lep2pt,ele_Reco,ele_Reco1);
		   ele_reco_scale_Up=get_ele_Reco_up(lep2eta,lep2pt,ele_Reco,ele_Reco1);
		   ele_reco_scale_Down=get_ele_Reco_down(lep2eta,lep2pt,ele_Reco,ele_Reco1);
		   muon_id_scale=get_muon_ID(lep1eta,lep1pt,muon_ID);
		   muon_id_scale_Up=get_muon_ID_up(lep1eta,lep1pt,muon_ID);
		   muon_id_scale_Down=get_muon_ID_down(lep1eta,lep1pt,muon_ID);
		   muon_iso_scale=get_muon_iso(lep1eta,lep1pt,muon_ISO);
		   muon_iso_scale_Up=get_muon_iso_up(lep1eta,lep1pt,muon_ISO);
		   muon_iso_scale_Down=get_muon_iso_down(lep1eta,lep1pt,muon_ISO);
		   if(photonet>0){
			   photon_id_scale=get_photon_ID(photoneta,photonet,photon_ID);
			   photon_id_scale_Up=get_photon_ID_up(photoneta,photonet,photon_ID);
			   photon_id_scale_Down=get_photon_ID_down(photoneta,photonet,photon_ID);
			   photon_veto_scale_Up=get_photon_veto_up(photoneta,photon_pix,photon_stat,photon_pu,photon_model,year);
			   photon_veto_scale_Down=get_photon_veto_down(photoneta,photon_pix,photon_stat,photon_pu,photon_model,year);
			   if(fabs(photoneta)<1.4442) photon_veto_scale=photon_pix->GetBinContent(1);
			   if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=photon_pix->GetBinContent(4); 
		   }
	   }
          
	   if(year.Contains("16") ){
		   HLT_ee = (HLT_Ele27_WPTight_Gsf) ;
		   HLT_mm = (HLT_IsoMu24 || HLT_IsoTkMu24);
		   if( isMC ){
			   HLT_emu = ( HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL || HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
		   }
		   else if(isdata){
			   if(name.Contains("H")) //16 data era H
				   HLT_emu = ( HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
			   else
				   HLT_emu = ( HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL  );
		   }
	   }
	   else if(year.Contains("17")){
		   HLT_emu = ( HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ );
		   HLT_ee = ( HLT_Ele32_WPTight_Gsf_L1DoubleEG || HLT_Ele35_WPTight_Gsf);
		   HLT_mm = (HLT_IsoMu27);
	   }
	   else if(year.Contains("18")){
		   HLT_emu = ( HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
		   HLT_ee = ( HLT_Ele32_WPTight_Gsf );
		   HLT_mm = (HLT_IsoMu27);
	   }
	   int index=get_index(lep1pt,nMuon,Muon_pt);
           int pho_index=get_index(photonet,nPhoton,Photon_pt);
           if(jentry%10000==0 && photonet>0) cout<<jentry<<" "<<nentries<<", nPhoton "<<pho_index<<" "<<photonet<<" "<<Photon_pt[pho_index]<<endl;
	   muon1_rochester=get_rochester_scale(isdata, lep1_charge, lep1pt,lep1eta, lep1phi, Muon_nTrackerLayers[index] , r1);
           if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<" "<<photon_id_scale<<" "<<photon_id_scale_Up<<" "<<photon_id_scale_Down<<" ; btag SFs "<<btag_weight_medium<<" "<<btag_weight_loose <<" rochester "<<muon1_rochester<<"; index "<<index<<" "<<lep1pt<<" "<<Muon_pt[index]<<" nMuon "<<nMuon<<endl;

           lep1pt*=muon1_rochester;

	   lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
	   lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
	   mll=(lep1p4+lep2p4).M();
	   yVlep=(lep1p4+lep2p4).Eta();
	   phiVlep=(lep1p4+lep2p4).Phi();
	   ptll=(lep1p4+lep2p4).Pt();

	   Zp4.SetPtEtaPhiM(ptll, yVlep, phiVlep, mll);
	   photonp4.SetPtEtaPhiM(photonet, photoneta, photonphi,0);
	   mllg=(Zp4+photonp4).M();

	   BSL = (channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && drll>0.5 && lep1pt>10 && lep2pt>10 && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20);
	   if( !( BSL ) )
		   continue;

	   ExTree->Fill();
	   tot++;
	   // if (Cut(ientry) < 0) continue;
   }
   f_muonID->Close();
   f_muonIso->Close();
   f_eleID->Close();
   f_eleReco->Close();
   f_photonID->Close();
   f_pix->Close();
   cout<<nentries<<" "<<tot<<endl;
}
void WWg::Init(){
	ele_id_scale=1;ele_id_scale_Up=1;ele_id_scale_Down=1;
	ele_reco_scale=1;ele_reco_scale_Up=1;ele_reco_scale_Down=1;
	muon_id_scale=1;muon_id_scale_Up=1;muon_id_scale_Down=1;
	muon_iso_scale=1;muon_iso_scale_Up=1;muon_iso_scale_Down=1;
	photon_id_scale=1;photon_id_scale_Up=1;photon_id_scale_Down=1;
	photon_veto_scale=1;photon_veto_scale_Up=1;photon_veto_scale_Down=1;
	btag_weight_medium=1;btag_weight_medium_up=1;btag_weight_medium_down=1;
	btag_weight_loose=1;btag_weight_loose_up=1;btag_weight_loose_down=1;
        muon1_rochester=1;
}
Float_t WWg::delta_R(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2)
{
	Float_t dp = phi1-phi2;
	if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
	Float_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
	return dr;
}
float WWg::get_rochester_scale(bool isdata, float charge_temp, float pt, float eta, float phi, int nl, float r1)
{
        int charge = int(charge_temp/fabs(charge_temp));
        // data correction
        double corr;

        if(isdata)
           corr = rc.kScaleDT(charge, pt, eta, phi, 0, 0);

        // MC without genPT avalible
        if((!isdata))
                corr = rc.kSmearMC(charge, pt, eta, phi, nl, r1, 0, 0);
        return corr;
}
int WWg::get_index(float pt,int npar, float pt_ori[16]){
	int index=0;
	for(int i=0;i<npar;i++){
		if(pt-pt_ori[i]==0){
			index=i;
			break;
		}
	}
	return index;             
}
