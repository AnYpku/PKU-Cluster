void draw(TGraph*graph,TString tag,TString op,TString op1);
TGraph* run(TString tag,TString op){
	TFile*file=new TFile("../higgs_root/higgsCombinenominal.MultiDimFit.mH125.expected."+op+"_"+tag+".root");
	TTree*tree=(TTree*)file->Get("limit");
        float param,deltaNLL;
        tree->SetBranchAddress("param",&param);
        tree->SetBranchAddress("deltaNLL",&deltaNLL);
        int entries=tree->GetEntries();
        TGraph*gr=new TGraph(entries);
        for(int i=0;i<tree->GetEntries();i++){
            tree->GetEntry(i);
            gr->SetPoint(i,param,2*deltaNLL);
	}
return gr;
}
int draw_deltaNLL(){
	vector<TString>op1={"F_{M_{0}}","F_{M_{1}}","F_{M_{2}}","F_{M_{3}}","F_{M_{4}}","F_{M_{5}}","F_{M_{6}}","F_{M_{7}}","F_{T_{0}}","F_{T_{1}}","F_{T_{2}}","F_{T_{5}}","F_{T_{6}}","F_{T_{7}}","F_{T_{8}}","F_{T_{9}}"};
	vector<TString>op2={"fM0","fM1","fM2","fM3","fM4","fM5","fM6","fM7","fT0","fT1","fT2","fT5","fT6","fT7","fT8","fT9"};
        vector<TString>tag={"16","17","18","combine"};
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<op2.size();j++){
			TGraph*gr=run(tag[i],op2[j]);
			draw(gr,tag[i],op1[j],op2[j]);
		}
	}
	return 0;
}
void draw(TGraph*graph,TString tag,TString op,TString op1){
	TCanvas*c1=new TCanvas("c1","",900,600);
	c1->SetBottomMargin(0.2);
	graph->SetTitle("");
	graph->GetYaxis()->SetRangeUser(0,14);
	graph->SetMarkerColor(kBlue);
	graph->SetMarkerStyle(7);
	graph->SetLineColor(kBlue);
	graph->GetYaxis()->SetTitle("2#DeltaNLL");
	graph->GetXaxis()->SetTitle(op+"/#Lambda ^{4}(TeV^{-4})");
	graph->GetXaxis()->SetTitleSize(0.08);
	graph->GetXaxis()->SetLabelSize(0.05);
	graph->Draw("AP");
	TLine*line=new TLine(graph->GetXaxis()->GetXmin(),3.84,graph->GetXaxis()->GetXmax(),3.84);
	line->SetLineColor(1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw();
	TLegend*l1=new TLegend(0.4,0.6,0.89,0.89);
        l1->SetLineColor(0);
	l1->AddEntry(graph,"Obseved 2#DeltaNLL","l");
	l1->AddEntry(line,"Obseved 95% CL interval","l");
	l1->SetTextSize(0.04);
	l1->Draw();
	c1->Print("deltaNLL_"+op1+tag+".pdf");
}
