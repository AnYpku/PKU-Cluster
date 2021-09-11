#define num 103
#define pi 3.1415926
void run( TFile*file,vector<TString> vec_branchname,vector<vector<double>> bins,TString cut1,TString tag){
     const int kk = vec_branchname.size();
     TString name=file->GetName();
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
//     tree->SetBranchStatus("*",0);
     map<TString, double> variables;
     for(int i=0;i<vec_branchname.size();i++){
             tree->SetBranchStatus(vec_branchname[i],1);
	     tree->SetBranchAddress(vec_branchname[i], &variables[vec_branchname[i]]);
     }
     Double_t scalef,pileupWeight,pweight[703],prefWeight;
     double Mjj,deltaetajj;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,muon_hlt_scale,ele_hlt_scale,puIdweight_T,puIdweight_M,puIdweight_L;
     int lep;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("deltaetajj",&deltaetajj);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("pweight",pweight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
     tree->SetBranchAddress("photon_veto_scale", &photon_veto_scale);
     tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
     tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
     tree->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale);
     tree->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
     tree->SetBranchAddress("puIdweight_T", &puIdweight_T);
     tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
     tree->SetBranchAddress("puIdweight_L", &puIdweight_L);
     TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
     double actualWeight[num],weight,puIdweight;
     TH1D*th1[num][kk];
     TString th1name[num][kk];
     for(Int_t i=0;i<num;i++){
	     for(int j=0;j<kk;j++){
		     th1name[i][j]=vec_branchname[j]+Form("_%d",i);
		     th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins[j].size()-1,&bins[j][0]);
	     }
     }      
     cout<<tag<<" "<<name<<endl;
     for(int k=0;k<tree->GetEntries();k++){
	     tree->GetEntry(k);
	     int p=0;
	     int init;
	     if(tag.Contains("18")){prefWeight=1;puIdweight=puIdweight_L;}
	     if(tag.Contains("17")) puIdweight=puIdweight_T;
	     if(tag.Contains("16")) puIdweight=puIdweight_M;
	     weight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale*puIdweight;
	     if(lep==11)
		     weight=weight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
	     if(lep==13)
		     weight=weight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
	     if(tag.Contains("16")&&name.Contains("EWK"))
		     init=9;//16 ewk
	     else if(tag.Contains("16")&&name.Contains("EWK")==0)
		     init=0;//16 qcd
	     else if(( tag.Contains("17")||tag.Contains("18"))&&name.Contains("EWK"))
		     init=45;//17 ewk,18 ewk

	     if (  tformula->EvalInstance() ){
		     for(Int_t i=init;i<(num+init);i++){
			     actualWeight[p]=weight*pweight[i];
			     for(int j=0;j<kk;j++){
				     th1[p][j]->Fill(variables[vec_branchname[j]],actualWeight[p]);
			     }
			     p++;
		     }
	     }
     }
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	     if(name.Contains("EWK")==0){
		     fout[j]= new TFile("hist_"+vec_branchname[j]+"_qcd_pdf"+tag+".root","recreate");
	     }
	     else{
		     fout[j]= new TFile("hist_"+vec_branchname[j]+"_Sig_pdf"+tag+".root","recreate");
	     }
     }
     for(int j=0;j<kk;j++){
	     fout[j]->cd();
	     for(Int_t i=0;i<num;i++){
		     th1[i][j]->Write();
	     }
	     fout[j]->Close();
     }
     for(int j=0;j<kk;j++){
	     for(Int_t i=0;i<num;i++){
		     delete  th1[i][j];
	     }
     }
}
int Unfold_uncer_batch_bkg(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet ;
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)<2.5 && Mva>100)";
	vector<vector<double>> bins;
	vector<double> MjjBins={500,600,700,800};
	bins.push_back(MjjBins);

	TString dir[3];     
	TFile*file1[3];
	TFile*file2[3];

	vector<TString> recovars={"Mjj"};
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<3;i++){
		if(tag[i].Contains("16")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		}
		if(tag[i].Contains("18")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
		}
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut2 ="("+Reco+")";
//		if(tag[i].Contains("17")==0) continue;
		dir[i]="/home/pku/anying/cms/rootfiles/20"+tag[i]+"/";
		file1[i]=new TFile(dir[i]+"cutla-outZA-EWK"+tag[i]+".root");
		file2[i]=new TFile(dir[i]+"cutla-outZA"+tag[i]+".root");
		run(file1[i],recovars, bins,Reco,tag[i]);
		if(tag[i].Contains("16"))run(file2[i],recovars, bins,Reco,tag[i]);
	}
	return 1;
}
