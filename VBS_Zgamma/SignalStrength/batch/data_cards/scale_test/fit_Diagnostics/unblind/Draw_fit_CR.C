TH1F*run(TFile*file,TString channel, TString tag,TString process,int index){
	TString hname="hist_"+process+"_"+channel+"_CR";
	TH1F*hist=new TH1F(hname,"",3,0,3);
        TH1F*h1[3];
	for(int i=0;i<3;i++){
		h1[i]=(TH1F*)file->Get(Form("shapes_fit_s/ch1_ch%i/",index)+process);
		bool flag=h1[i];
		if(flag){
			hist->SetBinContent(i+1,h1[i]->GetBinContent(1));
			hist->SetBinError(i+1,h1[i]->GetBinError(1)); 
			cout<<flag<<" "<<index<<" "<<channel<<" "<<tag<<" "<<Form("shapes_fit_s/ch1_ch%i/",index)+process<<" "<<h1[i]->GetBinContent(1)<<endl;
		}
		else{
			hist->SetBinContent(i+1,0);
			hist->SetBinError(i+1,0); 
		}
//		cout<<flag<<" "<<channel<<" "<<tag<<" "<<process<<" "<<hist->GetBinContent(i+1)<<endl;
		index++;
	}
	return hist;
}
TGraphAsymmErrors*run_data(TFile*file,TString channel, TString tag,int index){
	double x[3],x_up[3],x_down[3],y[3],y_up[3],y_down[3];
	TGraphAsymmErrors*g1[3];
	for(int i=0;i<3;i++){
		g1[i]=(TGraphAsymmErrors*)file->Get(Form("shapes_fit_s/ch1_ch%i/data",index));
		index++;
		g1[i]->GetPoint(0,x[i],y[i]);
		x[i]=0.5+i;
		x_up[i]  =g1[i]->GetErrorXhigh(0);
		x_down[i]=g1[i]->GetErrorXlow(0);
		y_up[i]  =g1[i]->GetErrorYhigh(0);
		y_down[i]=g1[i]->GetErrorYlow(0);
	}
	TGraphAsymmErrors*gr=new TGraphAsymmErrors(3,x,y,x_down,x_up,y_down,y_up);
	return gr;
}
int Draw_fit_CR(){
	vector<TString> tag={"16","17","18"};
	vector<TString> channel={"mubarrel","elebarrel","muendcap","eleendcap"};
	vector<TString> process={"ST","VV","QCD","Sig","TTA","non_prompt","total"};
	TFile*file=new TFile("./fitDiagnostics.root","r");
	TFile*fout[3];
	for(int j=0;j<tag.size();j++){
		fout[j]=new TFile("hist_fit"+tag[j]+"CR.root","recreate");
		for(int i=0;i<channel.size();i++){
			int index;
			if(channel[i].Contains("elebarrel")){
				if(tag[j].Contains("16")) index=85;
				if(tag[j].Contains("17")) index=88;
				if(tag[j].Contains("18")) index=91;
			}
			if(channel[i].Contains("eleendcap")){
				if(tag[j].Contains("16")) index=94;
				if(tag[j].Contains("17")) index=97;
				if(tag[j].Contains("18")) index=100;
			}
			if(channel[i].Contains("mubarrel")){
				if(tag[j].Contains("16")) index=103;
				if(tag[j].Contains("17")) index=106;
				if(tag[j].Contains("18")) index=109;
			}
			if(channel[i].Contains("muendcap")){
				if(tag[j].Contains("16")) index=112;
				if(tag[j].Contains("17")) index=115;
				if(tag[j].Contains("18")) index=118;
			}
			cout<<tag[j]<<" "<<channel[i]<<" "<<index<<endl;
			TH1F*h_ST        =run(file,channel[i],tag[j],"ST",index);
			TH1F*h_VV        =run(file,channel[i],tag[j],"VV",index);
			TH1F*h_QCD       =run(file,channel[i],tag[j],"QCD",index);
			TH1F*h_Sig       =run(file,channel[i],tag[j],"Sig",index);
			TH1F*h_Sig_out   =run(file,channel[i],tag[j],"Sig_out",index);
			TH1F*h_TTA       =run(file,channel[i],tag[j],"TTA",index);
			TH1F*h_non_prompt=run(file,channel[i],tag[j],"non_prompt",index);
			TH1F*h_total     =run(file,channel[i],tag[j],"total",index);
			TGraphAsymmErrors*data=run_data(file,channel[i],tag[j],index);
			fout[j]->cd();
			h_ST->Write();h_QCD->Write();h_Sig->Write();h_TTA->Write();h_non_prompt->Write();
			h_VV->Write();h_total->Write();h_Sig_out->Write();data->Write("data_"+channel[i]+"_CR");
		}
	}
	file->Close();
	return 0;
}
