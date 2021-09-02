TH1D* run(TString cut,TString file,TString channel,TString isBarrel){
	vector<double> ptbins;
	if(isBarrel.Contains("barrel"))
		ptbins={20,25,30,35,40,50,60,100,400};
	else    ptbins={20,25,30,40,50,60,400};
	TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/cutlep-"+file+".root");
	TTree*tree=(TTree*)f1->Get("Events");
        TString histname=file+"_"+channel+"_"+isBarrel;
        TH1D*h1 = new TH1D(histname,"",ptbins.size()-1,&ptbins[0]);
        if(channel=="emu") cut = "( ( (channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11&&lep1_is_tight==1&&lep2_is_tight==1&&lep1_charge*lep2_charge<0&&drll>0.5&& lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5&&n_loose_ele==1&&n_loose_mu==1&&ptll>30 && mll>20) && "+cut +")"+" && ((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) )";
        if(isBarrel.Contains("barrel")) cut="("+cut+"&& (fabs(photoneta)<1.4442)"+")";
        else cut="("+cut+"&& (fabs(photoneta)<2.5&&fabs(photoneta)>1.566)"+")";
	if(file.Contains("Muon")||file.Contains("Ele"))
		tree->Draw("photonet>>"+histname,cut+"*1","goff");
        else
//		tree->Draw("photonet>>"+histname,cut+"*scalef*puWeight","goff");
		tree->Draw("photonet>>"+histname,cut+"*scalef*ele_id_scale*ele_reco_scale*muon_id_scale*muon_iso_scale*photon_id_scale*photon_veto_scale*puWeight","goff");
//      cout<<cut<<endl;
        cout<<channel<<" "<<" "<<file<<" "<<isBarrel<<" "<<h1->GetSum()<<" "<<h1->GetEntries()<<endl;
        h1->SetBinContent(h1->GetNbinsX(),h1->GetBinContent(h1->GetNbinsX())+h1->GetBinContent(h1->GetNbinsX()+1));
        h1->SetBinContent(h1->GetNbinsX()+1,0);
	return h1;
}
int cal_weight(){
	TString cut1="( n_photon>0 && photonet > 20. && drl1a>0.5 && drl2a>0.5 && photon_selection==1  )";
	TString cut2="( n_photon>0 && photonet > 20. && drl1a>0.5 && drl2a>0.5 && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) )";
	TString cut3="( n_photon>0 && photonet > 20. && drl1a>0.5 && drl2a>0.5 && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) && photon_isprompt==1 && lep1_isprompt==1 && lep2_isprompt==1 )";
	vector<TString> year={"16","17","18"};
        vector<TString> fname={"outMuonEG"};
	vector<TString> channel={"emu"};
        vector<TString> isBarrel={"barrel","endcap"};
	for(int i=0;i<fname.size();i++){
		for(int ik=2;ik<year.size();ik++){
			TFile*fhist=new TFile("weight_"+year[ik]+".root","recreate");
			for(int k=0;k<isBarrel.size();k++){
				cout<<fname[i]<<" "<<channel[i]<<" "<<year[ik]<<" "<<isBarrel[k]<<endl;
				double lumi;
				if(year[ik].Contains("16")) lumi=36;
				if(year[ik].Contains("17")) lumi=41.52;
				if(year[ik].Contains("18")) lumi=59.7;
				TH1D*h1=run(cut1,fname[i]+year[ik],channel[i],isBarrel[k]);
				TH1D*h2=run(cut2,fname[i]+year[ik],channel[i],isBarrel[k]);
				TH1D*h3=run(cut3,"outVV"+year[ik],channel[i],isBarrel[k]);
				TH1D*h4=run(cut3,"outTTGJets"+year[ik],channel[i],isBarrel[k]);
				TH1D*h5=run(cut3,"outZGJets"+year[ik],channel[i],isBarrel[k]);
				TH1D*h6=run(cut3,"outST"+year[ik],channel[i],isBarrel[k]);
				TH1D*h7=run(cut3,"outWWG"+year[ik],channel[i],isBarrel[k]);
				h3->Scale(lumi);
				h4->Scale(lumi);
				h5->Scale(lumi);
				h6->Scale(lumi);
				h7->Scale(lumi);
				fhist->cd();
				h1->Write();
                                TString name=h2->GetName();
				h2->Write(name+"_f");
				h3->Write();
				h4->Write();
				h5->Write();
				h6->Write();
				h7->Write();
				TCanvas*c1=new TCanvas("c1","",900,600);
//				c1->SetLogy();
				TLegend*l1=new TLegend(0.6,0.6,0.9,0.9);
				gStyle->SetOptStat(0);
				h2->Draw();
				h1->Draw("same");
				h3->Draw("same");
				h4->Draw("same");
				h5->Draw("same");
				h6->Draw("same");
				h7->Draw("same");
				h1->SetLineColor(2);
				h2->SetLineColor(3);
				h3->SetLineColor(4);
				h4->SetLineColor(5);
				h5->SetLineColor(6);
				h6->SetLineColor(7);
				h7->SetLineColor(8);
				l1->AddEntry(h1,"data");
				l1->AddEntry(h2,"plj");
				l1->AddEntry(h3,"VV");
				l1->AddEntry(h4,"TTGJets");
				l1->AddEntry(h5,"ZGJets");
				l1->AddEntry(h6,"ST");
				l1->AddEntry(h7,"WWG");
				l1->Draw();
				c1->Print("hist_com_"+channel[i]+"_"+isBarrel[k]+".pdf");
				ifstream f1;
				vector<double> ptbins;
				if(isBarrel[k].Contains("barrel"))
					ptbins={20,25,30,35,40,50,60,100,400};
				else    ptbins={20,25,30,40,50,60,400};
				const int n=ptbins.size()-1;
				double fakerate[n];
                                double plj_weight[n];
				ofstream ftxt("pljweight_"+channel[i]+"_"+isBarrel[k]+year[ik]+".txt");
                                TString c;
				if(channel[i]=="emu") c="ee";
                                else c=channel[i];
                                cout<<channel[i]<<" "<<c<<endl;
				TH2D*hist=new TH2D("weight_"+isBarrel[k],"",1,0,1,ptbins.size()-1,&ptbins[0]);
				for(int j=0;j<ptbins.size()-1;j++){
					f1.open(Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/"+isBarrel[k]+"/txt/fakerate_"+c+"_ZA_pt%0.f_%0.f.txt",ptbins[j],ptbins[j+1]));
					if(!f1.is_open())  cout<<"can not open the file "<<Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/"+isBarrel[k]+"/txt/fakerate_"+c+"_ZA_pt%0.f_%0.f",ptbins[j],ptbins[j+1])<<endl;
					f1>>fakerate[j];
					plj_weight[j]=h1->GetBinContent(j+1)/(h2->GetBinContent(j+1)-h3->GetBinContent(j+1)-h4->GetBinContent(j+1)-h5->GetBinContent(j+1)-h6->GetBinContent(j+1)-h7->GetBinContent(j+1))*fakerate[j];
					cout<<" pt "<<ptbins[j]<<"~"<<ptbins[j+1]<<", fake photon fraction "<<fakerate[j]<<", data yields "<<h1->GetBinContent(j+1)<<", plj yields "<<h2->GetBinContent(j+1)<<", prompt contribution from MC "<<h3->GetBinContent(j+1)+h4->GetBinContent(j+1)+h5->GetBinContent(j+1)+h6->GetBinContent(j+1)+h7->GetBinContent(j+1)<<", event weight "<<plj_weight[j]<<endl;

					ftxt<<fixed<<setprecision(2)<<plj_weight[j]<<endl;
					f1.close();
					hist->SetBinContent(1,j+1,plj_weight[j]);
				}
				fhist->cd();
                                hist->Write();
			}
			fhist->Close();
		}
	}
	return 0;
}
