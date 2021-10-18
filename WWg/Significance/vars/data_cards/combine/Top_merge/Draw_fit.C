TH1F*run(TFile*file,TString tag,TString process,int index,TString region,int num){
	TString hname="hist_"+process+"_"+tag+"_"+region;
	TH1F*hist=new TH1F(hname,"",num,0,num);
        TH1F*h1[num];
	for(int i=0;i<num;i++){
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
TGraphAsymmErrors*run_data(TFile*file,TString tag,int index,int num){
	double x[num],x_up[num],x_down[num],y[num],y_up[num],y_down[num];
	TGraphAsymmErrors*g1[num];
	for(int i=0;i<num;i++){
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
	TGraphAsymmErrors*gr=new TGraphAsymmErrors(num,x,y,x_down,x_up,y_down,y_up);
	return gr;
}
int Draw_fit(){
	vector<TString> tag={"16","17","18"};
	vector<TString>njets={"0","1","2"};
	TFile*fout;TFile*fout1;TFile*fout2;
	for(int j=1;j<tag.size();j++){
		for(int i=0;i<njets.size()-1;i++){
			TFile*file=new TFile("./fitDiagnostics"+tag[j]+"_"+njets[i]+"jets.root");
			fout=new TFile("hist_full_fit"+tag[j]+"_"+njets[i]+"jets.root","recreate");
			int index;index=1;
			cout<<tag[j]<<endl;
			TH1F*h_Top        =run(file,tag[j],"Top",index,"full",24);
			TH1F*h_VV        =run(file,tag[j],"VV",index,"full",24);
			TH1F*h_QCD       =run(file,tag[j],"VA",index,"full",24);
			TH1F*h_Sig       =run(file,tag[j],"Sig",index,"full",24);
			TH1F*h_Nonprompt_photon=run(file,tag[j],"Nonprompt_photon",index,"full",24);
			TH1F*h_Nonprompt_lepton=run(file,tag[j],"Nonprompt_lepton",index,"full",24);
			TH1F*h_total     =run(file,tag[j],"total",index,"full",24);
			TGraphAsymmErrors*data=run_data(file,tag[j],index,24);
			fout->cd();
			h_Top->Write();h_QCD->Write();h_Sig->Write();
			h_Nonprompt_photon->Write(); h_Nonprompt_lepton->Write();
			h_VV->Write();h_total->Write();data->Write("data_"+tag[j]);
			file->Close();
		}
	}
	for(int j=1;j<tag.size();j++){
		for(int i=0;i<njets.size()-1;i++){
			TFile*file=new TFile("./fitDiagnostics"+tag[j]+"_"+njets[i]+"jets.root");
			fout1=new TFile("hist_SR_fit"+tag[j]+"_"+njets[i]+"jets.root","recreate");
			int index;index=13;
			cout<<tag[j]<<endl;
			TH1F*h_Top        =run(file,tag[j],"Top",index,"SR",12);
			TH1F*h_VV        =run(file,tag[j],"VV",index,"SR",12);
			TH1F*h_QCD       =run(file,tag[j],"VA",index,"SR",12);
			TH1F*h_Sig       =run(file,tag[j],"Sig",index,"SR",12);
			TH1F*h_Nonprompt_photon=run(file,tag[j],"Nonprompt_photon",index,"SR",12);
			TH1F*h_Nonprompt_lepton=run(file,tag[j],"Nonprompt_lepton",index,"SR",12);
			TH1F*h_total     =run(file,tag[j],"total",index,"SR",12);
			TGraphAsymmErrors*data=run_data(file,tag[j],index,12);
			fout1->cd();
			h_Top->Write();h_QCD->Write();h_Sig->Write();
			h_Nonprompt_photon->Write(); h_Nonprompt_lepton->Write();
			h_VV->Write();h_total->Write();data->Write("data_"+tag[j]);
			file->Close();
		}
	}

	for(int j=1;j<tag.size();j++){
		for(int i=0;i<njets.size()-1;i++){
			TFile*file=new TFile("./fitDiagnostics"+tag[j]+"_"+njets[i]+"jets.root");
			fout2=new TFile("hist_CR_fit"+tag[j]+"_"+njets[i]+"jets.root","recreate");
			int index;index=1;
			cout<<tag[j]<<endl;
			TH1F*h_Top        =run(file,tag[j],"Top",index,"CR",12);
			TH1F*h_VV        =run(file,tag[j],"VV",index,"CR",12);
			TH1F*h_QCD       =run(file,tag[j],"VA",index,"CR",12);
			TH1F*h_Sig       =run(file,tag[j],"Sig",index,"CR",12);
			TH1F*h_Nonprompt_photon=run(file,tag[j],"Nonprompt_photon",index,"CR",12);
			TH1F*h_Nonprompt_lepton=run(file,tag[j],"Nonprompt_lepton",index,"CR",12);
			TH1F*h_total     =run(file,tag[j],"total",index,"CR",12);
			TGraphAsymmErrors*data=run_data(file,tag[j],index,12);
			fout2->cd();
			h_Top->Write();h_QCD->Write();h_Sig->Write();
			h_Nonprompt_photon->Write(); h_Nonprompt_lepton->Write();
			h_VV->Write();h_total->Write();data->Write("data_"+tag[j]);
			file->Close();
		}
	}

	return 0;
}
