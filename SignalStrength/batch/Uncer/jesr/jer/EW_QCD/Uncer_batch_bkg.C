#define num 3
#define pi 3.1415926
void run_1d (TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn);
void run(TString dir, TString sample,TString cut1[num],int kk,TString tag,bool turn){
     Double_t Mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TFile*file;  TTree*tree;
     if(sample.Contains("ZA")){
	     file=new TFile(dir+"unfold_GenCutla-JESR_"+sample+tag+".root");
             tree=(TTree*)file->Get("ZPKUCandidates");     
     }
     else{   file=new TFile(dir+"JESR_cutla-out"+sample+tag+".root");
             tree=(TTree*)file->Get("ZPKUCandidates");     
     }

     Double_t scalef,pileupWeight;
     Double_t Mjj_new,jet1eta_new,jet2eta_new;
     Double_t Mjj_JER_up,jet1eta_JER_up,jet2eta_JER_up;
     Double_t Mjj_JER_down,jet1eta_JER_down,jet2eta_JER_down;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,prefWeight;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double actualWeight;int lep;
     double puIdweight_M_new,puIdweight_M_JER_up,puIdweight_M_JER_down;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("puIdweight_M_new",&puIdweight_M_new);
     tree->SetBranchAddress("puIdweight_M_JER_up",&puIdweight_M_JER_up);
     tree->SetBranchAddress("puIdweight_M_JER_down",&puIdweight_M_JER_down);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("Mjj_new",&Mjj_new);
     tree->SetBranchAddress("Mjj_JER_up",&Mjj_JER_up);
     tree->SetBranchAddress("Mjj_JER_down",&Mjj_JER_down);
     tree->SetBranchAddress("jet1eta_new",&jet1eta_new);
     tree->SetBranchAddress("jet1eta_JER_up",&jet1eta_JER_up);
     tree->SetBranchAddress("jet1eta_JER_down",&jet1eta_JER_down);
     tree->SetBranchAddress("jet2eta_new",&jet2eta_new);
     tree->SetBranchAddress("jet2eta_JER_up",&jet2eta_JER_up);
     tree->SetBranchAddress("jet2eta_JER_down",&jet2eta_JER_down);
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
     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
     TH1D*th1[kk];
     TString th1name[kk];
     for(int j=0;j<kk;j++){
	     th1name[j]=Form("hist_%i",j);
	     th1[j] = new TH1D(th1name[j],th1name[j],9,0,9);
	     th1[j]->Sumw2(); 
     }
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj_new     =fabs(jet1eta_new     -jet2eta_new);
             double detajj_JER_up  =fabs(jet1eta_JER_up  -jet2eta_JER_up);
             double detajj_JER_down=fabs(jet1eta_JER_down-jet2eta_JER_down);
//             cout<<detajj_new<<" "<<Mjj_new<<"; "<<detajj_JER_up<<" "<<Mjj_JER_up<<"; "<<detajj_JER_down<<" "<<Mjj_JER_down<<endl;
             if(tag.Contains("18"))  prefWeight=1;
             if(tag.Contains("17")==0){
		     puIdweight_M_new=1;
		     puIdweight_M_JER_up=1;
		     puIdweight_M_JER_down=1;
	     }
             actualWeight=scalef*pileupWeight*prefWeight;
	     if(lep==11)
		     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale;
	     if(lep==13)
		     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale;
	     if(k%2000==0) cout<<k<<endl;
	     double weight[3];
	     weight[0]=actualWeight*puIdweight_M_new;
	     weight[1]=actualWeight*puIdweight_M_JER_up;
	     weight[2]=actualWeight*puIdweight_M_JER_down;
	     if (  tformula1->EvalInstance() ){
		     if(Mjj_new>=500 &&Mjj_new<800&&detajj_new>=2.5&&detajj_new<4.5)
			     th1[0]->Fill(0.5,weight[0]);//0~1, 2.5~4.5 and 500~800
		     if(Mjj_new>=800 &&Mjj_new<1200&&detajj_new>=2.5&&detajj_new<4.5)
			     th1[0]->Fill(1.5,weight[0]);//1~2 2.5~4.5 and 800~1200
		     if(Mjj_new>=1200&&detajj_new>=2.5&&detajj_new<4.5)
			     th1[0]->Fill(2.5,weight[0]);//2~3 2.5~4.5 1200~2000
		     if(Mjj_new>=500 &&Mjj_new<800&&detajj_new>=4.5&&detajj_new<6)
			     th1[0]->Fill(3.5,weight[0]);//3~4 4.5~6 500~800 
		     if(Mjj_new>=800 &&Mjj_new<1200&&detajj_new>=4.5&&detajj_new<6)
			     th1[0]->Fill(4.5,weight[0]);//4~5 4.5~6 800~1200
		     if(Mjj_new>=1200&&detajj_new>=4.5&&detajj_new<6)
			     th1[0]->Fill(5.5,weight[0]);//5~6 6~infi 500~800
		     if(Mjj_new>=500 &&Mjj_new<800&&detajj_new>=6)
			     th1[0]->Fill(6.5,weight[0]);//6~7 6~infi 800~1200
		     if(Mjj_new>=800 &&Mjj_new<1200&&detajj_new>=6)
			     th1[0]->Fill(7.5,weight[0]);//7~8 6~infi800~1200
		     if(Mjj_new>=1200&&detajj_new>=6)
			     th1[0]->Fill(8.5,weight[0]);//8~9 6~infi 800~1200
	     }
	     if (  tformula2->EvalInstance() ){
		     if(Mjj_JER_up>=500 &&Mjj_JER_up<800&&detajj_JER_up>=2.5&&detajj_JER_up<4.5)
			     th1[1]->Fill(0.5,weight[1]);//0~1, 2.5~4.5 and 500~800
		     if(Mjj_JER_up>=800 &&Mjj_JER_up<1200&&detajj_JER_up>=2.5&&detajj_JER_up<4.5)
			     th1[1]->Fill(1.5,weight[1]);//1~2 2.5~4.5 and 800~1200
		     if(Mjj_JER_up>=1200&&detajj_JER_up>=2.5&&detajj_JER_up<4.5)
			     th1[1]->Fill(2.5,weight[1]);//2~3 2.5~4.5 1200~2000
		     if(Mjj_JER_up>=500 &&Mjj_JER_up<800&&detajj_JER_up>=4.5&&detajj_JER_up<6)
			     th1[1]->Fill(3.5,weight[1]);//3~4 4.5~6 500~800 
		     if(Mjj_JER_up>=800 &&Mjj_JER_up<1200&&detajj_JER_up>=4.5&&detajj_JER_up<6)
			     th1[1]->Fill(4.5,weight[1]);//4~5 4.5~6 800~1200
		     if(Mjj_JER_up>=1200&&detajj_JER_up>=4.5&&detajj_JER_up<6)
			     th1[1]->Fill(5.5,weight[1]);//5~6 6~infi 500~800
		     if(Mjj_JER_up>=500 &&Mjj_JER_up<800&&detajj_JER_up>=6)
			     th1[1]->Fill(6.5,weight[1]);//6~7 6~infi 800~1200
		     if(Mjj_JER_up>=800 &&Mjj_JER_up<1200&&detajj_JER_up>=6)
			     th1[1]->Fill(7.5,weight[1]);//7~8 6~infi800~1200
		     if(Mjj_JER_up>=1200&&detajj_JER_up>=6)
			     th1[1]->Fill(8.5,weight[1]);//8~9 6~infi 800~1200

	     }
	     if (  tformula3->EvalInstance() ){
		     if(Mjj_JER_down>=500 &&Mjj_JER_down<800&&detajj_JER_down>=2.5&&detajj_JER_down<4.5)
			     th1[2]->Fill(0.5,weight[2]);//0~1, 2.5~4.5 and 500~800
		     if(Mjj_JER_down>=800 &&Mjj_JER_down<1200&&detajj_JER_down>=2.5&&detajj_JER_down<4.5)
			     th1[2]->Fill(1.5,weight[2]);//1~2 2.5~4.5 and 800~1200
		     if(Mjj_JER_down>=1200&&detajj_JER_down>=2.5&&detajj_JER_down<4.5)
			     th1[2]->Fill(2.5,weight[2]);//2~3 2.5~4.5 1200~2000
		     if(Mjj_JER_down>=500 &&Mjj_JER_down<800&&detajj_JER_down>=4.5&&detajj_JER_down<6)
			     th1[2]->Fill(3.5,weight[2]);//3~4 4.5~6 500~800 
		     if(Mjj_JER_down>=800 &&Mjj_JER_down<1200&&detajj_JER_down>=4.5&&detajj_JER_down<6)
			     th1[2]->Fill(4.5,weight[2]);//4~5 4.5~6 800~1200
		     if(Mjj_JER_down>=1200&&detajj_JER_down>=4.5&&detajj_JER_down<6)
			     th1[2]->Fill(5.5,weight[2]);//5~6 6~infi 500~800
		     if(Mjj_JER_down>=500 &&Mjj_JER_down<800&&detajj_JER_down>=6)
			     th1[2]->Fill(6.5,weight[2]);//6~7 6~infi 800~1200
		     if(Mjj_JER_down>=800 &&Mjj_JER_down<1200&&detajj_JER_down>=6)
			     th1[2]->Fill(7.5,weight[2]);//7~8 6~infi800~1200
		     if(Mjj_JER_down>=1200&&detajj_JER_down>=6)
			     th1[2]->Fill(8.5,weight[2]);//8~9 6~infi 800~1200
	     }

     }
     TFile*fout;
     if(sample.Contains("ZA")&&turn==1)
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
	TString drjj_JER_up ="(sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(2*"+Pi+"-fabs(jet1phi_JER_up-jet2phi_JER_up))*(2*"+Pi+"-fabs(jet1phi_JER_up-jet2phi_JER_up)))>0.5 || sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(fabs(jet1phi_JER_up-jet2phi_JER_up))*(fabs(jet1phi_JER_up-jet2phi_JER_up)))>0.5)";
	TString drjj_JER_down ="(sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(2*"+Pi+"-fabs(jet1phi_JER_down-jet2phi_JER_down))*(2*"+Pi+"-fabs(jet1phi_JER_down-jet2phi_JER_down)))>0.5 || sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(fabs(jet1phi_JER_down-jet2phi_JER_down))*(fabs(jet1phi_JER_down-jet2phi_JER_down)))>0.5)";
	TString drjj_new ="(sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new))*(2*"+Pi+"-fabs(jet1phi_new-jet2phi_new)))>0.5 || sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)))>0.5)";
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 && Mva>100)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110 && Mva>100)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString JET_new ="(jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new >2.5)";
	TString JET_down="(jet1pt_JER_down> 30 && jet2pt_JER_down > 30 && fabs(jet1eta_JER_down)< 4.7 && fabs(jet2eta_JER_down)<4.7 && Mjj_JER_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5 && deltaeta_JER_down>2.5)";
	TString JET_up="(jet1pt_JER_up> 30 && jet2pt_JER_up > 30 && fabs(jet1eta_JER_up)< 4.7 && fabs(jet2eta_JER_up)<4.7 && Mjj_JER_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+") && drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 && deltaeta_JER_up>2.5)";
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ) )";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";
	vector<TString> tags={"16","17","18"};

	TString cut[3];  
	TString cut1[3]; 
	TString Reco[3]; 
	TString dir1[3];
	dir1[0]="/home/pku/anying/cms/rootfiles/2016/";     
	dir1[1]="/home/pku/anying/cms/rootfiles/2017/";     
	dir1[2]="/home/pku/anying/cms/rootfiles/2018/";     
	TString dir="/home/pku/anying/cms/rootfiles/JESR/";
