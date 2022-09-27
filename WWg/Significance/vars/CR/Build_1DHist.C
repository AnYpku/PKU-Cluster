#define pi 3.1415926
TH1D*unroll(TH2D*h2){
	TString histname=h2->GetName();
	TH1D*h1=new TH1D("hist_"+histname,"",h2->GetNbinsX()*h2->GetNbinsY()+0,0,h2->GetNbinsX()*h2->GetNbinsY()+0);
	for(int iy=1;iy<=h2->GetNbinsY();iy++){
		for(int ix=1;ix<=h2->GetNbinsX();ix++){
                   int i=ix+h2->GetNbinsX()*(iy-1);
                   cout<<iy<<" "<<ix<<" "<<i<<endl;
                   h1->SetBinContent(i,h2->GetBinContent(ix,iy));
                   h1->SetBinError(i,h2->GetBinError(ix,iy));
                   if(h2->GetBinContent(ix,iy)<0){
			   h1->SetBinContent(i,0);
			   h1->SetBinError(i,0);
		   }
		}
	}
	return h1;
}
void run(TString dir,TString name,TString cut,TString vec_branchname,vector<double> bins1, TString njets,TString tag){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<endl;
     TTree*tree=(TTree*)file->Get("outtree");
     float actualWeight,scalef;
     map<TString, float> variable;
     tree->SetBranchAddress(vec_branchname, &variable[vec_branchname]);
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("actualWeight", &actualWeight);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="hist_sig";
     }
     else  th2name="hist_bkg";
             
     TH1D* h2=new TH1D(th2name,"",bins1.size()-1,&bins1[0]);
     double lumi;
     if(tag.Contains("16pre"))lumi=19.5;else if(tag.Contains("16")) lumi=16.8;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=actualWeight*lumi;
	     if(name.Contains("plj")||name.Contains("fake")) actualWeight=scalef;
             if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;
	     if (  tformula1->EvalInstance() ){ 
                if(variable[vec_branchname]>=bins1[bins1.size()-1])
                        variable[vec_branchname]=bins1[bins1.size()-1]-1;
		h2->Fill(variable[vec_branchname],actualWeight);
	     }

     }
     for(int i=0;i<h2->GetNbinsX();i++){
	     if(h2->GetBinContent(i+1)<0)
		     h2->SetBinContent(i+1,0);
     }
     TFile*fout=new TFile("./root/hist_1D_"+name+"_"+vec_branchname+"_"+njets+"jets_"+tag+".root","recreate");
     fout->cd();
     h2->Write();
     fout->Close();
}
int Build_1DHist(){
	TString LEP = "( channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 )";
	TString met;
	vector<TString> tags={"16","16pre","18","17"};
        vector<TString> vars={"mT_puppi"};
	vector<Double_t> mT_bins;
	vector<Double_t> vars_bins={20,30,50,400};
        
	TString dir1;
	dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/Top_gamma/rootfiles/optimal_emua_";
	TString Reco;
	vector<TString> names={"ZGJets","TTGJets","TTJets","VV","ST","plj","fakeL","tZq","WGJets","WWG_emu_tot","MuonEG","Ele","Muon"};
        vector<TString>njets={"0"};
	TString jet_cut;
	for(int ij=0;ij<njets.size();ij++){
		if(ij!=2)
			jet_cut="(njets30_pc=="+njets[ij]+")";
		else
			jet_cut="(njets30_pc<=1)";
		for(int i=0;i<vars.size();i++){     
			if(vars[i].Contains("mllg"))
				vars_bins={20,150,250,400};
			else if(vars[i].Contains("mT"))
				vars_bins={0,90,120,160,200};
			for(int k=0;k<tags.size();k++){
				for(int j=0;j<names.size();j++){     
					if(names[j].Contains("Muon")==0&&names[j].Contains("Ele")==0)
						met="(n_bjets20_medium_deepFlavB_pc>0 && PuppiMET_pt > 20  && "+jet_cut+")";
					else
						met="(n_bjets20_medium_deepFlavB_pc>0 && PuppiMET_pt > 20 && "+jet_cut+")";
					Reco= LEP+"&&"+photon+"&&"+met;
					//Reco= met;
					run(dir1,names[j],Reco,vars[i],vars_bins,njets[ij],tags[k]);
				}
			}
		}
	}
	return 1;
}
