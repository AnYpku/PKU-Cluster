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
void run(TString dir,TString name,TString cut,TString tag){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<endl;
     TTree*tree=(TTree*)file->Get("outtree");
     double actualWeight,scalef,mT;
     float LHEScaleWeight[9];
     float mll,mllg;
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("LHEScaleWeight", LHEScaleWeight);
     tree->SetBranchAddress("actualWeight", &actualWeight);
     tree->SetBranchAddress("mT", &mT);
     tree->SetBranchAddress("mll", &mll);
     tree->SetBranchAddress("mllg", &mllg);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="sig";
     }
     else  th2name="bkg";
     th2name="bkg";

     vector<Double_t> mT_bins    ={60,90,120,160,200};
     vector<Double_t> mll_bins   ={20,80,140,200};
//   vector<Double_t> mll_bins   ={20,80,120,160,200};
     TH2D* h2[9];
     for(int i=0;i<9;i++){
	     h2[i]=new TH2D(th2name+Form("_%d",i),"",mT_bins.size()-1,&mT_bins[0],mll_bins.size()-1,&mll_bins[0]);
     }
     double lumi;
     if(tag.Contains("16"))lumi=35.86;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=actualWeight*lumi;
	     if(name.Contains("plj")||name.Contains("fake")) actualWeight=scalef;
             if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;
	     if (  tformula1->EvalInstance() ){ 
		if (mT>=200) mT=199;
		if (mll>=200) mll=199;
                if(mllg>300) mllg=299;
		for(int j=0;j<9;j++){
			h2[j]->Fill(mT,mll,actualWeight*LHEScaleWeight[j]);
		}
	     }

     }
     TH1D*hist[9];
     for(int i=0;i<9;i++){
	     hist[i]=unroll(h2[i]);
     }
     TFile*fout=new TFile("./root/hist_"+name+"_"+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<9;i++){
	     hist[i]->Write();
	     h2[i]->Write();
     }
     fout->Close();
}
int Build_Hist(){
	TString LEP = "((HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_isprompt==1 && lep2_isprompt==1 && lep1_is_tight==1 && lep2_is_tight==1)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1)";
	TString met="(n_bjets==0 && PuppiMET_T1Smear_pt > 20 && mT2>30 && mT>60 )";
	vector<TString> tags={"17","18"};
	TString dir1;
	dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/SR/output-slimmed-rootfiles/optimal_emua_";
	TString Reco;
	vector<TString> names={"TTGJets","WWG_emu"};
	for(int k=0;k<tags.size();k++){
		Reco= LEP+"&&"+photon+"&&"+met;
		for(int j=0;j<names.size();j++){     
			run(dir1,names[j],Reco,tags[k]);
		}
	}
	return 1;
}
