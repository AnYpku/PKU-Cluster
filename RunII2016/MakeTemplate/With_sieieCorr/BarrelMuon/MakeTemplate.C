#define MakeTemplate_cxx
#include "MakeTemplate.h"
#include <TH2.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include "ele_channel_scale.C"
#define Pi 3.1415926
//#include <fiostream>
using namespace std;
void MakeTemplate::Loop(TString name,TGraph* gr)
{
   if (fChain == 0) return;
   ResetVal();   
   histo();
   TFile* fout = new TFile("./"+name+".root", "RECREATE");
   TTree* ExTree = fChain->CloneTree(0);
//   style();
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   Int_t jet=0;   
//   nentries = 100000;
   int count=0;
   bool jet_flag;
   double Mchiso = 10.19;
   double chisomax=13,chisomin=8;//8~13
   double actualWeight;
   TFile* ID_photon_file = TFile::Open("./ele_SFs/Fall17V2_2016_Medium_photons.root");
   TH2F* ID_photon=0;
   ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
   cout<<"open the photon ID file: 2016_PhotonsMedium.root"<<endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   if(jentry%1000000==0) cout<<jentry<<"; "<<nentries<<endl;
	   LEP = lep==13 && (HLT_Mu1>0|| HLT_Mu2>0)  && ptlep1 > 20. && ptlep2 > 20.&& abs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110;// && drla>0.7;
	   for(Int_t j=0;j<6;j++){
		   if(photon_pt[j]>400) photon_pt[j]=399;
		   Photon_cut[j]= photon_pev[j]==1 && /*photon_pevnew[j]==1 &&*/ photon_hoe[j]<0.02197 && photon_nhiso[j]<1.189 + 0.01512*photon_pt[j]+0.00002259*photon_pt[j]*photon_pt[j] && photon_phoiso[j]<2.08 + 0.004017*photon_pt[j]&&fabs(photon_eta[j])<1.4442&&photon_pt[j]>20&&photon_pt[j]<400&&photon_drla[j]>0.7&&photon_drla[j]!=10&&photon_drla2[j]>0.7&&photon_drla2[j]!=10; 
		   if(Photon_cut[j]&&LEP){
			   vector_pt.push_back(photon_pt[j]);}
		   else {vector_pt.push_back(0);}
	   }//fill the vector_pt
	   size=vector_pt.size();
	   biggest_pt = max_element(begin(vector_pt),end(vector_pt));
	   if(*biggest_pt==0){
		   vector_pt.clear();
		   continue;
	   }
	   ExTree->Fill();
	   count++;
	   position = distance( begin(vector_pt), biggest_pt);
	   if(count%1000==0) cout<<"jentry "<<jentry<<"; the biggest pt"<<*biggest_pt<<"; position = "<<position<<endl;
	   //    cout<<"the biggest pt"<<*biggest_pt<<endl;

	   for(Int_t k=0;k<num;k++){
		   if(name.Contains("A")==1){
			   photon_id_scale=get_photon_ID(photon_eta[position],photon_pt[position],ID_photon);
                        if(fabs(photoneta)<1.4442) photon_veto_scale=0.9938;
                        if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.9875;
			   actualWeight = scalef*prefWeight*pileupWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*photon_id_scale*photon_veto_scale;
			   double sieie=gr->Eval(photon_sieie[position]);
			   if(photon_isprompt[position]==1 && photon_chiso[position]<1.141 && photon_pt[position]<highpt[k] && photon_pt[position]>lowpt[k])
			   { h1[k]->Fill(sieie,actualWeight);m1[k]++;

				   if(photon_sieie[position]<0.01015)
				   { hsieie[k]->Fill(sieie,actualWeight);}
			   }//true
			   if(photon_chiso[position]>chisomin && photon_chiso[position]<chisomax && photon_pt[position]<highpt[k] &&
					   photon_pt[position]>lowpt[k] && photon_isprompt[position]==1 )
			   {
				   h4[k]->Fill(sieie,actualWeight);
				   //if(count%1000==0)cout<<"fake contribution from ZA"<<endl;
			   }//fake contribution from true(ZA)
		   }else{
			   actualWeight=1;
			   if(photon_chiso[position]>chisomin && photon_chiso[position]<chisomax && photon_pt[position]<highpt[k] && photon_pt[position]>lowpt[k])
			   { h2[k]->Fill(photon_sieie[position],actualWeight);m2[k]++;}//fake

			   if(photon_chiso[position]<1.141 && photon_pt[position]<highpt[k] && photon_pt[position]>lowpt[k])
			   { h3[k]->Fill(photon_sieie[position],actualWeight);
				   m3[k]++;}//data
		   }
	   }
	   vector_pt.clear();
   }
   ID_photon_file->Close();
   fout->cd();
   ExTree->Write();
   fout->Close();
   cout<<"count = "<<count<<endl;
   for(Int_t i=0;i<num;i++){
	   cout<<Form(" %0.f<photonet<%0.f",lowpt[i],highpt[i])<< "  True template m1["<<i<<"] = "<<m1[i]<<endl;
	   cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  Fake template m2["<<i<<"] = "<<m2[i]<<endl;
	   cout<<Form(" %0.f<photon_pt<%0.f",lowpt[i],highpt[i])<<"  Data template m3["<<i<<"] = "<<m3[i]<<endl;
	   if(name.Contains("A")==1){
		   ofstream myfile_true(Form("./txt/truenumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]),ios::out);
		   myfile_true<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m1[i]<<"\t"<<TrueNumber[i]<<endl;
	   }
	   if(name.Contains("Data")==1){   
		   ofstream myfile_fake(Form("./txt/fakenumber_pt%0.f-%0.f.txt",lowpt[i],highpt[i]),ios::out);
		   myfile_fake<<lowpt[i]<<"\t"<<highpt[i]<<"\t"<<m2[i]<<"\t"<<FakeNumber[i]<<endl;
	   }
   } 

   if(name.Contains("A")==1){
	   f1= new TFile("./root/True_template-"+name+".root","recreate");
	   for(Int_t i=0;i<num;i++){h1[i]->Write();h4[i]->Write();/*hsieie[i]->Write();*/}
	   f1->Close();
   }
   if(name.Contains("D")==1){
	   f2= new TFile("./root/Fake_template-"+name+".root","recreate");
	   for(Int_t i=0;i<num;i++){h2[i]->Write();}
	   f2->Close();

	   f3 = new TFile("./root/Data_template-"+name+".root","recreate");
	   for(Int_t i=0;i<num;i++){h3[i]->Write();}
	   f3->Close();
   }
}

void MakeTemplate::style(){
	gStyle->SetOptStat(0);
	gStyle->SetPadGridX(1);
	gStyle->SetPadGridY(1);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetAxisColor(1, "XYZ");
	gStyle->SetStripDecimals(kTRUE);
	gStyle->SetTickLength(0.03, "XYZ");
}

void MakeTemplate::histo(){
	bin=34;
	xlow= 0.00515;
	xhigh= 0.02215;
	for(Int_t i=0;i<num;i++){
		h1[i]=new TH1D(Form("h1_pt%0.f_%0.f",lowpt[i],highpt[i]),"true template",bin,xlow,xhigh);
		h2[i]=new TH1D(Form("h2_pt%0.f_%0.f",lowpt[i],highpt[i]),"fake template",bin,xlow,xhigh);
		h3[i]=new TH1D(Form("h3_pt%0.f_%0.f",lowpt[i],highpt[i]),"data template",bin,xlow,xhigh);
		hsieie[i]=new TH1D(Form("hsieie_pt%0.f_%0.f",lowpt[i],highpt[i]),"real template",bin,xlow,xhigh);
		h4[i]=new TH1D(Form("h4_pt%0.f_%0.f",lowpt[i],highpt[i]),"fake contribution from ZA",bin,xlow,xhigh);

	}
}

void MakeTemplate::draw(TCanvas *c,TH1D *h1,TH1D *h2,TH1D *h3,Double_t ptlow,Double_t pthigh){
	c=new TCanvas("c","Zjets and leading photon",900,600);
	c->SetGrid();
	// c->SetLogy();
	h1->SetLineColor(51);
	h1->SetTitle(Form("Barrel Region  %0.f < photon PT <% 0.f",ptlow,pthigh));
	h1->GetXaxis()->SetTitle("#sigma_{i#eta i#eta}");
	h1->GetYaxis()->SetTitle("count");
	h1->SetLineStyle(1);
	h1->SetLineWidth(3);
	h1->SetFillColor(51);
	h1->SetFillStyle(3002);
	s1=1/h1->Integral();
	cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
	cout<<"s1 = "<<s1<<endl;
	h2->SetLineColor(2);
	// h1->Scale(s1);
	h2->SetLineStyle(2);
	h2->SetLineWidth(3);
	s2=1/h2->Integral();
	cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
	cout<<"  s2 = "<<s2<<endl;
	// h2[i]->Draw("HIST,SAME");
	// h2->Scale(s2);
	//   }
	h3->SetLineStyle(3);
	Int_t ci=ci = TColor::GetColor("#3399ff");
	h3->SetLineColor(ci);
	h3->SetFillColor(ci);
	h3->SetFillStyle(3008);
	h3->SetLineWidth(3);
	s3=1/h3->Integral();
	cout<<Form(" %0.f<photon_pt<%0.f ",ptlow,pthigh);
	cout<<"s3 = "<<s3<<endl;
	// h3->Scale(s3);
	// h1->DrawNormalized("HIST");
	// h2->DrawNormalized("HIST,SAME");
	// h3->DrawNormalized("HIST,SAME");
	h1->Draw("HIST");
	h2->Draw("HIST,SAME");
	h3->Draw("HIST,SAME");
	TLegend *l1 = new TLegend(0.5,0.6,0.9,0.9);
	l1->AddEntry(h1,"true template" );
	l1->AddEntry(h2,"Fake #gamma" );
	l1->AddEntry(h3,"data template");
	l1->Draw();
	delete c;
	delete h1;
	delete h2;
	delete h3;
	}
void MakeTemplate::ResetVal(){

	//   lowpt[7] ={25,30,35,40,50,65,100};
	//   highpt[7]={30,35,40,50,65,100,400};
	bin=34;
	xlow= 0.00515;
	xhigh= 0.02215;
	for(Int_t i=0;i<num;i++){
		m1[i]=0;
		m2[i]=0;
		m3[i]=0;
		TrueNumber[i]=0;
		FakeNumber[i]=0;
	}
	position=0,size=0,m=0;
} 
double MakeTemplate::delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2){
	Double_t dp = phi1-phi2;
	if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
	Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
	return dr;
}
