#define num 3
#define pi 3.1415926
void run(TString dir, TString sample,TString vec_branchname,vector<double> bins,TString cut1[num],int kk,TString tag){
     TFile*file;  TTree*tree;
     file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
     tree=(TTree*)file->Get("ZPKUCandidates");     

     map<TString, double> variables;
     tree->SetBranchStatus(vec_branchname,1);
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     Double_t scalef,pileupWeight;
     tree->SetBranchAddress("scalef",&scalef);
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     for(int j=0;j<kk;j++){
	     th1name[j]=vec_branchname+Form("_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],bins.size()-1,&bins[0]);
	     th1[j]->Sumw2(); 
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     if (  tformula1->EvalInstance() )
		     th1[0]->Fill(variables[vec_branchname],scalef);
	     if (  tformula2->EvalInstance() )
		     th1[1]->Fill(variables[vec_branchname],scalef);
	     if (  tformula3->EvalInstance() )
		     th1[2]->Fill(variables[vec_branchname],scalef);
	     
     }
    TFile*fout=new TFile("./unfold_"+sample+"_"+vec_branchname+"_jes"+tag+".root","recreate");
    fout->cd();
    for(int i=0;i<kk;i++){
	    th1[i]->Write();
    }
    fout->Close();
}
int Unfold_uncer_batch_bkg(){
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

	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt"};
	TString dir="/home/pku/anying/cms/rootfiles/JESR/";     
	const int kk=genvars.size();
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	//     vector<TString> sample={"ZA-EWK"};
	vector<TString> tags={"16","17","18"};
	for(int k=0;k<tags.size();k++){
		if(tags[k].Contains("17")){
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
		TString Reco_new= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_new;
		TString Reco_up= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_up;
		TString Reco_down= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_down;
		TString cut1="("+ Reco_new +")&&!("+Gen+")";
		TString cut2="("+ Reco_up +")&&!("+Gen+")";
		TString cut3="("+ Reco_down +")&&!("+Gen+")";
		TString cut[3];cut[0]=cut1;cut[1]=cut2;cut[2]=cut3;
		TString Reco[3]; Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 

		for(int i=0;i<recovars.size();i++){
			for(int j=0;j<sample.size();j++){
				cout<<recovars[i]<<" "<<sample[j]<<endl;
				run(dir,sample[j],recovars[i], bins[i],Reco,3,tags[k]);
			}
		}
	}
	return 1;
}
