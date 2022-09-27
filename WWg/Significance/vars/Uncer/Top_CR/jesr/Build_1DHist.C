#define pi 3.1415926
vector<vector<double>> get_vector(vector<double> v1,vector<double> v2,vector<double> v3);
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
void run(TString dir,TString name,TString cut,TString tag,TString type,TString njets,TString vec_branchname,vector<Double_t> bins1){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<endl;
     TTree*tree=(TTree*)file->Get("outtree");
     float scalef,actualWeight;
     float mll,mllg,ptll;
     float PuppiMET_phi,PuppiMET_pt;
     float lep1pt,lep2pt,lep1eta,lep2eta,lep1phi,lep2phi;
     map<TString, float> variables;
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     tree->SetBranchAddress("PuppiMET_pt"+type+"Up", &variables["PuppiMET_pt"+type+"Up"]);
     tree->SetBranchAddress("PuppiMET_pt"+type+"Down", &variables["PuppiMET_pt"+type+"Down"]);
     tree->SetBranchAddress("PuppiMET_phi"+type+"Up", &variables["PuppiMET_phi"+type+"Up"]);
     tree->SetBranchAddress("PuppiMET_phi"+type+"Down", &variables["PuppiMET_phi"+type+"Down"]);
     tree->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt);
     tree->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi);
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("ptll", &ptll);
     tree->SetBranchAddress("lep1pt", &lep1pt);
     tree->SetBranchAddress("lep2pt", &lep2pt);
     tree->SetBranchAddress("lep1eta", &lep1eta);
     tree->SetBranchAddress("lep2eta", &lep2eta);
     tree->SetBranchAddress("lep1phi", &lep1phi);
     tree->SetBranchAddress("lep2phi", &lep2phi);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="hist_sig";
     }
     else  th2name="hist_bkg";
             
     TH1D* h2[3];
     for(int i=0;i<3;i++){
	     h2[i]=new TH1D(th2name+Form("_%d",i),"",bins1.size()-1,&bins1[0]);
     }
     float lumi;
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
	     float phiVlep=(lep1p4+lep2p4).Phi();    
             float mT=sqrt(2*(ptll*PuppiMET_pt*(1-cos(phiVlep-PuppiMET_phi) ) ) );
	     float mT_Up=sqrt(2*(ptll*variables["PuppiMET_pt"+type+"Up"]*(1-cos(phiVlep-variables["PuppiMET_phi"+type+"Up"]) ) ) );
	     float mT_Down=sqrt(2*(ptll*variables["PuppiMET_pt"+type+"Down"]*(1-cos(phiVlep-variables["PuppiMET_phi"+type+"Down"]) ) ) );
             float lep_pt,lep_phi;
	     if(lep1pt>lep2pt){lep_pt=lep2pt;lep_phi=lep2phi;}
	     else{lep_pt=lep1pt;lep_phi=lep1phi;}
             float mT2=sqrt(2*(lep_pt*PuppiMET_pt*(1-cos(lep_phi-PuppiMET_phi) ) ) );
	     float mT2_Up=sqrt(2*(lep_pt*variables["PuppiMET_pt"+type+"Up"]*(1-cos(lep_phi-variables["PuppiMET_phi"+type+"Up"]) ) ) );
	     float mT2_Down=sqrt(2*(lep_pt*variables["PuppiMET_pt"+type+"Down"]*(1-cos(lep_phi-variables["PuppiMET_phi"+type+"Down"]) ) ) );
          
	     if (  ! tformula1->EvalInstance() ) continue;

	     if (mT>=bins1[bins1.size()-1])      mT     =bins1[bins1.size()-1]-1;
	     if (mT_Up>=bins1[bins1.size()-1])   mT_Up  =bins1[bins1.size()-1]-1;
	     if (mT_Down>=bins1[bins1.size()-1]) mT_Down=bins1[bins1.size()-1]-1;

	     if(PuppiMET_pt>20 )    
		     h2[0]->Fill(mT,actualWeight);
	     if(variables["PuppiMET_pt"+type+"Up"]>20)
		     h2[1]->Fill(mT_Up,actualWeight);
	     if(variables["PuppiMET_pt"+type+"Down"]>20)
		     h2[2]->Fill(mT_Down,actualWeight);

     }
     TFile*fout=new TFile("./root/hist_"+name+"_"+vec_branchname+"_"+njets+"jets_"+type+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<3;i++){
	     h2[i]->Write();
     }
     fout->Close();
     file->Close();
}
int Build_1DHist(){
	TString LEP = "( ( HLT_emu || HLT_ee || HLT_mm ) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1 )";
	TString met;
        vector<TString> types={"btag","l1pref","pileup","pdf","scale","fakephoton"};
        vector<TString> vars={"mT_puppi"};
        vector<Double_t> mT_bins;
        vector<Double_t> vars_bins={20,30,60,400};
	vector<TString> tags={"16","16pre","17","18"};
	TString dir1;
	TString Reco;
	vector<TString> names={"ZGJets","TTGJets","TTJets","VV","ST","tZq","WGJets","WWG_emu_tot"};
        vector<TString>njets={"0"};
        TString jet_cut;
	for(int ij=0;ij<njets.size();ij++){
		if(ij==0) mT_bins={0,90,120,160,200};
		else if(ij==1) mT_bins={0,90,120,160,200};
		else if(ij==2) mT_bins={0,90,120,160,200};
		if(ij!=2)jet_cut="(njets30_pc=="+njets[ij]+")";
		else jet_cut="(njets30<=1)";
		met="(n_bjets20_medium_deepFlavB_pc>=1 && "+jet_cut+")";
		Reco= LEP+"&&"+photon+"&&"+met;
		for(int i=0;i<vars.size();i++){
                        if(vars[i].Contains("mllg"))
                                vars_bins={20,150,250,400};
                        else if(vars[i].Contains("photonet"))
                                vars_bins={20,30,50,400};
                        else if(vars[i].Contains("ptllg"))
                                vars_bins={0,55,80,400};
                        else if(vars[i].Contains("mT"))
                                vars_bins={0,90,130,200};
			for(int j=0;j<names.size();j++){
				for(int k=0;k<tags.size();k++){
					TString y;
					if(tags[k].Contains("pre")) y="16";
					else y=tags[k];
					dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/Top_gamma/rootfiles/optimal_emua_";
					run(dir1,names[j],Reco,tags[k],"JER",njets[ij],vars[i],mT_bins);
					run(dir1,names[j],Reco,tags[k],"JES",njets[ij],vars[i],mT_bins);
				}
			}
		}
	}
	return 1;
}
vector<vector<double>> get_vector(vector<double> v1,vector<double> v2,vector<double> v3){
	vector<vector<double>> bins;
	bins.push_back(v1);
	bins.push_back(v2);
	bins.push_back(v3);
	return bins;
}
