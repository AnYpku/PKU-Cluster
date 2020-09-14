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
	if(tag.Contains("16")==0)
		dir="/eos/user/y/yian/"+tag+"cutla/";
	else    dir="/eos/user/y/yian/"+tag+"legacy/";

	TString filename = isEW? dir+"outZA-EWK.root": dir+"cutlep-outZA.root";

        TFile*file=new TFile(filename);

	TTree*tree=(TTree*)file->Get("demo");
        double photon_pt[6],photon_eta[6];double photon_hoe[6],photon_sieie[6], photon_chiso[6],photon_nhiso[6],photon_phoiso[6]; bool photon_pev[6];
        double scalef,pileupWeight,prefWeight;
	double jet1pt, jet2pt, jet1eta, jet2eta, Mjj; 

        map<TString, double[6]> var;//transfer TString to double
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
/*
	temp = {0}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3,4}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3,4,5}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3,4,5,6}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3,4,5,6}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3,4,5,6}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3,4,5,6}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
        temp = {0,1,2,3,4,5,6}; vec_cuts.push_back(temp); vec_eff.push_back(0); vec_yields.push_back(0); vec_error.push_back(0);
*/
 
        bool tmp_photon_barrel[6], tmp_photon_endcap[6];

	bool doTest=false;

	int max= tree->GetEntries();
	if(doTest) max=200;

	for(int i=0;i<max;i++){
		//numb=0;numbe=0;
		if(doTest) if (i%1000==0) cout<<"Proceding event "<< i << "/"<<tree->GetEntries()<<" ----------------"<<endl;
		tree->GetEntry(i);

		//cout<<scalef<<endl;

                totalweight=scalef*pileupWeight*prefWeight*lumi;

		if (  !tformula->EvalInstance() ) continue;
		//max_ptb=photon_pt[0];posb_max=0;
                //max_pte=photon_pt[0];pose_max=0;
/*
		for(int j=0;j<6;j++){

                        PHOTON_barrel[j]=photon_pev[j]==1 && photon_hoe[j]<0.02197 && photon_nhiso[j]<1.189 + 0.01512*photon_pt[j]+0.00002259*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.08 + 0.004017*photon_pt[j]&&fabs(photon_eta[j])<1.4442&&photon_pt[j]>20&&photon_pt[j]<400;
                        PHOTON_endcap[j]=photon_pev[j]==1 && photon_hoe[j]<0.0326 && photon_nhiso[j]<2.718 + 0.0117*photon_pt[j] + 0.000023*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<3.867 + 0.0037*photon_pt[j]&& ( fabs(photon_eta[j]) )<2.5&&fabs(photon_eta[j])>1.566&& photon_pt[j]>20&&photon_pt[j]<400;

                        PHOTON_barrel[j]=  1;
                        PHOTON_endcap[j]=  1;
                        //PHOTON_barrel[j]=  photon_pev[j]==1 && photon_hoe[j]<0.02197 && fabs(photon_eta[j])<1.4442&&photon_pt[j]>100;
                        //PHOTON_endcap[j]=  photon_pev[j]==1 && photon_hoe[j]<0.0326 && ( fabs(photon_eta[j])<2.5&&fabs(photon_eta[j])>1.566 )&& photon_pt[j]>100;
		}
*/
		//if ( !( ElementPass(PHOTON_barrel, 6) || ElementPass(PHOTON_endcap, 6) ) ) continue; 

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

/*
	TCanvas *c1 = new TCanvas("c1","",800,600);
	hentries->Draw("HIST E");


        TCanvas *c2 = new TCanvas("c2","",800,600);
	hyields->Draw("HIST E");
*/

/*
			PHOTON_barrel[j]=photon_pev[j]==1 && photon_hoe[j]<0.02197 && photon_nhiso[j]<1.189 + 0.01512*photon_pt[j]+0.00002259*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.08 + 0.004017*photon_pt[j]&&fabs(photon_eta[j])<1.4442&&photon_pt[j]>20&&photon_pt[j]<400;
			PHOTON_endcap[j]=photon_pev[j]==1 && photon_hoe[j]<0.0326 && photon_nhiso[j]<2.718 + 0.0117*photon_pt[j] + 0.000023*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<3.867 + 0.0037*photon_pt[j]&& ( fabs(photon_eta[j]) )<2.5&&fabs(photon_eta[j])>1.566 )&& photon_pt[j]>20&&photon_pt[j]<400;

			if((PHOTON_barrel[j])){
				if(photon_pt[j]>max_ptb){
					max_ptb=photon_pt[j];
					posb_max=j;
				}
				numb++;
			}
			if(PHOTON_endcap[j]){
				if(photon_pt[j]>max_pte){
					max_pte=photon_pt[j];
					pose_max=j;
				}
				nume++;
			}


		}
                if(photon_sieie[posb_max]<mediume_barrel||photon_sieie[pose_max]<mediume_endcap){
		}
		count++;

	}
	cout<<"after LEP cuts, there are "<<nlep<<" events left"<<endl;
	cout<<"after LEP and "<<branchname2<<" cuts, there are "<<count<<" events left"<<endl;
*/
	cout<<endl;



}
int cuts_eff(){
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && (HLT_Mu1>0||HLT_Mu2>0 || HLT_Mu3>0)";// && (jet1pt>30 && jet2pt>30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) && Mjj>500. && fabs(jet1eta-jet2eta)>2.5";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && (HLT_Ele1 >0 || HLT_Ele2 >0) ";
	TString LEP = "("+LEPmu+")||("+LEPele+")";
//	TString LEP = "("+LEPele+")";
//	TString LEP = "("+LEPmu+")";
	//vector<TString> branch={"photon_pt","photon_hoe","photon_sieie","photon_chiso","photon_nhiso","photon_phoiso"};
	//vector<double> medium_barrel={20,0.02197,0.01015,1.141,1.189,2.08 };
	//vector<double> medium_endcap={20,0.0326, 0.0272, 1.051,2.718,3.867};
	//for(int i=0;i<branch.size();i++){
	//	run(branch[i]/*,medium_barrel[i],medium_endcap[i],*/LEP,"2017");
	//}
	
	//QCD samples
//	run(LEP,"2017", 30488043, 41.52, false);
//	run(LEP,"2016", 20967964, 35.86, false);
//	run(LEP,"2018", 13946364, 58.7, false);
	
	//EWK samples
	run(LEP,"2017", 299973, 41.52, true);
	run(LEP,"2018", 287399, 58.7, true);
        run(LEP,"2016", 299991, 35.86, true);
	
	return 1;
}
