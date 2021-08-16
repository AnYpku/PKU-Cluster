#define pi 3.1415926
TH1D*unroll(TH2D*h2){
	TString histname=h2->GetName();
	TH1D*h1=new TH1D("hist_"+histname,"",h2->GetNbinsX()*h2->GetNbinsY()+0,0,h2->GetNbinsX()*h2->GetNbinsY()+0);
	for(int iy=1;iy<=h2->GetNbinsX();iy++){
		for(int ix=1;ix<=h2->GetNbinsX();ix++){
                   int i=ix+4*(iy-1);
                   cout<<iy<<" "<<ix<<" "<<i<<endl;
                   h1->SetBinContent(i,h2->GetBinContent(ix,iy));
                   h1->SetBinError(i,h2->GetBinError(ix,iy));
		}
	}
	return h1;
}
void run(TString dir,TString name,TString cut,TString tag,TString type){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<endl;
     TTree*tree=(TTree*)file->Get("Events");
     double scalef,actualWeight;
     float mll,mllg,ptll;
     float PuppiMET_T1Smear_phi,PuppiMET_T1Smear_pt;
     float lep1pt,lep2pt,lep1eta,lep2eta,lep1phi,lep2phi;
     map<TString, float> variables;
     tree->SetBranchAddress("PuppiMET_T1Smear_pt_"+type+"Up", &variables["PuppiMET_T1Smear_pt_"+type+"Up"]);
     tree->SetBranchAddress("PuppiMET_T1Smear_pt_"+type+"Down", &variables["PuppiMET_T1Smear_pt_"+type+"Down"]);
     tree->SetBranchAddress("PuppiMET_T1Smear_phi_"+type+"Up", &variables["PuppiMET_T1Smear_phi_"+type+"Up"]);
     tree->SetBranchAddress("PuppiMET_T1Smear_phi_"+type+"Down", &variables["PuppiMET_T1Smear_phi_"+type+"Down"]);
     tree->SetBranchAddress("PuppiMET_T1Smear_pt", &PuppiMET_T1Smear_pt);
     tree->SetBranchAddress("PuppiMET_T1Smear_phi", &PuppiMET_T1Smear_phi);
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("mll", &mll);
     tree->SetBranchAddress("mllg", &mllg);
     tree->SetBranchAddress("ptll", &ptll);
     tree->SetBranchAddress("lep1pt", &lep1pt);
     tree->SetBranchAddress("lep2pt", &lep2pt);
     tree->SetBranchAddress("lep1eta", &lep1eta);
     tree->SetBranchAddress("lep2eta", &lep2eta);
     tree->SetBranchAddress("lep1phi", &lep1phi);
     tree->SetBranchAddress("lep2phi", &lep2phi);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="sig";
     }
     else  th2name="bkg";
             
     vector<Double_t> mT_bins    ={60,90,120,160,200};
     vector<Double_t> mll_bins   ={20,80,120,160,200};
//   vector<Double_t> mllg_bins   ={40,100,150,200,300};
     TH2D* h2[3];
     for(int i=0;i<3;i++){
	     h2[i]=new TH2D(th2name+Form("_%d",i),"",mT_bins.size()-1,&mT_bins[0],mll_bins.size()-1,&mll_bins[0]);
     }
     double lumi;
     if(tag.Contains("16"))lumi=35.86;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     TLorentzVector lep1p4,lep2p4;
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=scalef*lumi;
	     if(name.Contains("plj")||name.Contains("fake")) actualWeight=scalef;
             if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;

	     lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
	     lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
	     double phiVlep=(lep1p4+lep2p4).Phi();    
             double mT=sqrt(2*(ptll*PuppiMET_T1Smear_pt*(1-cos(phiVlep-PuppiMET_T1Smear_phi) ) ) );
	     double mT_Up=sqrt(2*(ptll*variables["PuppiMET_T1Smear_pt_"+type+"Up"]*(1-cos(phiVlep-variables["PuppiMET_T1Smear_phi_"+type+"Up"]) ) ) );
	     double mT_Down=sqrt(2*(ptll*variables["PuppiMET_T1Smear_pt_"+type+"Down"]*(1-cos(phiVlep-variables["PuppiMET_T1Smear_phi_"+type+"Down"]) ) ) );
             double lep_pt,lep_phi;
	     if(lep1pt>lep2pt){lep_pt=lep2pt;lep_phi=lep2phi;}
	     else{lep_pt=lep1pt;lep_phi=lep1phi;}
             double mT2=sqrt(2*(lep_pt*PuppiMET_T1Smear_pt*(1-cos(lep_phi-PuppiMET_T1Smear_phi) ) ) );
	     double mT2_Up=sqrt(2*(lep_pt*variables["PuppiMET_T1Smear_pt_"+type+"Up"]*(1-cos(lep_phi-variables["PuppiMET_T1Smear_phi_"+type+"Up"]) ) ) );
	     double mT2_Down=sqrt(2*(lep_pt*variables["PuppiMET_T1Smear_pt_"+type+"Down"]*(1-cos(lep_phi-variables["PuppiMET_T1Smear_phi_"+type+"Down"]) ) ) );
          
	     if (  ! tformula1->EvalInstance() ) continue;
	     if (mT>=200) mT=199; if(mT_Up>200) mT_Up=199; if(mT_Down>200) mT_Down=199;
	     if (mll>=200) mll=199; if(mllg>300) mllg=299;
	     if(PuppiMET_T1Smear_pt>20 && mT>60 && mT2>30)    
		     h2[0]->Fill(mT,mll,actualWeight);
	     if(variables["PuppiMET_T1Smear_pt_"+type+"Up"]>20 && mT_Up>60 && mT2_Up>30)
		     h2[1]->Fill(mT_Up,mll,actualWeight);
	     if(variables["PuppiMET_T1Smear_pt_"+type+"Down"]>20 && mT_Down>60 && mT2_Down>30)
		     h2[2]->Fill(mT_Down,mll,actualWeight);

     }
     TH1D*hist[3];
     for(int i=0;i<3;i++){
	     hist[i]=unroll(h2[i]);
     }
     TFile*fout=new TFile("./root/hist_"+name+"_"+type+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<3;i++){
	     hist[i]->Write();
	     h2[i]->Write();
     }
     fout->Close();
}
int Build_Hist(){
	TString LEP = "( ( (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL) ) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1 )";
	TString met="(n_bjets==0)";
	vector<TString> tags={"18"};
	TString dir1;
	dir1="/home/pku/anying/cms/rootfiles/WWg/cutla-out";
	TString Reco;
	vector<TString> names={"ZGJets","TTGJets","VV","ST","tZq","TGJets","WGJets","WWG"};
	for(int k=0;k<tags.size();k++){
		Reco= LEP+"&&"+photon+"&&"+met;
		for(int j=0;j<names.size();j++){     
			run(dir1,names[j],Reco,tags[k],"jer1");
			run(dir1,names[j],Reco,tags[k],"jesTotal");
		}
	}
	return 1;
}
