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
TH2D*merge_hist(TFile*f1,TFile*f2,TFile*f3,TString sample){
	cout<<"get histograms"<<endl;
	TH2D*h2    =(TH2D*)f1->Get("genMjj_"+sample+"_recobin7"); 
	TH2D*h2_1  =(TH2D*)f2->Get("genMjj_"+sample+"_recobin8"); 
	TH2D*h2_2  =(TH2D*)f3->Get("genMjj_"+sample+"_recobin9"); 
	cout<<"add histograms"<<endl;
	h2->Add(h2_1,1);
	h2->Add(h2_2,1);
//        cout<<h2->GetNbinsX()<<" "<<h2->GetNbinsY()<<endl;
	return h2;
}
int unroll_2d(){
	TH1D* hist;
	TH2D* th2;
        TH2D* th2_7; 
        TH1D* hist_7;
        TFile*file[7][3][2];//[recobin][year][sample] 
        TFile*fout[7][3][2];//[recobin][year][sample]
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"EWK","interf"};
	for(int i=0;i<tag.size();i++){
		for(int ik=0;ik<sample.size();ik++){
			for(int j=0;j<6;j++){
				file[j][i][ik]=new TFile(Form("unfold_2dgenMjj_recobin%i_",j+1)+sample[ik]+tag[i]+".root");
				fout[j][i][ik]=new TFile(Form("unfold_genMjj_recobin%i_",j+1)+sample[ik]+tag[i]+".root","recreate");
				cout<<tag[i]<<" recobin"<<j+1<<endl;
				fout[j][i][ik]->cd();
				th2=(TH2D*)file[j][i][ik]->Get("genMjj_"+sample[ik]+Form("_recobin%i",j+1));
				hist=unroll_hist(th2,"genMjj_"+sample[ik]+Form("_recobin%i",j+1));
				hist->Write();
				cout<<sample[ik]<<" file index "<<j+1<<" "<<tag[i]<<endl;
				fout[j][i][ik]->Close();
			}
			TFile*f1=new TFile("unfold_2dgenMjj_recobin7_"+sample[ik]+tag[i]+".root");
			TFile*f2=new TFile("unfold_2dgenMjj_recobin8_"+sample[ik]+tag[i]+".root");
			TFile*f3=new TFile("unfold_2dgenMjj_recobin9_"+sample[ik]+tag[i]+".root");

			fout[6][i][ik]=new TFile("unfold_genMjj_recobin7_"+sample[ik]+tag[i]+".root","recreate");
			th2_7=merge_hist(f1,f2,f3,sample[ik]); 
			cout<<"get merged histograms"<<endl;
			cout<<th2_7->GetNbinsX()<<" "<<th2_7->GetNbinsY()<<endl;
			hist_7=unroll_hist(th2_7,"genMjj_"+sample[ik]+"_recobin7");
			//cout<<" "<<hist_7[k]->GetNbinsX()<<endl;
			fout[6][i][ik]->cd();
			hist_7->Write();
			cout<<tag[i]<<" get 7 recobins "<<endl;
			fout[6][i][ik]->Close();
			f1->Close();
			f2->Close();
			f3->Close();
		}
	}

	return 0;
}
