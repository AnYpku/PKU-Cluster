#define num 3
#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString cut1){
     vector<Double_t> mjj_bins={150,300,400,500};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TString dir1;
     dir1="/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_";
     TFile*file;
     file=new TFile(dir1+"ZA"+sample+tag+".root");
     TTree*tree=(TTree*)file->Get("outtree");
     map<TString, double> variables;
     int lep;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,pileupWeight,prefWeight;
     double jet1pt,jet2pt,jet1eta,jet2eta,jet1e,jet2e,jet1phi,jet2phi;
     double photonet,photoneta,photone,photonphi;
     double ptVlep, yVlep, phiVlep, massVlep;
     double Mjj,scalef,zepp,actualWeight;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("actualWeight",&actualWeight);
     tree->SetBranchAddress("Mjj",&Mjj);
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
     tree->SetBranchAddress("prefWeight", &prefWeight);
     tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
     tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
     tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
//     TH1D*th1[kk];
     TString th1name;
     th1name="hist"+sample;
     TH1D* th1;
     th1 = new TH1D(th1name,th1name,mjj_bins.size()-1,&mjj_bins[0]);
     th1->Sumw2(); 
     double delta_phi,detajj;
     TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     detajj=fabs(jet1eta-jet2eta);
             Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
             photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
             jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
             jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
             delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
             if (delta_phi>pi) delta_phi=2*pi-delta_phi;
	     if (  tformula->EvalInstance() /*&& (zepp<2.4 && delta_phi>1.9)*/ ){
		     if(Mjj>=150&&Mjj<500)th1->Fill(Mjj,actualWeight);//0~1, 2.5~4.5 and 500~800
	     }
     }
     return th1;
}
int Uncer_batch_bkg(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"-EWK","_interf"};
	const int kk=sample.size();
	TH1D*hist[3][kk];TH1D*hist_up[3][kk];TH1D*hist_down[3][kk];//hist[year][sample]
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString ControlRegion = "(Mjj>150  && Mjj<500 && ZGmass>100)";
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
		for(int j=0;j<kk;j++){
			hist[i][j]=run(sample[j],tag[i],Reco);
		}
	}
	//     cout<<hist[0][0]->GetBinContent(1);
	TFile*fout[3][kk];
	for(int i=0;i<3;i++){
		for(int j=0;j<kk;j++){
			fout[i][j]= new TFile("hist"+sample[j]+"_"+tag[i]+".root","recreate");
			cout<<hist[i][j]->GetBinContent(1)<<endl;
			fout[i][j]->cd();
			hist[i][j]->Write();
			fout[i][j]->Close();
		}//fout[year][sample]
	}
	/*     for(int j=0;j<kk;j++){
	       for(int i=0;i<3;i++){
	       fout[i][j]->cd();
	       hist[i][j]->Write();
	       hist_up[i][j]->Write();
	       hist_down[i][j]->Write();
	       fout[i][j]->Close();
	       }
	       }*/
	return 1;
}
