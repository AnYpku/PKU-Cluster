#include "CMS_lumi.C"
#define num 103
#define n_scale 3
void cmsLumi(bool channel,TString tag);
void run(TString var, TString recovar,TString title,TString tag){
        double xs16=0,xs17=0,xs18=0;//cross section [fb] for 2016/2017/2018 EW sample 
        int num16=0,num17=0,num18=0;//the number of events for 2016/2017/2018 EW process
        if(tag.Contains("16")){
          num17=0;num18=0;
          xs16=109.7;xs17=0;xs18=0;
	  num16=884668;
	}
        if(tag.Contains("17")){
          num16=0;num18=0;
          xs16=0;xs17=114.3,xs18=0;
	  num17=799717;
	}
        if(tag.Contains("18")){
          num16=0;num17=0;
          xs16=0;xs17=0;xs18=114.3;
	  num18=879399;
	}
        if(num16==0&&num17==0&&num18==0)cout<<"error, exit!"<<endl;
	TFile*file1=new TFile("../pdf_draw/unfold_"+var+"_ewk_pdf"+tag+".root");
        TFile*file11=new TFile("../scale_draw/"+var+"_unfold_ewk_scale"+tag+".root");
	TH1D*h1[num];TH1D*h2[num];TH1D*h3[num];
        TH1D*h11[3];TH1D*h22[3];TH1D*h33[3];
        TFile*fout=new TFile("histo_"+var+"_xsec"+tag+".root","recreate");       
        for(int i=0;i<num;i++){
           if(i<3){
		   h11[i]=(TH1D*)file11->Get(var+Form("_%i",i));
	   }
           h1[i]=(TH1D*)file1->Get(var+Form("_%i",i));
	}
        const int kk=h1[0]->GetNbinsX();
	cout<<kk<<endl;
        TFile*fin=new TFile("../pdf_draw/unfold_"+var+"_ewk"+tag+".root");
        TH1D*hist_clone=(TH1D*)fin->Get(var+"_0");
        hist_clone->SetBinContent(kk,hist_clone->GetBinContent(kk)+hist_clone->GetBinContent(kk+1));
        hist_clone->SetBinError(kk,sqrt(pow(hist_clone->GetBinError(kk),2)+pow(hist_clone->GetBinError(kk+1),2)));//add overflow bin and handle the bin error
        TH1D*hin=(TH1D*)hist_clone->Clone("hin");
        double xbin[kk],ybin[kk],xerror_up[kk],xerror_down[kk],yerror_up[kk],yerror_down[kk];
	double Err_up[kk],Err_down[kk];
        double Err_sysUp[kk],Err_sysDown[kk],yerror_sysUp[kk],yerror_sysDown[kk],xerror_sysUp[kk],xerror_sysDown[kk];
        ifstream f_in;
	f_in.open("/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/scale_3NPs/combine/r_"+recovar+"_"+tag+".txt");  
        ifstream f_sys;
	f_sys.open("/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/scale_3NPs/combine/breakdown/r_sys_"+recovar+"_"+tag+".txt");  
        if(!f_in.is_open())cout<<"can not open the file "<<"/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/combine/r_"+recovar+"_"+tag+".txt"<<endl;
        if(!f_sys.is_open())cout<<"/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/combine/breakdown/r_sys_"+recovar+"_"+tag+".txt"<<endl;
	for(int i=0;i<hist_clone->GetNbinsX();i++){
                f_in>>Err_down[i]>>Err_up[i];
                f_sys>>Err_sysDown[i]>>Err_sysUp[i];
//		cout<<Err_down[i]<<" "<<Err_up[i]<<endl;
                xbin[i]=hist_clone->GetBinCenter(i+1);
                xerror_up[i]=0.5*hist_clone->GetBinWidth(i+1);
                xerror_down[i]=0.5*hist_clone->GetBinWidth(i+1);
                yerror_up[i]=Err_up[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18);
                yerror_down[i]=Err_down[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18);
		xerror_sysUp[i]=0;
		xerror_sysDown[i]=0;
                yerror_sysUp[i]=Err_sysUp[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18);
                yerror_sysDown[i]=Err_sysDown[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18);
		hist_clone->SetBinError(i+1,Err_up[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18));//handle the bin error
                cout<<"bin"<<i+1<<"; number of events "<<hist_clone->GetBinContent(i+1)<<"; nnumber of events processed "<<(num16+num17+num18)<<"; cross section "<<(xs16+xs17+xs18)<<"; normalization "<<hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)<<" "<<hist_clone->GetBinError(i+1)<<endl;
                hist_clone->SetBinContent(i+1,hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18));//scale the bincontent to cross section
                ybin[i]=hist_clone->GetBinContent(i+1);
