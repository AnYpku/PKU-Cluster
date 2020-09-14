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
   ResetVal();   
//   lowpt[0]=20; 
   histo();
//   style();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   TFile* fout = new TFile("./T-"+name +".root", "RECREATE");
   TTree* ExTree = fChain->CloneTree(0);
   int jet=0;
   double Mchiso = 5.83;
   double chisomax = 8;
   double chisomin = 3;//3~8   
   double actualWeight;
//   nentries = 100000;
//   cout<<"lowpt[0]"<<lowpt[0]<<endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%1000000==0) cout<<jentry<<"; "<<nentries<<endl;
      // if (Cut(ientry) < 0) continue;
      LEP = lep==13 && ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110 && (HLT_Mu2>0||HLT_Mu5>0);
      jet=0;
      for(Int_t j=0;j<6;j++){
          Photon_cut[j]= photon_pevnew[j]==1 &&
		         photon_hoe[j]<0.0219  &&
		         photon_nhiso[j]<1.715 + 0.0163*photon_pt[j] + 0.000014*photon_pt[j]*photon_pt[j] &&
		         photon_phoiso[j]<3.863 + 0.0034*photon_pt[j]&&
		        (fabs(photon_eta[j])<2.5&&fabs(photon_eta[j])>1.566)  &&
		         photon_pt[j]>20&&photon_pt[j]<400 && 
                         photon_drla[j]>0.7 && photon_drla[j]!=10 &&
			 photon_drla2[j]>0.7 && photon_drla2[j]!=10;//muon endcap 
          JET[j] =  ak4jet_pt[j]>30 && fabs(ak4jet_eta[j])<4.7;
	  if(JET[j])  jet++;
          if(Photon_cut[j]&&LEP){
		  vector_pt.push_back(photon_pt[j]);
	  }
          else {vector_pt.push_back(0);}
       }//fill the vector_pt
    size=vector_pt.size();
    biggest_pt = max_element(begin(vector_pt),end(vector_pt));
    if(*biggest_pt==0){
        vector_pt.clear();
        continue;}
    ExTree->Fill();
