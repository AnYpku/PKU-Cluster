#include <iostream>
#include "TLatex.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "THStack.h"
#include "TString.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TGraph.h"
#include <fstream>
#include "math.h"
#define pi 3.1415926
using namespace std;
void fX0_parameterization_hist(int index,TString tag,TString file,TString cut,TString channel,vector<double>ZGbin){

//	const TString InData_New = "/home/pku/anying/cms/rootfiles/20"+tag+"/cutla-";
	const TString InData_New = "../rootfiles/optimal_";

	// Specify event selection cuts:
	// Create output ROOT file:

	TFile * fout;
	TString name;
	if(index==1) name="fM0";
	if(index==2) name="fM1";
	if(index==3) name="fM2";
	if(index==4) name="fM3";
	if(index==5) name="fM4";
	if(index==6) name="fM5";
	if(index==7) name="fM6";
	if(index==8) name="fM7";
	if(index==9) name="fT0";
	if(index==10) name="fT1";
	if(index==11) name="fT2";
	if(index==12) name="fT5";
	if(index==13) name="fT6";
	if(index==14) name="fT7";
	if(index==15) name="fT8";
	if(index==16) name="fT9";
	fout = new TFile("./hist/referee/hist_"+channel+"_"+name+"_"+tag+".root", "RECREATE");
	// The input tree
	TFile *f_file;
	f_file =  new TFile(InData_New+file);
//	TTree* treef = (TTree*) f_file->Get("ZPKUCandidates");
	TTree* treef = (TTree*) f_file->Get("outtree");
	Long64_t numberOfEntries = treef->GetEntries();
	cout<<"Nentry="<<numberOfEntries<<endl;
	Double_t        ZGmass,Mjj;  
        Int_t HLT_Mu1,HLT_Mu2,HLT_Mu3,HLT_Ele1,HLT_Ele2,lep,nlooseeles,nloosemus;
	Double_t        photoneta,photonet,massVlep;  
	Double_t        pweight[703];
	Double_t        prefWeight;
	Double_t	jet1eta,jet1pt,etalep1,ptlep1;
	Double_t	jet2eta,jet2pt,etalep2,ptlep2;
	Double_t        photon_id_scale;
	Double_t        photon_veto_scale;
        Double_t        ele1_id_scale;
        Double_t        ele2_id_scale;
        Double_t        ele1_reco_scale;
        Double_t        ele2_reco_scale;
        Double_t        muon1_id_scale;
        Double_t        muon2_id_scale;
        Double_t        muon1_iso_scale;
        Double_t        muon2_iso_scale;
        Double_t        ele_hlt_scale;
        Double_t        muon_hlt_scale;
        Double_t        lumiWeight;
        Double_t        scalef;
        Double_t        pileupWeight;
        Double_t        puIdweight;

	treef->SetBranchAddress("ZGmass",&ZGmass);
	treef->SetBranchAddress("HLT_Ele2",&HLT_Ele2);
	treef->SetBranchAddress("HLT_Ele1",&HLT_Ele1);
	treef->SetBranchAddress("HLT_Mu1",&HLT_Mu1);
	treef->SetBranchAddress("HLT_Mu2",&HLT_Mu2);
	treef->SetBranchAddress("HLT_Mu3",&HLT_Mu3);
	treef->SetBranchAddress("lep",&lep);
	treef->SetBranchAddress("nloosemus",&nloosemus);
	treef->SetBranchAddress("nlooseeles",&nlooseeles);
	treef->SetBranchAddress("ptlep1",&ptlep1);
	treef->SetBranchAddress("ptlep2",&ptlep2);
	treef->SetBranchAddress("etalep1",&etalep1);
	treef->SetBranchAddress("etalep2",&etalep2);
	treef->SetBranchAddress("massVlep",&massVlep);
	treef->SetBranchAddress("photoneta",&photoneta);
	treef->SetBranchAddress("photonet",&photonet);
	treef->SetBranchAddress("pweight",pweight);
	treef->SetBranchAddress("jet1eta",&jet1eta);
	treef->SetBranchAddress("jet2eta",&jet2eta);
	treef->SetBranchAddress("jet1pt",&jet1pt);
	treef->SetBranchAddress("jet2pt",&jet2pt);
	treef->SetBranchAddress("Mjj",&Mjj);
	treef->SetBranchAddress("photon_id_scale", &photon_id_scale);
	treef->SetBranchAddress("photon_veto_scale", &photon_veto_scale);
        treef->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
        treef->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
        treef->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
        treef->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
        treef->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
        treef->SetBranchAddress("ele1_id_scale", &ele1_id_scale);
        treef->SetBranchAddress("ele2_id_scale", &ele2_id_scale);
        treef->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
        treef->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
        treef->SetBranchAddress("scalef", &scalef);
        treef->SetBranchAddress("lumiWeight", &lumiWeight);
        treef->SetBranchAddress("pileupWeight", &pileupWeight);
        treef->SetBranchAddress("prefWeight", &prefWeight);
        treef->SetBranchAddress("puIdweight", &puIdweight);
        treef->SetBranchAddress("muon_hlt_scale",   &muon_hlt_scale);

	// Do parameterization
        const int num=ZGbin.size()-1;

//	double ZGbin[7] = {150,300,450,600,750,1000,2e4};;
//      const int num=6;
	// Ratio of fT0

        double xxf[17];
	std::ofstream ParamSetf ;
//	ParamSetf.open("paramsets_fT0_el.txt");
	if(index==1) {double xf[17] = {-150, -120, -80, -60, -50, -30, -20, -8, 0, 8, 20, 30, 50, 60, 80, 120, 150};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==2) {double xf[17] = {-400, -300, -200, -150, -100, -80, -50, -20, 0, 20, 50, 80, 100, 150, 200, 300, 400};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==3) {double xf[17] = {-100, -50, -40, -30, -20, -10, -5, -1, 0, 1, 5, 10, 20, 30, 40, 50, 100};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==4) {double xf[17] = {-200, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==5) {double xf[17] = {-200, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==6) {double xf[17] = {-200, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==7) {double xf[17] = {-250, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 250};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==8) {double xf[17] = {-200, -120, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 120, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==9) {double xf[17] = {-20, -10, -6, -5, -3, -2, -1, -0.6, 0, 0.6, 1, 2, 3, 5, 6, 10, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==10){double xf[17] = {-20, -10, -6, -5, -3, -2, -1, -0.6, 0, 0.6, 1, 2, 3, 5, 6, 10, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==11){double xf[17] = {-40, -20, -15, -10, -8, -6, -4, -1, 0, 1, 4, 6, 8, 10, 15, 20, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==12){double xf[17] = {-40, -10, -8, -6, -5, -4, -2, -1, 0, 1, 2, 4, 5, 6, 8, 10, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==13){double xf[17] = {-40, -10, -8, -6, -5, -4, -2, -1, 0, 1, 2, 4, 5, 6, 8, 10, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==14){double xf[17] = {-40, -10, -8, -6, -5, -4, -2, -1, 0, 1, 2, 4, 5, 6, 8, 10, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==15){double xf[17] = {-20, -8, -6, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 4, 6, 8, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==16){double xf[17] = {-20, -8, -6, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 4, 6, 8, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        TGraph*g1[num];
	// Times 10^{-12} (GeV^{-4})
//	const double xf[17] = {-20, -10, -6, -5, -3, -2, -1, -0.6, 0, 0.6, 1, 2, 3, 5, 6, 10, 20};

        TTreeFormula* formula= new TTreeFormula("f",cut,treef);
	for(int abin=0;abin<num;abin++){
//		cout<<"abin="<<abin<<endl;
//		h1[abin]=new TH1D(name+Form("_bin%i",abin+1),"yields with every "+name+" value",16,xxf);
		double rf[17] ={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
                int iii;
                if(tag.Contains("16")) iii= 447+(index-1)*16;
                else iii = 1+(index-1)*16;
		for(int count=0; count < numberOfEntries; count++){
			treef->GetEntry(count);
                        double deltaetajj = fabs(jet1eta-jet2eta);
                        if( ! formula->EvalInstance())
                                continue;
                        if(ZGmass>2e4) ZGmass=1999;
                        Double_t weight;
                        if(tag.Contains("18")) prefWeight=1;
                        if(channel.Contains("ele"))
                                weight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale*puIdweight;
                        else    weight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale*puIdweight;
			if(fabs(jet1eta-jet2eta)>2.5 && ZGmass>ZGbin[abin]&&ZGmass<ZGbin[abin+1]){
				rf[0]+=pweight[iii]*weight;
                                rf[1]+=pweight[iii+1]*weight;
                                rf[2]+=pweight[iii+2]*weight;
                                rf[3]+=pweight[iii+3]*weight;
                                rf[4]+=pweight[iii+4]*weight;
                                rf[5]+=pweight[iii+5]*weight;
                                rf[6]+=pweight[iii+6]*weight;
                                rf[7]+=pweight[iii+7]*weight;
                                if(tag.Contains("16"))
                                        rf[8] +=pweight[446]*weight;//SM
                                else    rf[8] +=pweight[0]*weight;//SM
                                rf[9]+=pweight[iii+8]*weight;
                                rf[10]+=pweight[iii+9]*weight;
                                rf[11]+=pweight[iii+10]*weight;
                                rf[12]+=pweight[iii+11]*weight;
                                rf[13]+=pweight[iii+12]*weight;
                                rf[14]+=pweight[iii+13]*weight;
                                rf[15]+=pweight[iii+14]*weight;
                                rf[16]+=pweight[iii+15]*weight;
			} 
		}
		double rsm = rf[8];
//		for(int j=0;j<17;j++){
//			cout<<j<<"; "<<rf[j]<<endl;}
                g1[abin]=new TGraph(17,xxf,rf); 
		TGraph *gr = new TGraph(17,xxf,rf);
		double low;
		double high;
		if(index==1) {low=-150;high=150;};
	        if(index==2) {low=-400;high=400;};
	        if(index==3) {low=-100;high=100;};
	        if(index==4) {low=-200;high=200;};
	        if(index==5) {low=-200;high=200;};
	        if(index==6) {low=-200;high=200;};
	        if(index==7) {low=-250;high=250;};
	        if(index==8) {low=-200;high=200;};
	        if(index==9) {low=-20;high=20;};
	        if(index==10) {low=-20;high=20;};
	        if(index==11) {low=-40;high=40;};
	        if(index==12) {low=-40;high=40;};
	        if(index==13) {low=-40;high=40;};
	        if(index==14) {low=-40;high=40;};
	        if(index==15) {low=-20;high=20;};
	        if(index==16) {low=-20;high=20;};

                TString tf1_name = TString("signal_proc_")+name+Form("_bin%u",abin+1);
                TF1 *fitFunc = new TF1(tf1_name,"[0]*(x**2) + [1]*x + 1",low,high) ;

		cout<<"OK"<<endl;
		fitFunc->SetLineColor(kBlue) ;

	} // Do this for all W PT bins

	fout->cd();
	for(int i=0;i<num;i++){
		g1[i]->Write(Form("bin%i",i));	
	}
	fout->Close();

}

void f_hist(){
        gSystem->Load("libTreePlayer.so");
        TString cut;
        vector<TString>channel={"ele","muon"};
        vector<TString> tag={"16","17","18"};
//        vector<TString> tag={"17"};
        vector<TString> file={"ZA_aQGC16.root","ZA_aQGC17.root","ZA_aQGC18.root"};
	vector<double> ZGbin = {150,400,600,800,1000,1200,2e4};
	TString LEPele="(lep==11  && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
        TString LEPmu = "(drll>0.3 && lep==13 && (HLT_Mu1>0 || HLT_Mu2>0 || HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>120 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
        TString Pi=Form("%f",pi);
        TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
        TString SignalRegion = "(Mjj>500 && detajj>2.5 && zepp<2.4 && delta_phi>1.9)";
	TString jet;
        for(int k=0;k<tag.size();k++){
//	       if(tag[k].Contains("17")==0) continue;
		if(tag[k].Contains("16")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else if(tag[k].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		}
		else if(tag[k].Contains("18")){
			jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
		}
		for(int j=0;j<channel.size();j++){
			if(channel[j].Contains("ele"))
				cut="(("+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
			else if(channel[j].Contains("muon"))
				cut="(("+LEPmu+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
			for(int i=1;i<=16;i++){
				cout<<tag[k]<<" "<<file[k]<<" "<<channel[j]<<endl;
				cout<<cut<<endl;
				fX0_parameterization_hist(i,tag[k],file[k],cut,channel[j],ZGbin);
			}
		}
	}
}
