#define xx_cxx
#include <algorithm>
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
using namespace std;

void xx::Loop(TString name)
{
//   In a ROOT session, you can do:
//      root> .L xx.C
//      root> xx t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   TFile* input1 = new TFile ("puweight.root");
   TH1* h = NULL;
   input1->GetObject("h2",h);

   if(name.Contains("WA")){
      f1 = new TFile("./rootfiles/waMC_template.root","recreate") ;} 
   if(name.Contains("SMu")){
      f1 = new TFile("./rootfiles/waData_template.root","recreate") ;} 
   for(Int_t i=0;i<ptnumber;i++){
      if(name.Contains("WA")){
           h_mcwa[i]=new TH1F(Form("hmcwa_pt%0.f-%0.f",lowpt[i],highpt[i]),"MC WA",bin,0,xhigh);
           h_mcFc[i]=new TH1F(Form("hmcFc_pt%0.f-%0.f",lowpt[i],highpt[i]),"fake template contamination",bin,0,xhigh);
           h_mcwaT[i]=new TH1F(Form("hmcwaT_pt%0.f-%0.f",lowpt[i],highpt[i]),"True template from WA mc ",bin,0,xhigh);
          fmcwa[i] = new TFile(Form("./rootfiles/fmcwa_%0.f_%0.f.root",lowpt[i],highpt[i]), "RECREATE"); 
	  tree_mcwa[i] = new TTree("tree_mcwa","tree_mcwa");
	  tree_mcwa[i]->Branch("sieie",&Sieie_wa);}
      if(name.Contains("SMu")){
           h_datawa[i]=new TH1F(Form("hdatawa_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,0,xhigh);
           h_sieie[i]=new TH1F(Form("hsieie_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,0,xhigh);
           h_waFc[i]=new TH1F(Form("hwaFc_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,0,xhigh);
           h_waFs[i]=new TH1F(Form("hwaFs_pt%0.f-%0.f",lowpt[i],highpt[i]),"data template",bin,0,xhigh);
          fdata[i] = new TFile(Form("./rootfiles/fdata_%0.f_%0.f.root",lowpt[i],highpt[i]), "RECREATE"); 
	  tree_datawa[i] = new TTree("tree_datawa","tree_datawa");
	  tree_datawa[i]->Branch("sieie",&Sieie_wa);}
   }
   //nentries=100;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

     // scalef = 1000.*178.6/(59408914-15166663)*fabs(theWeight)/theWeight;
     //pileupWeight=h->GetBinContent(h->GetXaxis()->FindBin(npT));
     //AddWeight(); 

      LEP = lep==13 && nlooseeles==0 && nloosemus<2 && HLT_Mu2==1 && 
            mtVlepJECnew>30. && ptlep1>25 && fabs(etalep1)<2.4 && MET_et>30;
      if(jentry%10000000==0) 
              {cout<<jentry<<"; "<<nentries<<endl;
	      cout<<"pileupWeight = "<<pileupWeight<<endl;
	      cout<<"scalef = "<<scalef<<endl;}
      if(LEP==false) continue;
      // if (Cut(ientry) < 0) continue;
      for(Int_t j=0;j<6;j++){
          Photon_cut[j]= photon_pev[j]==1  && 
                        photon_hoe[j]<0.0396 &&/* photon_chiso[j]<0.441 &&*/
			photon_nhiso[j]<2.725+0.0148*photon_pt[j]+0.000017*pow(photon_pt[j],2) &&
			photon_phoiso[j]<2.571 + 0.0047*photon_pt[j]&&
			abs(photon_eta[j])<1.4442;
          if(Photon_cut[j]&&LEP){
             vector_pt.push_back(photon_pt[j]);}
	  else {vector_pt.push_back(0);}
       }//fill the vector_pt
      size=vector_pt.size();
      biggest_pt = max_element(begin(vector_pt),end(vector_pt));
      if(*biggest_pt==0){
        vector_pt.clear();
        continue;}
      ExTree->Fill();
      position = distance( begin(vector_pt), biggest_pt);
      Sieie_wa=photon_sieie[position];
      if(jentry%10000==0){
          cout<<jentry<<"; the biggest pt = "<<*biggest_pt<<"; the position = "<<position<<endl;
      }
      actualWeight=scalef*pileupWeight*lumiWeight*35.857;
      for(Int_t k=0;k<ptnumber;k++){
        if( photon_drla[position]>0.4){
            if(name.Contains("WA") &&
               photon_pt[position]>lowpt[k]&&photon_pt[position]<highpt[k])
               {
		   if(photon_chiso[position]<0.441){
			   h_mcwa[k]->Fill(photon_sieie[position],actualWeight);
			   fmcwa[k]->cd();
			   tree_mcwa[k]->Fill(); 
		   }
		   if( photon_chiso[position]<10 && photon_chiso[position]>4 && photon_isprompt[position]==2 ){
                      h_mcFc[k]->Fill(photon_sieie[position],actualWeight);
		   }
		   if( photon_chiso[position]<0.441 && photon_isprompt[position]==2 ){
                      h_mcwaT[k]->Fill(photon_sieie[position],actualWeight);
		   }
	       }
            if(name.Contains("SMu") && 
               photon_pt[position]>lowpt[k]&&photon_pt[position]<highpt[k])
               {
		   if(photon_chiso[position]<0.441)
		   {       h_datawa[k]->Fill(photon_sieie[position]);
			   fdata[k]->cd();
			   tree_datawa[k]->Fill(); 
		   }
                   if(photon_chiso[position]<0.441 && photon_sieie[position]<0.01022){
                      h_sieie[k]->Fill(photon_sieie[position]);}
                   if(photon_chiso[position]<10&&photon_chiso[position]>4){
                      h_waFc[k]->Fill(photon_sieie[position]);}
                   if(photon_sieie[position]>0.012&&photon_sieie[position]<0.2){
                      h_waFs[k]->Fill(photon_chiso[position]);}
               }
        }//end if
      }//end for loop
      vector_pt.clear();
    }//end for the biggest loop
if(name.Contains("WA")){
   for(Int_t i=0;i<ptnumber;i++){f1->cd();h_mcwa[i]->Write();h_mcFc[i]->Write();h_mcwaT[i]->Write();}
 }
if(name.Contains("SMu")){
   for(Int_t i=0;i<ptnumber;i++){f1->cd();h_datawa[i]->Write();h_sieie[i]->Write();h_waFc[i]->Write();h_waFs[i]->Write();}
 }
input1->Close();
   
}
void xx::AddWeight(){

//===============SF=================//
         if(photonet>10 && photonet<200)
	     {if(fabs(photoneta)>0 && fabs(photoneta)<1.4442){scalef=scalef*0.9978;}
              if(fabs(photoneta)>1.566 && fabs(photoneta)<2.5){scalef=scalef*0.9931;}
	     }
//////////////////photon medium ID scalefactor
	 if(photonet>20 && photonet<35)
		{if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.939;}
	         if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.955;}
		 if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*0.974;}
		 if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.963;}
		 if(photoneta>0 && photoneta<0.8){scalef=scalef*0.966;}
		 if(photoneta>0.8 && photoneta<1.444){scalef=scalef*0.978;}
		 if(photoneta>1.566 && photoneta<2){scalef=scalef*0.95;}
		 if(photoneta>2 && photoneta<2.5){scalef=scalef*0.934;}
		}
	 if(photonet>35 && photonet<50)
		{if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.955;}
	         if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.971;}
		 if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*0.974;}
		 if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.961;}
		 if(photoneta>0 && photoneta<0.8){scalef=scalef*0.97;}
		 if(photoneta>0.8 && photoneta<1.444){scalef=scalef*0.977;}
		 if(photoneta>1.566 && photoneta<2){scalef=scalef*0.971;}
		 if(photoneta>2 && photoneta<2.5){scalef=scalef*0.96;}
		}
	 if(photonet>50 && photonet<90)
		{if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.961;}
		 if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.969;}
		 if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*0.97;}
		 if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.953;}
		 if(photoneta>0 && photoneta<0.8){scalef=scalef*0.958;}
		 if(photoneta>0.8 && photoneta<1.444){scalef=scalef*0.968;}
		 if(photoneta>1.566 && photoneta<2){scalef=scalef*0.966;}
		 if(photoneta>2 && photoneta<2.5){scalef=scalef*0.96;}
		}
	 if(photonet>90 && photonet<500)
	        {if(photoneta>-2.5 && photoneta<-2){scalef=scalef*0.972;}
	         if(photoneta>-2 && photoneta<-1.566){scalef=scalef*0.996;}
		 if(photoneta>-1.444 && photoneta<-0.8){scalef=scalef*1.022;}
		 if(photoneta>-0.8 && photoneta<0){scalef=scalef*0.992;}
		 if(photoneta>0 && photoneta<0.8){scalef=scalef*1;}
		 if(photoneta>0.8 && photoneta<1.444){scalef=scalef*1.019;}
		 if(photoneta>1.566 && photoneta<2){scalef=scalef*0.993;}
		 if(photoneta>2 && photoneta<2.5){scalef=scalef*1.02;}
		}
	double bf=0.54976;   double gh=0.45024;
	if(lep==13)
	{
//////////////////////muon tracking scalefactor
		if(fabs(etalep1)<0.20000004){scalef=scalef*0.9969965;}
                if(fabs(etalep1)>0.20000004 && fabs(etalep1)<0.40000002){scalef=scalef*0.9977118;}
                if(fabs(etalep1)>0.40000002 && fabs(etalep1)<0.59999999){scalef=scalef*0.9980776;}
                if(fabs(etalep1)>0.59999999 && fabs(etalep1)<0.80000004){scalef=scalef*0.9978039;}
                if(fabs(etalep1)>0.80000004 && fabs(etalep1)<1.00000003){scalef=scalef*0.9979708;}
                if(fabs(etalep1)>1.00000003 && fabs(etalep1)<1.20000008){scalef=scalef*0.9971477;}
                if(fabs(etalep1)>1.20000008 && fabs(etalep1)<1.40000008){scalef=scalef*0.9962274;}
                if(fabs(etalep1)>1.40000008 && fabs(etalep1)<1.60000003){scalef=scalef*0.9954786;}
                if(fabs(etalep1)>1.60000003 && fabs(etalep1)<1.80000004){scalef=scalef*0.9957808;}
                if(fabs(etalep1)>1.80000004 && fabs(etalep1)<2.00000004){scalef=scalef*0.9938919;}
                if(fabs(etalep1)>2.00000004 && fabs(etalep1)<2.20000001){scalef=scalef*0.9929427;}
                if(fabs(etalep1)>2.20000001 && fabs(etalep1)<2.4){scalef=scalef*0.9873133;}
	}

