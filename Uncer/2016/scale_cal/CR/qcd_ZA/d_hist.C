#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#define num 7

using namespace std;

TH2D*th2[num];
void run(std::string filename);
void run(std::string filename){

	std::string file = filename;
	TFile* f1 = TFile::Open(file.c_str());

//	TTree* t = (TTree*)f1->Get("demo");
	TTree* t = (TTree*)f1->Get("ZPKUCandidates");
//	TTree* t = (TTree*)f1->Get("outtree");

	Double_t Mjj,zepp;
	Double_t detajj;
    Double_t theWeight,lumiWeight,scalef,pweight[703],pileupWeight;
//    Double_t pileupWeight;
	Double_t actualWeight[num];
    Int_t lep;Double_t photoneta;
    
    t->SetBranchAddress("lep",&lep);
    t->SetBranchAddress("photoneta", &photoneta);
    t->SetBranchAddress("Mjj", &Mjj);
    t->SetBranchAddress("zepp", &zepp);
    t->SetBranchAddress("deltaetajj", &detajj);
    t->SetBranchAddress("pweight", pweight);
    t->SetBranchAddress("pileupWeight",&pileupWeight);
    t->SetBranchAddress("scalef", &scalef);
    t->SetBranchAddress("theWeight", &theWeight);
    t->SetBranchAddress("lumiWeight", &lumiWeight);
    //	t->SetBranchAddress("pileupWeight", &pileupWeight);

    //	Double_t mjj_bins[4]={500, 750, 1000, 400};
    Double_t mjj_bins[2]={150,400};
    Double_t detajj_bins[2]={2.5, 6.5};
    char th2name[num];
    for(Int_t i=0;i<num;i++){
       sprintf(th2name,"th2_%d",i);
	   th2[i] = new TH2D(th2name,th2name,1, mjj_bins, 1, detajj_bins);
	   th2[i]->Sumw2();}
    Int_t p;
    bool flag=false;
    if(num==7) flag = true;
	for(Int_t j=0; j<t->GetEntries();j++)
	{
		p=0;
		t->GetEntry(j);
		if( !(Mjj>150 && Mjj<400 && detajj>2.5) ) continue;
		for(Int_t i=104;i<113;i++){
			if( num==7 && (i==109 || i==111) ) continue;
			if(p==0)  actualWeight[p]=scalef*lumiWeight*pweight[i]*pileupWeight;
			else actualWeight[p]=2*scalef*lumiWeight*pweight[i]*pileupWeight;
			if(Mjj<400 && detajj<6.5) th2[p]->Fill(Mjj, detajj, actualWeight[p]);
			if(Mjj<400 && detajj>=6.5) th2[p]->Fill(Mjj, 6.1, actualWeight[p]);
			p++;
		}
		cout<<"p = "<<p<<endl;
		cout<<"entry "<<j<<endl;
		cout<<"scalef = "<<scalef<<endl;
		cout<<"pileupWeight = "<<pileupWeight<<endl;
		for(Int_t k=104;k<(104+num);k++){
			cout<<"pweight ["<<k<<"] = "<<pweight[k]<<endl;
		}
		for(Int_t k=104;k<(104+num);k++){
			cout<<"actualWeight ["<<k<<"] = "<<actualWeight[k]<<endl;
		}
		cout<<"######################################"<<endl;
	}
	//  return 0;
}

int d_hist(){
//	run("/home/pku/anying/cms/file_in_cms/2017RunIIrootfiles/2017cutla/cutla-outZA_pweight.root");
	run("/home/pku/anying/cms/file_in_cms/files_weighted/outZA-mu-ele.root");
	TFile* f5=new TFile("th2-histo.root","RECREATE");
	for(Int_t i=0;i<num;i++){
		th2[i]->Write();}
	f5->Close();
	return 0;
}