//                cout<<xbin[i]<<" "<<ybin[i]<<" "<<yerror_up[i]<<" "<< yerror_down[i]<<endl;
                cout<<var<<tag<<" stat+sys "<<yerror_up[i]<<" "<< yerror_down[i]<<endl;
                cout<<var<<tag<<" sys "<<yerror_sysUp[i]<<" "<<yerror_sysDown[i]<<endl;
	}// expected 
//        cout<<"before scale "<<h1[0]->GetBinContent(1)<<" "<<h1[0]->GetBinError(1)<<endl;
	for(int i=0;i<num;i++){
		h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
                h1[i]->SetBinError(kk,sqrt(pow(h1[i]->GetBinError(kk),2)+pow(h1[i]->GetBinError(kk+1),2)));
		//add overflow for pdf and handle the bin error
		if(i<3){
			h11[i]->SetBinContent(kk,h11[i]->GetBinContent(kk)+h11[i]->GetBinContent(kk+1));
			h11[i]->SetBinError(kk,sqrt(pow(h11[i]->GetBinError(kk),2)+pow(h11[i]->GetBinError(kk+1),2)));
			//add overflow for scale and handle the bin error
		}
		for(int j=0;j<kk;j++){
                   h1[i]->SetBinContent(j+1,h1[i]->GetBinContent(j+1)/(num16+num17+num18)*(xs16+xs17+xs18));
                   h1[i]->SetBinError(j+1,h1[i]->GetBinError(j+1)/(num16+num17+num18)*(xs16+xs17+xs18));
                   // scale yields to cross section for pdf and handle the bin error
                   if(i<3){
			   h11[i]->SetBinContent(j+1,h11[i]->GetBinContent(j+1)/(num16+num17+num18)*(xs16+xs17+xs18));
			   h11[i]->SetBinError(j+1,h11[i]->GetBinError(j+1)/(num16+num17+num18)*(xs16+xs17+xs18));
			   // scale yields to cross section for scale and handle the bin error
		   }
		}
	}
//        cout<<"after scale "<<h1[0]->GetBinContent(1)<<" "<<h1[0]->GetBinError(1)<<endl;
	hist_clone->SetLineColor(1);
        TGraphAsymmErrors* gr = new TGraphAsymmErrors(kk, xbin, ybin, xerror_down,xerror_up, yerror_down, yerror_up);
        TGraphAsymmErrors* gr_sys = new TGraphAsymmErrors(kk, xbin, ybin, xerror_sysDown,xerror_sysUp, yerror_sysDown, yerror_sysUp);
        for(int i=0;i<hin->GetNbinsX();i++){
             hin->SetBinContent(i+1,ybin[i]/1000);
             hin->SetBinError(i+1,yerror_up[i]/1000);
	}
	hin->SetBinContent(hin->GetNbinsX()+1,0);
	TCanvas*c1=new TCanvas("c0","reco && gen",800,600);
	c1->cd();
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
	TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
	fPads1->SetBottomMargin(0);
	fPads2->SetTopMargin(0);
	fPads2->SetBottomMargin(0.3);
	fPads2->Draw();
	fPads1->Draw();
        fPads1->SetTicky();
        fPads1->SetTickx();
	fPads1->SetLogy();
	if(tag.Contains("16"))CMS_lumi(fPads1, 4, 0, "35.86");
	else if(tag.Contains("17"))CMS_lumi(fPads1, 4, 0, "41.52");
	else if(tag.Contains("18"))CMS_lumi(fPads1, 4, 0, "59.7");
	fPads1->cd();
