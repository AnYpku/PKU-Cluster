#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#define num 7

using namespace std;

TH1D* hist = new TH1D("h","mjj vs deltaetajj",9,0,9);
TH2D* run(std::string filename,Int_t i);
TH2D* run(std::string filename,Int_t i){

	std::string file = filename;
	TFile* f1 = TFile::Open(file.c_str());

//	TTree* t = (TTree*)f1->Get("demo");
	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj,zepp;
	Double_t deltaetajj;
	Double_t theWeight,lumiWeight,scalef,pweight[703],pileupWeight;
	Int_t lep;Double_t photoneta;
    
	t->SetBranchAddress("lep",&lep);
	t->SetBranchAddress("photoneta", &photoneta);
	t->SetBranchAddress("Mjj", &Mjj);
	t->SetBranchAddress("zepp", &zepp);
//	t->SetBranchAddress("deltaetajj", &deltaetajj);
	t->SetBranchAddress("detajj", &deltaetajj);
	t->SetBranchAddress("pileupWeight",&pileupWeight);
	t->SetBranchAddress("scalef", &scalef);
	t->SetBranchAddress("theWeight", &theWeight);
	t->SetBranchAddress("lumiWeight", &lumiWeight);

	Double_t mjj_bins[4]={500, 800,1200, 2000};
	Double_t deltaetajj_bins[4]={2.5, 4.5, 6, 6.5};
        TH2D* th2[3]; 
	char th2name[num];
	sprintf(th2name,"th2_%d",i);
	th2[i] = new TH2D(th2name,th2name,3, mjj_bins, 3, deltaetajj_bins);
	th2[i]->Sumw2();

	for(Int_t j=0; j<t->GetEntries();j++)
	{
		t->GetEntry(j);
//		if( !(lep==13 && fabs(photoneta)<1.4442) ) continue;
//		cout<<"scalef "<<scalef<<endl;
		if(Mjj<2000 && deltaetajj<6.5)   th2[i]->Fill(Mjj,deltaetajj,scalef);
		if(Mjj>=2000 && deltaetajj<6.5)  th2[i]->Fill(1999,deltaetajj,scalef);
		if(Mjj<2000 && deltaetajj>=6.5)  th2[i]->Fill(Mjj,6.1,scalef);
		if(Mjj>=2000 && deltaetajj>=6.5) th2[i]->Fill(1999,6.1,scalef);

/*		if(Mjj>=500&&Mjj<800&&deltaetajj>=2.5&&deltaetajj<4.5) hist->Fill(0.5,scalef);//0~1, 2.5~4.5 500~800
		if(Mjj>=800&&Mjj<1200&&deltaetajj>=2.5&&deltaetajj<4.5) hist->Fill(1.5,scalef);//1~2 2.5~4.5 800~1200
		if(Mjj>=1200&&deltaetajj>=2.5&&deltaetajj<4.5) hist->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000

		if(Mjj>=500&&Mjj<800&&deltaetajj>=4.5&&deltaetajj<6) hist->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		if(Mjj>=800&&Mjj<1200&&deltaetajj>=4.5&&deltaetajj<6) hist->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		if(Mjj>=1200&&deltaetajj>=4.5&&deltaetajj<6) hist->Fill(5.5,scalef);

		if(Mjj>=500&&Mjj<800&&deltaetajj>=6) hist->Fill(6.5,scalef);
		if(Mjj>=800&&Mjj<1200&&deltaetajj>=6) hist->Fill(7.5,scalef);
		if(Mjj>=1200&&deltaetajj>=6) hist->Fill(8.5,scalef);*/
	}
	return th2[i];
}

int d_hist(){
	TH2D* h0 =    run("/home/pku/anying/cms/RunII2017/aa2/Barrel/output-slimmed-rootfiles/optimal_2017_plj_barrel.root",0);
	TH2D* hup =   run("/home/pku/anying/cms/RunII2017/aa2/Barrel/output-slimmed-rootfiles/optimal_2017_plj_barrel_up.root",1);
	TH2D* hdown = run("/home/pku/anying/cms/RunII2017/aa2/Barrel/output-slimmed-rootfiles/optimal_2017_plj_barrel_down.root",2);
	TFile* f5=new TFile("th2-histo.root","RECREATE");
	h0->Write();
	hup->Write();
	hdown->Write();
	f5->Close();
	return 0;
}
