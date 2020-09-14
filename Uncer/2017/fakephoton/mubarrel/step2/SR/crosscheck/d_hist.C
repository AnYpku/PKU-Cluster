#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#define num 7

using namespace std;

TH1D* hist = new TH1D("h","mjj vs detajj",9,0,9);
TH2D* run(std::string filename,Int_t i);
TH2D* run(std::string filename,Int_t i){

	std::string file = filename;
	TFile* f1 = TFile::Open(file.c_str());

//	TTree* t = (TTree*)f1->Get("demo");
	TTree* t = (TTree*)f1->Get("outtree");
        Int_t lep;
        Double_t detajj,Mjj,delta_phi,zepp,photoneta,actualWeight;
        t->SetBranchAddress("lep",&lep);
        t->SetBranchAddress("actualWeight",&actualWeight);
        t->SetBranchAddress("detajj",&detajj);
        t->SetBranchAddress("Mjj",&Mjj);
        t->SetBranchAddress("delta_phi",&delta_phi);
        t->SetBranchAddress("zepp",&zepp);
        t->SetBranchAddress("photoneta",&photoneta);
	Double_t mjj_bins[4]={500, 800,1200, 2000};
	Double_t detajj_bins[4]={2.5, 4.5, 6, 6.5};
        TH2D* th2; 
	char th2name[100];
	sprintf(th2name,"th2_%d",i);
	th2 = new TH2D(th2name,th2name,3, mjj_bins, 3, detajj_bins);
	th2->Sumw2();

	for(Int_t j=0; j<t->GetEntries();j++)
	{
		t->GetEntry(j);
		if( !(lep==13 && fabs(photoneta)<1.4442 && Mjj>500 && detajj>2.5 && delta_phi>1.9 && zepp<2.4) ) continue;
//		cout<<" "<<actualWeight<<endl;
		if(Mjj<2000 && detajj<6.5)   th2[i]->Fill(Mjj,detajj);
		if(Mjj>=2000 && detajj<6.5)  th2[i]->Fill(1999,detajj);
		if(Mjj<2000 && detajj>=6.5)  th2[i]->Fill(Mjj,6.1);
		if(Mjj>=2000 && detajj>=6.5) th2[i]->Fill(1999,6.1);

/*		if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5) hist->Fill(0.5,);//0~1, 2.5~4.5 500~800
		if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5) hist->Fill(1.5,);//1~2 2.5~4.5 800~1200
		if(Mjj>=1200&&detajj>=2.5&&detajj<4.5) hist->Fill(2.5,);//2~3 2.5~4.5 1200~2000

		if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6) hist->Fill(3.5,);//3~4 4.5~6 500~800 
		if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6) hist->Fill(4.5,);//4~5 4.5~6 800~1200
		if(Mjj>=1200&&detajj>=4.5&&detajj<6) hist->Fill(5.5,);

		if(Mjj>=500&&Mjj<800&&detajj>=6) hist->Fill(6.5,);
		if(Mjj>=800&&Mjj<1200&&detajj>=6) hist->Fill(7.5,);
		if(Mjj>=1200&&detajj>=6) hist->Fill(8.5,);*/
	}
	return th2;
}

int d_hist(){
	TH2D* h0 = run("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/aa2/ScalSeq/output-slimmed-rootfiles/optimal_2016_plj_mubarrel.root");
	TH2D* hup = run("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/aa2/ScalSeq/output-slimmed-rootfiles/optimal_2016_plj_mubarrel_up.root");
	TH2D* hdown = run("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/aa2/ScalSeq/output-slimmed-rootfiles/optimal_2016_plj_mubarrel_down.root");
	TFile* f5=new TFile("th2-histo.root","RECREATE");
	h0->Write();
	hup->Write();
	hdown->Write();
	f5->Close();
	return 0;
}
