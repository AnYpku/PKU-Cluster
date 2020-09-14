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

using namespace std;
void fX0_parameterization_el(int index){

	const TString InData_New = "/home/pku/anying/cms/file_in_cms/cutla/cutla-";

	// Specify event selection cuts:
	TCut the_cut("(lep == 11 && (HLT_Ele1 >0 || HLT_Ele2 >0 ||HLT_Ele3 >0 ||HLT_Ele4 >0 ||HLT_Ele5 >0 ||HLT_Ele6 >0 ||HLT_Ele7 >0 )  && ptlep1 > 25. && ptlep2 > 25. && abs(etalep1) < 2.5 && abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus ==0 && massVlep > 70. && massVlep < 110. && jet1pt>30. && jet2pt>30.&& abs(jet1eta)< 4.7 && abs(jet2eta)<4.7 && Mjj>500. &&deltaetajj>2.5 && photonet>80.&&(abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5)))");
	// Create output ROOT file:

	TFile * fano;
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
	fano = new TFile(name+"_el_EWKZAJJ.root", "RECREATE");
	fout = new TFile("signal_proc_el__"+name+".root", "RECREATE");
	// The input tree
	TFile *f_file;
	f_file =  new TFile(InData_New+"outZA_aQGC.root");
	fano->cd();
	TTree* torig = (TTree*) f_file->Get("demo");
	TTree* treef = (TTree*) torig->CopyTree(the_cut);
	Long64_t numberOfEntries = treef->GetEntries();
	cout<<"Nentry="<<numberOfEntries<<endl;
	Double_t        Mva;  
	Double_t        photoneta;  
	Double_t        pweight[703];
	Double_t	jet1eta;
	Double_t	jet2eta;
	Double_t        photon_id_scale;
        Double_t        ele1_id_scale;
        Double_t        ele2_id_scale;
        Double_t        ele1_reco_scale;
        Double_t        ele2_reco_scale;
        Double_t        lumiWeight;
        Double_t        scalef;
        Double_t        pileupWeight;
        Double_t        photon_veto_scale=0.9938;

	treef->SetBranchAddress("Mva",&Mva);
	treef->SetBranchAddress("photoneta",&photoneta);
	treef->SetBranchAddress("pweight",pweight);
	treef->SetBranchAddress("jet1eta",&jet1eta);
	treef->SetBranchAddress("jet2eta",&jet2eta);
	treef->SetBranchAddress("photon_id_scale", &photon_id_scale);
        treef->SetBranchAddress("ele1_id_scale", &ele1_id_scale);
        treef->SetBranchAddress("ele2_id_scale", &ele2_id_scale);
        treef->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
        treef->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
        treef->SetBranchAddress("scalef", &scalef);
        treef->SetBranchAddress("lumiWeight", &lumiWeight);
        treef->SetBranchAddress("pileupWeight", &pileupWeight);

	// Do parameterization
	//double ZGbin[6] = {150,250,350,400,600,2e4};
	double ZGbin[6] = {150,400,600,800, 1000, 2e4};


	// Ratio of fT0

        double xxf[17];
	std::ofstream ParamSetf ;
//	ParamSetf.open("paramsets_fT0_el.txt");
	if(index==1) {ParamSetf.open("paramsets_fM0_el.txt");double xf[17] = {-150, -120, -80, -60, -50, -30, -20, -8, 0, 8, 20, 30, 50, 60, 80, 120, 150};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==2) {ParamSetf.open("paramsets_fM1_el.txt");double xf[17] = {-400, -300, -200, -150, -100, -80, -50, -20, 0, 20, 50, 80, 100, 150, 200, 300, 400};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==3) {ParamSetf.open("paramsets_fM2_el.txt");double xf[17] = {-100, -50, -40, -30, -20, -10, -5, -1, 0, 1, 5, 10, 20, 30, 40, 50, 100};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==4) {ParamSetf.open("paramsets_fM3_el.txt");double xf[17] = {-200, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==5) {ParamSetf.open("paramsets_fM4_el.txt");double xf[17] = {-200, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==6) {ParamSetf.open("paramsets_fM5_el.txt");double xf[17] = {-200, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==7) {ParamSetf.open("paramsets_fM6_el.txt");double xf[17] = {-250, -100, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 100, 250};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==8) {ParamSetf.open("paramsets_fM7_el.txt");double xf[17] = {-200, -120, -80, -60, -40, -20, -10, -5, 0, 5, 10, 20, 40, 60, 80, 120, 200};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==9) {ParamSetf.open("paramsets_fT0_el.txt");double xf[17] = {-20, -10, -6, -5, -3, -2, -1, -0.6, 0, 0.6, 1, 2, 3, 5, 6, 10, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==10) {ParamSetf.open("paramsets_fT1_el.txt");double xf[17] = {-20, -10, -6, -5, -3, -2, -1, -0.6, 0, 0.6, 1, 2, 3, 5, 6, 10, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==11) {ParamSetf.open("paramsets_fT2_el.txt");double xf[17] = {-40, -20, -15, -10, -8, -6, -4, -1, 0, 1, 4, 6, 8, 10, 15, 20, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==12) {ParamSetf.open("paramsets_fT5_el.txt");double xf[17] = {-40, -10, -8, -6, -5, -4, -2, -1, 0, 1, 2, 4, 5, 6, 8, 10, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==13) {ParamSetf.open("paramsets_fT6_el.txt");double xf[17] = {-40, -10, -8, -6, -5, -4, -2, -1, 0, 1, 2, 4, 5, 6, 8, 10, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==14) {ParamSetf.open("paramsets_fT7_el.txt");double xf[17] = {-40, -10, -8, -6, -5, -4, -2, -1, 0, 1, 2, 4, 5, 6, 8, 10, 40};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==15) {ParamSetf.open("paramsets_fT8_el.txt");double xf[17] = {-20, -8, -6, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 4, 6, 8, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }
        if(index==16) {ParamSetf.open("paramsets_fT9_el.txt");double xf[17] = {-20, -8, -6, -4, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 4, 6, 8, 20};for(int i=0;i<17;i++){xxf[i]=xf[i];} }

	// Times 10^{-12} (GeV^{-4})
//	const double xf[17] = {-20, -10, -6, -5, -3, -2, -1, -0.6, 0, 0.6, 1, 2, 3, 5, 6, 10, 20};

	for(int abin=0;abin<5;abin++){
		cout<<"abin="<<abin<<endl;
		double rf[17] ={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
		int iii = 447+(index-1)*16;
		for(int count=0; count < numberOfEntries; count++){
			treef->GetEntry(count);
			if(fabs(photoneta)<1.4442) photon_veto_scale=0.9938;
			if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.9875;
			Double_t weight=lumiWeight * pileupWeight * scalef*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale;
			if(count%100==0)  cout<<"abin="<<abin<<" count="<<count<<endl;
			if(fabs(jet1eta-jet2eta)>2.5 && Mva>ZGbin[abin]&&Mva<ZGbin[abin+1]){
				rf[0]+=pweight[iii]*weight;
                                rf[1]+=pweight[iii+1]*weight;
                                rf[2]+=pweight[iii+2]*weight;
                                rf[3]+=pweight[iii+3]*weight;
                                rf[4]+=pweight[iii+4]*weight;
                                rf[5]+=pweight[iii+5]*weight;
                                rf[6]+=pweight[iii+6]*weight;
                                rf[7]+=pweight[iii+7]*weight;
                                rf[8]+=pweight[446]*weight;//SM
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
		rf[0]=rf[0]/rsm;
		rf[1]=rf[1]/rsm;
		rf[2]=rf[2]/rsm;
		rf[3]=rf[3]/rsm;
		rf[4]=rf[4]/rsm;
		rf[5]=rf[5]/rsm;
		rf[6]=rf[6]/rsm;
		rf[7]=rf[7]/rsm;
		rf[8]=rf[8]/rsm; //SM
		rf[9]=rf[9]/rsm;
		rf[10]=rf[10]/rsm;
		rf[11]=rf[11]/rsm;
		rf[12]=rf[12]/rsm;
		rf[13]=rf[13]/rsm;
		rf[14]=rf[14]/rsm;
		rf[15]=rf[15]/rsm;
		rf[16]=rf[16]/rsm;

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
		fitFunc->SetParLimits(0,0.,1000) ;
		cout<<"OK"<<endl;
		fitFunc->SetLineColor(kBlue) ;
		cout <<"x1"<<endl;
		TFitResultPtr r = gr->Fit(tf1_name,"ESR") ;  //C:Do not calc chi2 M:mirror R:range
		Double_t chi2   = r->Chi2() ;
		Double_t par0   = fitFunc->GetParameter(0);
		Double_t par1   = fitFunc->GetParameter(1);
		Double_t err0   = fitFunc->GetParError(0) ;
		Double_t err1   = fitFunc->GetParError(1) ;
		r->Print("V") ;
		//r->Write() ;
		fout->cd();
		fitFunc->Write();
		cout <<"x2"<<endl;

		TCanvas *c1= new TCanvas("c1","fitFunc",500,500) ;
		c1->SetGridx(1) ;
		c1->SetGridy(1) ;
		cout <<"x3"<<endl;

		gr->SetTitle(TString(" Fitted line of AQGC/SM in ZGmass : ")+Form("(%.0f,%.0f)",ZGbin[abin],ZGbin[abin+1])) ;
		cout <<"x4"<<endl;
		gr->GetYaxis()->SetTitleOffset(1.4) ;
		char buffer2[256];
		if(index==1) sprintf(buffer2, "fM0/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==2) sprintf(buffer2, "fM1/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==3) sprintf(buffer2, "fM2/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==4) sprintf(buffer2, "fM3/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==5) sprintf(buffer2, "fM4/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==6) sprintf(buffer2, "fM5/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==7) sprintf(buffer2, "fM6/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==8) sprintf(buffer2, "fM7/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==9) sprintf(buffer2, "fT0/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==10) sprintf(buffer2, "fT1/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==11) sprintf(buffer2, "fT2/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==12) sprintf(buffer2, "fT5/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==13) sprintf(buffer2, "fT6/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==14) sprintf(buffer2, "fT7/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==15) sprintf(buffer2, "fT8/#Lambda^{4} (#times 10^{-12} GeV)");
	        if(index==16) sprintf(buffer2, "fT9/#Lambda^{4} (#times 10^{-12} GeV)");
		
		gr->GetXaxis()->SetTitle(buffer2) ;
//		gr->GetXaxis()->SetTitle("fT0/#Lambda^{4} (#times 10^{-12} GeV)") ;
		gr->GetYaxis()->SetTitle("Ratio") ;
		gr->SetMarkerStyle(4) ;
		//gr->SetMarkerSize(0.7) ;
		cout <<"x5"<<endl;
		gr->SetLineWidth(2) ;
		gr->SetLineColor(kBlue) ;
		//gr->GetYaxis()->SetRangeUser(0.95,1.12) ;
		gr->Draw("AP") ;
		cout <<"x6"<<endl;
		TLegend *leg = new TLegend(0.3,0.58,0.70,0.88) ;
		leg->SetFillColor(10) ;
		leg->AddEntry(gr,"Fitted line: r =  p0 x^{2} + p1 x + 1","L") ;
		cout <<"x7"<<endl;
		leg->AddEntry(gr,Form("p0 = %f ",par0),"") ;
		leg->AddEntry(gr,Form("p1 = %f ",par1),"") ;
		cout <<"x8"<<endl;
		//leg->AddEntry(gr,TString("SM yield: ")+Form("%f",signal_SM->Integral()),"") ;
		leg->Draw("SAME") ;
		cout <<"x9"<<endl;
		if(index==1) c1->SaveAs(TString("fit_fM0")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==2) c1->SaveAs(TString("fit_fM1")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==3) c1->SaveAs(TString("fit_fM2")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==4) c1->SaveAs(TString("fit_fM3")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==5) c1->SaveAs(TString("fit_fM4")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==6) c1->SaveAs(TString("fit_fM5")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==7) c1->SaveAs(TString("fit_fM6")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==8) c1->SaveAs(TString("fit_fM7")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==9) c1->SaveAs(TString("fit_fT0")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==10) c1->SaveAs(TString("fit_fT1")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==11) c1->SaveAs(TString("fit_fT2")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==12) c1->SaveAs(TString("fit_fT5")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==13) c1->SaveAs(TString("fit_fT6")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==14) c1->SaveAs(TString("fit_fT7")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==15) c1->SaveAs(TString("fit_fT8")+Form("_ZGbin_%u",abin)+TString(".png")) ;
                if(index==16) c1->SaveAs(TString("fit_fT9")+Form("_ZGbin_%u",abin)+TString(".png")) ;
//		c1->SaveAs(TString("fit_fT0")+Form("_ZPTbin_%u",abin)+TString(".png")) ;

		ParamSetf << par0 << " " << par1 << " " << endl;
		cout <<"x10 "<<abin<<endl;

	} // Do this for all W PT bins

	ParamSetf.close();

}


void f_parameterization_el(){
	fX0_parameterization_el(1);
	fX0_parameterization_el(2);
	fX0_parameterization_el(3);
	fX0_parameterization_el(4);
	fX0_parameterization_el(5);
	fX0_parameterization_el(6);
	fX0_parameterization_el(7);
	fX0_parameterization_el(8);
	fX0_parameterization_el(9);
	fX0_parameterization_el(10);
	fX0_parameterization_el(11);
	fX0_parameterization_el(12);
	fX0_parameterization_el(13);
	fX0_parameterization_el(14);
	fX0_parameterization_el(15);
	fX0_parameterization_el(16);
}