//        cout<<"minimum "<<h1[0]->GetMinimum()<<endl; 
	hist_clone->SetTitle("");
        if(var.Contains("Mjj")==0)
                hist_clone->GetYaxis()->SetTitle("#sigma_{fid} [fb]");
        else
                hist_clone->GetYaxis()->SetTitle("#sigma_{fid} [fb]");
	hist_clone->GetYaxis()->SetTitleOffset(0.45);
	hist_clone->GetYaxis()->SetTitleSize(0.10);
	hist_clone->GetYaxis()->SetRangeUser(hist_clone->GetMinimum()*0.2,hist_clone->GetMaximum()*35);
        const char *name[7]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~2000"};
        if(var.Contains("Mjj")==1) {for(int i=0;i<hist_clone->GetNbinsX();i++){hist_clone->GetXaxis()->SetBinLabel(i+1,name[i]);}}
	hist_clone->SetLineStyle(1);
	hist_clone->SetLineColor(kRed-7);
	hist_clone->SetLineWidth(3);
        hist_clone->SetFillStyle(3002);
        hist_clone->SetFillColor(kRed-7);
	TH1D * upper =(TH1D*) h1[0]->Clone("upper");
	TH1D * lower =(TH1D*) h1[0]->Clone("lower");
	upper->Reset();
	lower->Reset();
	for(int j=1;j<=h1[0]->GetNbinsX();j++){
		double n = h1[0]->GetBinContent(j);
		double err2Up=0, /* pow(h1[0]->GetBinError(j),2)*/ err2Dn =0;// pow(h1[0]->GetBinError(j),2);
                double err_scale=0;
		for(int k=0;k<num;k++){
			double content= h1[k]->GetBinContent(j);
			double err = content - n;
			err2Up+=pow(err,2);
			err2Dn+=pow(err,2);
		}
		err_scale=fabs(h11[1]->GetBinContent(j)-h11[2]->GetBinContent(j))/2;
//		cout<<"sys pdf "<<sqrt(err2Up/(num-1))<<"; stat+sys(pdf)"<<sqrt(err2Up/(num-1)+pow(h1[0]->GetBinError(j),2))<<endl;
		err2Up=err2Up/(num-1)+pow(h1[0]->GetBinError(j),2)+pow(err_scale,2); 
		err2Dn=err2Dn/(num-1)+pow(h1[0]->GetBinError(j),2)+pow(err_scale,2); 
		//cout<<sqrt(err2Dn/num+pow(h1[0]->GetBinError(j),2))<<endl;
		//cout<<n+sqrt(err2Up/num)<<endl;
		//cout<<nominal->GetBinContent(j)<<endl;
		upper->SetBinContent(j,n+sqrt(err2Up));
		lower->SetBinContent(j,n-sqrt(err2Dn));
                hist_clone->SetBinError(j,sqrt(err2Up));
	}
        hist_clone->GetYaxis()->SetLabelSize(0.07);
        hist_clone->SetMarkerSize(0);
	hist_clone->Draw("E2");
//        cout<<"Uncertainty of data "<<hist_clone->GetBinError(1)<<endl;

	TLegend*l1=new TLegend(0.45,0.5,0.88,0.88);
	TLegend*l2=new TLegend(0.2,0.5,0.5,0.88);
	l1->AddEntry(hist_clone,"EW Z#gamma MadGraph");
	l1->AddEntry(gr,"Expected result (stat.#oplus syst.)");
	l1->AddEntry(gr_sys,"systematic uncertainty");
        l1->SetTextSize(0.065);
        l1->SetLineColor(0);
        l2->SetLineColor(0);

        gr->SetMarkerColor(1);
        gr->SetMarkerStyle(20);
        gr->SetFillColor(0);
	gr->SetMarkerSize(1);
        gr->SetLineColor(1);
	for(int i=0;i<kk;i++){
//		cout<<gr->GetErrorYhigh(i)<<endl;
	}
        gr->Draw("P SAME");
        gr_sys->SetLineColor(2);
        gr_sys->SetLineWidth(4);
        gr_sys->SetLineStyle(2);
        gr_sys->SetFillColor(0);
        gr_sys->SetMarkerSize(0);
        gr_sys->Draw("P SAME");
