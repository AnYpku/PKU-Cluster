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
#define ptnumber 5
#define Pi 3.1415926
using namespace std;

TString rootfiles = "ptotal";
TString sieiecut = "nosieiecut_muendcap";
//TString sieiecut = "sieiecut";
TString dir = "./txt/";
TString dir1 = "./root/";
Double_t chiso = 1.051;
//Double_t chiso = 0.442;
Double_t sieie = 0.0272;
//Double_t sieie = 0.03001;
void style();
void histo();
void select(TTree *tree,TH1D *h1[ptnumber],TH1D *h2[ptnumber][21],TH1D *h3[ptnumber]);
void draw(TCanvas *c,TH1D *h1,TH1D *h2,TH1D *h3,Double_t ptlow,Double_t pthigh);
void creatfiles();
double delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
 //the needed variables in the root file
 Double_t ptlep1,ptlep2,etalep1,etalep2,massVlep;
 Double_t scalef;
 Int_t nlooseeles,nloosemus,HLT_Mu1,HLT_Mu2,ngoodmus;//,ngoodeles;
 Bool_t photon_pev[6],ewk=false,tta=false,za=false;
 Double_t photon_drla[6],photon_pt[6],photon_drla2[6],photon_sieie[6],photon_chiso[6],ak4jet_pt[6],ak4jet_eta[6],ak4jet_phi[6];
 double photon_hoe[6];
 double photon_nhiso[6];
 double photon_phoiso[6];
 double photon_eta[6],photon_phi[6];
 int photon_isprompt[6],lep,isprompt;
 bool LEP,Leading_photon[6],medium_cut[6],loose_cut[6],JET[6],jet_flag;
 vector<double> vector_pt;
 vector<double>::iterator biggest_pt;
 Int_t position=0,size,m=0,jet;
 Double_t m1[ptnumber],m2[ptnumber],m3[ptnumber];
 Int_t nentries;
 Double_t lowchiso[21],highchiso[21];
 Double_t TrueNumber[ptnumber],FakeNumber[ptnumber];
// Double_t lowpt[ptnumber]= {20,30,40,60,80,120};
// Double_t highpt[ptnumber]={30,40,60,80,120,400};
// Double_t lowpt[ptnumber] ={20,25,30,35,40,45,50,60,80,120};
// Double_t highpt[ptnumber]={25,30,35,40,45,50,60,80,120,400};
Double_t lowpt[ptnumber] ={20,25,30,40,60};
Double_t highpt[ptnumber]={25,30,40,60,400};
 TH1D* h11[ptnumber];
 TH1D* h21[ptnumber];
 TH1D* h12[ptnumber][21];
 TH1D* h22[ptnumber][21];
 TH1D* h13[ptnumber];
 TH1D* h23[ptnumber];
 TH1D* h_sieie[ptnumber];
 TH1D* hfake[ptnumber];
 TH1D* htrue[ptnumber];
 TH1D* h31;
 TH1D* h32;
 TH1D* h33;

