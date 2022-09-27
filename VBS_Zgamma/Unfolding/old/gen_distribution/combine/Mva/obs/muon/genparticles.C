#include "TLorentzVector.h"
#define Pi 3.1415926
#include "rm.h"
#include <iostream>
#include <vector>

using namespace std;

struct myclass {
  bool operator() (double i,double j) { return (i>j);}
} myobject;
Double_t delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{
        Double_t dp = phi1-phi2;
        if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
        Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}
void rm::genparticles(){
	int pho1_index=0,jet1_index=0,muon1_index=0,ele1_index=0;
	int pho2_index=1,jet2_index=1,muon2_index=1,ele2_index=1;
        TLorentzVector lep1p4,lep2p4;
	TLorentzVector photonp42;
	TLorentzVector vp4;

        for(int i=0;i<6;i++){
                genphoton[i] = genphoton_pt[i]>20 &&( (fabs(genphoton_eta[i])<1.4442) || ( fabs(genphoton_eta[i])<2.5 && fabs(genphoton_eta[i])>1.566 ) );
                genjet[i] = genjet_pt[i]>30 && fabs(genjet_eta[i])<4.7;
                genmuon[i] = fabs(genmuon_pid[i])==13 && genmuon_pt[i]>20 && fabs(genmuon_eta[i])<2.4;
                genele[i] = fabs(genmuon_pid[i])!=13 && genelectron_pt[i]>25 && fabs(genelectron_eta[i])<2.5;

		if(genjet[i]) vector_jet.push_back(genjet_pt[i]);
		else vector_jet.push_back(0);

		if(genphoton[i]) vector_photon.push_back(genphoton_pt[i]);
		else vector_photon.push_back(0);

		if(genmuon[i]) vector_muon.push_back(genmuon_pt[i]);
		else vector_muon.push_back(0);

		if(genele[i]) vector_ele.push_back(genelectron_pt[i]);
		else vector_ele.push_back(0);
	}
   //muon1_index
	biggest_muon1=max_element(begin(vector_muon),end(vector_muon));
	muon1_index = distance( begin(vector_muon), biggest_muon1);
//	cout<<*biggest_muon1<<endl;
        if(*biggest_muon1>0){
		genlep1pt  = genmuon_pt[muon1_index];
		genlep1eta = genmuon_eta[muon1_index]; 
		genlep1phi = genmuon_phi[muon1_index]; 
		lep1p4.SetPtEtaPhiM(genlep1pt, genlep1eta, genlep1phi, 0.105666);
	}
        cout<<"muon1 "<<*biggest_muon1<<" "<<genmuon_pid[muon1_index]<<endl;
   //muon2_index
        vector_muon[muon1_index] = 0;
        biggest_muon2=max_element(begin(vector_muon),end(vector_muon));
	muon2_index = distance( begin(vector_muon), biggest_muon2);
	if(*biggest_muon2>0){
		genlep2pt  = genmuon_pt[muon2_index];
		genlep2eta = genmuon_eta[muon2_index]; 
		genlep2phi = genmuon_phi[muon2_index]; 
		lep2p4.SetPtEtaPhiM(genlep2pt, genlep2eta, genlep2phi, 0.105666);
	}        
//        cout<<genlep1pt<<" "<<genlep1eta<<" "<<genlep2pt<<" "<<genlep2eta<<endl; 
        cout<<"muon2 "<<*biggest_muon2<<" "<<genmuon_pid[muon2_index]<<endl;
   //ele1_index
      /*biggest_ele1=max_element(begin(vector_ele),end(vector_ele));
        if(*biggest_ele1==0){
		genlep1pt  = -10;
		genlep1eta = -10; 
		genlep1phi = -10; 
	} 
	else{ 
		ele1_index = distance( begin(vector_ele), biggest_ele1);
		genlep1pt  = genelectron_pt[ele1_index];
		genlep1eta = genelectron_eta[ele1_index]; 
		genlep1phi = genelectron_phi[ele1_index]; 
		lep1p4.SetPtEtaPhiM(genele1pt, genele1eta, genele1phi, 0.00051);
	}
   //ele2_index
        vector_ele[ele1_index] = 0;
        biggest_ele2=max_element(begin(vector_ele),end(vector_ele));
	if(*biggest_ele2==0){ 
		genele2pt  = -10;
		genele2eta = -10; 
		genele2phi = -10; 
	}
        else{
		ele2_index = distance( begin(vector_ele), biggest_ele2);
		genlep2pt  = genelectron_pt[ele2_index];
		genlep2eta = genelectron_eta[ele2_index]; 
		genlep2phi = genelectron_phi[ele2_index]; 
		lep2p4.SetPtEtaPhiM(genele2pt, genele2eta, genele2phi, 0.00051);
	}*/
	genyVlep  =(lep1p4+lep2p4).Eta();
	genphiVlep=(lep1p4+lep2p4).Phi();
	genptVlep =(lep1p4+lep2p4).Pt();
	genmassVlep=(lep1p4+lep2p4).M();
	vp4.SetPtEtaPhiM(genptVlep,genyVlep,genphiVlep,genmassVlep);
   //pho1_index 
        biggest_photon=max_element(begin(vector_photon),end(vector_photon));
        if(*biggest_photon>0){
		pho1_index = distance( begin(vector_photon), biggest_photon);
		genphotonet= genphoton_pt[pho1_index];
		genphotoneta= genphoton_eta[pho1_index];
		genphotonphi= genphoton_phi[pho1_index];
		photonp42.SetPtEtaPhiM(genphotonet, genphotoneta, photonphi,0);
		genZGmass=(vp4+photonp42).M();
		gendrla1 = delta_R(genphotoneta,genphotonphi,genlep1eta,genlep1phi);
		gendrla2 = delta_R(genphotoneta,genphotonphi,genlep2eta,genlep2phi);
	
		Int_t jetindexphoton12[2] = {-1,-1};
		for(Int_t i=0; i<6; i++)
		{
			if(genphotonet>0){
				double drtmp1=delta_R(genjet_eta[i], genjet_phi[i], genphotoneta,genphotonphi);
				double drjlep1 = delta_R(genjet_eta[i], genjet_phi[i],genlep1eta,genlep1phi);
				double drjlep2 = delta_R(genjet_eta[i], genjet_phi[i],genlep2eta,genlep2phi);
				if(genjet_pt[i]>0 && drtmp1>0.5 && drjlep1>0.5 && drjlep2>0.5 && jetindexphoton12[0]==-1&&jetindexphoton12[1]==-1) {
					jetindexphoton12[0] = i;
					continue;
				}
				if(genjet_pt[i]>0 && drtmp1>0.5 && drjlep1>0.5 && drjlep2>0.5 && jetindexphoton12[0]!=-1&&jetindexphoton12[1]==-1) {
					jetindexphoton12[1] = i;
					continue;
				}
			}
		}

		if(jetindexphoton12[0]>-1 && jetindexphoton12[1]>-1)
		{
			genjet1pt  = genjet_pt[jetindexphoton12[0]];
			genjet1eta = genjet_eta[jetindexphoton12[0]];
			genjet1phi = genjet_phi[jetindexphoton12[0]];
			genjet1e   = genjet_e[jetindexphoton12[0]];
			genjet2pt  = genjet_pt[jetindexphoton12[1]];
			genjet2eta = genjet_eta[jetindexphoton12[1]];
			genjet2phi = genjet_phi[jetindexphoton12[1]];
			genjet2e   = genjet_e[jetindexphoton12[1]];
			gendrj1a= delta_R(genjet1eta,genjet1phi,genphotoneta,genphotonphi);
			gendrj2a= delta_R(genjet2eta,genjet2phi,genphotoneta,genphotonphi);
			gendrj1l= delta_R(genjet1eta,genjet1phi,genlep1eta,genlep1phi);
			gendrj2l= delta_R(genjet2eta,genjet2phi,genlep1eta,genlep1phi);
			gendrj1l2=delta_R(genjet1eta,genjet1phi,genlep2eta,genlep2phi);
			gendrj2l2=delta_R(genjet2eta,genjet2phi,genlep2eta,genlep2phi);
			TLorentzVector j1p4;
			j1p4.SetPtEtaPhiE(genjet1pt, genjet1eta, genjet1phi, genjet1e);
			TLorentzVector j2p4;
			j2p4.SetPtEtaPhiE(genjet2pt, genjet2eta, genjet2phi, genjet2e);
			TLorentzVector photonp4;
			photonp4.SetPtEtaPhiM(genphotonet, genphotoneta, genphotonphi, 0);
			TLorentzVector vp4;
			vp4.SetPtEtaPhiM(genptVlep,genyVlep,genphiVlep,genmassVlep);
			genMjj=(j1p4 + j2p4).M();
			genzepp = fabs((vp4+photonp4).Rapidity() - (j1p4.Rapidity() + j2p4.Rapidity())/ 2.0);
			gendetajj = fabs(genjet1eta - genjet2eta);
			gendelta_phi=fabs((vp4+photonp4).Phi()-(j1p4+j2p4).Phi());
			if (gendelta_phi>Pi) gendelta_phi=2*Pi-gendelta_phi;
			if (fabs(genjet1phi-genjet2phi)>Pi) gendrjj = sqrt((genjet1eta-genjet2eta)*(genjet1eta-jet2eta)+(2*Pi-fabs(genjet1phi-genjet2phi))*(2*Pi-fabs(genjet1phi-genjet2phi)));
			else gendrjj = sqrt((genjet1eta-genjet2eta)*(genjet1eta-genjet2eta)+(fabs(genjet1phi-genjet2phi))*(fabs(genjet1phi-genjet2phi)));
		}
	}
	if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
	else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));
	vector_photon.clear();
	vector_jet.clear();
        vector_muon.clear();
        vector_ele.clear();
}
void rm::ResetValue(){

	genlep1pt=-10;genlep2pt=-10;genlep1eta=-10;genlep2eta=-10;genlep1phi=-10;genlep2phi=-10;
	genjet1pt=-10;genjet2pt=-10;genjet1eta=-10;genjet2eta=-10;genjet1phi=-10;genjet2phi=-10;
	genjet1e=-10;genjet2e=-10;
	genphotonet=-10;genphotoneta=-10;genphotonphi=-10;
	gendrj1a=-10;gendrj2a=-10;gendrj1l=-10;gendrj2l=-10;gendrj1l2=-10;gendrj2l2=-10;
        gendrla1=-10;gendrla2=-10;
	genMjj=-10;gendetajj=-10;genzepp=-10;gendelta_phi=-10;genZGmass=-10;
        genmassVlep=-10;genyVlep=-10;genphiVlep=-10;genptVlep=-10;
        genlep=-10;gendrjj=-10;drjj=-10;
	genmuon1pt=-10;genmuon2pt=-10;genmuon1eta=-10;genmuon2eta=-10;genmuon1phi=-10;genmuon2phi=-10;
	genele1pt=-10;genele2pt=-10;genele1eta=-10;genele2eta=-10;genele1phi=-10;genele2phi=-10;
        GenDrmu=false;GenDrele=false;Genmu=false;Genele=false;
	for(int i=0;i<6;i++){
		genmuon[i]=false;
		genele[i]=false;
                genphoton[i]=false;
		genjet[i]=false;
	}
}

