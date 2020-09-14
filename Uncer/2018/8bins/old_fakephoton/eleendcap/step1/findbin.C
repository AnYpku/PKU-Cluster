#define findbin_cxx
#include "findbin.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>

#define num 1
using namespace std;

void findbin::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   ofstream file("./bincontent.txt");
   TH1D * h1[num];
   for(Int_t k=0;k<num;k++){
	   h1[k] = new TH1D(Form("h_%i",k+1),"",20000,4,13);
   }
   TFile* f1 = new TFile("chiso-hist.root","recreate");
   const int n = h1[0]->GetNbinsX();
   double bin[num],sum[num]={0};
   bool Photon_cut[6]={0},LEP=false;
   vector<double> vector_pt;
   vector<double>::iterator biggest_pt;
   Int_t position;
//   Double_t lowpt[num]= {20,25,30,40,50,70,100,120};
//   Double_t highpt[num]={25,30,40,50,70,100,120,400};
   Double_t lowpt[num]= {20};
   Double_t highpt[num]={400};
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
//      if(jentry%2000==0) cout<<jentry<<";"<<nentries<<endl;
      LEP = lep==13 && (HLT_Mu1>0|| HLT_Mu2>0)  && ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110;// && drla>0.7;
      for(Int_t j=0;j<6;j++){
	      if(photon_pt[j]>400) photon_pt[j]=399;
	      Photon_cut[j]= photon_pev[j]==1 && /*photon_pevnew[j]==1 &&*/ photon_hoe[j]<0.02197 && 
		      photon_nhiso[j]<1.189 + 0.01512*photon_pt[j]+0.00002259*photon_pt[j]*photon_pt[j] && 
		      photon_phoiso[j]<2.08 + 0.004017*photon_pt[j]&&
		      fabs(photon_eta[j])<1.4442&&photon_pt[j]>20&&photon_pt[j]<400&&
		      photon_drla[j]>0.7&&photon_drla[j]!=10&&photon_drla2[j]>0.7&&photon_drla2[j]!=10;
          if(Photon_cut[j]&&LEP/*&&(jet_flag==true)*/){
                  vector_pt.push_back(photon_pt[j]);}
          else {vector_pt.push_back(0);}
      }
    biggest_pt = max_element(begin(vector_pt),end(vector_pt));
    if(*biggest_pt==0){
        vector_pt.clear();
        continue;
      }
    position = distance( begin(vector_pt), biggest_pt);
    for(Int_t k=0;k<num;k++){

	    if(photon_chiso[position]<13 && photon_chiso[position]>4 && photon_pt[position]<highpt[k] && photon_pt[position]>lowpt[k]){
		    h1[k]->Fill(photon_chiso[position]);
	    } 
      } 
    vector_pt.clear();
   }
    f1->cd();
    file<<"pt range"<<"\t"<<"total"<<"\t"<<"half"<<"\t"<<"sum"<<"\t"<<"chiso"<<endl;
    for(Int_t k=0;k<num;k++){
	    h1[k]->Write();
	    for(Int_t i=0;i<h1[k]->GetNbinsX();i++){
		    bin[k] = h1[k]->GetBinContent(i+1);
		    sum[k] = sum[k] + bin[k];
		    if(   abs(sum[k]- (h1[k]->GetSumOfWeights()/2) )<5  )  
		    {
			    cout<<lowpt[k]<<"~"<<highpt[k]<<"; the total:"<<h1[k]->GetSumOfWeights()<<"; the half:"<<h1[k]->GetSumOfWeights()/2<<"; sum of the first "<<i+1<<" bin:"<<sum[k]<<"; the chiso value in "<<i+1<<" bin = "<<h1[k]->GetBinCenter(i+1)+0.5*h1[k]->GetBinWidth(i+1)<<endl;
			    file<<lowpt[k]<<"~"<<highpt[k]<<"\t\t"<<h1[k]->GetSumOfWeights()<<"\t"<<h1[k]->GetSumOfWeights()/2<<"\t"<<sum[k]<<"\t"<<h1[k]->GetBinCenter(i+1)+0.5*h1[k]->GetBinWidth(i+1)<<endl;
//		    break;
		    }
	    }
    } 
    f1->Close();
}
