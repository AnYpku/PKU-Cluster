void run(TString tag,TString sample,TString type,TString var,TString njets,int num){
	ofstream f1("./txt/"+type+"_uncer_"+sample+"_"+var+"_"+njets+"_"+tag+".txt");
	ofstream ftxt("./"+type+"_uncer_"+var+"_"+njets+"_"+tag+".txt",ios::app);
	TFile* file ;TString str;
        if(sample.Contains("Top")==0){
                file= new TFile("./root/hist_"+sample+"_"+var+"_"+njets+"_"+type+tag+".root");
		str=sample;
	}
        else{
                file= new TFile("./root/hist_TTJets_"+var+"_"+njets+"_"+type+tag+".root");
		str="TTJets";
	}
        TString mc_type;
        if(sample.Contains("WWG")) mc_type="sig"; else mc_type="bkg";
	cout<<mc_type<<endl;
        TH1D*h1[num];TH1D*h2[num];
	TFile*ff1;
	if(tag.Contains("16") ){
		ff1 = new TFile("./root/hist_"+str+"_"+var+"_"+njets+"_"+type+"16pre.root");
	}
        for(int i=0;i<num;i++){
		h1[i] = (TH1D*)file->Get(Form("hist_"+mc_type+"_%d",i));
		if(type.Contains("scale") && (sample.Contains("TTJets")||sample.Contains("Top")) && i!=4)
			h1[i]->Scale(2);
		else if(type.Contains("pdf") && (sample.Contains("TTJets")||sample.Contains("Top")) && i!=0)
			h1[i]->Scale(2);
		if(tag.Contains("16")){
			h2[i] = (TH1D*)ff1->Get(Form("hist_"+mc_type+"_%d",i));
			if(type.Contains("scale") && (str.Contains("TTJets")||str.Contains("Top")) && i!=4)
				h2[i]->Scale(2);
			else if(type.Contains("pdf") && (str.Contains("TTJets")||str.Contains("Top")) && i!=0)
				h2[i]->Scale(2);
			h1[i]->Add(h2[i]);
		}
	}
	TH1D*hh1[num];TH1D*hh2[num];
	TH1D*hh3[num];TH1D*hh4[num];
	TFile* file1;TFile* file2;
	TFile* file3;TFile* file4;
        if(sample.Contains("Top")){
                file1 = new TFile("./root/hist_TTGJets_"+var+"_"+njets+"_"+type+tag+".root");
                file2 = new TFile("./root/hist_ST_"+var+"_"+njets+"_"+type+tag+".root");
		for(int i=0;i<num;i++){
			hh1[i] = (TH1D*)file1->Get(Form("hist_"+mc_type+"_%d",i));
			hh2[i] = (TH1D*)file2->Get(Form("hist_"+mc_type+"_%d",i));
			h1[i]->Add(hh1[i]);
			h1[i]->Add(hh2[i]);
		}
		if(tag.Contains(16)){
			file3 = new TFile("./root/hist_TTGJets_"+var+"_"+njets+"_"+type+"16pre.root");
			file4 = new TFile("./root/hist_ST_"+var+"_"+njets+"_"+type+"16pre.root");
			for(int i=0;i<num;i++){
				hh3[i] = (TH1D*)file3->Get(Form("hist_"+mc_type+"_%d",i));
				hh4[i] = (TH1D*)file4->Get(Form("hist_"+mc_type+"_%d",i));
				h1[i]->Add(hh3[i]);
				h1[i]->Add(hh4[i]);
			}
		}
        }

        const int kk =h1[0]->GetNbinsX();
	Double_t bincontent_new[kk],bincontent_up[kk],bincontent_down[kk];
	Double_t uncer[kk];
        vector<Float_t> vec_content;
        vector<Float_t>:: iterator biggest;
        vector<Float_t>:: iterator smallest;
	f1<<type<<"_"<<var<<"_"<<njets<<"_"<<tag<<"=[";
	ftxt<<type<<"_"<<var<<"_"<<njets<<"_"<<sample<<"=[";
	cout<<type<<"_"<<var<<"_"<<njets<<"_"<<sample<<"_"<<tag<<" uncertainty ";
	for(Int_t i=0;i<kk;i++){
		float error=0;
		float diff=0,sum=0;
		float center=h1[0]->GetBinContent(i+1);
		for(int j=0;j<num;j++){
                        diff=h1[j]->GetBinContent(i+1)-center;
                        sum+=pow(diff,2);
			if(type.Contains("scale") && (j==2||j==6)) continue;
			cout<<type<<" "<<j<<" "<<h1[j]->GetBinContent(i+1)<<endl;
			vec_content.push_back(h1[j]->GetBinContent(i+1));
		}
		biggest = max_element(begin(vec_content),end(vec_content));
		smallest= min_element(begin(vec_content),end(vec_content));

		if(type.Contains("scale")==0 ) bincontent_new[i] = h1[0]->GetBinContent(i+1);
		else bincontent_new[i] = h1[4]->GetBinContent(i+1);

		if(bincontent_new[i]<=0) uncer[i] =0;
		else{
			if(type.Contains("scale")==0&&type.Contains("pdf")==0) 
				uncer[i] =fabs( h1[1]->GetBinContent(i+1)-h1[2]->GetBinContent(i+1))/2/bincontent_new[i];
			else if(type.Contains("scale"))uncer[i] = (*biggest - *smallest)/2/bincontent_new[i];
			else uncer[i] = sqrt(sum/(num-1))/h1[0]->GetBinContent(i+1);
		}
		if(uncer[i]>=1) uncer[i]=1;
		cout<<fixed<<"bin"<<i<<" "<<setprecision(3)<<*biggest<<" "<<*smallest<<" "<<bincontent_new[i]<<" "<<1+uncer[i]<<",";
		if(i<kk-1){
			f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<",";
		}
		if(i==kk-1){
			f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		}
		vec_content.clear(); 
	}
	cout<<endl;
	file->Close();
	if(sample.Contains("Top")){
		file1->Close();file2->Close();
	}
}
int uncer(){
        vector<TString> vars={"photonet","mllg","mll","mT_puppi"};
        vector<TString> types={"btag","l1pref","pileup","pdf","scale","fakephoton","ele_id","ele_reco","muon_id","muon_iso","photon_id","photon_veto"};
	vector<TString> names;
        vector<TString> tags={"16","17","18"};
	vector<TString> njets={"0jets","1jets","2jets"};
	int num;
        for(int i=0;i<njets.size();i++){
		for(int ik=0;ik<types.size();ik++){
//			if(types[ik].Contains("scale")==0)continue;
			if(types[ik].Contains("fakephoton")) {names={"plj"};}
			else if(types[ik].Contains("scale") || types[ik].Contains("pdf"))
				names={"TTGJets","TTJets","ST","WWG_emu_tot","Top"};
			else
				names={"ZGJets","TTGJets","TTJets","VV","ST","tZq","WGJets","WWG_emu_tot","Top"};
                        if(types[ik].Contains("scale")) num=9;
                        else if(types[ik].Contains("pdf")) num=101;
                        else num=3;
			for(int j=0;j<names.size();j++){
				for(int k=0;k<tags.size();k++){
					if(types[ik].Contains("l1pref") && tags[k].Contains("18"))
                                                continue;
					for(int n=0;n<vars.size();n++){
						if(i==0 && vars[n].Contains("mT")==0) continue;
						if(i>0 && vars[n].Contains("mT")) continue;
                                                run(tags[k],names[j],types[ik],vars[n],njets[i],num);
					}
                                }
			}
		}
	}
	return 1;
}
