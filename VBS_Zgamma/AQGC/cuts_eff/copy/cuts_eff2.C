int TotalEntries=30488043;


bool ElementPass(bool array[], int size){
	for (int i=0; i<size; i++){
	//cout<<array[i]<<endl;
		if (array[i]==1) return true;
	}

	return false;
}


struct CutScan1D {

	TString	Var;
	vector<double>	ListOfWPs;
	vector<double>	ListOfEffs; 	
	bool isUpper;
	bool isAbs;

};


bool ApplySelection(map<TString, double[6]> map_var, int j){

	bool  Cut_Barrel = 1; 
	Cut_Barrel = Cut_Barrel && map_var["photon_hoe"][j]<0.02197;
	Cut_Barrel = Cut_Barrel && map_var["photon_chiso"][j]<1.141;
	Cut_Barrel = Cut_Barrel && map_var["photon_nhiso"][j]<1.189 + 0.01512*map_var["photon_pt"][j]+0.00002259*map_var["photon_pt"][j]*map_var["photon_pt"][j];
	Cut_Barrel = Cut_Barrel && map_var["photon_phoiso"][j]<2.08 + 0.004017*map_var["photon_pt"][j];
	Cut_Barrel = Cut_Barrel && fabs(map_var["photon_eta"][j])<1.4442;
        Cut_Barrel = Cut_Barrel && fabs(map_var["photon_pt"][j])>20;

	bool Cut_Endcap = 1;
	Cut_Endcap = Cut_Endcap && map_var["photon_hoe"][j]<0.0326;
	Cut_Endcap = Cut_Endcap && map_var["photon_chiso"][j]<1.051;
	Cut_Endcap = Cut_Endcap && map_var["photon_nhiso"][j]<2.718 + 0.0117*map_var["photon_pt"][j] + 0.000023*map_var["photon_pt"][j]*map_var["photon_pt"][j];
	Cut_Endcap = Cut_Endcap && map_var["photon_phoiso"][j]<3.867 + 0.0037*map_var["photon_pt"][j];
	Cut_Endcap = Cut_Endcap && fabs(map_var["photon_eta"][j])<2.5 && fabs(map_var["photon_eta"][j])>1.566;
        Cut_Endcap = Cut_Endcap && fabs(map_var["photon_pt"][j])>20;

	return (Cut_Barrel || Cut_Endcap);
}



