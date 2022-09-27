#define MakeTemplate_cxx
#include "MakeTemplate.h"
#include <TH2.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include "L1_weight.C"
//#include <fiostream>
using namespace std;
void MakeTemplate::Loop(TString name)
{
//   In a ROOT session, you can do:
//      root> .L MakeTemplate.C
//      root> MakeTemplate t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   histo();
   ResetVal();   
   style();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   double lep1_phi_station2_tmp; 
   double lep2_phi_station2_tmp; 
//   nentries = 1000000;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%1000000==0) cout<<jentry<<"; "<<nentries<<endl;
      actualWeight = scalef * lumiWeight * pileupWeight*35.862*0.96;
      // if (Cut(ientry) < 0) continue;
      lep1_phi_station2_tmp = lep1_phi_station2;
      lep2_phi_station2_tmp = lep2_phi_station2;
      l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
      LEP = lep==13 && ptlep1 >20. && ptlep2 >20.&& abs(etalep1) <2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && ((run_period<7 && HLT_Mu5 > 0)|| (run_period==7 && HLT_Mu2 > 0));
      if(LEP==false) continue;
      for(Int_t j=0;j<6;j++){
         if(name.Contains("outZA")==1)
           {Photon_cut[j]= /*photon_pev[j]==1*/ photon_pevnew[j]==1 && 
                           photon_hoe[j]<0.0396 && 
                           photon_chiso[j]<0.441 && 
                           photon_nhiso[j]<2.725 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j] && 
                           photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&
                           fabs(photon_eta[j])<1.4442 && 
                           photon_isprompt[j]==1;
	   }
    
         if(name.Contains("outZJets")==1)
           {Photon_cut[j]= /*photon_pev[j]==1*/ photon_pevnew[j]==1 && 
                           photon_hoe[j]<0.0396 && 
                           photon_chiso[j]<0.441 &&
                           photon_nhiso[j]<2.725 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j] &&
                           photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&
                           fabs(photon_eta[j])<1.4442 && 
                           photon_isprompt[j]==-1 && 
                           photon_pt[j]>10;
	   } 

         if(name.Contains("outDMuon")==1)
           {Photon_cut[j]= /*photon_pev[j]==1*/ photon_pevnew[j]==1 && 
                           photon_hoe[j]<0.0396  &&
                           photon_chiso[j]<0.441 && 
                           photon_nhiso[j]<2.725 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j] &&
                           photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&
                           fabs(photon_eta[j])<1.4442&&
                           photon_pt[j]>10;
	   } 
/*&&photon_sieie[j]<0.0102&&photon_sieie[j]>0.0052;*/

          if(Photon_cut[j]){
             vector_pt.push_back(photon_pt[j]);}
          else {vector_pt.push_back(0);}
       }//fill the vector_pt
    size=vector_pt.size();
    biggest_pt = max_element(begin(vector_pt),end(vector_pt));
    if(*biggest_pt==0){
        vector_pt.clear();
        continue;}
    position = distance( begin(vector_pt), biggest_pt);
    if(jentry%10000==0) cout<<jentry<<"; the biggest pt = "<<*biggest_pt<<"; the position = "<<position<<endl;

      for(Int_t k=0;k<ptnumber;k++){
         if(name.Contains("outZA")==1){
            if(photon_drla[position]>1 && photon_drla[position]<10 && 
               photon_drla2[position]>1&& photon_drla2[position]<10&&
               massVlep>80 && massVlep<100)
	    {
                  newtree->Fill();
	          if(photon_pt[position]>lowpt[k] && photon_pt[position]<highpt[k])
                    {h1[k]->Fill(photon_sieie[position],actualWeight);f++;}
	    }//fake
	 }
         if(name.Contains("outZJets")==1){
            if(photon_drla[position]>0.4 && photon_drla2[position]>0.4&& 
               TMath::Min(photon_drla[position],photon_drla2[position])<1 &&
               massVlep<80 &&
               Mva>81 && Mva<101 &&
	       photon_pt[position]>10/*&&
	       photon_pt[position]>lowpt[k] && photon_pt[position]<highpt[k]*/)
	    { 
		      newtree->Fill();
		      h2[k]->Fill(photon_sieie[position],actualWeight);t++;
	    }//true
	 }
         if(name.Contains("outDMuon")==1){
            if(photon_drla[position]>1 && photon_drla2[position]>1 &&
               photon_drla[position]<10 && photon_drla2[position]<10 &&
               massVlep>80 && massVlep<100)
	    {
		    newtree->Fill();
		    if(photon_pt[position]>lowpt[k]&& photon_pt[position]<highpt[k])
		      {h3[k]->Fill(photon_sieie[position]);df++;}//data fake
	    }
            if(photon_drla[position]>0.4 && photon_drla2[position]>0.4 &&
               TMath::Min(photon_drla[position],photon_drla2[position])<1&&
               massVlep<80 &&
               Mva>81 && Mva<101 && photon_pt[position]>10/*&&
	       photon_pt[position]>lowpt[k] && photon_pt[position]<highpt[k]*/)
	    {
			 newtree->Fill();
			 h4[k]->Fill(photon_sieie[position]);dt++;
	    }//data true
	 }
         if(name.Contains("end")) continue; 
       }
         vector_pt.clear();
   }
  if(name.Contains("ZA")==1)        cout<<"mc fake "<<f<<endl;
  if(name.Contains("ZJets")==1)     cout<<"mc true "<<t<<endl;
  if(name.Contains("outDMuon")==1)  cout<<"data fake "<<df<<endl;
  if(name.Contains("outDMuon")==1)  cout<<"data true "<<dt<<endl;

   if(name.Contains("outZA")){
       f1 = new TFile("./mcFake_template.root","recreate");
       f1->cd();
       for(Int_t i=0;i<ptnumber;i++){h1[i]->Write();}
       file1++;
       cout<<"number of "<<name<<" file:"<<file1<<endl;
     }
   if(name.Contains("outDMuon")){
       f3 = new TFile("./dataFake_template.root","recreate");
       f4 = new TFile("./dataTrue_template.root","recreate");
       f3->cd();
       for(Int_t i=0;i<ptnumber;i++){h3[i]->Write();}
       f4->cd();
       for(Int_t i=0;i<ptnumber;i++){h4[i]->Write();}
       file2++;
       cout<<"number of "<<name<<" file:"<<file2<<endl;
     }
   if(name.Contains("outZJets")){
       f2 = new TFile("./mcTrue_template.root","recreate");
       f2->cd();
       for(Int_t i=0;i<ptnumber;i++){h2[i]->Write();}
       file3++;
       cout<<"number of "<<name<<" file:"<<file3<<endl;
      }
      /*f3 = new TFile("./root/Data_template-"+name+".root","recreate");
      for(Int_t i=0;i<9;i++){h3[i]->Write();}
      f3->Close();
      delete f3;*/
  /* if(name.Contains("end")) {
      cout<<"OK2"<<endl;
      f1->Close();       
      f2->Close();       
      cout<<"OK3"<<endl;
      f3->Close();       
      f4->Close();       
      //delete f1;delete f2;
      cout<<"OK4"<<endl;
      //delete f3;delete f4;
      }*/
   /*for(Int_t i=0;i<9;i++){
     c1[i]=new TCanvas(Form("pt%0.f-%0.f",lowpt[i],highpt[i]),"mediumID selection",900,600);
     draw(c1[i],h1[i],h2[i],h3[i],lowpt[i],highpt[i]);
     cout<<"######################################finish######################################"<<endl;
     c1[i]->Print(Form("./eps/"+name+"photon_sieiept%0.f_%0.f.eps",lowpt[i],highpt[i]));
   }*/
}
void MakeTemplate::style(){
 gStyle->SetOptStat(0);
 gStyle->SetPadGridX(1);
 gStyle->SetPadGridY(1);
 gStyle->SetPadTickX(1);
 gStyle->SetPadTickY(1);
 gStyle->SetAxisColor(1, "XYZ");
 gStyle->SetStripDecimals(kTRUE);
 gStyle->SetTickLength(0.03, "XYZ");
 }

