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
#include "TTreeFormula.h"
#define Pi 3.1415926
//#define ptnumber 6
using namespace std;

void style();
void histo(TString channel,vector<double> lowpt,vector<double> highpt,const int ptnumber, TH1D *h1[ptnumber],TH1D *h2[ptnumber][21],TH1D *h3[ptnumber],TH1D* h_sieie[ptnumber],TH1D* hfake[ptnumber],TH1D* htrue[ptnumber]);
//const int ptnumber;
Double_t scalef;
Bool_t photon_pev[6],za=false;
Double_t photon_drla[6],photon_pt[6],photon_drla2[6],photon_sieie[6],photon_chiso[6];
double photon_hoe[6];
double photon_nhiso[6];
double photon_phoiso[6];
double photon_eta[6],photon_phi[6];
int photon_isprompt[6],lep,isprompt;
bool medium_cut[6];
Double_t lowchiso[21],highchiso[21];
vector<double> vector_pt;
double biggest_pt;
// vector<double>::iterator biggest_pt;
Int_t position=0,size,m=0;
Int_t nentries;
TString dir = "./txt/";
TString dir1 = "./root/";
void select(vector<double> lowpt,vector<double> highpt,const int ptnumber, TH1D *h1[ptnumber],TH1D *h2[ptnumber][21],TH1D *h3[ptnumber],TH1D* h_sieie[ptnumber],TH1D* hfake[ptnumber],TH1D* htrue[ptnumber],TString tag,TString cut,TString channel,TGraph*gr){
	Double_t m1[ptnumber],m2[ptnumber][21],m3[ptnumber];
	Double_t TrueNumber[ptnumber],FakeNumber[ptnumber];
	TFile* fin = new TFile("./rootfiles/Pdata_cutlep_"+channel+tag+".root");
//	TFile* fin = new TFile("/home/pku/anying/cms/rootfiles/"+tag+"/Pdata.root");
	TTree*tree=(TTree*)fin->Get("ZPKUCandidates");
	cout<<"open file "<<fin->GetName()<<endl;
	tree->SetBranchAddress("photon_hoe",photon_hoe);
	tree->SetBranchAddress("photon_pev",photon_pev);
	tree->SetBranchAddress("photon_nhiso",photon_nhiso);
	tree->SetBranchAddress("photon_phoiso",photon_phoiso);
	tree->SetBranchAddress("photon_pt",photon_pt);
	tree->SetBranchAddress("photon_eta",photon_eta);
	tree->SetBranchAddress("photon_phi",photon_phi);
	tree->SetBranchAddress("scalef",&scalef);
	tree->SetBranchAddress("photon_isprompt",photon_isprompt);
	tree->SetBranchAddress("isprompt",&isprompt);
	tree->SetBranchAddress("photon_drla",photon_drla);
	tree->SetBranchAddress("photon_drla2",photon_drla2);
	tree->SetBranchAddress("photon_sieie",photon_sieie);
	tree->SetBranchAddress("photon_chiso",photon_chiso);
	tree->SetBranchAddress("photon_pt",photon_pt);

	for(Int_t i=0;i<ptnumber;i++){
		m1[i]=0;m3[i]=0;TrueNumber[i]=0;FakeNumber[i]=0;
		for(Int_t j=0;j<21;j++){m2[i][j]=0;}
	}
	TFile* fT = new TFile("./Pdata_cutlep_"+channel+tag+".root","recreate");
	TTree* newtree = tree->CloneTree(0);
	nentries = tree->GetEntries();
	TTreeFormula*tformula=new TTreeFormula("formula", cut, tree);
	TString sieiecut = "nosieiecut_"+channel;
	Double_t chiso = 1.141;
	Double_t sieie = 0.01015;
	if(channel.Contains("barrel")) {sieie=0.01015;chiso=1.141;}
	if(channel.Contains("endcap")) {sieie=0.0272;chiso=1.051;}
	cout<<"sieie="<<sieie<<"; chiso="<<chiso<<endl;
	for(Int_t i=0;i<nentries;i++){
		tree->GetEntry(i);
		if (  !tformula->EvalInstance() )
			continue;
		for(Int_t k=0;k<6;k++){
			if(photon_drla[k]==10) photon_drla[k]=-10;if(photon_drla2[k]==10) photon_drla2[k]=-10; 
		}
		for(Int_t j=0;j<6;j++){
			if(channel.Contains("barrel")){
				medium_cut[j]=  photon_pev[j]==1 &&
					photon_hoe[j]<0.02197 &&
					photon_nhiso[j]<1.189 + 0.01512*photon_pt[j]+0.00002259*photon_pt[j]*photon_pt[j] &&
					photon_phoiso[j]<2.08 + 0.004017*photon_pt[j]&&
					fabs(photon_eta[j])<1.4442 &&
					photon_drla[j]>0.7 && photon_drla2[j]>0.7 &&
					photon_pt[j]>20 &&photon_pt[j]<400;//Barrel
			}
			else if(channel.Contains("endcap")){ 
				medium_cut[j]= photon_pev[j]==1 && photon_hoe[j]<0.0326
					&& photon_nhiso[j]<2.718 + 0.0117*photon_pt[j] + 0.000023*photon_pt[j]*photon_pt[j]
					&& photon_phoiso[j]<3.867 + 0.0037*photon_pt[j]
					&& ( fabs(photon_eta[j])<2.5&&fabs(photon_eta[j])>1.566 )
					&& photon_drla[j]>0.7 && photon_drla2[j]>0.7
					&& photon_pt[j]>20&&photon_pt[j]<400;//Endcap
			}

			if(medium_cut[j] ){
				/*cout<<"OK"<<endl;*/
				vector_pt.push_back(photon_pt[j]);
			}
			else {vector_pt.push_back(0);}
		}//fill the vector_pt
		biggest_pt=vector_pt[0];position=0;
		for(int kk=0;kk<vector_pt.size();kk++){
			if(vector_pt[kk]>biggest_pt){ 
				biggest_pt=vector_pt[kk];
				position=kk;
			}
		} 
		if(biggest_pt==0){
			vector_pt.clear();
			continue;}
		newtree->Fill();
		za = false;
		if(tag.Contains("16") && fabs(scalef)<0.004&&fabs(scalef)>0.003)  za=true;
		if(tag.Contains("17") && fabs(scalef)<0.003&&fabs(scalef)>0.0028)  za=true;
		if(tag.Contains("18") && fabs(scalef)<0.0027&&fabs(scalef)>0.0025)  za=true;
                photon_sieie[position]=gr->Eval(photon_sieie[position]);
		if(i%10000==0) cout<<i<<" "<<nentries<<" "<<"the biggest pt "<<biggest_pt<<" position "<<position<<endl;
		//cout<<"the biggest pt"<<*biggest_pt<<endl;
		for(Int_t k=0;k<ptnumber;k++){
			if(photon_chiso[position]< chiso && biggest_pt<highpt[k] && biggest_pt>lowpt[k]) 
			{
				if( (photon_isprompt[position]!=1 && (za == false) && isprompt !=1 ) || 
						(photon_isprompt[position]==1 && isprompt ==1 && (za==true))  )    
					h1[k]->Fill(photon_sieie[position],scalef);//data template
				if(photon_sieie[position]< sieie){   
					m1[k] += scalef;}// the number of data in medium sieie region
				if(photon_sieie[position]< sieie && photon_isprompt[position]!=1 && isprompt !=1 && (za ==false)){
					FakeNumber[k]+=scalef;}
				if(photon_sieie[position]< sieie && photon_isprompt[position]==1 && isprompt ==1 && (za==true)){
					TrueNumber[k]+=scalef;}
				if(photon_isprompt[position]!=1 && (za == false) && isprompt !=1 ){
					hfake[k]->Fill(photon_sieie[position],scalef);} //mcTruth fake
				if(photon_isprompt[position]==1 && isprompt ==1 && (za==true)){
					htrue[k]->Fill(photon_sieie[position],scalef);}//mcTruth real
				if(photon_isprompt[position]==1 && isprompt==1 && (za==true) ){ 
					h3[k]->Fill(photon_sieie[position],scalef);m3[k] +=scalef;}//true template
				if(photon_sieie[position]< sieie) h_sieie[k]->Fill(photon_sieie[position],scalef);
			}//datamc
			for(Int_t j=0;j<21;j++){
				if(photon_chiso[position]>lowchiso[j]&&photon_chiso[position]<highchiso[j]&&biggest_pt<highpt[k] && biggest_pt>lowpt[k] && photon_isprompt[position]!=1 && (za ==false) && isprompt!=1) 
				{ 
					h2[k][j]->Fill(photon_sieie[position],scalef);m2[k][j] +=scalef;
				}  
			}//fake template
		}
		vector_pt.clear();
	}  
	fT->cd();
	newtree->Write();
	delete fT;

	TFile *ff1= new TFile(dir1 + "histo_Pdata"+tag+"_"+channel+".root","recreate");
	ff1->cd();
	for(Int_t i=0;i<ptnumber;i++){
		cout<<"pt range "<<lowpt[i]<<" ~ "<<highpt[i]<<"; the number of events(m1) in the medium sieie region = "<<m1[i]<<endl;
		ofstream myfile1(Form(dir + sieiecut+tag+"_datanumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
		myfile1<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m1[i]<<endl;

		h_sieie[i]->Write();
		hfake[i]->Write();
		htrue[i]->Write();
		h1[i]->Write();
		h3[i]->Write();
		for(Int_t j=0;j<21;j++){
			h2[i][j]->Write();
			cout<<Form(" %0.f<pt<%0.f , %0.f<photon_chiso<%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j])<<" the number of fake photon(FakeNumber) in medium sieie region = "<<FakeNumber[i]<<endl;
			ofstream myfile_fake(Form(dir + sieiecut+tag+"_fakenumber_pt%0.f-%0.f_chiso%0.f-%0.f.txt",lowpt[i],highpt[i],lowchiso[j],highchiso[j]));
			myfile_fake<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<lowchiso[j]<<"\t"<<highchiso[j]<<"\t"<<FakeNumber[i]<<"\t"<<m2[i][j]<<endl;
		}
		cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  the TrueNumber is the number of real photons in medium sieie region "<<TrueNumber[i]<<endl;
		ofstream myfile(Form(dir + sieiecut+tag+"_truenumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]));
		myfile<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m3[i]<<"\t"<<TrueNumber[i]<<endl;
	} 
	cout<<"#####################################"<<endl;
	ff1->Close();
	fin->Close();
}
int build(){
	for(Int_t j=0;j<21;j++){
		if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
		if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
		if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
		if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
		if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
		if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
	}
	TString LEPmu="lep==13 && (HLT_Mu1>0 || HLT_Mu2>0) && ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110";
	TString LEPele="lep==11 && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& abs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0 && massVlep >70. && massVlep < 110";
	vector<TString> tag={"2016","2017","2018"};
	vector<TString> channel={"mubarrel","muendcap","elebarrel","eleendcap"};
	TString cut;
        vector<double> lowpt;vector<double> highpt;
	for(int i=1;i<tag.size();i++){
		for(int j=0;j<channel.size();j++){
                        if(tag[i]=="2016" && channel[j]=="mubarrel") continue;
			TFile* f_gr;
			TGraph* gr;
			cout<<tag[i]<<" "<<channel[j]<<endl;
			if(channel[j].Contains("barrel")) {
				lowpt={20,25,30,40,50,60};
				highpt={25,30,40,50,60,400};
				f_gr=new TFile("../RunII"+tag[i]+"2016/sigmaEtaEta_corr/transformation_barrel.root");
				gr=(TGraph*)f_gr->Get("barrel"); 
			}
			else if(channel[j].Contains("endcap")) {
				lowpt={20,25,30,50};
				highpt={25,30,50,400};
				f_gr=new TFile("../RunII"+tag[i]+"/sigmaEtaEta_corr/transformation_endcap.root");
				gr=(TGraph*)f_gr->Get("endcap"); 
			}
			const int ptnumber=lowpt.size();
			cout<<"ptnumber "<<ptnumber<<endl;
			TH1D* h11[ptnumber];
			TH1D* h12[ptnumber][21];
			TH1D* h13[ptnumber];
			TH1D* h_sieie[ptnumber];
			TH1D* hfake[ptnumber];
			TH1D* htrue[ptnumber];
			histo(channel[j],lowpt,highpt,ptnumber,h11,h12,h13,h_sieie,hfake,htrue);
			if(channel[j].Contains("mu")) cut=LEPmu;
			else if(channel[j].Contains("ele")) cut=LEPele;
			select(lowpt,highpt,ptnumber,h11,h12,h13,h_sieie,hfake,htrue,tag[i],cut,channel[j],gr);
                        f_gr->Close();
		}
	}
	return 0;
}

void histo(TString channel,vector<double> lowpt,vector<double> highpt,const int ptnumber, TH1D *h1[ptnumber],TH1D *h2[ptnumber][21],TH1D *h3[ptnumber],TH1D* h_sieie[ptnumber],TH1D* hfake[ptnumber],TH1D* htrue[ptnumber]){
	Int_t bin=34;
	Double_t xlow=  0.00515;
	Double_t xhigh= 0.02215;
	if(channel.Contains("barrel")){
		Int_t bin=34;
		Double_t xlow=  0.00515;
		Double_t xhigh= 0.02215;
	}
	if(channel.Contains("endcap")){
		bin = 40;
		xlow= 0.0172;;
		xhigh=0.0572;
	}

	for(Int_t i=0;i<ptnumber;i++){
		h_sieie[i]=new TH1D(Form("hsieie_pt%0.f_%0.f",lowpt[i],highpt[i]),"medium photon",bin,xlow,xhigh);
		hfake[i]=new TH1D(Form("hfake_pt%0.f_%0.f",lowpt[i],highpt[i]),"isprompt!=1 with medium chiso",bin,xlow,xhigh);
		htrue[i]=new TH1D(Form("htrue_pt%0.f_%0.f",lowpt[i],highpt[i]),"isprompt=1 with medium chiso ",bin,xlow,xhigh);
		h1[i]=new TH1D(Form("h11_pt%0.f_%0.f",lowpt[i],highpt[i]),"medium chiso data template",bin,xlow,xhigh);
		h3[i]=new TH1D(Form("h13_pt%0.f_%0.f",lowpt[i],highpt[i]),"chiso<1.141",bin,xlow,xhigh);
		for(Int_t j=0;j<21;j++){  
			h2[i][j]=new TH1D(Form("h12_pt%0.f_%0.f_chiso%0.f_%0.f",lowpt[i],highpt[i],lowchiso[j],highchiso[j]),Form("fake template %0.f>chiso>%0.f",highchiso[j],lowchiso[j]),bin,xlow,xhigh);
		}
	}  
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
