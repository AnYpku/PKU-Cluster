TH1D* run(TString cut,TString style,TString file,TString channel,TString isBarrel,TString extra){
	vector<double> ptbins={20,25,30,35,40,50,60,100,400};
	TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/"+file+".root");
	TTree*tree=(TTree*)f1->Get("Events");
        TString histname=style+"_"+file+"_"+channel+"_"+isBarrel;
        TH1D*h1 = new TH1D(histname,"",ptbins.size()-1,&ptbins[0]);
	if(channel=="ee") cut = "( ( (channel==2 && lep1_pid==11 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.5 && lep2pt>20 && fabs(lep2eta)<2.5) && "+cut +")" + "&& (HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) )";
	else if(channel=="mm") cut = "( ( (channel==3 && lep1_pid==13 && lep2_pid==13 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.4) && "+cut +")"+"&& ((HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ)) )";
	else if(channel=="emu") cut = "( ( (channel==1 && lep1_pid==13 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.5) && "+cut +")"+" && ((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) )";
	if(isBarrel.Contains("barrel")) cut="("+cut+"&& (fabs(photoneta)<1.4442)"+")";
	else cut="("+cut+"&& (fabs(photoneta)<2.5&&fabs(photoneta)>1.566)"+")";
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
	TString cut1="( (n_loose_ele+n_loose_mu)==2 && n_photon>0 && photonet > 20. )";
	TString cut2="( (n_loose_ele+n_loose_mu)==2 && n_photon>0 && photonet > 20. &&  (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) )";
	TString cut3="( (n_loose_ele+n_loose_mu)==2 && n_photon>0 && photonet > 20. && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) && photon_isprompt==1 )";
        vector<TString> fname={"TTJets","DY","DY"};
	vector<TString> channel={"emu","mm","ee"};
        vector<TString> isBarrel={"barrel","endcap"};
	vector<TString> year={"16","17","18"};
	for(int i=1;i<fname.size();i++){
		for(int ik=2;ik<year.size();ik++){
			for(int k=0;k<isBarrel.size()-1;k++){
                                cout<<fname[i]<<" "<<channel[i]<<" "<<isBarrel[k]<<endl;
				TFile*fout=new TFile("hist_"+channel[i]+"_"+isBarrel[k]+year[ik]+".root","recreate");
                                int ikk;
                                if(channel[i]=="emu")ikk=1;else if(channel[i]=="mm")ikk=3;else ikk=2;
				TH1D*h1=run(cut1,"n","out"+fname[i]+year[ik],channel[i],isBarrel[k],"mll>70 && mll<110");  
				TH1D*h2=run(cut2,"d","out"+fname[i]+"_f"+year[ik],channel[i],isBarrel[k],"mll>70 && mll<110");
				TH1D*h3=run(cut1,"n","out"+fname[i]+year[ik],channel[i],isBarrel[k],"met>30"); 
				TH1D*h4=run(cut2,"d","out"+fname[i]+"_f"+year[ik],channel[i],isBarrel[k],"met>30");
				TH1D*h5=run(cut1,"n","out"+fname[i]+year[ik],channel[i],isBarrel[k],Form("channel==%0.d",ikk)); 
				TH1D*h6=run(cut2,"d","out"+fname[i]+"_f"+year[ik],channel[i],isBarrel[k],Form("channel==%0.d",ikk));
				fout->cd();
				h1->Write();
				h2->Write();
				h3->Write();
				h4->Write();
				h5->Write();
				h6->Write();
				ifstream f1;
                                vector<double> ptbins;
                                if(isBarrel[k].Contains("barrel"))
                                        ptbins={20,25,30,35,40,50,60,100,400};
                                else    ptbins={20,25,30,40,50,60,400};
				const int n=ptbins.size()-1;
				double fakerate[n];TString c;
                                if(channel[i]=="emu") c="ee";
                                else c=channel[i];
				for(int i=0;i<ptbins.size()-1;i++){
					f1.open(Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/barrel/txt/fakerate_"+c+"_ZA_pt%0.f_%0.f.txt",ptbins[i],ptbins[i+1]));
					if(!f1.is_open())  cout<<"can not open the file "<<Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/barrel/txt/fakerate_"+c+"_ZA_pt%0.f_%0.f",ptbins[i],ptbins[i+1])<<endl;
					f1>>fakerate[i];
					f1.close();
				}
			}
		}
	}
	return 0;
}
