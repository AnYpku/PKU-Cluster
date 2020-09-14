TFile*f1 = new TFile("eff_50_120_barrel.root");
TFile*f2 = new TFile("eff_50_120_endcap.root");
TFile*f3 = new TFile("eff_120_200_barrel.root");
TFile*f4 = new TFile("eff_120_200_endcap.root");
TGraphAsymmErrors* effS_barrel;
TGraphAsymmErrors* effUS_barrel;
TGraphAsymmErrors* effS_endcap;
TGraphAsymmErrors* effUS_endcap;
void Eff(int i,TFile* file1,TFile*file2,TCanvas* c1,TCanvas* c2,TCanvas*c3){
TString filename = file1->GetName();
cout<<filename<<endl;
TH1D* h1 = (TH1D*) file1->Get(Form("hsN_%i",i+1));
TH1D* h2 = (TH1D*) file2->Get(Form("hsN_%i",i+1));
TEfficiency* eS_barrel = (TEfficiency*)file1->Get(Form("hsD_%i_clone",i+1));
TEfficiency* eUS_barrel = (TEfficiency*)file1->Get(Form("hunsD_%i_clone",i+1));
TEfficiency* eS_endcap = (TEfficiency*)file2->Get(Form("hsD_%i_clone",i+1));
TEfficiency* eUS_endcap = (TEfficiency*)file2->Get(Form("hunsD_%i_clone",i+1));
TString name = eS_barrel->GetTitle();
cout<<name<<endl;
cout<<"OK"<<endl;
const int num = h1->GetNbinsX();
double eff_SB[num],x_SB[num],yerror_SBlow[num],yerror_SBhigh[num],xerror_SBhigh[num],xerror_SBlow[num];
double eff_SE[num],x_SE[num],yerror_SElow[num],yerror_SEhigh[num],xerror_SEhigh[num],xerror_SElow[num];
double eff_USB[num],x_USB[num],yerror_USBlow[num],yerror_USBhigh[num],xerror_USBhigh[num],xerror_USBlow[num];
double eff_USE[num],x_USE[num],yerror_USElow[num],yerror_USEhigh[num],xerror_USEhigh[num],xerror_USElow[num];
for(int i = 0;i<num;i++){

	eff_SB[i]=eS_barrel->GetEfficiency(i+1);
        x_SB[i]=h1->GetBinCenter(i+1);
        yerror_SBlow[i] = eS_barrel->GetEfficiencyErrorLow(i+1);
        yerror_SBhigh[i] = eS_barrel->GetEfficiencyErrorUp(i+1);
	xerror_SBhigh[i]=h1->GetBinWidth(i+1)/2;
	xerror_SBlow[i]=h1->GetBinWidth(i+1)/2;
        if(name.Contains("Eta")&&eS_barrel->GetEfficiency(i+1)==0){
		eff_SB[i]= 0;yerror_SBlow[i]=0;yerror_SBhigh[i]=0;
	}

	eff_SE[i]=eS_endcap->GetEfficiency(i+1);
        x_SE[i]=h1->GetBinCenter(i+1);
        yerror_SElow[i] = eS_endcap->GetEfficiencyErrorLow(i+1);
        yerror_SEhigh[i] = eS_endcap->GetEfficiencyErrorUp(i+1);
	xerror_SEhigh[i] = h2->GetBinWidth(i+1)/2;
	xerror_SElow[i] = h2->GetBinWidth(i+1)/2;
        if(name.Contains("Eta")&&eS_endcap->GetEfficiency(i+1)==0){
		eff_SE[i]= 0;yerror_SElow[i]=0;yerror_SEhigh[i]=0;
	}

	eff_USB[i]=eUS_barrel->GetEfficiency(i+1);
        x_USB[i]=h1->GetBinCenter(i+1);
        yerror_USBlow[i] = eUS_barrel->GetEfficiencyErrorLow(i+1);
        yerror_USBhigh[i] = eUS_barrel->GetEfficiencyErrorUp(i+1);
	xerror_USBhigh[i]=h1->GetBinWidth(i+1)/2;
	xerror_USBlow[i]=h1->GetBinWidth(i+1)/2;
        if(name.Contains("Eta")&&eUS_barrel->GetEfficiency(i+1)==0){
                eff_USB[i]= 0;yerror_USBlow[i]=0;yerror_USBhigh[i]=0;
        }

	eff_USE[i]=eUS_endcap->GetEfficiency(i+1);
        x_USE[i]=h1->GetBinCenter(i+1);
        yerror_USElow[i] = eUS_endcap->GetEfficiencyErrorLow(i+1);
        yerror_USEhigh[i] = eUS_endcap->GetEfficiencyErrorUp(i+1);
	xerror_USEhigh[i] = h2->GetBinWidth(i+1)/2;
	xerror_USElow[i] = h2->GetBinWidth(i+1)/2;
        if(name.Contains("Eta")&&eUS_endcap->GetEfficiency(i+1)==0){
                eff_USE[i]= 0;yerror_USElow[i]=0;yerror_USEhigh[i]=0;
        }

	cout<<filename<<"; Seed barrel: "<<name<<"; eff = "<<eff_SB[i]<<"; errorLow = "<<yerror_SBlow[i]<<"; errorHigh = "<<yerror_SBhigh[i]<<"; xbin "<<x_SB[i]<<endl;
	cout<<filename<<"; UnSeed barrel: "<<name<<"; eff =  "<<eff_USB[i]<<"; errorLow = "<<yerror_USBlow[i]<<"; errorHigh =  "<<yerror_USBhigh[i]<<"; xbin "<<x_USB[i]<<endl;
	cout<<filename<<"; Seed endcap: "<<name<<"; eff =  "<<eff_SE[i]<<"; errorLow = "<<yerror_SElow[i]<<"; errorHigh = "<<yerror_SEhigh[i]<<"; xbin "<<x_SE[i]<<endl;
	cout<<filename<<"; UnSeed endcap: "<<name<<"; eff = "<<eff_USE[i]<<"; errorLow = "<<yerror_USElow[i]<<"; errorHigh = "<<yerror_USEhigh[i]<<"; xbin "<<x_USE[i]<<endl;
}
effS_barrel = new TGraphAsymmErrors(num,x_SB,eff_SB,xerror_SBlow,xerror_SBhigh,yerror_SBlow,yerror_SBhigh);
effS_endcap = new TGraphAsymmErrors(num,x_SE,eff_SE,xerror_SElow,xerror_SEhigh,yerror_SElow,yerror_SEhigh);
effUS_barrel = new TGraphAsymmErrors(num,x_USB,eff_USB,xerror_USBlow,xerror_USBhigh,yerror_USBlow,yerror_USBhigh);
effUS_endcap = new TGraphAsymmErrors(num,x_USE,eff_USE,xerror_USElow,xerror_USEhigh,yerror_USElow,yerror_USEhigh);

TString nameUS = "_US"; 
TString nameS = "_Seed"; 
TString tag1 = "50_120";
TString tag2 = "120_200";
TLegend* l1 = new TLegend(0.2,0.25,0.4,0.45);
TLegend* l2 = new TLegend(0.2,0.25,0.4,0.45);
TLegend* l3 = new TLegend(0.2,0.25,0.4,0.45);
c1->cd();
if(filename.Contains("200"))
	effS_barrel->SetTitle("seed/gen efficiency vs "+ name + " "+tag2);
else    effS_barrel->SetTitle("seed/gen efficiency vs "+ name + " "+tag1);
cout<<"OK"<<endl;
//if(name.Contains("Eta")){
//	effS_barrel->GetXaxis()->SetRangeUser(0,2.5);}
if(name.Contains("Nrgy")){
	effS_barrel->GetYaxis()->SetRangeUser(0,1.1);}
else    effS_barrel->GetYaxis()->SetRangeUser(0,1.1);
effS_barrel->GetXaxis()->SetTitle(name);
effS_barrel->GetYaxis()->SetTitle("efficiency");
effS_barrel->SetLineColor(kRed-7);
effS_barrel->SetLineWidth(2);
effS_barrel->SetLineStyle(1);
effS_endcap->SetLineColor(kBlue);
effS_endcap->SetLineWidth(4);
effS_endcap->SetLineStyle(2);
effS_barrel->Draw("ap");
effS_endcap->Draw("P same");
l1->AddEntry(effS_barrel,"Barrel","l");
l1->AddEntry(effS_endcap,"Endcap","l");
l1->SetTextSize(0.045);
l1->SetTextFont(30);
l1->Draw();

//effS->GetXaxis();
c2->cd();
if(filename.Contains("200"))
	effUS_barrel->SetTitle("unseed/gen efficiency vs "+ name + " "+ tag2);
else    effUS_barrel->SetTitle("unseed/gen efficiency vs "+ name + " "+ tag1);
//if(name.Contains("Eta")){
//	effUS_barrel->GetXaxis()->SetRangeUser(0,2.5);}
if(name.Contains("Nrgy")){
	effUS_barrel->GetYaxis()->SetRangeUser(0.1,1.1);}
else    effUS_barrel->GetYaxis()->SetRangeUser(0,1.1);
effUS_barrel->GetXaxis()->SetTitle(name);
effUS_barrel->GetYaxis()->SetTitle("efficiency");
effUS_barrel->SetLineColor(kRed-7);
effUS_barrel->SetLineWidth(2);
effUS_barrel->SetLineStyle(1);
effUS_endcap->SetLineColor(kBlue);
effUS_endcap->SetLineWidth(4);
effUS_endcap->SetLineStyle(2);
effUS_barrel->Draw("ap");
effUS_endcap->Draw("P same");
l2->AddEntry(effUS_barrel,"Barrel","l");
l2->AddEntry(effUS_endcap,"Endcap","l");
l2->SetTextSize(0.045);
l2->SetTextFont(30);
l2->Draw();
c3->cd();
effS_barrel->SetLineColor(kRed-7);
effS_barrel->SetLineWidth(2);
effS_barrel->SetLineStyle(1);
effS_endcap->SetLineColor(kRed);
effS_endcap->SetLineWidth(4);
effS_endcap->SetLineStyle(2);
effUS_barrel->SetLineColor(kBlue-7);
effUS_barrel->SetLineWidth(2);
effUS_barrel->SetLineStyle(1);
effUS_endcap->SetLineColor(kBlue);
effUS_endcap->SetLineWidth(4);
effUS_endcap->SetLineStyle(2);
l3->AddEntry(effUS_barrel,"Barrel, US","l");
l3->AddEntry(effUS_endcap,"Endcap, US","l");
l3->SetTextSize(0.045);
l3->SetTextFont(30);
l3->AddEntry(effS_barrel,"Barrel, Seed","l");
l3->AddEntry(effS_endcap,"Endcap, Seed","l");

effS_barrel->Draw("ap");
effS_endcap->Draw("P same");
effUS_barrel->Draw("P same");
effUS_endcap->Draw("P same");
l3->Draw();

if(filename.Contains("200"))
   {
	   c1->Print("./"+tag2+name+nameS+".pdf");
	   c2->Print("./"+tag2+name+nameUS+".pdf");
	   c3->Print("./"+tag2+name+"_comp.pdf");
   }
else  {
	c1->Print("./"+tag1+name+nameS+".pdf"); c2->Print("./"+tag1+name+nameUS+".pdf");
	c3->Print("./"+tag1+name+"_comp.pdf");
      }
//delete c1;delete c2;
}

int asymmErrorsEff() {
	TCanvas* c1[4];
	TCanvas* c2[4];
	TCanvas* cc[4];
        const int n =4;
	for(int i =0;i<n;i++){
        c1[i] = new TCanvas(Form("50_120_seed%i",i),"",900,600);
        c2[i] = new TCanvas(Form("50_120_unseed%i",i),"",900,600);
        cc[i] = new TCanvas(Form("comp%i",i),"",900,600);
	Eff(i,f1,f2,c1[i],c2[i],cc[i]);
	}
	TCanvas* c3[4];
	TCanvas* c4[4];
	TCanvas* cc1[4];
	for(int i =0;i<n;i++){
        c3[i] = new TCanvas(Form("120_200_seed%i",i),"",900,600);
        c4[i] = new TCanvas(Form("120_200_unseed%i",i),"",900,600);
        cc1[i] = new TCanvas(Form("comp%i",i),"",900,600);
	Eff(i,f3,f4,c3[i],c4[i],cc1[i]);
	}

	return 1;
}
