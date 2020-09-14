#include "L1_weight.C"
#include <iostream>
#include <fstream>
#include <TH2.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <THStack.h>
#include <TFile.h>
#include <TROOT.h>
#include <TChain.h>
#include "TObject.h"

using namespace std;

TH1D* h1 = new TH1D("h1","",200,0,200);
TH1D* h2 = new TH1D("h2","",200,0,200);
TH1D* h3 = new TH1D("h3","",200,0,200);
THStack* hs = new THStack("hs","");
TH1D* hh1 = new TH1D("hh1","",200,0,200);
TH1D* hh2 = new TH1D("hh2","",200,0,200);
TH1D* hh3 = new TH1D("hh3","",200,0,200);
THStack* hhs = new THStack("hhs","");
	Double_t massVlep,Mva,pileupWeight,lumiWeight,scalef;
	Int_t nlooseeles,nloosemus;
	Double_t photon_drla[6],photon_pt[6],photon_drla2[6],photon_sieie[6],photon_chiso[6];
	double photon_hoe[6];
	double photon_nhiso[6];
	double photon_phoiso[6];
	double photon_eta[6];
	Double_t ptlep1,ptlep2,etalep1,etalep2;
	double lep1_phi_station2_tmp;
	double lep2_phi_station2_tmp;
	double lep1_phi_station2;
	double lep2_phi_station2;
	double lep1_eta_station2;
	double lep2_eta_station2;
	vector<double> vector_pt;
	vector<double>::iterator biggest_pt;
	Int_t position,size,lep,run_period;
	Bool_t Photon_cut[6],photon_pevnew[6],LEPdata,LEPmc,HLT_Mu2,HLT_Mu5,LEP;
