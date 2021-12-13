TH1D* run(TString cut,TString file,TString channel,TString isBarrel,TString year){
        vector<double> ptbins;
        if(isBarrel.Contains("barrel"))
                ptbins={20,25,30,35,40,50,60,100,400};
        else    ptbins={20,25,30,40,50,60,400};
        TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/20"+year+"/cutlep-"+file+".root");
        TTree*tree=(TTree*)f1->Get("Events");
        TString histname=file+"_"+channel+"_"+isBarrel;
        TH1D*h1 = new TH1D(histname,"",ptbins.size()-1,&ptbins[0]);
        TString HLT_emu,HLT_ee,HLT_mm;
        HLT_emu="((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL))";
        
	if(file.Contains("MuonEG")) HLT_soup="((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL))"
	else if(file.Contains("Muon")) HLT_soup="(!((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) && (HLT_IsoMu24))"
	else HLT_soup="(!((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) && !(HLT_IsoMu24) && (HLT_Ele35_WPTight_Gsf))"