void run(/*double medium_barrel,double medium_endcap,*/TString cut1,TString tag, int TotalEntries=0){

	cout<<tag<<":"<<endl;
	TString dir;

	if(tag.Contains("16")==0)
		dir="/eos/user/y/yian/"+tag+"cutla/cutlep-";
	else    dir="/eos/user/y/yian/"+tag+"legacy/cutlep-";

        TFile*file=new TFile(dir+"outZA.root");
	TTree*tree=(TTree*)file->Get("demo");

//        double photon_pt[6],photon_eta[6];double photon_hoe[6],photon_sieie[6], photon_chiso[6],photon_nhiso[6],photon_phoiso[6]; 
        bool photon_pev[6];
        map<TString, double[6]> map_var;//transfer TString to double
	
	vector<TString> vec_vars = {"photon_pt", "photon_eta", "photon_chiso", "photon_nhiso", "photon_phoiso", "photon_sieie", "photon_hoe"};

	for ( TString var: vec_vars ) {
		map_var[var];
		tree->SetBranchAddress(var, map_var[var]);
	}
	tree->SetBranchAddress("photon_pev", photon_pev);


        TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);

	vector<CutScan1D> vec_Scan;

	CutScan1D temp_Scan;
	// pt scan
	temp_Scan.Var = "photon_pt";
	temp_Scan.ListOfWPs = {20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 400};
	temp_Scan.isUpper = false;
	temp_Scan.isAbs = false;
	vector<double> temp(temp_Scan.ListOfWPs.size(), 0);
	temp_Scan.ListOfEffs = temp;
	vec_Scan.push_back(temp_Scan);	
	// eta scam
	temp_Scan.Var = "photon_eta";
	temp_Scan.ListOfWPs = {0, 0.8, 1.442, 1.566, 2, 2.5};
	temp_Scan.isUpper = false;
	temp_Scan.isAbs = true;
	temp_Scan.ListOfEffs = temp;
	vec_Scan.push_back(temp_Scan);

        bool PHOTON_PASS[6];
        bool tmp_photon_pass[6];
	
	bool doTest=false;
	int max= tree->GetEntries();
	if(doTest) max=200;

	for(int i=0;i<max;i++){
		if(doTest) if (i%1000==0) cout<<"Proceding event "<< i << "/"<<tree->GetEntries()<<" ----------------"<<endl;
		tree->GetEntry(i);

		if (  !tformula->EvalInstance() ) continue;

		for(int j=0;j<6;j++){
			PHOTON_PASS[j] = photon_pev[j]==1 && ApplySelection(map_var, j);
		}
		if ( !( ElementPass(PHOTON_PASS, 6) ) ) continue; 
		
		// loop of Scan variables
		for (int j=0;j<vec_Scan.size();j++){
			bool isUpper = vec_Scan[j].isUpper;	
			bool isAbs = vec_Scan[j].isAbs;
			// loop of WPs
			for (int k=0; k<vec_Scan[j].ListOfWPs.size(); k++){
				// loop of Photons
				for (int m=0; m<6; m++){
					tmp_photon_pass[m] = PHOTON_PASS[m];
					if (isUpper){
						if (isAbs)	tmp_photon_pass[m] = tmp_photon_pass[m] && fabs(map_var[vec_Scan[j].Var][m]) < vec_Scan[j].ListOfWPs[k]; 
						else	tmp_photon_pass[m] = tmp_photon_pass[m] && map_var[vec_Scan[j].Var][m]<vec_Scan[j].ListOfWPs[k];
					}
					else{
						if (isAbs)	tmp_photon_pass[m] = tmp_photon_pass[m] && fabs(map_var[vec_Scan[j].Var][m]) > vec_Scan[j].ListOfWPs[k];	
						else	tmp_photon_pass[m] = tmp_photon_pass[m] && map_var[vec_Scan[j].Var][m]>vec_Scan[j].ListOfWPs[k];
					} 
//cout<<tmp_photon_pass[m];
				}
//cout<<endl;
				if ( ElementPass(tmp_photon_pass, 6) )	vec_Scan[j].ListOfEffs[k] += 1./TotalEntries;
			}
		}

	}

	for (int j=0;j<vec_Scan.size();j++){

		ofstream file("results/"+vec_Scan[j].Var+"_"+tag+".txt", ios::out | ios::trunc);
		file<<"Scan on variable: "<<vec_Scan[j].Var<<endl;
		file<<"isUpper WP: "<<vec_Scan[j].isUpper<<endl;
		file<<setw(20)<<"WP"<<setw(20)<<"Passed Events"<<endl;		

                cout<<"Scan on variable: "<<vec_Scan[j].Var<<endl;
                cout<<"isUpper WP: "<<vec_Scan[j].isUpper<<endl;
                cout<<setw(20)<<"WP"<<setw(20)<<"Passed Events"<<endl;

                TGraph *geff = new TGraph(vec_Scan[j].ListOfWPs.size(), &vec_Scan[j].ListOfWPs[0], &vec_Scan[j].ListOfEffs[0]);
		geff->GetXaxis()->SetTitle(vec_Scan[j].Var);
		geff->GetYaxis()->SetTitle("efficiency");	

		for (int k=0; k<vec_Scan[j].ListOfWPs.size(); k++){
			file<<setw(20)<<vec_Scan[j].ListOfWPs[k]<<setw(20)<<vec_Scan[j].ListOfEffs[k]<<endl;
			cout<<setw(20)<<vec_Scan[j].ListOfWPs[k]<<setw(20)<<vec_Scan[j].ListOfEffs[k]<<endl;
		}
		file.close();

		//TCanvas *c = new TCanvas("c","c",800,600);
		//TH1F *frame = new TH1F();		
		geff->SetMarkerStyle(20);	

		//geff->Draw("A L P");
		//c->SaveAs(vec_Scan[j].Var+"_"+tag+".png");
	
		TFile *fout = new TFile("results/"+vec_Scan[j].Var+"_"+tag+".root", "recreate");
		geff->Write();
		fout->Close();

	}




/*
	for (int index=0; index<vec_cuts.size(); index++ ){
		TString cut = "efficiency for cut [";
		for ( int option=0; option<vec_cuts[index].size(); option++ ){
			cut += vec_options[vec_cuts[index][option]]+"+"; 

		}
		cut[cut.Length()-1]=']';
		
		cut += Form(" = %i/%i = %.4f", vec_eff[index], TotalEntries, vec_eff[index]*1.0/TotalEntries);

		cout<<cut<<endl;

	}
*/
	cout<<endl;
}


int cuts_eff2(){
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString LEP = "("+LEPmu+")||("+LEPele+")";
	//vector<TString> branch={"photon_pt","photon_hoe","photon_sieie","photon_chiso","photon_nhiso","photon_phoiso"};
	//vector<double> medium_barrel={20,0.02197,0.01015,1.141,1.189,2.08 };
	//vector<double> medium_endcap={20,0.0326, 0.0272, 1.051,2.718,3.867};
	//for(int i=0;i<branch.size();i++){
	//	run(branch[i]/*,medium_barrel[i],medium_endcap[i],*/LEP,"2017");
	//}
	run(LEP,"2017", 30488043);
	run(LEP,"2016", 20967964);
	
	
	return 1;
}
