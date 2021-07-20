TH1D*run(TString filename,TString cut,TString channel,TString type){
	TChain*tree=new TChain("Events","");
	if(filename.Contains("Ele")==0){
		tree->Add("../rootfiles/out"+filename+"_fakerate18.root");
	}
	else{
		tree->Add("../rootfiles/out"+filename+"_fakerate18.root"); 
	}
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
void get_canvas(TString type,TString channel,TString filename){
        gStyle->SetOptStat(0);
        TString cut="( fabs(lepton_pid)==13 && lepton_pt>10 && fabs(lepton_eta)<2.4 && puppimet<30 && puppimt<20)";
	TH1D*h1=run(filename,cut,channel,type);
	TH1D*h2=run("WJets",cut,channel,type);
	TH1D*h3=run("DYJets",cut,channel,type);
	TH1D*h4=run("TTJets",cut,channel,type);
        TCanvas*c1=new TCanvas("c1_"+type,"",800,600);
        c1->SetLogy();
        h1->SetLineColor(1);
        h2->SetLineColor(2);
        h3->SetLineColor(3);
        h4->SetLineColor(4);
        h1->Draw();
        h2->Draw("same");
        h3->Draw("same");
        TLegend*l1=new TLegend(0.7,0.7,0.9,0.9);
        l1->AddEntry(h1,"Muon "+type);
        l1->AddEntry(h2,"WJets "+type);
        l1->AddEntry(h3,"DY "+type);
        l1->AddEntry(h4,"TTJets "+type);
        l1->Draw();
        c1->Print("com_"+type+".pdf");
        TFile*fout=new TFile("hist_lepton_pt_"+type+"_"+channel+"18.root","recreate");
        fout->cd();
        h1->Write();
        h2->Write();
        h3->Write();
        h4->Write();
        fout->Close();
         
}
int draw(){
        
	get_canvas("tight","mu","DMuon");
//	get_canvas("loose_not_tight");
	return 0;
}
