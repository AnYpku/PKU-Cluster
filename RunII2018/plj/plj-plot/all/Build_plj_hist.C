#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString cut1,TString channel,vector<double> vec_pt){
//     vector<double> vec_pt;
     if(channel.Contains("Endcap")) vec_pt={20,25,30,40,50,60,400};   
     if(channel.Contains("Barrel")) vec_pt={20,25,30,35,40,50,60,100,400};   
     
     TString dir1="/home/pku/anying/cms/rootfiles/"+tag+"/";
     TString cut;
     if(channel.Contains("ElectronBarrel"))
             cut="lep==11&&fabs(photoneta)<1.4442";
     if(channel.Contains("BarrelMuon"))
             cut="lep==13&&fabs(photoneta)<1.4442";
     if(channel.Contains("ElectronEndcap"))
             cut="lep==11&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";
     if(channel.Contains("EndcapMuon"))
             cut="lep==13&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";

     TString actualWeight;
     if(channel.Contains("Ele")) actualWeight="*scalef*pileupWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale";
     if(channel.Contains("Mu")) actualWeight="*scalef*pileupWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale";
     if(sample.Contains("ZA")==0) actualWeight="*1";
     TFile*file=new TFile(dir1+"cutla-out"+sample+".root");
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");     

     TString th1name="hist_"+sample;
     TH1D* th1 = new TH1D(th1name,th1name,vec_pt.size()-1,&vec_pt[0]);
     th1->Sumw2(); 
     cut="(("+cut+")&&("+cut1+"))";
     tree->Draw("photonet>>"+th1name,cut+actualWeight,"goff");
     cout<<"fill histograms for "<<sample<<" in "<<channel <<endl;
//     TFile*f_data;
//     if(channel.Contains("ele")) f_data=new TFile(dir1+"cutla-outDEle17.root");
//     else f_data=new TFile(dir1+"cutla-outDMuon17.root");
//     TTree*tree_data=(TTree*)f_data->Get("ZPKUCandidates");     
//
//     TFile*f_za_plj=new TFile(dir1+"cutla-outZA17_plj.root");
//     TTree*tree_za_plj=(TTree*)f_za_plj->Get("ZPKUCandidates");     

     return th1;
}
int Build_plj_hist(){
	ifstream f1;
	vector<double> vec_pt;
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
	TString Pi=Form("%f",pi);
	TString dr = "( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
	TString SignalRegion = "Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100";

	vector<TString> tag={"2016","2017","2018"};
	vector<TString> channels={"BarrelMuon","EndcapMuon","ElectronBarrel","ElectronEndcap"};
	vector<TString> copy_channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	const int kk=channels.size();
	TH1D*hist[3][kk];TH1D*hist_up[3][kk];TH1D*hist_down[3][kk];//hist[year][channels]
	for(int i=0;i<tag.size();i++){
                if(tag[i].Contains("18")==0) continue;
		if(tag[i].Contains("17")){
			jet="( ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65) && (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) &&  jet1pt<50 && jet2pt<50 && jet1pt>30 && jet2pt>30 && jet1puIdTight==1 && jet2puIdTight==1 ) || ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65) && (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) && jet1pt>50 && jet2pt>50 ) || ( !(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65) && !(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && jet1pt>30 && jet2pt>30 )  )";
		}
		else{
			jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
		}
		cout<<tag[i]<<" "<<jet<<endl;
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&("+photon+")&&!("+SignalRegion+")";
		TString cut1 ="("+Reco+")";
                double lumi;
		if(tag[i].Contains("16")) lumi=35.86;
		else if(tag[i].Contains("17")) lumi=41.52;
                else if(tag[i].Contains("18")) lumi=58.7;
		for(int j=0;j<kk;j++){
			if(channels[j].Contains("Endcap")) vec_pt={20,25,30,40,50,60,400};
			if(channels[j].Contains("Barrel")) vec_pt={20,25,30,35,40,50,60,100,400};
                        const int num=vec_pt.size()-1;
			if(channels[j].Contains("Mu"))
                             hist[i][j]=run("DMuon18",tag[i],cut1,channels[j],vec_pt);
			else hist[i][j]=run("DEle18",tag[i],cut1,channels[j],vec_pt);
			hist_up[i][j]=run("plj18",tag[i],cut1,channels[j],vec_pt);
			hist_down[i][j]=run("ZA18_plj",tag[i],cut1,channels[j],vec_pt);
                        double bin_za[num],bin_plj[num],bin_data[num],weight[num];
			double fakerate[num];
                        TString fname="./pljweight_"+copy_channels[j]+"_"+tag[i]+".txt";
			ofstream ftxt(fname);
                        for(int n=0;n<vec_pt.size()-1;n++){
				f1.open(Form("/home/pku/anying/cms/PKU-Cluster/RunII"+tag[i]+"/MakeTemplate/With_sieieCorr/"+channels[j]+"/ZAfit/fractionfitResult_za/txt/fakerate_ZA_pt%0.f_%0.f.txt",vec_pt[n],vec_pt[n+1]));
				if(!f1.is_open()) cout<<"can not open the file: "<<Form("/home/pku/anying/cms/PKU-Cluster/RunII"+tag[i]+"/MakeTemplate/With_sieieCorr/"+channels[j]+"/ZAfit/fractionfitResult_za/txt/fakerate_ZA_pt%0.f_%0.f.txt",vec_pt[n],vec_pt[n+1])<<endl;
				else cout<<"open the file: "<<Form("/home/pku/anying/cms/PKU-Cluster/RunII"+tag[i]+"/MakeTemplate/With_sieieCorr/"+channels[j]+"/ZAfit/fractionfitResult_za/txt/fakerate_ZA_pt%0.f_%0.f.txt",vec_pt[n],vec_pt[n+1])<<endl;

				f1>>fakerate[n];
				cout<<vec_pt[n]<<"<pt<"<<vec_pt[n+1]<<endl;
				bin_data[n]=hist[i][j]->GetBinContent(n+1);
				bin_plj[n] =hist_up[i][j]->GetBinContent(n+1);
				bin_za[n] = lumi*hist_down[i][j]->GetBinContent(n+1);
				weight[n] = bin_data[n]*fakerate[n]/(bin_plj[n]-bin_za[n]);
				cout<<fakerate[n]<<" "<<bin_data[n]<<" "<<bin_plj[n]<<" "<<bin_za[n]<<" "<<weight[n] <<endl; 
				ftxt<<fixed<<setprecision(2)<<weight[n]<<endl;
				f1.close();
		       }
		}
	}
        cout<<"get histograms"<<endl;
	//     cout<<hist[0][0]->GetBinContent(1);
	TFile*fout[3][kk];
	for(int i=0;i<3;i++){
		if(tag[i].Contains("18")==0) continue;
		for(int j=0;j<kk;j++){
			fout[i][j]= new TFile("hist_plj_"+channels[j]+"_"+tag[i]+".root","recreate");
			cout<<hist[i][j]->GetBinContent(1)<<endl;
			fout[i][j]->cd();
			hist[i][j]->Write();
			hist_up[i][j]->Write();
			hist_down[i][j]->Write();
			fout[i][j]->Close();
		}//fout[year][vars]
	}
	return 1;
}
