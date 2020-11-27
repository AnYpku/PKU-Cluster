void run(TString cut1,TString cut2,TString cut3,TString tag){
     TString dir="/home/pku/anying/cms/rootfiles/20"+tag+"/";
     TFile*file=new TFile(dir+"unfold_GenCutla-outZA-EWK"+tag+".root");
     const int nbins=7; 
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");
     double lumi;
     if(tag.Contains("16"))lumi=35.86;cout<<lumi<<endl;
     if(tag.Contains("17"))lumi=41.52;cout<<lumi<<endl;
     if(tag.Contains("18"))lumi=58.7;cout<<lumi<<endl;

     TTreeFormula *tformula=new TTreeFormula("formula", cut3, tree); 
     TTreeFormula *tformula1=new TTreeFormula("formula", cut1, tree); 
     TTreeFormula *tformula2=new TTreeFormula("formula", cut2, tree); 

     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,pileupWeight,prefWeight,muon1_track_scale,muon2_track_scale;
     double genMjj,gendetajj,Mjj,deltaetajj,scalef;
     int lep;
     tree->SetBranchAddress("lep",&lep);
     tree->SetBranchAddress("genMjj",&genMjj);
     tree->SetBranchAddress("Mjj",&Mjj);
     tree->SetBranchAddress("deltaetajj",&deltaetajj);
     tree->SetBranchAddress("gendetajj",&gendetajj);
     tree->SetBranchAddress("scalef", &scalef);
     tree->SetBranchAddress("pileupWeight", &pileupWeight);
     tree->SetBranchAddress("prefWeight", &prefWeight);
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
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t gendetajj_bins[4]={2.5, 4.5,  6, 6.5};

     TString h1name="hist1_2d"+tag;
     TH1D* h1 = new TH1D(h1name,"2d reco && gen",7,0,7);//fill(gen) 
     TString th2name;
     th2name="hist_2d"+tag;
     TH1D*th2 = new TH1D(th2name,"reco && !Gen",7,0,7);//out of gen
     TH1D*th1[nbins];
     TString th1name[nbins];
     for(Int_t i=0;i<nbins;i++){
	     th1name[i]=Form("hist2d_%d",i);
	     th1[i]= new TH1D(th1name[i],Form("%0.f<genMjj<%0.f  reco && gen;;yields",mjj_bins[0],mjj_bins[3]),7,0,7);
	     th1[i]->Sumw2(); 
     }      
     double count=0,nentries=tree->GetEntries();
     double actualWeight;
     cout<<"enter loop to build histograms"<<endl;
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
	     if(tag.Contains("18"))  prefWeight=1;
	     actualWeight=scalef*pileupWeight*prefWeight*lumi*photon_veto_scale;
	     if(lep==11)
		     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale;
	     if(lep==13)
		     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale;
             if(i%1000==0) cout<<"actualWeight "<<actualWeight<<endl;
	     if (  tformula->EvalInstance() ) 
		     count++;
	     if (  tformula1->EvalInstance() ) {//reco && gen
		     if(genMjj>=500&&genMjj<800&&gendetajj>=2.5&&gendetajj<4.5)h1->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
		     if(genMjj>=800&&genMjj<1200&&gendetajj>=2.5&&gendetajj<4.5)h1->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
		     if(genMjj>=1200&&gendetajj>=2.5&&gendetajj<4.5)h1->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
		     if(genMjj>=500&&genMjj<800&&gendetajj>=4.5&&gendetajj<6)h1->Fill(3.5,actualWeight);//3~4 4.5~6 500~800 
		     if(genMjj>=800&&genMjj<1200&&gendetajj>=4.5&&gendetajj<6)h1->Fill(4.5,actualWeight);//4~5 4.5~6 800~1200
		     if(genMjj>=1200&&gendetajj>=4.5&&gendetajj<6)h1->Fill(5.5,actualWeight);//5~6 6~infi 500~800
		     if(genMjj>=500&&genMjj<2000&&gendetajj>=6)h1->Fill(6.5,actualWeight);//6~7 6~infi 800~1200
		     for(int k=0;k<nbins;k++){
			     if(genMjj>=500&&genMjj<800&&gendetajj>=2.5&&gendetajj<4.5)th1[k]->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
			     if(genMjj>=800&&genMjj<1200&&gendetajj>=2.5&&gendetajj<4.5)th1[k]->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
			     if(genMjj>=1200&&gendetajj>=2.5&&gendetajj<4.5)th1[k]->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
			     if(genMjj>=500&&genMjj<800&&gendetajj>=4.5&&gendetajj<6)th1[k]->Fill(3.5,actualWeight);//3~4 4.5~6 500~800 
			     if(genMjj>=800&&genMjj<1200&&gendetajj>=4.5&&gendetajj<6)th1[k]->Fill(4.5,actualWeight);//4~5 4.5~6 800~1200
			     if(genMjj>=1200&&gendetajj>=4.5&&gendetajj<6)th1[k]->Fill(5.5,actualWeight);//5~6 6~infi 500~800
			     if(genMjj>=500&&genMjj<2000&&gendetajj>=6)th1[k]->Fill(6.5,actualWeight);//6~7 6~infi 800~1200
		     }
	     }
	     if (  tformula2->EvalInstance() ){//reco && !gen
		     if(Mjj>=500&&Mjj<800&&deltaetajj>=2.5&&deltaetajj<4.5)th2->Fill(0.5,actualWeight);//0~1, 2.5~4.5 and 500~800
		     if(Mjj>=800&&Mjj<1200&&deltaetajj>=2.5&&deltaetajj<4.5)th2->Fill(1.5,actualWeight);//1~2 2.5~4.5 and 800~1200
		     if(Mjj>=1200&&deltaetajj>=2.5&&deltaetajj<4.5)th2->Fill(2.5,actualWeight);//2~3 2.5~4.5 1200~2000
		     if(Mjj>=500&&Mjj<800&&deltaetajj>=4.5&&deltaetajj<6)th2->Fill(3.5,actualWeight);//3~4 4.5~6 500~800 
		     if(Mjj>=800&&Mjj<1200&&deltaetajj>=4.5&&deltaetajj<6)th2->Fill(4.5,actualWeight);//4~5 4.5~6 800~1200
		     if(Mjj>=1200&&deltaetajj>=4.5&&deltaetajj<6)th2->Fill(5.5,actualWeight);//5~6 6~infi 500~800
		     if(Mjj>=500&&Mjj<2000&&deltaetajj>=6)th2->Fill(6.5,actualWeight);//6~7 6~infi 800~1200
	     }
     }
     double eff=count/nentries;
     cout<<"after gen selection "<<count<<"; total enevts "<<nentries<<"; eff "<<eff<<endl;
     int p=0;
     TFile*fout=new TFile("hist_ZA-EWK_2d"+tag+".root","recreate");
     TFile*f1=new TFile("hist_EWK_2d"+tag+".root","recreate");
     for(Int_t i=0;i<nbins;i++){
	     th1[i]->SetBinContent(nbins,th1[i]->GetBinContent(nbins)+th1[i]->GetBinContent(nbins+1));
             th1[i]->SetBinError(nbins,sqrt(th1[i]->GetBinError(nbins)*th1[i]->GetBinError(nbins)+th1[i]->GetBinError(nbins+1)*th1[i]->GetBinError(nbins+1)));
     }//add overflow bin
     th2->SetBinContent(nbins,th2->GetBinContent(nbins)+th2->GetBinContent(nbins+1));//add overflowbin
     th2->SetBinError(nbins,sqrt(th2->GetBinError(nbins)*th2->GetBinError(nbins)+th2->GetBinError(nbins+1)*th2->GetBinError(nbins+1)));
     h1->SetBinContent(nbins,h1->GetBinContent(nbins)+h1->GetBinContent(nbins+1));//add overflowbin
     h1->SetBinError(nbins,sqrt(h1->GetBinError(nbins)*h1->GetBinError(nbins)+h1->GetBinError(nbins+1)*h1->GetBinError(nbins+1)));
     fout->cd();
     for(Int_t i=0;i<nbins;i++){
	     th1[i]->Write();
     }
     th2->Write();
     h1->Write();
//     h2->Write();
     fout->Close();
     f1->cd();
     h1->Write();
     f1->Close();
}
int Build_Unfold2DHist_sig(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5 && genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";
	TString Gen= "(((" + GenLEPmu +")||("+GenLEPele+"))"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion+")";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && deltaetajj>2.5 && Mva>100)";
	TString Reco= "(("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
	TString cut1 ="(("+Reco+")&&("+Gen+"))";
	TString cut2 ="(("+Reco+")&& !("+Gen+"))";
	TString cut3 =Gen; 

	run(cut1,cut2,cut3,"16");
	run(cut1,cut2,cut3,"17");
	run(cut1,cut2,cut3,"18");
	return 1;
	}
