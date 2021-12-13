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
void run(TString dir,TString name,TString Reco,TString Gen,TString vec_branchname,vector<double> bins1,vector<double> bins2, TString njets,TString tag){
     TString fname=name+tag;
     TFile*file;
     file=new TFile(dir+fname+".root") ;
     cout<<tag<<" "<<name<<" "<<endl;
     TTree*tree=(TTree*)file->Get("Events");
     float actualWeight,scalef,mT;
     map<TString, float> variable;
     tree->SetBranchAddress(vec_branchname, &variable[vec_branchname]);
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("actualWeight", &actualWeight);
     tree->SetBranchAddress("mT", &mT);
     TString th2name,th2name_out;
     if(name.Contains("WWG")) {
	     th2name="sig";
     }
     else  th2name="bkg";
             
     TH2D* h2=new TH2D(th2name,"",bins1.size()-1,&bins1[0],bins2.size()-1,&bins2[0]);
     TH2D* hout=new TH2D(th2name+"_out","",bins1.size()-1,&bins1[0],bins2.size()-1,&bins2[0]);
     double lumi;
     if(tag.Contains("16"))lumi=35.86;else if(tag.Contains("17"))lumi=41.52;else if(tag.Contains("18"))lumi=59.7;
     TString cut,cut1;
     if(name.Contains("WWG")==0) cut=Reco;
     else{
	     cut="("+Reco + ") && (" + Gen +")";
	     cut1="("+Reco + ") && !(" + Gen +")";
     }
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
     TTreeFormula *tformula2=new TTreeFormula("formula1", cut1, tree);
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     actualWeight=actualWeight*lumi;
	     if(name.Contains("plj")||name.Contains("fake")) actualWeight=scalef;
             if(name.Contains("Muon")||name.Contains("Ele")) actualWeight=1;
	     if (mT>=bins1[bins1.size()-1])  mT=bins1[bins1.size()-1]-1;
	     if(variable[vec_branchname]>=bins2[bins2.size()-1])
		     variable[vec_branchname]=bins2[bins2.size()-1]-1;
	     if (  tformula1->EvalInstance() ){ 
		     if (mT>=bins1[bins1.size()-1])  mT=bins1[bins1.size()-1]-1;
		     cout<<actualWeight<<" "<<mT<<" "<<variable[vec_branchname]<<endl;
		     h2->Fill(mT,variable[vec_branchname],actualWeight);
	     }
	     if(name.Contains("WWG") && tformula2->EvalInstance()){
		     if (mT>=bins1[bins1.size()-1])  mT=bins1[bins1.size()-1]-1;
		     hout->Fill(mT,variable[vec_branchname],actualWeight);
	     }
 
     }
     TH1D*hist=unroll(h2);
     TH1D*hist_out;
     if(h2->GetSum()!=h2->GetSumOfWeights())
	     cout<<"the overflow bin is not included"<<endl;
     if(name.Contains("WWG"))
	     hist_out=unroll(hout);
     TFile*fout=new TFile("./root/hist_"+name+"_"+vec_branchname+"_"+njets+"jets_"+tag+".root","recreate");
     fout->cd();
     hist->Write();
     h2->Write();
     if(name.Contains("WWG")){
	     hist_out->Write();
	     hout->Write();
     }
     fout->Close();
}
int Build_Hist(){
	TString LEP = "((HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>50 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1)";
        TString photon = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1 )";
	TString GenLEP = "( gen_channel==1 && fabs(genlep1)==13 && fabs(genlep2)==11 && gendrll>0.5 && genlep1pt>20 && genlep2pt>25 && fabs(genlep1eta) < 2.4 && fabs(genlep1eta) < 2.5 && genptll>30 && genmll>50 )";
        TString GenPHOTON = "( genphotonet>20 && ( fabs(genphotoneta)<1.4442 || (fabs(genphotoneta)<2.5 && fabs(genphotoneta)>1.566 )) && gendrl1a>0.5 && gendrl2a>0.5 )";
	TString GenMET = "(GenMET_pt>20 && genmT2>20)";

	TString met;
	vector<TString> tags={"17","18"};
        vector<TString> vars={"mllg"};
	vector<Double_t> mT_bins;
	vector<Double_t> mllg_bins={15,155,315,500};
        
	TString dir1;
	TString Reco,Gen;
	vector<TString> names={"WWG_emu"};
        vector<TString>njets={"0","1","2"};
	TString jet_cut,genjet_cut;
	for(int ij=0;ij<njets.size();ij++){
		if(ij==0) mT_bins={0,90,130,200};
		else if(ij==1) mT_bins={0,80,110,150,200};
		else if(ij==2) mT_bins={0,80,110,150,200};
		if(ij<2){
			jet_cut="(njets30=="+njets[ij]+")";
			genjet_cut="(n_genbjets>0 && n_genjets30=="+njets[ij]+")";
		}
		else{
			jet_cut="(njets30<=1)";
			genjet_cut="(n_genbjets>0 && n_genjets30<=1)";
		}
		for(int k=0;k<tags.size();k++){
			dir1="/home/pku/anying/cms/rootfiles/WWg/20"+tags[k]+"/Genlep1-out";
			for(int j=0;j<names.size();j++){     
				if(names[j].Contains("Muon")==0){
					met="(n_bjets_nom>0 && PuppiMET_T1Smear_pt > 20 && mT2>20 && "+jet_cut+")";
				}
				else{
					met="(n_bjets_nom>0 && PuppiMET_T1_pt > 20 && mT2>20 &&"+jet_cut+")";
				}
				Reco= "(" +LEP+"&&"+photon+"&&"+met +")";
				Gen = "(" + GenLEP +"&&"+GenPHOTON + "&&" + GenMET + "&&"+genjet_cut +")" ;
				cout<<Gen<<" "<<Reco<<endl;
				for(int i=0;i<vars.size();i++){     

					run(dir1,names[j],Reco,Gen,vars[i],mT_bins,mllg_bins,njets[ij],tags[k]);
				}
			}
		}
	}
	return 1;
}
