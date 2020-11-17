//gSystem->Load("/home/pku/anying/cms/Unfolding/RooUnfold/libRooUnfold.so");
#define rm_cxx
#include "genparticles.C"
#include <TH2.h>
#include <TH2F.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLegend.h"
#include <iostream>
#include "muon16_channel_scale.C"
#include "muon_channel_scale.C"
#include "ele_channel_scale.C"

void rm::Loop(TString tag)
{
   if (fChain == 0) return;
   TFile* file_ID;TH2F*ID_ele;
   TFile* file_gammaID;TH2F*ID_gamma;
   TFile*file_ID_sys1;TH2D*ID_muon_sys1;
   TFile*file_ID_sys2;TH2D*ID_muon_sys2;
   TFile*file_ISO_sys1;TH2D*ISO_muon_sys1;
   TFile*file_ISO_sys2;TH2D*ISO_muon_sys2;
   TFile*file_reco; TH2F*Reco_ele;
   if(tag.Contains("16")){
	   file_ID_sys1=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root");
	   file_ID_sys2=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root");
	   file_ISO_sys1=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root");
	   file_ISO_sys2=new TFile("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root");
	   ID_muon_sys1=(TH2D*)file_ID_sys1->Get("NUM_TightID_DEN_genTracks_eta_pt");
	   ID_muon_sys2=(TH2D*)file_ID_sys2->Get("NUM_TightID_DEN_genTracks_eta_pt");
	   ISO_muon_sys1=(TH2D*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");
	   ISO_muon_sys2=(TH2D*)file_ISO_sys2->Get("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt");

	   file_ID=new TFile("./egamma_SFs/2017_ElectronMedium.root");
	   file_reco=new TFile("./egamma_SFs/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
	   ID_ele=(TH2F*)file_ID->Get("EGamma_SF2D");
	   Reco_ele=(TH2F*)file_reco->Get("EGamma_SF2D");

	   file_gammaID=new TFile("./egamma_SFs/Fall17V2_2016_Medium_photons.root");
	   ID_gamma=(TH2F*)file_ID->Get("EGamma_SF2D");
   }
   if(tag.Contains("17")){
	   file_ID_sys1=new TFile("./muon_SFs/RunBCDEF_SF_ID_syst.root");
	   file_ISO_sys1=new TFile("./muon_SFs/RunBCDEF_SF_ISO_syst.root");
	   ID_muon_sys1=(TH2D*)file_ID_sys1->Get("NUM_TightID_DEN_genTracks_pt_abseta_syst");
	   ISO_muon_sys1=(TH2D*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta_syst");

	   file_ID=new TFile("./egamma_SFs/2017_ElectronMedium.root");
	   file_reco=new TFile("./egamma_SFs/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
	   ID_ele=(TH2F*)file_ID->Get("EGamma_SF2D");
	   Reco_ele=(TH2F*)file_reco->Get("EGamma_SF2D");

	   file_gammaID=new TFile("./egamma_SFs/2017_PhotonsMedium.root ");
	   ID_gamma=(TH2F*)file_ID->Get("EGamma_SF2D");
   }
   if(tag.Contains("18")){
	   file_ID_sys1=new TFile("./muon_SFs/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root");
	   file_ISO_sys1=new TFile("./muon_SFs/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root");
	   ID_muon_sys1=(TH2D*)file_ID_sys1->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");
	   ISO_muon_sys1=(TH2D*)file_ISO_sys1->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

	   file_ID=new TFile("./egamma_SFs/2018_ElectronMedium.root");
	   file_reco=new TFile("./egamma_SFs/egammaEffi.txt_EGM2D_updatedAll.root");
	   ID_ele=(TH2F*)file_ID->Get("EGamma_SF2D");
	   Reco_ele=(TH2F*)file_reco->Get("EGamma_SF2D");

	   file_gammaID=new TFile("./egamma_SFs/2018_PhotonsMedium.root ");
	   ID_gamma=(TH2F*)file_ID->Get("EGamma_SF2D");
   }
   TFile * input13 = new TFile ("/home/pku/anying/cms/PKU-Cluster/Unfolding/produce/copy/pu_"+tag+"/puweight.root");
   TH1* h13 = NULL;
   input13->GetObject("h2",h13);

   Long64_t nbytes = 0, nb = 0;
   double cut1=0;
   nentries=fChain->GetEntries();
   Long64_t npp = fChain->GetEntries("theWeight>0.");
   Long64_t nmm = fChain->GetEntries("theWeight<0.");
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   // if (Cut(ientry) < 0) continue;
	   if(jentry%50000==0)      cout<<jentry<<" "<<nentries<<endl;
	   ResetValue();
	   genparticles();

	   GenLEPmu  = genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4;
	   GenLEPele = genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5;
	   GenPhoton = genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) );
	   if( !( ((GenLEPmu)||(GenLEPele)) )  )
		   continue;
	   if( !(GenPhoton) )
		   continue;
           cut1++;
	   LEPmu = lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
	   LEPele = lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
	   photon = photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
//	   if( !( (LEPmu)||(LEPele) ) )
//		   continue;
	   if(tag.Contains("16")){
		   if(m_dataset.Contains("ZA")&&m_dataset.Contains("EWK")==0){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight;} 
		   if(m_dataset.Contains("ZA_interf")){ scalef=1000.*0.014/float(npp-nmm)*fabs(theWeight)/theWeight;}
		   if(m_dataset.Contains("EWK")){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight;}
	   }
	   if(tag.Contains("17")||tag.Contains("18")){
		   if(m_dataset.Contains("ZA")&&m_dataset.Contains("EWK")==0){ scalef=1000.*55.49/float(npp-nmm)*fabs(theWeight)/theWeight;}
		   if(m_dataset.Contains("ZA_interf")){ scalef=1000.*0.012/float(npp-nmm)*fabs(theWeight)/theWeight;}
		   if(m_dataset.Contains("EWK")){ scalef=1000.*0.1143/float(npp-nmm)*fabs(theWeight)/theWeight;}
	   }
	   if(lep==11){
		   ele1_id_scale=get_ele_ID(etalep1, ptlep1, ID_ele);
		   ele2_id_scale=get_ele_ID(etalep2, ptlep2, ID_ele);
		   ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco_ele);
		   ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco_ele);
	   }
	   if(lep==13){
		   if(tag.Contains("16")){
			   muon1_id_scale=get_muon_ID_sys16(etalep1,ptlep1,ID_muon_sys1,ID_muon_sys2);
			   muon2_id_scale=get_muon_ID_sys16(etalep2,ptlep2,ID_muon_sys1,ID_muon_sys2);
			   muon1_iso_scale=get_muon_iso_sys16(etalep1,ptlep1,ISO_muon_sys1,ISO_muon_sys2);
			   muon2_iso_scale=get_muon_iso_sys16(etalep2,ptlep2,ISO_muon_sys1,ISO_muon_sys2);
			   //muon_hlt_scale=muon_HLT_scale(etalep1,etalep2,di_lep_trigger);
			   if(fabs(photoneta)<1.4442) photon_veto_scale=0.9938;
			   if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.9875;
		   }
		   else if(tag.Contains("17")||tag.Contains("18")){
			   muon1_id_scale=get_muon_ID_sys(etalep1,ptlep1,ID_muon_sys1);
			   muon2_id_scale=get_muon_ID_sys(etalep2,ptlep2,ID_muon_sys1);
			   muon1_iso_scale=get_muon_iso_sys(etalep1,ptlep1,ISO_muon_sys1);
			   muon2_iso_scale=get_muon_iso_sys(etalep2,ptlep2,ISO_muon_sys1);
			   //muon_hlt_scale=muon_HLT_scale(ptlep1,ptlep2,di_lep_trigger);
			   if(tag.Contains("17")){
				   if(fabs(photoneta)<1.4442) photon_veto_scale=0.9862;
				   if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.9638;
			   }
			   if(tag.Contains("18")){
				   if(fabs(photoneta)<1.4442){
					   if(photonet<30) photon_veto_scale=0.9869;
					   else if(photonet>30 && photonet<60) photon_veto_scale=0.9908;
					   else photon_veto_scale=1.0084;
				   }
				   if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566){
					   if(photonet<30) photon_veto_scale=0.9535;
					   else if(photonet>30 && photonet<60) photon_veto_scale=0.9646;
					   else photon_veto_scale=1.0218;
				   }
			   }
		   }
		   else break;
	   }

	   if(photonet>0){
		   photon_id_scale=get_photon_ID(photoneta,photonet,ID_gamma);
	   }
	   ExTree->Fill();
   }
   eff=cut1/nentries;
   cout<<cut1<<" "<<nentries<<";  "<<eff<<endl;
}
