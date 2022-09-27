void run(TString var,TString year,int num){
     TFile*f1=new TFile("hist_ZA-EWK_"+var+year+".root");
     TH1D*h1[num];
     for(int i=0;i<num;i++){
         h1[i]=(TH1D*)f1->Get(var+Form("_%i",i));
         cout<<h1[i]->GetBinContent(i+1)/h1[i]->GetSum()<<endl;
     }
     f1->Close();
}
int print_eff(){
   vector<TString> var={"genlep1pt","genphotonet","genjet1pt","genMjj"};
   vector<int> num={4,4,4,7};
   vector<TString> year={"16","17","18"};
   for(int i=0;i<var.size();i++){
      for(int j=0;j<year.size();j++){
          cout<<var[i]<<" "<<year[j]<<endl;
          run(var[i],year[j],num[i]);
      }
   }

return 0;
}
