#define num 3
#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString cut1,TString channel){
     TString dir1; 
     dir1="../../batch_cards/rootfiles/";
     TFile*file=new TFile(dir1+"optimal_plj"+tag+"_weight"+sample+".root");
     TTree*tree=(TTree*)file->Get("outtree");     
     TString cut;
     if(channel.Contains("ele"))
             cut="(lep==11)";
     if(channel.Contains("mu"))
             cut="(lep==13)";
     double ZGbin[6] = {150,400,600,800,1000,2e4};
     TString th1name;
     th1name="hist"+sample;
     TH1D* th1 = new TH1D(th1name,th1name,5,ZGbin);
     cut1="("+cut1+"&&"+cut+")";
     TString lumi;
     if(tag.Contains("16"))lumi=Form("%f",35.86);
     if(tag.Contains("17"))lumi=Form("%f",41.52);
     if(tag.Contains("18"))lumi=Form("%f",58.7);
     tree->Draw("ZGmass>>"+th1name,cut1+"*actualWeight*"+lumi,"goff");

     return th1;
}
int Uncer_batch_bkg(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )  )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5)";

	vector<TString> tag={"16","17","18"};
	vector<TString> channels={"mu","ele"};
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="(  ( (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65&&jet1pt>30&&jet1pt<50&&jet1puIdTight==1) || (!(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) && fabs(jet1eta)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65&&jet2pt>30&&jet2pt<50&&jet2puIdTight==1)||(!(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65)&&fabs(jet2eta)<4.7&&jet2pt>30&&jet2pt<50) ||(fabs(jet2eta)<4.7 && jet2pt>50) ) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
	}
	TString Reco= "(("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
	const int kk=channels.size();
	TH1D*hist[3][kk];TH1D*hist_up[3][kk];TH1D*hist_down[3][kk];//hist[year][channels]
	for(int j=0;j<kk;j++){
		for(int i=0;i<tag.size();i++){
			hist[i][j]=run("",tag[i],Reco,channels[j]);
			hist_up[i][j]=run("_up",tag[i],Reco,channels[j]);
			hist_down[i][j]=run("_down",tag[i],Reco,channels[j]);
		}
	}
	//     cout<<hist[0][0]->GetBinContent(1);
	TFile*fout[3][kk];//hist[year][channels]
	for(int j=0;j<kk;j++){
		for(int i=0;i<3;i++){
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
