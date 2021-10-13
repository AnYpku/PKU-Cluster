#define pi 3.1415926
TH1D*unroll(TH2D*h2){
	TString histname=h2->GetName();
	TH1D*h1=new TH1D("hist_"+histname,"",h2->GetNbinsX()*h2->GetNbinsY()+0,0,h2->GetNbinsX()*h2->GetNbinsY()+0);
	for(int iy=1;iy<=h2->GetNbinsY();iy++){
		for(int ix=1;ix<=h2->GetNbinsX();ix++){
                   int i=ix+4*(iy-1);
                   cout<<iy<<" "<<ix<<" "<<i<<endl;
                   h1->SetBinContent(i,h2->GetBinContent(ix,iy));
                   h1->SetBinError(i,h2->GetBinError(ix,iy));
		}
	}
	return h1;
}
void run(TString cut,TString tag){
     TFile*file=new TFile("cutla-outplj_unc"+tag+".root");
     TTree*tree=(TTree*)file->Get("Events");
     double scalef;
     double mT;
     double scalef_up,scalef_down;
     float mll,mllg;
     float PuppiMET_T1_phi,PuppiMET_T1_pt;
     float lep1pt,lep2pt,lep1eta,lep2eta,lep1phi,lep2phi,ptll;
     TLorentzVector lep1p4,lep2p4;
     tree->SetBranchAddress("PuppiMET_T1_pt", &PuppiMET_T1_pt);
     tree->SetBranchAddress("PuppiMET_T1_phi", &PuppiMET_T1_phi);
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("scalef_up", &scalef_up);
     tree->SetBranchAddress("scalef_down", &scalef_down);
     tree->SetBranchAddress("mll", &mll);
     tree->SetBranchAddress("mT", &mT);
     tree->SetBranchAddress("ptll", &ptll);
     tree->SetBranchAddress("mllg", &mllg);
     tree->SetBranchAddress("lep1pt", &lep1pt);
     tree->SetBranchAddress("lep2pt", &lep2pt);
     tree->SetBranchAddress("lep1eta", &lep1eta);
     tree->SetBranchAddress("lep2eta", &lep2eta);
     tree->SetBranchAddress("lep1phi", &lep1phi);
     tree->SetBranchAddress("lep2phi", &lep2phi);
     TString th2name,th2name_out;
     th2name="hist";
             
     vector<Double_t> mT_bins    ={60,90,120,160,200};
     vector<Double_t> mll_bins   ={20,80,140,200};
//   vector<Double_t> mll_bins   ={20,80,120,160,200};
     TH2D* h2[3];
     for(int i=0;i<3;i++){
	     h2[i]=new TH2D(th2name+Form("_%d",i),"",mT_bins.size()-1,&mT_bins[0],mll_bins.size()-1,&mll_bins[0]);
     }
     double lumi;
     if(tag.Contains("16"))lumi=35.86;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     cout<<"test"<<endl;
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
             lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
             lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
             double phiVlep=(lep1p4+lep2p4).Phi();
	     double lep_pt,lep_phi;
             if(lep1pt>lep2pt){lep_pt=lep2pt;lep_phi=lep2phi;}
             else{lep_pt=lep1pt;lep_phi=lep1phi;}
             double mT2=sqrt(2*(lep_pt*PuppiMET_T1_pt*(1-cos(lep_phi-PuppiMET_T1_phi) ) ) );
	     if (  tformula1->EvalInstance() && mT>60 && mT2>30 ){ 
		if (mT>=200) mT=199;
		if (mll>=200) mll=199;
                if(mllg>300) mllg=299;
                cout<<scalef<<" "<<scalef_up<<" "<<scalef_down<<endl;
		h2[0]->Fill(mT,mll,scalef);
		h2[1]->Fill(mT,mll,scalef_up);
		h2[2]->Fill(mT,mll,scalef_down);
	     }

     }
     cout<<"end loop"<<endl;
     TH1D*hist[3];
     for(int i=0;i<3;i++){
	     hist[i]=unroll(h2[i]);
     }
     TFile*fout=new TFile("./root/hist_plj_"+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<3;i++){
	     hist[i]->Write();
	     h2[i]->Write();
     }
     fout->Close();
}
int Build_Hist(){
	TString LEP = "(( (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL) ) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_is_tight==1 && lep2_is_tight==1)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection !=1)";
	TString met="(n_bjets==0 && PuppiMET_T1_pt > 20  )";
	vector<TString> tags={"17","18"};
	TString Reco;
	for(int k=0;k<tags.size();k++){
		Reco= LEP+"&&"+photon+"&&"+met;
		run(Reco,tags[k]);
	}
	return 1;
}
