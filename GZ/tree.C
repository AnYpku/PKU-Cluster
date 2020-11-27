#define tree_cxx
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <iostream>
#include "TLorentzVector.h"
#define Pi 3.141592653589793
using namespace std;
void tree::Loop()
{
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntries();
	Bool_t lep_cut,photon_cut;
	double drl1a,drl2a;
	vector<double>::iterator biggest_photon;
	vector<double> pho_pt;
	double mll;
	int kk=0;
	int sum_charge;
	TLorentzVector lep1p4,lep2p4;
	Long64_t nbytes = 0, nb = 0;
	th1=new TH1D("h1","m_{ll}",30,10,300);
        cout<<"nentries "<<nentries<<endl;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		lep_cut="(nLepton>1&&nLepton<3&&Lepton_pt[0]>0 && Lepton_pt[1]>0)";
		if(!lep_cut) continue;
                sum_charge=Lepton_charge[0]+Lepton_charge[1];
		if(!sum_charge==0) continue;
		if(nPhoton==1){ 
			drl1a=Delta(Lepton_eta[0],Lepton_phi[0],Photon_eta[0],Photon_phi[0]);
			drl2a=Delta(Lepton_eta[1],Lepton_phi[1],Photon_eta[0],Photon_phi[0]);
		}
                
		if(drl1a<0.5 || drl2a<0.5) continue;
		double n_pho=0;
		if(nPhoton>1){
			for(int i=0;i<nPhoton;i++){
				drl1a=Delta(Lepton_eta[0],Lepton_phi[0],Photon_eta[nPhoton],Photon_phi[nPhoton]);
				drl2a=Delta(Lepton_eta[1],Lepton_phi[1],Photon_eta[nPhoton],Photon_phi[nPhoton]);
				if(drl1a>0.5 && drl2a>0.5 && Photon_pt[nPhoton]>20){ 
					pho_pt.push_back(Photon_pt[nPhoton]);
					n_pho++;
				}
			}
		}
		//    biggest_photon=max_element(begin(pho_pt),end(pho_pt)); 
		//    pho1_index = distance( begin(pho_pt), biggest_photon);
		if(n_pho<1) continue;
		lep1p4.SetPtEtaPhiM(Lepton_pt[0], Lepton_eta[0], Lepton_phi[0], Lepton_mass[0]);
		lep2p4.SetPtEtaPhiM(Lepton_pt[1], Lepton_eta[1], Lepton_phi[1], Lepton_mass[1]);
		mll=(lep1p4+lep2p4).M();
		pho_pt.clear();
                weight=0.34397*1000/nentries;
		th1->Fill(mll,weight);
                ExTree->Fill();
		kk++;
	}
       cout<<"weight "<<weight<<endl;
}
Double_t tree::Delta(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2){
	Double_t dp = phi1-phi2;
	if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
	Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
	return dr;
}


