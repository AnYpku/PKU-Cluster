#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>

using namespace std;
TH1D* hist_1d(std::string filename);
TH1D* hist_1d(std::string filename);

TH1D* hist_1d_mc(std::string filename){

	std::string file = "./optimal_"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj;
	Double_t detajj;
	Double_t actualWeight;
	Double_t scalef;
	Double_t pileupWeight;
	Double_t lumiWeight;

	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("detajj", &detajj);
	t->SetBranchAddress("scalef", &scalef);
	t->SetBranchAddress("pileupWeight", &pileupWeight);
	t->SetBranchAddress("lumiWeight", &lumiWeight);
	Double_t mjj_bins[2]={150,400};
//	Double_t mlla_bins[5]={90, 130, 170, 210, 240};
	Double_t detajj_bins[4]={2.5, 4.5, 6, 6.5};
//	TH1D* th2 = new TH1D("th2","th2",4, mjj_bins, 4, mlla_bins);
	TH1D* th2 = new TH1D("th2","th2",1, mjj_bins);
//	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		actualWeight = scalef * lumiWeight * pileupWeight;
                if(Mjj<400 && Mjj>150) th2->Fill(Mjj,actualWeight * 35.86*0.96);
		if(Mjj<=150 ) th2->Fill(150, actualWeight* 35.86*0.96);
	}

	return th2;
}
TH1D* hist_1d(std::string filename){

	std::string file = "./optimal_"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj;
	Double_t ZGmass;
	Double_t detajj;
	Double_t actualWeight;
	Double_t scalef;
	Double_t pileupWeight;
	Double_t lumiWeight;

	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("detajj", &detajj);
	t->SetBranchAddress("scalef", &scalef);
	t->SetBranchAddress("pileupWeight", &pileupWeight);
	t->SetBranchAddress("lumiWeight", &lumiWeight);

	Double_t mjj_bins[2]={150,400};
//	Double_t mlla_bins[5]={90, 130, 170, 210, 250};
	Double_t detajj_bins[4]={2.5, 4.5, 6, 6.5};
//	TH1D* th2 = new TH1D("th2","th2",4, mjj_bins, 4, mlla_bins);
	TH1D* th2 = new TH1D("th2","th2",1, mjj_bins);
//	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
		actualWeight = scalef * lumiWeight * pileupWeight;
                if(Mjj<400 && Mjj>150) th2->Fill(Mjj);
		if(Mjj<150 ) th2->Fill(150);
	}

	return th2;
}

int mm(){
	TH1D* h1= hist_1d_mc("ST");
	TH1D* h2= hist_1d_mc("VV");
	TH1D* h3= hist_1d_mc("TTA");
	TH1D* h4= hist_1d_mc("WA");
	TH1D* h5= hist_1d_mc("ZA");
	TH1D* h6= hist_1d_mc("ZA-EWK");
	TH1D* h7= hist_1d_mc("ZJets_FX");
	TH1D* h8= hist_1d_mc("TTJets");
	TH1D* h9= hist_1d_mc("WJets");
	TH1D* h10= hist_1d("Muon");

    TH1D* hist = (TH1D*)h1->Clone();
    hist->Add(h2,1);
    hist->Add(h3,1);
    hist->Add(h4,1);
    hist->Add(h5,1);
    hist->Add(h6,1);
    hist->Add(h7,1);
    hist->Add(h8,1);
    hist->Add(h9,1);
    h10->SetLineColor(kPink);
    h10->SetLineWidth(3);
    h10->SetLineStyle(3);
   // h1->SetLineColor(1);
   // h2->SetLineColor(2);
   // h3->SetLineColor(3);
   // h4->SetLineColor(4);
   // h5->SetLineColor(5);
    h6->SetLineColor(6);
    h6->SetLineWidth(3);
   // h7->SetLineColor(7);
   // h8->SetLineColor(8);
   // h9->SetLineColor(9);
    THStack* hs = new THStack("hs","");
    hs->Add(h1);
    hs->Add(h2);
    hs->Add(h3);
    hs->Add(h4);
    hs->Add(h5);
    hs->Add(h6);
    hs->Add(h7);
    hs->Add(h8);
    hs->Add(h9);
    hist->SetLineColor(kOrange);
    hist->SetLineWidth(2);
    hs->Draw(" hist");
    hist->Draw("same hist");
    h10->Draw("same hist");
    cout<<"SF = "<<h10->GetBinContent(1)/hist->GetBinContent(1);
return 0;
	
}
