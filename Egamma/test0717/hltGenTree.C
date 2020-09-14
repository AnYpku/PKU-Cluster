#define hltGenTree_cxx
#include "hltGenTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include "unroll.C"

void hltGenTree::Loop(TString name, int j,int i)
{
   if (fChain == 0) return;
file = new TFile(name+Form("et_%0.f_%0.f-eta_%1.f_%1.f",etbins[i],etbins[i+1],barreletabins[j],barreletabins[j+1]),"RECREATE");
het[0] = new TH1D("hclusEt_ele","clusEt",10,etbins[i],etbins[i+1]);
het[1] = new TH1D("het_eghlt","et",10,etbins[i],etbins[i+1]);
heta[0] = new TH1D("hdetEta_ele","detEta",10,barreletabins[j],barreletabins[j+1]);
heta[1] = new TH1D("heta_eghlt","eta",10,barreletabins[j],barreletabins[j+1]);
hnrgy[0] = new TH1D("hclusNrgy_ele","clusNrgy",40,0,400);
hnrgy[1] = new TH1D("hnrgy_eghlt","nrgy",40,0,400);
hphi[0] = new TH1D("hdetPhi_ele","detPhi",13,-6.5,6.5);
hphi[1] = new TH1D("hphi_eghlt","phi",13,-6.5,6.5);
hsieie[0] = new TH1D("hsieie_ele","sigamIEtaIEta",40,0,0.06);
hsieie[1] = new TH1D("hsieie_eghlt","sigamIEtaIEta",40,0,0.06);
detain[0] = new TH1D("hdEtaInSeed_ele","|dEtaInSeed|",40,0,0.02);
detain[1] = new TH1D("hetain_eghlt","dEtaIn",40,0,0.02);
dphiin[0] = new TH1D("hPhiIn_ele","|dPhiIn|",40,0,0.05);
dphiin[1] = new TH1D("hphiin_eghlt","dPhiIn",40,0,0.05);
hMhits[0]= new TH1D("hMHits_ele","missing hits",7,0,6);
hMhits[1]= new TH1D("hMHits_eghlt","missing hits",7,0,6);
TH2D* h2eta[4];TH2D*h2phi[4];TH2D*h2nrgy[4];TH2D*h2et[4];
h2eta[0] = new TH2D("heta1_seed","eleTruthEta",20,-2.5,2.5,1,-2000,2000);
h2eta[1] = new TH2D("heta2_seed","eleTruthEta",20,-2.5,2.5,1,-2000,2000);
h2eta[2] = new TH2D("heta1_US","eleTruthEta",  20,-2.5,2.5,1,-2000,2000);
h2eta[3] = new TH2D("heta2_US","eleTruthEta",  20,-2.5,2.5,1,-2000,2000);
h2phi[0] = new TH2D("hphi1_seed","eleTruthPhi",8,0,3.2,1,-2000,2000);
h2phi[1] = new TH2D("hphi2_seed","eleTruthPhi",8,0,3.2,1,-2000,2000);
h2phi[2] = new TH2D("hphi1_US","eleTruthPhi",8,0,3.2,1,-2000,2000);
h2phi[3] = new TH2D("hphi2_US","eleTruthPhi",8,0,3.2,1,-2000,2000);
h2nrgy[0] = new TH2D("hnrgy1_seed","eleTruthNrgy",25,0,1000,1,-2000,2000);
h2nrgy[1] = new TH2D("hnrgy2_seed","eleTruthNrgy",25,0,1000,1,-2000,2000);
h2nrgy[2] = new TH2D("hnrgy1_US","eleTruthNrgy",25,0,1000,1,-2000,2000);
h2nrgy[3] = new TH2D("hnrgy2_US","eleTruthNrgy",25,0,1000,1,-2000,2000);
h2et[0] = new TH2D("het1_seed","eleTruthEt",15,0,200,1,-2000,2000);
h2et[1] = new TH2D("het2_seed","eleTruthEt",15,0,200,1,-2000,2000);
h2et[2] = new TH2D("het1_US","eleTruthEt",  15,0,200,1,-2000,2000);
h2et[3] = new TH2D("het2_US","eleTruthEt ", 15,0,200,1,-2000,2000);
vector<TH2D*> hseed;vector<TH2D*> hunseed;
vector<TH2D*> hseed2;vector<TH2D*> hunseed2;
/*TFile* f1 = new TFile("./matching.root","RECREATE");
TTree* tree = new TTree("tree","tree");
tree->Branch("eleTruthEta",&eleTruthEta,"eleTruthEta/F");
tree->Branch("eleTruthEt",&eleTruthEt,"eleTruthEt/F");
tree->Branch("eleTruthPhi",&eleTruthPhi,"eleTruthPhi/F");
tree->Branch("eleTruthNrgy",&eleTruthNrgy,"eleTruthNrgy/F");*/
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
//      if( !(  (fabs(eleTruthEta)>1.566)&&(fabs(eleTruthEta)<2.5) ) ) continue;
      if( !( (fabs(eleTruthEta)<1.4442) ) ) continue;
//     if(jentry%1000==0&&egHLT_et>0){ cout<<jentry<<";"<<egHLT_et<<"; "<<egHLT_eta<<";"<<egHLT_nrgy<<endl;}
      if(clusEt>200) clusEt =201; if(egHLT_et>200) egHLT_et =201;
      if(! (fabs(eleTruthEta)<barreletabins[j+1] && fabs(eleTruthEta)>barreletabins[j] && eleTruthEt<etbins[i+1]&&eleTruthEt>etbins[i]) ) continue;
      het[0]->Fill(clusEt);het[1]->Fill(egHLT_et);hnrgy[0]->Fill(clusNrgy);hnrgy[1]->Fill(egHLT_nrgy);
      heta[0] ->Fill(detEta);heta[1] ->Fill(egHLT_eta);	hphi[0]->Fill(detPhi);hphi[1]->Fill(egHLT_phi);
      hsieie[0]->Fill(sigmaIEtaIEta);hsieie[1]->Fill(egHLT_sigmaIEtaIEta);
      detain[0]->Fill(dEtaInSeed);detain[1]->Fill(egHLT_dEtaIn);
      dphiin[0]->Fill(dPhiIn);dphiin[1]->Fill(egHLT_dPhiIn);
      hMhits[0]->Fill(nrMissHits);hMhits[1]->Fill(egHLT_nrMissHits);
      if(eleTruthEt>200) eleTruthEt =199;
	if(egHLT_nrgy>0) {h2eta[0]->Fill(eleTruthEta,egHLT_nrgy);}  hseed2.push_back(h2eta[0]);
	h2eta[1]->Fill(eleTruthEta,egHLT_nrgy);  hseed.push_back(h2eta[1]);
	if(egHLTUS_nrgy>0) {h2eta[2]->Fill(eleTruthEta,egHLTUS_nrgy);}hunseed2.push_back(h2eta[2]);
	h2eta[3]->Fill(eleTruthEta,egHLTUS_nrgy);hunseed.push_back(h2eta[3]);

	if(egHLT_nrgy>0) {h2phi[0]->Fill(eleTruthPhi,egHLT_nrgy);}   hseed2.push_back(h2phi[0]);
	h2phi[1]->Fill(eleTruthPhi,egHLT_nrgy);  hseed.push_back(h2phi[1]);
	if(egHLTUS_nrgy>0) {h2phi[2]->Fill(eleTruthPhi,egHLTUS_nrgy);} hunseed2.push_back(h2phi[2]);
	h2phi[3]->Fill(eleTruthPhi,egHLTUS_nrgy);hunseed.push_back(h2phi[3]);

	if(egHLT_nrgy>0) {h2nrgy[0]->Fill(eleTruthNrgy,egHLT_nrgy);}  hseed2.push_back(h2nrgy[0]);
	h2nrgy[1]->Fill(eleTruthNrgy,egHLT_nrgy);        hseed.push_back(h2nrgy[1]);
	if(egHLTUS_nrgy>0) {h2nrgy[2]->Fill(eleTruthNrgy,egHLTUS_nrgy);} hunseed2.push_back(h2nrgy[2]);
	h2nrgy[3]->Fill(eleTruthNrgy,egHLTUS_nrgy);      hunseed.push_back(h2nrgy[3]);

	if(egHLT_nrgy>0) {h2et[0]->Fill(eleTruthEt,egHLT_nrgy);}  hseed2.push_back(h2et[0]);  
	h2et[1]->Fill(eleTruthEt,egHLT_nrgy);         hseed.push_back(h2et[1]);     
	if(egHLTUS_nrgy>0) {h2et[2]->Fill(eleTruthEt,egHLTUS_nrgy);}hunseed2.push_back(h2et[2]);
	h2et[3]->Fill(eleTruthEt,egHLTUS_nrgy);       hunseed.push_back(h2et[3]);
   }
   TGraph* gr_seed[4];
   TGraph* gr_US[4];
   TGraphErrors* gre_seed[4];
   TGraphErrors* gre_US[4];
