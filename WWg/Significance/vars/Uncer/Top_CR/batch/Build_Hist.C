#define pi 3.1415926
vector<vector<double>> get_vector(vector<double> v1,vector<double> v2,vector<double> v3);
TH1D*unroll(TH2D*h2){
	TString histname=h2->GetName();
	TH1D*h1=new TH1D("hist_"+histname,"",h2->GetNbinsX()*h2->GetNbinsY()+0,0,h2->GetNbinsX()*h2->GetNbinsY()+0);
	for(int iy=1;iy<=h2->GetNbinsY();iy++){
		for(int ix=1;ix<=h2->GetNbinsX();ix++){
                   int i=ix+h2->GetNbinsX()*(iy-1);
                   cout<<iy<<" "<<ix<<" "<<i<<endl;
                   h1->SetBinContent(i,h2->GetBinContent(ix,iy));
                   h1->SetBinError(i,h2->GetBinError(ix,iy));
		}
	}
	return h1;
}
void run(TString dir,TString name,TString cut,TString tag,TString njets,TString vec_branchname,vector<Double_t> bins1,vector<Double_t> bins2,TString type,int num){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<" njets "<<njets<<" "<<vec_branchname<<" "<<type<<endl;
     TTree*tree;
     tree=(TTree*)file->Get("outtree");
     float actualWeight,scalef,mT_pf,mT_puppi;
     float weight[num];
     float scalef_up,scalef_down;
     map<TString, float> variable;

     tree->SetBranchAddress(vec_branchname, &variable[vec_branchname]);
     if(type.Contains("btag")){
	     tree->SetBranchAddress("btag_weight_medium",     &weight[0]);
	     tree->SetBranchAddress("btag_weight_medium_up",  &weight[1]);
	     tree->SetBranchAddress("btag_weight_medium_down",&weight[2]);
     }
     if(type.Contains("l1pref")){
	     tree->SetBranchAddress("L1PreFiringWeight_Nom",     &weight[0]);
	     tree->SetBranchAddress("L1PreFiringWeight_Up",  &weight[1]);
	     tree->SetBranchAddress("L1PreFiringWeight_Dn",&weight[2]);
     }
     if(type.Contains("pileup")){
	     tree->SetBranchAddress("puWeight",    &weight[0]);
	     tree->SetBranchAddress("puWeightUp",  &weight[1]);
	     tree->SetBranchAddress("puWeightDown",&weight[2]);
     }
     if(type.Contains("fakephoton")){
	     tree->SetBranchAddress("scalef",     &weight[0]);
	     tree->SetBranchAddress("scalef_up",  &weight[1]);
	     tree->SetBranchAddress("scalef_down",&weight[2]);
     }
     if(type.Contains("pdf"))
	     tree->SetBranchAddress("LHEPdfWeight", weight);
     if(type.Contains("scale"))
	     tree->SetBranchAddress("LHEScaleWeight", weight);

     if(type.Contains("id")||type.Contains("reco")||type.Contains("iso")||type.Contains("veto")){
             tree->SetBranchAddress(type+"_scale",&weight[0]);
             tree->SetBranchAddress(type+"_scale_Up",&weight[1]);
             tree->SetBranchAddress(type+"_scale_Down",&weight[2]);
     }

     tree->SetBranchAddress("actualWeight", &actualWeight);
     tree->SetBranchAddress("mT_pf", &mT_pf);
     tree->SetBranchAddress("mT_puppi", &mT_puppi);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="sig";
     }
     else  th2name="bkg";

     TH2D* h2[num];
     for(int i=0;i<num;i++){
	     h2[i]=new TH2D(th2name+Form("_%d",i),"",bins1.size()-1,&bins1[0],bins2.size()-1,&bins2[0]);
     }
     float lumi;
     if(tag.Contains("pre16"))lumi=19.5;else if(tag.Contains("16")) lumi=16.8;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=actualWeight*lumi;
	     if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;
             if( type.Contains("fakephoton")) actualWeight=1;
	     if( type.Contains("scale")==0 && type.Contains("pdf")==0 && type.Contains("fakephoton")==0)
		     actualWeight=actualWeight/weight[0];
	     cout<<weight[0]<<" "<<weight[1]<<" "<<weight[2]<<endl;
	     double mT; mT=mT_puppi;
             if (  tformula1->EvalInstance() ){ 
		     if (mT>=bins1[bins1.size()-1])
			     mT=bins1[bins1.size()-1]-1;
		     if(variable[vec_branchname]>=bins2[bins2.size()-1])
			     variable[vec_branchname]=bins2[bins2.size()-1]-1;
		     for(int k=0;k<num;k++){
			     h2[k]->Fill(mT,variable[vec_branchname],actualWeight*weight[k]);
		     }
	     }

     }
     TH1D*hist[num];
     for(int i=0;i<num;i++){
	     hist[i]=unroll(h2[i]);
     }
     TFile*fout=new TFile("./root/hist_"+name+"_"+vec_branchname+"_"+njets+"jets_"+type+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<num;i++){
	     hist[i]->Write();
	     h2[i]->Write();
     }
     fout->Close();
     file->Close();
}
int Build_Hist(){
	TString LEP = "( channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_isprompt==1 && lep2_isprompt==1 && lep1_is_tight==1 && lep2_is_tight==1)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 )";
	TString met;
	vector<TString> tags={"16","16pre","17","18"};
	TString dir1;
	TString Reco;
	vector<TString> types={"btag","l1pref","pileup","pdf","scale","fakephoton","ele_id","ele_reco","muon_id","muon_iso","photon_id","photon_veto"};
	vector<TString> names;
	vector<TString> vars={"photonet","mllg","mll"};
	vector<vector<Double_t>> bins2;
	vector<Double_t> mT_bins;
        vector<Double_t> vars_bins={20,30,60,200};

	vector<TString>njets={"1","2"};
	TString jet_cut;
	int num;
	for(int ij=0;ij<njets.size();ij++){
		if(njets[ij]=="1") mT_bins={0,90,120,160,200};
		else if(njets[ij]=="2") mT_bins={0,90,120,160,200};
		if(njets[ij]!="2")jet_cut="(njets30_pc=="+njets[ij]+")";
		else     jet_cut="(njets30_pc<=1)";
		for(int i=0;i<vars.size();i++){
                        if(vars[i].Contains("mllg"))
                                vars_bins={20,150,250,400};
                        else if(vars[i].Contains("photonet"))
                                vars_bins={20,30,50,400};
                        else if(vars[i].Contains("ptllg"))
                                vars_bins={0,55,80,400};
                        else if(vars[i].Contains("mll"))
                                vars_bins={20,80,140,400};
			for(int ik=0;ik<types.size();ik++){
				if(types[ik].Contains("fakephoton")){
					dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/Top_gamma/rootfiles/optimal_emua_";
					names={"plj"};
				} 
				else if(types[ik].Contains("scale")||types[ik].Contains("pdf")){ 
					names={"TTGJets","TTJets","ST","WWG_emu_tot"};
					dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/Top_gamma/rootfiles/optimal_emua_";
				}
				else{
					names={"ZGJets","TTGJets","TTJets","VV","ST","tZq","WGJets","WWG_emu_tot"};
					dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/Top_gamma/rootfiles/optimal_emua_";
				}
				if(types[ik].Contains("scale")) num=9;
				else if(types[ik].Contains("pdf")) num=103;
				else num=3;
				for(int j=0;j<names.size();j++){     
					if(names[j].Contains("Muon")==0 && names[j].Contains("plj")==0 && names[j].Contains("Ele")==0 )
						met="(n_bjets20_medium_deepFlavB_pc>=1 && PuppiMET_pt > 20 && "+jet_cut+")";
					else
						met="(n_bjets20_medium_deepFlavB_pc>=1 && PuppiMET_pt > 20 && "+jet_cut+")";
					Reco= LEP+"&&"+photon+"&&"+met;
					for(int k=0;k<tags.size();k++){
						if(types[ik].Contains("l1pref") && tags[k].Contains("18"))
							continue;
						run(dir1,names[j],Reco,tags[k],njets[ij],vars[i],mT_bins,vars_bins,types[ik],num);
					}
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