//    cout<<"the biggest pt"<<*biggest_pt<<endl;
    position = distance( begin(vector_pt), biggest_pt);

      for(Int_t k=0;k<num;k++){
//	      cout<<"lowpt["<<k<<"] "<<lowpt[k]<<endl;
//	      cout<<"highpt["<<k<<"] "<<highpt[k]<<endl;
         if(name.Contains("A")==1){
                 actualWeight  = scalef*prefWeight*pileupWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale*muon1_track_scale*muon2_track_scale;
                 if(photon_isprompt[position]==1 && photon_chiso[position]<0.442 && photon_pt[position]<highpt[k] && photon_pt[position]>lowpt[k]){ 
                          h1[k]->Fill(photon_sieie[position],actualWeight);
                          m1[k] +=actualWeight;
                  }//true
	                if(photon_chiso[position]>chisomin && photon_chiso[position]<chisomax &&
                     photon_pt[position]<highpt[k] &&  photon_pt[position]>lowpt[k] &&
                     photon_isprompt[position]==1 ){
                            h4[k]->Fill(photon_sieie[position],actualWeight);
//                          cout<<"fake contribution from ZA"<<endl;
	                }//fake contribution from true(ZA)
	      }else{
               actualWeight=scalef;
               if(photon_chiso[position]>chisomin && photon_chiso[position]<chisomax && 
                  photon_pt[position]<highpt[k] && photon_pt[position]>lowpt[k]){ 
                     h2[k]->Fill(photon_sieie[position],actualWeight);
                     m2[k] +=actualWeight;
               }//fake

               if(photon_chiso[position]<0.442 && photon_pt[position]<highpt[k] && photon_pt[position]>lowpt[k]){
                     h3[k]->Fill(photon_sieie[position],actualWeight);
                     m3[k] += actualWeight;
               }//data
         }
     }
         vector_pt.clear();
   }
   /*ff = new TFile("./root/Three_template.root","recreate");*/
   for(Int_t i=0;i<num;i++){
       //h3[i]->Write();
       cout<<Form(" %0.f<photonet<%0.f",lowpt[i],highpt[i])<< "  True template m1["<<i<<"] = "<<m1[i]<<endl;
       cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  Fake template m2["<<i<<"] = "<<m2[i]<<endl;
       cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  Data template: "<<"isprompt==1,TrueNumber = "<<TrueNumber[i]<<endl;
       cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  Data template: "<<"isprompt!=1,FakeNumber = "<<FakeNumber[i]<<endl;
       if(name.Contains("A")==1){
           ofstream myfile_true(Form("./txt/truenumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]),ios::out);
           myfile_true<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m1[i]<<"\t"<<TrueNumber[i]<<endl;
         }
      if(name.Contains("outDMuon")==1){   
         ofstream myfile_fake(Form("./txt/fakenumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]),ios::out);
         myfile_fake<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m2[i]<<"\t"<<FakeNumber[i]<<endl;
        }
     } 
   /*ff->Close();
   delete ff;*/
   ExTree->Write();
   fout->Close();

   if(name.Contains("A")==1){
      f1= new TFile("./root/True_template-"+name+".root","recreate");
      for(Int_t i=0;i<num;i++){h1[i]->Write();h4[i]->Write();}
      f1->Close();
      delete f1;
   }
   if(name.Contains("outDMuon")==1){
      f2= new TFile("./root/Fake_template-"+name+".root","recreate");
      for(Int_t i=0;i<num;i++){h2[i]->Write();}
      f2->Close();
      delete f2;
   
      f3 = new TFile("./root/Data_template-"+name+".root","recreate");
      for(Int_t i=0;i<num;i++){h3[i]->Write();}
      f3->Close();
      delete f3;
   }
   /*for(Int_t i=0;i<num;i++){
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
  bin=30;
  xlow= 0.0042;
  xhigh=  0.08163;
  for(Int_t i=0;i<num;i++){
//	  lowpt[0]=20;
//	      cout<<"lowpt["<<i<<"] "<<lowpt[i]<<endl;
         h1[i]=new TH1D(Form("h1_pt%0.f-%0.f",lowpt[i],highpt[i]),"true template",bin,xlow,xhigh);
         h2[i]=new TH1D(Form("h2_pt%0.f-%0.f",lowpt[i],highpt[i]),"fake template",bin,xlow,xhigh);
         h3[i]=new TH1D(Form("h3_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,xlow,xhigh);
         h4[i]=new TH1D(Form("h4_pt%0.f_%0.f",lowpt[i],highpt[i]),"fake contribution from ZA",bin,xlow,xhigh);
     }
}

void MakeTemplate::draw(TCanvas *c,TH1D *h1,TH1D *h2,TH1D *h3,Double_t ptlow,Double_t pthigh){
    c=new TCanvas("c","Zjets and leading photon",900,600);
    c->SetGrid();
   // c->SetLogy();
    h1->SetLineColor(51);
    h1->SetTitle(Form("Barrel Region  %0.f < photon PT <% 0.f",ptlow,pthigh));
    h1->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
    h1->GetYaxis()->SetTitle("count");
    h1->SetLineStyle(1);
    h1->SetLineWidth(3);
    h1->SetFillColor(51);
    h1->SetFillStyle(3002);
    s1=1/h1->Integral();
         cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
         cout<<"s1 = "<<s1<<endl;
         h2->SetLineColor(2);
   // h1->Scale(s1);
    h2->SetLineStyle(2);
    h2->SetLineWidth(3);
    s2=1/h2->Integral();
    cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
             cout<<"  s2 = "<<s2<<endl;
       // h2[i]->Draw("HIST,SAME");
       // h2->Scale(s2);
   //   }
    h3->SetLineStyle(3);
    Int_t ci=ci = TColor::GetColor("#3399ff");
    h3->SetLineColor(ci);
    h3->SetFillColor(ci);
    h3->SetFillStyle(3008);
    h3->SetLineWidth(3);
    s3=1/h3->Integral();
         cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
         cout<<"s3 = "<<s3<<endl;
   // h3->Scale(s3);
   // h1->DrawNormalized("HIST");
   // h2->DrawNormalized("HIST,SAME");
   // h3->DrawNormalized("HIST,SAME");
    h1->Draw("HIST");
    h2->Draw("HIST,SAME");
    h3->Draw("HIST,SAME");
    TLegend *l1 = new TLegend(0.5,0.6,0.9,0.9);
    l1->AddEntry(h1,"true template" );
    l1->AddEntry(h2,"Fake #gamma" );
    l1->AddEntry(h3,"data template");
    l1->Draw();
    delete c;
    delete h1;
    delete h2;
    delete h3;
}
void MakeTemplate::ResetVal(){
//	lowpt[num]= {20,25,30,35,40,50,65,100};
//	highpt[num]={25,30,35,40,50,65,100,400};
   bin=30;
   xlow= 0.0042;
   xhigh=  0.08163;

   for(Int_t i=0;i<9;i++){
      m1[i]=0;
      m2[i]=0;
      m3[i]=0;
      TrueNumber[i]=0;
      FakeNumber[i]=0;
     }
   position=0,size=0,m=0;
} 