void loop(TString name);
void loop(TString name){
	Double_t l1_weight,m=0,k=0,n=0;
//	TString dir = "/data/pku/home/anying/cms/file_in_cms/files_weighted/";
	TString dir = "../rootfiles/";
        TString filename = name + ".root";
	TFile* file = TFile::Open(dir+filename);
	TTree* tree = (TTree*)file->Get("demo");

	tree->SetBranchAddress("scalef",&scalef);
	tree->SetBranchAddress("pileupWeight",&pileupWeight);
	tree->SetBranchAddress("lumiWeight",&lumiWeight);
	tree->SetBranchAddress("massVlep",&massVlep);
	tree->SetBranchAddress("Mva",&Mva);
	tree->SetBranchAddress("lep1_phi_station2",&lep1_phi_station2);
	tree->SetBranchAddress("lep2_phi_station2",&lep2_phi_station2);
	tree->SetBranchAddress("lep1_eta_station2",&lep1_eta_station2);
	tree->SetBranchAddress("lep2_eta_station2",&lep2_eta_station2);

	tree->SetBranchAddress("photon_hoe",photon_hoe);
	tree->SetBranchAddress("photon_nhiso",photon_nhiso);
	tree->SetBranchAddress("photon_phoiso",photon_phoiso);
	tree->SetBranchAddress("photon_pt",photon_pt);
	tree->SetBranchAddress("photon_eta",photon_eta);
	tree->SetBranchAddress("nloosemus",&nloosemus);
	tree->SetBranchAddress("nlooseeles",&nlooseeles);
	tree->SetBranchAddress("ptlep1",&ptlep1);
	tree->SetBranchAddress("ptlep2",&ptlep2);
	tree->SetBranchAddress("etalep1",&etalep1);
	tree->SetBranchAddress("etalep2",&etalep2);
	tree->SetBranchAddress("photon_drla",photon_drla);
	tree->SetBranchAddress("photon_drla2",photon_drla2);
	tree->SetBranchAddress("photon_sieie",photon_sieie);
	tree->SetBranchAddress("photon_chiso",photon_chiso);
	tree->SetBranchAddress("photon_pt",photon_pt);
	tree->SetBranchAddress("photon_pevnew",photon_pevnew);


	cout<<"nentries = "<<tree->GetEntries()<<endl;
	double nentries = tree->GetEntries();
//        nentries=1000000;
	for(Int_t i=0;i<nentries;i++){
		tree->GetEntry(i);
		if(i%1000000==0) cout<<i<<endl;
		lep1_phi_station2_tmp = lep1_phi_station2;
		lep2_phi_station2_tmp = lep2_phi_station2;
		l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
		LEPdata = l1_weight==1  && lep==13 && ptlep1 >20. && ptlep2 >20.&& abs(etalep1) <2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && ((run_period<7 && HLT_Mu5 > 0)|| (run_period==7 && HLT_Mu2 > 0));
		LEPmc = l1_weight==1 && HLT_Mu2 > 0 && lep==13 && ptlep1 >20. && ptlep2 >20.&& abs(etalep1) <2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3;
		LEP = lep==13 && ptlep1 >20. && ptlep2 >20.&& abs(etalep1) <2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3;
	/*	for(Int_t j=0;j<6;j++)
		{
			if( (name.Contains("outZA")==1&& LEPmc==1) || (name.Contains("outZJets")==1&& LEPmc==1) || (name.Contains("outDMuon")==1&& LEPdata==1) )
			{
				Photon_cut[j]=photon_pevnew[j]==1&&
					photon_hoe[j]<0.0396 &&
					photon_chiso[j]<0.441 &&
					photon_nhiso[j]<2.725 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j] &&
					photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&
					fabs(photon_eta[j])<1.4442 &&
					photon_pt[j]>10;
			}
			if(Photon_cut[j]){
				vector_pt.push_back(photon_pt[j]);}
			else   {vector_pt.push_back(0);}
		}//fill the vector_pt
		size=vector_pt.size();
		biggest_pt = max_element(begin(vector_pt),end(vector_pt));
		if(*biggest_pt==0){
			vector_pt.clear();
			continue;}*/
		if(name.Contains("DMuon"))
	         	{
				h1->Fill(massVlep);m++;
				hh1->Fill(Mva);
			}

		if(name.Contains("ZJets"))
		        {
				h3->Fill(massVlep,scalef*pileupWeight*lumiWeight*35.8*0.96);n++;
				hh3->Fill(Mva,scalef*pileupWeight*lumiWeight*35.8*0.96);
			}
		if(name.Contains("ZA"))
		        {
				h2->Fill(massVlep,scalef*pileupWeight*lumiWeight*35.8*0.96);k++;
				hh2->Fill(Mva,scalef*pileupWeight*lumiWeight*35.8*0.96);
			}

	}
	if(name.Contains("DMuon")) cout<<"m "<<m<<endl;
	if(name.Contains("ZA"))    cout<<"k "<<k<<endl;
	if(name.Contains("ZJets")) cout<<"n "<<n<<endl;
}
int SR(){
	loop("ToutDMuon");
	loop("ToutZA");
	loop("ToutZJets_FX");
	TCanvas* c1 = new TCanvas("c1","",900,600);
	c1->SetGrid();
  //      c1->SetLogy();
	TLegend* t1 = new TLegend(0.7,0.7,0.9,0.9);
	h2->SetLineColor(2);
        h2->SetFillColor(2);
	h3->SetLineColor(3);
        h3->SetFillColor(3);
	h1->SetLineColor(kBlack);
	h1->SetMarkerStyle(20);
        t1->AddEntry("h1","Data","L");
        t1->AddEntry("h2","ZA","L");
        t1->AddEntry("h3","ZJets","L");
	hs->Add(h3);
	hs->Add(h2);
        hs->Draw(" hist");
        h1->Draw("same PE");
        t1->Draw();
        c1->Print("./fig/massVlep.eps");
        cout<<"massVlep saved"<<endl;

	TCanvas* can = new TCanvas("can","",900,600);
	TLegend* t2 = new TLegend(0.7,0.7,0.9,0.9);
	can->SetGrid();
//        can->SetLogy();
	hh2->SetLineColor(2);
        hh2->SetFillColor(2);
	hh3->SetLineColor(3);
        hh3->SetFillColor(3);
	hh1->SetLineColor(kBlack);
	hh1->SetMarkerStyle(20);
	hhs->Add(hh3);
	hhs->Add(hh2);
        t2->AddEntry(hh1,"Data");
        t2->AddEntry("hh2","ZA");
        t2->AddEntry("hh3","ZJets");
        hhs->Draw(" hist");
        hh1->Draw("same PE");
	t2->Draw();
        can->Print("./fig/Mva.eps");
        cout<<"Mva saved"<<endl;
	return 1;
}
