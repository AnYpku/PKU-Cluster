#include "TLorentzVector.h"
#define Pi 3.1415926
#include "xx.h"
#include <iostream>

using namespace std;

Double_t delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{
	Double_t dp = phi1-phi2;
	if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
	Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
	return dr;
}

void xx::modify_photon_jets()
{
	//set dummy value
	iphoton=-1;
	photonet=-99;
    photoneta=-99;
    photonphi=-99;
    photone=-99;
    photonsieie=-99;
    photonphoiso=-99;
    photonchiso=-99;
    photonnhiso=-99;
    drla=-99;
    drla2=-99;
    Mla=-99;
    Mla2=-99;
    Mva=-99;
	jet1pt=-99;
	jet1eta=-99;
	jet1phi=-99;
	jet1e=-99;
	jet2pt=-99;
	jet2eta=-99;
	jet2phi=-99;
	jet2e=-99;
	jet1csv =-99;
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
	
	for (Int_t ip = 0; ip < 6; ip++)
	{
	Int_t isfake_medium = 0;
	//barrel 2016
//	if(/*chiso invert*/(photon_sieie[ip]<0.01022 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.0396 && photon_chiso[ip]>1.295 && photon_chiso[ip]<std::min(0.2*photon_pt[ip], 5.*1.295) && photon_nhiso[ip]<(2.725 + 0.0148*photon_pt[ip]+0.000017*photon_pt[ip]*photon_pt[ip]) && photon_phoiso[ip]<(2.571+0.0047*photon_pt[ip])) || 
//	  (/*sieie invert*/photon_sieie[ip]>0.01031 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.0396 && photon_chiso[ip]<0.441 && photon_nhiso[ip]<(2.725 + 0.0148*photon_pt[ip]+0.000017*photon_pt[ip]*photon_pt[ip]) && photon_phoiso[ip]<(2.571+0.0047*photon_pt[ip])) || 
//	  (/*nhiso invert*/photon_sieie[ip]<0.01022 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.0396 && photon_chiso[ip]<0.441 && photon_nhiso[ip]>(10.91 + 0.0148*photon_pt[ip]+0.000017*photon_pt[ip]*photon_pt[ip]) && photon_nhiso[ip] < std::min(0.2*photon_pt[ip], 5.*(10.91 + 0.0148*photon_pt[ip]+0.000017*photon_pt[ip]*photon_pt[ip])) && photon_phoiso[ip]<(2.571+0.0047*photon_pt[ip])) ||
//	  (/*phoiso invert*/photon_sieie[ip]<0.01022 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.0396 && photon_chiso[ip]<0.441 && photon_nhiso[ip]<(2.725 + 0.0148*photon_pt[ip]+0.000017*photon_pt[ip]*photon_pt[ip]) && photon_phoiso[ip]>(3.630+0.0047*photon_pt[ip]) && photon_phoiso[ip]<std::min(0.2*photon_pt[ip], 5.*(3.630+0.0047*photon_pt[ip])))) isfake_medium=1;
//
	if(/*chiso invert*/(photon_sieie[ip]<0.01015 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.02197 &&photon_chiso[ip]>1.694 && photon_chiso[ip]<std::min(0.2*photon_pt[ip], 5.*1.694) && photon_nhiso[ip]<(1.189 + (0.01512*photon_pt[ip]+0.00002259*photon_pt[ip]*photon_pt[ip])) && photon_phoiso[ip]<(2.08+0.004017*photon_pt[ip]))||
	(/*sieie invert*/photon_sieie[ip]>0.0106 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.02197 &&photon_chiso[ip]<1.141 && photon_nhiso[ip]<(1.189 + (0.01512*photon_pt[ip]+0.00002259*photon_pt[ip]*photon_pt[ip])) && photon_phoiso[ip]<(2.08+0.004017*photon_pt[ip])) ||
	(/*nhiso invert*/photon_sieie[ip]<0.01015 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.02197 &&photon_chiso[ip]<1.141 && photon_nhiso[ip]>(24.032 + (0.01512*photon_pt[ip]+0.00002259*photon_pt[ip]*photon_pt[ip]))&&photon_nhiso[ip] < std::min(0.2*photon_pt[ip], 5.*(24.032 + 0.01512*photon_pt[ip]+0.00002259*photon_pt[ip]*photon_pt[ip])) && photon_phoiso[ip]<(2.08+0.004017*photon_pt[ip])) ||
	(/*phoiso invert*/photon_sieie[ip]<0.01015 && photon_pev[ip] && fabs(photon_eta[ip])<1.4442 && photon_hoe[ip]<0.02197 &&photon_chiso[ip]<1.141 && photon_nhiso[ip]<(1.189 + (0.01512*photon_pt[ip]+0.00002259*photon_pt[ip]*photon_pt[ip])) && photon_phoiso[ip]<(2.876+0.004017*photon_pt[ip])&& std::min(0.2*photon_pt[ip], 5.*(2.876+0.004017*photon_pt[ip]))  ))isfake_medium=1; 
	// endcap
	if(/*chiso invert*/(photon_sieie[ip]<0.0272 && photon_pev[ip] && fabs(photon_eta[ip])>1.566 && fabs(photon_eta[ip])<2.5 && photon_hoe[ip]<0.0326 && photon_chiso[ip]>2.089 && photon_chiso[ip]<std::min(0.2*photon_pt[ip], 5.*2.089) && photon_nhiso[ip]<(2.718+0.0117*photon_pt[ip]+0.000023*photon_pt[ip]*photon_pt[ip]) && photon_phoiso[ip]<(3.867+0.0037*photon_pt[ip])) || 
          (/*sieie invert*/photon_sieie[ip]>0.0272 && photon_pev[ip] && fabs(photon_eta[ip])>1.566 && fabs(photon_eta[ip])<2.5 && photon_hoe[ip]<0.0326 && photon_chiso[ip]<1.051 && photon_nhiso[ip]<(2.718+0.0117*photon_pt[ip]+0.000023*photon_pt[ip]*photon_pt[ip]) && photon_phoiso[ip]<(3.867+0.0037*photon_pt[ip])) || 
          (/*nhiso invert*/photon_sieie[ip]<0.0272 && photon_pev[ip] && fabs(photon_eta[ip])>1.566 && fabs(photon_eta[ip])<2.5 && photon_hoe[ip]<0.0326 && photon_chiso[ip]<1.051 && photon_nhiso[ip]>(19.722+0.0117*photon_pt[ip]+0.000023*photon_pt[ip]*photon_pt[ip]) && photon_nhiso[ip] < std::min(0.2*photon_pt[ip], 5.*(19.722+0.0117*photon_pt[ip]+0.000023*photon_pt[ip]*photon_pt[ip])) && photon_phoiso[ip]<(3.867+0.0037*photon_pt[ip])) || 
          (/*phoiso invert*/photon_sieie[ip]<0.0272 && photon_pev[ip] && fabs(photon_eta[ip])>1.566 && fabs(photon_eta[ip])<2.5 && photon_hoe[ip]<0.0326 && photon_chiso[ip]<1.051 && photon_nhiso[ip]<(2.718+0.0117*photon_pt[ip]+0.000023*photon_pt[ip]*photon_pt[ip]) && photon_phoiso[ip]>(4.162+0.0037*photon_pt[ip]) && photon_phoiso[ip]<std::min(0.2*photon_pt[ip], 5.*(4.162+0.0037*photon_pt[ip])))) isfake_medium=1;

	if(isfake_medium==1 && delta_R(photon_eta[ip], photon_phi[ip], etalep1, philep1) > 0.7 && delta_R(photon_eta[ip], photon_phi[ip], etalep2, philep2) > 0.7)
	{
	if(ip==0) {photonet=photon_pt[ip]; iphoton=ip;}
	if(photon_pt[ip]>photonet) {
	photonet=photon_pt[ip]; iphoton=ip; }
	}	
//	if(ak4jet_pt[ip]>30 && fabs(ak4jet_eta[ip])<4.7) ijet++;
	}
	if(iphoton>-1/*&& (jet_flag==true)*/ ){	
	photonet=photon_pt[iphoton];
	photoneta=photon_eta[iphoton];
	photonphi=photon_phi[iphoton];
	photone=photon_e[iphoton];
	photonsieie=photon_sieie[iphoton];
	photonphoiso=photon_phoiso[iphoton];
	photonchiso=photon_chiso[iphoton];
	photonnhiso=photon_nhiso[iphoton];
	drla=delta_R(photon_eta[iphoton],photon_phi[iphoton],etalep1,philep1);
	drla2=delta_R(photon_eta[iphoton],photon_phi[iphoton],etalep2,philep2);
	TLorentzVector photonp4;
	photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
	TLorentzVector  glepton;
	glepton.SetPtEtaPhiM(ptlep1, etalep1, philep1, 0.0005);
	TLorentzVector  glepton2;
	glepton2.SetPtEtaPhiE(ptlep2, etalep2, philep2, 0.0005);
	Mla=(photonp4+glepton).M();
	Mla2=(photonp4+glepton2).M();
	TLorentzVector wp4;
	wp4.SetPtEtaPhiM(ptVlep,yVlep,phiVlep,massVlep);;
	Mva=(photonp4+wp4).M();
        Int_t jetindexphoton12[2] = {-1,-1};
        for(Int_t i=0; i<6; i++)
        {
                if(iphoton>-1){
                        double drtmp1=delta_R(ak4jet_eta[i], ak4jet_phi[i], photoneta,photonphi);
                        if(ak4jet_pt[i]>0 && drtmp1>0.5) {
                           ak4jet_pt[i] = ak4jet_pt[i];
                        }
                        else ak4jet_pt[i] = 0; 
                }
        }
	int jet1_index,jet2_index;
	double maxPt_1st=0,maxPt_2nd=0;
	for(int ijet=0; ijet< 6 ;ijet++) {
		if(ak4jet_pt[ijet]>maxPt_1st) {
			maxPt_1st= ak4jet_pt[ijet];
			jet1_index=ijet;
		}
	}
	for(int ijet=0; ijet< 6 ;ijet++) {
                if(ijet==jet1_index) continue;
		if(ak4jet_pt[ijet]>maxPt_2nd) {
			maxPt_2nd= ak4jet_pt[ijet];
			jet2_index=ijet;
		}
	}
	jetindexphoton12[0] = jet1_index;
        jetindexphoton12[1] = jet2_index;
	if(jetindexphoton12[0]>-1 && jetindexphoton12[1]>-1) 
	{
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
}
