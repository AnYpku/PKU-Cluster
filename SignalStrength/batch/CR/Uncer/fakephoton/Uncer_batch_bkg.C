#define num 3
#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString cut1,TString channel){
     Double_t Mjj_bins[2]={150, 400};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TString dir1;
     dir1="/home/pku/anying/cms/rootfiles/20"+tag+"/cutla-out";
     TFile*file=new TFile(dir1+"plj"+tag+"_weight"+sample+".root");
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");
     map<TString, double> variables;
     double Mjj,jet1eta,jet2eta;
     Double_t scalef;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     TString cut;
     if(channel.Contains("elebarrel"))
             cut="lep==11&&fabs(photoneta)<1.4442";
     if(channel.Contains("mubarrel"))
             cut="lep==13&&fabs(photoneta)<1.4442";
     if(channel.Contains("eleendcap"))
             cut="lep==11&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";
     if(channel.Contains("muendcap"))
             cut="lep==13&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";
     TTreeFormula *tformula=new TTreeFormula("formula", cut1+"&&("+cut+")", tree);
//     TH1D*th1[kk];
     TString th1name;
     th1name="hist"+sample;
     TH1D* th1;
     th1 = new TH1D(th1name,th1name,1,0,1);
     th1->Sumw2(); 
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     double detajj=fabs(jet1eta-jet2eta);
	     if (  tformula->EvalInstance() ){
		     if(Mjj>=150&&Mjj<400)th1->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
	     }
     }
     return th1;
}
int Uncer_batch_bkg(){
	TString GenLEPmu  = "genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4";
	TString GenLEPele = "genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5";
	TString GenPhoton = "genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) )";
	TString GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
	TString GenDr = "gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5";
	TString GenControlRegion = "genMjj >150 && genMjj<400 && genZGmass>100";

	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
	TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
	TString Pi=Form("%f",pi);
	TString dr = "( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
	TString ControlRegion = "Mjj>150 && Mjj<400 && fabs(jet1eta-jet2eta)>2.5 && Mva>100";

	vector<TString> tag={"16","17","18"};
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	const int kk=channels.size();
	TH1D*hist[3][kk];TH1D*hist_up[3][kk];TH1D*hist_down[3][kk];//hist[year][channels]
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
			jet="(  ( (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65&&jet1pt>30&&jet1pt<50&&jet1puIdTight==1) || (!(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) && fabs(jet1eta)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65&&jet2pt>30&&jet2pt<50&&jet2puIdTight==1)||(!(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65)&&fabs(jet2eta)<4.7&&jet2pt>30&&jet2pt<50) ||(fabs(jet2eta)<4.7 && jet2pt>50) ) )";
		}
		else{
			GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
			jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
		}
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenControlRegion;
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+ControlRegion;
		TString cut1 ="("+Reco+")";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		cout<<tag[i]<<" "<<jet<<endl;
		cout<<GenJet<<endl;
		for(int j=0;j<kk;j++){
			hist[i][j]=run("",tag[i],cut1,channels[j]);
			hist_up[i][j]=run("_up",tag[i],cut1,channels[j]);
			hist_down[i][j]=run("_down",tag[i],cut1,channels[j]);
		}
	}
	//     cout<<hist[0][0]->GetBinContent(1);
	TFile*fout[3][kk];
	for(int j=0;j<kk;j++){
		for(int i=0;i<3;i++){
			fout[i][j]= new TFile("hist_plj_"+channels[j]+"_"+tag[i]+"CR.root","recreate");
			cout<<hist[i][j]->GetBinContent(1)<<endl;
			fout[i][j]->cd();
			hist[i][j]->Write();
			hist_up[i][j]->Write();
			hist_down[i][j]->Write();
			fout[i][j]->Close();
		}//fout[year][vars]
	}
	/*     for(int j=0;j<kk;j++){
	       for(int i=0;i<3;i++){
	       fout[i][j]->cd();
	       hist[i][j]->Write();
	       hist_up[i][j]->Write();
	       hist_down[i][j]->Write();
	       fout[i][j]->Close();
	       }
	       }*/
	return 1;
}
