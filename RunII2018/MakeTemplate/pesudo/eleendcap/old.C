#include <iostream>
#include <ostream>
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
#include <algorithm>
#include <vector>
using namespace std;

TString rootfiles = "pesudo";
TString sieiecut = "nosieiecut_barrel";
//TString sieiecut = "sieiecut";
TString dir = "./txt/";
TString dir1 = "./root/";
Double_t chiso = 1.141;
//Double_t chiso = 0.442;
Double_t sieie = 0.01022;
//Double_t sieie = 0.03001;
void style();
void histo();
void select(TTree *tree,TH1D *h1[7],TH1D *h2[7][21],TH1D *h3[7]);
void draw(TCanvas *c,TH1D *h1,TH1D *h2,TH1D *h3,Double_t ptlow,Double_t pthigh);
void creatfiles();
 //the needed variables in the root file
 Double_t ptlep1,ptlep2,etalep1,etalep2,massVlep;
 Double_t scalef;
 Int_t nlooseeles,nloosemus;
 Bool_t photon_pev[6];
 Double_t photon_drla[6],photon_pt[6],photon_drla2[6],photon_sieie[6],photon_chiso[6];
 double photon_hoe[6];
 double photon_nhiso[6];
 double photon_phoiso[6];
 double photon_eta[6];
 int photon_isprompt[6];
 bool LEP,Leading_photon[6],medium_cut[6],loose_cut[6];
 vector<double> vector_pt;
 vector<double>::iterator biggest_pt;
 Int_t position=0,size,m=0;
 Double_t m1[7],m2[7][21],m3[7];
 Int_t nentries;
 Double_t lowchiso[21],highchiso[21];
 Double_t TrueNumber[7],FakeNumber[7];
 Double_t lowpt[7] ={25,30,35,40,50,65,100};
 Double_t highpt[7]={30,35,40,50,65,100,400};
 TH1D* h11[7];
 TH1D* h21[7];
 TH1D* h12[7][21];
 TH1D* h22[7][21];
 TH1D* h13[7];
 TH1D* h23[7];
 TH1D* h_sieie[7];
 TH1D* hfake[7];
 TH1D* htrue[7];
 TH1D* h31;
 TH1D* h32;
 TH1D* h33;
// TCanvas *c1;
// TFile *f1;
// TFile *f2;
// TTree *t1;
// TTree *t2;

void style(){
 gStyle->SetOptStat(0);
 gStyle->SetPadGridX(1);
 gStyle->SetPadGridY(1);
 gStyle->SetPadTickX(1);
 gStyle->SetPadTickY(1);
 gStyle->SetAxisColor(1, "XYZ");
 gStyle->SetStripDecimals(kTRUE);
 gStyle->SetTickLength(0.03, "XYZ");
 }
