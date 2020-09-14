#include "TLorentzVector.h"
#define Pi 3.1415926
#include "rm.h"
#include <iostream>

using namespace std;

Double_t delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{
        Double_t dp = phi1-phi2;
        if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
        Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}
void rm::genparticles(){
	int pho1_index,jet1_index,muon1_index,ele1_index;
	double maxPhoton_1st=0,maxJet_1st=0,maxMuon_1st=0,maxEle_1st=0;
	int pho2_index,jet2_index,muon2_index,ele2_index;
	double maxPhoton_2nd=0,maxJet_2nd=0,maxMuon_2nd=0,maxEle_2nd=0;
	for(int i=0;i<6;i++){
		genmu[i] =genmuon_pid[i]==13 && genmuon_pt[i]>20 && fabs(genmuon_eta[i])<2.4;
		genele[i]=genelectron_pt[i]>25 && fabs(genelectron_eta[i])<2.5;
		genphoton[i] = genphoton_pt[i]>20 &&(fabs(genphoton_eta[i])<1.4442 &&( fabs(genphoton_eta[i])<2.5 && fabs(genphoton_eta[i])>1.566 ) );
		genjet[i] = genjet_pt[i]>30 && fabs(genjet_eta[i])<4.7;
	}
	for(int index=0;index<6;index++) {
		if( genphoton[index]==true) {
			if(genphoton_pt[index]>maxPhoton_1st){
				maxPhoton_1st= genphoton_pt[index];
				pho1_index=index;
			}
		}else pho1_index=0;
		if( genjet[index]==true ) {
			if(genjet_pt[index]>maxJet_1st){
				maxJet_1st= genjet_pt[index];
			jet1_index=index;
			}
		}else jet1_index=0;
		if( genmu[index]==true ) {
			if(genmuon_pt[index]>maxMuon_1st){
				maxMuon_1st= genmuon_pt[index];
				muon1_index=index;
			}
		}else muon1_index=0;
		if( genele[index]==true ) {
			if(genelectron_pt[index]>maxEle_1st){
				maxEle_1st= genelectron_pt[index];
				ele1_index=index;
			}
		}else ele1_index=0;
	}

	for(int index=0;index<6;index++) {
		if( genphoton[index]==true) {
			if(genphoton_pt[index]>maxPhoton_2nd){
				maxPhoton_2nd= genphoton_pt[index];
				if(index==pho1_index) continue;
				pho2_index=index;
			}
		}else pho2_index=1;
		if( genjet[index]==true ) {
			if(genjet_pt[index]>maxJet_2nd){
				maxJet_2nd= genjet_pt[index];
				if(index==jet1_index) continue;
				jet2_index=index;
			}
		}else jet2_index=1; 
		if( genmu[index]==true ) {
			if(genmuon_pt[index]>maxMuon_2nd){
				maxMuon_2nd= genmuon_pt[index];
				if(index==muon1_index) continue;
				muon2_index=index;
			}
		}else muon2_index=1;
		if( genele[index]==true ) {
			if(genelectron_pt[index]>maxEle_2nd){
				maxEle_2nd= genelectron_pt[index];
				if(index==ele1_index) continue;
				ele2_index=index;
			}
		}else ele2_index=1;
	}
        if(genmuon_pid[muon1_index]==13){
                genmu_pid = genmuon_pid[muon1_index];
		genlep1pt  = genmuon_pt[muon1_index];
		genlep2pt  = genmuon_pt[muon2_index];
		genlep1eta = genmuon_eta[muon1_index]; 
		genlep2eta = genmuon_eta[muon2_index]; 
		genlep1phi = genmuon_phi[muon1_index]; 
		genlep2phi = genmuon_phi[muon2_index]; 
	}
	else {
		genlep1pt  = genelectron_pt[ele1_index];
		genlep2pt  = genelectron_pt[ele2_index];
		genlep1eta = genelectron_eta[ele1_index]; 
		genlep2eta = genelectron_eta[ele2_index]; 
		genlep1phi = genelectron_phi[ele1_index]; 
		genlep2phi = genelectron_phi[ele2_index]; 
	}

        genjet1pt  = genmuon_pt[jet1_index];
        genjet2pt  = genmuon_pt[jet2_index];
	genjet1eta = genmuon_eta[jet1_index]; 
	genjet2eta = genmuon_eta[jet2_index]; 
	genjet1phi = genmuon_phi[jet1_index]; 
	genjet2phi = genmuon_phi[jet2_index]; 

	genphotonet= genphoton_pt[pho1_index];
	genphotoneta= genphoton_eta[pho1_index];
	genphotonphi= genphoton_phi[pho1_index];

	gendrla1 = delta_R(genphotonet,genphotonphi,genlep1eta,genlep1phi);
	gendrla2 = delta_R(genphotonet,genphotonphi,genlep2eta,genlep2phi);

	gendrj1a = delta_R(genphotonet,genphotonphi,genjet1eta,genjet1phi);
	gendrj2a = delta_R(genphotonet,genphotonphi,genjet2eta,genjet2phi);

	gendrj1l1 = delta_R(genlep1eta,genlep1phi,genjet1eta,genjet1phi);
	gendrj1l2 = delta_R(genlep2eta,genlep2phi,genjet1eta,genjet1phi);
	gendrj2l1 = delta_R(genlep1eta,genlep1phi,genjet2eta,genjet2phi);
	gendrj2l2 = delta_R(genlep2eta,genlep2phi,genjet2eta,genjet2phi);

	TLorentzVector j1p4;
	j1p4.SetPtEtaPhiE(genjet1pt, genjet1eta, genjet1phi, genjet1e);
	TLorentzVector j2p4;
	j2p4.SetPtEtaPhiE(genjet2pt, genjet2eta, genjet2phi, genjet2e);
	TLorentzVector photonp42;
	photonp42.SetPtEtaPhiM(genphotonet, genphotoneta, photonphi,0);
	TLorentzVector vp4;
	vp4.SetPtEtaPhiM(ptVlep,yVlep,phiVlep,massVlep);
	genMjj=(j1p4 + j2p4).M();
	genzepp = fabs((vp4+photonp42).Rapidity() - (j1p4.Rapidity() + j2p4.Rapidity())/ 2.0);
	gendetajj = fabs(genjet1eta - genjet2eta);
        TLorentzVector Zp4;
	Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
	gendelta_phi=fabs((Zp4+photonp42).Phi()-(j1p4+j2p4).Phi());
	genZGmass=(Zp4+photonp42).M();
	if (gendelta_phi>Pi) gendelta_phi=2*Pi-gendelta_phi;
//	cout<<genlep1pt<<" "<<genlep2pt<<endl;
//	cout<<muon1_index<<" "<<muon2_index<<" "<<endl;
//	cout<<ele1_index<<" "<<ele2_index<<" "<<endl;
	cout<<genphoton_pt[pho1_index]<<" "<<genphoton_pt[pho2_index]<<endl;
        cout<<genmuon_pt[muon1_index]<<" "<<genmuon_pt[muon2_index]<<endl;
}
void rm::ResetValue(){

	genlep1pt=-10,genlep2pt=-10,genlep1eta=-10,genlep2eta=-10,genlep1phi=-10,genlep2phi=-10;
	genmu_pid=-10;
	genjet1pt=-10,genjet2pt=-10,genjet1eta=-10,genjet2eta=-10,genjet1phi=-10,genjet2phi=-10;
	genjet1e=-10;genjet2e=-10;
	genphotonet=-10,genphotoneta=-10,genphotonphi=-10;
	gendrj1a=-10,gendrj2a=-10,gendrj1l1=-10,gendrj1l2=-10,gendrj2l1=-10,gendrj2l2=-10;
	genMjj=-10,gendetajj=-10,genzepp=-10,gendelta_phi=-10,genZGmass=-10;
	gendrla1=-10,gendrla2=-10;
	for(int i=0;i<6;i++){
		genmu[i]=false;
		genele[i]=false;
                genphoton[i]=false;
		genjet[i]=false;
	}
}

