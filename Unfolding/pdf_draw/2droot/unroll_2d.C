#define num 1
TH1D*unroll_hist(TH2D*h2,TString histname){
        int binsx=h2->GetNbinsX();int binsy=h2->GetNbinsY();
	int nbins=binsx*binsy;
	TH1D*h1=new TH1D(histname+"_tmp",histname,nbins,0,nbins);
        TH1D*h1_out=new TH1D(histname,histname,nbins-2,0,nbins-2);
	for(int ix=1;ix<=binsy;ix++){
		for(int iy=1;iy<=binsx;iy++){
                    h1->SetBinContent(ix+(iy-1)*binsx,h2->GetBinContent(ix,iy));
                    h1->SetBinError(ix+(iy-1)*binsx,h2->GetBinError(ix,iy));
		}
	}
	for(int i=0;i<nbins-2;i++){
                h1_out->SetBinContent(i+1,h1->GetBinContent(i+1));
                h1_out->SetBinError(i+1,h1->GetBinError(i+1));
	}
	h1_out->SetBinContent(nbins-2,h1->GetBinContent(nbins-2)+h1->GetBinContent(nbins-1)+h1->GetBinContent(nbins));
	h1_out->SetBinError(nbins-2,sqrt( pow(h1->GetBinError(nbins-2),2)+pow(h1->GetBinError(nbins-1),2)+pow(h1->GetBinError(nbins),2) ) );
	return h1_out;
}
TH2D*merge_hist(TFile*file,TString histname1,TString histname2,TString histname3){
	TH2D*h2  =(TH2D*)file->Get(histname1); 
	//	cout<<file->GetName()<<" "<<histname1<<endl;
	TH2D*h2_1=(TH2D*)file->Get(histname2);
	TH2D*h2_2=(TH2D*)file->Get(histname3);
	h2->Add(h2_1);
	h2->Add(h2_2);
	return h2;
}
int unroll_2d(){
	TH1D* hist[num];
	TH2D* th2[num];
	TH1D*h1;TH2D*h2;
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"ZA-EWK"};//,"ZA","plj","TTA","VV","ST";
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<sample.size();j++){
			cout<<tag[i]<<" "<<sample[j]<<endl;
			TFile*file=new TFile("./unfold_genMjj_ewk"+tag[i]+".root");
			TFile*fout;
			if(sample[j].Contains("EWK")){
				fout=new TFile("../unfold_genMjj_ewk"+tag[i]+".root","recreate");
				for(int k=0;k<num;k++){
					th2[k]=(TH2D*)file->Get(Form("genMjj_%i",k));
					hist[k]=unroll_hist(th2[k],Form("genMjj_%i",k));
				}
			}
			if(sample[j].Contains("EWK")){
				fout->cd(); 
				for(int k=0;k<num;k++){
					hist[k]->Write();
				}
			}
			fout->Close();
		}
	} 

	return 0;
}
