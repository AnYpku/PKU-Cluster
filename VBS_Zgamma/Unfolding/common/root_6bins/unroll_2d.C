TH1D*unroll_hist(TH2D*h2,TString histname){
        int binsx=h2->GetNbinsX();int binsy=h2->GetNbinsY();
	int nbins=binsx*binsy;
	TH1D*h1=new TH1D(histname+"_tmp",histname,nbins,0,nbins);
        TH1D*h1_out=new TH1D(histname,histname,nbins-3,0,nbins-3);
	for(int ix=1;ix<=binsy;ix++){
		for(int iy=1;iy<=binsx;iy++){
                    h1->SetBinContent(ix+(iy-1)*binsx,h2->GetBinContent(ix,iy));
                    h1->SetBinError(ix+(iy-1)*binsx,h2->GetBinError(ix,iy));
		}
	}
	for(int i=1;i<=nbins-3;i++){//1 to 6
		if(i<=3){
			h1_out->SetBinContent(i,h1->GetBinContent(i));
			h1_out->SetBinError(i,h1->GetBinError(i));//1,2,3
		}
		else if(i==4){
			h1_out->SetBinContent(4,h1->GetBinContent(4)+h1->GetBinContent(5));
			h1_out->SetBinError(4,sqrt(h1->GetBinError(4)*h1->GetBinError(4)+h1->GetBinError(5)*h1->GetBinError(5)));//4
		}
		else if(i==5){
			h1_out->SetBinContent(5,h1->GetBinContent(6));
                        h1_out->SetBinError(5,h1->GetBinError(6));//5
		}
		else if(i==6){
                        h1_out->SetBinContent(6,h1->GetBinContent(7)+h1->GetBinContent(8)+h1->GetBinContent(9));
                        h1_out->SetBinError(6,sqrt(h1->GetBinError(7)*h1->GetBinError(7)+h1->GetBinError(8)*h1->GetBinError(8)+h1->GetBinError(9)*h1->GetBinError(9)));//6
		}
	}
	return h1_out;
}
TH2D*merge_hist6(TFile*file,TString histname1,TString histname2,TString histname3){
	TH2D*h2  =(TH2D*)file->Get(histname1); 
	//	cout<<file->GetName()<<" "<<histname1<<endl;
	TH2D*h2_1=(TH2D*)file->Get(histname2);
	TH2D*h2_2=(TH2D*)file->Get(histname3);
	h2->Add(h2_1);
	h2->Add(h2_2);
	return h2;
}

TH2D*merge_hist4(TFile*file,TString histname1,TString histname2){
	TH2D*h2  =(TH2D*)file->Get(histname1); 
	TH2D*h2_1=(TH2D*)file->Get(histname2);
	h2->Add(h2_1);
	return h2;
}
int unroll_2d(){
	TH1D* hist[6];
	TH2D* th2[6];
	TH1D*h1;TH2D*h2;
	TH2D*th2_7;TH1D*hist_7;
        TH2D*hist2_out;
        TH1D*hist_out;
	TH2D*h2Gen;
	TH1D*h1Gen;
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"ZA-EWK","ZA","plj","TTA","VV","ST"};
//	vector<TString> sample={"plj"};
//	vector<TString> sample={"DMuon","DEle"};
	for(int i=0;i<tag.size();i++){
//              if(tag[i].Contains("17")==0) continue;
		for(int j=0;j<sample.size();j++){
			cout<<tag[i]<<" "<<sample[j]<<endl;
			TFile*file=new TFile("../2droot/hist_"+sample[j]+"_2d"+tag[i]+".root");
			TFile*fout;
			if(sample[j].Contains("EWK")){
				fout=new TFile("./hist_"+sample[j]+"_genMjj"+tag[i]+".root","recreate");
				th2_7=merge_hist6(file,"hist2d_6","hist2d_7","hist2d_8");
				hist_7=unroll_hist(th2_7,"genMjj_5");
                                hist2_out=(TH2D*)file->Get("hist_2d"+tag[i]);
                                h2Gen=(TH2D*)file->Get("histGen_genMjj");
				h1Gen = unroll_hist(h2Gen,"histGen_genMjj"); 
				for(int k=0;k<5;k++){
					if(k<3)th2[k]=(TH2D*)file->Get(Form("hist2d_%i",k));
					else if(k==3)th2[k]=merge_hist4(file,"hist2d_3","hist2d_4");
					else if(k==4)th2[k]=(TH2D*)file->Get("hist2d_5");
					hist[k]=unroll_hist(th2[k],Form("genMjj_%i",k));
				}
				hist_out=unroll_hist(hist2_out,"hist_Mjj");
			}
			else{
				fout=new TFile("./hist_"+sample[j]+"_Mjj"+tag[i]+".root","recreate");
				h2=(TH2D*)file->Get("hist_2d"+tag[i]);
				h1=unroll_hist(h2,"hist_Mjj");
				fout->cd();
				h1->Write();
			}
			if(sample[j].Contains("EWK")){
				fout->cd(); 
				h1Gen->Write();
				hist_out->Write();
				for(int k=0;k<5;k++){
					hist[k]->Write();
				}
				hist_7->Write();
			}
			fout->Close();
		}
	} 

	return 0;
}
