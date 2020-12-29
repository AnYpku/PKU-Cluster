#define num 3
#define pi 3.1415926
void run(TString dir, TString sample,TString vec_branchname,vector<double> bins,TString cut1[num],int kk,TString tag){
     TFile*file;  TTree*tree;
     if(sample.Contains("EWK"))
	     file=new TFile("/home/pku/anying/cms/rootfiles/JESR/unfold_"+tag+"JESR_ZA-EWK"+tag+".root");
     else    file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
     tree=(TTree*)file->Get("ZPKUCandidates");     

     map<TString, double> variables;
     double deltaeta,deltaeta_new,deltaeta_JEC_up,deltaeta_JEC_down;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,prefWeight;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double actualWeight;int lep;
     double puIdweight_M_new,puIdweight_M_JEC_up,puIdweight_M_JEC_down,puIdweight_M_JER_up,puIdweight_M_JER_down;
     Double_t scalef,pileupWeight;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
     tree->SetBranchAddress("photon_veto_scale", &photon_veto_scale);
     tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
     tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
     tree->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale);
     tree->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
     tree->SetBranchAddress("pileupWeight", &pileupWeight);
     tree->SetBranchAddress("prefWeight", &prefWeight);
     tree->SetBranchAddress("puIdweight_M_new",&puIdweight_M_new);
     tree->SetBranchAddress("puIdweight_M_JEC_up",&puIdweight_M_JEC_up);
     tree->SetBranchAddress("puIdweight_M_JEC_down",&puIdweight_M_JEC_down);
     tree->SetBranchAddress("deltaeta_new",&deltaeta_new);
     tree->SetBranchAddress("deltaeta_JEC_up",&deltaeta_JEC_up);
     tree->SetBranchAddress("deltaeta_JEC_down",&deltaeta_JEC_down);
     tree->SetBranchStatus(vec_branchname,1);
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     if(vec_branchname.Contains("Mjj")){
	     tree->SetBranchAddress(vec_branchname+"_new", &variables[vec_branchname+"_new"]);
	     tree->SetBranchAddress(vec_branchname+"_JEC_up", &variables[vec_branchname+"_JEC_up"]);
	     tree->SetBranchAddress(vec_branchname+"_JEC_down", &variables[vec_branchname+"_JEC_down"]);
     }
     TTreeFormula *tformula[3];
     tformula[0]=new TTreeFormula("formula1", cut1[0], tree);
     tformula[1]=new TTreeFormula("formula2", cut1[1], tree);
     tformula[2]=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TH1D*th2[kk];
     TString th1name[kk];
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     for(int j=0;j<kk;j++){
	     th1name[j]=vec_branchname+Form("_%i",j);
	     if(vec_branchname.Contains("Mjj")==0)
		     th1[j] = new TH1D(th1name[j],th1name[j],bins.size()-1,&bins[0]);
	     else
		     th2[j] = new TH1D(th1name[j],th1name[j],7,0,7);
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             if(tag.Contains("18"))  prefWeight=1;
             if(tag.Contains("17")==0){
                     puIdweight_M_new=1;
                     puIdweight_M_JEC_up=1;
                     puIdweight_M_JEC_down=1;
             }
             actualWeight=scalef*pileupWeight*prefWeight;
             if(lep==11)
                     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale;
             if(lep==13)
                     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale;
             double weight[3];
             weight[0]=actualWeight*puIdweight_M_new;
             weight[1]=actualWeight*puIdweight_M_JEC_up;
             weight[2]=actualWeight*puIdweight_M_JEC_down;
	     double detajj[3],var_reco[3];
	     detajj[0]=deltaeta_new;detajj[1]=deltaeta_JEC_up;detajj[2]=deltaeta_JEC_down;
             var_reco[0]=variables[vec_branchname+"_new"];var_reco[1]=variables[vec_branchname+"_JEC_up"];
             var_reco[2]=variables[vec_branchname+"_JEC_down"];
	     for(int i=0;i<3;i++){
		     if (  tformula[i]->EvalInstance() ){
			     if(vec_branchname.Contains("Mjj")==0)
				     th1[i]->Fill(variables[vec_branchname],weight[i]);
			     else{
				     if(var_reco[i]>=500&&var_reco[i]<800&&detajj[i]>=2.5&&detajj[i]<4.5)
					     th2[i]->Fill(0.5,weight[i]);//0~1, 2.5~4.5 and 500~800
				     if(var_reco[i]>=800&&var_reco[i]<1200&&detajj[i]>=2.5&&detajj[i]<4.5)
					     th2[i]->Fill(1.5,weight[i]);//1~2, 2.5~4.5 and 800~1200
				     if(var_reco[i]>=1200&&detajj[i]>=2.5&&detajj[i]<4.5)
					     th2[i]->Fill(2.5,weight[i]);//2~3, 2.5~4.5 and 1200~infi
				     if(var_reco[i]>=500&&var_reco[i]<800&&detajj[i]>=4.5&&detajj[i]<6)
					     th2[i]->Fill(3.5,weight[i]);//3~4, 4.5~6 and 500~800
				     if(var_reco[i]>=800&&var_reco[i]<1200&&detajj[i]>=4.5&&detajj[i]<6)
					     th2[i]->Fill(4.5,weight[i]);//4~5, 4.5~6 and 800~1200
				     if(var_reco[i]>=1200&&detajj[i]>=4.5&&detajj[i]<6)
					     th2[i]->Fill(5.5,weight[i]);//5~6, 4.5~6 and 1200~infi
				     if(var_reco[i]>=500&&detajj[i]>6)
					     th2[i]->Fill(6.5,weight[i]);//6~7, 6~infi and 500~infi
			     }
		     }
	     }

     }
     TFile*fout;
     if(sample.Contains("EWK")){
	     fout=new TFile("./unfold_"+sample+"out_"+vec_branchname+"_jes"+tag+".root","recreate");
     }
     else{
	     fout=new TFile("./unfold_"+sample+"_"+vec_branchname+"_jes"+tag+".root","recreate");
     }
     fout->cd();
     for(int i=0;i<kk;i++){
	     if(vec_branchname.Contains("Mjj"))
		     th2[i]->Write();
	     else
		     th1[i]->Write();
     }
     fout->Close();
}
int Unfold_uncer_batch_bkg(){
	gSystem->Load("libTreePlayer.so");
	TString Pi=Form("%f",pi);
	TString drjj_JEC_up ="(sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(2*"+Pi+"-fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(2*"+Pi+"-fabs(jet1phi_JEC_up-jet2phi_JEC_up)))>0.5 || sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(fabs(jet1phi_JEC_up-jet2phi_JEC_up)))>0.5)";
	TString drjj_JEC_down ="(sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(2*"+Pi+"-fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(2*"+Pi+"-fabs(jet1phi_JEC_down-jet2phi_JEC_down)))>0.5 || sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(fabs(jet1phi_JEC_down-jet2phi_JEC_down)))>0.5)";
	TString drjj_new ="(sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new))*(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new)))>0.5 || sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)))>0.5)";
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && Mva>100)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && Mva>100)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString JET_new ="((jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new >2.5))";
	TString JET_down="(jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && deltaeta_JEC_down>2.5)";
	TString JET_up="(jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+") && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && deltaeta_JEC_up>2.5)";
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MjjBins={500,1000,1500,2000};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MjjBins);

	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