/*	for(int i=0;i<num;i++){
		if(i!=0){
			h1[i]->SetLineColor(kBlue);
			h1[i]->SetLineStyle(3);
			h1[i]->SetLineWidth(1);
			h1[i]->Draw("same hist error");
		}
	}
	l1->AddEntry(h1[1],"p_{T}^{gen} pdf weight");
	l1->AddEntry(hist_clone,"#pm #Delta r");*/
	l1->Draw();
//	l2->Draw();
	cmsLumi(0,tag);
	fPads1->Update();
	fPads2->cd();
//        fPads2->SetGridy();
        fPads2->SetTicky();
        fPads2->SetTickx();
	/*for(int i=0;i<upper->GetNbinsX();i++){
		cout<<upper->GetBinContent(i+1)<<" "<<lower->GetBinContent(i+1)<<endl;

	}*///check the bincontent
	TH1D*nominal=(TH1D*)hist_clone->Clone("nominal");
	TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
	for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
	nominal->Divide(nomNoErr);
	upper->Divide(nominal);
	lower->Divide(nominal);
	cout<<"check the stat uncertainty "<<hist_clone->GetBinError(1)/hist_clone->GetBinContent(1)<<" "<<nominal->GetBinError(1)<<endl;
	nominal->SetFillStyle(3002);
	nominal->SetFillColor(kRed-7);
	nominal->SetLineColor(kRed-7);
	const int m=upper->GetNbinsX();
	nominal->SetTitle("");
	nominal->GetXaxis()->SetLabelSize(0.1);
	nominal->GetXaxis()->SetTitleSize(0.15);
	nominal->GetXaxis()->SetTitleOffset(0.8);
	nominal->GetXaxis()->SetTitleFont(32);
	nominal->GetXaxis()->SetTitle(title);
	nominal->GetYaxis()->SetTitle("Ratio to MG");
	nominal->GetYaxis()->SetTitleOffset(0.45);
	nominal->GetYaxis()->SetTitleFont(32);
	nominal->GetYaxis()->SetTitleSize(0.08);
	nominal->GetYaxis()->SetLabelSize(0.07);
	TLine*line=new TLine(nominal->GetXaxis()->GetXmin(),1,nominal->GetXaxis()->GetXmax(),1);
	TLine*line1=new TLine(nominal->GetXaxis()->GetXmin(),1.5,nominal->GetXaxis()->GetXmax(),1.5);
	TLine*line2=new TLine(nominal->GetXaxis()->GetXmin(),0.5,nominal->GetXaxis()->GetXmax(),0.5);
	line->SetLineColor(kRed-7);
	line->SetLineWidth(3);
        line1->SetLineStyle(2);
        line2->SetLineStyle(2);
	cout<<"check expected data uncertainty "<<endl;
        TH1D*hist_nominal=(TH1D*)hist_clone->Clone();
	for(int i=0;i<hist_clone->GetNbinsX();i++){
		cout<<hist_clone->GetBinError(i+1)<<" "<<hist_clone->GetBinError(i+1)/nomNoErr->GetBinContent(i+1)<<endl;
	}
	hist_nominal->Divide(nomNoErr);
        double y_ratio[kk],yerror_down_ratio[kk],yerror_up_ratio[kk];
        vector<double> ye_h,ye_l;
	for(int i=0;i<hist_clone->GetNbinsX();i++){
//		cout<<hist_nominal->GetBinError(i+1)<<endl;
                 y_ratio[i]=ybin[i]/nomNoErr->GetBinContent(i+1);
                 yerror_down_ratio[i]=yerror_down[i]/nomNoErr->GetBinContent(i+1);
                 yerror_up_ratio[i]=yerror_up[i]/nomNoErr->GetBinContent(i+1);
                 cout<<y_ratio[i]<<" "<< yerror_down_ratio[i]<<" "<<yerror_up_ratio[i]<<" "<<hist_nominal->GetBinError(i+1)<<endl;
                 ye_h.push_back(yerror_up_ratio[i]); 
                 ye_l.push_back(yerror_down_ratio[i]); 
	}
	TGraphAsymmErrors* gr1 = new TGraphAsymmErrors(kk, xbin, y_ratio, xerror_down,xerror_up, yerror_down_ratio, yerror_up_ratio);
        hist_nominal->SetMarkerStyle(20);
        hist_nominal->SetMarkerColor(1);
        hist_nominal->SetLineColor(1);
        gr1->SetMarkerColor(1);
        gr1->SetMarkerStyle(20);
        gr1->SetMarkerSize(1);
        gr1->SetLineColor(1);
	sort(ye_h.begin(), ye_h.end(), greater<double>());
	sort(ye_l.begin(), ye_l.end(), greater<double>());
	nominal->GetYaxis()->SetRangeUser(1-ye_l[0]-0.3,1+ye_h[0]+0.3);
        ye_h.clear();ye_l.clear();
	nominal->Draw("E2");
	gr1->Draw("P SAME");
