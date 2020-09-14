{
//=========Macro generated from canvas: c01/
//=========  (Wed May 23 04:16:52 2018) by ROOT version5.34/18
   TCanvas *c01 = new TCanvas("c01", "",0,0,700,500);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c01->Range(42.16867,-3.060358,524.0964,1.811816);
   c01->SetFillColor(0);
   c01->SetBorderMode(0);
   c01->SetBorderSize(2);
   c01->SetLogy();
   c01->SetTickx(1);
   c01->SetTicky(1);
   c01->SetLeftMargin(0.12);
   c01->SetRightMargin(0.05);
   c01->SetTopMargin(0.05);
   c01->SetBottomMargin(0.13);
   c01->SetFrameFillStyle(0);
   c01->SetFrameBorderMode(0);
   c01->SetFrameFillStyle(0);
   c01->SetFrameBorderMode(0);
   
   THStack *Mstack = new THStack();
   Mstack->SetName("Mstack");
   Mstack->SetTitle("");
   Mstack->SetMinimum(0.01);
   Mstack->SetMaximum(22.16735);
   Double_t xAxis1[8] = {100, 140, 180, 220, 260, 300, 400, 500}; 
   
   TH1F *Mstack_stack_1 = new TH1F("Mstack_stack_1","",7, xAxis1);
   Mstack_stack_1->SetMinimum(0.003741315);
   Mstack_stack_1->SetMaximum(37.00047);
   Mstack_stack_1->SetDirectory(0);
   Mstack_stack_1->SetStats(0);
   Mstack_stack_1->SetLineStyle(0);
   Mstack_stack_1->SetMarkerStyle(20);
   Mstack_stack_1->GetXaxis()->SetTitle("pT_{Z} (GeV) ");
   Mstack_stack_1->GetXaxis()->SetLabelFont(42);
   Mstack_stack_1->GetXaxis()->SetLabelOffset(0.007);
   Mstack_stack_1->GetXaxis()->SetLabelSize(0.05);
   Mstack_stack_1->GetXaxis()->SetTitleOffset(1.5);
   Mstack_stack_1->GetXaxis()->SetTitleFont(42);
   Mstack_stack_1->GetYaxis()->SetTitle("Events /bin");
   Mstack_stack_1->GetYaxis()->SetLabelFont(42);
   Mstack_stack_1->GetYaxis()->SetLabelOffset(0.007);
   Mstack_stack_1->GetYaxis()->SetLabelSize(0.05);
   Mstack_stack_1->GetYaxis()->SetTitleOffset(1.25);
   Mstack_stack_1->GetYaxis()->SetTitleFont(42);
   Mstack_stack_1->GetZaxis()->SetLabelFont(42);
   Mstack_stack_1->GetZaxis()->SetLabelOffset(0.007);
   Mstack_stack_1->GetZaxis()->SetLabelSize(0.05);
   Mstack_stack_1->GetZaxis()->SetTitleSize(0.06);
   Mstack_stack_1->GetZaxis()->SetTitleFont(42);
   Mstack->SetHistogram(Mstack_stack_1);
   
   Double_t xAxis2[8] = {100, 140, 180, 220, 260, 300, 400, 500}; 
   
   TH1D *ptz_optimal_bkg_nominal = new TH1D("ptz_optimal_bkg_nominal"," ",7, xAxis2);
   ptz_optimal_bkg_nominal->SetBinContent(0,6.244523);
   ptz_optimal_bkg_nominal->SetBinContent(1,3.910705);
   ptz_optimal_bkg_nominal->SetBinContent(2,2.071728);
   ptz_optimal_bkg_nominal->SetBinContent(3,1.425073);
   ptz_optimal_bkg_nominal->SetBinContent(4,1.526159);
   ptz_optimal_bkg_nominal->SetBinContent(5,0.864622);
   ptz_optimal_bkg_nominal->SetBinContent(6,0.01523058);
   ptz_optimal_bkg_nominal->SetBinContent(7,0.818449);
   ptz_optimal_bkg_nominal->SetBinContent(8,0.5554703);
   ptz_optimal_bkg_nominal->SetBinError(0,0.9399809);
   ptz_optimal_bkg_nominal->SetBinError(1,0.7010053);
   ptz_optimal_bkg_nominal->SetBinError(2,0.5026691);
   ptz_optimal_bkg_nominal->SetBinError(3,0.4805242);
   ptz_optimal_bkg_nominal->SetBinError(4,0.5770016);
   ptz_optimal_bkg_nominal->SetBinError(5,0.3321932);
   ptz_optimal_bkg_nominal->SetBinError(6,0.3508716);
   ptz_optimal_bkg_nominal->SetBinError(7,0.3779923);
   ptz_optimal_bkg_nominal->SetBinError(8,0.2630955);
   ptz_optimal_bkg_nominal->SetEntries(459);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#00cc00");
   ptz_optimal_bkg_nominal->SetFillColor(ci);

   ci = TColor::GetColor("#00cc00");
   ptz_optimal_bkg_nominal->SetLineColor(ci);

   ci = TColor::GetColor("#00cc00");
   ptz_optimal_bkg_nominal->SetMarkerColor(ci);
   ptz_optimal_bkg_nominal->GetXaxis()->SetLabelFont(42);
   ptz_optimal_bkg_nominal->GetXaxis()->SetLabelSize(0.035);
   ptz_optimal_bkg_nominal->GetXaxis()->SetTitleSize(0.035);
   ptz_optimal_bkg_nominal->GetXaxis()->SetTitleFont(42);
   ptz_optimal_bkg_nominal->GetYaxis()->SetLabelFont(42);
   ptz_optimal_bkg_nominal->GetYaxis()->SetLabelSize(0.035);
   ptz_optimal_bkg_nominal->GetYaxis()->SetTitleSize(0.035);
   ptz_optimal_bkg_nominal->GetYaxis()->SetTitleFont(42);
   ptz_optimal_bkg_nominal->GetZaxis()->SetLabelFont(42);
   ptz_optimal_bkg_nominal->GetZaxis()->SetLabelSize(0.035);
   ptz_optimal_bkg_nominal->GetZaxis()->SetTitleSize(0.035);
   ptz_optimal_bkg_nominal->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ptz_optimal_bkg_nominal,"");
   Double_t xAxis3[8] = {100, 140, 180, 220, 260, 300, 400, 500}; 
   
   TH1D *ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal = new TH1D("ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal"," ",7, xAxis3);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetBinContent(0,0.712713);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetBinContent(1,0.27969);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetBinContent(3,0.116375);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetBinError(0,0.4498929);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetBinError(1,0.2005366);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetBinError(3,0.116375);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetEntries(7);

   ci = TColor::GetColor("#cc00ff");
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetFillColor(ci);

   ci = TColor::GetColor("#cc00ff");
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetLineColor(ci);

   ci = TColor::GetColor("#cc00ff");
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->SetMarkerColor(ci);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetXaxis()->SetLabelFont(42);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetXaxis()->SetLabelSize(0.035);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetXaxis()->SetTitleSize(0.035);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetXaxis()->SetTitleFont(42);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetYaxis()->SetLabelFont(42);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetYaxis()->SetLabelSize(0.035);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetYaxis()->SetTitleSize(0.035);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetYaxis()->SetTitleFont(42);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetZaxis()->SetLabelFont(42);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetZaxis()->SetLabelSize(0.035);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetZaxis()->SetTitleSize(0.035);
   ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal,"");
   Double_t xAxis4[8] = {100, 140, 180, 220, 260, 300, 400, 500}; 
   
   TH1D *ptz_optimal_outZA_EWK_nominal = new TH1D("ptz_optimal_outZA_EWK_nominal"," ",7, xAxis4);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(0,3.522566);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(1,1.351442);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(2,1.102116);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(3,0.6251654);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(4,0.5171147);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(5,0.339714);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(6,0.6179123);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(7,0.2455175);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(8,0.09415395);
   ptz_optimal_outZA_EWK_nominal->SetBinError(0,0.2144917);
   ptz_optimal_outZA_EWK_nominal->SetBinError(1,0.1337115);
   ptz_optimal_outZA_EWK_nominal->SetBinError(2,0.119635);
   ptz_optimal_outZA_EWK_nominal->SetBinError(3,0.09101707);
   ptz_optimal_outZA_EWK_nominal->SetBinError(4,0.08284812);
   ptz_optimal_outZA_EWK_nominal->SetBinError(5,0.06629047);
   ptz_optimal_outZA_EWK_nominal->SetBinError(6,0.09017617);
   ptz_optimal_outZA_EWK_nominal->SetBinError(7,0.05785412);
   ptz_optimal_outZA_EWK_nominal->SetBinError(8,0.03561232);
   ptz_optimal_outZA_EWK_nominal->SetEntries(700);

   ci = TColor::GetColor("#ffff00");
   ptz_optimal_outZA_EWK_nominal->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   ptz_optimal_outZA_EWK_nominal->SetLineColor(ci);

   ci = TColor::GetColor("#ffff00");
   ptz_optimal_outZA_EWK_nominal->SetMarkerColor(ci);
   ptz_optimal_outZA_EWK_nominal->SetMarkerStyle(21);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelFont(42);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleFont(42);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelFont(42);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleFont(42);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelFont(42);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ptz_optimal_outZA_EWK_nominal,"");
   Mstack->Draw("bar hist");
   Double_t xAxis5[8] = {100, 140, 180, 220, 260, 300, 400, 500}; 
   
   TH1D *ptz_optimal_outZA_EWK_nominal = new TH1D("ptz_optimal_outZA_EWK_nominal"," ",7, xAxis5);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(0,10.4798);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(1,5.525669);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(2,3.188409);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(3,2.152423);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(4,2.047729);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(5,1.186989);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(6,0.6208044);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(7,2.132448);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(8,0.6496243);
   ptz_optimal_outZA_EWK_nominal->SetBinError(0,1.063943);
   ptz_optimal_outZA_EWK_nominal->SetBinError(1,0.7412841);
   ptz_optimal_outZA_EWK_nominal->SetBinError(2,0.5167095);
   ptz_optimal_outZA_EWK_nominal->SetBinError(3,0.5027234);
   ptz_optimal_outZA_EWK_nominal->SetBinError(4,0.582919);
   ptz_optimal_outZA_EWK_nominal->SetBinError(5,0.3387429);
   ptz_optimal_outZA_EWK_nominal->SetBinError(6,0.3622742);
   ptz_optimal_outZA_EWK_nominal->SetBinError(7,0.3823941);
   ptz_optimal_outZA_EWK_nominal->SetBinError(8,0.2654948);
   ptz_optimal_outZA_EWK_nominal->SetEntries(1173);

   ci = TColor::GetColor("#ff0000");
   ptz_optimal_outZA_EWK_nominal->SetLineColor(ci);
   ptz_optimal_outZA_EWK_nominal->SetLineWidth(2);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelFont(42);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleFont(42);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelFont(42);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleFont(42);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelFont(42);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleSize(0.035);
   ptz_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleFont(42);
   ptz_optimal_outZA_EWK_nominal->Draw("hist same");
   
   TLegend *leg = new TLegend(0.5,0.78,0.65,0.91,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ptz_optimal_outZA_EWK_nominal","VBS ZA","f");

   ci = TColor::GetColor("#ffff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("ptz_optimal_outphotonlikejet_mu_mediumlikephoton_nominal","JFP","f");

   ci = TColor::GetColor("#cc00ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#cc00ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("ptz_optimal_bkg_nominal","Other Bkg","f");

   ci = TColor::GetColor("#00cc00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00cc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("ptz_optimal_outZA_EWK_nominal","fM0=-10e-12","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   TLatex *   tex = new TLatex(0.21,0.84,"Preliminary");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.21,0.88,"CMS");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.76,0.96,"35.862 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
   c01->Modified();
   c01->cd();
   c01->SetSelected(c01);
}
