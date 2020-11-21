#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

using namespace std;

TH1D* hist_1d(TString filename){

	TString file;
	if(filename.Contains("plj")==0) file = "./optimal_aqgc_"+filename+"16.root";
	else file="./optimal_aqgc_"+filename+"16_weight.root";
	TFile* f1 = TFile::Open(file);

	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj;
	Double_t ZGmass;
	Double_t detajj;
	Double_t actualWeight;
        int lep;

	t->SetBranchAddress("lep", &lep);
	t->SetBranchAddress("ZGmass", &ZGmass);
	t->SetBranchAddress("detajj", &detajj);
	t->SetBranchAddress("actualWeight", &actualWeight);
        const double lumi=35.86;
	Double_t mva_bins[6]={150,400,600,800,1000,2000};
	TH1D* th2 = new TH1D(filename,"th2",5,mva_bins);
	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
                if(ZGmass>2000) ZGmass=1999;
                if(filename.Contains("plj")==0 && filename.Contains("Muon")==0&&filename.Contains("Ele")==0)
			actualWeight = actualWeight*lumi;
		if(lep==11)
			th2->Fill(ZGmass,actualWeight);
	}

	return th2;
}

int d_hist_ele(){
	TFile* f1=new TFile("out_aqgc_ele16.root","RECREATE");

	TH1D* h1= hist_1d("bkg");
	TH1D* h2= hist_1d("ZA");
	TH1D* h3= hist_1d("plj");
	TH1D* h5= hist_1d("ZA-EWK");
	TH1D* h6= hist_1d("Muon");
	TH1D* h7= hist_1d("Ele");
	
	f1->cd();
	h1->Write();
	h2->Write();
	h3->Write();
	h5->Write();
	h6->Write();
	h7->Write();
	f1->Close();
return 0;
}
