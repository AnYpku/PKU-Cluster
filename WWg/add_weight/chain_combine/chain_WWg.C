#define chain_WWg_cxx
#define Pi 3.1415926
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "get_btag_scale.C"
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
using namespace std;
void chain_WWg::Loop(TString name,double nevents,TString year,bool flag)
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
   TFile * f_eleID= TFile::Open("./SFs/20"+year+"/egammaEffi.txt_Ele_Medium_EGM2D"+VFP+".root");
   TH2F* ele_ID=0;
   f_eleID->GetObject("EGamma_SF2D", ele_ID);
   cout<<"open the ele ID file: egammaEffi.txt_Ele_Medium_EGM2D"+VFP+".root"<<endl;

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
   TFile* f_photonID = TFile::Open("./SFs/20"+year+"/egammaEffi.txt_EGM2D_Pho_Med_UL"+year+VFP+".root");
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

   TFile*fbtag=new TFile("btag_eff/eff_medium_b_jet"+year+".root");
   TH1D*hbeff=(TH1D*)fbtag->Get("b_jet_eff"+year);
   TFile*fctag=new TFile("btag_eff/eff_medium_c_jet"+year+".root");
   TH1D*hceff=(TH1D*)fctag->Get("c_jet_eff"+year);
   TFile*fltag=new TFile("btag_eff/eff_medium_l_jet"+year+".root");
   TH1D*hleff=(TH1D*)fltag->Get("l_jet_eff"+year);

   TFile*fbtag1=new TFile("btag_eff/eff_loose_b_jet"+year+".root");
   TH1D*hbeff1=(TH1D*)fbtag->Get("b_jet_eff"+year);
   TFile*fctag1=new TFile("btag_eff/eff_loose_c_jet"+year+".root");
   TH1D*hceff1=(TH1D*)fctag->Get("c_jet_eff"+year);
   TFile*fltag1=new TFile("btag_eff/eff_loose_l_jet"+year+".root");
   TH1D*hleff1=(TH1D*)fltag->Get("l_jet_eff"+year);

   Long64_t nbytes = 0, nb = 0;
   Bool_t BSL=0;
   int tot=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   Init();

	   bool isdata=0,isMC=0;
           if(name.Contains("Muon")==0 && name.Contains("Ele")==0 && name.Contains("MET")==0 && name.Contains("EGamma")==0 ) isMC=1;
           else isdata=1;

	   if(isdata) { scalef=1.0;}
	   if(name.Contains("Muon")||name.Contains("Ele")||name.Contains("EGamma") || name.Contains("MET")) { scalef=1.0;}
	   if(name.Contains("WZ")) { scalef=1000.*47.13/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ZZ")) { scalef=1000.*16.523/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TGJets")){ scalef=1000.*2.967/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TTG")){ scalef=1000.*3.697/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("tZq")){ scalef=1000.*0.0758/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ZGJets")){ scalef=1000.*55.49/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WGJets")){ scalef=1000.*489/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("DYJets")){ scalef=1000.*6077.22/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HWW")){ scalef=1000.*21.47/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGC")){ scalef=1000.*0.002464*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGC_NLO")){ scalef=1000.*0.00288*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGS")){ scalef=1000.*5.875e-06*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGD")){ scalef=1000.*4.371e-08*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGU")){ scalef=1000.*6.409e-08*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WJets") && name.Contains("TTW")==0 ){ scalef=1000.*61526.7/float(nevents)*fabs(gen_weight)/gen_weight;}
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
          

           double value,value1;
           if(year.Contains("18")){ value=0.4168;value1=0.1208;}
           else if(year.Contains("17")){ value=0.4506;value1=0.1355;}
           else if(year.Contains("16")){
		   if(name.Contains("pre")){ value=0.6001;value1=0.2027;}
		   else{value=0.5847;value1=0.1918;}
	   }
	   if( isMC ){
		   btag_weight_medium      = get_btag_scale(hbeff,hceff,hleff,value,nJet,Jet_btagDeepB,Jet_partonFlavour,Jet_btagSF_deepcsv_M,Jet_btagSF_deepcsv_M_up,Jet_btagSF_deepcsv_M_down,Jet_pt,"nominal");
		   btag_weight_medium_up   = get_btag_scale(hbeff,hceff,hleff,value,nJet,Jet_btagDeepB,Jet_partonFlavour,Jet_btagSF_deepcsv_M,Jet_btagSF_deepcsv_M_up,Jet_btagSF_deepcsv_M_down,Jet_pt,"up");
		   btag_weight_medium_down = get_btag_scale(hbeff,hceff,hleff,value,nJet,Jet_btagDeepB,Jet_partonFlavour,Jet_btagSF_deepcsv_M,Jet_btagSF_deepcsv_M_up,Jet_btagSF_deepcsv_M_down,Jet_pt,"down");

		   btag_weight_loose      = get_btag_scale(hbeff1,hceff1,hleff1,value1,nJet,Jet_btagDeepB,Jet_partonFlavour,Jet_btagSF_deepcsv_L,Jet_btagSF_deepcsv_L_up,Jet_btagSF_deepcsv_L_down,Jet_pt,"nominal");
		   btag_weight_loose_up   = get_btag_scale(hbeff1,hceff1,hleff1,value1,nJet,Jet_btagDeepB,Jet_partonFlavour,Jet_btagSF_deepcsv_L,Jet_btagSF_deepcsv_L_up,Jet_btagSF_deepcsv_L_down,Jet_pt,"up");
		   btag_weight_loose_down = get_btag_scale(hbeff1,hceff1,hleff1,value1,nJet,Jet_btagDeepB,Jet_partonFlavour,Jet_btagSF_deepcsv_L,Jet_btagSF_deepcsv_L_up,Jet_btagSF_deepcsv_L_down,Jet_pt,"down");
	   }

	   if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<" "<<photon_id_scale<<" "<<photon_id_scale_Up<<" "<<photon_id_scale_Down<<" ; btag SFs "<<btag_weight_medium<<" "<<btag_weight_loose <<endl;

           if(year.Contains("16") ){
                   HLT_ee = (HLT_Ele27_WPTight_Gsf) ;
                   HLT_mm = (HLT_IsoMu24 || HLT_IsoTkMu24);
                   if( isMC ){
                           HLT_emu = ( HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL || HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL || HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
                   }
                   else{
                           if(name.Contains("H"))
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

	   BSL = (channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && drll>0.5 && lep1pt>15 && lep2pt>15 && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 /*&& photonet>20 && ( (fabs(photoneta)<1.4442) || (fabs(photoneta)<2.5 && fabs(photoneta)>1.566) )*/);
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
   fbtag->Close();
   fctag->Close();
   fltag->Close();
   fbtag1->Close();
   fctag1->Close();
   fltag1->Close();
   cout<<nentries<<" "<<tot<<endl;
}
void chain_WWg::Init(){
	ele_id_scale=1;ele_id_scale_Up=1;ele_id_scale_Down=1;
	ele_reco_scale=1;ele_reco_scale_Up=1;ele_reco_scale_Down=1;
	muon_id_scale=1;muon_id_scale_Up=1;muon_id_scale_Down=1;
	muon_iso_scale=1;muon_iso_scale_Up=1;muon_iso_scale_Down=1;
	photon_id_scale=1;photon_id_scale_Up=1;photon_id_scale_Down=1;
	photon_veto_scale=1;photon_veto_scale_Up=1;photon_veto_scale_Down=1;
	btag_weight_medium=1;btag_weight_medium_up=1;btag_weight_medium_down=1;
	btag_weight_loose=1;btag_weight_loose_up=1;btag_weight_loose_down=1;
}
Float_t chain_WWg::delta_R(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2)
{
	Float_t dp = phi1-phi2;
	if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
	Float_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
	return dr;
}