//	vector<TString> genvars={"genMjj"};
//	vector<TString> recovars={"Mjj"};
	TString dir="/home/pku/anying/cms/rootfiles/JESR/";     
	const int kk=genvars.size();
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	//vector<TString> sample={"ZA-EWK"};
	vector<TString> tags={"16","17","18"};
	for(int k=0;k<tags.size();k++){
		if(tags[k].Contains("17")){
			GenJet="genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";                             
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdMedium_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdMedium_new==1)) ) && Mjj_new > 500 && deltaeta_new >2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JEC_up>50&&fabs(jet1eta_JEC_up)<4.7)||(jet1pt_JEC_up>30&&jet1pt_JEC_up<50&&fabs(jet1eta_JEC_up)<4.7&&jet1puIdMedium_JEC_up==1)) && ((jet2pt_JEC_up>50&&fabs(jet2eta_JEC_up)<4.7)||(jet2pt_JEC_up>30&&jet2pt_JEC_up<50&&fabs(jet2eta_JEC_up)<4.7&&jet2puIdMedium_JEC_up==1)) ) && Mjj_JEC_up > 500 && deltaeta_JEC_up>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+")&& drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 )";
			JET_down="( ( ((jet1pt_JEC_down>50&&fabs(jet1eta_JEC_down)<4.7)||(jet1pt_JEC_down>30&&jet1pt_JEC_down<50&&fabs(jet1eta_JEC_down)<4.7&&jet1puIdMedium_JEC_down==1)) && ((jet2pt_JEC_down>50&&fabs(jet2eta_JEC_down)<4.7)||(jet2pt_JEC_down>30&&jet2pt_JEC_down<50&&fabs(jet2eta_JEC_down)<4.7&&jet2puIdMedium_JEC_down==1)) ) && Mjj_JEC_down > 500 && deltaeta_JEC_down>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5)";
		}
		else{
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			JET_new ="(jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new >2.5)";
			JET_down="(jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && deltaeta_JEC_down>2.5)";
			JET_up="(jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+") && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && deltaeta_JEC_up>2.5)";
		}
		TString Reco_new= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_new;
		TString Reco_up= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_up;
		TString Reco_down= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_down;
		TString cut1="("+ Reco_new +") &&!("+Gen+")";
		TString cut2="("+ Reco_up +")  &&!("+Gen+")";
		TString cut3="("+ Reco_down +")&&!("+Gen+")";
		TString cut[3];cut[0]=cut1;cut[1]=cut2;cut[2]=cut3;
		TString Reco[3]; Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 

		for(int i=0;i<recovars.size();i++){
			for(int j=0;j<sample.size();j++){
				cout<<recovars[i]<<" "<<sample[j]<<endl;
				if(sample[j].Contains("EWK"))
					run(dir,sample[j],recovars[i], bins[i],cut,3,tags[k]);
				run(dir,sample[j],recovars[i], bins[i],Reco,3,tags[k]);
			}
		}
	}
	return 1;
}