void histo(){
 Int_t bin=20;
 Double_t xlow= 0.00;
 Double_t xhigh= 0.02;
  for(Int_t i=0;i<7;i++){
      h_sieie[i]=new TH1D(Form("hsieie_pt%0.f-%0.f",lowpt[i],highpt[i]),"chiso<1.141 and sieie<0.01022",bin,0,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      hfake[i]=new TH1D(Form("hfake_pt%0.f-%0.f",lowpt[i],highpt[i]),"chiso<1.141 isprompt!=1",bin,0,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      htrue[i]=new TH1D(Form("htrue_pt%0.f-%0.f",lowpt[i],highpt[i]),"chiso<1.141 isprompt=1",bin,0,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      h11[i]=new TH1D(Form("h11_pt%0.f-%0.f",lowpt[i],highpt[i]),"chiso<1.141",bin,0,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      h21[i]=new TH1D(Form("h21_pt%0.f-%0.f",lowpt[i],highpt[i]),"chiso<1.141",bin,0,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      h23[i]=new TH1D(Form("h23_pt%0.f-%0.f",lowpt[i],highpt[i]),"chiso<1.141 photon_isprompt=1",bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
      h13[i]=new TH1D(Form("h13_pt%0.f-%0.f",lowpt[i],highpt[i]),"chiso<1.141",bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
    for(Int_t j=0;j<21;j++){  
         h12[i][j]=new TH1D(Form("h12_pt%0.f-%0.f_chiso%0.f-%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j]),Form("%0.f>chiso>%0.f",highchiso[j],lowchiso[j]),bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
         h22[i][j]=new TH1D(Form("h22_pt%0.f-%0.f_chiso%0.f-%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j]),Form("%0.f>chiso>%0.f",highchiso[j],lowchiso[j]),bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
       }
  }  
  h31=new TH1D("h31","10>chiso>4",bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
  h32=new TH1D("h32","",bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
  h33=new TH1D("h33","",bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
}

void select(TTree *tree,TH1D *h1[7],TH1D *h2[7][21],TH1D *h3[7]){
 tree->SetBranchAddress("photon_hoe",photon_hoe);
 tree->SetBranchAddress("photon_pev",photon_pev);
 tree->SetBranchAddress("photon_nhiso",photon_nhiso);
 tree->SetBranchAddress("photon_phoiso",photon_phoiso);
 tree->SetBranchAddress("photon_pt",photon_pt);
 tree->SetBranchAddress("photon_eta",photon_eta);
 tree->SetBranchAddress("scalef",&scalef);
 tree->SetBranchAddress("nloosemus",&nloosemus);
 tree->SetBranchAddress("nlooseeles",&nlooseeles);
 tree->SetBranchAddress("ptlep1",&ptlep1);
 tree->SetBranchAddress("ptlep2",&ptlep2);
 tree->SetBranchAddress("etalep1",&etalep1);
 tree->SetBranchAddress("etalep2",&etalep2);
 tree->SetBranchAddress("massVlep",&massVlep);
 tree->SetBranchAddress("photon_isprompt",photon_isprompt);
 tree->SetBranchAddress("photon_drla",photon_drla);
 tree->SetBranchAddress("photon_drla2",photon_drla2);
 tree->SetBranchAddress("photon_sieie",photon_sieie);
 tree->SetBranchAddress("photon_chiso",photon_chiso);
 tree->SetBranchAddress("photon_pt",photon_pt);
 nentries = tree->GetEntries();
// cout<<"nentries = "<<nentries<<endl;
// nentries=100000;
 for(Int_t i=0;i<7;i++)
   { m1[i]=0;m3[i]=0;TrueNumber[i]=0;FakeNumber[i]=0;
     for(Int_t j=0;j<21;j++){m2[i][j]=0;}
   }
 for(Int_t i=0;i<nentries;i++){
    tree->GetEntry(i);
    for(Int_t k=0;k<6;k++){if(photon_drla[k]==10) photon_drla[k]=0;if(photon_drla2[k]==10) photon_drla2[k]=0; }
    LEP = ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110;
    for(Int_t j=0;j<6;j++){
         Leading_photon[j]= photon_drla[j]>0.7 && photon_drla2[j]>0.7;
	 medium_cut[j]=  photon_pev[j]==1 &&
                           photon_hoe[j]<0.0396 && 
                           photon_nhiso[j]<2.725 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j] &&
                           photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&
                           fabs(photon_eta[j])<1.4442 &&
                           photon_pt[j]>25 &&photon_pt[j]<400;//muon Barrel

         if(LEP&&Leading_photon[j]&&medium_cut[j]){
            /*cout<<"OK"<<endl;*/vector_pt.push_back(photon_pt[j]);}
         else {vector_pt.push_back(0);}
      }//fill the vector_pt
   size=vector_pt.size();
   biggest_pt = max_element(begin(vector_pt),end(vector_pt));
   position = distance( begin(vector_pt), biggest_pt);
   if(*biggest_pt==0){
       vector_pt.clear();
       continue;}
//   cout<<"the biggest pt"<<*biggest_pt<<endl;
   for(Int_t k=0;k<7;k++){
       if(photon_chiso[position]< chiso && *biggest_pt<highpt[k] && *biggest_pt>lowpt[k]) 
            {h1[k]->Fill(photon_sieie[position],scalef);m1[k] += scalef;
              if(photon_sieie[position]< sieie && photon_isprompt[position]!=1)  {FakeNumber[k]+=scalef;}
	      if(photon_isprompt[position]!=1)
		      hfake[k]->Fill(photon_sieie[position],scalef);
	      if(photon_isprompt[position]==1)
		      htrue[k]->Fill(photon_sieie[position],scalef);
              if(photon_isprompt[position]==1 && photon_sieie[position]< sieie )  TrueNumber[k]+=scalef;
              if(photon_sieie[position]< sieie) h_sieie[k]->Fill(photon_sieie[position],scalef);
               }//datamc
       for(Int_t j=0;j<21;j++){
             if(photon_chiso[position]>lowchiso[j]&&photon_chiso[position]<highchiso[j]&&*biggest_pt<highpt[k] && *biggest_pt>lowpt[k]) 
                 { 
                  h2[k][j]->Fill(photon_sieie[position],scalef);m2[k][j] +=scalef;
                 }  
             }//fake
       if(photon_isprompt[position]==1&&photon_chiso[position]< chiso &&*biggest_pt<highpt[k] && *biggest_pt>lowpt[k]) 
          {h3[k]->Fill(photon_sieie[position],scalef);m3[k] +=scalef;}//real
   }
   vector_pt.clear();
//   cout<<"i "<<i<<" size "<<size<<endl;
   }  
// cout<<"the number of gamma in mix = m1 = "<<m1<<endl;
// cout<<"the number of fake gamma in ZJ = m2 = "<<m2<<endl;
// cout<<"the number of real gamma in Za = m3 = "<<m3<<endl;
// cout<<"nentries = "<<nentries<<endl;
}

void draw(TCanvas *c,TH1D *h1,TH1D *h2,TH1D *h3,Double_t ptlow,Double_t pthigh){
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
 Double_t s1=1/h1->Integral();
      cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
      cout<<"s1 = "<<s1<<endl;
      h2->SetLineColor(2);
// h1->Scale(s1);
 Double_t s2;
 h2->SetLineStyle(2);
 h2->SetLineWidth(3);
 s2=1/h2->Integral();
 cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
 for(Int_t i=0;i<21;i++){
          cout<<Form(" %0.f<photon_chiso<%0.f ",lowchiso[i],highchiso[i]);
          cout<<"  s2 = "<<s2<<endl;}
    // h2[i]->Draw("HIST,SAME");
    // h2->Scale(s2);
//   }
 h3->SetLineStyle(3);
 Int_t ci=ci = TColor::GetColor("#3399ff");
 h3->SetLineColor(ci);
 h3->SetFillColor(ci);
 h3->SetFillStyle(3008);
 h3->SetLineWidth(3);
 Double_t s3=1/h3->Integral();
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
 l1->AddEntry(h1,"photon_chiso<1.141 datamc #gamma" );
 l1->AddEntry(h2,Form("%0d<photon_chiso<%0d  Fake #gamma",4,10) );
 l1->AddEntry(h3,"photon_chiso<1.141 Real #gamma"); 
 l1->Draw(); 
 //c->Print("./"+plot+Form("_sieiept%0.f_%0.f.eps",ptlow,pthigh));
 delete c;
}
int main(){
for(Int_t j=0;j<21;j++){
     if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
     if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
     if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;} 
     if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;} 
     if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;} 
     if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
//     if(highchiso[j]>10&&highchiso[j]<13) {highchiso[j]=10;}
//     if(highchiso[j]==13)                 {highchiso[j]=12;}
//     if(lowchiso[j]==7||lowchiso[j]==8)   {lowchiso[j]=4;}
//     if(lowchiso[j]==9)                   {lowchiso[j]=6;}
//     if(lowchiso[j]==10)                  {lowchiso[j]=8;}
//     if(lowchiso[j]==11)                  {lowchiso[j]=5;}
   }
style();
histo();
TFile *f1 = new TFile("/home/pku/anying/cms/file_in_cms/2018RunIIrootfiles/"+rootfiles+".root");     
TFile *ff1[7][21];
TTree *t1 =(TTree*)f1->Get("demo");
Double_t cnt = t1->GetEntries();
cout<<" entries = "<<cnt<<endl;
cout<<"file " + rootfiles + ".root"<<endl;
select(t1,h11,h12,h13);
for(Int_t i=0;i<7;i++){
    cout<<"pt range "<<lowpt[i]<<" ~ "<<highpt[i]<<endl;
    ofstream myfile1(Form(dir + sieiecut+"datanumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
    cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i]);
    cout<<"the number  m1 is in pesudo data = ";
    cout<<" "<<m1[i]<<endl;
    myfile1<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m1[i]<<endl;

    for(Int_t j=0;j<21;j++){
	    ff1[i][j]= new TFile(Form(dir1 + rootfiles+"_fake_pt%0.f-%0.f_chiso%0.f-%0.f.root",lowpt[i],highpt[i],lowchiso[j],highchiso[j]),"recreate");
	    h12[i][j]->Write();
	    h_sieie[i]->Write();
	    hfake[i]->Write();
	    htrue[i]->Write();
	    h11[i]->Write();
//       cout<<Form(" %0.f<pt<%0.f , %0.f<photon_chiso<%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j])<<"the number  m2 is the number of fake photon in fake template = "<<m2[i][j]<<endl;
	    cout<<Form(" %0.f<pt<%0.f , %0.f<photon_chiso<%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j])<<"the FakeNumber is the number of fake photon in pesudo data = "<<FakeNumber[i]<<endl;
	    ofstream myfile_fake(Form(dir + sieiecut+"mfakenumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt[i],highpt[i],lowchiso[j],highchiso[j]));
	    myfile_fake<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<lowchiso[j]<<"\t"<<highchiso[j]<<"\t"<<FakeNumber[i]<<"\t"<<m2[i][j]<<endl;
    }
} 
//cout<<"succeed to fill histo h11 and h12"<<endl;
cout<<"#####################################"<<endl;
for(Int_t i=0;i<7;i++){
   for(Int_t j=0;j<21;j++){
        ff1[i][j]->Close();}
 }
f1->Close();
TFile *f2 = new TFile("/home/pku/anying/cms/file_in_cms/2018RunIIrootfiles/cutlep-outZA.root");     

TFile *ff2[21];
TTree *t2 =(TTree*)f2->Get("demo");
cout<<"file za sample"<<endl;
select(t2,h21,h22,h23);
for(Int_t i=0;i<7;i++){
 cout<<"pt range "<<lowpt[i]<<" ~ "<<highpt[i]<<endl;
ofstream myfile(Form(dir + sieiecut+"truenumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
 ff2[i]   = new TFile(Form(dir1 + rootfiles+"_photonreal_pt%0.f_%0.f.root",lowpt[i],highpt[i]),"recreate");
// cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  the number m3 is the number of real photon in the true template = "<<m3[i]<<endl;
 cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  the TrueNumber is the number of real photons in pesudo data "<<TrueNumber[i]<<endl;
 h23[i]->Write();
 myfile<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m3[i]<<"\t"<<TrueNumber[i]<<endl;
 }
cout<<"#####################################"<<endl;
for(Int_t i=0;i<21;i++){
   ff2[i]->Close();}
f2->Close();
//TFile *f3 = new TFile("../rootfiles/outZJets_FX.root");     
//TFile *ff3= new TFile(Form("photonfakept%0.f_%0.f.root",lowpt,highpt),"recreate");
//TTree *t3 =(TTree*)f1->Get("demo");
//cout<<"pt range "<<lowpt<<" ~ "<<highpt<<endl;
//select(t3,h31,h32,h33,lowpt,highpt);
//cout<<"the number  m2 is fake photon "<<endl;
/*TCanvas *c1[7];
for(Int_t i=0;i<7;i++){
c1[i]=new TCanvas(Form("pt%0.f-%0.f",lowpt[i],highpt[i]),"mediumID selection",900,600);   
   draw(c1[i],h11[i],h12[i][6],h23[i],lowpt[i],highpt[i]);
   cout<<"######################################finish######################################"<<endl;
}*/

return 0;
//delete c1;
//for(Int_t i=0;i<10;i++){
//  delete h11[i];
//  delete h21[i];
//  delete h13[i];
//  delete h23[i];}
//
//for(Int_t i=0;i<10;i++){
//  for(Int_t j=0;j<10;i++){
//   delete h12[i][j];
//   delete h22[i][j];
//  }
// } 
//delete h31;
//delete h32;
//delete h33;
}

