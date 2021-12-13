#define WWg_cxx
#include "genparticles.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
using namespace std;
void WWg::Loop(TString name,double nevents,TString year)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
//   nentries=1000;
   // muon ID
   TFile * f_muonID= TFile::Open("./SFs/20"+year+"/Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ID.root");
   TH2F* muon_ID=0;
   f_muonID->GetObject("NUM_TightID_DEN_TrackerMuons_abseta_pt",muon_ID);
   cout<<"open the muon ID file: Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ID.root; "<<muon_ID->GetSum()<<endl;

   // muon iso
   TFile * f_muonIso= TFile::Open("./SFs/20"+year+"/Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ISO.root");
   TH2F* muon_ISO=0;
   f_muonIso->GetObject("NUM_TightRelIso_DEN_TightIDandIPCut_abseta_pt", muon_ISO);
   cout<<"open the muon ISO file: Efficiencies_muon_generalTracks_Z_Run20"+year+"_UL_ISO.root"<<endl;

   // ele id
   TFile * f_eleID= TFile::Open("./SFs/20"+year+"/egammaEffi.txt_Ele_Medium_EGM2D.root");
   TH2F* ele_ID=0;
   f_eleID->GetObject("EGamma_SF2D", ele_ID);
   cout<<"open the ele ID file: egammaEffi.txt_Ele_Medium_EGM2D.root"<<endl;

   //ele reco
   TFile* f_eleReco = TFile::Open("./SFs/20"+year+"/egammaEffi_ptAbove20.txt_EGM2D_UL20"+year+".root");
   TH2F* ele_Reco=0;
   f_eleReco->GetObject("EGamma_SF2D", ele_Reco);
   cout<<"open the ele RECO file: egammaEffi_ptAbove20.txt_EGM2D_UL20"+year+".root"<<endl;

   //photon id
   TFile* f_photonID = TFile::Open("./SFs/20"+year+"/egammaEffi.txt_EGM2D_Pho_Med_UL"+year+".root");
   TH2F* photon_ID=0;
   f_photonID->GetObject("EGamma_SF2D", photon_ID);
   cout<<"open the photon ID file: egammaEffi.txt_EGM2D_Pho_Med_UL"+year+".root"<<endl;
 
   TFile* f_pix = TFile::Open("./SFs/20"+year+"/HasPix_SummaryPlot_UL"+year+".root");
   TH1F*photon_pix=(TH1F*)f_pix->Get("MediumID/SF_HasPix_MediumID");
   TH1F*photon_stat=(TH1F*)f_pix->Get("MediumID/Staunc_HasPix_MediumID");
   TH1F*photon_pu=(TH1F*)f_pix->Get("MediumID/PUunc_HasPix_MediumID");
   TH1F*photon_model=(TH1F*)f_pix->Get("MediumID/Modelunc_HasPix_MediumID");

   TFile*fbtag=new TFile("eff_b_jet"+year+".root");
   TH1D*hbeff=(TH1D*)fbtag->Get("b_jet_eff"+year);
   TFile*fctag=new TFile("eff_c_jet"+year+".root");
   TH1D*hceff=(TH1D*)fctag->Get("c_jet_eff"+year);
   TFile*fltag=new TFile("eff_l_jet"+year+".root");
   TH1D*hleff=(TH1D*)fltag->Get("l_jet_eff"+year);

   Long64_t nbytes = 0, nb = 0;
   Bool_t BSL=0;
   Bool_t GenLEP=0,GenPHOTON=0,GenMET=0,GenJET=0;
   Bool_t LEP=0,PHOTON=0,MET=0,JET=0;
   int tot=0,nlep=0,nphoton=0;
   TLorentzVector Zp4, photonp4, lep1p4, lep2p4;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
           ResetValue();
	   Init();
           genparticles();

	   lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
	   lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
	   yVlep=(lep1p4+lep2p4).Eta();
	   phiVlep=(lep1p4+lep2p4).Phi();
	   ptVlep=(lep1p4+lep2p4).Pt();
	   mll=(lep1p4+lep2p4).M();
	   photonp4.SetPtEtaPhiM(photonet, photoneta, photonphi,0);
           Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, mll);
	   mllg=(Zp4+photonp4).M();

	   genmT=sqrt(2*(genptll*GenMET_pt*(1-cos(genphiVlep-GenMET_phi) ) ) );
	   mT=sqrt(2*(ptll*PuppiMET_T1Smear_pt*(1-cos(phiVlep-PuppiMET_T1Smear_phi) ) ) );

	   if(genlep1>genlep2)
		   genmT2=sqrt(2*(genlep2pt*GenMET_pt*(1-cos(genlep2phi-GenMET_phi) ) ) );
           else
                   genmT2=sqrt(2*(genlep2pt*GenMET_pt*(1-cos(genlep2phi-GenMET_phi) ) ) );

	   if(lep1pt>lep2pt)
		   mT2=sqrt(2*(lep2pt*PuppiMET_T1Smear_pt*(1-cos(lep2phi-PuppiMET_T1Smear_phi) ) ) );
	   else
		   mT2=sqrt(2*(lep1pt*PuppiMET_T1Smear_pt*(1-cos(lep1phi-PuppiMET_T1Smear_phi) ) ) );

	   HLT_emu1=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
	   HLT_emu2=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
	   HLT_emu3=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
	   HLT_emu4=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;

	   if(name.Contains("Mu")) { scalef=1.0;}
	   if(name.Contains("Ele")){ scalef=1.0;}
	   if(name.Contains("WW")&&name.Contains("G")==0&&name.Contains("L")==0) { scalef=1000.*75.8/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WWTo")) { scalef=1000.*11.09/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WZ")) { scalef=1000.*47.13/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ZZ")) { scalef=1000.*16.523/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TTG")){ scalef=1000.*3.697/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("tZq")){ scalef=1000.*0.0758/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TTWJets")){ scalef=1000.*0.2043/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TG")==1 && name.Contains("TTG")==0 ){ scalef=1000.*2.967/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ZGJets")){ scalef=1000.*55.49/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WGJets")){ scalef=1000.*489/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("DYJets")){ scalef=1000.*6077.22/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HWW")){ scalef=1000.*21.47/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGC")){ scalef=1000.*0.002464*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGC_NLO")){ scalef=1000.*0.00288*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGS")){ scalef=1000.*5.875e-06*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGD")){ scalef=1000.*4.371e-08*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("HGU")){ scalef=1000.*6.409e-08*0.01055/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("DYtau")) { scalef=1000.*1967.3/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WJets") && name.Contains("TTW")==0 ){ scalef=1000.*61526.7/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("TTJets"))  { scalef=1000.*831.76/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("WWG_emu")) { scalef=1000*0.074721/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ST"))      { scalef=1000.*34.91/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ST_tW"))   { scalef=1000.*34.91/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("ST_tbarW")){ scalef=1000.*34.91/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("STt"))     { scalef=1000.*113.3/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("STbart"))  { scalef=1000.*67.91/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("STs"))     { scalef=1000.*3.74/float(nevents)*fabs(gen_weight)/gen_weight;}
	   if(name.Contains("MuonEGB") && year.Contains("17"))
		   HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL=0;
	   if( !( name.Contains("Mu")||name.Contains("Ele")||name.Contains("gamma") )){
		   ele_id_scale=get_ele_ID(lep2eta,lep2pt,ele_ID);
		   ele_id_scale_Up=get_ele_ID_up(lep2eta,lep2pt,ele_ID);
		   ele_id_scale_Down=get_ele_ID_down(lep2eta,lep2pt,ele_ID);
		   ele_reco_scale=get_ele_Reco(lep2eta,lep2pt,ele_Reco);
		   ele_reco_scale_Up=get_ele_Reco_up(lep2eta,lep2pt,ele_Reco);
		   ele_reco_scale_Down=get_ele_Reco_down(lep2eta,lep2pt,ele_Reco);
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
			   photon_veto_scale_Up=get_photon_veto_up(photoneta,photon_pix,photon_stat,photon_pu,photon_model);
			   photon_veto_scale_Down=get_photon_veto_down(photoneta,photon_pix,photon_stat,photon_pu,photon_model);
			   if(fabs(photoneta)<1.4442) photon_veto_scale=photon_pix->GetBinContent(1);
			   if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=photon_pix->GetBinContent(4); 
		   }
	   }
          
	   if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<" "<<photon_id_scale<<" "<<photon_id_scale_Up<<" "<<photon_id_scale_Down<<endl;

	   float MCweight=1,Dataweight=1;
	   float MCweight_up=1,Dataweight_up=1;
	   float MCweight_down=1,Dataweight_down=1;
	   btag_weight=1;btag_weight_up=1;btag_weight_down=1;
           n_bjets_nom=0;njets20_nom=0;njets25_nom=0;njets30_nom=0;njets35_nom=0;njets40_nom=0;njets50_nom=0;
           bool pass_dr_cut=true;
	   for(int i=0;i<nJet;i++){
                   if(fabs(Jet_eta[i])>4.7) continue;
                   if(delta_R(Jet_eta[i],Jet_phi[i],lep1eta,lep1phi)<0.5) pass_dr_cut=false;
                   if(delta_R(Jet_eta[i],Jet_phi[i],lep2eta,lep2phi)<0.5) pass_dr_cut=false;
		   if(n_photon>0)
			   pass_dr_cut=delta_R(Jet_eta[i],Jet_phi[i],photoneta,photonphi)>0.5;
		   if(!pass_dr_cut) continue;
		   if( Jet_jetId[i]>> 1 & 1){
			   if(Jet_pt_nom[i]>20) njets20_nom++;
			   if(Jet_pt_nom[i]>25) njets25_nom++;
			   if(Jet_pt_nom[i]>30) njets30_nom++;
			   if(Jet_pt_nom[i]>35) njets35_nom++;
			   if(Jet_pt_nom[i]>40) njets40_nom++;
			   if(Jet_pt_nom[i]>50) njets50_nom++;
		   }
                   if(Jet_pt_nom[i]<20)   continue;
		   if(Jet_btagDeepB[i]> 0.4168) n_bjets_nom++;
		   if(fabs(Jet_partonFlavour[i])==5 && name.Contains("Muon")==0){
			   if(Jet_btagDeepB[i]>0.4168){
				   MCweight=MCweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]));
				   Dataweight=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i];
				   Dataweight_up=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i];
				   Dataweight_down=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i];
			   }
			   else{
				   MCweight=MCweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i])));
				   Dataweight=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i]);
				   Dataweight_up=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i]);
				   Dataweight_down=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i]);
			   }
		   }
		   else if(fabs(Jet_partonFlavour[i])==4 && name.Contains("Muon")==0 ){
			   if(Jet_btagDeepB[i]>0.4168){
				   MCweight=MCweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]));
				   Dataweight=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i];
				   Dataweight_up=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i];
				   Dataweight_down=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i];
			   }
			   else{
				   MCweight=MCweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i])));
				   Dataweight=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i]);
				   Dataweight_up=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i]);
				   Dataweight_down=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i]);
			   }
		   }
		   else if( name.Contains("Muon")==0 ){
			   if(Jet_btagDeepB[i]>0.4168){
				   MCweight=MCweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]));
				   Dataweight=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i];
				   Dataweight_up=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i];
				   Dataweight_down=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i];
			   }
			   else{
				   MCweight=MCweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i])));
				   Dataweight=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i]);
				   Dataweight_up=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i]);
				   Dataweight_down=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i]);
			   }
		   }
	   }
	   if(MCweight>0){
		   btag_weight=Dataweight/MCweight;
		   btag_weight_up=Dataweight_up/MCweight;
		   btag_weight_down=Dataweight_down/MCweight;
	   }
	   LEP = ( (HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1_charge*lep2_charge<0 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1 && drll>0.5 );
	   PHOTON = ( n_photon>0  && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 )) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1 );
           MET = ( PuppiMET_T1Smear_pt > 20 );
           JET = ( n_bjets_nom==0 && njets30<=1 );

           GenLEP = ( gen_channel==1 && fabs(genlep1)==13 && fabs(genlep2)==11 && gendrll>0.5 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta) < 2.4 && fabs(genlep1eta) < 2.5 && genptll>30 && genmll>20);
           GenPHOTON = ( genphotonet>20 && ( fabs(genphotoneta)<1.4442 || (fabs(genphotoneta)<2.5 && fabs(genphotoneta)>1.566 )) && gendrl1a>0.5 && gendrl2a>0.5 );
           GenMET = (GenMET_pt>20) ;
           GenJET = (n_genbjets==0 && n_genjets30<=1);
	   if(year.Contains("18")) PrefireWeight=1;
	   actualWeight=scalef*ele_id_scale*ele_reco_scale*muon_id_scale*muon_iso_scale*photon_id_scale*photon_veto_scale*puWeight*PrefireWeight*btag_weight;
