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
void run(TString dir,TString name,TString Reco,TString Gen,TString tag,TString njets,TString vec_branchname,vector<Double_t> bins1,vector<Double_t> bins2,TString type,int num){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<" njets "<<njets<<" "<<vec_branchname<<" "<<type<<endl;
     TTree*tree;
     tree=(TTree*)file->Get("Events");
     float actualWeight,scalef,mT;
     float weight[num];
     float scalef_up,scalef_down;
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
     if(type.Contains("id")||type.Contains("reco")||type.Contains("iso")||type.Contains("veto")){
             tree->SetBranchAddress(type+"_scale",&weight[0]);
             tree->SetBranchAddress(type+"_scale_Up",&weight[1]);
             tree->SetBranchAddress(type+"_scale_Down",&weight[2]);
     }

     tree->SetBranchAddress("actualWeight", &actualWeight);
     tree->SetBranchAddress("mT", &mT);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="sig";
     }
     else  th2name="bkg";

     TH2D* h2[num];TH2D* hout[num];
     for(int i=0;i<num;i++){
	     h2[i]=new TH2D(th2name+Form("_%d",i),"",bins1.size()-1,&bins1[0],bins2.size()-1,&bins2[0]);
	     hout[i]=new TH2D(th2name+Form("_out_%d",i),"",bins1.size()-1,&bins1[0],bins2.size()-1,&bins2[0]);
     }
     float lumi;
     if(tag.Contains("16"))lumi=35.86;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TString cut,cut1;
     if(name.Contains("WWG")==0) cut=Reco;
     else{
             cut="("+Reco + ") && (" + Gen +")";
             cut1="("+Reco + ") && !(" + Gen +")";
     }
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=actualWeight*lumi;
	     if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;
             if( type.Contains("fakephoton")) actualWeight=1;
	     if( type.Contains("scale")==0 && type.Contains("pdf")==0 && type.Contains("fakephoton")==0)
		     actualWeight=actualWeight/weight[0];
//	     cout<<weight[0]<<" "<<weight[1]<<" "<<weight[2]<<endl;
	     if (mT>=bins1[bins1.size()-1])
		     mT=bins1[bins1.size()-1]-1;
	     if(variable[vec_branchname]>=bins2[bins2.size()-1])
		     variable[vec_branchname]=bins2[bins2.size()-1]-1;
             if (  tformula1->EvalInstance() ){ 
		     if (mT>=bins1[bins1.size()-1])
			     mT=bins1[bins1.size()-1]-1;
		     if(variable[vec_branchname]>=bins2[bins2.size()-1])
			     variable[vec_branchname]=bins2[bins2.size()-1]-1;
		     for(int k=0;k<num;k++){
			     h2[k]->Fill(mT,variable[vec_branchname],actualWeight*weight[k]);
		     }
	     }
             if(name.Contains("WWG") && tformula2->EvalInstance()){
		     if (mT>=bins1[bins1.size()-1])
			     mT=bins1[bins1.size()-1]-1;
		     if(variable[vec_branchname]>=bins2[bins2.size()-1])
			     variable[vec_branchname]=bins2[bins2.size()-1]-1;
		     for(int k=0;k<num;k++){
			     hout[k]->Fill(mT,variable[vec_branchname],actualWeight*weight[k]);
		     }
             }

     }
     TH1D*hist[num];TH1D*hist_out[num];
     for(int i=0;i<num;i++){
	     if(h2[i]->GetSum()!=h2[i]->GetSumOfWeights())
		     cout<<"the overflow bin is not included"<<endl;
	     hist[i]=unroll(h2[i]);
	     if(name.Contains("WWG"))
		     hist_out[i]=unroll(hout[i]);
     }
     TFile*fout=new TFile("./root/hist_"+name+"_"+vec_branchname+"_"+njets+"jets_"+type+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<num;i++){
	     hist[i]->Write();
	     h2[i]->Write();
	     if(name.Contains("WWG")){
		     hist_out[i]->Write();
		     hout[i]->Write();
	     }
     }
     fout->Close();
}
int Build_Hist(){
        TString LEP = "((HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1)";
        TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1 )";
        TString GenLEP = "( gen_channel==1 && fabs(genlep1)==13 && fabs(genlep2)==11 && gendrll>0.5 && genlep1pt>20 && genlep2pt>25 && fabs(genlep1eta) < 2.4 && fabs(genlep1eta) < 2.5 && genptll>30 && genmll>20 )";
        TString GenPHOTON = "( genphotonet>20 && ( fabs(genphotoneta)<1.4442 || (fabs(genphotoneta)<2.5 && fabs(genphotoneta)>1.566 )) && gendrl1a>0.5 && gendrl2a>0.5 )";
        TString GenMET = "(GenMET_pt>20 && genmT>50 && genmT2>20)";
	TString met;

	vector<TString> tags={"17","18"};
	vector<TString>njets={"0","1","2"};
	vector<TString> types={"btag","l1pref","pileup","pdf","scale","ele_id","ele_reco","muon_id","muon_iso","photon_id","photon_veto"};
	vector<TString> names={"WWG_emu"};
	vector<TString> vars={"mllg"};
	vector<vector<Double_t>> bins2;
	vector<Double_t> mT_bins;
	vector<Double_t> mllg_bins={15,155,315,500};
        bins2.push_back(mllg_bins);

	TString dir1;
	TString jet_cut,genjet_cut;
	TString Gen = "(" + GenLEP +"&&"+GenPHOTON + "&&" + GenMET + ")" ;
	TString Reco;
	int num;
	for(int ij=0;ij<njets.size();ij++){
		if(ij==0) mT_bins={50,95,120,140,200};
		else if(ij==1) mT_bins={50,105,150,200};
		else mT_bins={50,95,120,140,200};
                if(ij!=2){
                        jet_cut="(njets30=="+njets[ij]+")";
                        genjet_cut="(n_genbjets==0 && n_genjets30=="+njets[ij]+")";
                }
                else{
                        jet_cut="(njets30<=1)";
                        genjet_cut="(n_genbjets==0 && n_genjets30<=1)";
                }
		for(int ik=0;ik<types.size();ik++){
                        if(types[ik].Contains("scale")) num=9;
                        else if(types[ik].Contains("pdf")) num=103;
			else num=3;
			for(int j=0;j<names.size();j++){     
				if(names[j].Contains("Muon")==0 && names[j].Contains("plj")==0 )
					met="(n_bjets_nom==0 && PuppiMET_T1Smear_pt > 20 && mT >50 && mT2>20 && "+jet_cut+")";
				else
					met="(n_bjets_nom==0 && PuppiMET_T1_pt > 20 && mT>50 && mT2>20 &&"+jet_cut+")";
                                Reco= "(" +LEP+"&&"+photon+"&&"+met +")";
				Gen = "(" + GenLEP +"&&"+GenPHOTON + "&&" + GenMET + "&&"+genjet_cut +")" ;
				for(int k=0;k<tags.size()-1;k++){
					dir1="/home/pku/anying/cms/rootfiles/WWg/20"+tags[k]+"/Genlep1-out";
					if(types[ik].Contains("l1pref") && tags[k].Contains("18"))
						continue;
					for(int i=0;i<vars.size();i++){
						run(dir1,names[j],Reco,Gen,tags[k],njets[ij],vars[i],mT_bins,bins2[i],types[ik],num);
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
