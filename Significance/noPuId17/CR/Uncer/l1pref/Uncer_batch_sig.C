#define num 3
#define pi 3.1415926
void run(TString cut1,TString tag,TString channel){
     Double_t Mjj_bins[2]={150, 400};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TString dir="/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_";
     TFile*file=new TFile(dir+"ZA-EWK"+tag+".root");
     TTree*tree=(TTree*)file->Get("outtree");
     int lep;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,pileupWeight,prefWeight,prefWeightUp,prefWeightDown,muon1_track_scale,muon2_track_scale;
     double jet1pt,jet2pt,jet1eta,jet2eta,jet1e,jet2e,jet1phi,jet2phi;
     double photonet,photoneta,photone,photonphi;
     double ptVlep, yVlep, phiVlep, massVlep;
     double Mjj,scalef,zepp,actualWeight;
     tree->SetBranchAddress("actualWeight",&actualWeight);
     tree->SetBranchAddress("lep",&lep);
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
     tree->SetBranchAddress("prefWeightUp", &prefWeightUp);
     tree->SetBranchAddress("prefWeightDown", &prefWeightDown);
     tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
     tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
     tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
     tree->SetBranchAddress("muon1_track_scale", &muon1_track_scale);
     tree->SetBranchAddress("muon2_track_scale", &muon2_track_scale);
     TString cut;
     if(channel.Contains("elebarrel"))
             cut="lep==11&&fabs(photoneta)<1.4442";
     if(channel.Contains("mubarrel"))
             cut="lep==13&&fabs(photoneta)<1.4442";
     if(channel.Contains("eleendcap"))
             cut="lep==11&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";
     if(channel.Contains("muendcap"))
             cut="lep==13&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";
     TTreeFormula *tformula=new TTreeFormula("formula", cut1+"&&("+cut+")", tree);
     double Weight[num];
     TH1D*th1[num];
     TString th1name[num];
     for(Int_t i=0;i<num;i++){
		     th1name[i]=Form("hist_%d",i);
		     th1[i] = new TH1D(th1name[i],th1name[i],1,0,1);
		     th1[i]->Sumw2(); 
     }      
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
             actualWeight=actualWeight/prefWeight;
	     int p=0;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     if(p==0)Weight[p]=actualWeight*prefWeight;
			     if(p==1)Weight[p]=actualWeight*prefWeightUp;
			     if(p==2)Weight[p]=actualWeight*prefWeightDown;
			     if(Mjj>=150&&Mjj<400)th1[p]->Fill(0.5,Weight[p]);//0~1, 2.5~4.5 and 500~800
			     p++;
		     }
	     }
     }
     TFile*fout;
     fout= new TFile("hist_ewk_pref_"+tag+channel+".root","recreate");
     fout->cd();
     for(Int_t i=0;i<num;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_sig(){
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
	TString dr = "drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
	vector<TString> tag={"16","17"};

	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	const int kk=channels.size();
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
//                      GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
                        jet="(  ( (!(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65)&&fabs(jet1eta)<4.7&&jet1pt<50&&jet1pt>30) || (jet1pt>50&&fabs(jet1eta)< 4.7) )   &&   ( (!(fabs(jet2eta)<3.14 && fabs(jet2eta)>2.65) && fabs(jet2eta)<4.7 && jet2pt<50 && jet2pt>30) || (jet2pt>50&&fabs(jet2eta)< 4.7) )   )";
		}
		else{
			jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
		}
		TString ControlRegion = "Mjj>150 && Mjj<400 && ZGmass>100";
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
		cout<<tag[i]<<" "<<jet<<endl;
		for(int j=0;j<kk;j++){
			run(Reco,tag[i],channels[j]);
		}
	}
	return 1;
}