void select(TTree *tree,TH1D *h1[ptnumber],TH1D *h2[ptnumber][21],TH1D *h3[ptnumber]){
 tree->SetBranchAddress("photon_hoe",photon_hoe);
 tree->SetBranchAddress("photon_pev",photon_pev);
 tree->SetBranchAddress("photon_nhiso",photon_nhiso);
 tree->SetBranchAddress("photon_phoiso",photon_phoiso);
 tree->SetBranchAddress("photon_pt",photon_pt);
 tree->SetBranchAddress("photon_eta",photon_eta);
 tree->SetBranchAddress("photon_phi",photon_phi);
 tree->SetBranchAddress("scalef",&scalef);
 tree->SetBranchAddress("lep",&lep);
 tree->SetBranchAddress("nloosemus",&nloosemus);
 tree->SetBranchAddress("nlooseeles",&nlooseeles);
 tree->SetBranchAddress("ngoodmus",&ngoodmus);
// tree->SetBranchAddress("ngoodeles",&ngoodeles);
 tree->SetBranchAddress("HLT_Mu2",&HLT_Mu2);
 tree->SetBranchAddress("HLT_Mu1",&HLT_Mu1);
 tree->SetBranchAddress("ptlep1",&ptlep1);
 tree->SetBranchAddress("ptlep2",&ptlep2);
 tree->SetBranchAddress("etalep1",&etalep1);
 tree->SetBranchAddress("etalep2",&etalep2);
 tree->SetBranchAddress("massVlep",&massVlep);
 tree->SetBranchAddress("photon_isprompt",photon_isprompt);
 tree->SetBranchAddress("isprompt",&isprompt);
 tree->SetBranchAddress("photon_drla",photon_drla);
 tree->SetBranchAddress("photon_drla2",photon_drla2);
 tree->SetBranchAddress("photon_sieie",photon_sieie);
 tree->SetBranchAddress("photon_chiso",photon_chiso);
 tree->SetBranchAddress("photon_pt",photon_pt);
 tree->SetBranchAddress("ak4jet_pt",ak4jet_pt);
 tree->SetBranchAddress("ak4jet_eta",ak4jet_eta);
 tree->SetBranchAddress("ak4jet_phi",ak4jet_phi);
 nentries = tree->GetEntries();
// cout<<"nentries = "<<nentries<<endl;
// nentries=100000;
 for(Int_t i=0;i<ptnumber;i++)
   { m1[i]=0;m3[i]=0;TrueNumber[i]=0;FakeNumber[i]=0;m2[i]=0;
   }
 TFile* fT = new TFile("./"+rootfiles+".root","recreate");
 TTree* newtree = tree->CloneTree(0);
 for(Int_t i=0;i<nentries;i++){
    tree->GetEntry(i);
    LEP = lep==13&& (HLT_Mu1>0 || HLT_Mu2>0) && ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110 && ngoodmus>1;
    jet=0;
    Int_t jetindexphoton12[2] = {-1,-1};
    for(Int_t j=0;j<6;j++){
	    double drtmp1=delta_R(ak4jet_eta[j], ak4jet_phi[j], photon_eta[j],photon_phi[j]);
	    if(ak4jet_pt[j]>30 && fabs(ak4jet_eta[j])<4.7 && drtmp1>0.5 && jetindexphoton12[0]==-1&&jetindexphoton12[1]==-1) {
		    jetindexphoton12[0] = j;
		    continue;
	    }
	    if(ak4jet_pt[j]>30 && fabs(ak4jet_eta[j])<4.7  && drtmp1>0.5 && jetindexphoton12[0]!=-1&&jetindexphoton12[1]==-1) {
		    jetindexphoton12[1] = j;
		    continue;
	    }
    }
    if(jetindexphoton12[0]>-1 && jetindexphoton12[1]>-1)  { jet_flag=true;}
    else {jet_flag=false;}
    for(Int_t k=0;k<6;k++){if(photon_drla[k]==10) photon_drla[k]=0;if(photon_drla2[k]==10) photon_drla2[k]=0; }
    for(Int_t j=0;j<6;j++){
         Leading_photon[j]= photon_drla[j]>0.7 && photon_drla2[j]>0.7&&photon_drla[j]<9.&&photon_drla2[j]<9.;
	 medium_cut[j]= photon_pev[j]==1 /* photon_pevnew[j]==1*/ && photon_hoe[j]<0.0326 
                     && photon_nhiso[j]<2.718 + 0.0117*photon_pt[j] + 0.000023*photon_pt[j]*photon_pt[j] 
                     && photon_phoiso[j]<3.867 + 0.0037*photon_pt[j]
                     && ( fabs(photon_eta[j])<2.5&&fabs(photon_eta[j])>1.566 )  
                     && photon_pt[j]>20&&photon_pt[j]<400;
	//Muon Endcap		 
	 JET[j] =  ak4jet_pt[j]>30 && fabs(ak4jet_eta[j])<4.7;

	 if(LEP&&Leading_photon[j]&&medium_cut[j] /*&& (jet_flag==true)*/ ){
		 /*cout<<"OK"<<endl;*/vector_pt.push_back(photon_pt[j]);}
	 else {vector_pt.push_back(0);}
    }//fill the vector_pt
    size=vector_pt.size();
    biggest_pt = max_element(begin(vector_pt),end(vector_pt));
    position = distance( begin(vector_pt), biggest_pt);
    if(*biggest_pt==0){
	    vector_pt.clear();
	    continue;}
    newtree->Fill();
    za = false;
    if(fabs(scalef)<0.0065&&fabs(scalef)>0.0064)  za=true;
    //   cout<<"the biggest pt"<<*biggest_pt<<endl;
    for(Int_t k=0;k<ptnumber;k++){
	    if(photon_chiso[position]< chiso && *biggest_pt<highpt[k] && *biggest_pt>lowpt[k]) 
            {
		   if( (photon_isprompt[position]!=1 && isprompt!=1 && (za==false)) ||
                       (photon_isprompt[position]==1 && isprompt ==1 && (za==true))  ){ 
			   h1[k]->Fill(photon_sieie[position],scalef);}//data template
		    m2[k]+=scalef;
                    if(photon_sieie[position]< sieie){ 
			    m1[k] += scalef;}// the number of data in medium sieie region
		    if(photon_sieie[position]< sieie && photon_isprompt[position]!=1 && isprompt!=1 && (za==false)){
			    FakeNumber[k]+=scalef;}
		    if(photon_sieie[position]< sieie && photon_isprompt[position]==1 && isprompt ==1 && (za==true) ){
			    TrueNumber[k]+=scalef;}
		    if(photon_isprompt[position]!=1 && isprompt!=1 && (za==false)){
			    hfake[k]->Fill(photon_sieie[position],scalef);}
		    if(photon_isprompt[position]==1 && isprompt ==1 && (za==true)){
			    htrue[k]->Fill(photon_sieie[position],scalef);}
		    if(photon_isprompt[position]==1 && isprompt ==1 &&  (za==true) ){ 
		            h3[k]->Fill(photon_sieie[position],scalef);m3[k] +=scalef;}//true template
		    if(photon_sieie[position]< sieie /*&& photon_isprompt[position]!=1 && isprompt!=1 && (za==false)*/) h_sieie[k]->Fill(photon_sieie[position],scalef);
	    }//datamc
	    for(Int_t j=0;j<21;j++){
//		    if( ewk==false && isprompt==1) continue;
//		    if( tta==false && isprompt==1) continue;
//		    if( za==false &&  isprompt==1) continue;
		    if(photon_chiso[position]>lowchiso[j]&&photon_chiso[position]<highchiso[j]&&*biggest_pt<highpt[k] && *biggest_pt>lowpt[k] && photon_isprompt[position]!=1  && isprompt!=1 && (za==false)) 
		    { 
			    h2[k][j]->Fill(photon_sieie[position],scalef);
		    }  
	    }//fake template
    }
    vector_pt.clear();
 }  
 fT->cd();
 newtree->Write();
 delete fT;
}
int main(){
for(Int_t j=0;j<21;j++){
     if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
     if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
     if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;} 
     if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;} 
     if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;} 
     if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
   }
