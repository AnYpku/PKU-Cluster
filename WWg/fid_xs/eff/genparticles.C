#include "TLorentzVector.h"
#define pi 3.1415926
#include "WWg.h"
#include <iostream>
#include <vector>

using namespace std;

struct myclass {
  bool operator() (double i,double j) { return (i>j);}
} myobject;

Double_t delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{
        Double_t dp = phi1-phi2;
        if(std::fabs(dp) > pi) dp = 2*pi - std::fabs(dp);
        Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}

void WWg::genparticles(){
        TLorentzVector lep1p4,lep2p4;
	TLorentzVector photonp4;
	TLorentzVector vp4;

//      cout<<"nGenDressedLepton "<<nGenDressedLepton<<endl;
	if(nGenDressedLepton<=1) gen_channel=-10;
	if(nGenDressedLepton==2 && GenDressedLepton_pdgId[0]*GenDressedLepton_pdgId[1]<0 && fabs(GenDressedLepton_pdgId[0])!=fabs(GenDressedLepton_pdgId[1])){
		gen_channel=1;
		if(fabs(GenDressedLepton_pdgId[0])==11){
			lep2p4.SetPtEtaPhiM(GenDressedLepton_pt[0], GenDressedLepton_eta[0], GenDressedLepton_phi[0], 0.00051);
			lep1p4.SetPtEtaPhiM(GenDressedLepton_pt[1], GenDressedLepton_eta[1], GenDressedLepton_phi[1], 0.105666);
		}
		else{
			lep1p4.SetPtEtaPhiM(GenDressedLepton_pt[0], GenDressedLepton_eta[0], GenDressedLepton_phi[0], 0.105666);
			lep2p4.SetPtEtaPhiM(GenDressedLepton_pt[1], GenDressedLepton_eta[1], GenDressedLepton_phi[1], 0.00051);
		}
	}
	if(gen_channel==1){
		genlep1    = 13;
		genlep1pt  = lep1p4.Pt();
		genlep1eta = lep1p4.Eta();
		genlep1phi = lep1p4.Phi();

		genlep2    = 11;
		genlep2pt  = lep2p4.Pt();
		genlep2eta = lep2p4.Eta();
		genlep2phi = lep2p4.Phi();
	}

	//cout<<gen_channel<<" "<<genlep1<<" "<<genlep2<<" "<<genlep1pt<<" "<<genlep1eta<<" "<<genlep2pt<<" "<<genlep2eta<<endl; 
	genyVlep  =(lep1p4+lep2p4).Eta();
	genphiVlep=(lep1p4+lep2p4).Phi();
	genptll =(lep1p4+lep2p4).Pt();
	genmll=(lep1p4+lep2p4).M();
	gendrll=delta_R(genlep2eta,genlep2phi,genlep1eta,genlep1phi);
	//cout<<"dilep: "<<genptll<<" "<<genmll<<" "<<gendrll<<endl;
	vp4.SetPtEtaPhiM(genptll,genyVlep,genphiVlep,genmll);

	//cout<<"nGenIsolatedPhoton "<<nGenIsolatedPhoton<<endl;
	int gen_nphoton=0;
	for(int i=0;i<nGenIsolatedPhoton;i++){
		//cout<<"test"<<endl;
                if(GenIsolatedPhoton_pt[i]<20) continue;
		if(fabs(GenIsolatedPhoton_eta[i])>2.5) continue;
		double dr1 = delta_R(GenIsolatedPhoton_eta[i],GenIsolatedPhoton_phi[i],genlep1eta,genlep1phi);
		double dr2 = delta_R(GenIsolatedPhoton_eta[i],GenIsolatedPhoton_phi[i],genlep2eta,genlep2phi);
		if( !(dr1 > 0.5 && dr2>0.5) ) continue;
		gen_nphoton++;
		if(gen_nphoton>0){
			photonp4.SetPtEtaPhiM(GenIsolatedPhoton_pt[i], GenIsolatedPhoton_eta[i],GenIsolatedPhoton_phi[i],0);
			break;
		}
	}
	//cout<<"pho test"<<gen_nphoton<<endl;
	if(gen_nphoton>0){
		genphotonet= photonp4.Pt();
		genphotoneta= photonp4.Eta();
		genphotonphi= photonp4.Phi();
		gendrl1a = delta_R(genphotoneta,genphotonphi,genlep1eta,genlep1phi);
		gendrl2a = delta_R(genphotoneta,genphotonphi,genlep2eta,genlep2phi);
		genmllg=(vp4+photonp4).M();
		//cout<<"gendrla "<<gendrl1a<<" "<<gendrl2a<<endl;
	}
	//cout<<"pho: "<<gen_nphoton<<" "<<genphotonet<<" "<<genphotoneta<<" "<<gendrl1a<<" "<<gendrl2a <<endl;
	bool pass_dr=true;
	//cout<<"nGenJet "<<nGenJet<<endl;
	for(Int_t i=0; i<nGenJet; i++)
	{
		if(fabs(GenJet_eta[i])>4.7) continue;
		if(genphoton>0)
			pass_dr=delta_R(GenJet_eta[i], GenJet_phi[i], genphotoneta,genphotonphi)>0.5;
		if( delta_R(GenJet_eta[i], GenJet_phi[i],genlep1eta,genlep1phi)<0.5) pass_dr=false;
		if( delta_R(GenJet_eta[i], GenJet_phi[i],genlep2eta,genlep2phi)<0.5) pass_dr=false;
		if( ! pass_dr)  continue;
		n_genjets++;
		if(GenJet_pt[i]>15)  n_genjets15++;
		if(GenJet_pt[i]>20)  n_genjets20++;
		if(GenJet_pt[i]>30)  n_genjets30++;
		if(GenJet_pt[i]>40)  n_genjets40++;
		if(GenJet_pt[i]>50)  n_genjets50++;
		if(fabs(GenJet_partonFlavour[i])==5 && GenJet_pt[i]>20) n_genbjets++;
	}

}
void WWg::ResetValue(){

	genlep1pt=-10;genlep2pt=-10;genlep1eta=-10;genlep2eta=-10;genlep1phi=-10;genlep2phi=-10;
	genphotonet=-10;genphotoneta=-10;genphotonphi=-10;
	genmll=-10;genyVlep=-10;genphiVlep=-10;genptll=-10;
	gendrl1a=-10;gendrl2a=-10;gendrll=10;genmllg=-10;
	genlep1=-10;genlep2=-10;gen_channel=-10;
	n_genjets15=0;n_genjets20=0;n_genjets30=0;n_genjets40=0;n_genjets50=0;n_genbjets=0;
}

