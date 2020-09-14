#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

using namespace std;

TH2D* hist_2d_mc(std::string filename){

	std::string file = "./"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("ZPKUCandidates");

	Double_t Mjj,Mjj_new,Mjj_JER_up,Mjj_JER_down;
	Double_t ZGmass;
	Double_t deltaeta;
	Double_t actualWeight;
        Double_t scalef,lumiWeight,pileupWeight,muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,muon1_track_scale,muon2_track_scale,muon_hlt_scale;

	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("Mjj_new", &Mjj_new);
	t->SetBranchAddress("Mjj_JER_up", &Mjj_JER_up);
	t->SetBranchAddress("Mjj_JER_down", &Mjj_JER_down);
	t->SetBranchAddress("Mva", &ZGmass);
	t->SetBranchAddress("deltaeta", &deltaeta);
	t->SetBranchAddress("pileupWeight", &pileupWeight);
	t->SetBranchAddress("lumiWeight", &lumiWeight);
//	t->SetBranchAddress("scalef", &scalef);
	t->SetBranchAddress("muon1_id_scale",&muon1_id_scale);
	t->SetBranchAddress("muon2_id_scale",&muon2_id_scale);
	t->SetBranchAddress("muon1_iso_scale",&muon1_iso_scale);
	t->SetBranchAddress("muon2_iso_scale",&muon2_iso_scale);
	t->SetBranchAddress("muon1_track_scale",&muon1_track_scale);
	t->SetBranchAddress("muon2_track_scale",&muon2_track_scale);
	t->SetBranchAddress("muon_hlt_scale",&muon_hlt_scale);
 

	Double_t mjj_bins[4]={500, 750, 1000, 2000};
//	Double_t mlla_bins[5]={90, 130, 170, 210, 240};
	Double_t deltaeta_bins[4]={2.5, 4.5,  6, 6.5};
//	TH2D* th2 = new TH2D("th2","th2",4, mjj_bins, 4, mlla_bins);
	TH2D* th2 = new TH2D("th2","th2",3, mjj_bins, 3, deltaeta_bins);
	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		scalef = 0.000365678;
                actualWeight = scalef * pileupWeight*lumiWeight ;
		cout<<"scalef = "<<scalef<<"; pileupWeight = "<<pileupWeight<<"; limiWeight = "<<lumiWeight<<endl;
                cout<<"muon1_id_scale = "<<muon1_id_scale<<endl;
                cout<<"muon2_id_scale = "<<muon2_id_scale<<endl;
                cout<<"muon1_iso_scale = "<<muon1_iso_scale<<endl;
                cout<<"muon2_iso_scale = "<<muon2_iso_scale<<endl;
                cout<<"muon1_track_scale = "<<muon1_track_scale<<endl;
                cout<<"muon2_track_scale = "<<muon2_track_scale<<endl;
                cout<<"muon_hlt_scale = "<<muon_hlt_scale<<endl;
               
//* muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon1_track_scale*muon2_track_scale*muon_hlt_scale;
		cout<<"actualWeight = "<<actualWeight<<endl;
		if(Mjj<2000 && deltaeta<6.5) th2->Fill(Mjj, deltaeta, actualWeight);
		if(Mjj>=2000 && deltaeta<6.5) th2->Fill(1999, deltaeta, actualWeight);
		if(Mjj<2000 && deltaeta>=6.5) th2->Fill(Mjj, 6.1, actualWeight);
		if(Mjj>=2000 && deltaeta>=6.5) th2->Fill(1999, 6.1, actualWeight);
	}

	return th2;
}
/*TH2D* hist_2d(std::string filename){

	std::string file = "../result_andy/optimal_"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj;
	Double_t ZGmass;
	Double_t deltaeta;
	Double_t actualWeight;

	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("ZGmass", &ZGmass);
	t->SetBranchAddress("deltaeta", &deltaeta);
	t->SetBranchAddress("actualWeight", &actualWeight);

	Double_t mjj_bins[4]={500, 750, 1000, 2000};
//	Double_t mlla_bins[5]={90, 130, 170, 210, 250};
	Double_t deltaeta_bins[4]={2.5, 4.5, 6, 6.5};
//	TH2D* th2 = new TH2D("th2","th2",4, mjj_bins, 4, mlla_bins);
	TH2D* th2 = new TH2D("th2","th2",3, mjj_bins, 3, deltaeta_bins);
	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		if(Mjj<2000 && deltaeta<6.5) th2->Fill(Mjj, deltaeta);
		if(Mjj>=2000 && deltaeta<6.5) th2->Fill(1999, deltaeta);
		if(Mjj<2000 && deltaeta>=6.5) th2->Fill(Mjj, 6.1);
		if(Mjj>=2000 && deltaeta>=6.5) th2->Fill(1999, 6.1);
	}

	return th2;
}*/

int main(){
//	TFile* f1=new TFile("2d_ST.root","RECREATE");
//	TFile* f2=new TFile("2d_VV.root","RECREATE");
//	TFile* f3=new TFile("2d_TTA.root","RECREATE");
//	TFile* f4=new TFile("2d_WA.root","RECREATE");
//	TFile* f5=new TFile("2d_ZA.root","RECREATE");
//	TFile* f6=new TFile("2d_ZA_EWK.root","RECREATE");
//	TFile* f7=new TFile("2d_plj.root","RECREATE");
//	TFile* f8=new TFile("2d_DMuon.root","RECREATE");

//	TH2D* h1= hist_2d_mc("ST");
//	TH2D* h2= hist_2d_mc("VV");
//	TH2D* h3= hist_2d_mc("TTA");
//	TH2D* h4= hist_2d_mc("WA");
//	TH2D* h5= hist_2d_mc("ZA");
//	TH2D* h6= hist_2d_mc("outZA-EWK");
//	TH2D* h7= hist_2d_mc("plj_weightb");
//	TH2D* h8= hist_2d("outDMuon");
	TFile *file = new TFile("2d_jec.root","RECREATE");	
        TH2D* hist = hist_2d_mc("sig-outJEC-ZA-EWK");
        file->cd();
        hist->Write();
        file->Close();
	return 0;
//	f1->cd();
//	h1->Write();
//	f1->Close();
//	f2->cd();
//	h2->Write();
//	f2->Close();
//	f3->cd();
//	h3->Write();
//	f3->Close();
//	f4->cd();
//	h4->Write();
//	f4->Close();
//	f5->cd();
//	h5->Write();
//	f5->Close();
//	f6->cd();
//	h6->Write();
//	f6->Close();
//	f7->cd();
//	h7->Write();
//	f7->Close();
//	f8->cd();
//	h8->Write();
//	f8->Close();
}
