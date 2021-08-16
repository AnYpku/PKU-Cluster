void run(vector<double> ptbins,TString tag,TString channel){
        ofstream fout1("./txt/uncer_summary_"+channel+tag+".txt");
        ofstream fout2("./txt/pljweight_"+channel+tag+".txt");
        ofstream fout3("./txt/pljweight_up_"+channel+tag+".txt");
        ofstream fout4("./txt/pljweight_down_"+channel+tag+".txt");
        ofstream fout5("./txt/plj_summary_"+channel+tag+".txt");
        ofstream fout6("./txt/fakerate_summary_"+channel+tag+".txt");
	ifstream f_cl,f_tr,f_sd,f_fraction;
	f_cl.open("/home/pku/anying/cms/PKU-Cluster/FakePhoton/closure_test/closure_uncer/ele"+channel+"20"+tag+"_closure_uncer.txt");
	f_tr.open("/home/pku/anying/cms/PKU-Cluster/FakePhoton/Truetemplate/truetemplate_uncer/ele"+channel+"20"+tag+"_truetemplate_uncer.txt");
	f_sd.open("/home/pku/anying/cms/PKU-Cluster/FakePhoton/sideband/sideband_uncer/ele"+channel+"20"+tag+"_sideband_uncer.txt");
        const int num=ptbins.size()-1; 
	double closure_uncer[num],truetemplate_uncer[num],sideband_uncer[num];
        double uncer_tot[num],fakerate[num],fakerate_up[num],fakerate_down[num];
	double pljweight[num],pljweight_up[num],pljweight_down[num];
	if(!f_cl.is_open())cout<<"can not open file /home/pku/anying/cms/PKU-Cluster/FakePhoton/closure_test/closure_uncer/"<<channel<<tag<<"_closure_uncer.txt"<<endl;
	if(!f_tr.is_open())cout<<"can not open file /home/pku/anying/cms/PKU-Cluster/FakePhoton/truetemplate/truetemplate_uncer/"<<channel<<tag<<"_truetemplate_uncer.txt"<<endl;
	if(!f_sd.is_open())cout<<"can not open file /home/pku/anying/cms/PKU-Cluster/FakePhoton/sideband/sideband_uncer/"<<channel<<tag<<"_sideband_uncer.txt"<<endl;
        
        TFile*f1=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/plj/cal_weight/weight_"+tag+".root");
        TString par;
        TH1D*hdata=(TH1D*)f1->Get("outMuonEG"+tag+"_emu_"+channel);
        TH1D*hplj=(TH1D*)f1->Get("outMuonEG"+tag+"_emu_"+channel+"_f");
        TH1D*hVV_plj=(TH1D*)f1->Get("outVV"+tag+"_emu_"+channel);
        TH1D*hTTA_plj=(TH1D*)f1->Get("outTTGJets"+tag+"_emu_"+channel);
        TH1D*hZA_plj=(TH1D*)f1->Get("outZGJets"+tag+"_emu_"+channel);
        TH1D*hST_plj=(TH1D*)f1->Get("outST"+tag+"_emu_"+channel);
        TH1D*hWWG_plj=(TH1D*)f1->Get("outWWG"+tag+"_emu_"+channel);
        hZA_plj->Add(hVV_plj,1);hZA_plj->Add(hTTA_plj,1);hZA_plj->Add(hST_plj);
	hZA_plj->Add(hWWG_plj,1);
        TH1D*h_up=new TH1D("weight_up","",ptbins.size()-1,&ptbins[0]);
        TH1D*h_down=new TH1D("weight_down","",ptbins.size()-1,&ptbins[0]);
        TFile*fout=new TFile("weight_"+channel+"_uncer"+tag+".root","recreate");
	for(int i=0;i<num;i++){
		f_fraction.open(Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/"+channel+"/txt/fakerate_ee"+"_ZA_pt%0.f_%0.f.txt",ptbins[i],ptbins[i+1]));
                if(!f_fraction.is_open()) cout<<"can not open file"<<Form("/home/pku/anying/cms/PKU-Cluster/WWg/fakephoton/fit/"+channel+"/txt/fakerate_ee"+"_ZA_pt%0.f_%0.f.txt",ptbins[i],ptbins[i+1])<<endl;
                f_fraction>>fakerate[i];
		f_cl>>closure_uncer[i];
		f_tr>>truetemplate_uncer[i];
		f_sd>>sideband_uncer[i];
                uncer_tot[i]=sqrt(pow(closure_uncer[i],2)+pow(truetemplate_uncer[i],2)+pow(sideband_uncer[i],2));
                fakerate_up[i]=fakerate[i]*(1+uncer_tot[i]);
                fakerate_down[i]=fakerate[i]*(1-uncer_tot[i]);
                pljweight[i]=hdata->GetBinContent(i+1)*fakerate[i]/(hplj->GetBinContent(i+1)-hZA_plj->GetBinContent(i+1));
                pljweight_up[i]=hdata->GetBinContent(i+1)*fakerate_up[i]/(hplj->GetBinContent(i+1)-hZA_plj->GetBinContent(i+1));
                pljweight_down[i]=hdata->GetBinContent(i+1)*fakerate_down[i]/(hplj->GetBinContent(i+1)-hZA_plj->GetBinContent(i+1));
                fout1<<fixed<<setprecision(0)<<ptbins[i]<<"~"<<ptbins[i+1]<<"\t"<<fixed<<setprecision(2)<<closure_uncer[i]<<"\t"<<truetemplate_uncer[i]<<"\t"<<sideband_uncer[i]<<"\t"<<uncer_tot[i]<<endl;
                fout2<<fixed<<setprecision(2)<<pljweight[i]<<endl;
                fout3<<fixed<<setprecision(2)<<pljweight_up[i]<<endl;
                fout4<<fixed<<setprecision(2)<<pljweight_down[i]<<endl;
		fout5<<fixed<<setprecision(0)<<ptbins[i]<<"~"<<ptbins[i+1]<<"\t"<<fixed<<setprecision(2)<<pljweight[i]<<"\t"<<pljweight_up[i]<<"\t"<<pljweight_down[i]<<endl;
                fout6<<fixed<<setprecision(0)<<ptbins[i]<<"~"<<ptbins[i+1]<<"\t"<<fixed<<setprecision(2)<<fakerate[i]<<"\t"<<fakerate_down[i]<<"\t"<<fakerate_up[i]<<endl;
                h_up->SetBinContent(i+1,pljweight_up[i]);
                h_down->SetBinContent(i+1,pljweight_down[i]);
                f_fraction.close();
	}
	fout->cd();
	h_up->Write();
	h_down->Write();
}
int Uncer_tot(){
        vector<TString> tag={"18"};
        vector<TString> channel={"barrel","endcap"};
        vector<double> ptbins;
        for(int i=0;i<tag.size();i++){
		for(int j=0;j<channel.size();j++){
			cout<<tag[i]<<" "<<channel[j]<<endl;
			if(channel[j].Contains("barrel")) {
				ptbins={20,25,30,35,40,50,60,100,400};
			}
			else if(channel[j].Contains("endcap")) {
				ptbins={20,25,30,40,50,60,400};
			}
			run(ptbins,tag[i],channel[j]);
		}
	}
	return 0;
} 
