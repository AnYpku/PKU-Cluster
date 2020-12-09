#define num 3
#define pi 3.1415926
void run_1d (TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn);
void run(TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn){
     Double_t Mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TFile*file;  TTree*tree;
     if(sample.Contains("EWK")){
	     file=new TFile(dir+"unfold_"+tag+"JESR_"+sample+tag+".root");
             tree=(TTree*)file->Get("ZPKUCandidates");     
     }
     else{   file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
             tree=(TTree*)file->Get("ZPKUCandidates");     
     }

     Double_t scalef,pileupWeight;
     Double_t Mjj_new,jet1eta_new,jet2eta_new;
     Double_t Mjj_JEC_up,jet1eta_JEC_up,jet2eta_JEC_up;
     Double_t Mjj_JEC_down,jet1eta_JEC_down,jet2eta_JEC_down;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("Mjj_new",&Mjj_new);
     tree->SetBranchAddress("Mjj_JEC_up",&Mjj_JEC_up);
     tree->SetBranchAddress("Mjj_JEC_down",&Mjj_JEC_down);
     tree->SetBranchAddress("jet1eta_new",&jet1eta_new);
     tree->SetBranchAddress("jet1eta_JEC_up",&jet1eta_JEC_up);
     tree->SetBranchAddress("jet1eta_JEC_down",&jet1eta_JEC_down);
     tree->SetBranchAddress("jet2eta_new",&jet2eta_new);
     tree->SetBranchAddress("jet2eta_JEC_up",&jet2eta_JEC_up);
     tree->SetBranchAddress("jet2eta_JEC_down",&jet2eta_JEC_down);
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     for(int j=0;j<kk;j++){
	     th1name[j]=Form("Mjj_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],7,0,7);
	     th1[j]->Sumw2(); 
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj_new     =fabs(jet1eta_new     -jet2eta_new);
             double detajj_JEC_up  =fabs(jet1eta_JEC_up  -jet2eta_JEC_up);
             double detajj_JEC_down=fabs(jet1eta_JEC_down-jet2eta_JEC_down);
//             cout<<detajj_new<<" "<<Mjj_new<<"; "<<detajj_JEC_up<<" "<<Mjj_JEC_up<<"; "<<detajj_JEC_down<<" "<<Mjj_JEC_down<<endl;
	     if (  tformula1->EvalInstance() ){
		     if(Mjj_new>=500 &&Mjj_new<800&&detajj_new>=2.5&&detajj_new<4.5)
			     th1[0]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(Mjj_new>=800 &&Mjj_new<1200&&detajj_new>=2.5&&detajj_new<4.5)
			     th1[0]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(Mjj_new>=1200&&detajj_new>=2.5&&detajj_new<4.5)
			     th1[0]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		     if(Mjj_new>=500 &&Mjj_new<800&&detajj_new>=4.5&&detajj_new<6)
			     th1[0]->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		     if(Mjj_new>=800 &&Mjj_new<1200&&detajj_new>=4.5&&detajj_new<6)
			     th1[0]->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		     if(Mjj_new>=1200&&detajj_new>=4.5&&detajj_new<6)
			     th1[0]->Fill(5.5,scalef);//5~6 6~infi 500~800
		     if(Mjj_new>=500 &&Mjj_new<2000&&detajj_new>=6)
			     th1[0]->Fill(6.5,scalef);//6~7 6~infi 800~1200
	     }
	     if (  tformula2->EvalInstance() ){
		     if(Mjj_JEC_up>=500 &&Mjj_JEC_up<800&&detajj_JEC_up>=2.5&&detajj_JEC_up<4.5)
			     th1[1]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(Mjj_JEC_up>=800 &&Mjj_JEC_up<1200&&detajj_JEC_up>=2.5&&detajj_JEC_up<4.5)
			     th1[1]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(Mjj_JEC_up>=1200&&detajj_JEC_up>=2.5&&detajj_JEC_up<4.5)
			     th1[1]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		     if(Mjj_JEC_up>=500 &&Mjj_JEC_up<800&&detajj_JEC_up>=4.5&&detajj_JEC_up<6)
			     th1[1]->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		     if(Mjj_JEC_up>=800 &&Mjj_JEC_up<1200&&detajj_JEC_up>=4.5&&detajj_JEC_up<6)
			     th1[1]->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		     if(Mjj_JEC_up>=1200&&detajj_JEC_up>=4.5&&detajj_JEC_up<6)
			     th1[1]->Fill(5.5,scalef);//5~6 6~infi 500~800
		     if(Mjj_JEC_up>=500 &&Mjj_JEC_up<2000&&detajj_JEC_up>=6)
			     th1[1]->Fill(6.5,scalef);//6~7 6~infi 800~1200

	     }
	     if (  tformula3->EvalInstance() ){
		     if(Mjj_JEC_down>=500 &&Mjj_JEC_down<800&&detajj_JEC_down>=2.5&&detajj_JEC_down<4.5)
			     th1[2]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(Mjj_JEC_down>=800 &&Mjj_JEC_down<1200&&detajj_JEC_down>=2.5&&detajj_JEC_down<4.5)
			     th1[2]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(Mjj_JEC_down>=1200&&detajj_JEC_down>=2.5&&detajj_JEC_down<4.5)
			     th1[2]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
		     if(Mjj_JEC_down>=500 &&Mjj_JEC_down<800&&detajj_JEC_down>=4.5&&detajj_JEC_down<6)
			     th1[2]->Fill(3.5,scalef);//3~4 4.5~6 500~800 
		     if(Mjj_JEC_down>=800 &&Mjj_JEC_down<1200&&detajj_JEC_down>=4.5&&detajj_JEC_down<6)
			     th1[2]->Fill(4.5,scalef);//4~5 4.5~6 800~1200
		     if(Mjj_JEC_down>=1200&&detajj_JEC_down>=4.5&&detajj_JEC_down<6)
			     th1[2]->Fill(5.5,scalef);//5~6 6~infi 500~800
		     if(Mjj_JEC_down>=500 &&Mjj_JEC_down<2000&&detajj_JEC_down>=6)
			     th1[2]->Fill(6.5,scalef);//6~7 6~infi 800~1200
	     }

     }
     TFile*fout;
     if(sample.Contains("EWK")&&turn==1)
	     fout=new TFile("./unfold_"+sample+"out_jes"+tag+".root","recreate");
     else 
	     fout=new TFile("./unfold_"+sample+"_Mjj_jes"+tag+".root","recreate");
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
        vector<TString> tags={"16","17","18"};

	TString cut[3];  
	TString cut1[3]; 
	TString Reco[3]; 
	TString dir1[3];
	dir1[0]="/home/pku/anying/cms/rootfiles/2016/";     
	dir1[1]="/home/pku/anying/cms/rootfiles/2017/";     
	dir1[2]="/home/pku/anying/cms/rootfiles/2018/";     
        TString dir="/home/pku/anying/cms/rootfiles/JESR/";
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
//	vector<TString> sample={"WA"};
	//	vector<TString> sample={"ZA-EWK"};
	for(int i=0;i<tags.size();i++){
		if(tags[i].Contains("17")){
			GenJet="genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";       
			JET_new="( (  ( (fabs(jet1eta_new)<3.14&&fabs(jet1eta_new)>2.65&&jet1pt_new>30&&jet1pt_new<50&&jet1puIdTight_new==1) || (!(fabs(jet1eta_new)<3.14&&fabs(jet1eta_new)>2.65) && fabs(jet1eta_new)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta_new)<4.7&& jet1pt_new>50) ) && ( (fabs(jet2eta_new)<3.14&&fabs(jet2eta_new)>2.65&&jet2pt_new>30&&jet2pt_new<50&&jet2puIdTight_new==1)||(!(fabs(jet2eta_new)<3.14&&fabs(jet2eta_new)>2.65)&&fabs(jet2eta_new)<4.7&&jet2pt_new>30&&jet2pt_new<50) ||(fabs(jet2eta_new)<4.7 && jet2pt_new>50) ) ) && Mjj_new > 500 && deltaeta_new >2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( (  ( (fabs(jet1eta_JEC_up)<3.14&&fabs(jet1eta_JEC_up)>2.65&&jet1pt_JEC_up>30&&jet1pt_JEC_up<50&&jet1puIdTight_JEC_up==1) || (!(fabs(jet1eta_JEC_up)<3.14&&fabs(jet1eta_JEC_up)>2.65) && fabs(jet1eta_JEC_up)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta_JEC_up)<4.7&& jet1pt_JEC_up>50) ) && ( (fabs(jet2eta_JEC_up)<3.14&&fabs(jet2eta_JEC_up)>2.65&&jet2pt_JEC_up>30&&jet2pt_JEC_up<50&&jet2puIdTight_JEC_up==1)||(!(fabs(jet2eta_JEC_up)<3.14&&fabs(jet2eta_JEC_up)>2.65)&&fabs(jet2eta_JEC_up)<4.7&&jet2pt_JEC_up>30&&jet2pt_JEC_up<50) ||(fabs(jet2eta_JEC_up)<4.7 && jet2pt_JEC_up>50) ) ) && Mjj_JEC_up > 500 && deltaeta_JEC_up>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+")&& drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 )";
			JET_down="( (  ( (fabs(jet1eta_JEC_down)<3.14&&fabs(jet1eta_JEC_down)>2.65&&jet1pt_JEC_down>30&&jet1pt_JEC_down<50&&jet1puIdTight_JEC_down==1) || (!(fabs(jet1eta_JEC_down)<3.14&&fabs(jet1eta_JEC_down)>2.65) && fabs(jet1eta_JEC_down)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta_JEC_down)<4.7&& jet1pt_JEC_down>50) ) && ( (fabs(jet2eta_JEC_down)<3.14&&fabs(jet2eta_JEC_down)>2.65&&jet2pt_JEC_down>30&&jet2pt_JEC_down<50&&jet2puIdTight_JEC_down==1)||(!(fabs(jet2eta_JEC_down)<3.14&&fabs(jet2eta_JEC_down)>2.65)&&fabs(jet2eta_JEC_down)<4.7&&jet2pt_JEC_down>30&&jet2pt_JEC_down<50) ||(fabs(jet2eta_JEC_down)<4.7 && jet2pt_JEC_down>50) ) ) && Mjj_JEC_down > 500 && deltaeta_JEC_down>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5)";
		}
		else{
			GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
			JET_new ="jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new >2.5";
			JET_down="jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && deltaeta_JEC_down>2.5";
			JET_up="jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+") && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && deltaeta_JEC_up>2.5";
		}
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
		TString Reco_new= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_new;
		TString Reco_up= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_up;
		TString Reco_down= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_down;

		TString cut11="("+ Reco_new  +")&&("+Gen+")";
		TString cut12="("+ Reco_up   +")&&("+Gen+")";
		TString cut13="("+ Reco_down +")&&("+Gen+")";

		TString cut21="("+ Reco_new  +")&&!("+Gen+")";
		TString cut22="("+ Reco_up   +")&&!("+Gen+")";
		TString cut23="("+ Reco_down +")&&!("+Gen+")";
		cut[0]=cut11; cut[1]=cut12; cut[2]=cut13;//reco && gen
		cut1[0]=cut21;cut1[1]=cut22;cut1[2]=cut23;//reco && !gen
		Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 
                cout<<tags[i]<<" "<<JET_new<<endl;
                cout<<tags[i]<<" "<<JET_up<<endl;
                cout<<tags[i]<<" "<<JET_down<<endl;
		for(int j=0;j<sample.size();j++){
			cout<<sample[j]<<endl;
			if(sample[j].Contains("EWK")){
				run(dir,"ZA-EWK",cut,3,tags[i],0);
//				run(dir,"ZA-EWK",cut1,3,tags[i],1);
//				run_1d(dir,tags[i]+"outJEC_ZA-EWK",cut,3,tags[i],0);
//				run_1d(dir,tags[i]+"outJEC_ZA-EWK",cut1,3,tags[i],1);
			}
			else{
				run(dir,sample[j],Reco,3,tags[i],0);
//				run_1d(dir1[i],sample[j],Reco,3,tags[i],0);
			}
		}
	}
	return 1;
}
void run_1d (TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn){
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
     Double_t Mjj_new,jet1eta_new,jet2eta_new;
     Double_t Mjj_JEC_up,jet1eta_JEC_up,jet2eta_JEC_up;
     Double_t Mjj_JEC_down,jet1eta_JEC_down,jet2eta_JEC_down;
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("Mjj_new",&Mjj_new);
     tree->SetBranchAddress("Mjj_JEC_up",&Mjj_JEC_up);
     tree->SetBranchAddress("Mjj_JEC_down",&Mjj_JEC_down);
     tree->SetBranchAddress("jet1eta_new",&jet1eta_new);
     tree->SetBranchAddress("jet1eta_JEC_up",&jet1eta_JEC_up);
     tree->SetBranchAddress("jet1eta_JEC_down",&jet1eta_JEC_down);
     tree->SetBranchAddress("jet2eta_new",&jet2eta_new);
     tree->SetBranchAddress("jet2eta_JEC_up",&jet2eta_JEC_up);
     tree->SetBranchAddress("jet2eta_JEC_down",&jet2eta_JEC_down);
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     for(int j=0;j<kk;j++){
	     th1name[j]=Form("Mjj_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],3,0,3);
	     th1[j]->Sumw2(); 
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj_new     =fabs(jet1eta_new     -jet2eta_new);
             double detajj_JEC_up  =fabs(jet1eta_JEC_up  -jet2eta_JEC_up);
             double detajj_JEC_down=fabs(jet1eta_JEC_down-jet2eta_JEC_down);
//             cout<<detajj_new<<" "<<Mjj_new<<"; "<<detajj_JEC_up<<" "<<Mjj_JEC_up<<"; "<<detajj_JEC_down<<" "<<Mjj_JEC_down<<endl;
	     if (  tformula1->EvalInstance() ){
		     if(detajj_new>=2.5&&detajj_new<4.5)
			     th1[0]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(detajj_new>=4.5&&detajj_new<6)
			     th1[0]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(detajj_new>6)
			     th1[0]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
	     }
	     if (  tformula2->EvalInstance() ){
		     if(detajj_JEC_up>=2.5&&detajj_JEC_up<4.5)
			     th1[1]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(detajj_JEC_up>=4.5&&detajj_JEC_up<6)
			     th1[1]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(detajj_JEC_up>=6)
			     th1[1]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000

	     }
	     if (  tformula3->EvalInstance() ){
		     if(detajj_JEC_down>=2.5&&detajj_JEC_down<4.5)
			     th1[2]->Fill(0.5,scalef);//0~1, 2.5~4.5 and 500~800
		     if(detajj_JEC_down>=4.5&&detajj_JEC_down<6)
			     th1[2]->Fill(1.5,scalef);//1~2 2.5~4.5 and 800~1200
		     if(detajj_JEC_down>=6)
			     th1[2]->Fill(2.5,scalef);//2~3 2.5~4.5 1200~2000
	     }

     }
     TFile*fout;
     if(sample.Contains("EWK")&&turn==1)
	     fout=new TFile("./hist_1d_"+sample+"out_jes"+tag+".root","recreate");
     else 
	     fout=new TFile("./hist_1d_"+sample+"_jes"+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<kk;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
