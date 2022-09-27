TH1D*h1;TH1D*h2;
void run(TString cut1,TString cut2,TString var,double low,double high,TString lumi,int nbins){
	TFile*file=new TFile("/eos/user/y/yian/2017cutla/outZA-EWK_PU1.root");
	TTree*tree=(TTree*)file->Get("demo");
	TTreeFormula *tformula1=new TTreeFormula("formula1", cut1, tree);
	TTreeFormula *tformula2=new TTreeFormula("formula2", cut2, tree);
        TString h1name="h1_"+var;
        TString h2name="h2_"+var;
	h1=new TH1D(h1name,"with tight PU ID",   nbins,low,high);
	h2=new TH1D(h2name,"without tight PU ID",nbins,low,high);
	cout<<"entries after cut1 "<< tree->GetEntries(cut1)<<endl;
	cout<<"entries after cut2 "<< tree->GetEntries(cut2)<<endl;
	tree->Draw(var+">>"+h1name,cut1+"*scalef*"+lumi,"goff");
	tree->Draw(var+">>"+h2name,cut2+"*scalef*"+lumi,"goff");
}
void draw(TH1D*h1,TH1D*h2,TString title,double low,double high){
      gStyle->SetOptStat(0);
      TCanvas*c1=new TCanvas(title,title,750,500);
      TLegend *l1=new TLegend(0.6,0.7,0.9,0.9);
      TPad *top_pad=new TPad("top_pad", "top_pad",0,0.2, 1.0, 1.0);
      top_pad->Draw();
      top_pad->cd();
      top_pad->SetBottomMargin(0.1);
      h1->SetLineColor(kRed);
      h1->SetLineWidth(3);
      h1->SetMarkerStyle(20);
      double max=h1->GetMaximum();
      h1->GetYaxis()->SetRangeUser(0,4.5*max);
      h1->Draw("HIST");
      h1->SetTitle(title);

      h2->SetLineColor(kBlue);
      h2->SetLineWidth(4);
      h2->SetLineStyle(5);
      h2->SetMarkerStyle(20);
      h2->Draw("HIST same");
      l1->AddEntry(h1,"with PU ID");
      l1->AddEntry(h2,"without PU ID");
      l1->SetBorderSize(1);
      l1->SetFillColor(0);

      c1->cd();
      TLine* line;
      line = new TLine(low,1.,high,1);
      TPad *bottom_pad=new TPad("bottom_pad", "bottom_pad", 0, 0., 1.0, 0.2);
      bottom_pad->Draw();
      bottom_pad->cd();
      bottom_pad->SetTopMargin(0);
      TH1D *h3= (TH1D *)h2->Clone();
      h3->Divide(h1);
      h3->Draw("PE");
      h3->SetTitle("");
      h3->GetXaxis()->SetTitle( title );
      h3->GetYaxis()->SetTitle("ratio");
      h3->GetXaxis()->CenterTitle();
      h3->GetYaxis()->CenterTitle();
      h3->SetLineColor(kBlack);
      h3->GetXaxis()->SetTitleOffset(0.9);
      h3->GetYaxis()->SetTitleOffset(0.22);
      h3->GetXaxis()->SetTitleSize(0.15);
      h3->GetYaxis()->SetTitleSize(0.15);
      h3->GetXaxis()->SetLabelSize(0.12);
      h3->GetYaxis()->SetLabelSize(0.1);
//      h3->SetMaximum(1.35);
//      h3->SetMinimum(0.7);
      line->SetLineColor(kRed);
      line->Draw();
      l1->AddEntry(h3,"no-PU/PU");
      top_pad->cd();
      l1->Draw();
      c1->Draw();
      c1->Print(title +".pdf");
}
int draw_puId(){
     TString LEPmu = "lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110";
     TString LEPele = "lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110";
     TString photon = "photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )";
     TString jet1 = "( (jet1pt> 30 && jet2pt > 30 && jet1pt<50 && jet2pt<50 && jet1puIdTight>0 && jet2puIdTight>0 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7))";
     TString jet = "jet1pt> 30 && jet2pt > 30 && jet1pt<50 && jet2pt<50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
// || (jet1pt>50 && jet1pt>50 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7) )";
//     TString jet = "jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7";
     TString dr = " drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5";
     TString SignalRegion = "Mjj>500 && deltaetajj>2.5 && Mva>100";
     TString cut1= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet1+"&&"+SignalRegion;
     TString cut2= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
 
     vector<TString> titles={"photonet","photoneta","etalep1","etalep2","ptlep1","ptlep2","jet1pt","jet2pt","jet1eta","jet2eta","ptVlep","npT","nVtx","Mjj"};
     Double_t low[14] ={0,-3.3,-3.,-3.,0.,0.,30.,30.,-5.,-5.,0.,0.,0.,0.};
     Double_t high[14]={100,3.3,3.,3.,120.,120.,50.,50.,5.,5.,120.,120.,50.,1200 };
     for(int i=0;i<14;i++){
	     run(cut1,cut2,titles[i],low[i],high[i],"41.52",15);
             draw(h1,h2,titles[i],low[i],high[i]);
     }


	     return 1;
}