//////////////////////muon trigger scalefactor
	if(ptlep1>26 && ptlep1<30)
            {if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.97493*bf+0.986981*gh);}
             if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.951008*bf+0.96284*gh);}
	     if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.981343*bf+0.98392*gh);}
	     if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.899932*bf+0.913885*gh);}
	    }
	if(ptlep1>30 && ptlep1<40)
	    {if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.9784*bf+0.991048*gh);}
	     if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.961095*bf+0.971896*gh);}
	     if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.994604*bf+0.99655*gh);}
	     if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.941213*bf+0.948634*gh);}
	    }
	if(ptlep1>40 && ptlep1<50)
	    {if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.978602*bf+0.992596*gh);}
             if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.962331*bf+0.974604*gh);}
	     if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.996797*bf+1.00213*gh);}
	     if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.953082*bf+0.962964*gh);}
	    }
	if(ptlep1>50 && ptlep1<60)
	   {
	     if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.979472*bf+0.992018*gh);}
	     if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.962257*bf+0.975398*gh);}
	     if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.996425*bf+1.00241*gh);}
	     if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.954931*bf+0.967069*gh);}
	   }
	if(ptlep1>60 && ptlep1<120)
           {  
             if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.976239*bf+0.993243*gh);}
	     if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.959941*bf+0.970948*gh);}
	     if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.995473*bf+1.00316*gh);}
	     if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.943909*bf+0.962784*gh);}
	   }
	if(ptlep1>120 && ptlep1<200)
	   { 
             if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.971637*bf+0.981393*gh);}
	     if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.940402*bf+0.954439*gh);}
	     if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(1.00587*bf+1.00509*gh);}
	     if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.972007*bf+0.983115*gh);}
	   }
	if(ptlep1>200 && ptlep1<500)
           {
		if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.974591*bf+0.993894*gh);}
		if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.927055*bf+0.977128*gh);}
		if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.970003*bf+0.998426*gh);}
		if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.903481*bf+0.935949*gh);}
	   }
