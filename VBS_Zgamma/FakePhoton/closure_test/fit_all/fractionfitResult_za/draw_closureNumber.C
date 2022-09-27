#include "CMS_lumi.C"
TFile*file;
void run(double lowpt,double highpt,TString tag,TString channel){
     vector<double> lowchiso={2.5,3.5,4.5,5.5,6.5,7.5,8.5};
     vector<double> highchiso={7.5,8.5,9.5,10.5,11.5,12.5,13.5};
     TString hist_name=channel+"_"+tag+Form("_pt%0.f_%0.f",lowpt,highpt);
//     TString hist_title=channel+"_"+tag+Form("_pt%0.f_%0.f",lowpt,highpt);
     TH2D*h2=new TH2D(hist_name,hist_name,lowchiso.size()-1,&lowchiso[0],highchiso.size()-1,&highchiso[0]);
     ifstream f_closure("./closure/"+channel+tag+Form("closure_number_pt%0.f_%0.f.txt",lowpt,highpt));
     double xlow,yhigh,fit,fitErr,mcTruth;
     TString number;
     if(!f_closure.is_open()) cout<<"can not open the file "<<channel+tag+Form("closure_test_pt%0.f_%0.f.txt",lowpt,highpt)<<endl; 
     if(f_closure.is_open()){
	     while(!f_closure.eof()){
                  f_closure>>xlow>>yhigh>>fit>>fitErr>>mcTruth;
//                  cout<<xlow<<" "<<yhigh<<" "<<closure<<endl;
                  int binx=h2->GetXaxis()->FindFixBin(xlow);
                  int biny=h2->GetYaxis()->FindFixBin(yhigh);
                  h2->SetBinContent(binx,biny,fit);
                  h2->SetBinError(binx,biny,fitErr);
	     }
	     number=Form("%0.2f",mcTruth);
     }
     file->cd();
     h2->Write();
     TCanvas*c1=new TCanvas("c1","",800,600);
     TPad* fPad1 = new TPad("pad1", "pad1", 0.00, 0.00, 0.99, 0.99);
     fPad1->Draw();
     fPad1->cd();
     fPad1->SetTicky();
     fPad1->SetLeftMargin(0.15);
     fPad1->SetTopMargin(0.1);
     fPad1->SetBottomMargin(0.18);
     gStyle->SetOptStat(0);
     h2->SetMarkerSize(1.5);
     h2->Draw("colztext E");
     TString Num = number+ " events from simulation";
     TString ch;
     if(channel.Contains("mubarrel"))
	     ch="#mu#mu#gamma_{#font[132]{barrel}}";
     else if(channel.Contains("muendcap"))
	     ch="#mu#mu#gamma_{#font[132]{endcap}}";
     else if(channel.Contains("elebarrel"))
	     ch="#font[132]{ee}#gamma_{#font[132]{barrel}}";
     else if(channel.Contains("eleendcap"))
	     ch="#font[132]{ee}#gamma_{#font[132]{endcap}}";
     TString ptR = Form("%0.f < p_{T}^{#gamma} < %0.f GeV",lowpt,highpt);
     h2->GetXaxis()->SetTitle("low I_{ch}");
     h2->GetYaxis()->SetTitle("high I_{ch}");
     h2->GetXaxis()->SetLabelSize(0.05);
     h2->GetXaxis()->SetLabelOffset(0.03);
     h2->GetYaxis()->SetLabelSize(0.05);
     h2->GetXaxis()->SetTitleSize(0.08);
     h2->GetYaxis()->SetTitleSize(0.08);
     h2->GetYaxis()->SetTitleOffset(0.6);
     h2->SetTitle("");
     TLatex *text1 = new TLatex(0.45, 0.35, Num);
     TLatex *text2 = new TLatex(0.45, 0.25, ch+" "+ptR);
     text1->SetNDC();
     text2->SetNDC();
     text1->SetTextSize(0.045);
     text2->SetTextSize(0.045);
     text1->SetLineWidth(1);
     text2->SetLineWidth(1);
     text1->Draw();
     text2->Draw();
     string lumi;
     if(tag.Contains("16")) lumi="35.9";
     else if(tag.Contains("17")) lumi="41.5";
     else lumi="59.7";
     CMS_lumi(fPad1, 4, 0., lumi);
     fPad1->Update();
     c1->Print("./closure/Number_"+channel+tag+Form("pt%0.f_%0.f.pdf",lowpt,highpt));
}
int draw_closureNumber(){ 
	vector<TString> tag={"2016","2017","2018"};
        vector<TString> channel={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<double> lowpt;vector<double> highpt;
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<channel.size();j++){
			cout<<tag[i]<<" "<<channel[j]<<endl;
			if(channel[j].Contains("barrel")) {
				lowpt={20,25,30,40,50,60};
				highpt={25,30,40,50,60,400};
			}
			else if(channel[j].Contains("endcap")) {
				lowpt={20,25,30,50};
				highpt={25,30,50,400};
			}
                        const int ptnumber=lowpt.size();
                        cout<<"ptnumber "<<ptnumber<<endl;
                        file=new TFile("closure_"+channel[j]+tag[i]+".root","recreate");
			for(Int_t k=0;k<ptnumber;k++){
                           run(lowpt[k],highpt[k],tag[i], channel[j]);
			}

		}
	}
	return 0;
}
