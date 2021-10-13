#include "CMS_lumi.C"
void run(TString var,TString title,TString cut,vector<double> bins,TString year){
	vector<TString>sample={"MuonEG","ZGJets","TTGJets","WGJets","ST","VV","TGJets"};
	vector<short> vec_cols = {kBlack,kYellow-7,kBlue,kBlue-6,kGreen,kCyan,kRed-7,kGreen-6,kViolet};
	const int num=sample.size();
	cout<<var<<endl;
        TFile*fout=new TFile("hist_"+var+year+".root","recreate");
	TH1D*h1[num];
	for(int i=0;i<num;i++){
//		TFile*fin=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/CR_plot/Common/output-slimmed-rootfiles/optimal_emua_"+sample[i]+"_fakeL"+year+".root");
//		TFile*fin=new TFile("/home/pku/anying/cms/rootfiles/WWg/2018/v9/cutlep1-out"+sample[i]+year+"_fakeL.root");
		TFile*fin=new TFile("/home/pku/anying/cms/rootfiles/WWg/2018/cutlep1-out"+sample[i]+year+"_fakeL.root");
		TString histname="hist_"+sample[i];
		h1[i]=new TH1D(histname,"prompt lepton contribution",bins.size()-1,&bins[0]);
		TTree*tree=(TTree*)fin->Get("Events");
                if(sample[i].Contains("Muon"))
			tree->Draw(var+">>"+histname,"("+cut+")*scalef","goff");
		else
			tree->Draw(var+">>"+histname,"("+cut+")*scalef","goff");
		cout<<sample[i]<<" "<<tree->GetEntries()<<" "<<h1[i]->GetSum()<<endl;
//		fin->Close();
	}
        gStyle->SetOptStat(0);
	TLegend*l1=new TLegend(0.64,0.65,0.89,0.89);
	TLegend*l2=new TLegend(0.2,0.55,0.5,0.89);
        l1->SetLineColor(0);
        l2->SetLineColor(0);
	TCanvas*c1=new TCanvas("c_"+var,"",800,600);
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0, 0.99, 0.99);
        fPads1->Draw();
	fPads1->SetBottomMargin(0.15);
        fPads1->cd();
//	c1->SetLogy();
	h1[0]->SetLineColor(1);
	h1[0]->SetLineWidth(2);
        h1[0]->SetMarkerStyle(20);
        h1[0]->SetMarkerColor(1);
//        h1[0]->GetYaxis()->SetRangeUser(0.001,h1[0]->GetMaximum()*3);
	h1[0]->SetTitle(";"+var+";Events/bins");
	l2->AddEntry(h1[0],Form("Nonprompt #font[12]{l} from data [%.1f]",h1[0]->GetSum()));
	fout->cd();

	TH1D*hist=new TH1D("hist_"+year,"",bins.size()-1,&bins[0]);
	for(int i=0;i<hist->GetNbinsX();i++){
                hist->SetBinContent(i+1,h1[1]->GetBinContent(i+1));
                hist->SetBinError(i+1,h1[1]->GetBinError(i+1));
	}
	for(int i=2;i<num;i++){
		hist->Add(h1[i],1);
	}
	cout<<hist->GetSum()<<endl;
        double tot=hist->GetSum();
	l2->AddEntry(hist,Form("Total MC removal [%.1f]",-hist->GetSum()),"f");
        THStack* hs = new THStack("hs", "");
	for(int i=1;i<num;i++){
                h1[i]->Scale(-1);
		if(h1[i]->GetSumOfWeights()<0) continue;
                h1[i]->SetMarkerSize(vec_cols[i]);
		h1[i]->SetMarkerColor(vec_cols[i]);
		h1[i]->SetLineColor(vec_cols[i]);
		h1[i]->SetFillColor(vec_cols[i]);
		if(i<=4)		
			l1->AddEntry(h1[i],sample[i]+Form(" [%.1f]",h1[i]->GetSum()));
		else{
			if(h1[i]->GetSumOfWeights()>0.05) 
				l2->AddEntry(h1[i],sample[i]+Form(" [%.1f]",h1[i]->GetSum()));
			else if(h1[i]->GetSumOfWeights()<0.05 && h1[i]->GetSumOfWeights()>0.015)
				l2->AddEntry(h1[i],sample[i]+Form(" [%.2f]",h1[i]->GetSum()));
}
                hs->Add(h1[i]);
		fout->cd();
		h1[i]->Write();
	}
        hs->Write();
        hist->Write();
        fout->Close();

	double max=h1[0]->GetMaximum();
	hs->SetMaximum(max*2.5);
        hs->Draw("HIST");
        hs->GetYaxis()->SetTitleSize(0.05);
        hs->GetXaxis()->SetTitleSize(0.05);
        hs->GetYaxis()->SetLabelSize(0.04);
        hs->GetXaxis()->SetLabelSize(0.04);
        hs->GetYaxis()->SetNdivisions(505);
	hs->GetYaxis()->SetTitle("Events /bin");
        hs->GetYaxis()->SetTitleOffset(0.8);
        hs->GetXaxis()->SetTitleOffset(1.2);
	hs->GetXaxis()->SetTitle(title);
	h1[0]->Draw("P E SAME");
        l2->Draw();
        l1->Draw();
        string lumivalue;
        if(year.Contains("16")) lumivalue="35.86";
        if(year.Contains("17")) lumivalue="41.52";
        if(year.Contains("18")) lumivalue="59.7";
        CMS_lumi(fPads1, 4, 0, lumivalue);
	fPads1->Update();
	c1->Print("hist_"+var+year+".pdf"); 
}
int get_promptMC(){
	vector<double> ptbins={20,25,30,40,60,100};
//	vector<double> ptbins={30,40,50,60,80,120};
	vector<double> mTbins={60,80,120,160,200,250};
	TString cut="(channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && !(lep1_is_tight==1 && lep2_is_tight==1 ) && lep1_isprompt==1 && lep2_isprompt==1 && n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 )) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && PuppiMET_T1_pt > 20 && n_bjets>=0)";


//	run("photonet", cut, ptbins,"17");
	run("photonet","p_{T}^{#gamma}", cut, ptbins,"18");
//	run("mT","m_{T}^{WW}", cut, mTbins,"18");
//	run("mT","m_{T}^{WW}", cut, mTbins,"17");

	return 0;
} 
