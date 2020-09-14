{
//=========Macro generated from canvas: c01/
//=========  (Sun Sep 16 06:23:14 2018) by ROOT version5.34/18
   TCanvas *c01 = new TCanvas("c01", "",0,0,700,500);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c01->Range(-45.18072,-3.049638,1581.325,1.76581);
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
   Mstack->SetMaximum(20.16901);
   Double_t xAxis1[6] = {150, 400, 600, 800, 1000, 1500}; 
   
   TH1F *Mstack_stack_1 = new TH1F("Mstack_stack_1","",5, xAxis1);
   Mstack_stack_1->SetMinimum(0.003770252);
   Mstack_stack_1->SetMaximum(33.49946);
   Mstack_stack_1->SetDirectory(0);
   Mstack_stack_1->SetStats(0);
   Mstack_stack_1->SetLineStyle(0);
   Mstack_stack_1->SetMarkerStyle(20);
   Mstack_stack_1->GetXaxis()->SetTitle("ZGmass (GeV) ");
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
   
   Double_t xAxis2[6] = {150, 400, 600, 800, 1000, 1500}; 
   
   TH1D *ZG_optimal_bkg_nominal = new TH1D("ZG_optimal_bkg_nominal"," ",5, xAxis2);
   ZG_optimal_bkg_nominal->SetBinContent(1,0.4783515);
   ZG_optimal_bkg_nominal->SetBinContent(2,0.3147173);
   ZG_optimal_bkg_nominal->SetBinContent(3,0.03942728);
   ZG_optimal_bkg_nominal->SetBinContent(4,-0.0333875);
   ZG_optimal_bkg_nominal->SetBinError(1,0.1953055);
   ZG_optimal_bkg_nominal->SetBinError(2,0.1136414);
   ZG_optimal_bkg_nominal->SetBinError(3,0.05515853);
   ZG_optimal_bkg_nominal->SetBinError(4,0.0333875);
   ZG_optimal_bkg_nominal->SetEntries(78);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#00cc00");
   ZG_optimal_bkg_nominal->SetFillColor(ci);

   ci = TColor::GetColor("#00cc00");
   ZG_optimal_bkg_nominal->SetLineColor(ci);

   ci = TColor::GetColor("#00cc00");
   ZG_optimal_bkg_nominal->SetMarkerColor(ci);
   ZG_optimal_bkg_nominal->GetXaxis()->SetLabelFont(42);
   ZG_optimal_bkg_nominal->GetXaxis()->SetLabelSize(0.035);
   ZG_optimal_bkg_nominal->GetXaxis()->SetTitleSize(0.035);
   ZG_optimal_bkg_nominal->GetXaxis()->SetTitleFont(42);
   ZG_optimal_bkg_nominal->GetYaxis()->SetLabelFont(42);
   ZG_optimal_bkg_nominal->GetYaxis()->SetLabelSize(0.035);
   ZG_optimal_bkg_nominal->GetYaxis()->SetTitleSize(0.035);
   ZG_optimal_bkg_nominal->GetYaxis()->SetTitleFont(42);
   ZG_optimal_bkg_nominal->GetZaxis()->SetLabelFont(42);
   ZG_optimal_bkg_nominal->GetZaxis()->SetLabelSize(0.035);
   ZG_optimal_bkg_nominal->GetZaxis()->SetTitleSize(0.035);
   ZG_optimal_bkg_nominal->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ZG_optimal_bkg_nominal,"");
   Double_t xAxis3[6] = {150, 400, 600, 800, 1000, 1500}; 
   
   TH1D *ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal = new TH1D("ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal"," ",5, xAxis3);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinContent(1,0.59873);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinContent(2,0.336789);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinError(1,0.3003272);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinError(2,0.336789);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetEntries(6);

   ci = TColor::GetColor("#cc00ff");
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetFillColor(ci);

   ci = TColor::GetColor("#cc00ff");
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetLineColor(ci);

   ci = TColor::GetColor("#cc00ff");
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetMarkerColor(ci);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetLabelFont(42);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetLabelSize(0.035);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetTitleSize(0.035);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetTitleFont(42);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetLabelFont(42);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetLabelSize(0.035);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetTitleSize(0.035);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetTitleFont(42);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetLabelFont(42);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetLabelSize(0.035);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetTitleSize(0.035);
   ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal,"");
   Double_t xAxis4[6] = {150, 400, 600, 800, 1000, 1500}; 
   
   TH1D *ZG_optimal_outZA_EWK_nominal = new TH1D("ZG_optimal_outZA_EWK_nominal"," ",5, xAxis4);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(0,0.01222695);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(1,3.965172);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(2,1.874342);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(3,0.8447222);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(4,0.2530481);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(5,0.2738496);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(6,0.03950186);
   ZG_optimal_outZA_EWK_nominal->SetBinError(0,0.01222695);
   ZG_optimal_outZA_EWK_nominal->SetBinError(1,0.2252204);
   ZG_optimal_outZA_EWK_nominal->SetBinError(2,0.1572361);
   ZG_optimal_outZA_EWK_nominal->SetBinError(3,0.1046872);
   ZG_optimal_outZA_EWK_nominal->SetBinError(4,0.05825729);
   ZG_optimal_outZA_EWK_nominal->SetBinError(5,0.05922007);
   ZG_optimal_outZA_EWK_nominal->SetBinError(6,0.02287495);
   ZG_optimal_outZA_EWK_nominal->SetEntries(588);

   ci = TColor::GetColor("#ffff00");
   ZG_optimal_outZA_EWK_nominal->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   ZG_optimal_outZA_EWK_nominal->SetLineColor(ci);

   ci = TColor::GetColor("#ffff00");
   ZG_optimal_outZA_EWK_nominal->SetMarkerColor(ci);
   ZG_optimal_outZA_EWK_nominal->SetMarkerStyle(21);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelFont(42);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleFont(42);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelFont(42);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleFont(42);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelFont(42);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ZG_optimal_outZA_EWK_nominal,"");
   Mstack->Draw("bar hist");
   Double_t xAxis5[6] = {150, 400, 600, 800, 1000, 1500}; 
   
   TH1D *ZG_optimal_outZA_EWK_nominal = new TH1D("ZG_optimal_outZA_EWK_nominal"," ",5, xAxis5);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(0,0.01222695);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(1,5.047277);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(2,2.559484);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(3,0.9213143);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(4,0.2755834);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(5,1.326088);
   ZG_optimal_outZA_EWK_nominal->SetBinContent(6,0.03950186);
   ZG_optimal_outZA_EWK_nominal->SetBinError(0,0.01222695);
   ZG_optimal_outZA_EWK_nominal->SetBinError(1,0.4231606);
   ZG_optimal_outZA_EWK_nominal->SetBinError(2,0.38867);
   ZG_optimal_outZA_EWK_nominal->SetBinError(3,0.1183295);
   ZG_optimal_outZA_EWK_nominal->SetBinError(4,0.06714639);
   ZG_optimal_outZA_EWK_nominal->SetBinError(5,0.05922007);
   ZG_optimal_outZA_EWK_nominal->SetBinError(6,0.02287495);
   ZG_optimal_outZA_EWK_nominal->SetEntries(677);

   ci = TColor::GetColor("#ff0000");
   ZG_optimal_outZA_EWK_nominal->SetLineColor(ci);
   ZG_optimal_outZA_EWK_nominal->SetLineWidth(2);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelFont(42);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetLabelSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetXaxis()->SetTitleFont(42);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelFont(42);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetLabelSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetYaxis()->SetTitleFont(42);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelFont(42);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetLabelSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleSize(0.035);
   ZG_optimal_outZA_EWK_nominal->GetZaxis()->SetTitleFont(42);
   ZG_optimal_outZA_EWK_nominal->Draw("hist same");
   Double_t xAxis6[6] = {150, 400, 600, 800, 1000, 1500}; 
   
   TH1D *ZG_optimal_outDEle_nominal = new TH1D("ZG_optimal_outDEle_nominal"," ",5, xAxis6);
   ZG_optimal_outDEle_nominal->SetBinContent(1,11);
   ZG_optimal_outDEle_nominal->SetBinContent(2,13);
   ZG_optimal_outDEle_nominal->SetBinContent(3,1);
   ZG_optimal_outDEle_nominal->SetBinContent(4,1);
   ZG_optimal_outDEle_nominal->SetBinContent(5,1);
   ZG_optimal_outDEle_nominal->SetBinError(1,3.316625);
   ZG_optimal_outDEle_nominal->SetBinError(2,3.605551);
   ZG_optimal_outDEle_nominal->SetBinError(3,1);
   ZG_optimal_outDEle_nominal->SetBinError(4,1);
   ZG_optimal_outDEle_nominal->SetBinError(5,1);
   ZG_optimal_outDEle_nominal->SetEntries(28);
   ZG_optimal_outDEle_nominal->SetFillColor(1);

   ci = TColor::GetColor("#000099");
   ZG_optimal_outDEle_nominal->SetLineColor(ci);
   ZG_optimal_outDEle_nominal->SetMarkerStyle(20);
   ZG_optimal_outDEle_nominal->SetMarkerSize(1.3);
   ZG_optimal_outDEle_nominal->GetXaxis()->SetLabelFont(42);
   ZG_optimal_outDEle_nominal->GetXaxis()->SetLabelSize(0.035);
   ZG_optimal_outDEle_nominal->GetXaxis()->SetTitleSize(0.035);
   ZG_optimal_outDEle_nominal->GetXaxis()->SetTitleFont(42);
   ZG_optimal_outDEle_nominal->GetYaxis()->SetLabelFont(42);
   ZG_optimal_outDEle_nominal->GetYaxis()->SetLabelSize(0.035);
   ZG_optimal_outDEle_nominal->GetYaxis()->SetTitleSize(0.035);
   ZG_optimal_outDEle_nominal->GetYaxis()->SetTitleFont(42);
   ZG_optimal_outDEle_nominal->GetZaxis()->SetLabelFont(42);
   ZG_optimal_outDEle_nominal->GetZaxis()->SetLabelSize(0.035);
   ZG_optimal_outDEle_nominal->GetZaxis()->SetTitleSize(0.035);
   ZG_optimal_outDEle_nominal->GetZaxis()->SetTitleFont(42);
   ZG_optimal_outDEle_nominal->Draw("hist P0 same");
   
   TLegend *leg = new TLegend(0.5,0.78,0.65,0.91,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ZG_optimal_outDEle_nominal","data","EP");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.3);
   entry->SetTextFont(62);
   entry=leg->AddEntry("ZG_optimal_outZA_EWK_nominal","VBS ZA","f");

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
   entry=leg->AddEntry("ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal","JFP","f");

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
   entry=leg->AddEntry("ZG_optimal_bkg_nominal","Other Bkg","f");

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
   entry=leg->AddEntry("ZG_optimal_outZA_EWK_nominal","fT0=-0.5e-12","l");

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
      tex = new TLatex(0.76,0.96,"35.866 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
   c01->Modified();
   c01->cd();
   c01->SetSelected(c01);
}
