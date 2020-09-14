#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#define num 9

using namespace std;

TH2D*th2[num];
void run(std::string filename);
void run(std::string filename){

	std::string file = filename+".root";
	TFile* f1 = TFile::Open(file.c_str());

	TTree* t = (TTree*)f1->Get("demo");
//	TTree* t = (TTree*)f1->Get("ZPKUCandidates");

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

//	Double_t mjj_bins[4]={500, 750, 1000, 2000};
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
        if( !(lep==13 && fabs(photoneta)<1.4442) ) continue;
        for(Int_t i=0;i<45;i++){
           if( flag  && (p==5 || p==7) ) continue;
        actualWeight[p]=scalef*lumiWeight*pweight[p];
		if(Mjj<2000 && detajj<6.5) th2[p]->Fill(Mjj, detajj, actualWeight[p]);
		if(Mjj>=2000 && detajj<6.5) th2[p]->Fill(1999, detajj, actualWeight[p]);
		if(Mjj<2000 && detajj>=6.5) th2[p]->Fill(Mjj, 6.1, actualWeight[p]);
		if(Mjj>=2000 && detajj>=6.5) th2[p]->Fill(1999, 6.1, actualWeight[p]);
        i=i+4;
        p++;
     	}
         cout<<"p = "<<p<<endl;
         cout<<"entry "<<j<<endl;
         cout<<"scalef = "<<scalef<<endl;
         cout<<"pileupWeight = "<<pileupWeight<<endl;
         cout<<"lumiWeight = "<<lumiWeight<<endl;
/*         cout<<"pweight[1001] = "<<pweight[0]<<endl; 
         cout<<"pweight[1006] = "<<pweight[5]<<endl; 
         cout<<"pweight[1011] = "<<pweight[10]<<endl; 
         cout<<"pweight[1016] = "<<pweight[15]<<endl; 
         cout<<"pweight[1021] = "<<pweight[20]<<endl; 
         cout<<"pweight[1026] = "<<pweight[25]<<endl; */
         
         for(Int_t k=0;k<5*num;k++){
             cout<<"pweight ["<<k<<"] = "<<pweight[k]<<endl;
             k=k+4;
          }

         for(Int_t k=0;k<num;k++){
            cout<<"actualWeight ["<<k<<"] = "<<actualWeight[k]<<endl;
          }
         cout<<"######################################"<<endl;
    }
//  return 0;
}

int d_hist(){
	run("cutlaj-outZA-EWK-pweight");
	TFile* f5=new TFile("th2-histo.root","RECREATE");
    for(Int_t i=0;i<num;i++){
	   th2[i]->Write();}
	f5->Close();
    return 0;
	
}
