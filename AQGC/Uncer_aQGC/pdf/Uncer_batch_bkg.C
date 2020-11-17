#define num 103
#define pi 3.1415926
void run( TFile*file,TString cut1,TString tag,bool turn){
	TString name=file->GetName();
	TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
	Double_t scalef,pileupWeight,prefWeight,pweight[703],Mjj,zepp,actualWeight;
	double jet1pt,jet2pt,jet1eta,jet2eta,jet1e,jet2e,jet1phi,jet2phi;
	double photonet,photoneta,photone,photonphi;
	double ptVlep, yVlep, phiVlep, massVlep,Mva;
	tree->SetBranchAddress("Mjj",&Mjj);
	tree->SetBranchAddress("Mva",&Mva);
	tree->SetBranchAddress("zepp",&zepp);
	tree->SetBranchAddress("jet1eta",&jet1eta);
	tree->SetBranchAddress("jet2eta",&jet2eta);
	tree->SetBranchAddress("jet1e",&jet1e);
	tree->SetBranchAddress("jet2e",&jet2e);
	tree->SetBranchAddress("jet1pt",&jet1pt);
	tree->SetBranchAddress("jet2pt",&jet2pt);
	tree->SetBranchAddress("jet1phi",&jet1phi);
	tree->SetBranchAddress("jet2phi",&jet2phi);
	tree->SetBranchAddress("photoneta",&photoneta);
	tree->SetBranchAddress("photonet",&photonet);
	tree->SetBranchAddress("photonphi",&photonphi);
	tree->SetBranchAddress("photone",&photone);
	tree->SetBranchAddress("ptVlep",&ptVlep);
	tree->SetBranchAddress("yVlep",&yVlep);
	tree->SetBranchAddress("phiVlep",&phiVlep);
	tree->SetBranchAddress("massVlep",&massVlep);
	tree->SetBranchAddress("scalef", &scalef);
	tree->SetBranchAddress("pileupWeight", &pileupWeight);
	tree->SetBranchAddress("pweight",pweight);
	tree->SetBranchAddress("prefWeight",&prefWeight);

	TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
	double Weight[num];
	TH1D*th1[num];
	TString th1name[num];
	vector<double> ZGbin={150,400,600,800,1000,2e4};
	for(Int_t i=0;i<num;i++){
		th1name[i]=Form("hist_%d",i);
		th1[i] = new TH1D(th1name[i],th1name[i],ZGbin.size()-1,&ZGbin[0]);
		th1[i]->Sumw2(); 
	}
	cout<<tag<<" "<<name<<endl;
	TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
	double delta_phi,detajj;
	for(int k=0;k<tree->GetEntries();k++){
		tree->GetEntry(k);
		detajj=fabs(jet1eta-jet2eta);
		Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
		photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
		if (delta_phi>pi) delta_phi=2*pi-delta_phi;
		int p=0;
		int init;
		if(tag.Contains("16")&&name.Contains("EWK"))
			init=9;//16 ewk
		else if(tag.Contains("16")&&name.Contains("EWK")==0)
			init=0;//16 qcd
		else if(( tag.Contains("17")||tag.Contains("18"))&&name.Contains("EWK"))
			init=45;//17 ewk,18 ewk
		if(tag.Contains("18"))prefWeight=1;
		if(Mva>2e4)Mva=1999;
		if (  tformula->EvalInstance()  ){
			for(Int_t i=init;i<(num+init);i++){
				Weight[p]=scalef*pileupWeight*prefWeight*pweight[i];
				th1[p]->Fill(Mva,Weight[p]);//8~9 6~infi 800~1200
				p++;
			}
		}
	}
	TFile*fout;
	if(name.Contains("EWK")==0)
		fout= new TFile("hist_qcd_pdf"+tag+".root","recreate");
	else{
		if(turn==1)	fout= new TFile("hist_Sigout_pdf"+tag+".root","recreate");
		else  fout= new TFile("hist_ewk_pdf"+tag+".root","recreate");
	}
	fout->cd();
	for(Int_t i=0;i<num;i++){
		th1[i]->Write();
	}
	fout->Close();
	for(Int_t i=0;i<num;i++){
		delete  th1[i];
	}
}
int Uncer_batch_bkg(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )  )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "( ( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5 )";
	TString SignalRegion = "( Mjj>500 && fabs(jet1eta-jet2eta)>2.5 ) ";
	vector<TString> tag={"16","17","18"};

	TFile*file1[3];
	TString dir1="/home/pku/anying/cms/rootfiles/2016/";     
	TString dir2="/home/pku/anying/cms/rootfiles/2017/";     
	TString dir3="/home/pku/anying/cms/rootfiles/2018/";     
	file1[0]=new TFile(dir1+"cutla-outZA16.root");
	file1[1]=new TFile(dir2+"cutla-outZA17.root");
	file1[2]=new TFile(dir3+"cutla-outZA18.root");

//	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";     
	TFile*file2[3];
	file2[0]=new TFile(dir1+"cutla-outZA-EWK16.root");
	file2[1]=new TFile(dir2+"cutla-outZA-EWK17.root");
	file2[2]=new TFile(dir3+"cutla-outZA-EWK18.root");

	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="(  ( (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65&&jet1pt>30&&jet1pt<50&&jet1puIdTight==1) || (!(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) && fabs(jet1eta)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65&&jet2pt>30&&jet2pt<50&&jet2puIdTight==1)||(!(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65)&&fabs(jet2eta)<4.7&&jet2pt>30&&jet2pt<50) ||(fabs(jet2eta)<4.7 && jet2pt>50) )  )";
		}
		else{
			jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
		}
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		cout<<tag[i]<<" "<<jet<<endl;
		if(tag[i].Contains("16"))	
			run(file1[i],Reco,tag[i],0);
		run(file2[i],Reco,tag[i],0);
	}
	return 1;
}
