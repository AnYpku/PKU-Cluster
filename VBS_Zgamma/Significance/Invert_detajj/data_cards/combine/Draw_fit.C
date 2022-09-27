TH1F*run(TFile*file, TString tag,TString process,int index){
	TString hname="hist_"+process;
	TH1F*hist=new TH1F(hname,"",3,0,3);
        TH1F*h1[3];
	for(int i=0;i<3;i++){
		h1[i]=(TH1F*)file->Get(Form("shapes_prefit/ch1_ch%i/",index)+process);
		bool flag=h1[i];
		if(flag){
			hist->SetBinContent(i+1,h1[i]->GetBinContent(1));
			hist->SetBinError(i+1,h1[i]->GetBinError(1)); 
			cout<<flag<<" "<<index<<" "<<" "<<tag<<" "<<Form("shapes_prefit/ch1_ch%i/",index)+process<<" "<<h1[i]->GetBinContent(1)<<endl;
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
TGraphAsymmErrors*run_data(TFile*file, TString tag,int index){
	double x[3],x_up[3],x_down[3],y[3],y_up[3],y_down[3];
	TGraphAsymmErrors*g1[3];
	for(int i=0;i<3;i++){
		g1[i]=(TGraphAsymmErrors*)file->Get(Form("shapes_prefit/ch1_ch%i/data",index));
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
int Draw_fit(){
	vector<TString> tag={"16","17","18"};
	vector<TString> channel={"mubarrel","elebarrel","muendcap","eleendcap"};
	vector<TString> process={"ST","VV","QCD","Sig","TTA","non_prompt","total"};
	TFile*file=new TFile("./fitDiagnostics.root","r");
	TFile*fout[3];
	for(int j=0;j<tag.size();j++){
		fout[j]=new TFile("hist_fit"+tag[j]+".root","recreate");
		int index;
		if(tag[j].Contains("16")) index=1;
		if(tag[j].Contains("17")) index=4;
		if(tag[j].Contains("18")) index=7;
		cout<<tag[j]<<" "<<" "<<index<<endl;
		TH1F*h_ST        =run(file,tag[j],"ST",index);
		TH1F*h_VV        =run(file,tag[j],"VV",index);
		TH1F*h_QCD       =run(file,tag[j],"QCD",index);
		TH1F*h_Sig       =run(file,tag[j],"Sig",index);
		TH1F*h_TTA       =run(file,tag[j],"TTA",index);
		TH1F*h_non_prompt=run(file,tag[j],"non_prompt",index);
		TH1F*h_total     =run(file,tag[j],"total",index);
		TGraphAsymmErrors*data=run_data(file,tag[j],index);
		fout[j]->cd();
		h_ST->Write();h_QCD->Write();h_Sig->Write();h_TTA->Write();h_non_prompt->Write();
		h_VV->Write();h_total->Write();data->Write("data_"+tag[j]);
	}
	file->Close();
	return 0;
}