//        hist_nominal->Draw("EP same");
	/*for(int i=0;i<hist_clone->GetNbinsX();i++){
		cout<<"check the expected data uncertainty "<<hist_clone->GetBinError(i+1)/hist_clone->GetBinContent(i+1)<<" "<<hist_nominal->GetBinError(i+1)<<" "<<hist_clone->GetBinError(i+1)<<endl;
	}*/
//	upper->Draw("same hist ][");
//	lower->Draw("same hist ][");
	line->Draw();
	line1->Draw();
	line2->Draw();
	fPads2->Update();
	fPads1->cd();
//	l2->AddEntry(nominal,"Stat","f");
//	l2->AddEntry(upper,"Sys+Stat","f");
//	l2->Draw();
	fPads1->Update();
	c1->Print(var+"_unfold_xsec"+tag+".pdf");
        fout->cd();
        hin->Write();
        fout->Close();
}
int Draw_xsec(){
	gStyle->SetOptStat(0);
	vector<TString> title={"leading p_{T}^{lep}","leading p_{T}^{#gamma}","leading p_{T}^{j}","m_{jj}"};
	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
//	vector<TString> genvars={"genMjj"};
//	vector<TString> recovars={"Mjj"};
//	vector<TString> title={"m_{jj}"};
	for(int i=0;i<genvars.size();i++){
		run(genvars[i],recovars[i],title[i],"16");
		run(genvars[i],recovars[i],title[i],"17");
		run(genvars[i],recovars[i],title[i],"18");
	}
	return 0;

}
void cmsLumi(bool channel,TString tag)
{
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.05);
	latex.SetLineWidth(2);
	float lumiel=136.1;
	float lumimu=136.1;
	int beamcomenergytev=13;
	latex.SetTextAlign(31);
	latex.SetTextAlign(11);
	latex.DrawLatex(0.18,0.82,"Preliminary");
	latex.DrawLatex(0.18,0.86,"CMS");
	latex.SetTextSize(0.05);
	if(tag.Contains("16"))latex.DrawLatex(0.76,0.92,Form("35.86 fb^{-1} (%d TeV)", (beamcomenergytev)));
	else if(tag.Contains("17"))latex.DrawLatex(0.76,0.92,Form("41.52 fb^{-1} (%d TeV)", (beamcomenergytev)));
	else if(tag.Contains("18"))latex.DrawLatex(0.76,0.92,Form("59.7 fb^{-1} (%d TeV)", (beamcomenergytev)));
}
