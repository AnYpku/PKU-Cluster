#include "draw_style.C"
TH1D*get_hist(TString var, int nbins,float low, float high,TString cut,TString filename,TString year){
        TFile*file;TTree*tree;TChain*chain;
	TString weight;
	if(filename.Contains("EGamma")||filename.Contains("Muon")){
		chain=new TChain("Events","");
		chain->Add("/home/pku/anying/cms/rootfiles/cutjet-out"+filename+"*_"+year+".root");
		tree=chain;
		weight="*scalef";
	}
	else{
		file=new TFile("/home/pku/anying/cms/rootfiles/cutjet-out"+filename+"_"+year+".root");
		tree=(TTree*)file->Get("Events");
//		weight="*scalef";
		weight="*scalef*puWeight";
	}
	TString histname="hist_"+filename;
        TH1D*h1=new TH1D(histname,var,nbins,low,high);
	tree->Draw(var+">>"+histname,"("+cut+")"+weight,"goff");
	cout<<filename<<" number of entries "<<tree->GetEntries()<<", number of yields "<<h1->GetSum()<<endl;
        h1->SetBinContent(nbins,h1->GetBinContent(nbins)+h1->GetBinContent(nbins+1));
        h1->SetBinError(nbins,sqrt( pow(h1->GetBinError(nbins),2)+pow(h1->GetBinError(nbins+1),2) ) );
        return h1;
}
void run(TString data,TString year,TString var,TString title,float nbins,float low,float high){
    vector<TString> filename={"EWKZ2Jets","DYJetsLO","TTJets","ST","DiPhoton40ToInf","WWinc","WZinc","ZZinc",data};
    vector<TString> fname={"EWK Zjj","DY LO","t#bar{t}","t(#bar{t})W","#gamma#gamma","WW","WZ","ZZ",data};
    const int nfile=filename.size();
    TH1D*histMC[nfile];TH1D*hdata;THStack*hs=new THStack("hs","");
    TString HLT; TString cut;
    if(data.Contains("EGamma")){
	    HLT="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL ==1";
	    cut= "(n_loose_ele==2 && lep1pt>30 && lep2pt>25 && abs(lep1eta)<2.5 && abs(lep2eta)<2.5 && lepton_is_tight[0]==1 && lepton_is_tight[1]==1 && Vpt>20 && abs(Vmass-91)<15 && drj1l1>0.4 && drj2l1>0.4 && drj1l2>0.4 && drj2l2>0.4 && " + HLT +" && jet1pt>30 && jet2pt>30 )";
    }
    else if(data.Contains("Muon")){
	    HLT="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8==1";
	    cut = "(n_loose_mu==2 && lep1pt>30 && lep2pt>25 && abs(lep1eta)<2.4 && abs(lep2eta)<2.4 && lepton_is_tight[0]==1 && lepton_is_tight[1]==1 && Vpt>20 && abs(Vmass-91)<15 && drj1l1>0.4 && drj2l1>0.4 && drj1l2>0.4 && drj2l2>0.4 && " + HLT +" && jet1pt>30 && jet2pt>30 )";
    }
    cout<<data<<" "<<var<<", the selection is "<<cut<<endl;
    double lumi;
    if(year=="18") lumi=59.7;
    TFile*fout=new TFile("fout.root","recreate");
    for(int i=0;i<nfile;i++){
	    if(filename[i].Contains("EGamma")==0 && filename[i].Contains("Muon")==0){
		    histMC[i]=get_hist(var,nbins,low,high,cut,filename[i],year);
                    histMC[i]->SetLineColor(i+2);
                    histMC[i]->SetFillColor(i+2);
                    histMC[i]->SetMarkerColor(i+2);
                    histMC[i]->SetMarkerSize(0);
		    if(year.Contains("18"))
			    histMC[i]->Scale(lumi);
		    if(filename[i].Contains("DY") && filename[i].Contains("NLO"))
			    histMC[i]->Scale(5321/6077.22);
		    if(filename[i].Contains("DY") && filename[i].Contains("LO"))
			    histMC[i]->Scale(6077.2/5321);
		    hs->Add(histMC[i]);
		    fout->cd();
		    histMC[i]->Write();
	    }
	    else    hdata=get_hist(var,nbins,low,high,cut,filename[i],year);
    }
    fout->cd();
    hdata->Write();
    cout<<"Data: "<<hdata->GetSum()<<endl;
    hs->Write();
    draw(hdata,hs,filename,fname,title,data,year,Form("%.2f",lumi));
    fout->Close();
}
int get_plots(){
	vector<TString> title={"p_{T}^{Z}","m_{Z}","#eta^{Z}","#phi^{Z}","p_{T}^{j1}","#eta^{j1}","#phi^{j1}","p_{T}^{j2}","#eta^{j2}","#phi^{j2}","m_{jj}","#Delta#eta_{jj}","#Delta R_{jj}","number of vertex","p_{T}^{l1}","#eta^{l1}","#phi^{l1}","p_{T}^{l2}","#eta^{l2}","#phi^{l2}"};
	vector<TString> var={"Vpt","Vmass","Veta","Vphi","jet1pt","jet1eta","jet1phi","jet2pt","jet2eta","jet2phi","mjj","detajj","drjj","npvs","lep1pt","lep1eta","lep1phi","lep2pt","lep2eta","lep2phi"};
	vector<float> low={20,75,-2.5,-5,30,-5,-5,30,-5,-5,500,0,0,0,30,-2.5,-5,30,-2.5,-5};
	vector<float> high={600,110,2.5,5,800,5,5,500,5,5,2000,10,10,70,200,2.5,5,200,2.5,5};
	vector<float> nbins={40,40,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30};
	vector<TString> data={"Muon","EGamma"};
	for(int i=0;i<data.size();i++){
		for(int k=0;k<var.size();k++){
			if(var[k].Contains("jet1pt")==0) continue;
			run(data[i],"18",var[k],title[k],nbins[k],low[k],high[k]);
		}
	}

	return 1;
}
