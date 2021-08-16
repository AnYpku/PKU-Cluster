TH1D* run(TString cut,TString style,TString file,TString channel,TString extra){
	vector<double> ptbins={20,25,30,35,40,50,60,100,400};
	TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/cutlep-out"+file+".root");
	TTree*tree=(TTree*)f1->Get("Events");
        TString histname=style+"_"+file+"_"+channel;
        TH1D*h1 = new TH1D(histname,extra,ptbins.size()-1,&ptbins[0]);
	if(channel=="emu") cut = "( ( (channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1_is_tight==1 && lep2_is_tight==1 && n_loose_ele==1 && n_loose_mu==1 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>25 && fabs(lep2eta)<2.5 && drll>0.5 && lep1_charge*lep2_charge<0) && "+cut +")"+" && ((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) )";
//	cout<<cut<<endl; 
        cut=cut+"&&("+extra+")";
	if(file.Contains("Muon")||file.Contains("Ele"))
		tree->Draw("photonet>>"+histname,cut+"*1","goff");
	else{
		tree->Draw("photonet>>"+histname,cut+"*scalef","goff");

	}
	cout<<extra<<" "<<h1->GetSum()<<endl; 
	return h1;
}
int cal_weight(){
	TString cut1="( n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5 && fabs(photoneta)>1.566 ) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 )";
	TString cut2="( n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5 && fabs(photoneta)>1.566 ) ) && drl1a>0.5 && drl2a>0.5 && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection==5))";
        vector<TString> fname={"TTJets"};
	vector<TString> channel={"emu"};
	vector<TString> year={"16","17","18"};
	vector<TString> extra={"mll>70 && mll<110","puppimet>20 && puppimt<60","puppimet>20 && puppimt>60","mll>20"};
	for(int i=0;i<fname.size();i++){
		for(int ik=2;ik<year.size();ik++){
			cout<<fname[i]<<" "<<channel[i]<<" "<<endl;
			for(int j=0;j<extra.size();j++){
				TH1D*h1=run(cut1,"n",fname[i]+year[ik],channel[i],extra[j]);  
				TH1D*h2=run(cut2,"d",fname[i]+year[ik],channel[i],extra[j]);
				TFile*fout=new TFile("hist_"+channel[i]+"_"+year[ik]+Form("_%d",j)+".root","recreate");
                                cout<<h1->GetSum()/h2->GetSum()<<endl;
				h1->Write();
				h2->Write();
				fout->Close();
			}

		}
	}
	return 0;
}
