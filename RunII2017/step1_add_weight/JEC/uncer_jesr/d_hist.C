#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

using namespace std;
TH2D* hist[3];
void hist_2d_mc(std::string filename,TH2D* th2[3]){

	std::string file = "../"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("ZPKUCandidates");

	Double_t Mjj,Mjj_new,Mjj_JER_up,Mjj_JER_down,Mjj_JEC_up,Mjj_JEC_down;
	Double_t Mva,photoneta;
	Double_t deltaeta;
	Int_t lep;
	Double_t actualWeight;
        Double_t scalef,lumiWeight,pileupWeight,muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;//,muon1_track_scale,muon2_track_scale,muon_hlt_scale;
        Double_t Mjj_JEC[3],Mjj_JER[3];
	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("lep", &lep);
	t->SetBranchAddress("photoneta", &photoneta);
	t->SetBranchAddress("Mjj_new", &Mjj_new);
	t->SetBranchAddress("Mjj_JER_up", &Mjj_JER_up);
	t->SetBranchAddress("Mjj_JER_down", &Mjj_JER_down);
	t->SetBranchAddress("Mjj_JEC_up", &Mjj_JEC_up);
	t->SetBranchAddress("Mjj_JEC_down", &Mjj_JEC_down);
	t->SetBranchAddress("Mva", &Mva);
	t->SetBranchAddress("deltaeta", &deltaeta);
	t->SetBranchAddress("pileupWeight", &pileupWeight);
	t->SetBranchAddress("lumiWeight", &lumiWeight);
	t->SetBranchAddress("scalef", &scalef);
	t->SetBranchAddress("muon1_id_scale",&muon1_id_scale);
	t->SetBranchAddress("muon2_id_scale",&muon2_id_scale);
	t->SetBranchAddress("muon1_iso_scale",&muon1_iso_scale);
	t->SetBranchAddress("muon2_iso_scale",&muon2_iso_scale);
//	t->SetBranchAddress("muon1_track_scale",&muon1_track_scale);
//	t->SetBranchAddress("muon2_track_scale",&muon2_track_scale);
//	t->SetBranchAddress("muon_hlt_scale",&muon_hlt_scale);
 

	Double_t mjj_bins[4]={500, 800, 1200, 2000};
	Double_t deltaeta_bins[4]={2.5, 4.5,  6, 6.5};
	for(int i=0;i<3;i++){
		th2[i] = new TH2D(Form("th2_%d",i),"Mjj vs deltaeta",3, mjj_bins, 3, deltaeta_bins);
		th2[i]->Sumw2();
	}
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
                Mjj_JEC[0] = Mjj_new;
		Mjj_JEC[1]=Mjj_JEC_up;
		Mjj_JEC[2]=Mjj_JEC_down;
                Mjj_JER[0] = Mjj_new;
		Mjj_JER[1]=Mjj_JER_up;
		Mjj_JER[2]=Mjj_JER_down;
//                actualWeight = scalef * pileupWeight*lumiWeight * muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon1_track_scale*muon2_track_scale*muon_hlt_scale;
                actualWeight = scalef*lumiWeight* muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale;
		cout<<"scalef = "<<scalef<<"; pileupWeight = "<<pileupWeight<<"; limiWeight = "<<lumiWeight<<endl;
                cout<<"muon1_id_scale = "<<muon1_id_scale<<endl;
                cout<<"muon2_id_scale = "<<muon2_id_scale<<endl;
                cout<<"muon1_iso_scale = "<<muon1_iso_scale<<endl;
                cout<<"muon2_iso_scale = "<<muon2_iso_scale<<endl;
               
		cout<<i<<"; "<<t->GetEntries()<<"; actualWeight = "<<actualWeight<<endl;
		for(int i=0;i<3;i++){
			if(Mjj_JEC[i]<2000 && deltaeta<6.5)  th2[i]->Fill(Mjj_JER[i], deltaeta, actualWeight);
			if(Mjj_JEC[i]>=2000 && deltaeta<6.5) th2[i]->Fill(1999, deltaeta, actualWeight);
			if(Mjj_JEC[i]<2000 && deltaeta>=6.5) th2[i]->Fill(Mjj_JER[i], 6.1, actualWeight);
			if(Mjj_JEC[i]>=2000 && deltaeta>=6.5)th2[i]->Fill(1999, 6.1, actualWeight);
		}
	}
}

int d_hist(){
	TFile *file = new TFile("2d_jec.root","RECREATE");	
        hist_2d_mc("cutla-outZA-EWK-JEC",hist);
        file->cd();
        hist[0]->Write();
        hist[1]->Write();
        hist[2]->Write();
        file->Close();
	return 0;
}
