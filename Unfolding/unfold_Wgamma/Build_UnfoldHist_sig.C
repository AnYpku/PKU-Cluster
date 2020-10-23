void run(TFile*file,TString var1, TString var2, vector<double> bins,TString cut1,TString cut2,TString cut3,TString cut4,TString tag){
     const int nbins=bins.size()-1; 
     TTree*tree=(TTree*)file->Get("PKUCandidates");
     TH1D*th1[nbins];
     TString th1name[nbins];

     TString h2name="hist_"+var1;
     TString h1name="hist1_"+var1;
     TH2D* h2 = new TH2D(h2name,"reco && gen",bins.size()-1,&bins[0],bins.size()-1,&bins[0]);
     TH1D* h1 = new TH1D(h1name,var1+" reco && gen",bins.size()-1,&bins[0]); 
     TString th2name;
     th2name="hist_"+var2;
     TH1D*th2 = new TH1D(th2name,"reco && !Gen",bins.size()-1,&bins[0]);
     TString lumi;
     if(tag.Contains("16"))lumi=Form("%f",35.86);cout<<lumi<<endl;
     if(tag.Contains("17"))lumi=Form("%f",41.52);cout<<lumi<<endl;
     if(tag.Contains("18"))lumi=Form("%f",58.7);cout<<lumi<<endl;
     TTreeFormula *tformula3=new TTreeFormula("formula", cut3, tree); //gen
     TTreeFormula *tformula4=new TTreeFormula("formula", cut4, tree); //reco
     TTreeFormula *tformula1=new TTreeFormula("formula", cut1, tree);  // reco && gen
     TTreeFormula *tformula2=new TTreeFormula("formula", cut2, tree);  // reco && !gen
     double count=0,nentries=tree->GetEntries();
     double count_1=0,count_2=0,count_4=0;
     for(int i=0;i<tree->GetEntries();i++){
             tree->GetEntry(i);
             if(i%10000==0)cout<<i<<" "<<tree->GetEntries()<<endl;
             if (  tformula3->EvalInstance() ) 
		     count++;
             if (  tformula4->EvalInstance() ) 
		     count_4++;
             if (  tformula1->EvalInstance() ) 
		     count_1++;
             if (  tformula2->EvalInstance() ) 
		     count_2++;
     }
     double eff=count/nentries;
     cout<<"after gen selection "<<count<<"; total enevts "<<nentries<<"; eff "<<eff<<endl;
     cout<<"reco="<<count_4<<"; reco && gen="<<count_1<<"; reco && !gen "<<count_2<<endl;
//     tree->Draw(var1+":"+var2+">>"+h2name,cut1+"*scalef*"+lumi,"goff");
/*     for(Int_t i=0;i<nbins;i++){
	     th1name[i]=var1+Form("_%d",i);
	     th1[i] = new TH1D(th1name[i],"reco && gen",bins.size()-1,&bins[0]);
	     th1[i]->Sumw2(); 
     }      
     int p=0;
     tree->Draw(var1+":"+var2+">>"+h2name,cut1+"*scalef*"+lumi,"goff");
     tree->Draw(var2+">>"+th2name,cut2+"*scalef*"+lumi,"goff");
     tree->Draw(var1+">>"+h1name,cut1+"*scalef*"+lumi,"goff");
     for(Int_t i=0;i<nbins;i++){
             TString low=Form("%f",bins[i]);
             TString high=Form("%f",bins[i+1]);
             cout<<var2<<" "<<low<<" "<<high<<endl;
//	     actualWeight[p]=scalef*pweight[i]*pileupWeight;
             TString index=Form("%i",i);
             if(i<nbins-1)
		     tree->Draw(var1+">>"+th1name[p],"("+cut1+"&&("+var2+">"+low+"&&"+var2+"<"+high+"))*scalef*"+lumi,"goff");
             else if(i==nbins-1)
		     tree->Draw(var1+">>"+th1name[p],"("+cut1+"&&("+var2+">"+low+"))*scalef*"+lumi,"goff");
	     p++;
     }
     TFile*fout=new TFile("hist_ZA-EWK_"+var1+tag+".root","recreate");
     TFile*f1=new TFile("hist_EWK"+tag+"_"+var1+".root","recreate");
     for(Int_t i=0;i<nbins;i++){
             th1[i]->SetBinContent(nbins,th1[i]->GetBinContent(nbins)+th1[i]->GetBinContent(nbins+1));
     }//add overflow bin
     th2->SetBinContent(nbins,th2->GetBinContent(nbins)+th2->GetBinContent(nbins+1));//add overflowbin
     h1->SetBinContent(nbins,h1->GetBinContent(nbins)+h1->GetBinContent(nbins+1));//add overflowbin
     fout->cd();
     for(Int_t i=0;i<nbins;i++){
	     th1[i]->Write();
     }
     th2->Write();
     h1->Write();
     h2->Write();
     fout->Close();
     f1->cd();
     h1->Write();
     f1->Close();*/
}
int Build_UnfoldHist_sig(){
     TString GenLEPmu  = "genlep==13 && genlep1pt>30 && fabs(genlep1eta)<2.4 && genMET>30";
     TString GenLEPele = "genlep==11 && genlep1pt>30 && fabs(genlep1eta)<2.5 && genMET>30";
     TString GenPhoton = "genphotonet>25 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) )";
     TString GenJet = "genjet1pt>40 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7";
     TString GenDr = "gendrjj>0.5 && gendrla1>0.5 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 ";
     TString GenSignalRegion = "genMjj >500 && gendetajj>2.5";
     TString Gen= "((" + GenLEPmu +")||("+GenLEPele+"))"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

     TString LEPmu = "abs(lep)==13 &&  ptlep1 > 30. && fabs(etalep1) < 2.4 && nlooseeles==0 && nloosemus <2  && HLT_Mu3==1 && (nloosemus+nlooseeles)==1";
     TString LEPele = "abs(lep)==11  && ptlep1 > 30.&& fabs(etalep1) < 2.5 && nlooseeles<2 && nloosemus ==0  && (nloosemus+nlooseeles)==1 && HLT_Ele2==1";
     TString photon = "photonet>25 &&( (fabs(photonsceta)<2.5&&fabs(photonsceta)>1.566) || (fabs(photonsceta)<1.4442) ) && photonhaspixelseed==0";
     TString jet = "jet1pt_new> 40 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && mtVlepJECnew_new>30 && MET_et>30 && abs(j1metPhi_new)>0.5 && fabs(j2metPhi_new)>0.5 && (jet1deepcsv_probb_new + jet1deepcsv_probbb_new)<0.4184 && (jet2deepcsv_probb_new + jet2deepcsv_probbb_new)<0.4184";
     TString dr = "drjj>0.5 && drla>0.5  && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5";
     TString SignalRegion = "Mjj_new>500 && Mla>30 && fabs(jet1eta_new-jet2eta_new)>2.5 && Mva>100";
     TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
     TString cut1 ="(("+Reco+")&&("+Gen+"))";
     TString cut2 ="(("+Reco+")&& !("+Gen+"))";
     TString cut3 =Gen; 
     TString cut4=Reco;

     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> massVlepBins={70,85,100,110};
     vector<double> MjjBins={500,2000};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(massVlepBins);
     bins.push_back(MjjBins);

     TString dir="/eos/user/y/yian/";
     TFile*file1=new TFile(dir+"unfold_16EWK_WG.root");
//     TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/produce/";
//     TFile*file1=new TFile(dir+"unfold_16outZA-EWK.root");
//     TFile*file2=new TFile(dir+"unfold_17outZA-EWK-pweight.root");
//     TFile*file3=new TFile(dir+"unfold_18outZA-EWK-pweight.root");

     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genmassVlep","genMjj"};
     vector<TString> recovars={"ptlep1","photonet","jet1pt","massVlep","Mjj"};
//     vector<TString> genvars={"genZGmass","genMjj"};
//     vector<TString> recovars={"Mva","Mjj"};

//     for(int j=0;j<genvars.size();j++){     
     for(int j=0;j<1;j++){     
	     run(file1,genvars[j], recovars[j], bins[j],cut1,cut2,cut3,cut4,"16");
//	     run(file2,genvars[j], recovars[j], bins[j],cut1,cut2,cut3,"17");
//	     run(file3,genvars[j], recovars[j], bins[j],cut1,cut2,cut3,"18");
     }
     return 1;
}
