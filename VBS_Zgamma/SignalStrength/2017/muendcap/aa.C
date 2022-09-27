void aa()
{
//=========Macro generated from canvas: /
//=========  (Mon Jun  8 04:08:52 2020) by ROOT version 6.12/07
   TCanvas * = new TCanvas("", "",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.15);
   c1->SetRightMargin(0.05);
   c1->SetBottomMargin(0.13);
   c1->SetFrameFillStyle(0);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "",0,0,0.99,0.99);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-1.3125,-5.695438,7.4375,38.11562);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetLeftMargin(0.15);
   pad1->SetRightMargin(0.05);
   pad1->SetBottomMargin(0.13);
   pad1->SetFrameFillStyle(0);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameFillStyle(0);
   pad1->SetFrameBorderMode(0);
   
   THStack *hs = new THStack();
   hs->SetName("hs");
   hs->SetTitle("");
   hs->SetMaximum(32.54536);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",7,0,7);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(34.17263);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 500~800");
   hs_stack_1->GetXaxis()->SetBinLabel(2,"Mjj 800~1200");
   hs_stack_1->GetXaxis()->SetBinLabel(3,"Mjj 1200~2000");
   hs_stack_1->GetXaxis()->SetBinLabel(4,"Mjj 500~800");
   hs_stack_1->GetXaxis()->SetBinLabel(5,"Mjj 800~1200");
   hs_stack_1->GetXaxis()->SetBinLabel(6,"Mjj 1200~2000");
   hs_stack_1->GetXaxis()->SetBinLabel(7,"Mjj 500~2000");
   hs_stack_1->GetXaxis()->SetLabelFont(42);
   hs_stack_1->GetXaxis()->SetLabelOffset(0.007);
   hs_stack_1->GetXaxis()->SetTitleSize(0.06);
   hs_stack_1->GetXaxis()->SetTitleOffset(0.9);
   hs_stack_1->GetXaxis()->SetTitleFont(42);
   hs_stack_1->GetYaxis()->SetTitle("Events /bin");
   hs_stack_1->GetYaxis()->SetLabelFont(42);
   hs_stack_1->GetYaxis()->SetLabelOffset(0.007);
   hs_stack_1->GetYaxis()->SetTitleSize(0.06);
   hs_stack_1->GetYaxis()->SetTitleOffset(0.8);
   hs_stack_1->GetYaxis()->SetTitleFont(42);
   hs_stack_1->GetZaxis()->SetLabelFont(42);
   hs_stack_1->GetZaxis()->SetLabelOffset(0.007);
   hs_stack_1->GetZaxis()->SetTitleSize(0.06);
   hs_stack_1->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_1);
   
   
   TH1D *ST_stack_1 = new TH1D("ST_stack_1","",7,0,7);
   ST_stack_1->SetEntries(7);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#33ff33");
   ST_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#33ff33");
   ST_stack_1->SetLineColor(ci);
   ST_stack_1->SetLineStyle(0);
   ST_stack_1->SetLineWidth(2);

   ci = TColor::GetColor("#33ff33");
   ST_stack_1->SetMarkerColor(ci);
   ST_stack_1->SetMarkerStyle(20);
   ST_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 500~800");
   ST_stack_1->GetXaxis()->SetBinLabel(2,"Mjj 800~1200");
   ST_stack_1->GetXaxis()->SetBinLabel(3,"Mjj 1200~2000");
   ST_stack_1->GetXaxis()->SetBinLabel(4,"Mjj 500~800");
   ST_stack_1->GetXaxis()->SetBinLabel(5,"Mjj 800~1200");
   ST_stack_1->GetXaxis()->SetBinLabel(6,"Mjj 1200~2000");
   ST_stack_1->GetXaxis()->SetBinLabel(7,"Mjj 500~2000");
   ST_stack_1->GetXaxis()->SetLabelFont(42);
   ST_stack_1->GetXaxis()->SetLabelOffset(0.007);
   ST_stack_1->GetXaxis()->SetTitleSize(0.06);
   ST_stack_1->GetXaxis()->SetTitleOffset(0.9);
   ST_stack_1->GetXaxis()->SetTitleFont(42);
   ST_stack_1->GetYaxis()->SetLabelFont(42);
   ST_stack_1->GetYaxis()->SetLabelOffset(0.007);
   ST_stack_1->GetYaxis()->SetTitleSize(0.06);
   ST_stack_1->GetYaxis()->SetTitleOffset(1.1);
   ST_stack_1->GetYaxis()->SetTitleFont(42);
   ST_stack_1->GetZaxis()->SetLabelFont(42);
   ST_stack_1->GetZaxis()->SetLabelOffset(0.007);
   ST_stack_1->GetZaxis()->SetTitleSize(0.06);
   ST_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(ST_stack_1,"");
   
   TH1D *TTA_stack_2 = new TH1D("TTA_stack_2","",7,0,7);
   TTA_stack_2->SetBinContent(1,0.4246222);
   TTA_stack_2->SetBinContent(2,0.09118345);
   TTA_stack_2->SetBinContent(3,0.08815677);
   TTA_stack_2->SetBinContent(4,-0.04454768);
   TTA_stack_2->SetBinContent(5,0.04587214);
   TTA_stack_2->SetBinError(1,0.2485354);
   TTA_stack_2->SetBinError(2,0.1466093);
   TTA_stack_2->SetBinError(3,0.06237231);
   TTA_stack_2->SetBinError(4,0.04454768);
   TTA_stack_2->SetBinError(5,0.1190306);
   TTA_stack_2->SetEntries(7);

   ci = TColor::GetColor("#ccffcc");
   TTA_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#ccffcc");
   TTA_stack_2->SetLineColor(ci);
   TTA_stack_2->SetLineStyle(0);
   TTA_stack_2->SetLineWidth(2);

   ci = TColor::GetColor("#ccffcc");
   TTA_stack_2->SetMarkerColor(ci);
   TTA_stack_2->SetMarkerStyle(20);
   TTA_stack_2->GetXaxis()->SetLabelFont(42);
   TTA_stack_2->GetXaxis()->SetLabelOffset(0.007);
   TTA_stack_2->GetXaxis()->SetTitleSize(0.06);
   TTA_stack_2->GetXaxis()->SetTitleOffset(0.9);
   TTA_stack_2->GetXaxis()->SetTitleFont(42);
   TTA_stack_2->GetYaxis()->SetLabelFont(42);
   TTA_stack_2->GetYaxis()->SetLabelOffset(0.007);
   TTA_stack_2->GetYaxis()->SetTitleSize(0.06);
   TTA_stack_2->GetYaxis()->SetTitleOffset(1.1);
   TTA_stack_2->GetYaxis()->SetTitleFont(42);
   TTA_stack_2->GetZaxis()->SetLabelFont(42);
   TTA_stack_2->GetZaxis()->SetLabelOffset(0.007);
   TTA_stack_2->GetZaxis()->SetTitleSize(0.06);
   TTA_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(TTA_stack_2,"");
   
   TH1D *VV_stack_3 = new TH1D("VV_stack_3","",7,0,7);
   VV_stack_3->SetBinContent(1,0.7911056);
   VV_stack_3->SetBinContent(2,0.2656805);
   VV_stack_3->SetBinError(1,0.4577097);
   VV_stack_3->SetBinError(2,0.2656805);
   VV_stack_3->SetEntries(7);

   ci = TColor::GetColor("#3333ff");
   VV_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#3333ff");
   VV_stack_3->SetLineColor(ci);
   VV_stack_3->SetLineStyle(0);
   VV_stack_3->SetLineWidth(2);

   ci = TColor::GetColor("#3333ff");
   VV_stack_3->SetMarkerColor(ci);
   VV_stack_3->SetMarkerStyle(20);
   VV_stack_3->GetXaxis()->SetLabelFont(42);
   VV_stack_3->GetXaxis()->SetLabelOffset(0.007);
   VV_stack_3->GetXaxis()->SetTitleSize(0.06);
   VV_stack_3->GetXaxis()->SetTitleOffset(0.9);
   VV_stack_3->GetXaxis()->SetTitleFont(42);
   VV_stack_3->GetYaxis()->SetLabelFont(42);
   VV_stack_3->GetYaxis()->SetLabelOffset(0.007);
   VV_stack_3->GetYaxis()->SetTitleSize(0.06);
   VV_stack_3->GetYaxis()->SetTitleOffset(1.1);
   VV_stack_3->GetYaxis()->SetTitleFont(42);
   VV_stack_3->GetZaxis()->SetLabelFont(42);
   VV_stack_3->GetZaxis()->SetLabelOffset(0.007);
   VV_stack_3->GetZaxis()->SetTitleSize(0.06);
   VV_stack_3->GetZaxis()->SetTitleFont(42);
   hs->Add(VV_stack_3,"");
   
   TH1D *WA_stack_4 = new TH1D("WA_stack_4","",7,0,7);
   WA_stack_4->SetEntries(7);

   ci = TColor::GetColor("#6666ff");
   WA_stack_4->SetFillColor(ci);

   ci = TColor::GetColor("#6666ff");
   WA_stack_4->SetLineColor(ci);
   WA_stack_4->SetLineStyle(0);
   WA_stack_4->SetLineWidth(2);

   ci = TColor::GetColor("#6666ff");
   WA_stack_4->SetMarkerColor(ci);
   WA_stack_4->SetMarkerStyle(20);
   WA_stack_4->GetXaxis()->SetLabelFont(42);
   WA_stack_4->GetXaxis()->SetLabelOffset(0.007);
   WA_stack_4->GetXaxis()->SetTitleSize(0.06);
   WA_stack_4->GetXaxis()->SetTitleOffset(0.9);
   WA_stack_4->GetXaxis()->SetTitleFont(42);
   WA_stack_4->GetYaxis()->SetLabelFont(42);
   WA_stack_4->GetYaxis()->SetLabelOffset(0.007);
   WA_stack_4->GetYaxis()->SetTitleSize(0.06);
   WA_stack_4->GetYaxis()->SetTitleOffset(1.1);
   WA_stack_4->GetYaxis()->SetTitleFont(42);
   WA_stack_4->GetZaxis()->SetLabelFont(42);
   WA_stack_4->GetZaxis()->SetLabelOffset(0.007);
   WA_stack_4->GetZaxis()->SetTitleSize(0.06);
   WA_stack_4->GetZaxis()->SetTitleFont(42);
   hs->Add(WA_stack_4,"");
   
   TH1D *plj_stack_5 = new TH1D("plj_stack_5","",7,0,7);
   plj_stack_5->SetBinContent(1,7.97321);
   plj_stack_5->SetBinContent(2,1.548071);
   plj_stack_5->SetBinContent(4,8.195231);
   plj_stack_5->SetBinContent(5,2.730626);
   plj_stack_5->SetBinContent(6,0.771196);
   plj_stack_5->SetBinContent(7,1.524574);
   plj_stack_5->SetBinError(1,1.411901);
   plj_stack_5->SetBinError(2,0.632112);
   plj_stack_5->SetBinError(4,1.429684);
   plj_stack_5->SetBinError(5,0.8249853);
   plj_stack_5->SetBinError(6,0.4453096);
   plj_stack_5->SetEntries(7);

   ci = TColor::GetColor("#ffcc33");
   plj_stack_5->SetFillColor(ci);

   ci = TColor::GetColor("#ffcc33");
   plj_stack_5->SetLineColor(ci);
   plj_stack_5->SetLineStyle(0);
   plj_stack_5->SetLineWidth(2);

   ci = TColor::GetColor("#ffcc33");
   plj_stack_5->SetMarkerColor(ci);
   plj_stack_5->SetMarkerStyle(20);
   plj_stack_5->GetXaxis()->SetLabelFont(42);
   plj_stack_5->GetXaxis()->SetLabelOffset(0.007);
   plj_stack_5->GetXaxis()->SetTitleSize(0.06);
   plj_stack_5->GetXaxis()->SetTitleOffset(0.9);
   plj_stack_5->GetXaxis()->SetTitleFont(42);
   plj_stack_5->GetYaxis()->SetLabelFont(42);
   plj_stack_5->GetYaxis()->SetLabelOffset(0.007);
   plj_stack_5->GetYaxis()->SetTitleSize(0.06);
   plj_stack_5->GetYaxis()->SetTitleOffset(1.1);
   plj_stack_5->GetYaxis()->SetTitleFont(42);
   plj_stack_5->GetZaxis()->SetLabelFont(42);
   plj_stack_5->GetZaxis()->SetLabelOffset(0.007);
   plj_stack_5->GetZaxis()->SetTitleSize(0.06);
   plj_stack_5->GetZaxis()->SetTitleFont(42);
   hs->Add(plj_stack_5,"");
   
   TH1D *t_ZA_stack_6 = new TH1D("t_ZA_stack_6","",7,0,7);
   t_ZA_stack_6->SetBinContent(1,9.805985);
   t_ZA_stack_6->SetBinContent(2,2.42695);
   t_ZA_stack_6->SetBinContent(3,0.5564465);
   t_ZA_stack_6->SetBinContent(4,4.63894);
   t_ZA_stack_6->SetBinContent(5,2.700935);
   t_ZA_stack_6->SetBinContent(6,0.7658911);
   t_ZA_stack_6->SetBinContent(7,1.112865);
   t_ZA_stack_6->SetBinError(1,1.199181);
   t_ZA_stack_6->SetBinError(2,0.6284059);
   t_ZA_stack_6->SetBinError(3,0.2982131);
   t_ZA_stack_6->SetBinError(4,0.8915806);
   t_ZA_stack_6->SetBinError(5,0.6164106);
   t_ZA_stack_6->SetBinError(6,0.3304212);
   t_ZA_stack_6->SetEntries(7);

   ci = TColor::GetColor("#ff6666");
   t_ZA_stack_6->SetFillColor(ci);

   ci = TColor::GetColor("#ff6666");
   t_ZA_stack_6->SetLineColor(ci);
   t_ZA_stack_6->SetLineStyle(0);
   t_ZA_stack_6->SetLineWidth(2);

   ci = TColor::GetColor("#ff6666");
   t_ZA_stack_6->SetMarkerColor(ci);
   t_ZA_stack_6->SetMarkerStyle(20);
   t_ZA_stack_6->GetXaxis()->SetLabelFont(42);
   t_ZA_stack_6->GetXaxis()->SetLabelOffset(0.007);
   t_ZA_stack_6->GetXaxis()->SetTitleSize(0.06);
   t_ZA_stack_6->GetXaxis()->SetTitleOffset(0.9);
   t_ZA_stack_6->GetXaxis()->SetTitleFont(42);
   t_ZA_stack_6->GetYaxis()->SetLabelFont(42);
   t_ZA_stack_6->GetYaxis()->SetLabelOffset(0.007);
   t_ZA_stack_6->GetYaxis()->SetTitleSize(0.06);
   t_ZA_stack_6->GetYaxis()->SetTitleOffset(1.1);
   t_ZA_stack_6->GetYaxis()->SetTitleFont(42);
   t_ZA_stack_6->GetZaxis()->SetLabelFont(42);
   t_ZA_stack_6->GetZaxis()->SetLabelOffset(0.007);
   t_ZA_stack_6->GetZaxis()->SetTitleSize(0.06);
   t_ZA_stack_6->GetZaxis()->SetTitleFont(42);
   hs->Add(t_ZA_stack_6,"");
   
   TH1D *ZA_sig_stack_7 = new TH1D("ZA_sig_stack_7","",7,0,7);
   ZA_sig_stack_7->SetBinContent(1,2.264078);
   ZA_sig_stack_7->SetBinContent(2,1.94691);
   ZA_sig_stack_7->SetBinContent(3,1.077153);
   ZA_sig_stack_7->SetBinContent(4,0.2244987);
   ZA_sig_stack_7->SetBinContent(5,0.7565638);
   ZA_sig_stack_7->SetBinContent(6,1.936091);
   ZA_sig_stack_7->SetBinContent(7,0.1548221);
   ZA_sig_stack_7->SetBinError(1,0.1791318);
   ZA_sig_stack_7->SetBinError(2,0.1658134);
   ZA_sig_stack_7->SetBinError(3,0.1278702);
   ZA_sig_stack_7->SetBinError(4,0.05615154);
   ZA_sig_stack_7->SetBinError(5,0.1049697);
   ZA_sig_stack_7->SetBinError(6,0.1655316);
   ZA_sig_stack_7->SetEntries(7);

   ci = TColor::GetColor("#ff0000");
   ZA_sig_stack_7->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   ZA_sig_stack_7->SetLineColor(ci);
   ZA_sig_stack_7->SetLineStyle(0);
   ZA_sig_stack_7->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   ZA_sig_stack_7->SetMarkerColor(ci);
   ZA_sig_stack_7->SetMarkerStyle(21);
   ZA_sig_stack_7->GetXaxis()->SetLabelFont(42);
   ZA_sig_stack_7->GetXaxis()->SetLabelOffset(0.007);
   ZA_sig_stack_7->GetXaxis()->SetTitleSize(0.06);
   ZA_sig_stack_7->GetXaxis()->SetTitleOffset(0.9);
   ZA_sig_stack_7->GetXaxis()->SetTitleFont(42);
   ZA_sig_stack_7->GetYaxis()->SetLabelFont(42);
   ZA_sig_stack_7->GetYaxis()->SetLabelOffset(0.007);
   ZA_sig_stack_7->GetYaxis()->SetTitleSize(0.06);
   ZA_sig_stack_7->GetYaxis()->SetTitleOffset(1.1);
   ZA_sig_stack_7->GetYaxis()->SetTitleFont(42);
   ZA_sig_stack_7->GetZaxis()->SetLabelFont(42);
   ZA_sig_stack_7->GetZaxis()->SetLabelOffset(0.007);
   ZA_sig_stack_7->GetZaxis()->SetTitleSize(0.06);
   ZA_sig_stack_7->GetZaxis()->SetTitleFont(42);
   hs->Add(ZA_sig_stack_7,"");
   
   TH1D *ZA_sigout_stack_8 = new TH1D("ZA_sigout_stack_8","",7,0,7);
   ZA_sigout_stack_8->SetBinContent(1,0.4379041);
   ZA_sigout_stack_8->SetBinContent(2,0.1528549);
   ZA_sigout_stack_8->SetBinContent(3,0.07243507);
   ZA_sigout_stack_8->SetBinContent(4,0.1121916);
   ZA_sigout_stack_8->SetBinContent(5,0.1851189);
   ZA_sigout_stack_8->SetBinContent(6,0.1124944);
   ZA_sigout_stack_8->SetBinContent(7,0.07121381);
   ZA_sigout_stack_8->SetBinError(1,0.07868897);
   ZA_sigout_stack_8->SetBinError(2,0.04609413);
   ZA_sigout_stack_8->SetBinError(3,0.03241174);
   ZA_sigout_stack_8->SetBinError(4,0.03968534);
   ZA_sigout_stack_8->SetBinError(5,0.05138657);
   ZA_sigout_stack_8->SetBinError(6,0.03978641);
   ZA_sigout_stack_8->SetEntries(7);
   ZA_sigout_stack_8->SetFillColor(1);
   ZA_sigout_stack_8->SetLineStyle(0);
   ZA_sigout_stack_8->SetLineWidth(2);
   ZA_sigout_stack_8->SetMarkerStyle(21);
   ZA_sigout_stack_8->GetXaxis()->SetLabelFont(42);
   ZA_sigout_stack_8->GetXaxis()->SetLabelOffset(0.007);
   ZA_sigout_stack_8->GetXaxis()->SetTitleSize(0.06);
   ZA_sigout_stack_8->GetXaxis()->SetTitleOffset(0.9);
   ZA_sigout_stack_8->GetXaxis()->SetTitleFont(42);
   ZA_sigout_stack_8->GetYaxis()->SetLabelFont(42);
   ZA_sigout_stack_8->GetYaxis()->SetLabelOffset(0.007);
   ZA_sigout_stack_8->GetYaxis()->SetTitleSize(0.06);
   ZA_sigout_stack_8->GetYaxis()->SetTitleOffset(1.1);
   ZA_sigout_stack_8->GetYaxis()->SetTitleFont(42);
   ZA_sigout_stack_8->GetZaxis()->SetLabelFont(42);
   ZA_sigout_stack_8->GetZaxis()->SetLabelOffset(0.007);
   ZA_sigout_stack_8->GetZaxis()->SetTitleSize(0.06);
   ZA_sigout_stack_8->GetZaxis()->SetTitleFont(42);
   hs->Add(ZA_sigout_stack_8,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.62,0.45,0.85,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ZA_sig_stack_7","EWK in fid.[8.36]","lpf");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("ZA_sigout_stack_8","EWK out fid. [1.14]","lpf");
   entry->SetFillColor(1);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("t_ZA_stack_6","ZA [22.01]","lpf");

   ci = TColor::GetColor("#ff6666");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff6666");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff6666");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("plj_stack_5","non-prompt [22.74]","lpf");

   ci = TColor::GetColor("#ffcc33");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffcc33");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ffcc33");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("WA_stack_4","WA [0.00]","lpf");

   ci = TColor::GetColor("#6666ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#6666ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#6666ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("VV_stack_3","VV [1.06]","lpf");

   ci = TColor::GetColor("#3333ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#3333ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#3333ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("TTA_stack_2","TTA [0.61]","lpf");

   ci = TColor::GetColor("#ccffcc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ccffcc");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ccffcc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("ST_stack_1","ST  [0.00]","lpf");

   ci = TColor::GetColor("#33ff33");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#33ff33");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#33ff33");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLatex *   tex = new TLatex(0.18,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18,0.86,"CMS");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.76,0.92,"41.52 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
   pad1->Modified();
   ->cd();
   c1->Modified();
   ->cd();
   ->SetSelected();
}
