int TotalEntries=30488043;


bool ElementPass(bool array[], int size){
	for (int i=0; i<size; i++){
	//cout<<array[i]<<endl;
		if (array[i]==1) return true;
	}

	return false;
}


void run(/*double medium_barrel,double medium_endcap,*/TString cut1,TString tag, int TotalEntries=0, double lumi=0, bool isEW=1){

	cout<<tag<<":"<<endl;
	TString dir;
	dir="/home/pku/anying/cms/rootfiles/20"+tag+"/";

	TString filename = isEW? dir+"outZA-EWK"+tag+".root": dir+"cutlep-outZA"+tag+".root";
	cout<<filename<<endl;
        /*TChain*chain;
	chain=new TChain("ZPKUCandidates","");
        if(tag.Contains("17")||filename.Contains("EW")){
		chain->Add(filename);
	}
	else{
		chain->Add(dir+"outZA"+tag+".root");
		chain->Add(dir+"outZA"+tag+"_1.root");
	}
        TTree*tree;tree = chain;*/
        TFile*file=new TFile(filename);
	TTree*tree=(TTree*)file->Get("ZPKUCandidates");
        double photon_pt[6],photon_eta[6];double photon_hoe[6],photon_sieie[6], photon_chiso[6],photon_nhiso[6],photon_phoiso[6]; bool photon_pev[6];
        double scalef,pileupWeight,prefWeight;
	double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,puIdweight_M,muon_hlt_scale,ele_hlt_scale;
	double jet1pt, jet2pt, jet1eta, jet2eta, Mjj; 
	int lep;

        map<TString, double[6]> var;//transfer TString to double
        tree->SetBranchAddress("lep", &lep);
        tree->SetBranchAddress("photon_pt", photon_pt);
        tree->SetBranchAddress("photon_eta",photon_eta);
        tree->SetBranchAddress("photon_pev",photon_pev);
        tree->SetBranchAddress("photon_chiso",photon_chiso);
        tree->SetBranchAddress("photon_nhiso",photon_nhiso);
        tree->SetBranchAddress("photon_phoiso",photon_phoiso);
        tree->SetBranchAddress("photon_sieie",photon_sieie);
        tree->SetBranchAddress("photon_hoe",photon_hoe);
        tree->SetBranchAddress("scalef",&scalef);
        tree->SetBranchAddress("pileupWeight",&pileupWeight);
        tree->SetBranchAddress("prefWeight",&prefWeight);
	tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
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
	tree->SetBranchAddress("jet1pt",&jet1pt);
	tree->SetBranchAddress("jet2pt",&jet2pt);
	tree->SetBranchAddress("jet1eta",&jet1eta);
	tree->SetBranchAddress("jet2eta",&jet2eta);
	tree->SetBranchAddress("Mjj",&Mjj);

	TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
	//bool PHOTON_barrel[6],PHOTON_endcap[6];
	//double max_ptb;int posb_max;
	//double max_pte;int pose_max;
	//double numb=0,numbe=0,countb=0,counte=0,nlep=0;

	double totalweight;

	vector<TString> vec_options = {"photon_eta", "photon_pev", "photon_pt", "photon_hoe", "photon_chiso", "photon_nhiso", "photon_phoiso", "jeteta", "jetpt", "djeta","mjj"} ;
	vector<vector<int>> vec_cuts;
	vector<int> vec_eff;
	vector<double> vec_yields;
	vector<double> vec_error;

	vector<int> temp;

	temp = {}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);

	for ( int i=0; i<vec_options.size(); i++){

		temp.push_back(i);
		vec_cuts.push_back(temp);
		vec_eff.push_back(0);
		vec_yields.push_back(0);
		vec_error.push_back(0);

	}

	bool tmp_photon_barrel[6], tmp_photon_endcap[6];

	bool doTest=false;

	int max= tree->GetEntries();
	if(doTest) max=200;

	for(int i=0;i<max;i++){
		//numb=0;numbe=0;
		if(doTest) if (i%1000==0) cout<<"Proceding event "<< i << "/"<<tree->GetEntries()<<" ----------------"<<endl;
		tree->GetEntry(i);

		//cout<<scalef<<endl;

             if(tag.Contains("18"))  prefWeight=1;
             if(tag.Contains("17")==0)  puIdweight_M=1;
             totalweight=scalef*pileupWeight*prefWeight*puIdweight_M*lumi;
	     if(lep==11)
		     totalweight=totalweight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*fabs(photon_id_scale*photon_veto_scale)*ele_hlt_scale;
	     if(lep==13)
		     totalweight=totalweight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*fabs(photon_id_scale*photon_veto_scale)*muon_hlt_scale;

		if (  !tformula->EvalInstance() ) continue;
		//max_ptb=photon_pt[0];posb_max=0;
		//max_pte=photon_pt[0];pose_max=0;

		for (int index=0; index<vec_cuts.size(); index++ ){
			//bool tmp_photon_barrel[6], tmp_photon_endcap[6];
			for (int arr_i=0; arr_i<6; arr_i++){
				tmp_photon_barrel[arr_i] = 1; //PHOTON_barrel[arr_i];
				tmp_photon_endcap[arr_i] = 1; //PHOTON_endcap[arr_i];	 

				for ( int icut=0; icut<vec_cuts[index].size(); icut++ ){

					if ( vec_options[vec_cuts[index][icut]] == "photon_eta" ) {
						//cout<<"pass 0";
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && fabs(photon_eta[arr_i])<1.4442;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && fabs(photon_eta[arr_i])<2.5 && fabs(photon_eta[arr_i])>1.566;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "photon_hoe" ) {
						//cout<<"pass 0";
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && photon_hoe[arr_i]<0.02197;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && photon_hoe[arr_i]<0.0326;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "photon_pev" ) {
						//cout<<"pass 0";
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && photon_pev[arr_i]==1;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && photon_pev[arr_i]==1;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "photon_pt" ) {
						//cout<<"pass 0";
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && photon_pt[arr_i]>100;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && photon_pt[arr_i]>100;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "photon_chiso" ) {
						//cout<<"pass 0";
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && photon_chiso[arr_i]<1.141; 
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && photon_chiso[arr_i]<1.051;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "photon_nhiso" ) {
						//cout<<"pass 1";
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && photon_nhiso[arr_i]<1.189 + 0.01512*photon_pt[arr_i]+0.00002259*photon_pt[arr_i]*photon_pt[arr_i]; 
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && photon_nhiso[arr_i]<2.718 + 0.0117*photon_pt[arr_i]+0.000023*photon_pt[arr_i]*photon_pt[arr_i];
					}
					else if ( vec_options[vec_cuts[index][icut]] == "photon_phoiso" ) {
						//cout<<"pass 2";
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && photon_phoiso[arr_i]<2.08 + 0.004017*photon_pt[arr_i];
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && photon_phoiso[arr_i]<3.867 + 0.0037*photon_pt[arr_i];
					}
					else if ( vec_options[vec_cuts[index][icut]] == "jeteta" ){
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "jetpt" ){
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && jet1pt>30 && jet2pt>30;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && jet1pt>30 && jet2pt>30;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "djeta" ){
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && fabs(jet1eta-jet2eta)>2.5;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && fabs(jet1eta-jet2eta)>2.5;
					}
					else if ( vec_options[vec_cuts[index][icut]] == "mjj" ){
						tmp_photon_barrel[arr_i] = tmp_photon_barrel[arr_i] && Mjj>500.;
						tmp_photon_endcap[arr_i] = tmp_photon_endcap[arr_i] && Mjj>500.;
					}
					//else cout<<"unknown selection!"<<endl;
					//cout<<endl;
				}
			}
			if ( ElementPass(tmp_photon_barrel, 6) || ElementPass(tmp_photon_endcap, 6) ) {
				vec_eff[index] += 1;	
				vec_yields[index] += totalweight;
				vec_error[index] += totalweight*totalweight;
			}
		}

	}

	TH1F *hentries = new TH1F("entries", "cut-flow of entries", vec_cuts.size(), 0, vec_cuts.size());
	TH1F *hyields = new TH1F("yields", "cut-flow of yields", vec_cuts.size(), 0, vec_cuts.size());
	TH1F *heff_entries = new TH1F("eff_entries", "cut-flow of entries efficiency", vec_cuts.size(), 0, vec_cuts.size());

	hentries->GetXaxis()->SetBinLabel(1, "pre-sel");
	hyields->GetXaxis()->SetBinLabel(1, "pre-sel");
	heff_entries->GetXaxis()->SetBinLabel(1, "pre-sel");

	for ( int index=0; index<vec_options.size(); index++ ){
		hentries->GetXaxis()->SetBinLabel(index+2, vec_options[index]);
		hyields->GetXaxis()->SetBinLabel(index+2, vec_options[index]);
		heff_entries->GetXaxis()->SetBinLabel(index+2, vec_options[index]);
	}


	for (int index=0; index<vec_cuts.size(); index++ ){
		TString cut = "For cut [";
		for ( int option=0; option<vec_cuts[index].size(); option++ ){
			cut += vec_options[vec_cuts[index][option]]+"+"; 
		}
		cut[cut.Length()-1]=']';

		cout<<cut<<endl;	

		cut = Form("Entries: %i/%i = %.4f", vec_eff[index], TotalEntries, vec_eff[index]*1.0/TotalEntries);

		cout<<cut<<endl;

		cout<<"yields: "<<vec_yields[index]<<"+-"<<sqrt(vec_error[index])<<endl;

		hentries->SetBinContent(index+1, vec_eff[index]);
		heff_entries->SetBinContent(index+1, vec_eff[index]*1./TotalEntries);
		heff_entries->SetBinError(index+1, sqrt(vec_eff[index]*1.)/TotalEntries);

		hyields->SetBinContent(index+1, vec_yields[index]);
		hyields->SetBinError(index+1, vec_error[index]); 

	}

	TString outfilename = isEW? "EWK/"+tag+"_results.root" : "QCD/"+tag+"_results.root";

	TFile *fout = new TFile(outfilename, "recreate");
	hentries->Write();
	hyields->Write();
	heff_entries->Write();
	fout->Close();


	cout<<endl;



}
int cuts_eff(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && (HLT_Mu1>0||HLT_Mu2>0))";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && (HLT_Ele1 >0 || HLT_Ele2 >0))";
	TString LEP = "("+LEPmu+")||("+LEPele+")";

	//QCD samples
//	run(LEP,"16", 30040390, 35.86, false);
//	run(LEP,"17", 30482963, 41.52, false);
	run(LEP,"18", 33805459, 59.7, false);

	//EWK samples
//	run(LEP,"17", 799717, 41.52, true);
//	run(LEP,"18", 879399, 59.7, true);
//	run(LEP,"16", 884668, 35.86, true);

	return 1;
}
