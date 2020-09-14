#include "TEfficiency.h"
//TCanvas* c1[4];
//TCanvas* c2[4];
void open(int i,TFile*file,TFile*f2){
	TH1D*hsN;TH1D*husN;
	TH1D*hsD;TH1D*husD;
	TEfficiency* hseed;
	TEfficiency* hunseed;
	TString name = file->GetName();
	hsN = (TH1D*)file->Get(Form("hsN_%i",i+1));
	hsD = (TH1D*)file->Get(Form("hsD_%i",i+1));
	husN = (TH1D*)file->Get(Form("hunsN_%i",i+1));
	husD = (TH1D*)file->Get(Form("hunsD_%i",i+1));
//cout<<"OK1"<<endl;
//        hsN->Sumw2();husN->Sumw2();
//        hsD->Sumw2();husD->Sumw2();
	if(TEfficiency::CheckConsistency(*hsN,*hsD))
        	{hseed = new TEfficiency(*hsN,*hsD);}
	if(TEfficiency::CheckConsistency(*husN,*husD))
        	{hunseed = new TEfficiency(*husN,*husD);}
	TString title1 = hsN->GetTitle();
	TString title2 = husN->GetTitle();
//cout<<"OK3"<<endl;
         hseed->SetTitle(/*"Seed_"+*/title1);
         hunseed->SetTitle(/*"unSeed_"+*/title1);
	hseed->Draw("ape");
	hunseed->Draw("ape");

	f2->cd();
	hseed->Write();hunseed->Write();hsN->Write();
	delete hsN;delete hsD;delete husN;delete husD;delete hseed;delete hunseed;
//	delete c1;
}
int draw(){
//	TFile* f1 = new TFile("50_120_barrel.root");
//	TFile* f2 = new TFile("120_200_barrel.root");
	TFile* f1 = new TFile("50_120_endcap.root");
	TFile* f2 = new TFile("120_200_endcap.root");
        TString filename1 = f1->GetName();
        TString filename2 = f2->GetName();
        TString name1 = "eff_"+ filename1 ;
        TString name2 = "eff_"+ filename2;
	TFile* eff1 = new TFile(name1,"recreate");
	TFile* eff2 = new TFile(name2,"recreate");
	f1->cd();
	for(int i=0;i<4;i++){
		open(i,f1,eff1);
	}
	f1->Close();
        eff1->Close();
	f2->cd();
	for(int i=0;i<4;i++){
		open(i,f2,eff2);
	}
	f2->Close();
return 1;
}