//style();
histo();
//TFile *f1 = new TFile("/home/pku/anying/cms/file_in_cms/2018RunIIrootfiles/"+rootfiles+".root");     
TFile *f1 = new TFile("./"+rootfiles+".root");     
TFile *ff1;
TTree *t1 =(TTree*)f1->Get("demo");
Double_t cnt = t1->GetEntries();
cout<<" entries = "<<cnt<<endl;
cout<<"file " + rootfiles + ".root"<<endl;
ff1= new TFile(dir1 + rootfiles+".root","recreate");
select(t1,h11,h12,h13);
ff1->cd();
for(Int_t i=0;i<ptnumber;i++){
    cout<<"pt range "<<lowpt[i]<<" ~ "<<highpt[i]<<endl;
    ofstream myfile1(Form(dir + sieiecut+"datanumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
    cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i]);
    cout<<"the number of data m1 in the medium sieie region = ";
    cout<<" "<<m1[i]<<endl;
    cout<<"the number of data in the total sieie region = ";
    cout<<" "<<m2[i]<<endl;
    myfile1<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m1[i]<<endl;

    h_sieie[i]->Write();
    hfake[i]->Write();
    htrue[i]->Write();
    h11[i]->Write();
    h13[i]->Write();
    for(Int_t j=0;j<21;j++){
	    h12[i][j]->Write();
//       cout<<Form(" %0.f<pt<%0.f , %0.f<photon_chiso<%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j])<<"the number  m2 is the number of fake photon in fake template = "<<m2[i][j]<<endl;
	    cout<<Form(" %0.f<pt<%0.f , %0.f<photon_chiso<%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j])<<"the FakeNumber is the number of fake photon medium sieie region = "<<FakeNumber[i]<<endl;
	    ofstream myfile_fake(Form(dir + sieiecut+"mfakenumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt[i],highpt[i],lowchiso[j],highchiso[j]));
	    myfile_fake<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<lowchiso[j]<<"\t"<<highchiso[j]<<"\t"<<FakeNumber[i]<<"\t"<<endl;
    }
    ofstream myfile(Form(dir + sieiecut+"truenumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
    cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  the TrueNumber is the number of real photons in medium sieie region "<<TrueNumber[i]<<endl;
    myfile<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m3[i]<<"\t"<<TrueNumber[i]<<endl;
} 
cout<<"#####################################"<<endl;
ff1->Close();
f1->Close();

return 0;
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
 l1->AddEntry(h1," datamc #gamma" );
 l1->AddEntry(h2,Form("%0d<photon_chiso<%0d  Fake #gamma",4,10) );
 l1->AddEntry(h3,"Real #gamma"); 
 l1->Draw(); 
 //c->Print("./"+plot+Form("_sieiept%0.f_%0.f.eps",ptlow,pthigh));
 delete c;
}
void histo(){
 Int_t bin=16;
 Double_t xlow= 0.0172;
 Double_t xhigh= 0.0572;
  for(Int_t i=0;i<ptnumber;i++){
      h_sieie[i]=new TH1D(Form("hsieie_pt%0.f_%0.f",lowpt[i],highpt[i]),"medium photon",bin,xlow,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      hfake[i]=new TH1D(Form("hfake_pt%0.f_%0.f",lowpt[i],highpt[i]),"isprompt!=1 with medium chiso",bin,xlow,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      htrue[i]=new TH1D(Form("htrue_pt%0.f_%0.f",lowpt[i],highpt[i]),"isprompt=1 with medium chiso ",bin,xlow,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      h11[i]=new TH1D(Form("h11_pt%0.f_%0.f",lowpt[i],highpt[i]),"medium chiso data template",bin,xlow,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      h21[i]=new TH1D(Form("h21_pt%0.f_%0.f",lowpt[i],highpt[i]),"medium chiso true template",bin,xlow,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      h23[i]=new TH1D(Form("h23_pt%0.f_%0.f",lowpt[i],highpt[i]),"medium chiso true template",bin,xlow,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
      h13[i]=new TH1D(Form("h13_pt%0.f_%0.f",lowpt[i],highpt[i]),"chiso<1.051",bin,xlow,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
    for(Int_t j=0;j<21;j++){  
         h12[i][j]=new TH1D(Form("h12_pt%0.f_%0.f_chiso%0.f_%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j]),Form("fake template %0.f>chiso>%0.f",highchiso[j],lowchiso[j]),bin,xlow,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
         h22[i][j]=new TH1D(Form("h22_pt%0.f_%0.f_chiso%0.f_%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j]),Form("%0.f>chiso>%0.f",highchiso[j],lowchiso[j]),bin,xlow,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
       }
  }  
  h31=new TH1D("h31","",bin,xlow,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
  h32=new TH1D("h32","",bin,xlow,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
  h33=new TH1D("h33","",bin,xlow,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
}
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
double delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2){
        Double_t dp = phi1-phi2;
        if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
        Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}
