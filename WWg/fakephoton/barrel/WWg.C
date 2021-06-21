#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
using namespace std;
void WWg::Loop(TString name,Bool_t isBarrel,int lep_channel)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
//   nentries=100;

   Long64_t nbytes = 0, nb = 0;
   TFile*f_hist;
   TString c;
   if(lep_channel==1)c="emu_";
   else if(lep_channel==2)c="ee_";
   else if(lep_channel==3)c="mm_";
   vector<double> vector_sieie;
   if(isBarrel){
	   f_hist=new TFile("./hist_barrel_"+c+name,"recreate");
           for(int i=0;i<21;i++){
		   vector_sieie.push_back(0.002+0.001*i);
	   }
   }
   else{
	   f_hist=new TFile("hist_endcap_"+c+name,"recreate");
           for(int i=0;i<21;i++){
		   vector_sieie.push_back(0.01+0.0025*i);
	   }
   }
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   for(int i=0;i<num;i++){
      htrue_mc[i]=new TH1D(Form("true_pt%0.f_%0.f",lowpt[i],highpt[i]),"true template from mc",vector_sieie.size()-1,&vector_sieie[0]); 
      hfake_mc[i]=new TH1D(Form("fake_pt%0.f_%0.f",lowpt[i],highpt[i]),"fake contamination from mc",vector_sieie.size()-1,&vector_sieie[0]);
      hdata_data[i]=new TH1D(Form("data_pt%0.f_%0.f",lowpt[i],highpt[i]),"data template from data",vector_sieie.size()-1,&vector_sieie[0]); 
      hfake_data[i]=new TH1D(Form("fake_pt%0.f_%0.f",lowpt[i],highpt[i]),"fake template from data",vector_sieie.size()-1,&vector_sieie[0]);
   }
   Bool_t BSL_emu=0,BSL_ee=0,BSL_mumu=0,photon_channel=0,photon_channel_f=0;
   Bool_t HLT_data=0;int n_data=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
   
      HLT_mm = (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_ee = (HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_emu = (HLT_Ele32_WPTight_Gsf) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL); 

      if(name.Contains("Muon") || name.Contains("Egamma") || name.Contains("Ele")){
        lepton1_isprompt=1;lepton2_isprompt=1;
      }

      if(name.Contains("MuonEG")) 
	      HLT_data = ( channel==1 && ((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) && !((HLT_Ele32_WPTight_Gsf) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)) ) ||
                         ( channel==2 && ((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) && !(HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) ) || 
                         ( channel==3 && ((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) && !(HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) ) ;
     if(name.Contains("DMuon")) 
	     HLT_data = ( channel==1 && (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) && !((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) ) ||
                        ( channel==3 && (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) && !((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) );
    if(name.Contains("EGamma")||name.Contains("Ele"))
             HLT_data = ( channel==1 && (HLT_Ele32_WPTight_Gsf) && !((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8)) ) ||
                        ( channel==2 && (HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) && !((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) );

      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<" "<<HLT_data<<" "<<(HLT_mm||HLT_ee||HLT_emu)<<endl;

      BSL_emu = (channel==1 && lep1_pid==13 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.5 && (n_loose_ele+n_loose_mu)==2) && HLT_emu && mll>70 && mll<110;
      BSL_ee = (channel==2 && lep1_pid==11 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.5 && lep2pt>20 && fabs(lep2eta)<2.5  && (n_loose_ele+n_loose_mu)==2) && HLT_ee && mll>70 && mll<110 ;
      BSL_mumu = (channel==3 && lep1_pid==13 && lep2_pid==13 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.4  && (n_loose_ele+n_loose_mu)==2) && HLT_mm && mll>70 && mll<110 ;
      if( !( BSL_emu || BSL_ee || BSL_mumu ) )
              continue;
      ExTree->Fill();
      if( isBarrel ){ 
	      photon_channel = fabs(photoneta)<1.4442;
	      photon_channel_f = fabs(photoneta_f)<1.4442;
      }
      else{           
	      photon_channel = fabs(photoneta)<2.5 && fabs(photoneta)>1.566;
	      photon_channel_f = fabs(photoneta_f)<2.5 && fabs(photoneta_f)>1.566;
      }
      if(name.Contains("ZG")||name.Contains("WW")||name.Contains("TTG")){
	      if(channel==lep_channel && photonet>20 && photon_channel && photon_isprompt==1 && pass_selection1 && (photon_selection==1 || photon_selection==5) ){
		      for(int i=0;i<num;i++){
			      if(photonet>lowpt[i] && photonet<highpt[i])
				      htrue_mc[i]->Fill(photonsieie,scalef);
		      }
	      }
	      if(channel==lep_channel && photonet_f>20 && photon_channel_f && photon_isprompt_f==1 && pass_selection2 && photonchiso_f>4 && photonchiso_f<10){
		      for(int i=0;i<num;i++){
			      if(photonet_f>lowpt[i] && photonet_f<highpt[i])
				      hfake_mc[i]->Fill(photonsieie_f,scalef);
		      }
	      }
      }
      else if(name.Contains("Muon") || name.Contains("EGamma") || name.Contains("Ele")){
	      if(channel==lep_channel && photonet>20 && photon_channel && pass_selection1 && (photon_selection==1 || photon_selection==5) && HLT_data ){
		      for(int i=0;i<num;i++){
			      if(photonet>lowpt[i] && photonet<highpt[i])
				      hdata_data[i]->Fill(photonsieie,1);
		      }
                      n_data++;
	      }
	      if(channel==lep_channel && photonet_f>20 && photon_channel_f && pass_selection2 && photonchiso_f>4 && photonchiso_f<10 && HLT_data){
		      for(int i=0;i<num;i++){
			      if(photonet_f>lowpt[i] && photonet_f<highpt[i])
				      hfake_data[i]->Fill(photonsieie_f,1);
		      }
	      }
      }
      // if (Cut(ientry) < 0) continue;
   }
   cout<<n_data<<" "<<nentries<<endl;
   f_hist->cd();
   for(int i=0;i<num;i++){
	   if(name.Contains("ZG")||name.Contains("WW")||name.Contains("TTG")){
		   htrue_mc[i]->Write();
		   hfake_mc[i]->Write();
	   }
	   else{
		   hdata_data[i]->Write();
		   hfake_data[i]->Write();
	   }
   }
  f_hist->Close();
}
