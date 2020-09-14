#define num 103
void run(TString var, TString recovar,TString title,TString tag){
        TFile*file1=new TFile("unfold_"+var+"_ewk_pdf16.root");
        TH1D*h1[num];TH1D*h2[num];TH1D*h3[num];
	for(int i=0;i<num;i++){
		h1[i]=(TH1D*)file1->Get(var+Form("_%i",i));
	}
	const int kk=h1[0]->GetNbinsX();
	double xbin[kk],ybin[kk],xerror_up[kk],xerror_down[kk],yerror_up[kk],yerror_down[kk];
	double Err_up[kk],Err_down[kk];
	double Err_sysUp[kk],Err_sysDown[kk],yerror_sysUp[kk],yerror_sysDown[kk],xerror_sysUp[kk],xerror_sysDown[kk];
	ifstream f_in("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/txt/r_"+recovar+"_"+tag+".txt");
	ifstream f_sys("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/txt/breakdown/r_sys_"+recovar+"_"+tag+".txt");
	if(!f_in.is_open())cout<<"can not open the file "<<"/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/txt/r_"+recovar+"_"+tag+".txt"<<endl;
	if(!f_sys.is_open())cout<<"/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/txt/breakdown/r_sys_"+recovar+"_"+tag+".txt"<<endl;
	for(int i=0;i<h1[0]->GetNbinsX();i++){
                f_in>>Err_down[i]>>Err_up[i];
                f_sys>>Err_sysDown[i]>>Err_sysUp[i];
//              cout<<Err_down[i]<<" "<<Err_up[i]<<endl;
                xbin[i]=h1[0]->GetBinCenter(i+1);
                ybin[i]=1;
                xerror_up[i]=0.5*h1[0]->GetBinWidth(i+1);
                xerror_down[i]=0.5*h1[0]->GetBinWidth(i+1);
                yerror_up[i]=Err_up[i];
                yerror_down[i]=Err_down[i];
                xerror_sysUp[i]=0;
                xerror_sysDown[i]=0;
                yerror_sysUp[i]=Err_sysUp[i];
                yerror_sysDown[i]=Err_sysDown[i];
	}
	TCanvas*c1=new TCanvas("c0","signal strength",800,600);
        TGraphAsymmErrors* gr = new TGraphAsymmErrors(kk, xbin, ybin, xerror_down,xerror_up, yerror_down, yerror_up);
        TGraphAsymmErrors* gr_sys = new TGraphAsymmErrors(kk, xbin, ybin, xerror_sysDown,xerror_sysUp, yerror_sysDown, yerror_sysUp);
        gr->SetTitle(";"+title+";signal strength");
        gr->GetXaxis()->SetRangeUser(h1[0]->GetBinLowEdge(1),h1[0]->GetBinCenter(kk)+0.5*h1[0]->GetBinWidth(kk));
        
        gr->GetYaxis()->SetRangeUser(-0.5,3);
	gr->SetMarkerColor(1);
        gr->SetMarkerStyle(20);
        gr->SetFillColor(0);
        gr->SetMarkerSize(1);
        gr->SetLineColor(1);
        gr->Draw("AP SAME");
        gr_sys->SetLineColor(2);
        gr_sys->SetLineWidth(4);
        gr_sys->SetLineStyle(2);
        gr_sys->SetFillColor(0);
        gr_sys->SetMarkerSize(0);
        gr_sys->Draw("P SAME");
        TLegend*l1=new TLegend(0.4,0.6,0.68,0.88);
        l1->AddEntry(gr," stat. #oplus syst.");
        l1->AddEntry(gr_sys,"systematic uncertainty");
        l1->SetTextSize(0.065);
        l1->SetLineColor(0);
        TLine*line1=new TLine(h1[0]->GetXaxis()->GetXmin(),1.5,h1[0]->GetXaxis()->GetXmax(),1.5);
        TLine*line2=new TLine(h1[0]->GetXaxis()->GetXmin(),0.5,h1[0]->GetXaxis()->GetXmax(),0.5);
        line1->SetLineStyle(2);
        line2->SetLineStyle(2);
        line1->Draw();
        line2->Draw();
	l1->Draw();
        c1->Print(var+"_signal_strength"+tag+".pdf");
}
int draw_r(){
        vector<TString> title={"leading p_{T}^{lep}","leading p_{T}^{#gamma}","leading p_{T}^{j}","M_{jj}","m_{Z#gamma}"};
        vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};//,"genZGmass","genMjj"};
        vector<TString> recovars={"ptlep1","photonet","jet1pt"};

        for(int i=0;i<genvars.size();i++){
                run(genvars[i],recovars[i],title[i],"16");
                run(genvars[i],recovars[i],title[i],"17");
                run(genvars[i],recovars[i],title[i],"18");
                run(genvars[i],recovars[i],title[i],"full");
        }
        return 0;

}
