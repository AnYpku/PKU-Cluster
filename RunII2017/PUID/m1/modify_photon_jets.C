#include "TLorentzVector.h"
#define Pi 3.1415926
#include "xx.h"
#include <iostream>

using namespace std;

void xx::modify_photon_jets()
{
	//set dummy value
	jet1pt=-99;
	jet1eta=-99;
	jet1phi=-99;
	jet1e=-99;
	jet1puIdTight=-99;
	jet1puIdLoose=-99;
	jet1puIdMedium=-99;
	jet2pt=-99;
	jet2eta=-99;
	jet2phi=-99;
	jet2e=-99;
	jet2puIdTight=-99;
	jet2puIdLoose=-99;
	jet2csv =-99;

	jet2csv =-99;
	jet1icsv =-99;
	jet2icsv =-99;
	drj1a=-99;
	drj2a=-99;
	drj1l=-99;
	drj2l=-99;
	drj1l2=-99;
	drj2l2=-99;
	j1metPhi=-99;
	j2metPhi=-99;
	Mjj=-99;
	zepp = -99;
	//set dummy value
	Int_t jetindexphoton12[2] = {-1,-1};
	for(Int_t i=0; i<6; i++){
		double drtmp1=delta_R(ak4jet_eta[i], ak4jet_phi[i], photoneta,photonphi);
		if(ak4jet_pt[i]>0 && ak4jet_puIdTight[i]==1 && drtmp1>0.5 && jetindexphoton12[0]==-1&&jetindexphoton12[1]==-1){
			jetindexphoton12[0] = i;
			continue;
		}
		if(ak4jet_pt[i]>0 && ak4jet_puIdTight[i]==1 && drtmp1>0.5 && jetindexphoton12[0]!=-1&&jetindexphoton12[1]==-1){
			jetindexphoton12[1] = i;
			continue;
		}
	}

	if(jetindexphoton12[0]>-1 && jetindexphoton12[1]>-1) 
	{
		jet1puIdTight=ak4jet_puIdTight[jetindexphoton12[0]];
		jet2puIdTight=ak4jet_puIdTight[jetindexphoton12[1]];
		jet1puIdMedium=ak4jet_puIdMedium[jetindexphoton12[0]];
		jet2puIdMedium=ak4jet_puIdMedium[jetindexphoton12[1]];
		jet1puIdLoose=ak4jet_puIdLoose[jetindexphoton12[0]];
		jet2puIdLoose=ak4jet_puIdLoose[jetindexphoton12[1]];
		jet1pt=ak4jet_pt[jetindexphoton12[0]];
		jet1eta=ak4jet_eta[jetindexphoton12[0]];
		jet1phi=ak4jet_phi[jetindexphoton12[0]];
		jet1e=ak4jet_e[jetindexphoton12[0]];
		jet2pt=ak4jet_pt[jetindexphoton12[1]];
		jet2eta=ak4jet_eta[jetindexphoton12[1]];
		jet2phi=ak4jet_phi[jetindexphoton12[1]];
		jet2e=ak4jet_e[jetindexphoton12[1]];
		jet1csv =ak4jet_csv[jetindexphoton12[0]];
		jet2csv =ak4jet_csv[jetindexphoton12[1]];
		jet1icsv =ak4jet_icsv[jetindexphoton12[0]];
		jet2icsv =ak4jet_icsv[jetindexphoton12[1]];
		drj1a=delta_R(jet1eta,jet1phi,photoneta,photonphi);
		drj2a=delta_R(jet2eta,jet2phi,photoneta,photonphi);
		drj1l=delta_R(jet1eta,jet1phi,etalep1,philep1);
		drj2l=delta_R(jet2eta,jet2phi,etalep1,philep1);
		drj1l2=delta_R(jet1eta,jet1phi,etalep2,philep2);
		drj2l2=delta_R(jet2eta,jet2phi,etalep2,philep2);
		TLorentzVector j1p4;
		j1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		TLorentzVector j2p4;
		j2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		TLorentzVector photonp42;
		photonp42.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		TLorentzVector vp4;
		vp4.SetPtEtaPhiM(ptVlep,yVlep,phiVlep,massVlep);
		j1metPhi=fabs(jet1phi-MET_phi);
		if(j1metPhi>Pi) {j1metPhi=2.0*Pi-j1metPhi;}
		j2metPhi=fabs(jet2phi-MET_phi);
		if(j2metPhi>Pi) {j2metPhi=2.0*Pi-j2metPhi;}
		Mjj=(j1p4 + j2p4).M();
		zepp = fabs((vp4+photonp42).Rapidity() - (j1p4.Rapidity() + j2p4.Rapidity())/ 2.0);
	}
}
