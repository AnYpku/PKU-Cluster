void run(TString sample,TString tag, TString cut1,TString cut2,TString cut3,TString Reco){
     TString dir="/home/pku/anying/cms/rootfiles/20"+tag+"/";
     TFile*file;
     if(sample.Contains("EWK"))file=new TFile(dir+"unfold_GenCutla-ZA-EWK"+tag+".root");
     else if(sample.Contains("plj"))file=new TFile(dir+"cutla-outplj"+tag+"_weight.root");
     else file=new TFile(dir+"cutla-out"+sample+tag+".root");
     const int nbins=9; 
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");
     double lumi;
     if(tag.Contains("16")){lumi=35.86;cout<<lumi<<endl;}
     if(tag.Contains("17")){lumi=41.52;cout<<lumi<<endl;}
     if(tag.Contains("18")){lumi=59.7;cout<<lumi<<endl;}

     TTreeFormula *tformula1=new TTreeFormula("formula1", cut1, tree); 
     TTreeFormula *tformula2=new TTreeFormula("formula2", cut2, tree); 
     TTreeFormula *tformula3=new TTreeFormula("formula3", cut3, tree); 
     TTreeFormula *tformula=new TTreeFormula("formula",Reco, tree); 

     double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,pileupWeight,prefWeight,puIdweight_T,ele_hlt_scale,muon_hlt_scale,puIdweight_L,puIdweight_M,puIdweight;
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
     tree->SetBranchAddress("puIdweight_T", &puIdweight_T);
     tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
     tree->SetBranchAddress("puIdweight_L", &puIdweight_L);
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
     tree->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
     tree->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale);
     Double_t mjj_bins[4]={500, 800, 1200, 2000};
     Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};

     TString h1name="histGen_genMjj";
     TH2D* h1 = new TH2D(h1name,"2D genMjj-gendetajj in gen",3,mjj_bins,3,detajj_bins);//fill(gen) 
     TString th2name;
     th2name="hist_2d"+tag;
     TH2D*th2 = new TH2D(th2name,"reco && !Gen",3,mjj_bins,3,detajj_bins);//out of gen
     TH2D*hist_bkg = new TH2D(th2name,"reco for bkg",3,mjj_bins,3,detajj_bins);//
     TH2D*th1[nbins];
     TString th1name[nbins];
     for(Int_t i=0;i<nbins;i++){
	     th1name[i]=Form("hist2d_%d",i);
	     th1[i]= new TH2D(th1name[i],Form("%0.f<genMjj<%0.f  reco && gen;;yields",mjj_bins[0],mjj_bins[3]),3,mjj_bins,3,detajj_bins);
	     th1[i]->Sumw2(); 
     }      
     double count=0,nentries=tree->GetEntries();
     double actualWeight;
     cout<<"enter loop to build histograms"<<endl;
     for(int i=0;i<tree->GetEntries();i++){
	     tree->GetEntry(i);
             if(Mjj>2000) Mjj=1999; if(deltaetajj>6.5) deltaetajj=6.1;
             if(genMjj>2000) genMjj=1999; if(gendetajj>6.5) gendetajj=6.1;
             if(tag.Contains("16")){ puIdweight=puIdweight_M;}
             if(tag.Contains("17")){ puIdweight=puIdweight_T;}
             if(tag.Contains("18")){ prefWeight=1;  puIdweight=puIdweight_L;}
	     actualWeight=scalef*pileupWeight*prefWeight*lumi*photon_id_scale*photon_veto_scale*puIdweight;
	     if(lep==11)
		     actualWeight=actualWeight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
	     if(lep==13)
		     actualWeight=actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
//           if(i%1000==0) cout<<"actualWeight "<<actualWeight<<endl;
	     if (  tformula3->EvalInstance()&&sample.Contains("EWK") ){ 
		     count++;
                     if(genMjj<2000&gendetajj<6.5)
                             h1->Fill(genMjj,gendetajj,actualWeight);
                     else if(genMjj>2000&&gendetajj<6.5)
                             h1->Fill(1999,gendetajj,actualWeight);
                     else if(genMjj<2000 &&gendetajj>6.5)
                             h1->Fill(genMjj,6.1,actualWeight);
                     else
                             h1->Fill(1999,6.1,actualWeight);
	     }
	     if (  tformula1->EvalInstance()&&sample.Contains("EWK") ) {//reco && gen
		     for(int iy=0;iy<3;iy++){
			     for(int ix=0;ix<3;ix++){
				     if(genMjj<2000 && gendetajj<6.5){
					     if(ix<2&&iy<2&&Mjj>mjj_bins[ix]&&Mjj<mjj_bins[ix+1]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(genMjj,gendetajj,actualWeight);
					     if(ix==2&&iy<2&&Mjj>mjj_bins[ix]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(genMjj,gendetajj,actualWeight);
					     if(ix<2&&iy==2&&Mjj>mjj_bins[ix]&& Mjj<mjj_bins[ix+1] &&deltaetajj>detajj_bins[iy])
						     th1[ix+(iy)*3]->Fill(genMjj,gendetajj,actualWeight);
                                             if(ix==2&&iy==2 && Mjj>mjj_bins[ix] && deltaetajj>detajj_bins[iy])
                                                     th1[ix+(iy)*3]->Fill(genMjj,gendetajj,actualWeight);
				     }
				     else if(genMjj>2000 && gendetajj<6.5){
					     if(ix<2&&iy<2&&Mjj>mjj_bins[ix]&&Mjj<mjj_bins[ix+1]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(1999,gendetajj,actualWeight);
					     if(ix==2&&iy<2&&Mjj>mjj_bins[ix]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(1999,gendetajj,actualWeight);
					     if(ix<2&&iy==2&&Mjj>mjj_bins[ix]&& Mjj<mjj_bins[ix+1] &&deltaetajj>detajj_bins[iy])
						     th1[ix+(iy)*3]->Fill(1999,gendetajj,actualWeight);
                                             if(ix==2&&iy==2 && Mjj>mjj_bins[ix] && deltaetajj>detajj_bins[iy])
                                                     th1[ix+(iy)*3]->Fill(genMjj,gendetajj,actualWeight);
				     }
				     else if(genMjj<2000 && gendetajj>6.5){
					     if(ix<2&&iy<2&&Mjj>mjj_bins[ix]&&Mjj<mjj_bins[ix+1]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(genMjj,6.1,actualWeight);
					     if(ix==2&&iy<2&&Mjj>mjj_bins[ix]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(genMjj,6.1,actualWeight);
					     if(ix<2&&iy==2&&Mjj>mjj_bins[ix]&& Mjj<mjj_bins[ix+1] &&deltaetajj>detajj_bins[iy])
						     th1[ix+(iy)*3]->Fill(genMjj,6.1,actualWeight);
                                             if(ix==2&&iy==2 && Mjj>mjj_bins[ix] && deltaetajj>detajj_bins[iy])
                                                     th1[ix+(iy)*3]->Fill(genMjj,6.1,actualWeight);
				     }
				     else{
					     if(ix<2&&iy<2&&Mjj>mjj_bins[ix]&&Mjj<mjj_bins[ix+1]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(1999,6.1,actualWeight);
					     if(ix==2&&iy<2&&Mjj>mjj_bins[ix]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
						     th1[ix+(iy)*3]->Fill(1999,6.1,actualWeight);
					     if(ix<2&&iy==2&&Mjj>mjj_bins[ix]&& Mjj<mjj_bins[ix+1] &&deltaetajj>detajj_bins[iy])
						     th1[ix+(iy)*3]->Fill(1999,6.1,actualWeight);
                                             if(ix==2&&iy==2 && Mjj>mjj_bins[ix] && deltaetajj>detajj_bins[iy])
                                                     th1[ix+(iy)*3]->Fill(1999,6.1,actualWeight);
				     }
			     }
		     }
	     }
	     if (  tformula2->EvalInstance()&&sample.Contains("EWK") ){//reco && !gen
		     if(Mjj<2000&deltaetajj<6.5)     
			     th2->Fill(Mjj,deltaetajj,actualWeight);
		     else if(Mjj>2000&&deltaetajj<6.5)
			     th2->Fill(1999,deltaetajj,actualWeight);
		     else if(Mjj<2000 &&deltaetajj>6.5)
			     th2->Fill(Mjj,6.1,actualWeight);
		     else                            
			     th2->Fill(1999,6.1,actualWeight);
	     }
	     if (  tformula->EvalInstance() &&sample.Contains("EWK")==0 ){//reco
		     if(Mjj<2000&deltaetajj<6.5)
			     hist_bkg->Fill(Mjj,deltaetajj,actualWeight);
		     else if(Mjj>2000&&deltaetajj<6.5)
			     hist_bkg->Fill(1999,deltaetajj,actualWeight);
		     else if(Mjj<2000 &&deltaetajj>6.5)
			     hist_bkg->Fill(Mjj,6.1,actualWeight);
		     else
			     hist_bkg->Fill(1999,6.1,actualWeight);
	     }
     }
     double eff=count/nentries;
     cout<<"after gen selection "<<count<<"; total enevts "<<nentries<<"; eff "<<eff<<endl;
     int p=0;
     TFile*fout=new TFile("./2droot/hist_"+sample+"_2d"+tag+".root","recreate");
     if(sample.Contains("EWK")){
	     fout->cd();
	     for(Int_t i=0;i<nbins;i++){
		     th1[i]->Write();
	     }
	     th2->Write();
	     h1->Write();
	     fout->Close();
     }
     else{ 
	     fout->cd();
	     hist_bkg->Write();
	     fout->Close();
     }
     //     h2->Write();
}
int Build_Unfold2DHist_sig(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5 && genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && deltaetajj>2.5 && Mva>100)";
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"ZA-EWK"};
	for(int i=0;i<tag.size();i++){
                if(tag[i].Contains("16")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
                }
                else if(tag[i].Contains("17")){
                        jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
                }
                else if(tag[i].Contains("18")){
                        jet = "( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdLoose==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdLoose==1)) )";
                }
		TString Reco= "(("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
		TString Gen= "(((" + GenLEPmu +")||("+GenLEPele+"))"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion+")";
		TString cut1 ="(("+Reco+")&&("+Gen+"))";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		TString cut3 =Gen; 
//		if(tag[i].Contains("17")==0) continue;
		for(int j=0;j<sample.size();j++){
			cout<<tag[i]<<" "<<sample[j]<<endl;
			run(sample[j],tag[i],cut1,cut2,cut3,Reco);
		}
	}
	return 1;
}
