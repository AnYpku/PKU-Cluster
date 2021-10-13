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
void run(TString dir,TString name,TString cut,TString njets,TString tag){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<endl;
     TTree*tree=(TTree*)file->Get("outtree");
     double actualWeight,scalef,mT;
     float mll,mllg,ml1g,ml2g;
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("actualWeight", &actualWeight);
     tree->SetBranchAddress("mT", &mT);
     tree->SetBranchAddress("mll", &mll);
     tree->SetBranchAddress("mllg", &mllg);
     tree->SetBranchAddress("ml1g", &ml1g);
     tree->SetBranchAddress("ml2g", &ml2g);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="sig";
     }
     else  th2name="bkg";
             
     vector<Double_t> mT_bins    ={0,80,110,150,200};
     vector<Double_t> ml1g_bins   ={5,60,90,200};
     vector<Double_t> ml2g_bins   ={5,60,90,200};
     vector<Double_t> mllg_bins   ={60,120,200,300};
     TH2D* h2=new TH2D(th2name,"",mT_bins.size()-1,&mT_bins[0],ml1g_bins.size()-1,&ml1g_bins[0]);
//   TH2D* h2=new TH2D(th2name,"",mT_bins.size()-1,&mT_bins[0],ml2g_bins.size()-1,&ml2g_bins[0]);
//   TH2D* h2=new TH2D(th2name,"",mT_bins.size()-1,&mT_bins[0],mllg_bins.size()-1,&mllg_bins[0]);
     double lumi;
     if(tag.Contains("16"))lumi=35.86;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=actualWeight*lumi;
	     if(name.Contains("plj")||name.Contains("fake")) actualWeight=scalef;
             if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;
	     if (  tformula1->EvalInstance() ){ 
                if (mT>=200) mT=199;if (mll>=200) mll=199;
                if(mllg>300) mllg=299;if(ml1g>200) ml1g=199;if(ml2g>200) ml2g=199;
                h2->Fill(mT,ml1g,actualWeight);
//              h2->Fill(mT,ml2g,actualWeight);
//              h2->Fill(mT,mllg,actualWeight);
	     }

     }
     TH1D*hist=unroll(h2);
     TFile*fout=new TFile("./root/hist_"+name+"_"+njets+"jets_"+tag+".root","recreate");
     fout->cd();
     hist->Write();
     h2->Write();
     fout->Close();
}
int Build_Hist(){
	TString LEP = "((HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>50 && lep1_charge*lep2_charge<0 && drll>0.5)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 )";
	TString met;
	vector<TString> tags={"17","18"};
	TString dir1;
	dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/Top_gamma/output-slimmed-rootfiles/optimal_emua_";
	TString Reco;
	vector<TString> names={"ZGJets","TTGJets","VV","ST","plj","fakeL","tZq","TGJets","WGJets","WWG_emu","MuonEG"};
        vector<TString>njets={"0","1","2"};
        TString jet_cut;
	for(int ij=0;ij<njets.size();ij++){
                if(ij!=2)
                        jet_cut="(njets30=="+njets[ij]+")";
                else
                        jet_cut="(njets30>="+njets[ij]+")";
		for(int k=0;k<tags.size();k++){
			for(int j=0;j<names.size();j++){     
				if(names[j].Contains("Muon")==0)
					met="(n_bjets>=1 && PuppiMET_T1Smear_pt > 20 && mT2>30 && "+jet_cut+")";
				else
					met="(n_bjets>=1 && PuppiMET_T1_pt > 20 && mT2>30 && "+jet_cut+")";
				Reco= LEP+"&&"+photon+"&&"+met;
				run(dir1,names[j],Reco,njets[ij],tags[k]);
			}
		}
	}
	return 1;
}
