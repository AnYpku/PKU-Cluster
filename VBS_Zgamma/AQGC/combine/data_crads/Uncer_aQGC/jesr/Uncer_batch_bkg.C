#define num 3
#define pi 3.1415926
void run(TString dir, TString sample,TString cut1[num],int kk,TString tag){
     Double_t Mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TFile*file;  TTree*tree;
     if(sample.Contains("EWK")){
	     file=new TFile(dir+"unfold_"+sample+".root");
             tree=(TTree*)file->Get("ZPKUCandidates");     
     }
     else{   file=new TFile(dir+"JEC_cutla-out"+sample+".root");
             tree=(TTree*)file->Get("ZPKUCandidates");     
     }

     Double_t scalef,pileupWeight;
     Double_t Mjj,jet1eta,jet2eta;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     for(int j=0;j<kk;j++){
	     th1name[j]=vec_branchname+Form("_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],9,0,9);
	     th1[j]->Sumw2(); 
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj=fabs(jet1eta-jet2eta);
	     if (  tformula1->EvalInstance() ){
		     if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[0]/g->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[0]/g->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[0]/g->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		     if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[0]/g->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		     if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[0]/g->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		     if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[0]/g->Fill(5.5,scalef);//5~6 6~infi 500~800
		     if(Mjj>=500&&Mjj<800&&detajj>=6)th1[0]/g->Fill(6.5,scalef);//6~7 6~infi 800~1200
		     if(Mjj>=800&&Mjj<1200&&detajj>=6)th1[0]/g->Fill(7.5,scalef);//7~8 6~infi800~1200
		     if(Mjj>=1200&&detajj>=6)th1[0]/g->Fill(8.5,scalef);//8~9 6~infi 800~1200
	     }
	     if (  tformula2->EvalInstance() ){
                             if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[1]/g->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
                             if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[1]/g->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
                             if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[1]/g->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
                             if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[1]/g->Fill(3.5,scalef);//3~4 4.5~6 500~800 
                             if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[1]/g->Fill(4.5,scalef);//4~5 4.5~6 800~1200
                             if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[1]/g->Fill(5.5,scalef);//5~6 6~infi 500~800
                             if(Mjj>=500&&Mjj<800&&detajj>=6)th1[1]/g->Fill(6.5,scalef);//6~7 6~infi 800~1200
                             if(Mjj>=800&&Mjj<1200&&detajj>=6)th1[1]/g->Fill(7.5,scalef);//7~8 6~infi800~1200
                             if(Mjj>=1200&&detajj>=6)th1[1]/g->Fill(8.5,scalef);//8~9 6~infi 800~1200
	     }
	     if (  tformula3->EvalInstance() ){
                             if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[2]/g->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
                             if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[2]/g->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
                             if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[2]/g->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
                             if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[2]/g->Fill(3.5,scalef);//3~4 4.5~6 500~800 
                             if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[2]/g->Fill(4.5,scalef);//4~5 4.5~6 800~1200
                             if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[2]/g->Fill(5.5,scalef);//5~6 6~infi 500~800
                             if(Mjj>=500&&Mjj<800&&detajj>=6)th1[2]/g->Fill(6.5,scalef);//6~7 6~infi 800~1200
                             if(Mjj>=800&&Mjj<1200&&detajj>=6)th1[2]/g->Fill(7.5,scalef);//7~8 6~infi800~1200
                             if(Mjj>=1200&&detajj>=6)th1[2]/g->Fill(8.5,scalef);//8~9 6~infi 800~1200
	     }

     }
     TFile*fout=new TFile("./hist_"+sample+"_jes"+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<kk;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_bkg(){
	gSystem->Load("libTreePlayer.so");
	TString Pi=Form("%f",pi);
	TString drjj_JEC_up ="sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(2*"+Pi+"-fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(2*"+Pi+"-fabs(jet1phi_JEC_up-jet2phi_JEC_up)))>0.5 || sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(fabs(jet1phi_JEC_up-jet2phi_JEC_up)))>0.5";
	TString drjj_JEC_down ="sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(2*"+Pi+"-fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(2*"+Pi+"-fabs(jet1phi_JEC_down-jet2phi_JEC_down)))>0.5 || sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(fabs(jet1phi_JEC_down-jet2phi_JEC_down)))>0.5";
	TString drjj_new ="sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new))*(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new)))>0.5 || sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)))>0.5";
	TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && Mva>100";
	TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && Mva>100";
	TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
	TString JET_new ="jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new >2.5";
	TString JET_down="jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && deltaeta_JEC_down>2.5";
	TString JET_up="jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+") && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && deltaeta_JEC_up>2.5";
	TString GenLEPmu  = "genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && genmassVlep>70 && genmassVlep<110";
	TString GenLEPele = "genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110";
	TString GenPhoton = "genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) )";
	TString GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
	TString GenDr = "gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5";
	TString GenSignalRegion = "genMjj >500 && gendetajj>2.5";
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

	TString Reco_new= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_new;
	TString Reco_up= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_up;
	TString Reco_down= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_down;
	TString cut1="("+ Reco_new +")&&!("+Gen+")";
	TString cut2="("+ Reco_up +")&&!("+Gen+")";
	TString cut3="("+ Reco_down +")&&!("+Gen+")";
	TString cut[3];cut[0]=cut1;cut[1]=cut2;cut[2]=cut3;
	TString Reco[3]; Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 
	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MvaBins={100,150,1000};
	vector<double> MjjBins={500,1000,1500,2000};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MvaBins);
	bins.push_back(MjjBins);

	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genZGmass","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mva","Mjj"};
	TString dir1="/eos/user/y/yian/2016cutla/";     
	TString dir2="/eos/user/y/yian/2017cutla/";     
	TString dir3="/eos/user/y/yian/2018cutla/";     
	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/JEC/";     
	const int kk=genvars.size();
        vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
//	vector<TString> sample={"ZA-EWK"};
		for(int j=0;j<sample.size();j++){
			cout<<recovars[i]<<" "<<sample[j]<<endl;
			if(sample[j].Contains("EWK")){
				run(dir,"16outJEC_ZA-EWK",cut,3,"16");
				run(dir,"17outJEC_ZA-EWK",cut,3,"17");
				run(dir,"18outJEC_ZA-EWK",cut,3,"18");
			}
			else{
				run(dir1,sample[j],Reco,3,"16");
				run(dir2,sample[j],Reco,3,"17");
				run(dir3,sample[j],Reco,3,"18");
			}
	}
	return 1;
}
