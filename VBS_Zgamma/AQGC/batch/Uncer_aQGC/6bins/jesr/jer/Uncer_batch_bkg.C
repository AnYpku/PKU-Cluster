#define num 3
#define pi 3.1415926
void run(TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn){
     Double_t Mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TFile*file;  TTree*tree;
     file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
     tree=(TTree*)file->Get("ZPKUCandidates");     

     Double_t scalef,pileupWeight;
     Double_t Mjj_new,jet1eta_new,jet2eta_new,jet1pt_new,jet2pt_new,jet1e_new,jet2e_new,jet1phi_new,jet2phi_new;
     Double_t Mjj_JER_up,jet1eta_JER_up,jet2eta_JER_up,jet1pt_JER_up,jet2pt_JER_up,jet1e_JER_up,jet2e_JER_up,jet1phi_JER_up,jet2phi_JER_up;
     Double_t Mjj_JER_down,jet1eta_JER_down,jet2eta_JER_down,jet1pt_JER_down,jet2pt_JER_down,jet1e_JER_down,jet2e_JER_down,jet1phi_JER_down,jet2phi_JER_down;
     double ptVlep, yVlep, phiVlep, massVlep,Mva;
     double photonet,photoneta,photone,photonphi;
     double zepp_new,zepp_JER_up,zepp_JER_down;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,prefWeight;
     double puIdweight_T_new,puIdweight_T_JER_up,puIdweight_T_JER_down;
     double puIdweight_M_new,puIdweight_M_JER_up,puIdweight_M_JER_down;
     double puIdweight_L_new,puIdweight_L_JER_up,puIdweight_L_JER_down;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double actualWeight;int lep;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("zepp_new",&zepp_new);
     tree->SetBranchAddress("zepp_JER_up",&zepp_JER_up);
     tree->SetBranchAddress("zepp_JER_down",&zepp_JER_down);
     tree->SetBranchAddress("Mva",&Mva);
     tree->SetBranchAddress("Mjj_new",&Mjj_new);
     tree->SetBranchAddress("Mjj_JER_up",&Mjj_JER_up);
     tree->SetBranchAddress("Mjj_JER_down",&Mjj_JER_down);
     tree->SetBranchAddress("jet1eta_new",&jet1eta_new);
     tree->SetBranchAddress("jet1eta_JER_up",&jet1eta_JER_up);
     tree->SetBranchAddress("jet1eta_JER_down",&jet1eta_JER_down);
     tree->SetBranchAddress("jet2eta_new",&jet2eta_new);
     tree->SetBranchAddress("jet2eta_JER_up",&jet2eta_JER_up);
     tree->SetBranchAddress("jet2eta_JER_down",&jet2eta_JER_down);
     tree->SetBranchAddress("jet1pt_new",&jet1pt_new);
     tree->SetBranchAddress("jet1pt_JER_up",&jet1pt_JER_up);
     tree->SetBranchAddress("jet1pt_JER_down",&jet1pt_JER_down);
     tree->SetBranchAddress("jet2pt_new",&jet2pt_new);
     tree->SetBranchAddress("jet2pt_JER_up",&jet2pt_JER_up);
     tree->SetBranchAddress("jet2pt_JER_down",&jet2pt_JER_down);
     tree->SetBranchAddress("jet1e_new",&jet1e_new);
     tree->SetBranchAddress("jet1e_JER_up",&jet1e_JER_up);
     tree->SetBranchAddress("jet1e_JER_down",&jet1e_JER_down);
     tree->SetBranchAddress("jet2e_new",&jet2e_new);
     tree->SetBranchAddress("jet2e_JER_up",&jet2e_JER_up);
     tree->SetBranchAddress("jet2e_JER_down",&jet2e_JER_down);
     tree->SetBranchAddress("jet1phi_new",&jet1phi_new);
     tree->SetBranchAddress("jet1phi_JER_up",&jet1phi_JER_up);
     tree->SetBranchAddress("jet1phi_JER_down",&jet1phi_JER_down);
     tree->SetBranchAddress("jet2phi_new",&jet2phi_new);
     tree->SetBranchAddress("jet2phi_JER_up",&jet2phi_JER_up);
     tree->SetBranchAddress("jet2phi_JER_down",&jet2phi_JER_down);
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
     tree->SetBranchAddress("ptVlep",&ptVlep);
     tree->SetBranchAddress("yVlep",&yVlep);
     tree->SetBranchAddress("phiVlep",&phiVlep);
     tree->SetBranchAddress("massVlep",&massVlep);
     tree->SetBranchAddress("photoneta",&photoneta);
     tree->SetBranchAddress("photonet",&photonet);
     tree->SetBranchAddress("photonphi",&photonphi);
     tree->SetBranchAddress("photone",&photone);
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
     TTreeFormula *tformula[3];
     tformula[0]=new TTreeFormula("formula1", cut1[0], tree);
     tformula[1]=new TTreeFormula("formula2", cut1[1], tree);
     tformula[2]=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     vector<double> ZGbin = {150,400,600,800,1000,1200,2e4};
     for(int j=0;j<kk;j++){
	     th1name[j]=Form("hist_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],ZGbin.size()-1,&ZGbin[0]);
	     th1[j]->Sumw2(); 
     }
     double puIdweight,puIdweight_up,puIdweight_down;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
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
		     for(int ik=0;ik<3;ik++){
			    if (  !(tformula[ik]->EvalInstance() ) )
				    continue;
			    if(k%20000==0)cout<<"actualWeight "<<actualWeight<<endl;
			    th1[ik]->Fill(Mva,weight[ik]);
		     }
     }
     TFile*fout;
     if(sample.Contains("EWK")&&turn==1)
	     fout=new TFile("./hist_"+sample+"out_jer"+tag+".root","recreate");
     else 
	     fout=new TFile("./hist_"+sample+"_jer"+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<kk;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_bkg(){
	gSystem->Load("libTreePlayer.so");
	TString Pi=Form("%f",pi);
	TString drjj_JER_up ="(sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(2*"+Pi+"-fabs(jet1phi_JER_up-jet2phi_JER_up))*(2*"+Pi+"-fabs(jet1phi_JER_up-jet2phi_JER_up)))>0.5 || sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(fabs(jet1phi_JER_up-jet2phi_JER_up))*(fabs(jet1phi_JER_up-jet2phi_JER_up)))>0.5)";
	TString drjj_JER_down ="(sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(2*"+Pi+"-fabs(jet1phi_JER_down-jet2phi_JER_down))*(2*"+Pi+"-fabs(jet1phi_JER_down-jet2phi_JER_down)))>0.5 || sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(fabs(jet1phi_JER_down-jet2phi_JER_down))*(fabs(jet1phi_JER_down-jet2phi_JER_down)))>0.5)";
	TString drjj_new ="(sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new))*(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new)))>0.5 || sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)))>0.5)";
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && Mva>100 && (HLT_Mu1>0 || HLT_Mu2>0))";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && Mva>100 && (HLT_Ele1>0 || HLT_Ele2>0))";
	TString photon = "(photonet>120 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString JET_new;
	TString JET_down;
	TString JET_up;

	vector<TString> tags={"16","17","18"};
	TString cut[3];  
	TString cut1[3]; 
	TString Reco[3]; 
	TString dir1[3];
	dir1[0]="/home/pku/anying/cms/rootfiles/JESR/";     
	dir1[1]="/home/pku/anying/cms/rootfiles/JESR/";     
	dir1[2]="/home/pku/anying/cms/rootfiles/JESR/";     
	vector<TString> sample={"ZA","ZA-EWK","others"};
//	vector<TString> sample={"others"};
	for(int i=0;i<tags.size();i++){
		if(tags[i].Contains("16")){
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdMedium_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdMedium_new==1)) ) && Mjj_new > 500 && deltaeta_new >2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JER_up>50&&fabs(jet1eta_JER_up)<4.7)||(jet1pt_JER_up>30&&jet1pt_JER_up<50&&fabs(jet1eta_JER_up)<4.7&&jet1puIdMedium_JER_up==1)) && ((jet2pt_JER_up>50&&fabs(jet2eta_JER_up)<4.7)||(jet2pt_JER_up>30&&jet2pt_JER_up<50&&fabs(jet2eta_JER_up)<4.7&&jet2puIdMedium_JER_up==1)) ) && Mjj_JER_up > 500 && deltaeta_JER_up>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+")&& drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 )";
			JET_down="( ( ((jet1pt_JER_down>50&&fabs(jet1eta_JER_down)<4.7)||(jet1pt_JER_down>30&&jet1pt_JER_down<50&&fabs(jet1eta_JER_down)<4.7&&jet1puIdMedium_JER_down==1)) && ((jet2pt_JER_down>50&&fabs(jet2eta_JER_down)<4.7)||(jet2pt_JER_down>30&&jet2pt_JER_down<50&&fabs(jet2eta_JER_down)<4.7&&jet2puIdMedium_JER_down==1)) ) && Mjj_JER_down > 500 && deltaeta_JER_down>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5)";
		}
		else if(tags[i].Contains("17")){
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdTight_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdTight_new==1)) ) && Mjj_new > 500 && deltaeta_new >2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JER_up>50&&fabs(jet1eta_JER_up)<4.7)||(jet1pt_JER_up>30&&jet1pt_JER_up<50&&fabs(jet1eta_JER_up)<4.7&&jet1puIdTight_JER_up==1)) && ((jet2pt_JER_up>50&&fabs(jet2eta_JER_up)<4.7)||(jet2pt_JER_up>30&&jet2pt_JER_up<50&&fabs(jet2eta_JER_up)<4.7&&jet2puIdTight_JER_up==1)) ) && Mjj_JER_up > 500 && deltaeta_JER_up>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+")&& drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 )";
			JET_down="( ( ((jet1pt_JER_down>50&&fabs(jet1eta_JER_down)<4.7)||(jet1pt_JER_down>30&&jet1pt_JER_down<50&&fabs(jet1eta_JER_down)<4.7&&jet1puIdTight_JER_down==1)) && ((jet2pt_JER_down>50&&fabs(jet2eta_JER_down)<4.7)||(jet2pt_JER_down>30&&jet2pt_JER_down<50&&fabs(jet2eta_JER_down)<4.7&&jet2puIdTight_JER_down==1)) ) && Mjj_JER_down > 500 && deltaeta_JER_down>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5)";
		}
		else if(tags[i].Contains("18")){
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdLoose_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdLoose_new==1)) ) && Mjj_new > 500 && deltaeta_new >2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JER_up>50&&fabs(jet1eta_JER_up)<4.7)||(jet1pt_JER_up>30&&jet1pt_JER_up<50&&fabs(jet1eta_JER_up)<4.7&&jet1puIdLoose_JER_up==1)) && ((jet2pt_JER_up>50&&fabs(jet2eta_JER_up)<4.7)||(jet2pt_JER_up>30&&jet2pt_JER_up<50&&fabs(jet2eta_JER_up)<4.7&&jet2puIdLoose_JER_up==1)) ) && Mjj_JER_up > 500 && deltaeta_JER_up>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+")&& drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 )";
			JET_down="( ( ((jet1pt_JER_down>50&&fabs(jet1eta_JER_down)<4.7)||(jet1pt_JER_down>30&&jet1pt_JER_down<50&&fabs(jet1eta_JER_down)<4.7&&jet1puIdLoose_JER_down==1)) && ((jet2pt_JER_down>50&&fabs(jet2eta_JER_down)<4.7)||(jet2pt_JER_down>30&&jet2pt_JER_down<50&&fabs(jet2eta_JER_down)<4.7&&jet2puIdLoose_JER_down==1)) ) && Mjj_JER_down > 500 && deltaeta_JER_down>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5)";
		}
		TString Reco_new= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_new;
		TString Reco_up= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_up;
		TString Reco_down= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_down;

		Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 
//		if(tags[i].Contains("17")==0) continue;
		cout<<tags[i]<<" "<<dir1[i]<<endl;
		cout<<Reco[0]<<endl;
		cout<<Reco[1]<<endl;

		for(int j=0;j<sample.size();j++){
			cout<<sample[j]<<endl;
			if(sample[j].Contains("EWK")){
				run(dir1[i],sample[j],Reco,3,tags[i],0);
			}
			else{
				run(dir1[i],sample[j],Reco,3,tags[i],0);
			}
		}
	}
	return 1;
}
