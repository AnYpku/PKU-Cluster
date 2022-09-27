#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
using namespace std;
void WWg::Loop(TString name,TString year)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   Long64_t npp = fChain->GetEntries("gen_weight>0.");
   Long64_t nmm = fChain->GetEntries("gen_weight<0.");
   Bool_t HLT;
   Bool_t BSL=0,LEP=0,PHOTON=0;
   TFile*fele=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/fakelepton/fakerate/ele"+year+"_fakerate.root");
   TH2D*hele=(TH2D*)fele->Get("TtoL");
   TFile*fmu=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/fakelepton/fakerate/mu"+year+"_fakerate.root");
   TH2D*hmu=(TH2D*)fmu->Get("TtoL");
   double lumi;
   if(year.Contains("18"))
	   lumi=59.83;
   else if(year.Contains("17"))
	   lumi=41.5;
   else if(year.Contains("16") && name.Contains("pre"))
	   lumi=19.52;
   else 
	   lumi=16.81;
   double actualWeight;
   bool isSignal=0,isBkg=0;
   if(name.Contains("WWG_emu")||name.Contains("HGC") || name.Contains("HGS") || name.Contains("HGU") || name.Contains("HGD") )
	   isSignal=1;
   else isBkg=1;
   cout<<name<<" "<<isSignal<<" "<<isBkg<<endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(year.Contains("18")) {L1PreFiringWeight_Nom=1;L1PreFiringWeight_Muon_Nom=1;}
      actualWeight=scalef*ele_id_scale*ele_reco_scale*muon_id_scale*muon_iso_scale*puWeight*L1PreFiringWeight_Nom*L1PreFiringWeight_Muon_Nom*btag_weight_medium;
      if(name.Contains("Ele")||name.Contains("Muon")){ scalef=1;photon_isprompt=1;lep1_isprompt=1;lep2_isprompt=1;}
      if(jentry%1000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      if(name.Contains("MuonEG")) HLT = (HLT_emu);
      else if(name.Contains("Muon")) HLT = ( !(HLT_emu) && HLT_mm);
      else if(name.Contains("Ele")) HLT = ( !(HLT_emu) && !(HLT_mm) && HLT_ee);
      else HLT = (HLT_ee || HLT_emu || HLT_mm);

      LEP = pass_selection>0 && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && drll>0.5 && lep1pt>15 && lep2pt>15 && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && !(lep1_is_tight==1 && lep2_is_tight==1 ) && lep1_isprompt==1 && lep2_isprompt==1 && HLT; 
      PHOTON = n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 )) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 /*&& photon_isprompt==1*/;

      if(name.Contains("Muon")==0 && name.Contains("Ele")==0){
              MET_T1_pt =MET_T1Smear_pt;
              MET_T1_phi=MET_T1Smear_phi;
      }

      double lep1pt_tmp,lep2pt_tmp;
      if(lep1pt>60) lep1pt_tmp=59; else lep1pt_tmp=lep1pt;
      if(lep2pt>60) lep2pt_tmp=59; else lep2pt_tmp=lep2pt;
      if(LEP){
	      if(lep1_is_tight!=1 && lep2_is_tight!=1){
		      if(name.Contains("Muon")||name.Contains("Ele"))
			      scalef=hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) * (-1);
		      else{
			      if(isSignal)
				      scalef=scalef * hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) ;//MC loose+loose
			      else
				      scalef=actualWeight * lumi * hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) ;//MC loose+loose
		      }
	      }
	      else if(lep1_is_tight!=1 && lep2_is_tight==1){
		      if(name.Contains("Muon")||name.Contains("Ele"))
			      scalef=hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp)));
		      else{
			      if(isSignal)
				      scalef = scalef * hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * (-1);//MC tight+loose
			      else
				      scalef = actualWeight * lumi * hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * (-1);//MC tight+loose
		      }
	      }
	      else if(lep1_is_tight==1 && lep2_is_tight!=1){
		      if(name.Contains("Muon")||name.Contains("Ele")){
			      scalef=hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp)));
		      }
		      else{
			      if(isSignal)
				      scalef=scalef * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) * (-1); //MC tight+loose
			      else
				      scalef=actualWeight * lumi * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) * (-1); //MC tight+loose
		      }
	      }
      }
      else{
	      if(isBkg) continue;
      }

      if(jentry%1000==0) cout<<jentry<<" after adding weight "<<nentries<<" "<<scalef<<" "<<lep1pt_tmp<<" "<<lep2pt_tmp<<endl;

      ExTree->Fill();
   }
}
