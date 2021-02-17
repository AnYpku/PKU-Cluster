#define num 3
#define pi 3.1415926
void run(TString sample,TString vec_branchname,TString reco,vector<double> bins,TString cut1[num],int kk,TString tag){
     TFile*file;  TTree*tree;
     if(sample.Contains("ZA"))
	     file=new TFile("/home/pku/anying/cms/rootfiles/JESR/unfold_"+tag+"JESR_ZA"+tag+".root");
     else    file=new TFile("/home/pku/anying/cms/rootfiles/JESR/JESR_cutla-out"+sample+tag+".root");
     tree=(TTree*)file->Get("ZPKUCandidates");     

     map<TString, double> variables;
     double deltaeta,deltaeta_new,deltaeta_JEC_up,deltaeta_JEC_down;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,prefWeight;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double actualWeight;int lep;
     double puIdweight_M_new,puIdweight_M_JEC_up,puIdweight_M_JEC_down,puIdweight_M_JER_up,puIdweight_M_JER_down;
     Double_t scalef,pileupWeight;
     double Mjj,deltaetajj;
     double genMjj,gendetajj;
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
     tree->SetBranchAddress("gendetajj",&gendetajj);
     tree->SetBranchStatus(vec_branchname,1);
     tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
     tree->SetBranchAddress(reco, &variables[reco]);
     if(vec_branchname.Contains("Mjj")){
	     tree->SetBranchAddress(reco+"_new", &variables[reco+"_new"]);
	     tree->SetBranchAddress(reco+"_JEC_up", &variables[reco+"_JEC_up"]);
	     tree->SetBranchAddress(reco+"_JEC_down", &variables[reco+"_JEC_down"]);
     }
     TTreeFormula *tformula[3];
     tformula[0]=new TTreeFormula("formula1", cut1[0], tree);
     tformula[1]=new TTreeFormula("formula2", cut1[1], tree);
     tformula[2]=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[num][kk];
     TH2D*th2[num][kk];
     TString th1name[num][kk];
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     for(int j=0;j<kk;j++){
	     for(Int_t i=0;i<num;i++){
		     th1name[i][j]=vec_branchname+Form("_%i",i)+Form("_recobin%d",j+1);
		     if(vec_branchname.Contains("Mjj")==0)
			     th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins.size()-1,&bins[0]);
		     else
			     th2[i][j] = new TH2D(th1name[i][j],th1name[i][j],3,mjj_bins,3,detajj_bins);
	     }
     }
     cout<<"enter loop"<<endl;
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
	     double var_reco[3],detajj[3];
             detajj[0]=deltaeta_new;detajj[1]=deltaeta_JEC_up;
	     detajj[2]=deltaeta_JEC_down;
	     if(vec_branchname.Contains("Mjj")){
		     var_reco[0]=variables[reco+"_new"];var_reco[1]=variables[reco+"_JEC_up"];
		     var_reco[2]=variables[reco+"_JEC_down"];
	     }
	     for(int i=0;i<3;i++){
		     if (  !tformula[i]->EvalInstance() ) continue;
		     if(vec_branchname.Contains("Mjj")==0){
			     for(Int_t j=0;j<kk;j++){
				     if(j<kk-1 && variables[reco]>bins[j] && variables[reco]<bins[j+1]){
					     th1[i][j]->Fill(variables[vec_branchname],weight[i]);
				     }
				     if(j==kk-1 && variables[reco]>bins[j]){
					     th1[i][j]->Fill(variables[vec_branchname],weight[i]);
				     }
			     }
		     }
		     else if(vec_branchname.Contains("Mjj")){
			     if(variables[vec_branchname]>2000) variables[vec_branchname]=1999;
			     if(gendetajj>6.5) gendetajj=6.1;
			     for(int iy=0;iy<3;iy++){
				     for(int ix=0;ix<3;ix++){
//					     cout<<k<<" "<<iy<<" "<<ix<<" "<<ix+(iy)*3<<endl;
					     if(ix<2&&iy<2&&var_reco[i]>mjj_bins[ix]&&var_reco[i]<mjj_bins[ix+1]&&detajj[i]>detajj_bins[iy]&&detajj[i]<detajj_bins[iy+1])
						     th2[i][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,weight[i]);
					     if(ix==2&&iy<2&&var_reco[i]>mjj_bins[ix]&&detajj[i]>detajj_bins[iy]&&detajj[i]<detajj_bins[iy+1])
						     th2[i][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,weight[i]);
					     if(ix<2&&iy==2&&var_reco[i]>mjj_bins[ix]&&var_reco[i]<mjj_bins[ix+1]&&detajj[i]>detajj_bins[iy])
						     th2[i][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,weight[i]);
					     if(ix==2&&iy==2&&var_reco[i]>mjj_bins[ix]&&detajj[i]>detajj_bins[iy])
						     th2[i][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,weight[i]);
				     }
			     }
		     }
	     }
     }
     cout<<"end loop"<<endl;
     TFile*fout[kk];
     for(int j=0;j<kk;j++){
	     if(vec_branchname.Contains("Mjj"))
		     fout[j]=new TFile("./unfold_"+sample+"_2d"+vec_branchname+Form("_recobin%d",j+1)+"_jes"+tag+".root","recreate");
	     else
		     fout[j]=new TFile("./unfold_"+sample+"_"+vec_branchname+Form("_recobin%d",j+1)+"_jes"+tag+".root","recreate");
     }
     for(int j=0;j<kk;j++){
	     fout[j]->cd();
	     for(Int_t i=0;i<num;i++){
		     if(vec_branchname.Contains("Mjj"))
			     th2[i][j]->Write();
		     else
			     th1[i][j]->Write();
	     }
	     fout[j]->Close();
     }
     /*for(int i=0;i<num;i++){
       for(int j=0;j<kk;j++){
       if(vec_branchname.Contains("Mjj")==0)
       delete th1[i][j];
       else delete th2[i][j];
       }
       }*/
}
int Unfold_uncer_batch_sig(){
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

//	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};
//	vector<TString> recovars={"ptlep1","photonet","jet1pt"};
	vector<TString> genvars={"genMjj"};
	vector<TString> recovars={"Mjj"};
	TString dir="/home/pku/anying/cms/rootfiles/JESR/";     
	const int kk=genvars.size();
	vector<TString> sample={"ZA"};
	vector<TString> tags={"16","17","18"};
	for(int k=0;k<tags.size();k++){
		if(tags[k].Contains("17")){
			GenJet="(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";   
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
		TString cut1="("+ Reco_new +") && ("+Gen+")";
		TString cut2="("+ Reco_up +")  && ("+Gen+")";
		TString cut3="("+ Reco_down +")&& ("+Gen+")";
		TString cut[3];cut[0]=cut1;cut[1]=cut2;cut[2]=cut3;
		TString Reco[3]; Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 

		for(int i=0;i<recovars.size();i++){
			for(int j=0;j<sample.size();j++){
				cout<<tags[k]<<" "<<recovars[i]<<" "<<sample[j]<<endl;
				if(genvars[j].Contains("Mjj")==0)
					run(sample[j],genvars[i],recovars[i],bins[i],cut,bins[i].size()-1,tags[k]);
				else
					run(sample[j],genvars[i],recovars[i],bins[i],cut,9,tags[k]);
			}
		}
	}
	return 1;
}
