void aa()
{
//=========Macro generated from canvas: /
//=========  (Mon Jan 20 00:11:29 2020) by ROOT version6.10/09
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
   pad1->Range(-1.3125,-11.1254,7.4375,74.45458);
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
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",7,0,7);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(66.75239);
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
   ST_stack_1->SetBinContent(2,0.05040901);
   ST_stack_1->SetBinContent(4,0.003015078);
   ST_stack_1->SetBinError(2,0.05040901);
   ST_stack_1->SetBinError(4,0.003015078);
   ST_stack_1->SetEntries(7);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   ST_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   ST_stack_1->SetLineColor(ci);
   ST_stack_1->SetLineStyle(0);
   ST_stack_1->SetLineWidth(2);

   ci = TColor::GetColor("#00ff00");
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
   TTA_stack_2->SetBinContent(1,1.184597);
   TTA_stack_2->SetBinContent(2,0.2116905);
   TTA_stack_2->SetBinContent(3,0.01035476);
   TTA_stack_2->SetBinContent(4,0.3653994);
   TTA_stack_2->SetBinContent(5,-0.0596319);
   TTA_stack_2->SetBinContent(6,-0.1209242);
   TTA_stack_2->SetBinContent(7,0.1203659);
   TTA_stack_2->SetBinError(1,0.4516039);
   TTA_stack_2->SetBinError(2,0.2365697);
   TTA_stack_2->SetBinError(3,0.1333417);
   TTA_stack_2->SetBinError(4,0.2435165);
   TTA_stack_2->SetBinError(5,0.2088253);
   TTA_stack_2->SetBinError(6,0.08127552);
   TTA_stack_2->SetBinError(7,0.08586217);
   TTA_stack_2->SetEntries(7);

   ci = TColor::GetColor("#00ffff");
   TTA_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   TTA_stack_2->SetLineColor(ci);
   TTA_stack_2->SetLineStyle(0);
   TTA_stack_2->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
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
   VV_stack_3->SetBinContent(1,0.2913233);
   VV_stack_3->SetBinContent(3,0.3066027);
   VV_stack_3->SetBinContent(4,0.8643058);
   VV_stack_3->SetBinContent(5,0.3550145);
   VV_stack_3->SetBinContent(7,0.498655);
   VV_stack_3->SetBinError(1,0.2913233);
   VV_stack_3->SetBinError(3,0.3066027);
   VV_stack_3->SetBinError(4,0.5129019);
   VV_stack_3->SetBinError(5,0.333351);
   VV_stack_3->SetEntries(7);

   ci = TColor::GetColor("#6666cc");
   VV_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   VV_stack_3->SetLineColor(ci);
   VV_stack_3->SetLineStyle(0);
   VV_stack_3->SetLineWidth(2);

   ci = TColor::GetColor("#6666cc");
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

   ci = TColor::GetColor("#000099");
   WA_stack_4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   WA_stack_4->SetLineColor(ci);
   WA_stack_4->SetLineStyle(0);
   WA_stack_4->SetLineWidth(2);

   ci = TColor::GetColor("#000099");
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
   plj_stack_5->SetBinContent(1,18.87674);
   plj_stack_5->SetBinContent(2,3.422899);
   plj_stack_5->SetBinContent(3,2.270478);
   plj_stack_5->SetBinContent(4,17.8698);
   plj_stack_5->SetBinContent(5,11.00755);
   plj_stack_5->SetBinContent(6,0.746816);
   plj_stack_5->SetBinContent(7,13.59797);
   plj_stack_5->SetBinError(1,2.614971);
   plj_stack_5->SetBinError(2,1.025647);
   plj_stack_5->SetBinError(3,0.8980617);
   plj_stack_5->SetBinError(4,2.463138);
   plj_stack_5->SetBinError(5,1.96371);
   plj_stack_5->SetBinError(6,0.533908);
   plj_stack_5->SetBinError(7,1.225955);
   plj_stack_5->SetEntries(7);

   ci = TColor::GetColor("#ffff00");
   plj_stack_5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   plj_stack_5->SetLineColor(ci);
   plj_stack_5->SetLineStyle(0);
   plj_stack_5->SetLineWidth(2);

   ci = TColor::GetColor("#ffff00");
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
   t_ZA_stack_6->SetBinContent(1,32.36468);
   t_ZA_stack_6->SetBinContent(2,6.820891);
   t_ZA_stack_6->SetBinContent(3,1.143983);
   t_ZA_stack_6->SetBinContent(4,31.34586);
   t_ZA_stack_6->SetBinContent(5,8.741344);
   t_ZA_stack_6->SetBinContent(6,0.8224697);
   t_ZA_stack_6->SetBinContent(7,9.048706);
   t_ZA_stack_6->SetBinError(1,2.578729);
   t_ZA_stack_6->SetBinError(2,1.061497);
   t_ZA_stack_6->SetBinError(3,0.4980202);
   t_ZA_stack_6->SetBinError(4,2.628916);
   t_ZA_stack_6->SetBinError(5,1.368942);
   t_ZA_stack_6->SetBinError(6,0.618492);
   t_ZA_stack_6->SetBinError(7,0.9950558);
   t_ZA_stack_6->SetEntries(7);

   ci = TColor::GetColor("#ff00ff");
   t_ZA_stack_6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   t_ZA_stack_6->SetLineColor(ci);
   t_ZA_stack_6->SetLineStyle(0);
   t_ZA_stack_6->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
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
   ZA_sig_stack_7->SetBinContent(1,10.85635);
   ZA_sig_stack_7->SetBinContent(2,8.135157);
   ZA_sig_stack_7->SetBinContent(3,5.241634);
   ZA_sig_stack_7->SetBinContent(4,1.898026);
   ZA_sig_stack_7->SetBinContent(5,4.135093);
   ZA_sig_stack_7->SetBinContent(6,6.212362);
   ZA_sig_stack_7->SetBinContent(7,3.135251);
   ZA_sig_stack_7->SetBinError(1,0.4185235);
   ZA_sig_stack_7->SetBinError(2,0.3631355);
   ZA_sig_stack_7->SetBinError(3,0.2896819);
   ZA_sig_stack_7->SetBinError(4,0.1744792);
   ZA_sig_stack_7->SetBinError(5,0.2564902);
   ZA_sig_stack_7->SetBinError(6,0.3142016);
   ZA_sig_stack_7->SetBinError(7,0.07141595);
   ZA_sig_stack_7->SetEntries(7);

   ci = TColor::GetColor("#ff3333");
   ZA_sig_stack_7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   ZA_sig_stack_7->SetLineColor(ci);
   ZA_sig_stack_7->SetLineStyle(0);
   ZA_sig_stack_7->SetLineWidth(2);

   ci = TColor::GetColor("#ff3333");
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
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.82,0.7,0.95,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ZA_sig_stack_7","ZA_sig","lpf");

   ci = TColor::GetColor("#ff3333");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff3333");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff3333");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("t_ZA_stack_6","ZA","lpf");

   ci = TColor::GetColor("#ff00ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff00ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("plj_stack_5","non-prompt","lpf");

   ci = TColor::GetColor("#ffff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffff00");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ffff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("WA_stack_4","WA","lpf");

   ci = TColor::GetColor("#000099");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("VV_stack_3","VV","lpf");

   ci = TColor::GetColor("#6666cc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#6666cc");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#6666cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("TTA_stack_2","TTA","lpf");

   ci = TColor::GetColor("#00ffff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("ST_stack_1","ST","lpf");

   ci = TColor::GetColor("#00ff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#00ff00");
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
