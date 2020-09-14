#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>
#include "TTreeFormula.h"
#include "TSystem.h"

using namespace std;

TH2D* hist_2d_mc(std::string filename){

	std::string file = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2018/aa2/ScalSeq/output-slimmed-rootfiles/optimal_2018_"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj;
	Double_t ZGmass;
	Double_t detajj;
	Double_t actualWeight;

	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("ZGmass", &ZGmass);
	t->SetBranchAddress("detajj", &detajj);
	t->SetBranchAddress("actualWeight", &actualWeight);

	Double_t mjj_bins[2]={150,400 };
	Double_t detajj_bins[2]={0,6.5};
        TString cut="ZGmass>100 && lep==11 && fabs(photoneta)<2.5 && fabs(photoneta)>1.566 && Mjj<400 && Mjj>150";
//        TString cut="ZGmass>100 && lep==13 && fabs(photoneta)<1.4442 && Mjj<400 && Mjj>150";
        TTreeFormula* formula= new TTreeFormula("f",cut,t);
	TH2D* th2 = new TH2D("th2","th2",1, mjj_bins, 1, detajj_bins);
	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		if( ! formula->EvalInstance())
			continue;
                if(detajj>6.5) detajj=6.1;
		th2->Fill(Mjj, detajj,actualWeight);
	}

	return th2;
}
TH2D* hist_2d(std::string filename){

	std::string file = "/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2018/aa2/ScalSeq/output-slimmed-rootfiles/optimal_2018_"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj;
	Double_t ZGmass;
	Double_t detajj;
	Double_t actualWeight;

	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("ZGmass", &ZGmass);
	t->SetBranchAddress("detajj", &detajj);
	t->SetBranchAddress("actualWeight", &actualWeight);
//        TString cut="ZGmass>100 && lep==13 && fabs(photoneta)<1.4442 && Mjj<400 && Mjj>150";
        TString cut="ZGmass>100 && lep==11 && fabs(photoneta)<2.5 && fabs(photoneta)>1.566 && Mjj<400 && Mjj>150";
        TTreeFormula* formula= new TTreeFormula("f",cut,t);
	Double_t mjj_bins[2]={150,400};
	Double_t detajj_bins[2]={0,6.5};
//	TH2D* th2 = new TH2D("th2","th2",4, mjj_bins, 4, mlla_bins);
	TH2D* th2 = new TH2D("th2","th2",1, mjj_bins, 1, detajj_bins);
	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		if( ! formula->EvalInstance())
			continue;
                if(detajj>6.5) detajj=6.1;
		th2->Fill(Mjj, detajj,actualWeight);
	}

	return th2;
}

int main(){
	gSystem->Load("libTreePlayer.so");
	TFile* f1=new TFile("2d_ST.root","RECREATE");
	TFile* f2=new TFile("2d_VV.root","RECREATE");
	TFile* f3=new TFile("2d_TTA.root","RECREATE");
	TFile* f4=new TFile("2d_WA.root","RECREATE");
	TFile* f5=new TFile("2d_ZA.root","RECREATE");
	TFile* f6=new TFile("2d_ZA_EWK.root","RECREATE");
	TFile* f7=new TFile("2d_plj.root","RECREATE");
	TFile* f8=new TFile("2d_Ele.root","RECREATE");

	TH2D* h1= hist_2d_mc("ST");
	TH2D* h2= hist_2d_mc("VV");
	TH2D* h3= hist_2d_mc("TTA");
	TH2D* h4= hist_2d_mc("WA");
	TH2D* h5= hist_2d_mc("ZA");
	TH2D* h6= hist_2d_mc("ZA-EWK");
	TH2D* h7= hist_2d_mc("plj_eleendcap");
	TH2D* h8= hist_2d("Ele");
	
	f1->cd();
	h1->Write();
	f1->Close();
	f2->cd();
	h2->Write();
	f2->Close();
	f3->cd();
	h3->Write();
	f3->Close();
	f4->cd();
	h4->Write();
	f4->Close();
	f5->cd();
	h5->Write();
	f5->Close();
	f6->cd();
	h6->Write();
	f6->Close();
	f7->cd();
	h7->Write();
	f7->Close();
	f8->cd();
	h8->Write();
	f8->Close();
}
