#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

using namespace std;

TH1D* hist_1d(TString filename){

	std::string file = "./optimal_2016aqgc_"+filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

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
        const double lumi=41.52;
	Double_t mva_bins[6]={150,400,600,800,1000,2000};
	TH1D* th2 = new TH1D(filename,"th2",5,mva_bins);
	th2->Sumw2();
	for(Int_t i=0; i<t->GetEntries();i++)
	{
		t->GetEntry(i);
                if(filename.Contains("plj")==0 && filename.Contains("Muon")==0&&filename.Contains("Ele")==0)
			actualWeight = actualWeight*lumi;
		if(lep==13)
			th2->Fill(ZGmass,actualWeight);
	}

	return th2;
}

int d_hist_mu(){
	TFile* f1=new TFile("out_aqgc_mu.root","RECREATE");

	TH1D* h1= hist_1d("bkg");
	TH1D* h2= hist_1d("ZA");
	TH1D* h3= hist_1d("plj");
	TH1D* h4= hist_1d("ZA_aQGC");
	TH1D* h5= hist_1d("ZA_EWK");
	TH1D* h6= hist_1d("Muon16");
	TH1D* h7= hist_1d("Ele16");
	
	f1->cd();
	h1->Write();
	h2->Write();
	h3->Write();
	h4->Write();
	h5->Write();
	h6->Write();
	h7->Write();
	f1->Close();
}
