TFile*file;
void run(double lowpt,double highpt,TString tag,TString channel){
     vector<double> lowchiso={2.5,3.5,4.5,5.5,6.5,7.5,8.5};
     vector<double> highchiso={7.5,8.5,9.5,10.5,11.5,12.5,13.5};
     TString hist_name=channel+"_"+tag+Form("_pt%0.f_%0.f",lowpt,highpt);
     TH2D*h2=new TH2D(hist_name,hist_name,lowchiso.size()-1,&lowchiso[0],highchiso.size()-1,&highchiso[0]);
     ifstream f_closure("./closure/"+channel+tag+Form("closure_test_pt%0.f_%0.f.txt",lowpt,highpt));
     double xlow,yhigh,closure;
     if(!f_closure.is_open()) cout<<"can not open the file "<<channel+tag+Form("closure_test_pt%0.f_%0.f.txt",lowpt,highpt)<<endl; 
     if(f_closure.is_open()){
	     while(!f_closure.eof()){
                  f_closure>>xlow>>yhigh>>closure;
//                  cout<<xlow<<" "<<yhigh<<" "<<closure<<endl;
                  int binx=h2->GetXaxis()->FindFixBin(xlow);
                  int biny=h2->GetYaxis()->FindFixBin(yhigh);
                  h2->SetBinContent(binx,biny,closure);
	     }

     }
     file->cd();
     h2->Write();
     TCanvas*c1=new TCanvas("c1","",900,600);
     gStyle->SetOptStat(0);
     h2->SetMarkerSize(1.5);
     h2->Draw("colztext");
     h2->GetXaxis()->SetTitle("low chiso");
     h2->GetYaxis()->SetTitle("high chiso");
     c1->Print("./closure/"+channel+tag+Form("pt%0.f_%0.f.pdf",lowpt,highpt));
}
int draw_closure(){ 
	vector<TString> tag={"2016","2017","2018"};
        vector<TString> channel={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<double> lowpt;vector<double> highpt;
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<channel.size();j++){
			cout<<tag[i]<<" "<<channel[j]<<endl;
			if(channel[j].Contains("barrel")) {
				lowpt={20,25,30,40,50,60};
				highpt={25,30,40,50,60,400};
			}
			else if(channel[j].Contains("endcap")) {
				lowpt={20,25,30,50};
				highpt={25,30,50,400};
			}
                        const int ptnumber=lowpt.size();
                        cout<<"ptnumber "<<ptnumber<<endl;
                        file=new TFile("closure_"+channel[j]+tag[i]+".root","recreate");
			for(Int_t k=0;k<ptnumber;k++){
                           run(lowpt[k],highpt[k],tag[i], channel[j]);
			}

		}
	}
	return 0;
}
