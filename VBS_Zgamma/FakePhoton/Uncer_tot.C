void run(vector<double> lowpt,vector<double> highpt,TString tag,TString channels,TString channel,const int num){
        ofstream fout1("./txt-WWg/uncer_summary_"+channel+tag+".txt");
        ofstream fout2("./txt-WWg/pljweight_"+channel+tag+".txt");
        ofstream fout3("./txt-WWg/pljweight_up_"+channel+tag+".txt");
        ofstream fout4("./txt-WWg/pljweight_down_"+channel+tag+".txt");
        ofstream fout5("./txt-WWg/plj_summary_"+channel+tag+".txt");
        ofstream fout6("./txt-WWg/fakerate_summary_"+channel+tag+".txt");
	ifstream f_cl,f_tr,f_sd;
	f_cl.open("./closure_test/closure_uncer/"+channel+"20"+tag+"_closure_uncer.txt");
	f_tr.open("./Truetemplate/truetemplate_uncer/"+channel+"20"+tag+"_truetemplate_uncer.txt");
	f_sd.open("./sideband/sideband_uncer/"+channel+"20"+tag+"_sideband_uncer.txt");
       
	double closure_uncer[num],truetemplate_uncer[num],sideband_uncer[num];
        double uncer_tot[num],fakerate[num],fakerate_up[num],fakerate_down[num];
	double pljweight[num],pljweight_up[num],pljweight_down[num];
	if(!f_cl.is_open())cout<<"can not open file ./closure_test/closure_uncer/"<<channel<<tag<<"_closure_uncer.txt"<<endl;
	if(!f_tr.is_open())cout<<"can not open file ./truetemplate/truetemplate_uncer/"<<channel<<tag<<"_truetemplate_uncer.txt"<<endl;
	if(!f_sd.is_open())cout<<"can not open file ./sideband/sideband_uncer/"<<channel<<tag<<"_sideband_uncer.txt"<<endl;
        TFile*f1=new TFile("/home/pku/anying/cms/PKU-Cluster/RunII20"+tag+"/plj/plj-plot/all/hist_plj_"+channels+"_20"+tag+".root");
        TString par;
	if(channels.Contains("Muon")) par="DMuon";
	if(channels.Contains("Ele")) par="DEle";
        TH1D*hdata=(TH1D*)f1->Get("hist_"+par+tag);
        TH1D*hplj=(TH1D*)f1->Get("hist_plj"+tag);
//        TH1D*hZA_plj=(TH1D*)f1->Get("hist_ZA"+tag+"_plj");
	for(int i=0;i<num;i++){
		f_cl>>closure_uncer[i];
		f_tr>>truetemplate_uncer[i];
		f_sd>>sideband_uncer[i]>>fakerate[i];
                uncer_tot[i]=sqrt(pow(closure_uncer[i],2)+pow(truetemplate_uncer[i],2)+pow(sideband_uncer[i],2));
                fakerate_up[i]=fakerate[i]*(1+uncer_tot[i]);
                fakerate_down[i]=fakerate[i]*(1-uncer_tot[i]);
                pljweight[i]=hdata->GetBinContent(i+1)*fakerate[i]/(hplj->GetBinContent(i+1)/*-hZA_plj->GetBinContent(i+1)*/);
                pljweight_up[i]=hdata->GetBinContent(i+1)*fakerate_up[i]/(hplj->GetBinContent(i+1)/*-hZA_plj->GetBinContent(i+1)*/);
                pljweight_down[i]=hdata->GetBinContent(i+1)*fakerate_down[i]/(hplj->GetBinContent(i+1)/*-hZA_plj->GetBinContent(i+1)*/);
                fout1<<fixed<<setprecision(0)<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<fixed<<setprecision(2)<<closure_uncer[i]<<"\t"<<truetemplate_uncer[i]<<"\t"<<sideband_uncer[i]<<"\t"<<uncer_tot[i]<<endl;
                fout2<<fixed<<setprecision(2)<<pljweight[i]<<endl;
                fout3<<fixed<<setprecision(2)<<pljweight_up[i]<<endl;
                fout4<<fixed<<setprecision(2)<<pljweight_down[i]<<endl;
		fout5<<fixed<<setprecision(0)<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<fixed<<setprecision(2)<<pljweight[i]<<"\t"<<pljweight_up[i]<<"\t"<<pljweight_down[i]<<endl;
                fout6<<fixed<<setprecision(0)<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<fixed<<setprecision(2)<<fakerate[i]<<"\t"<<fakerate_down[i]<<"\t"<<fakerate_up[i]<<endl;
	}
}
int Uncer_tot(){
        vector<TString> tag={"16","17","18"};
        vector<TString> channel={"BarrelMuon","EndcapMuon","ElectronBarrel","ElectronEndcap"};
        vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
        vector<double> lowpt;vector<double> highpt;
        for(int i=0;i<tag.size();i++){
		for(int j=0;j<channel.size();j++){
			cout<<tag[i]<<" "<<channel[j]<<endl;
			if(channel[j].Contains("Barrel")) {
				lowpt={20,25,30,35,40,50,60,100};
				highpt={25,30,35,40,50,60,100,400};
			}
			else if(channel[j].Contains("Endcap")) {
				lowpt={20,25,30,40,50,60};
				highpt={25,30,40,50,60,400};
			}
			const int num=lowpt.size();
			run(lowpt,highpt,tag[i],channel[j],channels[j],num);
		}
	}
	return 0;
} 
