#define num 3
#define pi 3.1415926
void run(TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn){
     TFile*file;  TTree*tree;
     file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
     tree=(TTree*)file->Get("ZPKUCandidates");     

     Double_t scalef,pileupWeight,prefWeight,muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,ele_hlt_scale,muon_hlt_scale,puIdweight_T_new,puIdweight_T_JEC_up,puIdweight_T_JEC_down;
     int lep;
     double Mva,actualWeight;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("photon_id_scale",&photon_id_scale);
     tree->SetBranchAddress("photon_veto_scale",&photon_veto_scale);
     tree->SetBranchAddress("muon1_id_scale",&muon1_id_scale);
     tree->SetBranchAddress("muon2_id_scale",&muon2_id_scale);
     tree->SetBranchAddress("muon1_iso_scale",&muon1_iso_scale);
     tree->SetBranchAddress("muon2_iso_scale",&muon2_iso_scale);
     tree->SetBranchAddress("ele1_id_scale",&ele1_id_scale);
     tree->SetBranchAddress("ele2_id_scale",&ele2_id_scale);
     tree->SetBranchAddress("ele1_reco_scale",&ele1_reco_scale);
     tree->SetBranchAddress("ele2_reco_scale",&ele2_reco_scale);
     tree->SetBranchAddress("ele_hlt_scale",&ele_hlt_scale);
     tree->SetBranchAddress("Mva",&Mva);
     tree->SetBranchAddress("muon_hlt_scale",&muon_hlt_scale);
     tree->SetBranchAddress("puIdweight_T_new",&puIdweight_T_new);
     tree->SetBranchAddress("puIdweight_T_JEC_up",&puIdweight_T_JEC_up);
     tree->SetBranchAddress("puIdweight_T_JEC_down",&puIdweight_T_JEC_down);

     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     vector<double> ZGbin = {150,400,600,800,1000,1200,2e4};
     for(int j=0;j<kk;j++){
	     th1name[j]=Form("hist_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],ZGbin.size()-1,&ZGbin[0]);
	     th1[j]->Sumw2(); 
     }
     double lumi;
     if(tag.Contains("16"))lumi=35.86;
     if(tag.Contains("17"))lumi=41.52;
     if(tag.Contains("18"))lumi=59.7;
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             if(Mva>2e4) Mva=1999;
	     if(tag.Contains("18")) prefWeight=1;
	     if(tag.Contains("17")==0){
		     puIdweight_T_new=1;
		     puIdweight_T_JEC_up=1;
		     puIdweight_T_JEC_down=1;
	     }
	     actualWeight=scalef*prefWeight*pileupWeight*photon_id_scale*photon_veto_scale*lumi;
	     if(lep==11)actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
	     if(lep==13)actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
	     if(k%5000==0)cout<<sample<<" "<<tag<<" "<<actualWeight<<endl;
	     if (  tformula1->EvalInstance() ){
		     th1[0]->Fill(Mva,actualWeight*puIdweight_T_new);
	     }
	     if (  tformula2->EvalInstance() ){
		     th1[1]->Fill(Mva,actualWeight*puIdweight_T_JEC_up);
	     }
	     if (  tformula3->EvalInstance() ){
		     th1[2]->Fill(Mva,actualWeight*puIdweight_T_JEC_down);
	     }

     }
     TFile*fout;
     if(sample.Contains("EWK")&&turn==1)
	     fout=new TFile("./hist_"+sample+"out_jes"+tag+".root","recreate");
     else 
	     fout=new TFile("./hist_"+sample+"_jes"+tag+".root","recreate");
     fout->cd();
     for(int i=0;i<kk;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_bkg(){
	gSystem->Load("libTreePlayer.so");
	TString Pi=Form("%f",pi);
	TString drjj_JEC_up ="(sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(2*"+Pi+"-fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(2*"+Pi+"-fabs(jet1phi_JEC_up-jet2phi_JEC_up)))>0.5 || sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(fabs(jet1phi_JEC_up-jet2phi_JEC_up)))>0.5)";
	TString drjj_JEC_down ="(sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(2*"+Pi+"-fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(2*"+Pi+"-fabs(jet1phi_JEC_down-jet2phi_JEC_down)))>0.5 || sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(fabs(jet1phi_JEC_down-jet2phi_JEC_down)))>0.5)";
	TString drjj_new ="(sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new))*(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new)))>0.5 || sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)))>0.5)";
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && Mva>100)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && Mva>100)";
	TString photon = "(photonet>120 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString JET_new ="(jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 &&  drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && fabs(jet1eta_new-jet2eta_new) >2.5 && Mjj_new > 500 )";
	TString JET_down="(jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7  && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && fabs(jet1eta_JEC_down-jet2eta_JEC_down)>2.5 && Mjj_JEC_down > 500 )";
	TString JET_up="( jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7  && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+") && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && fabs(jet1eta_JEC_up-jet2eta_JEC_up)>2.5 && Mjj_JEC_up > 500)";
        vector<TString> tags={"16","17","18"};
	for(int i=0;i<tags.size();i++){
		if(tags[i].Contains("17")){
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdTight_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdTight_new==1)) )  && Mjj_new > 500 && fabs(jet1eta_new-jet2eta_new)>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JEC_up>50&&fabs(jet1eta_JEC_up)<4.7)||(jet1pt_JEC_up>30&&jet1pt_JEC_up<50&&fabs(jet1eta_JEC_up)<4.7&&jet1puIdTight_JEC_up==1)) && ((jet2pt_JEC_up>50&&fabs(jet2eta_JEC_up)<4.7)||(jet2pt_JEC_up>30&&jet2pt_JEC_up<50&&fabs(jet2eta_JEC_up)<4.7&&jet2puIdTight_JEC_up==1)) ) && Mjj_JEC_up > 500 && fabs(jet1eta_JEC_up-jet2eta_JEC_up)>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+")&& drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 )";
			JET_down="( ( ((jet1pt_JEC_down>50&&fabs(jet1eta_JEC_down)<4.7)||(jet1pt_JEC_down>30&&jet1pt_JEC_down<50&&fabs(jet1eta_JEC_down)<4.7&&jet1puIdTight_JEC_down==1)) && ((jet2pt_JEC_down>50&&fabs(jet2eta_JEC_down)<4.7)||(jet2pt_JEC_down>30&&jet2pt_JEC_down<50&&fabs(jet2eta_JEC_down)<4.7&&jet2puIdTight_JEC_down==1)) )  && Mjj_JEC_down > 500 && fabs(jet1eta_JEC_down-jet2eta_JEC_down)>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5)";
		}
		else{
			JET_new ="(jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && fabs(jet1eta_new-jet2eta_new)>2.5)";
			JET_down="(jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && ("+drjj_JEC_down+")&& drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 && fabs(jet1eta_JEC_down-jet2eta_JEC_down)>2.5)";
			JET_up="(jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5  && ("+drjj_JEC_up+") && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5 && fabs(jet1eta_JEC_up-jet2eta_JEC_up)>2.5)";
		}
		TString Reco_new= "((("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_new+")";
		TString Reco_up= "((("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_up+")";
		TString Reco_down= "((("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+JET_down+")";
		if(tags[i].Contains("17")==0) continue;
		TString Reco[3]; Reco[0]=Reco_new;Reco[1]=Reco_up;Reco[2]=Reco_down; 
		TString dir="/home/pku/anying/cms/rootfiles/JESR/";     
		vector<TString> sample={"ZA","ZA-EWK","TTA","others"};
		for(int j=0;j<sample.size();j++){
			cout<<tags[i]<<" "<<sample[j]<<endl;
			run(dir,sample[j],Reco,3,tags[i],0);
		}
	}
	return 1;
}
