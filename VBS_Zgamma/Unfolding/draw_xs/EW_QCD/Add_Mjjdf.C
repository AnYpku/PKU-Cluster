#include "CMS_lumi.C"
#define num 103
#define n_scale 3
void cmsLumi(bool channel);
void run(TString var, TString recovar, TString title,TString tag){
        double xs16=114.3+55.49*1000,xs17=114.3+55.49*1000,xs18=114.3+55.49*1000;//cross section [fb] for 2016/2017/2018 EW sample 
        int num16,num17,num18;//the number of events for 2016/2017/2018 EW process
        num16=884668+30040390;num17=799717+30482963;num18=879399+33805459;
        TFile*file1=new TFile("../../pdf_draw/unfold_"+var+"_qcd_pdf16.root");
        TFile*file11=new TFile("../../scale_draw/"+var+"_unfold_qcd_scale16.root");
        TFile*file22=new TFile("../../scale_draw/"+var+"_unfold_qcd_scale17.root");
        TFile*file33=new TFile("../../scale_draw/"+var+"_unfold_qcd_scale18.root");

        TFile*file4=new TFile("../../pdf_draw/unfold_"+var+"_ewk_pdf16.root");
        TFile*file5=new TFile("../../pdf_draw/unfold_"+var+"_ewk_pdf16.root");
        TFile*file6=new TFile("../../pdf_draw/unfold_"+var+"_ewk_pdf16.root");
        TFile*file44=new TFile("../../scale_draw/"+var+"_unfold_ewk_scale16.root");
        TFile*file55=new TFile("../../scale_draw/"+var+"_unfold_ewk_scale17.root");
        TFile*file66=new TFile("../../scale_draw/"+var+"_unfold_ewk_scale18.root");

        TFile*f1=new TFile("../../pdf_draw/unfold_"+var+"_ewk16.root");
        TFile*f2=new TFile("../../pdf_draw/unfold_"+var+"_ewk17.root");
        TFile*f3=new TFile("../../pdf_draw/unfold_"+var+"_ewk18.root");
        TFile*f11=new TFile("../../pdf_draw/unfold_"+var+"_qcd16.root");
        TFile*f22=new TFile("../../pdf_draw/unfold_"+var+"_qcd17.root");
        TFile*f33=new TFile("../../pdf_draw/unfold_"+var+"_qcd18.root");
        TH1D*h1[num];TH1D*h2[num];TH1D*h3[num];//qcd pdf
        TH1D*h11[9];TH1D*h22[9];TH1D*h33[9];//qcd scale
        TH1D*h4[num];TH1D*h5[num];TH1D*h6[num];//ewk pdf
        TH1D*h44[3];TH1D*h55[3];TH1D*h66[3];//ewk scale

        for(int i=0;i<num;i++){
           if(i<9){
                   h11[i]=(TH1D*)file11->Get(var+Form("_%i",i));
                   if(i!=0)h11[i]->Scale(2);
                   h22[i]=(TH1D*)file22->Get(var+Form("_%i",i));
                   h33[i]=(TH1D*)file33->Get(var+Form("_%i",i));
                   h11[i]->Add(h22[i],1); h11[i]->Add(h33[i],1);
                   cout<<i<<" get three year qcd scale histos"<<endl;
                   if(i<3){
                           h44[i]=(TH1D*)file44->Get(var+Form("_%i",i));
                           h55[i]=(TH1D*)file55->Get(var+Form("_%i",i));
                           h66[i]=(TH1D*)file66->Get(var+Form("_%i",i));
                           h44[i]->Add(h55[i],1);h44[i]->Add(h66[i],1);
                           cout<<i<<" get three year ewk scale histos"<<endl;
                   }
                        if(i==0||i==3||i==6) h11[i]->Add(h44[0]);
                        if(i==1||i==4)       h11[i]->Add(h44[1]);
                        if(i==2||i==8)       h11[i]->Add(h44[2]);
                        cout<<i<<" get three year ewk+qcd scale histos"<<endl;
           }
           h1[i]=(TH1D*)file1->Get(var+Form("_%i",i));
           h4[i]=(TH1D*)file4->Get(var+Form("_%i",i));
           h5[i]=(TH1D*)file5->Get(var+Form("_%i",i));
           h6[i]=(TH1D*)file6->Get(var+Form("_%i",i));
           h1[i]->Add(h4[i],1);h1[i]->Add(h5[i],1);h1[i]->Add(h6[i],1);
        }
        const int kk=h1[0]->GetNbinsX();
        TH1D*hist_clone=(TH1D*)f1->Get(var+"_0");
        TH1D*hist_clone2=(TH1D*)f2->Get(var+"_0");
        TH1D*hist_clone3=(TH1D*)f3->Get(var+"_0");
        TH1D*hist_clone11=(TH1D*)f11->Get(var+"_0");
        TH1D*hist_clone22=(TH1D*)f22->Get(var+"_0");
        TH1D*hist_clone33=(TH1D*)f33->Get(var+"_0");
        hist_clone->Add(hist_clone2,1);hist_clone->Add(hist_clone3,1);
        hist_clone->Add(hist_clone11,1);hist_clone->Add(hist_clone22,1);hist_clone->Add(hist_clone33,1);
        double BinWidth[7];
        double binwidth[7]={300,400,800,300,400,800,1500};
        for(int i=0;i<kk;i++){
                BinWidth[i]=binwidth[i];
        }
        hist_clone->SetBinContent(kk,hist_clone->GetBinContent(kk)+hist_clone->GetBinContent(kk+1));
        hist_clone->SetBinError(kk,sqrt(pow(hist_clone->GetBinError(kk),2)+pow(hist_clone->GetBinError(kk+1),2)));//add overflow bin
        double xbin[kk],ybin[kk],xerror_up[kk],xerror_down[kk],yerror_up[kk],yerror_down[kk];
        double Err_up[kk],Err_down[kk];
        double Err_sysUp[kk],Err_sysDown[kk],yerror_sysUp[kk],yerror_sysDown[kk],xerror_sysUp[kk],xerror_sysDown[kk];
        ifstream f_in("/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/EW_QCD/combine/r_"+recovar+"_"+tag+".txt");
        ifstream f_sys("/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/EW_QCD/combine/breakdown/r_sys_"+recovar+"_"+tag+".txt");
        if(!f_in.is_open())cout<<"can not open the file "<<"/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/EW_QCD/combine/r_"+recovar+"_"+tag+".txt"<<endl;
        if(!f_sys.is_open())cout<<"/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/EW_QCD/combine/breakdown/r_sys_"+recovar+"_"+tag+".txt"<<endl;

	for(int i=0;i<hist_clone->GetNbinsX();i++){
                f_in>>Err_down[i]>>Err_up[i];
                f_sys>>Err_sysDown[i]>>Err_sysUp[i];
                xbin[i]=hist_clone->GetBinCenter(i+1);
                xerror_up[i]=0.5*hist_clone->GetBinWidth(i+1);
                xerror_down[i]=0.5*hist_clone->GetBinWidth(i+1);
                yerror_up[i]=Err_up[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3;
                yerror_up[i]=yerror_up[i]/BinWidth[i];
                yerror_down[i]=Err_down[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3;
                yerror_down[i]=yerror_down[i]/BinWidth[i];
                xerror_sysUp[i]=0;
                xerror_sysDown[i]=0;
                yerror_sysUp[i]=Err_sysUp[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3;
		yerror_sysUp[i]=yerror_sysUp[i]/BinWidth[i];
                yerror_sysDown[i]=Err_sysDown[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3;
                yerror_sysDown[i]=yerror_sysDown[i]/BinWidth[i];
		hist_clone->SetBinError(i+1,Err_up[i]*hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3);//handle the bin error
               cout<<"bin"<<i+1<<"; number of events "<<hist_clone->GetBinContent(i+1)<<"; nnumber of events processed "<<(num16+num17+num18)<<"; cross section "<<(xs16+xs17+xs18)/3<<"; xs in bin"<<i+1<<" "<<hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3<<endl;
                hist_clone->SetBinContent(i+1,hist_clone->GetBinContent(i+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3);
		ybin[i]=hist_clone->GetBinContent(i+1);
                ybin[i]=ybin[i]/BinWidth[i];
//                cout<<xbin[i]<<" "<<ybin[i]<<" "<<yerror_up[i]<<" "<< yerror_down[i]<<endl; 
	}// expected 
//        cout<<"before scale "<<hist_clone->GetBinContent(1)<<" "<<hist_clone->GetBinError(1)<<endl;
	for(int i=0;i<num;i++){
		h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
		if(i<9){
			h11[i]->SetBinContent(kk,h11[i]->GetBinContent(kk)+h11[i]->GetBinContent(kk+1));
		}
		for(int j=0;j<kk;j++){
                   h1[i]->SetBinContent(j+1,h1[i]->GetBinContent(j+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3);
                   h1[i]->SetBinError(j+1,h1[i]->GetBinError(j+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3);
                   // scale yields to cross section for pdf 
                   if(i<9){
			   h11[i]->SetBinContent(j+1,h11[i]->GetBinContent(j+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3);
			   h11[i]->SetBinError(j+1,h11[i]->GetBinError(j+1)/(num16+num17+num18)*(xs16+xs17+xs18)/3);
			   // scale yields to cross section for scale
		   }
		}
	}
//        cout<<"after scale "<<hist_clone->GetBinContent(1)<<" "<<hist_clone->GetBinError(1)<<endl;
	hist_clone->SetLineColor(1);
        TGraphAsymmErrors* gr = new TGraphAsymmErrors(kk, xbin, ybin, xerror_down,xerror_up, yerror_down, yerror_up);
        TGraphAsymmErrors* gr_sys = new TGraphAsymmErrors(kk, xbin, ybin, xerror_sysDown,xerror_sysUp, yerror_sysDown, yerror_sysUp);
	TCanvas*c1=new TCanvas("c0","reco && gen",800,600);
	c1->cd();
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
	TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
	fPads1->SetBottomMargin(0);
	fPads2->SetTopMargin(0);
	fPads2->SetBottomMargin(0.5);
	fPads2->Draw();
	fPads1->Draw();
	fPads1->cd();
        fPads1->SetTicky();
        fPads1->SetTickx();
        fPads1->SetLogy();
        hist_clone->SetTitle("");
        if(var.Contains("Mjj")==0)
                hist_clone->GetYaxis()->SetTitle("d#sigma/dp_{T} [fb/GeV]");
        else
                hist_clone->GetYaxis()->SetTitle("d#sigma/dm [fb/GeV]");
        hist_clone->GetYaxis()->SetTitleOffset(0.45);
        hist_clone->GetYaxis()->SetTitleSize(0.10);
	hist_clone->SetLineStyle(1);
	hist_clone->SetLineColor(kRed-7);
	hist_clone->SetLineWidth(3);
        hist_clone->SetFillStyle(3002);
        hist_clone->SetFillColor(kRed-7);
	TH1D * upper =(TH1D*) h1[0]->Clone("upper");
	TH1D * lower =(TH1D*) h1[0]->Clone("lower");
	upper->Reset();
	lower->Reset();
        vector<double> vec_content;
        vector<Double_t>:: iterator biggest;
        vector<Double_t>:: iterator smallest;
	for(int j=1;j<=h1[0]->GetNbinsX();j++){
		double n = h1[0]->GetBinContent(j);
		double err2Up=0, /* pow(h1[0]->GetBinError(j),2)*/ err2Dn =0;// pow(h1[0]->GetBinError(j),2);
                double err_scale=0;
		for(int k=0;k<num;k++){
			double content= h1[k]->GetBinContent(j);
			double err = content - n;
			err2Up+=pow(err,2);
			err2Dn+=pow(err,2);
                        if(k<9){
                                if(!(k==5||k==7))
                                vec_content.push_back(h11[k]->GetBinContent(j));
                        }
		}
                biggest = max_element(begin(vec_content),end(vec_content));
                smallest= min_element(begin(vec_content),end(vec_content));
                err_scale=(*biggest - *smallest)/2;
                vec_content.clear();
                cout<<"bin"<<j<<" theoretical unc."<<sqrt(err2Up/(num-1))<<endl;
		err2Up=err2Up/(num-1)+pow(h1[0]->GetBinError(j),2)+pow(err_scale,2); 
		err2Dn=err2Dn/(num-1)+pow(h1[0]->GetBinError(j),2)+pow(err_scale,2); 
		//cout<<sqrt(err2Dn/num+pow(h1[0]->GetBinError(j),2))<<endl;
		//cout<<n+sqrt(err2Up/num)<<endl;
		//cout<<nominal->GetBinContent(j)<<endl;
		upper->SetBinContent(j,n+sqrt(err2Up));
		lower->SetBinContent(j,n-sqrt(err2Dn));
		hist_clone->SetBinContent(j,hist_clone->GetBinContent(j)/BinWidth[j-1]);
                hist_clone->SetBinError(j,sqrt(err2Up)/BinWidth[j-1]);
                cout<<"bin"<<j<<" MadGraph(stat included) info, scale to binwidth("<<BinWidth[j-1]<<") bin error "<<hist_clone->GetBinError(j)<<"; bin content "<<hist_clone->GetBinContent(j)<<endl;
	}
        hist_clone->GetYaxis()->SetRangeUser(hist_clone->GetMinimum()*0.2,hist_clone->GetMaximum()*35);
        hist_clone->GetYaxis()->SetLabelSize(0.05);
        hist_clone->SetMarkerSize(0);
//	const char *name[7]={"500~800","800~1200","1200~2000","500~800","800~1200","1200~2000","500~2000"};
	const char *name[7]={"0.5~0.8","8~1.2","1.2~2","0.5~0.8","8~1.2","1.2~2","0.5~2"};
        if(var.Contains("Mjj")==1) {for(int i=0;i<hist_clone->GetNbinsX();i++){hist_clone->GetXaxis()->SetBinLabel(i+1,name[i]);}}
	hist_clone->Draw("E2");

        TLegend*l1=new TLegend(0.45,0.5,0.72,0.88);
        TLegend*l2=new TLegend(0.2,0.5,0.5,0.88);
        l1->AddEntry(hist_clone,"Z#gamma MadGraph");
        l1->AddEntry(gr,"Expected result (stat.#oplus syst.)");
        l1->AddEntry(gr_sys,"systematic uncertainty");
        l1->SetTextSize(0.065);
        l1->SetLineColor(0);
        l1->SetFillColor(0);
        gr->SetMarkerColor(1);
        gr->SetMarkerStyle(20);
        gr->SetFillColor(0);
        gr->SetMarkerSize(1);
        gr->SetLineColor(1);
        gr->Draw("P SAME");
        gr_sys->SetLineColor(2);
        gr_sys->SetLineWidth(4);
        gr_sys->SetLineStyle(2);
        gr_sys->SetMarkerSize(0);
        gr_sys->SetMarkerSize(0);
        gr_sys->Draw("P SAME");

        double max=hist_clone->GetMaximum();
        TLine* vline1 = new TLine(hist_clone->GetBinLowEdge(4),0,hist_clone->GetBinLowEdge(4),max*1.);
        TLine* vline2 = new TLine(hist_clone->GetBinLowEdge(7),0,hist_clone->GetBinLowEdge(7),max*1.);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline1->Draw();
        vline2->Draw();
	l1->Draw();

        CMS_lumi(fPads1, 4,0, "137.1");
        TLatex latex;
        latex.SetTextSize(0.065);
        latex.SetLineWidth(2);
        latex.DrawLatex(1.2,0.002,"2.5<|#Delta#eta_{jj}|<4.5");
        latex.DrawLatex(4.2,0.002,"4.5<|#Delta#eta_{jj}|<6");
        latex.DrawLatex(6.1,0.018,"|#Delta#eta_{jj}|>6");

//	cmsLumi(0);
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
        cout<<"consistency of stat uncertainty check for 1st bin "<<hist_clone->GetBinError(1)/hist_clone->GetBinContent(1)<<" "<<nominal->GetBinError(1)<<endl;
	nominal->SetFillStyle(3002);
	nominal->SetFillColor(kRed-7);
	nominal->SetLineColor(0);
	const int m=upper->GetNbinsX();
	nominal->GetYaxis()->SetRangeUser(-0.5,2);
	nominal->SetTitle("");
	nominal->GetXaxis()->SetLabelSize(0.2);
	nominal->GetXaxis()->SetTitleSize(0.2);
        nominal->GetXaxis()->SetLabelOffset(0.03);
        nominal->GetXaxis()->SetTitleOffset(1);
        nominal->GetXaxis()->SetTitleFont(22);
	nominal->GetXaxis()->SetTitle(title+" [TeV]");
	nominal->GetYaxis()->SetTitle("Ratio to MG");
//        nominal->GetYaxis()->SetTitleFont(22);
        nominal->GetYaxis()->SetNdivisions(404);
	nominal->GetYaxis()->SetTitleOffset(0.25);
	nominal->GetYaxis()->SetTitleSize(0.13);
	nominal->GetYaxis()->SetLabelSize(0.13);
	TLine*line=new TLine(nominal->GetXaxis()->GetXmin(),1,nominal->GetXaxis()->GetXmax(),1);
        TLine*line1=new TLine(nominal->GetXaxis()->GetXmin(),1.5,nominal->GetXaxis()->GetXmax(),1.5);
        TLine*line2=new TLine(nominal->GetXaxis()->GetXmin(),0.5,nominal->GetXaxis()->GetXmax(),0.5);
	line->SetLineColor(kRed-7);
	line->SetLineWidth(3);
        line1->SetLineStyle(2);
        line2->SetLineStyle(2);
        TH1D*hist_nominal=(TH1D*)hist_clone->Clone();
	TH1D*hist_nomNoErr=(TH1D*)hist_nominal->Clone();
//	for (int i = 1; i<= hist_nomNoErr->GetNbinsX(); ++i){hist_nomNoErr->SetBinError(i,0);}
	hist_nominal->Divide(nomNoErr);
        hist_nominal->SetMarkerStyle(20);
        hist_nominal->SetMarkerColor(1);
        hist_nominal->SetLineColor(1);
        double y_ratio[kk],yerror_down_ratio[kk],yerror_up_ratio[kk];
        vector<double> ye_h,ye_l;
        for(int i=0;i<hist_clone->GetNbinsX();i++){
                 y_ratio[i]=ybin[i]/nomNoErr->GetBinContent(i+1);
                 yerror_down_ratio[i]=yerror_down[i]/nomNoErr->GetBinContent(i+1);
                 yerror_up_ratio[i]=yerror_up[i]/nomNoErr->GetBinContent(i+1);
                 cout<<"bin"<<i+1<<" "<<y_ratio[i]<<" "<< yerror_down_ratio[i]<<" "<<yerror_up_ratio[i]<<" "<<nominal->GetBinError(i+1)<<endl;
                 ye_h.push_back(yerror_up_ratio[i]);
                 ye_l.push_back(yerror_down_ratio[i]);
        }
        TGraphAsymmErrors* gr1 = new TGraphAsymmErrors(kk, xbin, y_ratio, xerror_down,xerror_up, yerror_down_ratio, yerror_up_ratio);
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
//	line->Draw();
        line1->Draw();
        line2->Draw();
	fPads2->Update();
	fPads1->cd();
	fPads1->Update();
	c1->Print(var+"_unfold_df.pdf");


}
int Add_Mjjdf(){
	gStyle->SetOptStat(0);
        vector<TString> genvars={"genMjj"};
        vector<TString> recovars={"Mjj"};
        vector<TString> title={"m_{jj}"};
	for(int i=0;i<genvars.size();i++){
		run(genvars[i],recovars[i],title[i],"full");
	}
	return 0;

}
void cmsLumi(bool channel)
{
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.05);
	latex.SetLineWidth(2);
	float lumiel=137.1;
	float lumimu=137.1;
	int beamcomenergytev=13;
	latex.SetTextAlign(31);
	latex.SetTextAlign(11);
	latex.DrawLatex(0.18,0.85,"Preliminary");
	latex.DrawLatex(0.18,0.86,"CMS");
	latex.SetTextSize(0.045);
	latex.DrawLatex(0.76,0.92,Form("137.1 fb^{-1} (%d TeV)", (beamcomenergytev)));
}
