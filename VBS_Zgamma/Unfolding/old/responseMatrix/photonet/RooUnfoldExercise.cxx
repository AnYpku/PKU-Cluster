//==============================================================================
//Code template for the RooUnfold practical at the Advanced Scientific Computing
//Workshop, ETH Zurich, 15.7.2014
//
//Produced by Mikael Kuusela starting from RooUnfoldExample.cxx by Tim Adye
//and Fergus Wilson
//==============================================================================

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldTUnfold.h"
#include "RooUnfoldInvert.h"
#endif

// Smear x by additive zero-mean Gaussian noise with standard deviation sigmaSmear
Double_t smear(Double_t x)
{
  const Double_t sigmaSmear = 0.2;
  return x + gRandom->Gaus(0,sigmaSmear);
}

// Compute the chi2 statistic between hy and hMuHat = K * hLambdaHat
Double_t chi2smeared(TH1D* hLambdaHat, TH1D* hy, RooUnfoldResponse* K)
{
  TH1D* hMuHat = new TH1D("muHat", "", 40, -7.0, 7.0);
  hMuHat = (TH1D*) K->ApplyToTruth(hLambdaHat);

  Double_t chi2 = 0;
  for (Int_t i=1; i<=40; i++) {
    chi2 += 1.0/hMuHat->GetBinContent(i) * pow(hy->GetBinContent(i) - hMuHat->GetBinContent(i),2);
  }

  delete hMuHat;
  
  return chi2;
}


void RooUnfoldExercise()
{
#ifdef __CINT__
  // Load the RooUnfold shared library
  gSystem->Load("libRooUnfold");
#endif

  // Fix the random seed
  gRandom->SetSeed(123456);

  // Initialize the response matrix
  RooUnfoldResponse K(40,-7.0,7.0,40,-7.0, 7.0);

  TH1D* hLambda = new TH1D("lambda", "", 40, -7.0, 7.0); // True mean
  TH1D* hMu = new TH1D("mu", "", 40, -7.0, 7.0); // Smeared mean
  TH1D* hEff = new TH1D("eff", "", 40, -7.0, 7.0); // Efficiency, needed for plotting the response matrix

  // Fill the response matrix, hLambda and hMu by simulating a large number
  // of observations from the actual true distribution
  for (Int_t i = 0; i<1000000; i++) {
    Double_t u = gRandom->Uniform();
    Double_t x;
    if (u <= 0.2) {
      x = gRandom->Uniform(14.0) - 7.0;
    } else if (u <= 0.5) {
      x = gRandom->Gaus(-2.0,1.0);
    } else {
      x = gRandom->Gaus(2.0,1.0);
    }
    hLambda->Fill(x);
    Double_t y = smear(x);
    hMu->Fill(y);
    K.Fill(y,x);
    if (y >= -7.0 && y <= 7.0) {
      hEff->Fill(x);
    }
  }
  hEff->Divide(hLambda);
  hLambda->Scale(1.0/50.0); // Scale to match the observations
  hMu->Scale(1.0/50.0); // Scale to match the observations

  // Plot the response matrix
  TCanvas* c1 = new TCanvas("c1");
  TH2D* hResponse = (TH2D*) K.HresponseNoOverflow();
  TH1D* hProjY = hResponse->ProjectionY();
  for (Int_t i = 1; i <= 40; i++) {
    for (Int_t j = 1; j <= 40; j++) {
      // Normalize each row to sum up to the efficiency
      hResponse->SetBinContent(i,j,hEff->GetBinContent(j)*hResponse->GetBinContent(i,j)/hProjY->GetBinContent(j));
    }
  }
  hResponse->SetTitle("Response matrix;Detector level;Particle level");
  hResponse->SetStats(kFALSE);
  hResponse->Draw("colz");


  // Fill an alternative response matrix with a MC spectrum that differs
  // from the actual truth
  RooUnfoldResponse KAlt(40,-7.0,7.0,40,-7.0,7.0);

  for (Int_t i = 0; i<1000000; i++) {
    Double_t u = gRandom->Uniform();
    Double_t x;
    if (u <= 0.2) {
      x = gRandom->Uniform(14.0) - 7.0;
    } else if (u <= 0.5) {
      x = gRandom->Gaus(-4.0, 1.0);
      //x = gRandom->Gaus(-1.9, 1.1);
    } else {
      x = gRandom->Gaus(4.0, 1.0);
      //x = gRandom->Gaus(2.1,0.9);
    }
    Double_t y = smear(x);
    KAlt.Fill(y, x);
  }
  

  // Simulate the data to be unfolded
  TH1D* hx = new TH1D ("x", "", 40, -7.0, 7.0); // True observations
  TH1D* hy = new TH1D ("y", "", 40, -7.0, 7.0); // Smeared observations

  Int_t Nx = gRandom->Poisson(20000);
  for (Int_t i=0; i<Nx; i++) {
    Double_t u = gRandom->Uniform();
    Double_t x;
    if (u <= 0.2) {
      x = gRandom->Uniform(14.0) - 7.0;
    } else if (u <= 0.5) {
      x = gRandom->Gaus(-2.0, 1.0);
    } else {
      x = gRandom->Gaus(2.0,1.0);
    }
    Double_t y = smear(x);
    hx->Fill(x);
    hy->Fill(y);
  }

  // Unfold
  RooUnfoldInvert  unfoldInv(&K, hy);

  TH1D* hLambdaHatInv = (TH1D*) unfoldInv.Hreco();

  // Draw data
  TCanvas* c2 = new TCanvas("c2");
  TLegend* legendData = new TLegend(0.15,0.6,0.4,0.85);

  hLambda->SetStats(kFALSE);
  hLambda->SetLineColor(6); // Magenta
  hLambda->Draw();
  legendData->AddEntry(hLambda,"Lambda","l");

  hx->SetLineColor(8); // Light green
  hx->Draw("SAME");
  legendData->AddEntry(hx,"x","l");

  hMu->SetLineColor(2); // Red
  hMu->Draw("SAME");
  legendData->AddEntry(hMu,"Mu","l");

  hy->SetLineColor(1); // Black
  hy->Draw("SAME");
  legendData->AddEntry(hy,"y","l");

  legendData->Draw();

  // Draw unfolded histograms
  TCanvas* c3 = new TCanvas("c3");
  TLegend* legendUnfolded = new TLegend(0.15,0.6,0.4,0.85);

  hLambda->SetStats(kFALSE);
  hLambda->SetLineColor(6); // Magenta
  hLambda->Draw();
  legendUnfolded->AddEntry(hLambda,"Lambda","l");

  hLambdaHatInv->SetLineColor(15); // Gray
  hLambdaHatInv->Draw("SAME");
  legendUnfolded->AddEntry(hLambdaHatInv,"Inversion","l");

  legendUnfolded->Draw();  
}

#ifndef __CINT__
int main () { RooUnfoldExercise(); return 0; }  // Main program when run stand-alone
#endif
