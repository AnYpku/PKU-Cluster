{
#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>

	TFile *file1 = new TFile("out1.root","R"); 
	file1->cd("");

	TH1D* h1= (TH1D*) ZG_optimal_outDEle_nominal->Clone();
	h1->Sumw2();
	h1->SetName("data_obs");

	TH1D* h2= (TH1D*) ZG_optimal_outZA_EWK_nominal->Clone();
	h2->Sumw2();
	h2->SetName("signal_SM");

	TH1D* h3= (TH1D*) ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->Clone();
	h3->Sumw2();
	TH1D* h4= (TH1D*) ZG_optimal_bkg_nominal->Clone();
	h4->Sumw2();
	h4->Add(h3);
	h4->SetName("background");

	TH1D* h31= (TH1D*) ZG_optimal_outphotonlikejet_ele_mediumlikephoton_up->Clone();
	h31->Sumw2();
	TH1D* h41= (TH1D*) ZG_optimal_bkg_up->Clone();
	h41->Sumw2();
	h41->Add(h31);
	h41->SetName("background_el_backshapeUp");

	TH1D* h32= (TH1D*) ZG_optimal_outphotonlikejet_ele_mediumlikephoton_down->Clone();
	h32->Sumw2();
	TH1D* h42= (TH1D*) ZG_optimal_bkg_down->Clone();
	h42->Sumw2();
	h42->Add(h32);
	h42->SetName("background_el_backshapeDown");

	TFile *fout = new TFile("el_Limit_SM.root", "RECREATE");
	fout->cd(); 
	h1->Write();   
	h2->Write();   
	h4->Write();   
	h41->Write();   
	h42->Write();   
	fout->Write(); 
	fout->Close();
}
