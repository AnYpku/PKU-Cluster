#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"

double large(double a1, double a2){
	if(a1>a2) return a1;
	else return a2;
	}

void gen(){
//	TFile*file_in = TFile::Open("/eos/uscms/store/user/mlu/ZAjj-more-HLT/AddWeight_step2/outZA.root");
	TFile*file_in = TFile::Open("./outZA-EWK.root");
	TTree*tree_in = (TTree*)file_in->Get("demo");
//	std::ofstream myfile("output.txt",std::ofstream::out);
 
	Double_t	scalef; 
	Int_t	nVtx;
	Double_t	theWeight;
	Double_t	lumiWeight;
	Double_t	pileupWeight;
	Double_t	l1_weight;
	Int_t	lep;
	Double_t	ptVlep;
	Double_t	yVlep;
	Double_t	phiVlep;
	Double_t	massVlep;
	Double_t	Mva;
	Double_t	ptlep1;
	Double_t	etalep1;
	Double_t	philep1;
	Double_t	ptlep2;
	Double_t	etalep2;
	Double_t	philep2;
	Double_t	drla;
	Double_t	drla2;
	Int_t	nlooseeles;
	Double_t	drj1a;
	Double_t	drj2a;
	Double_t	drj1l;
	Double_t	drj2l;
	Double_t	drj1l2;
	Double_t	drj2l2;
	Int_t	nloosemus;
	Double_t	MET_et;
	Double_t	photonet;
	Double_t	photoneta;
	Double_t	photonphi;
	Double_t	photone;
	Int_t	isprompt;
	Double_t	jet1pt;
	Double_t	jet1eta;
	Double_t	jet1phi;
	Double_t	jet1e;
	Double_t	jet2pt;
	Double_t	jet2eta;
	Double_t	jet2phi;
	Double_t	jet2e;
	Double_t	Mjj;
	Double_t	zepp;
	Double_t	deltaetajj;
	Double_t	genphoton_pt[6] ;
	Double_t	genphoton_eta[6];
	Double_t	genphoton_phi[6];
	Double_t	genjet_pt[6];
	Double_t	genjet_eta[6];
	Double_t	genjet_phi[6];
	Double_t	genjet_e[6];
	Double_t	genmuon_pt[6];
	Double_t	genmuon_eta[6];
	Double_t	genmuon_phi[6];
	Double_t	genelectron_pt[6];  
	Double_t	genelectron_eta[6]; 
	Double_t	genelectron_phi[6] ;
	Double_t	ele1_id_scale;
	Double_t	ele2_id_scale;
	Double_t	ele1_reco_scale;
	Double_t	ele2_reco_scale;
	Double_t	photon_id_scale;
	Double_t	muon1_id_scale;
	Double_t	muon2_id_scale;
	Double_t	muon1_iso_scale;
	Double_t	muon2_iso_scale;
	Double_t	muon1_track_scale;
	Double_t	muon2_track_scale;
	Double_t	muon_hlt_scale;

	tree_in->SetBranchAddress("scalef", &scalef); 
	tree_in->SetBranchAddress("nVtx",&nVtx);
	tree_in->SetBranchAddress("theWeight",&theWeight);
	tree_in->SetBranchAddress("lumiWeight",&lumiWeight);
	tree_in->SetBranchAddress("pileupWeight",&pileupWeight);
	tree_in->SetBranchAddress("l1_weight",&l1_weight);
	tree_in->SetBranchAddress("lep",&lep);
	tree_in->SetBranchAddress("ptVlep",&ptVlep);
	tree_in->SetBranchAddress("yVlep",&yVlep);
	tree_in->SetBranchAddress("phiVlep",&phiVlep);
	tree_in->SetBranchAddress("massVlep",&massVlep);
	tree_in->SetBranchAddress("Mva",&Mva);
	tree_in->SetBranchAddress("ptlep1",&ptlep1);
	tree_in->SetBranchAddress("etalep1",&etalep1);
	tree_in->SetBranchAddress("philep1",&philep1);
	tree_in->SetBranchAddress("ptlep2",&ptlep2);
	tree_in->SetBranchAddress("etalep2",&etalep2);
	tree_in->SetBranchAddress("philep2",&philep2);
	tree_in->SetBranchAddress("drla",&drla);
	tree_in->SetBranchAddress("drla2",&drla2);
	tree_in->SetBranchAddress("nlooseeles",&nlooseeles);
	tree_in->SetBranchAddress("drj1a",&drj1a);
	tree_in->SetBranchAddress("drj2a",&drj2a);
	tree_in->SetBranchAddress("drj1l",&drj1l);
	tree_in->SetBranchAddress("drj2l",&drj2l);
	tree_in->SetBranchAddress("drj1l2",&drj1l2);
	tree_in->SetBranchAddress("drj2l2",&drj2l2);
	tree_in->SetBranchAddress("nloosemus",&nloosemus);
	tree_in->SetBranchAddress("MET_et",&MET_et);
	tree_in->SetBranchAddress("photonet",&photonet);
	tree_in->SetBranchAddress("photoneta",&photoneta);
	tree_in->SetBranchAddress("photonphi",&photonphi);
	tree_in->SetBranchAddress("photone",&photone);
	tree_in->SetBranchAddress("isprompt",&isprompt);
	tree_in->SetBranchAddress("jet1pt",&jet1pt);
	tree_in->SetBranchAddress("jet1eta",&jet1eta);
	tree_in->SetBranchAddress("jet1phi",&jet1phi);
	tree_in->SetBranchAddress("jet1e",&jet1e);
	tree_in->SetBranchAddress("jet2pt",&jet2pt);
	tree_in->SetBranchAddress("jet2eta",&jet2eta);
	tree_in->SetBranchAddress("jet2phi",&jet2phi);
	tree_in->SetBranchAddress("jet2e",&jet2e);
	tree_in->SetBranchAddress("Mjj",&Mjj);
	tree_in->SetBranchAddress("zepp",&zepp);
	tree_in->SetBranchAddress("deltaetajj",&deltaetajj);
	tree_in->SetBranchAddress("genphoton_pt",genphoton_pt);
	tree_in->SetBranchAddress("genphoton_eta",genphoton_eta);
	tree_in->SetBranchAddress("genphoton_phi",genphoton_phi);
	tree_in->SetBranchAddress("genjet_pt",genjet_pt);
	tree_in->SetBranchAddress("genjet_eta",genjet_eta);
	tree_in->SetBranchAddress("genjet_phi",genjet_phi);
	tree_in->SetBranchAddress("genjet_e",genjet_e);
	tree_in->SetBranchAddress("genmuon_pt",genmuon_pt);
	tree_in->SetBranchAddress("genmuon_eta",genmuon_eta);
	tree_in->SetBranchAddress("genmuon_phi",genmuon_phi);
	tree_in->SetBranchAddress("genelectron_pt",genelectron_pt);  
	tree_in->SetBranchAddress("genelectron_eta",genelectron_eta); 
	tree_in->SetBranchAddress("genelectron_phi",genelectron_phi);
	tree_in->SetBranchAddress("ele1_id_scale",&ele1_id_scale);
	tree_in->SetBranchAddress("ele2_id_scale",&ele2_id_scale);
	tree_in->SetBranchAddress("ele1_reco_scale",&ele1_reco_scale);
	tree_in->SetBranchAddress("ele2_reco_scale",&ele2_reco_scale);
	tree_in->SetBranchAddress("photon_id_scale",&photon_id_scale);
	tree_in->SetBranchAddress("muon1_id_scale",&muon1_id_scale);
	tree_in->SetBranchAddress("muon2_id_scale",&muon2_id_scale);
	tree_in->SetBranchAddress("muon1_iso_scale",&muon1_iso_scale);
	tree_in->SetBranchAddress("muon2_iso_scale",&muon2_iso_scale);
	tree_in->SetBranchAddress("muon1_track_scale",&muon1_track_scale);
	tree_in->SetBranchAddress("muon2_track_scale",&muon2_track_scale);
	tree_in->SetBranchAddress("muon_hlt_scale",&muon_hlt_scale);
	
	Long64_t nentries=tree_in->GetEntries();
	double yields=0.;
	double yields_e_b=0.;
	double yields_e_e=0.;
	double yields_m_b=0.;
	double yields_m_e=0.;
	TLorentzVector j1, j2, l1, l2, photon_p4;
	int plus_e=0;
	int minus_e=0;
	int plus_m=0;
	int minus_m=0;
	double ZGmass=-1.;
	for(Long64_t i=0;i<nentries;i++){
		ZGmass=-1.;
		j1.SetPtEtaPhiE(0,0,0,0);
		j2.SetPtEtaPhiE(0,0,0,0);
		l1.SetPtEtaPhiE(0,0,0,0);
		l2.SetPtEtaPhiE(0,0,0,0);
		photon_p4.SetPtEtaPhiE(0,0,0,0);
		int lep=-1;
		if(i%10000==0) std::cout<<i<<std::endl;
		tree_in->GetEntry(i);
		if(genphoton_pt[0]<0 || genjet_pt[1]<30 || (genelectron_pt[0]<0&&genmuon_pt[0]<0) || genelectron_pt[2]>0 || genmuon_pt[2]>0) continue;
		// choose gen leptons
		if(large(genelectron_pt[0],genelectron_pt[1])>large(genmuon_pt[0],genmuon_pt[1])) {
			lep=11;
			l1.SetPtEtaPhiM(genelectron_pt[0],genelectron_eta[0],genelectron_phi[0],0.0005);
			l2.SetPtEtaPhiM(genelectron_pt[1],genelectron_eta[1],genelectron_phi[1],0.0005);
			for(int iphoton=0;iphoton<6;iphoton++){
				TLorentzVector photon_temp;
	                        photon_temp.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
        	                if((l1.DeltaR(photon_temp)<0.1 || l2.DeltaR(photon_temp)<0.1) && l1.DeltaR(photon_temp)<l2.DeltaR(photon_temp)) {l1+=photon_temp;continue;}
                	        if((l1.DeltaR(photon_temp)<0.1 || l2.DeltaR(photon_temp)<0.1) && l1.DeltaR(photon_temp)>=l2.DeltaR(photon_temp)) {l2+=photon_temp;continue;}
			}
			if(l1.Pt()<25 || l2.Pt()<25 || fabs(l1.Eta())>2.5 || fabs(l2.Eta())>2.5 || (l1+l2).M()<70 || (l1+l2).M()>110) continue;
		}
		else {
			lep=13;
			l1.SetPtEtaPhiM(genmuon_pt[0],genmuon_eta[0],genmuon_phi[0],0.1);
			l2.SetPtEtaPhiM(genmuon_pt[1],genmuon_eta[1],genmuon_phi[1],0.1);
			for(int iphoton=0;iphoton<6;iphoton++){
                                TLorentzVector photon_temp;
                                photon_temp.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
                                if((l1.DeltaR(photon_temp)<0.1 || l2.DeltaR(photon_temp)<0.1) && l1.DeltaR(photon_temp)<l2.DeltaR(photon_temp)) {l1+=photon_temp;continue;}
                                if((l1.DeltaR(photon_temp)<0.1 || l2.DeltaR(photon_temp)<0.1) && l1.DeltaR(photon_temp)>=l2.DeltaR(photon_temp)) {l2+=photon_temp;continue;}
                        }
			if(l1.Pt()<20 || l2.Pt()<20 || fabs(l1.Eta())>2.4 || fabs(l2.Eta())>2.4 || (l1+l2).M()<70 || (l1+l2).M()>110) continue;
		}

		//choose gen photon
		int good_photon=-1;
		for(int iphoton=0;iphoton<6;iphoton++){
			if(good_photon!=-1)continue;
			TLorentzVector photon_temp;
			photon_temp.SetPtEtaPhiE(0,0,0,0);
			if(genphoton_pt[iphoton]<20 || fabs(genphoton_eta[iphoton]) >2.5 || (fabs(genphoton_eta[iphoton])<1.566 &&fabs(genphoton_eta[iphoton])>1.4442) ) continue; 
			photon_temp.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
			if(l1.DeltaR(photon_temp)<0.7 || l2.DeltaR(photon_temp)<0.7) continue;
			if(good_photon==-1)photon_p4.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
			if(good_photon!=-1 && photon_temp.Pt()>photon_p4.Pt()) photon_p4.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
			good_photon=iphoton;
		}
		if(good_photon==-1) continue;

		//choose gen jets
		for(int ijet=0;ijet<6;ijet++){
			if(j1.Pt()!=0 && j2.Pt()!=0) continue;
			TLorentzVector jet_temp;
			jet_temp.SetPtEtaPhiE(0,0,0,0);
			if(genjet_pt[ijet]<30 || fabs(genjet_eta[ijet])>4.7) continue;
			jet_temp.SetPtEtaPhiE(genjet_pt[ijet],genjet_eta[ijet],genjet_phi[ijet],genjet_e[ijet]);
			if(j1.Pt()==0 && l1.DeltaR(jet_temp)>0.5 && l2.DeltaR(jet_temp)>0.5 &&photon_p4.DeltaR(jet_temp)>0.5) j1.SetPtEtaPhiE(genjet_pt[ijet],genjet_eta[ijet],genjet_phi[ijet],genjet_e[ijet]);
			if(j1.Pt()!=0 &&l1.DeltaR(jet_temp)>0.5 && l2.DeltaR(jet_temp)>0.5 &&photon_p4.DeltaR(jet_temp)>0.5 &&j1.DeltaR(jet_temp)>0.5) j2.SetPtEtaPhiE(genjet_pt[ijet],genjet_eta[ijet],genjet_phi[ijet],genjet_e[ijet]);
		}

		if(j1.Pt()==0 || j2.Pt()==0) continue;
	
		ZGmass=(l1+l2+photon_p4).M();
		if((j1+j2).M()<500 || fabs(j1.Eta()-j2.Eta())<2.5 || ZGmass<=0) continue;
		yields++;
		if(lep==11 && fabs(genphoton_eta[good_photon])<=1.4442) {yields_e_b++;if(theWeight>0) plus_e++;if(theWeight<0) minus_e++;}
		if(lep==11 && fabs(genphoton_eta[good_photon])>1.4442) {yields_e_e++;if(theWeight>0) plus_e++;if(theWeight<0) minus_e++;}
		if(lep==13 && fabs(genphoton_eta[good_photon])<=1.4442) {yields_m_b++;if(theWeight>0) plus_m++;if(theWeight<0) minus_m++;}
		if(lep==13 && fabs(genphoton_eta[good_photon])>1.4442) {yields_m_e++;if(theWeight>0) plus_m++;if(theWeight<0) minus_m++;}
//		myfile<<i<<" l1_pt: "<<l1.Pt()<<" l1_eta:"<<l1.Eta()<<" l2_pt:"<<l2.Pt()<<" l2_eta:"<<l2.Eta()<<" photon_pt:"<<photon_p4.Pt()<<" photon_eta:"<<photon_p4.Eta()<<" j1_pt:"<<j1.Pt()<<" j2_pt:"<<j2.Pt()<<" Mjj:"<<(j1+j2).M()<<" j1_eta:"<<j1.Eta()<<" j2_eta:"<<j2.Eta()<<" detajj:"<<fabs(j1.Eta()-j2.Eta())<<" Zmass:"<<(l1+l2).M()<<std::endl;
	}
//	myfile.close();
	std::cout<<yields<<" ele barrel:"<<yields_e_b<<" ele endcap:"<<yields_e_e<<" +weight:"<<plus_e<<" -weight:"<<minus_e<<std::endl;
	std::cout<<yields<<" mu barrel:"<<yields_m_b<<" mu endcap:"<<yields_m_e<<" +weight:"<<plus_m<<" -weight:"<<minus_m<<std::endl;
}

int main(){
	gen();
	return 1;
}
