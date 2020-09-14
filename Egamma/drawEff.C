TFile*f1 = new TFile("eff_50_120_barrel.root");
TFile*f2 = new TFile("eff_50_120_endcap.root");
TFile*f3 = new TFile("eff_120_200_barrel.root");
TFile*f4 = new TFile("eff_120_200_endcap.root");
void Eff(int i,TFile* file1,TFile*file2,TCanvas* c1,TCanvas* c2){
TString filename = file1->GetName();
cout<<filename<<endl;
TEfficiency* effS_barrel = (TEfficiency*)file1->Get(Form("hsD_%i_clone",i+1));
//TH1D* effS_barrel = (TH1D*) eS_barrel->Clone();
TEfficiency* effUS_barrel = (TEfficiency*)file1->Get(Form("hunsD_%i_clone",i+1));
//TH1D* effUS_barrel = (TH1D*) eUS_barrel->Clone();
TEfficiency* effS_endcap = (TEfficiency*)file2->Get(Form("hsD_%i_clone",i+1));
//TH1D* effS_endcap = (TH1D*) eS_endcap->Clone();
TEfficiency* effUS_endcap = (TEfficiency*)file2->Get(Form("hunsD_%i_clone",i+1));
//TH1D* effUS_endcap = (TH1D*) eUS_endcap->Clone();
TString name = effS_barrel->GetTitle();
cout<<"OK"<<endl;
TString nameUS = "_US"; 
TString nameS = "_Seed"; 
TString tag1 = "50_120";
TString tag2 = "120_200";
TLegend* l1 = new TLegend(0.5,0.2,0.7,0.4);
TLegend* l2 = new TLegend(0.5,0.2,0.7,0.4);
c1->cd();
if(filename.Contains("200"))
	effS_barrel->GetPaintedHistogram()->SetTitle("seed/gen efficiency vs "+ name + " "+tag2);
else    effS_barrel->GetPaintedHistogram()->SetTitle("seed/gen efficiency vs "+ name + " "+tag1);
cout<<"OK"<<endl;
if(name.Contains("Eta")){
	effS_barrel->GetPaintedHistogram()->GetXaxis()->SetRangeUser(0,2.5);}
effS_barrel->GetPaintedHistogram()->GetYaxis()->SetRangeUser(0.1,1.0);
effS_barrel->SetLineColor(kRed-7);
effS_barrel->SetLineWidth(4);
effS_barrel->SetLineStyle(1);
effS_endcap->SetLineColor(kBlue);
effS_endcap->SetLineWidth(2);
effS_endcap->SetLineStyle(2);
effS_barrel->Draw("ape");
effS_endcap->Draw("same");
l1->AddEntry(effS_barrel,"Barrel","l");
l1->AddEntry(effS_endcap,"Endcap","l");
l1->SetTextSize(0.045);
l1->SetTextFont(30);
l1->Draw();

//effS->GetXaxis();
c2->cd();
if(filename.Contains("200"))
	effUS_barrel->GetPaintedHistogram()->SetTitle("unseed/gen efficiency vs "+ name + " "+ tag2);
else    effUS_barrel->GetPaintedHistogram()->SetTitle("unseed/gen efficiency vs "+ name + " "+ tag1);
if(name.Contains("Eta")){
	effUS_barrel->GetPaintedHistogram()->GetXaxis()->SetRangeUser(0,2.5);}
effUS_barrel->GetPaintedHistogram()->GetYaxis()->SetRangeUser(0.1,1.0);
effUS_barrel->SetLineColor(kRed-7);
effUS_barrel->SetLineWidth(4);
effUS_barrel->SetLineStyle(1);
effUS_endcap->SetLineColor(kBlue);
effUS_endcap->SetLineWidth(2);
effUS_endcap->SetLineStyle(2);
effUS_barrel->Draw("ape");
effUS_endcap->Draw("same");
l2->AddEntry(effS_barrel,"Barrel","l");
l2->AddEntry(effS_endcap,"Endcap","l");
l2->SetTextSize(0.045);
l2->SetTextFont(30);
l2->Draw();
if(filename.Contains("200"))
   {
	   c1->Print("./"+tag2+name+nameS+".pdf");
	   c2->Print("./"+tag2+name+nameUS+".pdf");
   }
else  {c1->Print("./"+tag1+name+nameS+".pdf"); c2->Print("./"+tag1+name+nameUS+".pdf");}
//delete c1;delete c2;
}

int drawEff() {
	TCanvas* c1[4];
	TCanvas* c2[4];
	for(int i =0;i<4;i++){
        c1[i] = new TCanvas(Form("50_120_seed%i",i),"",900,600);
        c2[i] = new TCanvas(Form("50_120_unseed%i",i),"",900,600);
	Eff(i,f1,f2,c1[i],c2[i]);
	}
	TCanvas* c3[4];
	TCanvas* c4[4];
	for(int i =0;i<4;i++){
        c3[i] = new TCanvas(Form("120_200_seed%i",i),"",900,600);
        c4[i] = new TCanvas(Form("120_200_unseed%i",i),"",900,600);
	Eff(i,f3,f4,c3[i],c4[i]);
	}

	return 1;
}
