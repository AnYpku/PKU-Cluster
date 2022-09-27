void aa()
{
//=========Macro generated from canvas: /
//=========  (Sat Jun 13 03:56:39 2020) by ROOT version 6.12/07
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
   pad1->Range(-1.3125,-12.62643,7.4375,84.49998);
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
   hs->SetMaximum(72.15105);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",7,0,7);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(75.7586);
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
   ST_stack_1->SetBinContent(1,0.1849506);
   ST_stack_1->SetBinError(1,0.1849506);
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
   TTA_stack_2->SetBinContent(1,2.150304);
   TTA_stack_2->SetBinContent(2,0.6462666);
   TTA_stack_2->SetBinContent(3,0.2857232);
   TTA_stack_2->SetBinContent(4,0.3793917);
   TTA_stack_2->SetBinContent(5,0.4329805);
   TTA_stack_2->SetBinContent(6,0.4133178);
   TTA_stack_2->SetBinContent(7,0.4678527);
   TTA_stack_2->SetBinError(1,0.6409967);
   TTA_stack_2->SetBinError(2,0.3619033);
   TTA_stack_2->SetBinError(3,0.2114868);
   TTA_stack_2->SetBinError(4,0.3526229);
   TTA_stack_2->SetBinError(5,0.3633155);
   TTA_stack_2->SetBinError(6,0.1912734);
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
   VV_stack_3->SetBinContent(1,0.5906482);
   VV_stack_3->SetBinContent(4,1.880422);
   VV_stack_3->SetBinContent(5,1.938064);
   VV_stack_3->SetBinError(1,0.5906482);
   VV_stack_3->SetBinError(4,1.880422);
   VV_stack_3->SetBinError(5,1.938064);
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
   plj_stack_5->SetBinContent(1,9.745476);
   plj_stack_5->SetBinContent(2,1.768583);
   plj_stack_5->SetBinContent(4,14.62653);
   plj_stack_5->SetBinContent(5,7.228162);
   plj_stack_5->SetBinContent(6,2.066555);
   plj_stack_5->SetBinContent(7,13.00019);
   plj_stack_5->SetBinError(1,1.72011);
   plj_stack_5->SetBinError(2,0.796478);
   plj_stack_5->SetBinError(4,2.188133);
   plj_stack_5->SetBinError(5,1.521968);
   plj_stack_5->SetBinError(6,0.8299614);
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
   t_ZA_stack_6->SetBinContent(1,27.0435);
   t_ZA_stack_6->SetBinContent(2,6.752813);
   t_ZA_stack_6->SetBinContent(3,2.26214);
   t_ZA_stack_6->SetBinContent(4,22.46717);
   t_ZA_stack_6->SetBinContent(5,7.734335);
   t_ZA_stack_6->SetBinContent(6,2.906974);
   t_ZA_stack_6->SetBinContent(7,12.227);
   t_ZA_stack_6->SetBinError(1,2.470168);
   t_ZA_stack_6->SetBinError(2,1.014928);
   t_ZA_stack_6->SetBinError(3,0.7093075);
   t_ZA_stack_6->SetBinError(4,2.373731);
   t_ZA_stack_6->SetBinError(5,1.316891);
   t_ZA_stack_6->SetBinError(6,0.8096736);
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
   ZA_sig_stack_7->SetBinContent(1,7.070644);
   ZA_sig_stack_7->SetBinContent(2,6.346396);
   ZA_sig_stack_7->SetBinContent(3,5.085401);
   ZA_sig_stack_7->SetBinContent(4,1.385414);
   ZA_sig_stack_7->SetBinContent(5,3.82657);
   ZA_sig_stack_7->SetBinContent(6,7.776191);
   ZA_sig_stack_7->SetBinContent(7,3.0655);
   ZA_sig_stack_7->SetBinError(1,0.3049464);
   ZA_sig_stack_7->SetBinError(2,0.2902871);
   ZA_sig_stack_7->SetBinError(3,0.2609879);
   ZA_sig_stack_7->SetBinError(4,0.1358892);
   ZA_sig_stack_7->SetBinError(5,0.2247035);
   ZA_sig_stack_7->SetBinError(6,0.3212572);
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
   ZA_sigout_stack_8->SetBinContent(1,1.315177);
   ZA_sigout_stack_8->SetBinContent(2,0.2879023);
   ZA_sigout_stack_8->SetBinContent(3,0.06765818);
   ZA_sigout_stack_8->SetBinContent(4,0.3205793);
   ZA_sigout_stack_8->SetBinContent(5,0.3667263);
   ZA_sigout_stack_8->SetBinContent(6,0.3147918);
   ZA_sigout_stack_8->SetBinContent(7,0.3610967);
   ZA_sigout_stack_8->SetBinError(1,0.1320856);
   ZA_sigout_stack_8->SetBinError(2,0.06264752);
   ZA_sigout_stack_8->SetBinError(3,0.02811331);
   ZA_sigout_stack_8->SetBinError(4,0.06367542);
   ZA_sigout_stack_8->SetBinError(5,0.06974836);
   ZA_sigout_stack_8->SetBinError(6,0.06544662);
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
   TLegendEntry *entry=leg->AddEntry("ZA_sig_stack_7","EWK in fid.[34.56]","lpf");

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
   entry=leg->AddEntry("ZA_sigout_stack_8","EWK out fid. [3.03]","lpf");
   entry->SetFillColor(1);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("t_ZA_stack_6","ZA [81.39]","lpf");

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
   entry=leg->AddEntry("plj_stack_5","non-prompt [48.44]","lpf");

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
   entry=leg->AddEntry("VV_stack_3","VV [4.41]","lpf");

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
   entry=leg->AddEntry("TTA_stack_2","TTA [4.78]","lpf");

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
   entry=leg->AddEntry("ST_stack_1","ST  [0.18]","lpf");

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
      tex = new TLatex(0.76,0.92,"35.86 fb^{-1} (13 TeV)");
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
