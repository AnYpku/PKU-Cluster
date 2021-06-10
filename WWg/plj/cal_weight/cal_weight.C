TH1D* run(TString cut,TString file){
	vector<double> ptbins={20,30,40,50,80,400};
	TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/cutla-"+file+".root");
	TTree*tree=(TTree*)f1->Get("Events");
        TH1D*h1 = new TH1D(file,"",ptbins.size()-1,&ptbins[0]);
	if(file.Contains("Muon")||file.Contains("Ele"))
		tree->Draw("photonet>>"+file,cut+"*1","goff");
        else
		tree->Draw("photonet>>"+file,cut+"*scalef","goff");

	return h1;
}
int cal_weight(){
	TString cut1="( channel==1 && lep1_pid==13 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.5 && (n_loose_ele+n_loose_mu)==2 && n_photon>0 && photonet > 20. && (fabs(photoneta) < 1.4442) && (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL||HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL||HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) )";
	TString cut2="( channel==1 && lep1_pid==13 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.5 && (n_loose_ele+n_loose_mu)==2 && n_photon>0 && photonet > 20. && (fabs(photoneta) < 1.4442) && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) && (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL||HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL||HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) )";
	TString cut3="( channel==1 && lep1_pid==13 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.5 && (n_loose_ele+n_loose_mu)==2 && n_photon>0 && photonet > 20. && (fabs(photoneta) < 1.4442) && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) && (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL||HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL||HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) && photon_isprompt==1 )";
     TFile*fout=new TFile("hist.root","recreate");
     TH1D*h1=run(cut1,"MuonEG18");
     TH1D*h2=run(cut2,"MuonEG_f18");
     TH1D*h3=run(cut3,"outZGJets_f18");
     TH1D*h4=run(cut3,"outTTGJets_f18");
     h3->Scale(59.7);
     h4->Scale(59.7);
     fout->cd();
     h1->Write();
     h2->Write();
     h3->Write();
     h4->Write();
     TCanvas*c1=new TCanvas("c1","",900,600);
     TLegend*l1=new TLegend(0.6,0.6,0.9,0.9);
     gStyle->SetOptStat(0);
     h2->Draw();
     h1->Draw("same");
     h3->Draw("same");
     h4->Draw("same");
     h1->SetLineColor(2);
     h2->SetLineColor(3);
     h3->SetLineColor(4);
     h4->SetLineColor(5);
     l1->AddEntry(h1,"data");
     l1->AddEntry(h2,"plj");
     l1->AddEntry(h3,"ZGJets");
     l1->AddEntry(h4,"TTGJets");
     l1->Draw();
     c1->Print("hist_dataVSplj.pdf");
     ifstream f1;
     vector<double> ptbins={20,30,40,50,80,400};     
     const int n=ptbins.size()-1;
     double fakerate[n];
     ofstream ftxt("pljweight_em_barrel.txt");
     for(int i=0;i<ptbins.size()-1;i++){
        f1.open(Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/barrel/txt/fakerate_ZA_pt%0.f_%0.f.txt",ptbins[i],ptbins[i+1]));
        if(!f1.is_open())  cout<<"can not open the file "<<Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/barrel/txt/fakerate_ZA_pt%0.f_%0.f",ptbins[i],ptbins[i+1])<<endl;
        f1>>fakerate[i];
        double plj_weight=h1->GetBinContent(i+1)/(h2->GetBinContent(i+1)-h3->GetBinContent(i+1)-h4->GetBinContent(i+1))*fakerate[i];
        cout<<" pt "<<ptbins[i]<<"~"<<ptbins[i+1]<<" "<<fakerate[i]<<" "<<plj_weight<<endl;
        
        ftxt<<fixed<<setprecision(2)<<plj_weight<<endl;
	f1.close();
     }
return 0;
}
