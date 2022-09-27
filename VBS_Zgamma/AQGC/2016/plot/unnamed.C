void unnamed()
{
//=========Macro generated from canvas: c01/
//=========  (Wed Jan 15 15:52:58 2020) by ROOT version6.10/09
   TCanvas *c01 = new TCanvas("c01", "",0,23,800,600);
   gStyle->SetOptStat(0);
   c01->Range(0,0,1,1);
   c01->SetFillColor(0);
   c01->SetBorderMode(0);
   c01->SetBorderSize(2);
   c01->SetLogy();
   c01->SetTickx(1);
   c01->SetTicky(1);
   c01->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "pad1",0,0,0.99,0.99);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-81.25002,-1.891539,2231.25,2.882123);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLogy();
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameBorderMode(0);
   
   THStack *Mstack = new THStack();
   Mstack->SetName("Mstack");
   Mstack->SetTitle("");
   Mstack->SetMinimum(0.1);
   Mstack->SetMaximum(155.0317);
   Double_t xAxis8[6] = {150, 400, 600, 800, 1000, 2000}; 
   
   TH1F *Mstack_stack_1_stack_2 = new TH1F("Mstack_stack_1_stack_2","",5, xAxis8);
   Mstack_stack_1_stack_2->SetMinimum(0.03853252);
   Mstack_stack_1_stack_2->SetMaximum(253.9549);
   Mstack_stack_1_stack_2->SetDirectory(0);
   Mstack_stack_1_stack_2->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Mstack_stack_1_stack_2->SetLineColor(ci);
   Mstack_stack_1_stack_2->GetXaxis()->SetTitle("m_{Z#gamma} [GeV] ");
   Mstack_stack_1_stack_2->GetXaxis()->SetLabelFont(42);
   Mstack_stack_1_stack_2->GetXaxis()->SetLabelSize(0.035);
   Mstack_stack_1_stack_2->GetXaxis()->SetTitleSize(0.05);
   Mstack_stack_1_stack_2->GetXaxis()->SetTitleOffset(1.05);
   Mstack_stack_1_stack_2->GetXaxis()->SetTitleFont(42);
   Mstack_stack_1_stack_2->GetYaxis()->SetTitle("Events / bin");
   Mstack_stack_1_stack_2->GetYaxis()->SetLabelFont(42);
   Mstack_stack_1_stack_2->GetYaxis()->SetLabelSize(0.035);
   Mstack_stack_1_stack_2->GetYaxis()->SetTitleSize(0.05);
   Mstack_stack_1_stack_2->GetYaxis()->SetTitleOffset(1.05);
   Mstack_stack_1_stack_2->GetYaxis()->SetTitleFont(42);
   Mstack_stack_1_stack_2->GetZaxis()->SetLabelFont(42);
   Mstack_stack_1_stack_2->GetZaxis()->SetLabelSize(0.035);
   Mstack_stack_1_stack_2->GetZaxis()->SetTitleSize(0.035);
   Mstack_stack_1_stack_2->GetZaxis()->SetTitleFont(42);
   Mstack->SetHistogram(Mstack_stack_1_stack_2);
   
   Double_t xAxis9[6] = {150, 400, 600, 800, 1000, 2000}; 
   
   TH1D *bkg_stack_1_stack_1 = new TH1D("bkg_stack_1_stack_1","th2",5, xAxis9);
   bkg_stack_1_stack_1->SetBinContent(0,-0.01147121);
   bkg_stack_1_stack_1->SetBinContent(1,0.9866493);
   bkg_stack_1_stack_1->SetBinContent(2,0.1997058);
   bkg_stack_1_stack_1->SetBinContent(3,0.01281326);
   bkg_stack_1_stack_1->SetBinContent(4,-0.03706186);
   bkg_stack_1_stack_1->SetBinError(0,0.05839601);
   bkg_stack_1_stack_1->SetBinError(1,0.4392336);
   bkg_stack_1_stack_1->SetBinError(2,0.2115283);
   bkg_stack_1_stack_1->SetBinError(3,0.1310871);
   bkg_stack_1_stack_1->SetBinError(4,0.03706186);
   bkg_stack_1_stack_1->SetEntries(140);

   ci = TColor::GetColor("#00cc00");
   bkg_stack_1_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#00cc00");
   bkg_stack_1_stack_1->SetLineColor(ci);

   ci = TColor::GetColor("#00cc00");
   bkg_stack_1_stack_1->SetMarkerColor(ci);
   bkg_stack_1_stack_1->GetXaxis()->SetLabelFont(42);
   bkg_stack_1_stack_1->GetXaxis()->SetLabelSize(0.035);
   bkg_stack_1_stack_1->GetXaxis()->SetTitleSize(0.035);
   bkg_stack_1_stack_1->GetXaxis()->SetTitleFont(42);
   bkg_stack_1_stack_1->GetYaxis()->SetLabelFont(42);
   bkg_stack_1_stack_1->GetYaxis()->SetLabelSize(0.035);
   bkg_stack_1_stack_1->GetYaxis()->SetTitleSize(0.035);
   bkg_stack_1_stack_1->GetYaxis()->SetTitleFont(42);
   bkg_stack_1_stack_1->GetZaxis()->SetLabelFont(42);
   bkg_stack_1_stack_1->GetZaxis()->SetLabelSize(0.035);
   bkg_stack_1_stack_1->GetZaxis()->SetTitleSize(0.035);
   bkg_stack_1_stack_1->GetZaxis()->SetTitleFont(42);
   Mstack->Add(bkg_stack_1_stack_1,"");
   Double_t xAxis10[6] = {150, 400, 600, 800, 1000, 2000}; 
   
   TH1D *plj_stack_2_stack_2 = new TH1D("plj_stack_2_stack_2","th2",5, xAxis10);
   plj_stack_2_stack_2->SetBinContent(1,4.684913);
   plj_stack_2_stack_2->SetBinContent(2,1.700898);
   plj_stack_2_stack_2->SetBinError(1,1.173691);
   plj_stack_2_stack_2->SetBinError(2,0.6882495);
   plj_stack_2_stack_2->SetEntries(28);
   plj_stack_2_stack_2->SetFillColor(7);
   plj_stack_2_stack_2->SetLineColor(7);
   plj_stack_2_stack_2->SetMarkerColor(7);
   plj_stack_2_stack_2->GetXaxis()->SetLabelFont(42);
   plj_stack_2_stack_2->GetXaxis()->SetLabelSize(0.035);
   plj_stack_2_stack_2->GetXaxis()->SetTitleSize(0.035);
   plj_stack_2_stack_2->GetXaxis()->SetTitleFont(42);
   plj_stack_2_stack_2->GetYaxis()->SetLabelFont(42);
   plj_stack_2_stack_2->GetYaxis()->SetLabelSize(0.035);
   plj_stack_2_stack_2->GetYaxis()->SetTitleSize(0.035);
   plj_stack_2_stack_2->GetYaxis()->SetTitleFont(42);
   plj_stack_2_stack_2->GetZaxis()->SetLabelFont(42);
   plj_stack_2_stack_2->GetZaxis()->SetLabelSize(0.035);
   plj_stack_2_stack_2->GetZaxis()->SetTitleSize(0.035);
   plj_stack_2_stack_2->GetZaxis()->SetTitleFont(42);
   Mstack->Add(plj_stack_2_stack_2,"");
   Double_t xAxis11[6] = {150, 400, 600, 800, 1000, 2000}; 
   
   TH1D *ZA_stack_3_stack_3 = new TH1D("ZA_stack_3_stack_3","th2",5, xAxis11);
   ZA_stack_3_stack_3->SetBinContent(0,0.1041148);
   ZA_stack_3_stack_3->SetBinContent(1,23.20369);
   ZA_stack_3_stack_3->SetBinContent(2,10.81816);
   ZA_stack_3_stack_3->SetBinContent(3,1.700771);
   ZA_stack_3_stack_3->SetBinContent(4,1.65599);
   ZA_stack_3_stack_3->SetBinContent(5,0.2361317);
   ZA_stack_3_stack_3->SetBinError(0,0.1960618);
   ZA_stack_3_stack_3->SetBinError(1,2.101397);
   ZA_stack_3_stack_3->SetBinError(2,1.389007);
   ZA_stack_3_stack_3->SetBinError(3,0.7890389);
   ZA_stack_3_stack_3->SetBinError(4,0.4906755);
   ZA_stack_3_stack_3->SetBinError(5,0.3743953);
   ZA_stack_3_stack_3->SetEntries(686);
   ZA_stack_3_stack_3->SetFillColor(6);
   ZA_stack_3_stack_3->SetLineColor(6);
   ZA_stack_3_stack_3->SetMarkerColor(6);
   ZA_stack_3_stack_3->GetXaxis()->SetLabelFont(42);
   ZA_stack_3_stack_3->GetXaxis()->SetLabelSize(0.035);
   ZA_stack_3_stack_3->GetXaxis()->SetTitleSize(0.035);
   ZA_stack_3_stack_3->GetXaxis()->SetTitleFont(42);
   ZA_stack_3_stack_3->GetYaxis()->SetLabelFont(42);
   ZA_stack_3_stack_3->GetYaxis()->SetLabelSize(0.035);
   ZA_stack_3_stack_3->GetYaxis()->SetTitleSize(0.035);
   ZA_stack_3_stack_3->GetYaxis()->SetTitleFont(42);
   ZA_stack_3_stack_3->GetZaxis()->SetLabelFont(42);
   ZA_stack_3_stack_3->GetZaxis()->SetLabelSize(0.035);
   ZA_stack_3_stack_3->GetZaxis()->SetTitleSize(0.035);
   ZA_stack_3_stack_3->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ZA_stack_3_stack_3,"");
   Double_t xAxis12[6] = {150, 400, 600, 800, 1000, 2000}; 
   
   TH1D *ZA_EWK_stack_4_stack_4 = new TH1D("ZA_EWK_stack_4_stack_4","th2",5, xAxis12);
   ZA_EWK_stack_4_stack_4->SetBinContent(0,0.02973931);
   ZA_EWK_stack_4_stack_4->SetBinContent(1,9.882665);
   ZA_EWK_stack_4_stack_4->SetBinContent(2,4.246045);
   ZA_EWK_stack_4_stack_4->SetBinContent(3,1.709955);
   ZA_EWK_stack_4_stack_4->SetBinContent(4,0.6866337);
   ZA_EWK_stack_4_stack_4->SetBinContent(5,0.5706957);
   ZA_EWK_stack_4_stack_4->SetBinContent(6,0.009543372);
   ZA_EWK_stack_4_stack_4->SetBinError(0,0.0210301);
   ZA_EWK_stack_4_stack_4->SetBinError(1,0.3720796);
   ZA_EWK_stack_4_stack_4->SetBinError(2,0.2443097);
   ZA_EWK_stack_4_stack_4->SetBinError(3,0.154255);
   ZA_EWK_stack_4_stack_4->SetBinError(4,0.09954983);
   ZA_EWK_stack_4_stack_4->SetBinError(5,0.0891719);
   ZA_EWK_stack_4_stack_4->SetBinError(6,0.009543372);
   ZA_EWK_stack_4_stack_4->SetEntries(1351);

   ci = TColor::GetColor("#ffff00");
   ZA_EWK_stack_4_stack_4->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   ZA_EWK_stack_4_stack_4->SetLineColor(ci);

   ci = TColor::GetColor("#ffff00");
   ZA_EWK_stack_4_stack_4->SetMarkerColor(ci);
   ZA_EWK_stack_4_stack_4->SetMarkerStyle(21);
   ZA_EWK_stack_4_stack_4->GetXaxis()->SetLabelFont(42);
   ZA_EWK_stack_4_stack_4->GetXaxis()->SetLabelSize(0.035);
   ZA_EWK_stack_4_stack_4->GetXaxis()->SetTitleSize(0.035);
   ZA_EWK_stack_4_stack_4->GetXaxis()->SetTitleFont(42);
   ZA_EWK_stack_4_stack_4->GetYaxis()->SetLabelFont(42);
   ZA_EWK_stack_4_stack_4->GetYaxis()->SetLabelSize(0.035);
   ZA_EWK_stack_4_stack_4->GetYaxis()->SetTitleSize(0.035);
   ZA_EWK_stack_4_stack_4->GetYaxis()->SetTitleFont(42);
   ZA_EWK_stack_4_stack_4->GetZaxis()->SetLabelFont(42);
   ZA_EWK_stack_4_stack_4->GetZaxis()->SetLabelSize(0.035);
   ZA_EWK_stack_4_stack_4->GetZaxis()->SetTitleSize(0.035);
   ZA_EWK_stack_4_stack_4->GetZaxis()->SetTitleFont(42);
   Mstack->Add(ZA_EWK_stack_4_stack_4,"");
   Mstack->Draw("bar hist");
   
   Double_t Graph0_fx3003[5] = {
   275,
   500,
   700,
   900,
   1500};
   Double_t Graph0_fy3003[5] = {
   38.75792,
   16.96481,
   3.423539,
   2.305562,
   0.8068274};
   Double_t Graph0_felx3003[5] = {
   125,
   100,
   100,
   100,
   500};
   Double_t Graph0_fely3003[5] = {
   2.474831,
   1.583496,
   0.8145925,
   0.5020421,
   0.3848681};
   Double_t Graph0_fehx3003[5] = {
   125,
   100,
   100,
   100,
   500};
   Double_t Graph0_fehy3003[5] = {
   2.474831,
   1.583496,
   0.8145925,
   0.5020421,
   0.3848681};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,Graph0_fx3003,Graph0_fy3003,Graph0_felx3003,Graph0_fehx3003,Graph0_fely3003,Graph0_fehy3003);
   grae->SetName("Graph0");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);
   grae->SetFillStyle(3008);
   
   TH1F *Graph_Graph_Graph30013003 = new TH1F("Graph_Graph_Graph30013003","Graph",100,0,2185);
   Graph_Graph_Graph30013003->SetMinimum(0.3797634);
   Graph_Graph_Graph30013003->SetMaximum(45.31383);
   Graph_Graph_Graph30013003->SetDirectory(0);
   Graph_Graph_Graph30013003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph30013003->SetLineColor(ci);
   Graph_Graph_Graph30013003->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph30013003->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph30013003->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph30013003->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph30013003->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph30013003->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph30013003->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph30013003->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_Graph30013003->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph30013003->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph30013003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph30013003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph30013003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_Graph30013003);
   
   grae->Draw(" 2");
   Double_t xAxis13[6] = {150, 400, 600, 800, 1000, 2000}; 
   
   TH1D *ZA_EWK__3 = new TH1D("ZA_EWK__3","th2",5, xAxis13);
   ZA_EWK__3->SetBinContent(0,0.1223829);
   ZA_EWK__3->SetBinContent(1,38.78021);
   ZA_EWK__3->SetBinContent(2,17.05826);
   ZA_EWK__3->SetBinContent(3,3.598839);
   ZA_EWK__3->SetBinContent(4,2.503052);
   ZA_EWK__3->SetBinContent(5,9.408495);
   ZA_EWK__3->SetBinContent(6,0.009543372);
   ZA_EWK__3->SetBinError(0,0.2056516);
   ZA_EWK__3->SetBinError(1,2.474831);
   ZA_EWK__3->SetBinError(2,1.583496);
   ZA_EWK__3->SetBinError(3,0.8145925);
   ZA_EWK__3->SetBinError(4,0.5020421);
   ZA_EWK__3->SetBinError(5,0.3848681);
   ZA_EWK__3->SetBinError(6,0.009543372);
   ZA_EWK__3->SetEntries(2215);

   ci = TColor::GetColor("#ff0000");
   ZA_EWK__3->SetLineColor(ci);
   ZA_EWK__3->SetLineWidth(2);
   ZA_EWK__3->GetXaxis()->SetLabelFont(42);
   ZA_EWK__3->GetXaxis()->SetLabelSize(0.035);
   ZA_EWK__3->GetXaxis()->SetTitleSize(0.035);
   ZA_EWK__3->GetXaxis()->SetTitleFont(42);
   ZA_EWK__3->GetYaxis()->SetLabelFont(42);
   ZA_EWK__3->GetYaxis()->SetLabelSize(0.035);
   ZA_EWK__3->GetYaxis()->SetTitleSize(0.035);
   ZA_EWK__3->GetYaxis()->SetTitleFont(42);
   ZA_EWK__3->GetZaxis()->SetLabelFont(42);
   ZA_EWK__3->GetZaxis()->SetLabelSize(0.035);
   ZA_EWK__3->GetZaxis()->SetTitleSize(0.035);
   ZA_EWK__3->GetZaxis()->SetTitleFont(42);
   ZA_EWK__3->Draw("hist same");
   Double_t xAxis14[6] = {150, 400, 600, 800, 1000, 2000}; 
   
   TH1D *Muon16__4 = new TH1D("Muon16__4","th2",5, xAxis14);
   Muon16__4->SetBinContent(1,32);
   Muon16__4->SetBinContent(2,17);
   Muon16__4->SetBinContent(3,2);
   Muon16__4->SetBinContent(4,2);
   Muon16__4->SetBinContent(5,3);
   Muon16__4->SetBinError(1,5.656854);
   Muon16__4->SetBinError(2,4.123106);
   Muon16__4->SetBinError(3,1.414214);
   Muon16__4->SetBinError(4,1.414214);
   Muon16__4->SetBinError(5,1.732051);
   Muon16__4->SetEntries(56);
   Muon16__4->SetFillColor(1);

   ci = TColor::GetColor("#000099");
   Muon16__4->SetLineColor(ci);
   Muon16__4->SetMarkerStyle(20);
   Muon16__4->SetMarkerSize(1.3);
   Muon16__4->GetXaxis()->SetLabelFont(42);
   Muon16__4->GetXaxis()->SetLabelSize(0.035);
   Muon16__4->GetXaxis()->SetTitleSize(0.035);
   Muon16__4->GetXaxis()->SetTitleFont(42);
   Muon16__4->GetYaxis()->SetLabelFont(42);
   Muon16__4->GetYaxis()->SetLabelSize(0.035);
   Muon16__4->GetYaxis()->SetTitleSize(0.035);
   Muon16__4->GetYaxis()->SetTitleFont(42);
   Muon16__4->GetZaxis()->SetLabelFont(42);
   Muon16__4->GetZaxis()->SetLabelSize(0.035);
   Muon16__4->GetZaxis()->SetTitleSize(0.035);
   Muon16__4->GetZaxis()->SetTitleFont(42);
   Muon16__4->Draw("hist P0 same");
   
   Double_t Graph_from_Muon16_fx3004[5] = {
   275,
   500,
   700,
   900,
   1500};
   Double_t Graph_from_Muon16_fy3004[5] = {
   32,
   17,
   2,
   2,
   3};
   Double_t Graph_from_Muon16_felx3004[5] = {
   125,
   100,
   100,
   100,
   500};
   Double_t Graph_from_Muon16_fely3004[5] = {
   5.627243,
   4.082258,
   1.29183,
   1.29183,
   1.632727};
   Double_t Graph_from_Muon16_fehx3004[5] = {
   125,
   100,
   100,
   100,
   500};
   Double_t Graph_from_Muon16_fehy3004[5] = {
   6.715892,
   5.203825,
   2.63791,
   2.63791,
   2.918242};
   grae = new TGraphAsymmErrors(5,Graph_from_Muon16_fx3004,Graph_from_Muon16_fy3004,Graph_from_Muon16_felx3004,Graph_from_Muon16_fehx3004,Graph_from_Muon16_fely3004,Graph_from_Muon16_fehy3004);
   grae->SetName("Graph_from_Muon16");
   grae->SetTitle("th2");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#000099");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(20);
   grae->SetMarkerSize(0.5);
   
   TH1F *Graph_Graph_Graph_from_Muon1630023004 = new TH1F("Graph_Graph_Graph_from_Muon1630023004","th2",100,0,2185);
   Graph_Graph_Graph_from_Muon1630023004->SetMinimum(0.6373533);
   Graph_Graph_Graph_from_Muon1630023004->SetMaximum(42.51666);
   Graph_Graph_Graph_from_Muon1630023004->SetDirectory(0);
   Graph_Graph_Graph_from_Muon1630023004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_from_Muon1630023004->SetLineColor(ci);
   Graph_Graph_Graph_from_Muon1630023004->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Muon1630023004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Muon1630023004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_from_Muon1630023004->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Muon1630023004->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Muon1630023004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Muon1630023004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_from_Muon1630023004->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_Graph_from_Muon1630023004->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_from_Muon1630023004->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_from_Muon1630023004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_from_Muon1630023004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_from_Muon1630023004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_Graph_from_Muon1630023004);
   
   grae->Draw("p");
   
   TLegend *leg = new TLegend(0.4999873,0.7003836,0.6999823,0.900996,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(0);
   leg->SetFillColor(10);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("Graph_from_Muon16","Data","lp");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("ZA_EWK_stack_4_stack_4","VBS Z#gamma","f");

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
   entry->SetTextFont(42);
   entry=leg->AddEntry("ZA_stack_3_stack_3","QCD Z#gamma","f");
   entry->SetFillColor(6);
   entry->SetFillStyle(1001);
   entry->SetLineColor(6);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.7,0.7,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(0);
   leg->SetFillColor(10);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("plj_stack_2_stack_2","Nonprompt","f");
   entry->SetFillColor(7);
   entry->SetFillStyle(1001);
   entry->SetLineColor(7);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("bkg_stack_1_stack_1","Other bkgd.","f");

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
   entry->SetTextFont(42);
   entry=leg->AddEntry("ZA_EWK","F_{T,0}=-0.75e-12","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLatex *   tex = new TLatex(0.9,0.92,"35.9 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.1,0.92,"CMS");
tex->SetNDC();
   tex->SetTextFont(60);
   tex->SetTextSize(0.075);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.196,0.92,"   Preliminary");
tex->SetNDC();
   tex->SetTextFont(52);
   tex->SetTextSize(0.057);
   tex->SetLineWidth(2);
   tex->Draw();
   pad1->Modified();
   c01->cd();
   c01->Modified();
   c01->cd();
   c01->SetSelected(c01);
}
