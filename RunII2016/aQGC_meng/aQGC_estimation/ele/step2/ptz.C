{
//=========Macro generated from canvas: c01/
//=========  (Wed May 23 04:38:03 2018) by ROOT version5.34/18
   TCanvas *c01 = new TCanvas("c01", "",0,0,700,500);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c01->Range(42.16867,-3.005945,524.0964,1.579589);
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
   Mstack->SetMaximum(13.76342);
   Double_t xAxis1[8] = {100, 140, 180, 220, 260, 300, 400, 500}; 
   
   TH1F *Mstack_stack_1 = new TH1F("Mstack_stack_1","",7, xAxis1);
   Mstack_stack_1->SetMinimum(0.003892015);
   Mstack_stack_1->SetMaximum(22.40334);
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
   ptz_optimal_bkg_nominal->SetBinContent(0,5.74872);
   ptz_optimal_bkg_nominal->SetBinContent(1,1.917304);
   ptz_optimal_bkg_nominal->SetBinContent(2,1.223464);
   ptz_optimal_bkg_nominal->SetBinContent(3,1.271228);
   ptz_optimal_bkg_nominal->SetBinContent(4,1.002891);
   ptz_optimal_bkg_nominal->SetBinContent(5,0.8949246);
   ptz_optimal_bkg_nominal->SetBinContent(6,0.9022714);
   ptz_optimal_bkg_nominal->SetBinContent(7,0.03363489);
   ptz_optimal_bkg_nominal->SetBinContent(8,-0.1985399);
   ptz_optimal_bkg_nominal->SetBinError(0,0.8874411);
   ptz_optimal_bkg_nominal->SetBinError(1,0.5560464);
   ptz_optimal_bkg_nominal->SetBinError(2,0.5414991);
   ptz_optimal_bkg_nominal->SetBinError(3,0.4526656);
   ptz_optimal_bkg_nominal->SetBinError(4,0.3917714);
   ptz_optimal_bkg_nominal->SetBinError(5,0.3845817);
   ptz_optimal_bkg_nominal->SetBinError(6,0.3799808);
   ptz_optimal_bkg_nominal->SetBinError(7,0.2375956);
   ptz_optimal_bkg_nominal->SetBinError(8,0.1427988);
   ptz_optimal_bkg_nominal->SetEntries(297);

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
   
   TH1D *ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal = new TH1D("ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal"," ",7, xAxis3);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinContent(0,0.393258);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinContent(1,0.589281);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinContent(2,0.196629);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinError(0,0.2780754);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinError(1,0.4391339);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetBinError(2,0.196629);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetEntries(6);

   ci = TColor::GetColor("#cc00ff");
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetFillColor(ci);

   ci = TColor::GetColor("#cc00ff");
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetLineColor(ci);

   ci = TColor::GetColor("#cc00ff");
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->SetMarkerColor(ci);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetLabelFont(42);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetLabelSize(0.035);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetTitleSize(0.035);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetXaxis()->SetTitleFont(42);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetLabelFont(42);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetLabelSize(0.035);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetTitleSize(0.035);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetYaxis()->SetTitleFont(42);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetLabelFont(42);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetLabelSize(0.035);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetTitleSize(0.035);
   ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal,"");
   Double_t xAxis4[8] = {100, 140, 180, 220, 260, 300, 400, 500}; 
   
   TH1D *ptz_optimal_outZA_EWK_nominal = new TH1D("ptz_optimal_outZA_EWK_nominal"," ",7, xAxis4);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(0,2.174135);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(1,0.9342694);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(2,0.7651055);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(3,0.742316);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(4,0.3445346);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(5,0.3426129);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(6,0.4503006);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(7,0.3656103);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(8,0.1269371);
   ptz_optimal_outZA_EWK_nominal->SetBinError(0,0.1674595);
   ptz_optimal_outZA_EWK_nominal->SetBinError(1,0.1108718);
   ptz_optimal_outZA_EWK_nominal->SetBinError(2,0.1007658);
   ptz_optimal_outZA_EWK_nominal->SetBinError(3,0.1001712);
   ptz_optimal_outZA_EWK_nominal->SetBinError(4,0.06709997);
   ptz_optimal_outZA_EWK_nominal->SetBinError(5,0.06749862);
   ptz_optimal_outZA_EWK_nominal->SetBinError(6,0.07707021);
   ptz_optimal_outZA_EWK_nominal->SetBinError(7,0.07083929);
   ptz_optimal_outZA_EWK_nominal->SetBinError(8,0.04060769);
   ptz_optimal_outZA_EWK_nominal->SetEntries(490);

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
   ptz_optimal_outZA_EWK_nominal->SetBinContent(0,8.316114);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(1,3.425989);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(2,2.178437);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(3,2.021846);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(4,1.338831);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(5,1.255127);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(6,1.384606);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(7,0.5564949);
   ptz_optimal_outZA_EWK_nominal->SetBinContent(8,-0.07160278);
   ptz_optimal_outZA_EWK_nominal->SetBinError(0,0.9449446);
   ptz_optimal_outZA_EWK_nominal->SetBinError(1,0.7171601);
   ptz_optimal_outZA_EWK_nominal->SetBinError(2,0.5848401);
   ptz_optimal_outZA_EWK_nominal->SetBinError(3,0.4636167);
   ptz_optimal_outZA_EWK_nominal->SetBinError(4,0.3974761);
   ptz_optimal_outZA_EWK_nominal->SetBinError(5,0.3904602);
   ptz_optimal_outZA_EWK_nominal->SetBinError(6,0.387718);
   ptz_optimal_outZA_EWK_nominal->SetBinError(7,0.2479312);
   ptz_optimal_outZA_EWK_nominal->SetBinError(8,0.1484604);
   ptz_optimal_outZA_EWK_nominal->SetEntries(800);

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
   entry=leg->AddEntry("ptz_optimal_outphotonlikejet_ele_mediumlikephoton_nominal","JFP","f");

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
      tex = new TLatex(0.76,0.96,"35.866 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
   c01->Modified();
   c01->cd();
   c01->SetSelected(c01);
}
