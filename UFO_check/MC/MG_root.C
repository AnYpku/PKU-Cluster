#define pi 3.1415926
double ptlep1=-10,ptlep2=-10,etalep1=-10,etalep2=-10,photonet=-10,photoneta=-10,jet1pt=-10,jet2pt=-10,jet1eta=-10,jet2eta=-10;  
double philep1=-10,philep2=-10,photonphi=-10,jet1phi=-10,jet2phi=-10;
double Mjj=-10,massVlep=-10,Mva=-10;
int lep=-10;
double drj1a=-10,drj2a=-10,drl1a=-10,drl2a=-10,drj1l1=-10,drj1l2=-10,drj2l2=-10,drj2l1=-10,drjj=-10;
double drll=-10;
void set_init();
Double_t delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
void MG_root(){

	//Load shared library
	//gSystem->Load("/home/pku/anying/MC-software/MG5_aMC_v2_8_3/ExRootAnalysis/libExRootAnalysis.so");
	R__LOAD_LIBRARY(/home/pku/anying/MC-software/MG5_aMC_v2_8_3/ExRootAnalysis/libExRootAnalysis.so);

	float inix= 500;
	float finx= 20000.0;
	float nbin= 10.0;


	TString IFile1 ="/data/pku/home/anying/cms/PKU-Cluster/MC/input/LLAJJ_aQGC_lhe.root";
	TChain chain("LHEF");
	chain.Add(IFile1); 
	// Create object of class ExRootTreeReader
	ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
	Long64_t numberOfEntries = treeReader->GetEntries();
	// Get pointers to branches used in this analysis
	TClonesArray *branchEvent = treeReader->UseBranch("Event");
	TClonesArray *branchParticle = treeReader->UseBranch("Particle");
	TH1F *h1= new TH1F("Mjj","",nbin,inix,finx);
	h1->Sumw2();
	double scalef=5.495412948087E-02*1000/float(numberOfEntries);
	TLorentzVector J1, J2, JJ,lep1,lep2,photon,V;
//	TFile*fout=new TFile("LLAJJ_aQGC_out.root","recreate");
	TFile*fout=new TFile("LLAJJ_UFO_out.root","recreate");
	TTree*treename=new TTree("demo","");
	treename->Branch("lep", &lep, "lep/I");
	treename->Branch("massVlep", &massVlep, "massVlep/D");
	treename->Branch("Mva", &Mva, "Mva/D");
	treename->Branch("ptlep1", &ptlep1, "ptlep1/D");
	treename->Branch("etalep1", &etalep1, "etalep1/D");
	treename->Branch("philep1", &philep1, "philep1/D");
	treename->Branch("ptlep2", &ptlep2, "ptlep2/D");
	treename->Branch("etalep2", &etalep2, "etalep2/D");
	treename->Branch("philep2", &philep2, "philep2/D");
	treename->Branch("photonet", &photonet, "photonet/D");
	treename->Branch("photoneta", &photoneta, "photoneta/D");
	treename->Branch("photonphi", &photonphi, "photonphi/D");
	treename->Branch("jet1pt", &jet1pt, "jet1pt/D");
	treename->Branch("jet1eta", &jet1eta, "jet1eta/D");
	treename->Branch("jet1phi", &jet1phi, "jet1phi/D");
	treename->Branch("jet2pt", &jet2pt, "jet2pt/D");
	treename->Branch("jet2eta", &jet2eta, "jet2eta/D");
	treename->Branch("jet2phi", &jet2phi, "jet2phi/D");
	treename->Branch("Mjj", &Mjj, "Mjj/D");
	treename->Branch("scalef", &scalef, "scalef/D");
	treename->Branch("drjj", &drjj, "drjj/D");
	treename->Branch("drj1a", &drj1a, "drj1a/D");
	treename->Branch("drj2a", &drj2a, "drj2a/D");
	treename->Branch("drl1a", &drl1a, "drl1a/D");
	treename->Branch("drl2a", &drl2a, "drl2a/D");
	treename->Branch("drj1l1", &drj1l1, "drj1l1/D");
	treename->Branch("drj2l1", &drj2l1, "drj2l1/D");
	treename->Branch("drj1l2", &drj1l2, "drj1l2/D");
	treename->Branch("drj2l2", &drj2l2, "drj2l2/D");
	treename->Branch("drll", &drll, "drll/D");
	for(int i=0; i<=numberOfEntries-1; i++)
	{
		set_init();
		J1.SetPtEtaPhiE(0.,0.,0.,0.);
		J2.SetPtEtaPhiE(0.,0.,0.,0.);
		treeReader->ReadEntry(i);
		TRootLHEFEvent *event=(TRootLHEFEvent*) branchEvent->At(0);
		int np=event->Nparticles;
		double weight=event->Weight;
		cout<<"event weight "<<weight<<endl;
		cout<<"N particles "<<np<<endl;
		int i_lep=0,i_jet=0;
		for(int j=2; j<np; j++){//0 and 1 are the two protons
			TRootLHEFParticle *particle1=(TRootLHEFParticle*) branchParticle->At(j);
			//cout<<j<<"th particle "<<abs(particle1->PID)<<" "<<particle1->PT<<endl;
			if( (abs(particle1->PID)<6 || abs(particle1->PID)==21) ) {//p and jet
				if(i_jet>0){
					J1.SetPtEtaPhiE(particle1->PT,particle1->Eta,particle1->Phi,particle1->E);
					jet1pt=particle1->PT;jet1eta=particle1->Eta;jet1phi=particle1->Phi;
					cout<<j<<"th particle "<<abs(particle1->PID)<<" jet1 "<<particle1->PT<<endl;
				}
				else{  
					J2.SetPtEtaPhiE(particle1->PT,particle1->Eta,particle1->Phi,particle1->E);
					jet2pt=particle1->PT;jet2eta=particle1->Eta;jet2phi=particle1->Phi;
					cout<<j<<"th particle "<<abs(particle1->PID)<<" jet2 "<<particle1->PT<<endl;
				}
				i_jet++;
			}
			if( (abs(particle1->PID)==11 || abs(particle1->PID)==13) ) {//lepton
				if( abs(particle1->PID)==11  ) lep=11;
				else lep=13;
				if(i_lep>0){
					lep1.SetPtEtaPhiE(particle1->PT,particle1->Eta,particle1->Phi,particle1->E);
					ptlep1=particle1->PT;etalep1=particle1->Eta;philep1=particle1->Phi;
					cout<<j<<"th particle "<<abs(particle1->PID)<<" lep1 "<<particle1->PT<<endl;
				}
				else{
					lep2.SetPtEtaPhiE(particle1->PT,particle1->Eta,particle1->Phi,particle1->E);
					ptlep2=particle1->PT;etalep2=particle1->Eta;philep2=particle1->Phi;
					cout<<j<<"th particle "<<abs(particle1->PID)<<" lep2 "<<particle1->PT<<endl;
				}
				i_lep++;
			}
			if( (abs(particle1->PID)==22) ){ // gamma
				photon.SetPtEtaPhiE(particle1->PT,particle1->Eta,particle1->Phi,particle1->E);
				photonet=particle1->PT;photoneta=particle1->Eta;photonphi=particle1->Phi;
				cout<<j<<"th particle "<<abs(particle1->PID)<<" photon "<<particle1->PT<<endl;
			}
			if( (abs(particle1->PID)==23) ){  // Z
				V.SetPtEtaPhiE(particle1->PT,particle1->Eta,particle1->Phi,particle1->E);
			}
		}
		JJ=J1+J2;
		Mjj=JJ.M(); 
		if(lep==13||lep==11){
			massVlep=(lep1+lep2).M();
			Mva=(lep1+lep2+photon).M();
		}
		cout<<"ptlep1 "<<ptlep1<<endl;
		drjj=delta_R(jet1eta, jet1phi, jet2eta, jet2phi);
		drj1a=delta_R(jet1eta, jet1phi, photoneta, photonphi);
		drj2a=delta_R(jet2eta, jet2phi, photoneta, photonphi);
		drl1a=delta_R(etalep1, philep1, photoneta, photonphi);
		drl2a=delta_R(etalep2, philep2, photoneta, photonphi);
		drj1l1=delta_R(jet1eta, jet1phi, etalep1, philep1);
		drj2l1=delta_R(jet2eta, jet2phi, etalep1, philep1);
		drj1l2=delta_R(jet1eta, jet1phi, etalep2, philep2);
		drj2l2=delta_R(jet2eta, jet2phi, etalep2, philep2);
		drll=delta_R(etalep1,philep1,etalep2,philep2);
		treename->Fill();
	}
	fout->cd();
	treename->Write();
} 
void set_init(){
	ptlep1=-10;ptlep2=-10;etalep1=-10;etalep2=-10;
	photonet=-10;photoneta=-10;
	jet1pt=-10;jet2pt=-10;jet1eta=-10;jet2eta=-10;  
	philep1=-10;philep2=-10;photonphi=-10;jet1phi=-10;jet2phi=-10;
	Mjj=-10;massVlep=-10;Mva=-10;
	lep=-10;
	drj1a=-10;drj2a=-10;drl1a=-10;drl2a=-10;drj1l1=-10;drj1l2=-10;drj2l2=-10;drj2l1=-10;drjj=-10;
}
Double_t delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{
        Double_t dp = phi1-phi2;
        if(std::fabs(dp) > pi) dp = 2*pi - std::fabs(dp);
        Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
        return dr;
}
