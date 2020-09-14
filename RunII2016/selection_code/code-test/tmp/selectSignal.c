void selectSignal(){
    
    TChain *chain=new TChain("treeDumper/ZPKUCandidates");
    chain->Add("root://xrootd-cms.infn.it//store/user/yian/ZGToLLG_01J_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/pweight_11-23_QCD-ZA/181123_085557/0000/QCDZA-pweight_*.root");
    /*for(Int_t i=1;i<220;i++){
	    chain->Add(Form("root://xrootd-cms.infn.it//store/user/yian/ZGToLLG_01J_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/pweight_11-23_QCD-ZA/181123_085557/0000/QCDZA-pweight_%0.d.root",i));
    }*/
    double ptlep1,ptlep2,etalep1,etalep2,massVlep;
    double jet1pt,jet2pt,jet1eta,jet2eta;
    double photonet,photoneta;
    double pweight[703],Mjj,deltaetajj,zepp;
    double scalef,theWeight,lumiWeight;
    double actualWeight,npT;
    int nlooseeles,nloosemus,HLT_Ele2,lep,HLT_Mu2;
//    chain->SetBranchAddress("scalef",&scalef);
    chain->SetBranchAddress("theWeight",&theWeight);
    chain->SetBranchAddress("lumiWeight",&lumiWeight);
    chain->SetBranchAddress("nloosemus",&nloosemus);
    chain->SetBranchAddress("nlooseeles",&nlooseeles);
    chain->SetBranchAddress("HLT_Ele2",&HLT_Ele2);
    chain->SetBranchAddress("HLT_Mu2",&HLT_Mu2);
    chain->SetBranchAddress("lep",&lep);
    chain->SetBranchAddress("pweight",pweight);
    chain->SetBranchAddress("Mjj",&Mjj);
    chain->SetBranchAddress("deltaetajj",&deltaetajj);
    chain->SetBranchAddress("zepp",&zepp);
    chain->SetBranchAddress("photonet",&photonet);
    chain->SetBranchAddress("photoneta",&photoneta);
    chain->SetBranchAddress("jet1pt",&jet1pt);
    chain->SetBranchAddress("jet2pt",&jet2pt);
    chain->SetBranchAddress("jet1eta",&jet1eta);
    chain->SetBranchAddress("jet2eta",&jet2eta);
    chain->SetBranchAddress("ptlep1",&ptlep1);
    chain->SetBranchAddress("ptlep2",&ptlep2);
    chain->SetBranchAddress("etalep1",&etalep1);
    chain->SetBranchAddress("etalep2",&etalep2);
    chain->SetBranchAddress("massVlep",&massVlep);

    Long64_t npp = chain->GetEntries("theWeight>0.");
    Long64_t nmm = chain->GetEntries("theWeight<0.");

    TFile * input13 = new TFile ("./pu_calc/puweight.root");
    TH1* h13 = NULL;
    input13->GetObject("h2",h13);

    TFile *newfile = new TFile("outZA-mu-ele.root", "recreate");
    //in the new.root files, all events satisfy your cuts 
    TTree *newtree = chain->CloneTree(0);
    newtree->Branch("scalef",&scalef,"scalef/D");
    newtree->Branch("actualWeight",&actualWeight,"actualWeight/D");
    int nentries = chain->GetEntriesFast();
    cout<<"nentries = "<<nentries<<endl;
    int cut0=0,cut1=0,cut2=0,cut3=0,cut4=0;
    bool LEPmu,LEPele,JET,PHOTON,SignalRegion;
    vector<double> vector_pt;
    vector<double>::iterator biggest_pt;
    int position=0,size,m=0;
    for (int i = 0; i < nentries; i++) {
      chain->GetEntry(i);
      scalef = 1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight;
      pileupWeight=h13->GetBinContent(h13->GetXaxis()->FindBin(npT));
      actualWeight = scalef*pileupWeight*lumiWeight;
      cut0++;//total events, cut0=chain->GetEntries()
      LEPmu = lep==13 && HLT_Mu2>0&& ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep < 110;
      LEPele = lep==11 && HLT_Ele2>0 && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep < 110;
      SignalRegion= Mjj>500 && deltaetajj>2.5 && zepp<1.8;
      PHOTON= photonet>25 &&((fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || fabs(photoneta)<1.4442); 
      JET=jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150;
      if(!( (LEPmu||LEPele) && PHOTON && JET && SignalRegion))
	      continue;
      cut1++; //how many events passing the selection 
      /*if(SignalRegion==false)
	      continue;
      cut2++;  //after passing the selection of photons,how many events pass the SignalRegion selection*/
      newtree->Fill(); //fill the brach when this entry pass the both selection
  }
    newtree->Write(); //fill this tree into KEY from OBJ
    newfile->Close();
    input13->Close();
	//print some information 
    std::cout << "The total events are      : " << cut0 << std::endl;
    std::cout << "The qualified events      : " << cut1 << std::endl;
//    std::cout << "The SignalRegion selection: " << cut2 << std::endl;
}
