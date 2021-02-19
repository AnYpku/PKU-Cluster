#define num 3
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
TH2D*merge_hist(TFile*f1,TFile*f2,TFile*f3,int i,TString var){
//	cout<<"get histograms"<<endl;
	TH2D*h2    =(TH2D*)f1->Get(var+Form("_%i_recobin7",i)); 
	TH2D*h2_1  =(TH2D*)f2->Get(var+Form("_%i_recobin8",i)); 
	TH2D*h2_2  =(TH2D*)f3->Get(var+Form("_%i_recobin9",i)); 
//	cout<<"add histograms"<<endl;
	h2->Add(h2_1,1);
	h2->Add(h2_2,1);
//        cout<<h2->GetNbinsX()<<" "<<h2->GetNbinsY()<<endl;
	return h2;
}
int unroll_2d(){
	TH1D* hist[num];
	TH2D* th2[num];
        TH2D* th2_7[num]; 
        TH1D* hist_7[num];
        TFile*file[7][3];//[recobin][year]
        TFile*fout[7][3];//[recobin][year]
	vector<TString> tag={"16","17","18"};
	vector<TString> sample;
	vector<TString> var={"genMjj"};
	for(int ik=0;ik<1;ik++){
		if(var[ik].Contains("gen"))sample={"ZA"};
		else  sample={"ZAout","ZA","ST","TTA","VV"};
		for(int kk=0;kk<sample.size();kk++){
			for(int i=0;i<tag.size();i++){
				if(tag[i].Contains("17")==0) continue;
				for(int j=0;j<6;j++){
					file[j][i]=new TFile("unfold_"+sample[kk]+"_2d"+var[ik]+Form("_recobin%i_jes",j+1)+tag[i]+".root");
					fout[j][i]=new TFile("unfold_"+sample[kk]+"_"+var[ik]+Form("_recobin%i_jes",j+1)+tag[i]+".root","recreate");
					cout<<tag[i]<<" recobin"<<j+1<<endl;
					fout[j][i]->cd();
					for(int k=0;k<num;k++){
						th2[k]=(TH2D*)file[j][i]->Get(var[ik]+Form("_%i_recobin%i",k,j+1));
						hist[k]=unroll_hist(th2[k],var[ik]+Form("_%i_recobin%i",k,j+1));
						hist[k]->Write();
					}
					cout<<"file index "<<j<<" "<<i<<endl;
					fout[j][i]->Close();
				}
				TFile*f1=new TFile("unfold_"+sample[kk]+"_2d"+var[ik]+"_recobin7_jes"+tag[i]+".root");
				TFile*f2=new TFile("unfold_"+sample[kk]+"_2d"+var[ik]+"_recobin8_jes"+tag[i]+".root");
				TFile*f3=new TFile("unfold_"+sample[kk]+"_2d"+var[ik]+"_recobin9_jes"+tag[i]+".root");

				fout[6][i]=new TFile("unfold_"+sample[kk]+"_"+var[ik]+"_recobin7_jes"+tag[i]+".root","recreate");
				for(int k=0;k<num;k++){
					th2_7[k]=merge_hist(f1,f2,f3,k,var[ik]); 
					//cout<<"get merged histograms"<<endl;
					//cout<<th2_7[k]->GetNbinsX()<<" "<<th2_7[k]->GetNbinsY()<<endl;
					hist_7[k]=unroll_hist(th2_7[k],var[ik]+Form("_%i_recobin7",k));
					//cout<<" "<<hist_7[k]->GetNbinsX()<<endl;
					fout[6][i]->cd();
					hist_7[k]->Write();
				}
				cout<<tag[i]<<" get 7 recobins "<<endl;
				fout[6][i]->Close();
				f1->Close();
				f2->Close();
				f3->Close();
			}
		}
	}

	return 0;
}
