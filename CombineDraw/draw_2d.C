#define pi 3.1415926
void run_full(TString tag,TString sample,TString channel,TString cut);
void run(TString tag,TString sample,TString channel,TString region){
	TString dir;
	if(region=="CR")
		dir="/home/pku/anying/cms/PKU-Cluster/RunII20"+tag+"/aa2/"+channel+"/output-slimmed-rootfiles/optimal_20"+tag+"CR_";
	else
		dir="/home/pku/anying/cms/PKU-Cluster/RunII20"+tag+"/aa2/SR/"+channel+"/output-slimmed-rootfiles/optimal_20"+tag+"CR_";
	TFile*file=new TFile(dir+sample+tag+".root");
	cout<<file->GetName()<<endl;
        TTree*tree=(TTree*)file->Get("outtree");
        double detajj,Mjj,actualWeight;
        tree->SetBranchAddress("Mjj",&Mjj);
        tree->SetBranchAddress("detajj",&detajj);
	tree->SetBranchAddress("actualWeight",&actualWeight);
	TH2D*h2;
	if(region=="CR")
		h2=new TH2D("h2",tag+" "+channel+" "+region+" "+sample,35,150,500,16,0,8);
	else
		h2=new TH2D("h2",tag+" "+channel+" "+region+" "+sample,30,500,2000,6,2.5,8);
	double lumi;
	if(tag.Contains("16")) lumi=35.86;
	if(tag.Contains("17")) lumi=41.52;
	if(tag.Contains("18")) lumi=59.7;
//      TTreeFormula*formula=new TTreeFormula("formula",cut,tree);
        for(int i=0;i<tree->GetEntries();i++){
		tree->GetEntry(i);
		if(Mjj>2000) Mjj=1999;
                if(detajj>8) detajj=7.5;
//              if (  !(formula->EvalInstance()) )
//  		   continue;
                h2->Fill(Mjj,detajj,actualWeight*lumi);
	}
        TCanvas*c1=new TCanvas("c1","",900,600);
//	Int_t palette[5];
//	palette[0] = 17;
//	palette[1] = 29;
//	palette[2] = 30;
//	palette[3] = 8;
//	palette[4] = 3;
//	gStyle->SetPalette(5,palette);
	gStyle->SetOptStat(0);
	h2->GetXaxis()->SetTitle("mjj [GeV]");
	h2->GetYaxis()->SetTitle("#Delta#eta_{jj}");
	h2->Draw("colz");
	c1->SaveAs("./figs/"+region+"_"+channel+"_"+sample+tag+".pdf");
	c1->SaveAs("./figs/"+region+"_"+channel+"_"+sample+tag+".png");
}
int draw_2d(){
	vector<TString> channel={"MuonBarrel","EleBarrel","MuonEndcap","EleEndcap"};	 
	vector<TString> sample={"ZA","ZA-EWK"};
	vector<TString> tag={"16","17","18"};
	TString LEPmu = "(drll>0.3 && lep==13 && (HLT_Mu1>0 || HLT_Mu2>0 || HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet;
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>150 && ZGmass>100)";
	TString opt="(zepp<2.4 && delta_phi>1.9)";
	for(int k=0;k<tag.size();k++){
		if(tag[k].Contains("17")==1){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Reco= "((("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+"&&"+opt+")";
		for(int i=0;i<channel.size();i++){
			run(tag[k],"ZA",channel[i],"CR");
			run(tag[k],"ZA",channel[i],"SR");
//			run_full(tag[k],"ZA",channel[i],Reco);
//			run_full(tag[k],"ZA-EWK",channel[i],Reco);
			run(tag[k],"ZA-EWK",channel[i],"CR");
			run(tag[k],"ZA-EWK",channel[i],"SR");
		}
	}
	return 0;
}
void run_full(TString tag,TString sample,TString channel,TString cut){
	TString dir;
	dir="/home/pku/anying/cms/PKU-Cluster/CombineDraw/ScalSeq/output-slimmed-rootfiles/optimal_";
	TFile*file=new TFile(dir+sample+tag+".root");
	cout<<file->GetName()<<endl;
	TTree*tree=(TTree*)file->Get("outtree");
	double detajj,Mjj,actualWeight;
	tree->SetBranchAddress("Mjj",&Mjj);
	tree->SetBranchAddress("detajj",&detajj);
	tree->SetBranchAddress("actualWeight",&actualWeight);
	TH2D*h2;
	h2=new TH2D("h2",tag+" "+channel+" Full "+sample,200,150,2000,16,0,8);
	double lumi;
	if(tag.Contains("16")) lumi=35.86;
	if(tag.Contains("17")) lumi=41.52;
	if(tag.Contains("18")) lumi=59.7;
	TTreeFormula*formula=new TTreeFormula("formula",cut,tree);
	for(int i=0;i<tree->GetEntries();i++){
		tree->GetEntry(i);
		if(Mjj>2000) Mjj=1999;
		if(detajj>8) detajj=7.5;
		if (  !(formula->EvalInstance()) )
			continue;
		h2->Fill(Mjj,detajj,actualWeight*lumi);
	}
	TCanvas*c1=new TCanvas("c1","",900,600);
	//	Int_t palette[5];
	//	palette[0] = 17;
	//	palette[1] = 29;
	//	palette[2] = 30;
	//	palette[3] = 8;
	//	palette[4] = 3;
	//	gStyle->SetPalette(5,palette);
	gStyle->SetOptStat(0);
	h2->GetXaxis()->SetTitle("mjj [GeV]");
	h2->GetYaxis()->SetTitle("#Delta#eta_{jj}");
	h2->Draw("colz");
	c1->SaveAs("figs/Full_"+channel+"_"+sample+tag+".pdf");
	c1->SaveAs("figs/Full_"+channel+"_"+sample+tag+".png");
}
