TH1F*run(TFile*file,TString tag,TString process,int index){
	TString hname="hist_"+process+"_"+tag;
	TH1F*hist=new TH1F(hname,"",16,0,16);
        TH1F*h1[16];
	for(int i=0;i<16;i++){
		h1[i]=(TH1F*)file->Get(Form("shapes_prefit/ch%i/",index)+process);
		bool flag=h1[i];
                cout<<Form("shapes_prefit/ch%i/",index)+process<<" "<<flag<<endl;
		if(flag){
			hist->SetBinContent(i+1,h1[i]->GetBinContent(1));
			hist->SetBinError(i+1,h1[i]->GetBinError(1)); 
			cout<<flag<<" "<<index<<" "<<" "<<tag<<" "<<Form("shapes_prefit/ch%i/",index)+process<<" "<<h1[i]->GetBinContent(1)<<endl;
		}
		else{
			hist->SetBinContent(i+1,0);
			hist->SetBinError(i+1,0); 
		}
		index++;
	}
        cout<<"finish "<<process<<endl;
	return hist;
}
TGraphAsymmErrors*run_data(TFile*file,TString tag,int index){
	double x[16],x_up[16],x_down[16],y[16],y_up[16],y_down[16];
	TGraphAsymmErrors*g1[16];
	for(int i=0;i<16;i++){
		g1[i]=(TGraphAsymmErrors*)file->Get(Form("shapes_prefit/ch%i/data",index));
		cout<<i<<" "<<Form("shapes_prefit/ch%i/data",index)<<endl;
		index++;
		g1[i]->GetPoint(0,x[i],y[i]);
		x[i]=0.5+i;
		x_up[i]  =g1[i]->GetErrorXhigh(0);
		x_down[i]=g1[i]->GetErrorXlow(0);
		y_up[i]  =g1[i]->GetErrorYhigh(0);
		y_down[i]=g1[i]->GetErrorYlow(0);
	}
	TGraphAsymmErrors*gr=new TGraphAsymmErrors(16,x,y,x_down,x_up,y_down,y_up);
	return gr;
}
int Draw_fit(){
	vector<TString> tag={"16","17","18"};
	TFile*file=new TFile("./fitDiagnostics18.root");
	TFile*fout;
	for(int j=2;j<tag.size();j++){
		fout=new TFile("hist_fit"+tag[j]+".root","recreate");
		int index;index=1;
                cout<<tag[j]<<endl;
		TH1F*h_ST        =run(file,tag[j],"ST",index);
		TH1F*h_VV        =run(file,tag[j],"VV",index);
		TH1F*h_QCD       =run(file,tag[j],"VA",index);
		TH1F*h_Sig       =run(file,tag[j],"Sig",index);
		TH1F*h_TTA       =run(file,tag[j],"TTA",index);
		TH1F*h_Nonprompt_photon=run(file,tag[j],"Nonprompt_photon",index);
		TH1F*h_Nonprompt_lepton=run(file,tag[j],"Nonprompt_lepton",index);
		TH1F*h_total     =run(file,tag[j],"total",index);
		TGraphAsymmErrors*data=run_data(file,tag[j],index);
		fout->cd();
		h_ST->Write();h_QCD->Write();h_Sig->Write();h_TTA->Write();
		h_Nonprompt_photon->Write(); h_Nonprompt_lepton->Write();
		h_VV->Write();h_total->Write();data->Write("data_"+tag[j]);
	}
	file->Close();
	return 0;
}