//////////////////////muon tight ID  and tight ISO scalefactor
	if(ptlep1>20 && ptlep1<25)
	  {
		if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.980779*bf+0.993173*gh)*(0.987723*bf+0.981144*gh);}
		if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.961656*bf+0.985596*gh)*(0.993162*bf+0.997662*gh);}
		if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.982584*bf+0.990863*gh)*(0.989717*bf+0.993687*gh);}
		if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.970229*bf+0.981501*gh)*(0.975341*bf+0.994233*gh);}
	  }	
	if(ptlep1>25 && ptlep1<30)
	  {
		if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.979747*bf+0.98699*gh)*(0.993733*bf+0.992791*gh);}
		if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.959323*bf+0.984686*gh)*(1.001*bf+0.999726*gh);}
		if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.982259*bf+0.990917*gh)*(0.994223*bf+0.99796*gh);}
		if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.969708*bf+0.979109)*(0.985961*bf+0.999098*gh);}
	  }
	if(ptlep1>30 && ptlep1<40)
	  {
		if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.981756*bf+0.987596*gh)*(0.994052*bf+0.993452*gh);}
		if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.965162*bf+0.983914*gh)*(0.999295*bf+0.999598*gh);}
		if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.984453*bf+0.992066*gh)*(0.997134*bf+0.99898*gh);}
		if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.967787*bf+0.971526*gh)*(0.993083*bf+1.00006*gh);}
	  }
	if(ptlep1>40 && ptlep1<50)
	  {
		if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.982723*bf+0.989777*gh)*(0.995378*bf+0.9952*gh);}
		if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.967988*bf+0.983265*gh)*(0.997179*bf+0.998324*gh);}
		if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.987816*bf+0.993847*gh)*(0.997531*bf+0.998603*gh);}
		if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.97077*bf+0.974776)*(0.99677*bf+1.00022*gh);}
	  }
	if(ptlep1>50 && ptlep1<60)
	  {
		if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.979586*bf+0.984749*gh)*(0.996878*bf+0.996716*gh);}
		if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.969637*bf+0.980582*gh)*(0.999354*bf+0.998887*gh);}
		if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.985261*bf+0.985655*gh)*(0.997972*bf+0.9988*gh);}
		if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.967764*bf+0.967651*gh)*(0.997456*bf+1*gh);}
	  }
	if(ptlep1>60 && ptlep1<120)
	  {
		if(fabs(etalep1)>0 && fabs(etalep1)<0.9){scalef=scalef*(0.992805*bf+0.99137*gh)*(0.998548*bf+0.999064*gh);}
		if(fabs(etalep1)>0.9 && fabs(etalep1)<1.2){scalef=scalef*(0.967575*bf+0.983879*gh)*(0.999297*bf+0.998908*gh);}
		if(fabs(etalep1)>1.2 && fabs(etalep1)<2.1){scalef=scalef*(0.988935*bf+0.989594*gh)*(0.999017*bf+0.999453*gh);}
		if(fabs(etalep1)>2.1 && fabs(etalep1)<2.4){scalef=scalef*(0.963107*bf+0.963199*gh)*(1.00152*bf+1.00153*gh);}
	  }	
//===============SF=================//
}