//	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	vector<TString> sample={"ZA"};
	for(int i=0;i<tags.size();i++){
		if(tags[i].Contains("17")){
			GenJet="(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";       
			JET_new="( ( ((jet1pt_new>50&&fabs(jet1eta_new)<4.7)||(jet1pt_new>30&&jet1pt_new<50&&fabs(jet1eta_new)<4.7&&jet1puIdMedium_new==1)) && ((jet2pt_new>50&&fabs(jet2eta_new)<4.7)||(jet2pt_new>30&&jet2pt_new<50&&fabs(jet2eta_new)<4.7&&jet2puIdMedium_new==1)) ) && Mjj_new > 500 && deltaeta_new >2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 )";
			JET_up="( ( ((jet1pt_JER_up>50&&fabs(jet1eta_JER_up)<4.7)||(jet1pt_JER_up>30&&jet1pt_JER_up<50&&fabs(jet1eta_JER_up)<4.7&&jet1puIdMedium_JER_up==1)) && ((jet2pt_JER_up>50&&fabs(jet2eta_JER_up)<4.7)||(jet2pt_JER_up>30&&jet2pt_JER_up<50&&fabs(jet2eta_JER_up)<4.7&&jet2puIdMedium_JER_up==1)) ) && Mjj_JER_up > 500 && deltaeta_JER_up>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+")&& drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 )";
			JET_down="( ( ((jet1pt_JER_down>50&&fabs(jet1eta_JER_down)<4.7)||(jet1pt_JER_down>30&&jet1pt_JER_down<50&&fabs(jet1eta_JER_down)<4.7&&jet1puIdMedium_JER_down==1)) && ((jet2pt_JER_down>50&&fabs(jet2eta_JER_down)<4.7)||(jet2pt_JER_down>30&&jet2pt_JER_down<50&&fabs(jet2eta_JER_down)<4.7&&jet2puIdMedium_JER_down==1)) ) && Mjj_JER_down > 500 && deltaeta_JER_down>2.5 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5)";
		}
		else{
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			JET_new ="(jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && ("+drjj_new+") && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 && deltaeta_new >2.5)";
			JET_down="(jet1pt_JER_down> 30 && jet2pt_JER_down > 30 && fabs(jet1eta_JER_down)< 4.7 && fabs(jet2eta_JER_down)<4.7 && Mjj_JER_down > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && ("+drjj_JER_down+")&& drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5 && deltaeta_JER_down>2.5)";
			JET_up="(jet1pt_JER_up> 30 && jet2pt_JER_up > 30 && fabs(jet1eta_JER_up)< 4.7 && fabs(jet2eta_JER_up)<4.7 && Mjj_JER_up > 500 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && ("+drjj_JER_up+") && drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 && deltaeta_JER_up>2.5)";
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
		if(tags[i].Contains("17")==0) continue;
		cout<<tags[i]<<" "<<JET_new<<endl;
		cout<<tags[i]<<" "<<JET_up<<endl;
		cout<<tags[i]<<" "<<JET_down<<endl;
		for(int j=0;j<sample.size();j++){
			cout<<sample[j]<<endl;
			if(sample[j].Contains("ZA")){
				run(dir,"ZA",cut,3,tags[i],0);
				run(dir,"ZA",cut1,3,tags[i],1);
				//run_1d(dir,tags[i]+"outJER_ZA-EWK",cut,3,tags[i],0);
				//run_1d(dir,tags[i]+"outJER_ZA-EWK",cut1,3,tags[i],1);
			}
			else{
				run(dir,sample[j],Reco,3,tags[i],0);
				//run_1d(dir1[i],sample[j],Reco,3,tags[i],0);
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
	else{   file=new TFile(dir+"JER_cutla-out"+sample+".root");
		tree=(TTree*)file->Get("ZPKUCandidates");     
	}

	Double_t scalef,pileupWeight;
	Double_t Mjj_new,jet1eta_new,jet2eta_new;
	Double_t Mjj_JER_up,jet1eta_JER_up,jet2eta_JER_up;
	Double_t Mjj_JER_down,jet1eta_JER_down,jet2eta_JER_down;
	double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,prefWeight;
	double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
	double muon_hlt_scale,ele_hlt_scale;
	double actualWeight;int lep;
	tree->SetBranchAddress("scalef",&scalef);
	tree->SetBranchAddress("Mjj_new",&Mjj_new);
	tree->SetBranchAddress("Mjj_JER_up",&Mjj_JER_up);
	tree->SetBranchAddress("Mjj_JER_down",&Mjj_JER_down);
	tree->SetBranchAddress("jet1eta_new",&jet1eta_new);
	tree->SetBranchAddress("jet1eta_JER_up",&jet1eta_JER_up);
	tree->SetBranchAddress("jet1eta_JER_down",&jet1eta_JER_down);
	tree->SetBranchAddress("jet2eta_new",&jet2eta_new);
	tree->SetBranchAddress("jet2eta_JER_up",&jet2eta_JER_up);
	tree->SetBranchAddress("jet2eta_JER_down",&jet2eta_JER_down);
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
	TTreeFormula *tformula1=new TTreeFormula("formula1", cut1[0], tree);
	TTreeFormula *tformula2=new TTreeFormula("formula2", cut1[1], tree);
	TTreeFormula *tformula3=new TTreeFormula("formula3", cut1[2], tree);
	TH1D*th1[kk];
	TString th1name[kk];
	for(int j=0;j<kk;j++){
		th1name[j]=Form("hist_%i",j);
		th1[j] = new TH1D(th1name[j],th1name[j],3,0,3);
		th1[j]->Sumw2(); 
	}
	for(int k=0;k<tree->GetEntries();k++){
		tree->GetEntry(k);
		double detajj_new     =fabs(jet1eta_new     -jet2eta_new);
		double detajj_JER_up  =fabs(jet1eta_JER_up  -jet2eta_JER_up);
		double detajj_JER_down=fabs(jet1eta_JER_down-jet2eta_JER_down);
		//             cout<<detajj_new<<" "<<Mjj_new<<"; "<<detajj_JER_up<<" "<<Mjj_JER_up<<"; "<<detajj_JER_down<<" "<<Mjj_JER_down<<endl;
		if (  tformula1->EvalInstance() ){
			if(detajj_new>=2.5&&detajj_new<4.5)
				th1[0]->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
			if(detajj_new>=4.5&&detajj_new<6)
				th1[0]->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
			if(detajj_new>6)
				th1[0]->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
		}
		if (  tformula2->EvalInstance() ){
			if(detajj_JER_up>=2.5&&detajj_JER_up<4.5)
				th1[1]->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
			if(detajj_JER_up>=4.5&&detajj_JER_up<6)
				th1[1]->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
			if(detajj_JER_up>=6)
				th1[1]->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000

		}
		if (  tformula3->EvalInstance() ){
			if(detajj_JER_down>=2.5&&detajj_JER_down<4.5)
				th1[2]->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
			if(detajj_JER_down>=4.5&&detajj_JER_down<6)
				th1[2]->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
			if(detajj_JER_down>=6)
				th1[2]->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
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
