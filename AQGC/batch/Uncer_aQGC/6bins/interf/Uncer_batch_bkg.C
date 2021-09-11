#define num 3
#define pi 3.1415926
TH1D* run( TString sample,TString tag,TString cut1,TString channel,vector<double>ZGbin){
     TString dir1; 
     dir1="../../../rootfiles/";
     TFile*file=new TFile(dir1+"optimal_ZA"+sample+tag+".root");
     TTree*tree=(TTree*)file->Get("outtree");     
     TString cut;
     if(channel.Contains("ele"))
             cut="(lep==11)";
     else if(channel.Contains("mu"))
             cut="(lep==13)";
     else cut="((lep==13)||(lep==11))";
     TString th1name;
     th1name="hist"+sample;
     TH1D* th1 = new TH1D(th1name,th1name,ZGbin.size()-1,&ZGbin[0]);
     cut1="("+cut1+"&&"+cut+")";
     TString lumi;
     if(tag.Contains("16"))lumi=Form("%f",35.86);
     if(tag.Contains("17"))lumi=Form("%f",41.52);
     if(tag.Contains("18"))lumi=Form("%f",59.7);
     tree->Draw("ZGmass>>"+th1name,cut1+"*actualWeight*"+lumi,"goff");

     return th1;
}
int Uncer_batch_bkg(){
	TString LEPmu = "(lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11 && (HLT_Ele1>0||HLT_Ele2>0)  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>120 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )  )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5)";

	vector<TString> tag={"16","17","18"};
	vector<TString> channels={"mu","ele",""};
	vector<double> ZGbin = {150,400,600,800,1000,1200,2e4};
	for(int i=0;i<tag.size();i++){
                if(tag[i].Contains("16")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
                }
                else if(tag[i].Contains("17")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
                }       
                else if(tag[i].Contains("18")){
                        jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
                }
	}
	TString Reco= "(("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
	const int kk=channels.size();
	TH1D*hist_EWK[3][kk];//hist[year][channels]
	TH1D*hist_interf[3][kk];//hist[year][channels]
	for(int j=0;j<kk;j++){
		for(int i=0;i<tag.size();i++){
			cout<<tag[i]<<" "<<Reco<<endl;
			hist_EWK[i][j]=run("-EWK",tag[i],Reco,channels[j],ZGbin);
			hist_interf[i][j]=run("_interf",tag[i],Reco,channels[j],ZGbin);
		}
	}
	//     cout<<hist[0][0]->GetBinContent(1);
	TFile*fout[3][kk];//hist[year][channels]
	for(int j=0;j<kk;j++){
		for(int i=0;i<3;i++){
			fout[i][j]= new TFile("hist_interf_"+channels[j]+"_"+tag[i]+".root","recreate");
			fout[i][j]->cd();
			hist_EWK[i][j]->Write();
			hist_interf[i][j]->Write();
			fout[i][j]->Close();
		}//fout[year][vars]
	}
	return 1;
}
