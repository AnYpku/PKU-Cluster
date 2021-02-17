#define num 3
void run(TString cut1,TString tag,TString channel,TString sample){
     Double_t Mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
     TString dir="/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_";     
     TFile*file;
     file=new TFile(dir+sample+tag+".root");
     TTree*tree=(TTree*)file->Get("outtree");     
//     tree->SetBranchStatus("*",0);
     Double_t scalef,pileupWeight,prefWeight,prefWeightUp,prefWeightDown,puIdweight_M;
     Double_t Mjj,jet1eta,jet2eta;
     double ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale;
     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale;
     double muon_hlt_scale,ele_hlt_scale;
     double weight;int lep;
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("jet1eta",&jet1eta);
     tree->SetBranchAddress("jet2eta",&jet2eta);
     tree->SetBranchAddress("scalef",&scalef);
     tree->SetBranchAddress("puIdweight_M",&puIdweight_M);
     tree->SetBranchAddress("pileupWeight",&pileupWeight);
     tree->SetBranchAddress("prefWeight",&prefWeight);
     tree->SetBranchAddress("prefWeightUp",&prefWeightUp);
     tree->SetBranchAddress("prefWeightDown",&prefWeightDown);
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

     TString cut;
     if(channel.Contains("elebarrel"))
             cut="lep==11&&fabs(photoneta)<1.4442";
     if(channel.Contains("mubarrel"))
             cut="lep==13&&fabs(photoneta)<1.4442";
     if(channel.Contains("eleendcap"))
             cut="lep==11&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";
     if(channel.Contains("muendcap"))
             cut="lep==13&&fabs(photoneta)<2.5&&fabs(photoneta)>1.566";
     TTreeFormula *tformula=new TTreeFormula("formula", cut1+"&&("+cut+")", tree);
     double actualWeight[num];
     TH1D*th1[num];
     TString th1name[num];
     for(Int_t i=0;i<num;i++){
		     th1name[i]=Form("hist_%d",i);
		     th1[i] = new TH1D(th1name[i],th1name[i],7,0,7);
		     th1[i]->Sumw2(); 
     }      
     for(int k=0;k<tree->GetEntries();k++){
             tree->GetEntry(k);
             double detajj=fabs(jet1eta-jet2eta);
	     int p=0;
	     if(tag.Contains("17")==0) puIdweight_M=1;
	     if(lep==11)
		     weight=scalef*pileupWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale*photon_veto_scale*ele_hlt_scale*puIdweight_M;
	     if(lep==13)
		     weight=scalef*pileupWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale*muon_hlt_scale*puIdweight_M;
	     if (  tformula->EvalInstance() ){
		     for(Int_t i=0;i<(num);i++){
			     if(p==0)actualWeight[p]=weight*prefWeight;
			     if(p==1)actualWeight[p]=weight*prefWeightUp;
			     if(p==2)actualWeight[p]=weight*prefWeightDown;
			     if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(0.5,actualWeight[p]);//0~1, 2.5~4.5 and 500~800
			     if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(1.5,actualWeight[p]);//1~2 2.5~4.5 and 800~1200
			     if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(2.5,actualWeight[p]);//2~3 2.5~4.5 1200~2000
			     if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[p]->Fill(3.5,actualWeight[p]);//3~4 4.5~6 500~800 
			     if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(4.5,actualWeight[p]);//4~5 4.5~6 800~1200
			     if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(5.5,actualWeight[p]);//5~6 6~infi 500~800
			     if(Mjj>=500&&detajj>=6)th1[p]->Fill(6.5,actualWeight[p]);//6~7 6~infi 800~1200
			     p++;
		     }
	     }
     }
     TFile*fout;
     fout= new TFile("hist_"+sample+"_pref_"+tag+channel+".root","recreate");
     fout->cd();
     for(Int_t i=0;i<num;i++){
	     th1[i]->Write();
     }
     fout->Close();
}
int Uncer_batch_sig(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
        vector<TString> tag={"16","17"};

        vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
        vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	const int kk=channels.size();
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			GenJet = "genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
		TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && ZGmass>100)";
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut1 ="(("+Reco+")&&("+Gen+"))";
		TString cut2 ="(("+Reco+"))";
                cout<<tag[i]<<" "<<jet<<endl;
                cout<<tag[i]<<" "<<GenJet<<endl;
		for(int j=0;j<kk;j++){
			for(int n=0;n<sample.size();n++){
				run(cut2,tag[i],channels[j],sample[n]);
			}
		}
	}
	return 1;
}
