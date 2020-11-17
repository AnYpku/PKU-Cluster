#define num 3
#define pi 3.1415926
vector<double> bin_j1pt={30,60,90,120,150,180,210,240,270,300};
vector<double> bin_j2pt={30,60,90,120,150,180,210,240,270,300};
vector<double> bin_Mjj={500,800,1200,2000};
vector<double> bin_j1eta={-4.7,-3.7,-2.7,-1.7,0,1.7,2.7,3.7,4.7};
vector<double> bin_j2eta={-4.7,-3.7,-2.7,-1.7,0,1.7,2.7,3.7,4.7};
vector<double> bin_deta={2.5,4.5,6,6.5};
vector<vector<double>> bins={/*bin_j1pt,bin_j2pt,*/bin_Mjj/*,bin_j1eta,bin_j2eta,bin_deta*/};
void run(TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn,TString var,vector<double>bins){
     TFile*file;  TTree*tree;
     file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
     tree=(TTree*)file->Get("ZPKUCandidates");     

     Double_t scalef,pileupWeight;
     Double_t Mjj_new,jet1eta_new,jet2eta_new,jet1pt_new,jet2pt_new,jet1e_new,jet2e_new,jet1phi_new,jet2phi_new;
     Double_t Mjj_JEC_up,jet1eta_JEC_up,jet2eta_JEC_up,jet1pt_JEC_up,jet2pt_JEC_up,jet1e_JEC_up,jet2e_JEC_up,jet1phi_JEC_up,jet2phi_JEC_up;
     Double_t Mjj_JEC_down,jet1eta_JEC_down,jet2eta_JEC_down,jet1pt_JEC_down,jet2pt_JEC_down,jet1e_JEC_down,jet2e_JEC_down,jet1phi_JEC_down,jet2phi_JEC_down;
     double ptVlep, yVlep, phiVlep, massVlep;
     double photonet,photoneta,photone,photonphi;
     double zepp_new,zepp_JEC_up,zepp_JEC_down;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,prefWeight;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double actualWeight;int lep;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("zepp_new",&zepp_new);
     tree->SetBranchAddress("zepp_JEC_up",&zepp_JEC_up);
     tree->SetBranchAddress("zepp_JEC_down",&zepp_JEC_down);
     tree->SetBranchAddress("Mjj_new",&Mjj_new);
     tree->SetBranchAddress("Mjj_JEC_up",&Mjj_JEC_up);
     tree->SetBranchAddress("Mjj_JEC_down",&Mjj_JEC_down);
     tree->SetBranchAddress("jet1eta_new",&jet1eta_new);
     tree->SetBranchAddress("jet1eta_JEC_up",&jet1eta_JEC_up);
     tree->SetBranchAddress("jet1eta_JEC_down",&jet1eta_JEC_down);
     tree->SetBranchAddress("jet2eta_new",&jet2eta_new);
     tree->SetBranchAddress("jet2eta_JEC_up",&jet2eta_JEC_up);
     tree->SetBranchAddress("jet2eta_JEC_down",&jet2eta_JEC_down);
     tree->SetBranchAddress("jet1pt_new",&jet1pt_new);
     tree->SetBranchAddress("jet1pt_JEC_up",&jet1pt_JEC_up);
     tree->SetBranchAddress("jet1pt_JEC_down",&jet1pt_JEC_down);
     tree->SetBranchAddress("jet2pt_new",&jet2pt_new);
     tree->SetBranchAddress("jet2pt_JEC_up",&jet2pt_JEC_up);
     tree->SetBranchAddress("jet2pt_JEC_down",&jet2pt_JEC_down);
     tree->SetBranchAddress("jet1e_new",&jet1e_new);
     tree->SetBranchAddress("jet1e_JEC_up",&jet1e_JEC_up);
     tree->SetBranchAddress("jet1e_JEC_down",&jet1e_JEC_down);
     tree->SetBranchAddress("jet2e_new",&jet2e_new);
     tree->SetBranchAddress("jet2e_JEC_up",&jet2e_JEC_up);
     tree->SetBranchAddress("jet2e_JEC_down",&jet2e_JEC_down);
     tree->SetBranchAddress("jet1phi_new",&jet1phi_new);
     tree->SetBranchAddress("jet1phi_JEC_up",&jet1phi_JEC_up);
     tree->SetBranchAddress("jet1phi_JEC_down",&jet1phi_JEC_down);
     tree->SetBranchAddress("jet2phi_new",&jet2phi_new);
     tree->SetBranchAddress("jet2phi_JEC_up",&jet2phi_JEC_up);
     tree->SetBranchAddress("jet2phi_JEC_down",&jet2phi_JEC_down);
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
     map<TString, double> variables;
     tree->SetBranchAddress(var+"_new", &variables[var+"_new"]);
     tree->SetBranchAddress(var+"_JEC_up", &variables[var+"_JEC_up"]);
     tree->SetBranchAddress(var+"_JEC_down", &variables[var+"_JEC_down"]);
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     double delta_phi_new,delta_phi_JEC_down,delta_phi_JEC_up;
     TLorentzVector Zp4, photonp4, jet1p4_new, jet2p4_new,jet1p4_JEC_up,jet2p4_JEC_up,jet1p4_JEC_down,jet2p4_JEC_down;
     for(int j=0;j<kk;j++){
	     th1name[j]=Form("hist_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],bins.size()-1,&bins[0]);
	     th1[j]->Sumw2(); 
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj_new     =fabs(jet1eta_new     -jet2eta_new);
             double detajj_JEC_up  =fabs(jet1eta_JEC_up  -jet2eta_JEC_up);
             double detajj_JEC_down=fabs(jet1eta_JEC_down-jet2eta_JEC_down);
             Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
             photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
             jet1p4_new.SetPtEtaPhiE(jet1pt_new, jet1eta_new, jet1phi_new, jet1e_new);
             jet2p4_new.SetPtEtaPhiE(jet2pt_new, jet2eta_new, jet2phi_new, jet2e_new);
             jet1p4_JEC_up.SetPtEtaPhiE(jet1pt_JEC_up, jet1eta_JEC_up, jet1phi_JEC_up, jet1e_JEC_up);
             jet2p4_JEC_up.SetPtEtaPhiE(jet2pt_JEC_up, jet2eta_JEC_up, jet2phi_JEC_up, jet2e_JEC_up);
             jet1p4_JEC_down.SetPtEtaPhiE(jet1pt_JEC_down, jet1eta_JEC_down, jet1phi_JEC_down, jet1e_JEC_down);
             jet2p4_JEC_down.SetPtEtaPhiE(jet2pt_JEC_down, jet2eta_JEC_down, jet2phi_JEC_down, jet2e_JEC_down);
             delta_phi_new=fabs((Zp4+photonp4).Phi()-(jet1p4_new+jet2p4_new).Phi());
             delta_phi_JEC_up=fabs((Zp4+photonp4).Phi()-(jet1p4_JEC_up+jet2p4_JEC_up).Phi());
             delta_phi_JEC_down=fabs((Zp4+photonp4).Phi()-(jet1p4_JEC_down+jet2p4_JEC_down).Phi());
             if (delta_phi_new>pi) delta_phi_new=2*pi-delta_phi_new;
             if (delta_phi_JEC_up>pi) delta_phi_JEC_up=2*pi-delta_phi_JEC_up;
             if (delta_phi_JEC_down>pi) delta_phi_JEC_down=2*pi-delta_phi_JEC_down;
//             cout<<detajj_new<<" "<<Mjj_new<<"; "<<detajj_JEC_up<<" "<<Mjj_JEC_up<<"; "<<detajj_JEC_down<<" "<<Mjj_JEC_down<<endl;
             if(tag.Contains("18"))  prefWeight=1;
             actualWeight=scalef*pileupWeight*prefWeight;
                     if(lep==11)
                             actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale;
                     if(lep==13)
                             actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale;
             if(k%20000==0)cout<<"actualWeight "<<actualWeight<<endl;
             if(variables[var+"_new"]>bins[bins.size()-1]) variables[var+"_new"]=bins[bins.size()-2]+1;
             if(variables[var+"_JEC_up"]>bins[bins.size()-1]) variables[var+"_JEC_up"]=bins[bins.size()-2]+1;
             if(variables[var+"_JEC_down"]>bins[bins.size()-1]) variables[var+"_JEC_down"]=bins[bins.size()-2]+1;
	     if (  tformula1->EvalInstance() && (delta_phi_new>1.9 && zepp_new<2.4) ){
		     th1[0]->Fill(variables[var+"_new"],actualWeight);//0~1, 2.5~4.5 and 500~800
	     }
	     if (  tformula2->EvalInstance() && (delta_phi_JEC_up>1.9 && zepp_JEC_up<2.4) ){
		     th1[1]->Fill(variables[var+"_JEC_up"],actualWeight);//0~1, 2.5~4.5 and 500~800

	     }
	     if (  tformula3->EvalInstance() && (delta_phi_JEC_down>1.9 && zepp_JEC_down<2.4) ){
		     th1[2]->Fill(variables[var+"_JEC_down"],actualWeight);//0~1, 2.5~4.5 and 500~800
	     }

     }
     TFile*fout;
     if(sample.Contains("EWK")&&turn==1)
	     fout=new TFile("./hist_"+sample+"out_jes"+tag+".root","recreate");
     else 
	     fout=new TFile("./hist_"+sample+"_"+var+"_jes"+tag+".root","recreate");
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
	TString JET_new;
	TString JET_down;
	TString JET_up;

        vector<TString> tags={"16","17","18"};
//        vector<TString> tags={"17"};
	TString cut[3];  
	TString cut1[3]; 
	TString Reco[3]; 
	TString dir1[3];
	dir1[0]="/home/pku/anying/cms/rootfiles/JESR/";     
	dir1[1]="/home/pku/anying/cms/rootfiles/JESR/";     
	dir1[2]="/home/pku/anying/cms/rootfiles/JESR/";     
	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/JEC/";     
	vector<TString> sample={"ZA","ZA-EWK"};//,"TTA","VV","ST";
	for(int i=0;i<tags.size();i++){
		if(tags[i].Contains("17")){
			JET_new="( (  ( (fabs(jet1eta_new)<3.14&&fabs(jet1eta_new)>2.65&&jet1pt_new>30&&jet1pt_new<50&&jet1puIdTight_new==1) || (!(fabs(jet1eta_new)<3.14&&fabs(jet1eta_new)>2.65) && fabs(jet1eta_new)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta_new)<4.7&& jet1pt_new>50) ) && ( (fabs(jet2eta_new)<3.14&&fabs(jet2eta_new)>2.65&&jet2pt_new>30&&jet2pt_new<50&&jet2puIdTight_new==1)||(!(fabs(jet2eta_new)<3.14&&fabs(jet2eta_new)>2.65)&&fabs(jet2eta_new)<4.7&&jet2pt_new>30&&jet2pt_new<50) ||(fabs(jet2eta_new)<4.7 && jet2pt_new>50) ) ) && Mjj_new > 500 && deltaeta_new >2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( (  ( (fabs(jet1eta_JEC_up)<3.14&&fabs(jet1eta_JEC_up)>2.65&&jet1pt_JEC_up>30&&jet1pt_JEC_up<50&&jet1puIdTight_JEC_up==1) || (!(fabs(jet1eta_JEC_up)<3.14&&fabs(jet1eta_JEC_up)>2.65) && fabs(jet1eta_JEC_up)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta_JEC_up)<4.7&& jet1pt_JEC_up>50) ) && ( (fabs(jet2eta_JEC_up)<3.14&&fabs(jet2eta_JEC_up)>2.65&&jet2pt_JEC_up>30&&jet2pt_JEC_up<50&&jet2puIdTight_JEC_up==1)||(!(fabs(jet2eta_JEC_up)<3.14&&fabs(jet2eta_JEC_up)>2.65)&&fabs(jet2eta_JEC_up)<4.7&&jet2pt_JEC_up>30&&jet2pt_JEC_up<50) ||(fabs(jet2eta_JEC_up)<4.7 && jet2pt_JEC_up>50) ) ) && Mjj_JEC_up > 500 && deltaeta_JEC_up>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+")&& drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 )";
			JET_down="( (  ( (fabs(jet1eta_JEC_down)<3.14&&fabs(jet1eta_JEC_down)>2.65&&jet1pt_JEC_down>30&&jet1pt_JEC_down<50&&jet1puIdTight_JEC_down==1) || (!(fabs(jet1eta_JEC_down)<3.14&&fabs(jet1eta_JEC_down)>2.65) && fabs(jet1eta_JEC_down)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta_JEC_down)<4.7&& jet1pt_JEC_down>50) ) && ( (fabs(jet2eta_JEC_down)<3.14&&fabs(jet2eta_JEC_down)>2.65&&jet2pt_JEC_down>30&&jet2pt_JEC_down<50&&jet2puIdTight_JEC_down==1)||(!(fabs(jet2eta_JEC_down)<3.14&&fabs(jet2eta_JEC_down)>2.65)&&fabs(jet2eta_JEC_down)<4.7&&jet2pt_JEC_down>30&&jet2pt_JEC_down<50) ||(fabs(jet2eta_JEC_down)<4.7 && jet2pt_JEC_down>50) ) ) && Mjj_JEC_down > 500 && deltaeta_JEC_down>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5)";
		}
		else{
			JET_new ="jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new >2.5";
			JET_down="jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && deltaeta_JEC_down>2.5";
			JET_up="jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+") && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && deltaeta_JEC_up>2.5";
		}
		TString Reco_new= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_new;
		TString Reco_up= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_up;
		TString Reco_down= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_down;

		Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 
                cout<<tags[i]<<" "<<dir1[i]<<endl;
//		cout<<Reco[0]<<endl;
//		cout<<Reco[1]<<endl;
		vector<TString> vars={/*"jet1pt","jet2pt",*/"Mjj"/*,"jet1eta","jet2eta","deltaeta"*/};
		for(int k=0;k<vars.size();k++){
			cout<<vars[k]<<" ";
			for(int j=0;j<sample.size();j++){
				cout<<sample[j]<<endl;
				run(dir1[i],sample[j],Reco,3,tags[i],0,vars[k],bins[k]);
			}
		}
	}
	return 1;
}
