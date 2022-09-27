#define ee_cxx
#include <iostream>
#include "ee.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#define Pi 3.1415926535
using namespace std;
void ee::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   np = fChain->GetEntries("theWeight>0.");
   nm = fChain->GetEntries("theWeight<0.");
   Long64_t nbytes = 0, nb = 0;
   bool flag=false;
   Bool_t PHOTON,LEPele,LEPmu;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      setValue();
      // if (Cut(ientry) < 0) continue;
//      cout<<"enter into the Loop"<<endl;
	      for(int i=0;i<jet1pt_unc_up->size();i++){
//                      cout<<"fill vector"<<endl;
		      TLorentzVector photonp4;
		      photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		      TLorentzVector j1p4_up,j1p4_down;
		      j1p4_up.SetPtEtaPhiE( jet1pt_unc_up->at(i), jet1eta_unc_up->at(i), jet1phi_unc_up->at(i), jet1e_unc_up->at(i));
		      j1p4_down.SetPtEtaPhiE(jet1pt_unc_down->at(i), jet1eta_unc_down->at(i), jet1phi_unc_down->at(i), jet1e_unc_down->at(i));
		      TLorentzVector j2p4_up,j2p4_down;
		      j2p4_up.SetPtEtaPhiE(  jet2pt_unc_up->at(i), jet2eta_unc_up->at(i), jet2phi_unc_up->at(i), jet2e_unc_up->at(i));
		      j2p4_down.SetPtEtaPhiE(jet2pt_unc_down->at(i), jet2eta_unc_down->at(i), jet2phi_unc_down->at(i), jet2e_unc_down->at(i));
		      TLorentzVector vp4;
		      vp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
//                      cout<<"define LorenzVector"<<endl;
		      drj1a_up[i]=delta_R(jet1eta_unc_up->at(i),jet1phi_unc_up->at(i),photoneta,photonphi);
//                      cout<<"calulate dr"<<endl;
		      drj1a_down[i]=delta_R(jet1eta_unc_down->at(i),jet1phi_unc_down->at(i),photoneta,photonphi);
		      drj2a_up[i]=delta_R(jet2eta_unc_up->at(i),jet2phi_unc_up->at(i),photoneta,photonphi);
		      drj2a_down[i]=delta_R(jet2eta_unc_down->at(i),jet2phi_unc_down->at(i),photoneta,photonphi);

		      drj1l1_up[i]=delta_R(jet1eta_unc_up->at(i),jet1phi_unc_up->at(i),etalep1,philep1);
		      drj1l1_down[i]=delta_R(jet1eta_unc_down->at(i),jet1phi_unc_down->at(i),etalep1,philep1);
		      drj1l2_up[i]=delta_R(jet1eta_unc_up->at(i),jet1phi_unc_up->at(i),etalep2,philep2);
		      drj1l2_down[i]=delta_R(jet1eta_unc_down->at(i),jet1phi_unc_down->at(i),etalep2,philep2);

		      drj2l1_up[i]=delta_R(jet2eta_unc_up->at(i),jet2phi_unc_up->at(i),etalep1,philep1);
		      drj2l1_down[i]=delta_R(jet2eta_unc_down->at(i),jet2phi_unc_down->at(i),etalep1,philep1);
		      drj2l2_up[i]=delta_R(jet2eta_unc_up->at(i),jet2phi_unc_up->at(i),etalep2,philep2);
		      drj2l2_down[i]=delta_R(jet2eta_unc_down->at(i),jet2phi_unc_down->at(i),etalep2,philep2);
//                      cout<<"calulate dr"<<endl;

		      zepp_up[i]=fabs((vp4+photonp4).Rapidity() - (j1p4_up.Rapidity() + j2p4_up.Rapidity())/ 2.0);   
		      zepp_down[i]=fabs((vp4+photonp4).Rapidity() - (j1p4_down.Rapidity() + j2p4_down.Rapidity())/ 2.0);   
		      Mjj_up[i] = (j1p4_up + j2p4_up).M();
		      Mjj_down[i] = (j1p4_down + j2p4_down).M();
		      detajj_up[i]=fabs(jet1eta_unc_up->at(i) - jet2eta_unc_up->at(i)); 
		      detajj_down[i]=fabs(jet1eta_unc_down->at(i) - jet2eta_unc_down->at(i)); 
                      delta_phi_up[i]=fabs((vp4+photonp4).Phi()-(j1p4_up+j2p4_up).Phi());
                      delta_phi_down[i]=fabs((vp4+photonp4).Phi()-(j1p4_down+j2p4_down).Phi());
		      if (fabs(jet1phi_unc_up->at(i)-jet2phi_unc_up->at(i))>Pi) drjj_up[i] = sqrt((jet1eta_unc_up->at(i)-jet2eta_unc_up->at(i))*(jet1eta_unc_up->at(i)-jet2eta_unc_up->at(i))+(2*Pi-fabs(jet1phi_unc_up->at(i)-jet2phi_unc_up->at(i)))*(2*Pi-fabs(jet1phi_unc_up->at(i)-jet2phi_unc_up->at(i))));
		      else drjj_up[i] = sqrt((jet1eta_unc_up->at(i)-jet2eta_unc_up->at(i))*(jet1eta_unc_up->at(i)-jet2eta_unc_up->at(i))+(fabs(jet1phi_unc_up->at(i)-jet2phi_unc_up->at(i)))*(fabs(jet1phi_unc_up->at(i)-jet2phi_unc_up->at(i))));
		      if (fabs(jet1phi_unc_down->at(i)-jet2phi_unc_down->at(i))>Pi) drjj_down[i] = sqrt((jet1eta_unc_down->at(i)-jet2eta_unc_down->at(i))*(jet1eta_unc_down->at(i)-jet2eta_unc_down->at(i))+(2*Pi-fabs(jet1phi_unc_down->at(i)-jet2phi_unc_down->at(i)))*(2*Pi-fabs(jet1phi_unc_down->at(i)-jet2phi_unc_down->at(i))));
		      else drjj_down[i] = sqrt((jet1eta_unc_down->at(i)-jet2eta_unc_down->at(i))*(jet1eta_unc_down->at(i)-jet2eta_unc_down->at(i))+(fabs(jet1phi_unc_down->at(i)-jet2phi_unc_down->at(i)))*(fabs(jet1phi_unc_down->at(i)-jet2phi_unc_down->at(i))));

//              cout<<"finish one time filling"<<endl;
	      }
      TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
      Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
      photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
      jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
      jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
      delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
      scalef = 1000.*55.49/float(np-nm)*fabs(theWeight)/theWeight;    
      LEPmu = lep==13 && (HLT_Mu2>0 || HLT_Mu1>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
      LEPele = lep==11 && ( HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70.&&massVlep<110;
      PHOTON= photonet>20 && (abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5));

      if(  ((LEPele||LEPmu)&&PHOTON) )
	      ExTree->Fill();
      drj1a_up.clear();       drj1a_down.clear();
      drj2a_up.clear();       drj2a_down.clear();
      drj1l1_up.clear();      drj1l1_down.clear();
      drj1l2_up.clear();      drj1l2_down.clear();
      drj2l1_up.clear();      drj2l1_down.clear();
      drj2l2_up.clear();      drj2l2_down.clear();

      Mjj_up.clear();          Mjj_down.clear();
      zepp_up.clear();         zepp_down.clear();
      drjj_up.clear();         drjj_down.clear();
      detajj_up.clear();       detajj_down.clear();
      delta_phi_up.clear();    delta_phi_down.clear();
   }
   
}
Double_t ee::delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{
        Double_t dp = phi1-phi2;
        if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
        Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
//        cout<<"run dr function"<<endl;
        return dr;
}
void ee::setValue(){
	for(int i=0;i<jet1pt_unc_up->size();i++){
		drj1a_up.push_back(-10);       drj1a_down.push_back(-10);
		drj2a_up.push_back(-10);       drj2a_down.push_back(-10);
		drj1l1_up.push_back(-10);      drj1l1_down.push_back(-10);
		drj1l2_up.push_back(-10);      drj1l2_down.push_back(-10);
		drj2l1_up.push_back(-10);      drj2l1_down.push_back(-10);
		drj2l2_up.push_back(-10);      drj2l2_down.push_back(-10);
              
                Mjj_up.push_back(-10);          Mjj_down.push_back(-10);
                zepp_up.push_back(-10);         zepp_down.push_back(-10);
                drjj_up.push_back(-10);         drjj_down.push_back(-10);
                detajj_up.push_back(-10);       detajj_down.push_back(-10);
                delta_phi_up.push_back(-10);    delta_phi_down.push_back(-10);
	}


}
