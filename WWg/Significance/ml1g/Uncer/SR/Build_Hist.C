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
void run(TString dir,TString name,TString cut,TString tag,TString njets,TString vec_branchname,vector<double> bins1,vector<double> bins2,TString type,int num){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<" njets "<<njets<<" "<<vec_branchname<<" "<<type<<endl;
     TTree*tree=(TTree*)file->Get("outtree");
     double actualWeight,scalef,mT;
     float weight[num];
     double scalef_up,scalef_down;
     map<TString, float> variable;
     tree->SetBranchAddress(vec_branchname, &variable[vec_branchname]);
     if(type.Contains("btag")){
	     tree->SetBranchAddress("btag_weight",     &weight[0]);
	     tree->SetBranchAddress("btag_weight_up",  &weight[1]);
	     tree->SetBranchAddress("btag_weight_down",&weight[2]);
     }
     if(type.Contains("l1pref")){
	     tree->SetBranchAddress("PrefireWeight",     &weight[0]);
	     tree->SetBranchAddress("PrefireWeight_Up",  &weight[1]);
	     tree->SetBranchAddress("PrefireWeight_Down",&weight[2]);
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
     tree->SetBranchAddress("actualWeight", &actualWeight);
     tree->SetBranchAddress("mT", &mT);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="sig";
     }
     else  th2name="bkg";

     TH2D* h2[num];
     for(int i=0;i<num;i++){
	     h2[i]=new TH2D(th2name+Form("_%d",i),"",bins1.size()-1,&bins1[0],bins2.size()-1,&bins2[0]);
     }
     double lumi;
     if(tag.Contains("16"))lumi=35.86;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=actualWeight*lumi;
	     if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;
             if( type.Contains("fakephoton")) actualWeight=1;
	     if( type.Contains("scale")==0 && type.Contains("pdf")==0 && type.Contains("fakephoton")==0)
		     actualWeight=actualWeight/weight[0];
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
}
int Build_Hist(){
	TString LEP = "((HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_isprompt==1 && lep2_isprompt==1 && lep1_is_tight==1 && lep2_is_tight==1)";
	TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1)";
	TString met;
	vector<TString> tags={"17","18"};
	TString dir1;
	dir1="/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/SR/output-slimmed-rootfiles/optimal_emua_";
	TString Reco;
	vector<TString> types={"btag","l1pref","pileup","pdf","scale","fakephoton"};
	vector<TString> names;
	vector<TString> vars={"ml1g","ml2g","mllg"};
	vector<vector<Double_t>> bins2;
	vector<Double_t> mT_bins;
	vector<Double_t> ml1g_bins={10,80,140,200};
	vector<Double_t> ml2g_bins={10,50,90,200};
	vector<Double_t> mllg_bins={15,155,315,500};
	bins2=get_vector(ml1g_bins,ml2g_bins,mllg_bins);

	vector<TString>njets={"0","1"};
	TString jet_cut;
	int num;
	for(int ij=0;ij<njets.size();ij++){
		if(ij==0) mT_bins={60,95,120,140,200};
		if(ij==1) mT_bins={60,105,150,200};
		jet_cut="(njets30=="+njets[ij]+")";
		for(int ik=0;ik<types.size();ik++){
                        if(types[ik].Contains("fakephoton")){
				dir1="./cutla-out";
                                names={"plj_unc"};
			} 
			else names={"ZGJets","TTGJets","VV","ST","tZq","TGJets","WGJets","WWG_emu"};
                        if(types[ik].Contains("scale")) num=9;
                        else if(types[ik].Contains("pdf")) num=103;
			else num=3;
			for(int j=0;j<names.size();j++){     
				if(names[j].Contains("Muon")==0)
					met="(n_bjets==0 && PuppiMET_T1Smear_pt > 20 && mT2>30 && mT>60 &&"+jet_cut+")";
				else
					met="(n_bjets==0 && PuppiMET_T1_pt > 20 && mT2>30 && mT>60 &&"+jet_cut+")";
				Reco= LEP+"&&"+photon+"&&"+met;
				for(int k=0;k<tags.size();k++){
					for(int i=0;i<vars.size();i++){
						run(dir1,names[j],Reco,tags[k],njets[ij],vars[i],mT_bins,bins2[i],types[ik],num);
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