void MakeTemplate::histo(){
  bin=20;
  xlow= 0.;
  xhigh= 0.02;
  for(Int_t i=0;i<ptnumber;i++){
      h2[i]=new TH1D(Form("h2_pt%0.f-%0.f",lowpt[i],highpt[i]),"true template",bin,0,xhigh);
      h1[i]=new TH1D(Form("h1_pt%0.f-%0.f",lowpt[i],highpt[i]),"fake template",bin,0,xhigh);
      h3[i]=new TH1D(Form("h3_pt%0.f-%0.f",lowpt[i],highpt[i]),"data fake template",bin,0,xhigh);
      h4[i]=new TH1D(Form("h4_pt%0.f-%0.f",lowpt[i],highpt[i]),"data true template",bin,0,xhigh);
  }
}

void MakeTemplate::draw(TCanvas *c,TH1D *h1,TH1D *h2,TH1D *h3,TH1D *h4,Double_t ptlow,Double_t pthigh){
    c=new TCanvas("c","Zjets and leading photon",900,600);
    c->SetGrid();
    h1->SetLineColor(51);
    h1->SetTitle(Form("Barrel Region  %0.f < photon PT <% 0.f",ptlow,pthigh));
    h1->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
    h1->GetYaxis()->SetTitle("count");
    h1->SetLineStyle(1);
    h1->SetLineWidth(3);
    h1->SetFillColor(51);
    h1->SetFillStyle(3002);
    h2->SetLineColor(2);
    h2->SetLineStyle(2);
    h2->SetLineWidth(3);
    Int_t ci=ci = TColor::GetColor("#3399ff");
    h3->SetLineStyle(3);
    h3->SetLineColor(ci);
    h3->SetFillColor(ci);
    h3->SetFillStyle(3008);
    h3->SetLineWidth(3);
    h4->SetLineStyle(3);
    h4->SetLineColor(6);
    h4->SetFillColor(6);
    h4->SetFillStyle(3008);
    h4->SetLineWidth(3);
   // h1->DrawNormalized("HIST");
   // h2->DrawNormalized("HIST,SAME");
   // h3->DrawNormalized("HIST,SAME");
   // h4->DrawNormalized("HIST,SAME");
    h1->Draw("HIST");
    h2->Draw("HIST,SAME");
    h3->Draw("HIST,SAME");
    h4->Draw("HIST,SAME");
    TLegend *l1 = new TLegend(0.5,0.6,0.9,0.9);
    l1->AddEntry(h1,"fake MC" );
    l1->AddEntry(h2,"true MC" );
    l1->AddEntry(h3,"data fake");
    l1->AddEntry(h4,"data true");
    l1->Draw();
    delete c;
    delete h1;
    delete h2;
    delete h3;
    delete h4;
}
void MakeTemplate::ResetVal(){

   position=0,size=0,m=0;
   actualWeight=0;
   f=0;
   t=0; 
   p=0; 
   df=0;
   dt=0;
   file1=0;
   file2=0;
   file3=0;
} 
/*void MakeTemplate::Del(TFile* f1, TFile*f2){
delete f1;
delete f2;
}*/
