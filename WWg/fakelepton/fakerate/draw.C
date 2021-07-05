TH1D*run(TString filename,TString cut,TString channel,TString type){
	TFile*f1=new TFile("../out"+filename+"18_fakerate.root");
        TTree*tree=(TTree*)f1->Get("Events");
        if(channel.Contains("mu")){
                if(filename.Contains("Muon")==0){
                        cut="("+cut+" && ( (lepton_pt>25 && HLT_Mu17_TrkIsoVVL)||(lepton_pt<25 && HLT_Mu8_TrkIsoVVL) ) && lepton_isprompt==1"+")";
                }
                else
                        cut="("+cut+"&&( (lepton_pt>25 && HLT_Mu17_TrkIsoVVL) || (lepton_pt<25 && HLT_Mu8_TrkIsoVVL) )"+")";
        }

        else if(channel.Contains("ele")){
                if(filename.Contains("Ele")==0){
                        cut="("+cut+"&&(HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30)&&lepton_isprompt==1"+")";
                }
                else
                        cut="("+cut+"&&(HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30)"+")";

        }
        if(type=="tight") cut="("+cut+"&& is_lepton_tight==1)";
	else cut="("+cut+"&& is_lepton_tight==0)";
        TString histname="hist_"+filename+"_"+type;
        TH1D*h1=new TH1D(histname,"",95,10,200);
        tree->Draw("lepton_pt>>"+histname,cut+"*scalef","goff");
        cout<<cut<<endl;
	return h1;
}
TCanvas* get_canvas(TString type){
        gStyle->SetOptStat(0);
        TString cut="( fabs(lepton_pid)==13 && lepton_pt>10 && fabs(lepton_eta)<2.4 && puppimet<30 && puppimt<20)";
	TH1D*h1=run("DMuon",cut,"mu",type);
	TH1D*h2=run("WJets",cut,"mu",type);
	TH1D*h3=run("DY",cut,"mu",type);
        TCanvas*c1=new TCanvas("c1_"+type,"",800,600);
        c1->SetLogy();
        h1->SetLineColor(1);
        h2->SetLineColor(2);
        h3->SetLineColor(3);
        h1->Draw();
        h2->Draw("same");
        h3->Draw("same");
        TLegend*l1=new TLegend(0.7,0.7,0.9,0.9);
        l1->AddEntry(h1,"Muon "+type);
        l1->AddEntry(h2,"WJets "+type);
        l1->AddEntry(h3,"DY "+type);
        l1->Draw();
        c1->Print("com_"+type+".pdf");
return c1;
}
int draw(){
        
	TCanvas*c1=get_canvas("tight");
	TCanvas*c2=get_canvas("loose_not_tight");
	return 0;
}