//   TH1D* h1[4];TH1D* h2[4];
   TH1D* hsN[4];TH1D* husN[4];
   TH1D* hsD[4];TH1D* husD[4];
   int count_seed[4],count_US[4];
   double grYseed;double grXseed;double grYUS;double grXUS;
   double grYseedError;double grXseedError;double grYUSerror;double grXUSerror;
   for(int i=0;i<4;i++){ 
             hseed2[i]->Sumw2();
             hseed[i]->Sumw2();
             hunseed2[i]->Sumw2();
             hunseed[i]->Sumw2();
             TString name1 = hseed2[i]->GetName();
             TString title1 = hseed2[i]->GetTitle();
             TString name2 = hunseed2[i]->GetName();
             TString title2 = hunseed2[i]->GetTitle();
	     count_seed[i]= hseed[i]->GetNbinsX();count_US[i]= hunseed[i]->GetNbinsX();
	     hsN[i] = unroll(hseed2[i],Form("hsN_%i",i+1),hseed2[i]->GetTitle());
             hsD[i] = unroll(hseed[i],Form("hsD_%i",i+1),hseed[i]->GetTitle());
	     husN[i] = unroll(hunseed2[i],Form("hunsN_%i",i+1),hunseed2[i]->GetTitle());
             husD[i] = unroll(hunseed[i],Form("hunsD_%i",i+1),hunseed[i]->GetTitle());
	     gr_seed[i] = new TGraph(count_seed[i]);
	     gr_US[i] = new TGraph(count_US[i]);
//	     h1[i]= new TH1D(Form("h1_%i",i+1),hseed[i]->GetName(),count_seed[i],hseed[i]->GetXaxis()->GetXmin(),hseed[i]->GetXaxis()->GetXmax());
//	     h2[i]= new TH1D(Form("h2_%i",i+1),hunseed[i]->GetName(),count_US[i],hunseed[i]->GetXaxis()->GetXmin(),hunseed[i]->GetXaxis()->GetXmax());
           for(int j=0;j<count_seed[i];j++){
              grXseed = hseed[i]->GetXaxis()->GetBinCenter(j+1);
              grYseed = hseed2[i]->GetBinContent(j+1,1)/hseed[i]->GetBinContent(j+1,1);
              grYseedError = 0;
              grXseedError =( hseed[i]->GetXaxis()->GetBinWidth(j+1) ) /2;
//	      cout<<name1<<";"<< hseed[i]->GetBinContent(j+1,1)<<";"<<hseed2[i]->GetBinContent(j+1,1)<<endl;
              gr_seed[i] -> SetPoint(j,grXseed,grYseed);
	      gr_seed[i]->SetTitle(title1);
	   }
           for(int j=0;j<count_US[i];j++){
              grYUS = hunseed2[i]->GetBinContent(j+1,1)/hunseed[i]->GetBinContent(j+1,1); 
              grXUS = hunseed[i]->GetXaxis()->GetBinCenter(j+1);
              grYUSerror = 0;
              grXUSerror = hunseed[i]->GetXaxis()->GetBinWidth(j+1)/2;
              gr_US[i] -> SetPoint(j,grXUS,grYUS);
	      gr_US[i]->SetTitle(title2);
	   }
   }

file->cd();
for(Int_t i=0;i<2;i++){
	het[i]->Write();
	hnrgy[i]->Write();
	heta[i]->Write();
	hphi[i]->Write();
	hsieie[i]->Write();
	detain[i]->Write();
	dphiin[i]->Write();
	hMhits[i]->Write();
/*	hseed->Write();
	hseed2->Write();
	hunseed->Write();
	hseed2->Write();*/
     }
for(int i=0;i<4;i++){
        hsN[i]->Write();
        hsD[i]->Write();
        husN[i]->Write();
        husD[i]->Write();
	gr_seed[i]->Write(Form("seed_%i",i+1));
	gr_US[i]->Write(Form("unseed_%i",i+1));
        h2eta[i]->Write();
        h2phi[i]->Write();
        h2nrgy[i]->Write();
        h2et[i]->Write();
}
file->Close();
cout<<"*******************************end***************************"<<endl;
}
