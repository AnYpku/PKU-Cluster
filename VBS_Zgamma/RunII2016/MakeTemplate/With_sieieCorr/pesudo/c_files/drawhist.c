{
 TString b ="0515_constrast";
 TFile *f = new TFile("../rootfiles/datapure.root");
 TTree *t1 =(TTree*)f->Get("demo");
 //the needed variables in the root file
 Double_t ptlep1,ptlep2,etalep1,etalep2,massVlep;
 Double_t scalef;
 Int_t nlooseeles,nloosemus;
 Double_t photon_drla[6],photon_pt[6],photon_drla2[6],photon_sieie[6],photon_chiso[6];
 double photon_hoe[6];
 double photon_nhiso[6];
 double photon_phoiso[6];
 double photon_eta[6];
 int photon_isprompt[6];
 t1->SetBranchAddress("photon_isprompt",photon_isprompt); t1->SetBranchAddress("photon_hoe",photon_hoe);
 t1->SetBranchAddress("photon_nhiso",photon_nhiso);
 t1->SetBranchAddress("photon_phoiso",photon_phoiso);
 t1->SetBranchAddress("photon_pt",photon_pt);
 t1->SetBranchAddress("photon_eta",photon_eta);
 t1->SetBranchAddress("scalef",&scalef);
 t1->SetBranchAddress("nloosemus",&nloosemus);
 t1->SetBranchAddress("nlooseeles",&nlooseeles);
 t1->SetBranchAddress("ptlep1",&ptlep1);
 t1->SetBranchAddress("ptlep2",&ptlep2);
 t1->SetBranchAddress("etalep1",&etalep1);
 t1->SetBranchAddress("etalep2",&etalep2);
 t1->SetBranchAddress("massVlep",&massVlep);
 t1->SetBranchAddress("photon_isprompt",photon_isprompt);
 t1->SetBranchAddress("photon_drla",photon_drla);
 t1->SetBranchAddress("photon_drla2",photon_drla2);
 t1->SetBranchAddress("photon_sieie",photon_sieie);
 t1->SetBranchAddress("photon_chiso",photon_chiso);
 t1->SetBranchAddress("photon_pt",photon_pt);
 

 gStyle->SetOptStat(0);
 gStyle->SetPadGridX(1);
 gStyle->SetPadGridY(1);
 gStyle->SetPadTickX(1);
 gStyle->SetPadTickY(1);
 gStyle->SetAxisColor(1, "XYZ");
 gStyle->SetStripDecimals(kTRUE);
 gStyle->SetTickLength(0.03, "XYZ");

 Int_t bin=10;
 Double_t xlow= 0.;
 Double_t xhigh= 0.018;
 Double_t lowpt[10] ={25,30,35,40,45,50,60,80,120,25};
 Double_t highpt[10]={30,35,40,45,50,60,80,120,400,400};
 TH1D *h11[10];
 TH1D *h11a[10];
 for(Int_t i=0;i<10;i++){
      h11[i] =new TH1D(Form("h11_%0.f-%0.f",lowpt[i],highpt[i]),Form("chiso<0.441 && %0.f<pt<%0.f",lowpt[i],highpt[i]),bin,0,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
      h11a[i] =new TH1D(Form("h11a_%0.f-%0.f",lowpt[i],highpt[i]),Form("chiso<0.441 && %0.f<pt<%0.f",lowpt[i],highpt[i]),bin,0,xhigh);//Zjets && leding_photon && medium_cut && photon_chiso<1.416
  }
 TH1D *h21=new TH1D("h21","10>chiso>4",bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
 TH1D *h31=new TH1D("h31","",bin,0,xhigh);////Zjets && leding_photon && medium_cut && photon_chiso>2
 bool Zjets[6],Leading_photon[6],medium_cut[6],loose_cut[6];
 Int_t nentries = t1->GetEntries();
 cout<<"nentries = "<<nentries<<endl;
// nentries=1000000;
 vector<double> vector_pt;
 vector<double>::iterator biggest_pt;
 double sieie,chiso;
 int position=0,size,m=0;
 for(Int_t i=0;i<nentries;i++){
    t1->GetEntry(i);
    for(Int_t j=0;j<6;j++){
         Zjets[j] = ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110;
         Leading_photon[j]= photon_drla[j]>0.7 && photon_drla2[j]>0.7;
         medium_cut[j]= photon_hoe[j]<0.0396  && photon_nhiso[j]<2.725 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&abs(photon_eta[j])<1.4442;
         loose_cut[j]= photon_hoe[j]<0.0597  && photon_nhiso[j]<(10.910 + 0.0148*photon_pt[j] + 0.000017*photon_pt[j]*photon_pt[j])*1 && photon_phoiso[j]<(3.63 + 0.0047*photon_pt[j])*1 &&abs(photon_eta[j])<1.4442;
             //&&photon_pt[j]<400.&&photon_pt[j]>120;
         if(Zjets[j]&&Leading_photon[j]&&loose_cut[j]){
            vector_pt.push_back(photon_pt[j]);
            position=j;}
         else {vector_pt.push_back(0);}
      }//fill the vector_pt
   size=vector_pt.size();
   biggest_pt = max_element(begin(vector_pt),end(vector_pt));
   if(*biggest_pt==0){
       vector_pt.clear();
       continue;}
   position = distance( begin(vector_pt), biggest_pt);
//   sieie = photon_sieie[position];
//   chiso = photon_chiso[position];
//   cout<<"i = "<<i<<"  "<<"size = "<<size<<endl;
//   cout<<"the max pt " <<*biggest_pt<<endl<<"position "<<position<<endl<<"sieie "<<sieie<<endl;
// cout<<"photon_sieie"<<photon_sieie[position]<<endl;
// cout<<endl;
   for(Int_t k=0;k<10;k++){
        if( photon_chiso[position]<0.441&&photon_pt[position]<highpt[k]&&photon_pt[position]>lowpt[k]) 
       
             {h11[k]->Fill(photon_sieie[position],scalef);}
      }
    vector_pt.clear();
    for(Int_t j=0;j<6;j++){
      if(Zjets[j]&&Leading_photon[j]&&medium_cut[j]){
            vector_pt.push_back(photon_pt[j]);
            position=j;}
    else {vector_pt.push_back(0);}
      }//fill the vector_pt
   size=vector_pt.size();
   biggest_pt = max_element(begin(vector_pt),end(vector_pt));
   if(*biggest_pt==0){
       vector_pt.clear();
       continue;}
   position = distance( begin(vector_pt), biggest_pt);
//   sieie = photon_sieie[position];
//   chiso = photon_chiso[position];
//   cout<<"i = "<<i<<"  "<<"size = "<<size<<endl;
//   cout<<"the max pt " <<*biggest_pt<<endl<<"position "<<position<<endl<<"sieie "<<sieie<<endl;
// cout<<"photon_sieie"<<photon_sieie[position]<<endl;
// cout<<endl;
   for(Int_t k=0;k<10;k++){
        if( photon_chiso[position]<0.441&&photon_pt[position]<highpt[k]&&photon_pt[position]>lowpt[k]) 
       
             {h11a[k]->Fill(photon_sieie[position],scalef);}
      }
//   if( photon_chiso[position]>4&&photon_chiso[position]<10&&photon_isprompt[position]!=1) 
//     {h21->Fill(photon_sieie[position],scalef);}
//   if(photon_chiso[position]<10&&photon_chiso[position]>4) 
//     {h31->Fill(photon_sieie[position],scalef);}
    vector_pt.clear();
//   m++;
//   if(i==m*100000) {cout<<"i = "<<i<<endl;}
   }  
TCanvas *c1=new TCanvas("c1","Zjets and leading photon",900,600);   
 c1->SetGrid();
 c1->SetFrameFillColor(41);
// c1->SetLogy();
 for(Int_t i=0;i<10;i++){
 h11[i]->SetLineColor(i);
 h11[i]->SetTitle("Barrel Region");
 h11[i]->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
 h11[i]->GetYaxis()->SetTitle("count");
 h11[i]->SetLineStyle(1);
 h11[i]->SetLineWidth(3);
 Double_t s1[i];
    s1[i] =1/h11[i]->Integral();
 cout<<"i = "<<i<<" s1 = "<<s1[i]<<endl;
 h11[i]->Scale(s1[i]);
 h11a[i]->SetLineColor(i+1);
 h11a[i]->SetTitle("Barrel Region");
 h11a[i]->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
 h11a[i]->GetYaxis()->SetTitle("count");
 h11a[i]->SetLineStyle(1);
 h11a[i]->SetLineWidth(3);
 Double_t s1a[i];
    s1a[i] =1/h11a[i]->Integral();
 cout<<"i = "<<i<<" s1 = "<<s1a[i]<<endl;
 h11a[i]->Scale(s1a[i]);
// h11->DrawNormalized("HIST");
// h11->DrawNormalized("HIST");
// h11[i]->DrawNormalized("HIST,SAME");
    }
 h11[8]->DrawNormalized("HIST,SAME");
 h11a[8]->DrawNormalized("HIST,SAME");
// h21->SetLineStyle(2);
// h21->SetLineColor(kRed);
// h21->SetLineWidth(3);
// Double_t s2=1/h21->Integral();
// cout<<"s2 = "<<s2<<endl;
// h21->Scale(s2);
// h21->DrawNormalized("HIST,SAME");
// h21->Draw("HIST,SAME");

// h31->SetLineStyle(3);
// h31->SetLineColor(kGreen);
// h31->SetLineWidth(3);
// Double_t s3=1/h31->Integral();
// cout<<"s3 = "<<s2<<endl;
// h31->Scale(s3);
// h31->DrawNormalized("HIST,SAME");
// h31->Draw("HIST,SAME");
 TLegend *l1 = new TLegend(0.2,0.4,0.4,0.9);
// for(Int_t i=0;i<10;i++){
    l1->AddEntry(h11[8],Form("%0.f<pt<%0.f mediumID",lowpt[8],highpt[8])); 
//   }
 TLegend *l2 = new TLegend(0.7,0.4,0.9,0.9);
// for(Int_t i=0;i<10;i++){
    l2->AddEntry(h11a[8],Form("%0.f<pt<%0.f looseID",lowpt[8],highpt[8])); 
//   }
// l1->AddEntry(h21,"4<photon_chiso<10  Fake #gamma isprompt!=1" );
// l1->AddEntry(h31,"photon_chiso<0.441 Fake #gamma" );
 l1->Draw(); 
 l2->Draw(); 
 c1->Print("./sieie_"+b+".eps");
 c1->Print("./sieie_"+b+".C");


}
