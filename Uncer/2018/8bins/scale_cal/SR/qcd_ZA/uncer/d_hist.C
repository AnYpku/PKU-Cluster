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
//	TTree* t = (TTree*)f1->Get("ZPKUCandidates");
	TTree* t = (TTree*)f1->Get("outtree");
    Double_t Mjj,zepp;
    Double_t detajj;
    Double_t theWeight,lumiWeight,scalef,pweight[703],pileupWeight;
//  Double_t pileupWeight;
    Double_t actualWeight;
    Int_t lep;Double_t photoneta;
    double jet1pt,jet2pt,jet1eta,jet2eta,ZGmass;
    double delta_phi;
    t->SetBranchAddress("zepp",&zepp);
    t->SetBranchAddress("actualWeight",&actualWeight);
    t->SetBranchAddress("delta_phi",&delta_phi);
    t->SetBranchAddress("ZGmass",&ZGmass); 
    t->SetBranchAddress("jet1pt",&jet1pt); 
    t->SetBranchAddress("jet2pt",&jet2pt); 
    t->SetBranchAddress("jet1eta",&jet1eta); 
    t->SetBranchAddress("jet2eta",&jet2eta); 
    t->SetBranchAddress("lep",&lep);
    t->SetBranchAddress("photoneta", &photoneta);
    t->SetBranchAddress("Mjj", &Mjj);
    t->SetBranchAddress("deltaetajj", &detajj);
    t->SetBranchAddress("pweight", pweight);
    t->SetBranchAddress("pileupWeight",&pileupWeight);
    t->SetBranchAddress("scalef", &scalef);
    t->SetBranchAddress("theWeight", &theWeight);
    t->SetBranchAddress("lumiWeight", &lumiWeight);

	Double_t mjj_bins[4]={500, 800,1200, 2000};
	Double_t detajj_bins[4]={2.5, 4.5, 6, 6.5};
    char th2name[num];
    for(Int_t i=0;i<num;i++){
       sprintf(th2name,"th2_%d",i);
	   th2[i] = new TH2D(th2name,th2name,3, mjj_bins, 3, detajj_bins);
	   th2[i]->Sumw2();}
    Int_t p;
    bool flag=false;
    if(num==7) flag = true;
	for(Int_t j=0; j<t->GetEntries();j++)
	{
        p=0;
		t->GetEntry(j);
        if( !(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7))
          continue;
        if( !(ZGmass>100)  ) continue;
        if( !( Mjj>500 && detajj>2.5 && zepp<2.4 && delta_phi>1.9) ) continue;
        for(Int_t i=0;i<9;i++){
         /*if(p==0)  actualWeight[p]=scalef*lumiWeight*pweight[i];
         else  actualWeight[p]=2*scalef*lumiWeight*pweight[i];*/
           if( flag  && (i==5 || i==7) ) continue;
	   actualWeight=scalef*pweight[i];
		if(Mjj<2000 && detajj<6.5) th2[p]->Fill(Mjj, detajj, actualWeight);
		if(Mjj>=2000 && detajj<6.5) th2[p]->Fill(1999, detajj, actualWeight);
		if(Mjj<2000 && detajj>=6.5) th2[p]->Fill(Mjj, 6.1, actualWeight);
		if(Mjj>=2000 && detajj>=6.5) th2[p]->Fill(1999, 6.1, actualWeight);
        p++;
     	}
         cout<<"p = "<<p<<endl;
         cout<<"entry "<<j<<endl;
         cout<<"scalef = "<<scalef<<endl;
         cout<<"pileupWeight = "<<pileupWeight<<endl;
         for(Int_t k=0;k<num;k++){
             cout<<"pweight ["<<k<<"] = "<<pweight[k]<<endl;
          }
//         for(Int_t k=0;k<num;k++){
//            cout<<"actualWeight ["<<k<<"] = "<<actualWeight[k]<<endl;
//          }
         cout<<"######################################"<<endl;
    }
//  return 0;
}

int d_hist(){
//	run("/home/pku/anying/cms/file_in_cms/2018RunIIrootfiles/2018cutla/cutlaj-outZA_pweight_2018.root");
	run("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2018/aa2/ScalSeq/output-slimmed-rootfiles/optimal_2018_ZA_pweight.root");
	TFile* f5=new TFile("th2-histo.root","RECREATE");
    for(Int_t i=0;i<num;i++){
	   th2[i]->Write();}
	f5->Close();
    return 0;
	
}
