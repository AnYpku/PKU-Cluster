void run(TFile*file,TString var1, TString var2, vector<double> bins,TString cut1,TString cut2,TString cut3,TString tag){
     const int nbins=bins.size()-1; 
     TTree*tree=(TTree*)file->Get("ZPKUCandidates");
     TH1D*th1[nbins];
     TString th1name[nbins];

     TString h2name="hist_"+var1;
     TString h1name="hist1_"+var1;
     TString hist2Dname="hist2D_"+var1;
     TH2D* h2 = new TH2D(h2name,"reco && gen",bins.size()-1,&bins[0],bins.size()-1,&bins[0]);
//     TH2D* hist2D = new TH2D(hist2Dname,"reco && gen",bins.size()-1,&bins[0],bins.size()-1,&bins[0]);
     TH1D* h1 = new TH1D(h1name,var1+" reco && gen",bins.size()-1,&bins[0]); 
     TString th2name;
     th2name="hist_"+var2;
     TH1D*th2 = new TH1D(th2name,"reco && !Gen",bins.size()-1,&bins[0]);
     TString lumi;
     if(tag.Contains("16"))lumi=Form("%f",35.86);cout<<lumi<<endl;
     if(tag.Contains("17"))lumi=Form("%f",41.52);cout<<lumi<<endl;
     if(tag.Contains("18"))lumi=Form("%f",59.7);cout<<lumi<<endl;
     TString weight;
     if(tag.Contains("16"))
        weight="*scalef*pileupWeight*photon_id_scale*photon_veto_scale*fabs(ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale)*fabs(muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale)*prefWeight*"+lumi;
     else if(tag.Contains("17"))
        weight="*scalef*pileupWeight*photon_id_scale*photon_veto_scale*fabs(ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale)*fabs(muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale)*prefWeight*puIdweight_M*"+lumi;
     else if(tag.Contains("18"))
        weight="*scalef*pileupWeight*photon_id_scale*photon_veto_scale*fabs(ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale)*fabs(muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale)*"+lumi;
     TTreeFormula *tformula=new TTreeFormula("formula", cut3, tree); 
     double count=0,nentries=tree->GetEntries();
     for(int i=0;i<tree->GetEntries();i++){
             tree->GetEntry(i);
             if (  tformula->EvalInstance() ) 
		     count++;
     }
     double eff=count/nentries;
     cout<<"after gen selection "<<count<<"; total enevts "<<nentries<<"; eff "<<eff<<endl;
     for(Int_t i=0;i<nbins;i++){
	     th1name[i]=var1+Form("_%d",i);
	     th1[i] = new TH1D(th1name[i],"reco && gen",bins.size()-1,&bins[0]);
	     th1[i]->Sumw2(); 
     }      
     int p=0;
     tree->Draw(var1+":"+var2+">>"+h2name,cut1+weight,"goff");
     tree->Draw(var2+">>"+th2name,cut2+weight,"goff");
     tree->Draw(var1+">>"+h1name,cut1+weight,"goff");
     TString h3name="histGen_"+var1;
     TH1D* h3 = new TH1D(h3name,var1+" gen",bins.size()-1,&bins[0]); 
     tree->Draw(var1+">>"+h3name,cut3+"*scalef*"+lumi,"goff");
     for(Int_t i=0;i<nbins;i++){
             TString low=Form("%f",bins[i]);
             TString high=Form("%f",bins[i+1]);
             cout<<var2<<" "<<low<<" "<<high<<endl;
//	     actualWeight[p]=scalef*pweight[i]*pileupWeight;
             TString index=Form("%i",i);
             if(i<nbins-1)
		     tree->Draw(var1+">>"+th1name[p],"("+cut1+"&&("+var2+">"+low+"&&"+var2+"<"+high+"))"+weight,"goff");
             else if(i==nbins-1)
		     tree->Draw(var1+">>"+th1name[p],"("+cut1+"&&("+var2+">"+low+"))"+weight,"goff");
	     p++;
     }
     TFile*fout=new TFile("./root/hist_ZA-EWK_"+var1+tag+".root","recreate");
     TFile*f1=new TFile("./root/hist_EWK"+tag+"_"+var1+".root","recreate");
     for(Int_t i=0;i<nbins;i++){
             th1[i]->SetBinContent(nbins,th1[i]->GetBinContent(nbins)+th1[i]->GetBinContent(nbins+1));
	     th1[i]->SetBinError(nbins,sqrt(pow(th1[i]->GetBinError(nbins),2)+pow(th1[i]->GetBinError(nbins+1),2)));
             if(i<nbins-1){
		     h2->SetBinContent(i+1,nbins,h2->GetBinContent(i+1,nbins)+h2->GetBinContent(i+1,nbins+1));
		     h2->SetBinError(i+1,nbins,sqrt(pow(h2->GetBinError(i+1,nbins),2)+pow(h2->GetBinError(i+1,nbins+1),2)));
		     h2->SetBinContent(nbins,i+1,h2->GetBinContent(nbins,i+1)+h2->GetBinContent(nbins+1,i+1));
		     h2->SetBinError(nbins,i+1,sqrt(pow(h2->GetBinError(nbins,i+1),2)+pow(h2->GetBinError(nbins+1,i+1),2)));
		     h2->SetBinContent(i+1,nbins+1,0);
		     h2->SetBinError(i+1,nbins+1,0);
		     h2->SetBinContent(nbins+1,i+1,0);
		     h2->SetBinError(nbins+1,i+1,0);
	     }
	     if(i==nbins-1){
		     h2->SetBinContent(nbins,nbins,h2->GetBinContent(nbins,nbins)+h2->GetBinContent(nbins+1,nbins+1)+h2->GetBinContent(nbins,nbins+1)+h2->GetBinContent(nbins+1,nbins));
		     h2->SetBinError(nbins,nbins,sqrt(pow(h2->GetBinError(nbins,nbins),2)+pow(h2->GetBinError(nbins+1,nbins+1),2)+pow(h2->GetBinError(nbins,nbins+1),2)+pow(h2->GetBinError(nbins+1,nbins),2)));
                     h2->SetBinContent(nbins,nbins+1,0);
                     h2->SetBinError(nbins,nbins+1,0);
                     h2->SetBinContent(nbins+1,nbins,0);
                     h2->SetBinError(nbins+1,nbins,0);
                     h2->SetBinContent(nbins+1,nbins+1,0);
                     h2->SetBinError(nbins+1,nbins+1,0);
	     }
     }//add overflow bin and error
     th2->SetBinContent(nbins,th2->GetBinContent(nbins)+th2->GetBinContent(nbins+1));//add overflowbin
     th2->SetBinError(nbins,sqrt(pow(th2->GetBinError(nbins),2)+pow(th2->GetBinError(nbins+1),2)));//error
     h1->SetBinContent(nbins,h1->GetBinContent(nbins)+h1->GetBinContent(nbins+1));//add overflowbin
     h1->SetBinError(nbins,sqrt(pow(h1->GetBinError(nbins),2)+pow(h1->GetBinError(nbins+1),2)));//error
     h3->SetBinContent(nbins,h3->GetBinContent(nbins)+h3->GetBinContent(nbins+1));//add overflowbin
     h3->SetBinError(nbins,sqrt(pow(h3->GetBinError(nbins),2)+pow(h3->GetBinError(nbins+1),2)));//error
     fout->cd();
     for(Int_t i=0;i<nbins;i++){
	     th1[i]->Write();
     }
     th2->Write();
     h1->Write();
     h2->Write();
     h3->Write();
     fout->Close();
     f1->cd();
     h1->Write();
     f1->Close();
}
int Build_UnfoldHist_sig(){
     TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4 && genmassVlep>70 && genmassVlep<110)";
     TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5 && genmassVlep>70 && genmassVlep<110)";
     TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ) )";
     TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
     TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
     TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";
     TString Gen= "(((" + GenLEPmu +")||("+GenLEPele+"))"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion +")";

     TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
     TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
     TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
     TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
     TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
     TString SignalRegion = "(Mjj>500 && deltaetajj>2.5 && Mva>100)";

     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,200,300,500,1000};
     vector<double> massVlepBins={70,80,90,100,110};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
//     bins.push_back(MvaBins);
//     bins.push_back(massVlepBins);

     TFile*file[3];

     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};
     vector<TString> recovars={"ptlep1","photonet","jet1pt"};
//     vector<TString> genvars={"genZGmass","genmassVlep"};
//     vector<TString> recovars={"Mva","massVlep"};
     vector<TString> tag={"16","17","18"};
     for(int i=0;i<tag.size();i++){
	     if(tag[i].Contains("17")){
		     jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
	     }
	     else jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	     TString Reco= "(("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
	     TString cut1 ="(("+Reco+")&&("+Gen+"))";
//	     TString cut1 ="(("+Gen+"))";
	     TString cut2 ="(("+Reco+")&& !("+Gen+"))";
	     TString cut3 =Gen; 
	     TString dir="/home/pku/anying/cms/rootfiles/20"+tag[i]+"/";
	     file[i]=new TFile(dir+"unfold_GenCutla-ZA-EWK"+tag[i]+".root");
	     for(int j=0;j<genvars.size();j++){     
		     run(file[i],genvars[j], recovars[j], bins[j],cut1,cut2,cut3,tag[i]);
	     }
     }
     return 1;
}