//	   cout<<actualWeight<<" "<<mT<<" "<<mllg<<endl;
           if( !(LEP && PHOTON && MET ))
		   continue;
	   tot++;
           if( (LEP && PHOTON && MET && JET && GenLEP))
		   nlep++;
           if( (LEP && PHOTON && MET && JET && GenLEP && GenPHOTON))
		   nphoton++;
	   ExTree->Fill();
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
   cout<<nentries<<" Full Reco "<<tot<<"; Full Reco + GenLEP "<<nlep<<" ; Full Reco + GenLEP + GenPHOTON "<<nphoton<<endl;
}
void WWg::Init(){
	ele_id_scale=1;ele_id_scale_Up=1;ele_id_scale_Down=1;
	ele_reco_scale=1;ele_reco_scale_Up=1;ele_reco_scale_Down=1;
	muon_id_scale=1;muon_id_scale_Up=1;muon_id_scale_Down=1;
	muon_iso_scale=1;muon_iso_scale_Up=1;muon_iso_scale_Down=1;
	photon_id_scale=1;photon_id_scale_Up=1;photon_id_scale_Down=1;
	photon_veto_scale=1;photon_veto_scale_Up=1;photon_veto_scale_Down=1;
	HLT_emu1=0;HLT_emu2=0;HLT_emu3=0;HLT_emu4=0;
}
      
Float_t WWg::delta_R(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2)
{
        Float_t dp = phi1-phi2;
        if(std::fabs(dp) > pi) dp = 2*pi - std::fabs(dp);
        Float_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}
