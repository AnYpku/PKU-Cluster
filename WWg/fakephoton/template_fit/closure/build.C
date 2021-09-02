TH1D* run(TString cut,TString file,TString channel,TString style){
	TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/cutla-"+file+".root");
        TTree*tree=(TTree*)f1->Get("Events");
	vector<double> vector_sieie;
	if(channel=="barrel"){
		for(int i=0;i<21;i++){
			vector_sieie.push_back(0.002+0.001*i);
		}
	}
	else{
		for(int i=0;i<21;i++){
		   vector_sieie.push_back(0.01+0.0025*i);
	}
        TString histname=style+"_"+file;
	TH1D*h1 = new TH1D(histname,"",vector_sieie.size()-1,&vector_sieie[0]);
	if(style=="data" || style=="true") 
		tree->Draw("photonsieie>>"+histname,cut+"*scalef","goff");
	if(style=="fake")
		tree->Draw("photonsieie_f>>"+histname,cut+"*scalef","goff");
	return h1;
}
int build(){
	TString cut1="(channel==1 && lep1_pid==13 && lep2_pid==11 && lep1pt>20 && fabs(lep1eta)<2.4 && lep2pt>20 && fabs(lep2eta)<2.5&&(n_loose_ele+n_loose_mu)==2)&&((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) )";//emu channel




	return 0;
}
