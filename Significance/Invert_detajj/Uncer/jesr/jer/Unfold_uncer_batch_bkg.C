#define num 3
#define pi 3.1415926
void run(TString dir, TString sample,TString vec_branchname,vector<double> bins,TString cut1[num],int kk,TString tag){
     TFile*file;  TTree*tree;
     file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
     tree=(TTree*)file->Get("ZPKUCandidates");     

     map<TString, double> variables;
     double deltaeta,deltaeta_new,deltaeta_JER_up,deltaeta_JER_down;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,prefWeight;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double actualWeight;int lep;
     double puIdweight_T_new,puIdweight_T_JER_up,puIdweight_T_JER_down;
     double puIdweight_M_new,puIdweight_M_JER_up,puIdweight_M_JER_down;
     double puIdweight_L_new,puIdweight_L_JER_up,puIdweight_L_JER_down;
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
     tree->SetBranchAddress("puIdweight_T_new",&puIdweight_T_new);
     tree->SetBranchAddress("puIdweight_T_JER_up",&puIdweight_T_JER_up);
     tree->SetBranchAddress("puIdweight_T_JER_down",&puIdweight_T_JER_down);
     tree->SetBranchAddress("puIdweight_M_new",&puIdweight_M_new);
     tree->SetBranchAddress("puIdweight_M_JER_up",&puIdweight_M_JER_up);
     tree->SetBranchAddress("puIdweight_M_JER_down",&puIdweight_M_JER_down);
     tree->SetBranchAddress("puIdweight_L_new",&puIdweight_L_new);
     tree->SetBranchAddress("puIdweight_L_JER_up",&puIdweight_L_JER_up);
     tree->SetBranchAddress("puIdweight_L_JER_down",&puIdweight_L_JER_down);
     tree->SetBranchAddress("deltaeta_new",&deltaeta_new);
     tree->SetBranchAddress("deltaeta_JER_up",&deltaeta_JER_up);
     tree->SetBranchAddress("deltaeta_JER_down",&deltaeta_JER_down);
     tree->SetBranchStatus(vec_branchname,1);
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     if(vec_branchname.Contains("Mjj")){
	     tree->SetBranchAddress(vec_branchname+"_new", &variables[vec_branchname+"_new"]);
	     tree->SetBranchAddress(vec_branchname+"_JER_up", &variables[vec_branchname+"_JER_up"]);
	     tree->SetBranchAddress(vec_branchname+"_JER_down", &variables[vec_branchname+"_JER_down"]);
     }
     TTreeFormula *tformula[3];
     tformula[0]=new TTreeFormula("formula1", cut1[0], tree);
     tformula[1]=new TTreeFormula("formula2", cut1[1], tree);
     tformula[2]=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     for(int j=0;j<kk;j++){
	     th1name[j]=vec_branchname+Form("_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],bins.size()-1,&bins[0]);
     }
     double puIdweight,puIdweight_up,puIdweight_down;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
	     if(k%5000==0) cout<<k<<" "<<tree->GetEntries()<<endl;
             if(tag.Contains("16")){  
                     puIdweight     =puIdweight_M_new;
                     puIdweight_up  =puIdweight_M_JER_up;
                     puIdweight_down=puIdweight_M_JER_down;
	     }
             if(tag.Contains("17")){
                    puIdweight     = puIdweight_T_new;
                    puIdweight_up  = puIdweight_T_JER_up;
                    puIdweight_down= puIdweight_T_JER_down;
             }
             if(tag.Contains("18")){
		     prefWeight=1;
		     puIdweight     = puIdweight_L_new;
		     puIdweight_up  = puIdweight_L_JER_up;
		     puIdweight_down= puIdweight_L_JER_down;
	     }
             actualWeight=scalef*pileupWeight*prefWeight;
             if(lep==11)
                     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale;
             if(lep==13)
                     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale;
             double weight[3];
             weight[0]=actualWeight*puIdweight;
             weight[1]=actualWeight*puIdweight_up;
             weight[2]=actualWeight*puIdweight_down;
	     double detajj[3],var_reco[3];
	     detajj[0]=deltaeta_new;detajj[1]=deltaeta_JER_up;detajj[2]=deltaeta_JER_down;
             var_reco[0]=variables[vec_branchname+"_new"];var_reco[1]=variables[vec_branchname+"_JER_up"];
             var_reco[2]=variables[vec_branchname+"_JER_down"];
	     for(int i=0;i<3;i++){
		     if (  tformula[i]->EvalInstance() ){
			     th1[i]->Fill(variables[vec_branchname],weight[i]);
		     }
	     }

     }
     TFile*fout;
     if(sample.Contains("EWK")){
	     fout=new TFile("./hist_"+sample+"_"+vec_branchname+"_jer"+tag+".root","recreate");
     }
     else{
	     fout=new TFile("./hist_"+sample+"_"+vec_branchname+"_jer"+tag+".root","recreate");
     }
     fout->cd();
     for(int i=0;i<kk;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Unfold_uncer_batch_bkg(){
	gSystem->Load("libTreePlayer.so");
	TString Pi=Form("%f",pi);
	TString drjj_JER_up ="(sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(2*"+Pi+"-fabs(jet1phi_JER_up-jet2phi_JER_up))*(2*"+Pi+"-fabs(jet1phi_JER_up-jet2phi_JER_up)))>0.5 || sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(fabs(jet1phi_JER_up-jet2phi_JER_up))*(fabs(jet1phi_JER_up-jet2phi_JER_up)))>0.5)";
	TString drjj_JER_down ="(sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(2*"+Pi+"-fabs(jet1phi_JER_down-jet2phi_JER_down))*(2*"+Pi+"-fabs(jet1phi_JER_down-jet2phi_JER_down)))>0.5 || sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(fabs(jet1phi_JER_down-jet2phi_JER_down))*(fabs(jet1phi_JER_down-jet2phi_JER_down)))>0.5)";
	TString drjj_new ="(sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new))*(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new)))>0.5 || sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)))>0.5)";
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && Mva>100)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && Mva>100)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString JET_new ="((jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new <2.5))";
	TString JET_down="(jet1pt_JER_down> 30 && jet2pt_JER_down > 30 && fabs(jet1eta_JER_down)< 4.7 && fabs(jet2eta_JER_down)<4.7 && Mjj_JER_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5 && deltaeta_JER_down<2.5)";
	TString JET_up="(jet1pt_JER_up> 30 && jet2pt_JER_up > 30 && fabs(jet1eta_JER_up)< 4.7 && fabs(jet2eta_JER_up)<4.7 && Mjj_JER_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+") && drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 && deltaeta_JER_up<2.5)";
	vector<vector<double>> bins;
	vector<double> MjjBins={500,600,700,800};
	bins.push_back(MjjBins);

	vector<TString> recovars={"Mjj"};
	TString dir="/home/pku/anying/cms/rootfiles/JESR/";     
	const int kk=recovars.size();
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	vector<TString> tags={"16","17","18"};
	for(int k=0;k<tags.size();k++){
		if(tags[k].Contains("16")){
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdMedium_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdMedium_new==1)) ) && Mjj_new > 500 && deltaeta_new <2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JER_up>50&&fabs(jet1eta_JER_up)<4.7)||(jet1pt_JER_up>30&&jet1pt_JER_up<50&&fabs(jet1eta_JER_up)<4.7&&jet1puIdMedium_JER_up==1)) && ((jet2pt_JER_up>50&&fabs(jet2eta_JER_up)<4.7)||(jet2pt_JER_up>30&&jet2pt_JER_up<50&&fabs(jet2eta_JER_up)<4.7&&jet2puIdMedium_JER_up==1)) ) && Mjj_JER_up > 500 && deltaeta_JER_up<2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+")&& drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 )";
			JET_down="( ( ((jet1pt_JER_down>50&&fabs(jet1eta_JER_down)<4.7)||(jet1pt_JER_down>30&&jet1pt_JER_down<50&&fabs(jet1eta_JER_down)<4.7&&jet1puIdMedium_JER_down==1)) && ((jet2pt_JER_down>50&&fabs(jet2eta_JER_down)<4.7)||(jet2pt_JER_down>30&&jet2pt_JER_down<50&&fabs(jet2eta_JER_down)<4.7&&jet2puIdMedium_JER_down==1)) ) && Mjj_JER_down > 500 && deltaeta_JER_down<2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5)";
		}
		if(tags[k].Contains("17")){
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdTight_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdTight_new==1)) ) && Mjj_new > 500 && deltaeta_new <2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JER_up>50&&fabs(jet1eta_JER_up)<4.7)||(jet1pt_JER_up>30&&jet1pt_JER_up<50&&fabs(jet1eta_JER_up)<4.7&&jet1puIdTight_JER_up==1)) && ((jet2pt_JER_up>50&&fabs(jet2eta_JER_up)<4.7)||(jet2pt_JER_up>30&&jet2pt_JER_up<50&&fabs(jet2eta_JER_up)<4.7&&jet2puIdTight_JER_up==1)) ) && Mjj_JER_up > 500 && deltaeta_JER_up<2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+")&& drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 )";
			JET_down="( ( ((jet1pt_JER_down>50&&fabs(jet1eta_JER_down)<4.7)||(jet1pt_JER_down>30&&jet1pt_JER_down<50&&fabs(jet1eta_JER_down)<4.7&&jet1puIdTight_JER_down==1)) && ((jet2pt_JER_down>50&&fabs(jet2eta_JER_down)<4.7)||(jet2pt_JER_down>30&&jet2pt_JER_down<50&&fabs(jet2eta_JER_down)<4.7&&jet2puIdTight_JER_down==1)) ) && Mjj_JER_down > 500 && deltaeta_JER_down<2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5)";
		}
		if(tags[k].Contains("18")){
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdLoose_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdLoose_new==1)) ) && Mjj_new > 500 && deltaeta_new <2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JER_up>50&&fabs(jet1eta_JER_up)<4.7)||(jet1pt_JER_up>30&&jet1pt_JER_up<50&&fabs(jet1eta_JER_up)<4.7&&jet1puIdLoose_JER_up==1)) && ((jet2pt_JER_up>50&&fabs(jet2eta_JER_up)<4.7)||(jet2pt_JER_up>30&&jet2pt_JER_up<50&&fabs(jet2eta_JER_up)<4.7&&jet2puIdLoose_JER_up==1)) ) && Mjj_JER_up > 500 && deltaeta_JER_up<2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+")&& drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 )";
			JET_down="( ( ((jet1pt_JER_down>50&&fabs(jet1eta_JER_down)<4.7)||(jet1pt_JER_down>30&&jet1pt_JER_down<50&&fabs(jet1eta_JER_down)<4.7&&jet1puIdLoose_JER_down==1)) && ((jet2pt_JER_down>50&&fabs(jet2eta_JER_down)<4.7)||(jet2pt_JER_down>30&&jet2pt_JER_down<50&&fabs(jet2eta_JER_down)<4.7&&jet2puIdLoose_JER_down==1)) ) && Mjj_JER_down > 500 && deltaeta_JER_down<2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5)";
		}
		TString Reco_new= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_new;
		TString Reco_up= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_up;
		TString Reco_down= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+JET_down;
		TString Reco[3]; Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 
//		if(tags[k].Contains("17")==0) continue;
		for(int i=0;i<recovars.size();i++){
			for(int j=0;j<sample.size();j++){
				cout<<recovars[i]<<" "<<sample[j]<<endl;
				run(dir,sample[j],recovars[i], bins[i],Reco,3,tags[k]);
			}
		}
	}
	return 1;
}
