{
//=========Macro generated from canvas: /
//=========  (Tue Jul  7 13:31:36 2020) by ROOT version5.34/38
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
   pad1->Range(-1.3125,-13.80008,7.4375,92.35435);
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
   hs->SetMaximum(78.85757);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",7,0,7);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(82.80045);
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
   
   
   TH1D *ST = new TH1D("ST","",7,0,7);
   ST->SetBinContent(1,0.2141245);
   ST->SetBinContent(2,0.1741633);
   ST->SetBinError(1,0.2141245);
   ST->SetBinError(2,0.1741633);
   ST->SetEntries(7);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#33ff33");
   ST->SetFillColor(ci);

   ci = TColor::GetColor("#33ff33");
   ST->SetLineColor(ci);
   ST->SetLineStyle(0);
   ST->SetLineWidth(2);

   ci = TColor::GetColor("#33ff33");
   ST->SetMarkerColor(ci);
   ST->SetMarkerStyle(20);
   ST->GetXaxis()->SetBinLabel(1,"Mjj 500~800");
   ST->GetXaxis()->SetBinLabel(2,"Mjj 800~1200");
   ST->GetXaxis()->SetBinLabel(3,"Mjj 1200~2000");
   ST->GetXaxis()->SetBinLabel(4,"Mjj 500~800");
   ST->GetXaxis()->SetBinLabel(5,"Mjj 800~1200");
   ST->GetXaxis()->SetBinLabel(6,"Mjj 1200~2000");
   ST->GetXaxis()->SetBinLabel(7,"Mjj 500~2000");
   ST->GetXaxis()->SetLabelFont(42);
   ST->GetXaxis()->SetLabelOffset(0.007);
   ST->GetXaxis()->SetTitleSize(0.06);
   ST->GetXaxis()->SetTitleOffset(0.9);
   ST->GetXaxis()->SetTitleFont(42);
   ST->GetYaxis()->SetLabelFont(42);
   ST->GetYaxis()->SetLabelOffset(0.007);
   ST->GetYaxis()->SetTitleSize(0.06);
   ST->GetYaxis()->SetTitleOffset(1.1);
   ST->GetYaxis()->SetTitleFont(42);
   ST->GetZaxis()->SetLabelFont(42);
   ST->GetZaxis()->SetLabelOffset(0.007);
   ST->GetZaxis()->SetTitleSize(0.06);
   ST->GetZaxis()->SetTitleFont(42);
   hs->Add(ST,"");
   
   TH1D *TTA = new TH1D("TTA","",7,0,7);
   TTA->SetBinContent(1,0.5755933);
   TTA->SetBinContent(2,0.1389345);
   TTA->SetBinContent(3,0.1297072);
   TTA->SetBinContent(4,0.04822177);
   TTA->SetBinContent(5,0.2665932);
   TTA->SetBinContent(6,0.1349074);
   TTA->SetBinContent(7,0.2648889);
   TTA->SetBinError(1,0.4608543);
   TTA->SetBinError(2,0.2614892);
   TTA->SetBinError(3,0.1297072);
   TTA->SetBinError(4,0.1929077);
   TTA->SetBinError(5,0.1766717);
   TTA->SetBinError(6,0.1613186);
   TTA->SetEntries(7);

   ci = TColor::GetColor("#ccffcc");
   TTA->SetFillColor(ci);

   ci = TColor::GetColor("#ccffcc");
   TTA->SetLineColor(ci);
   TTA->SetLineStyle(0);
   TTA->SetLineWidth(2);

   ci = TColor::GetColor("#ccffcc");
   TTA->SetMarkerColor(ci);
   TTA->SetMarkerStyle(20);
   TTA->GetXaxis()->SetLabelFont(42);
   TTA->GetXaxis()->SetLabelOffset(0.007);
   TTA->GetXaxis()->SetTitleSize(0.06);
   TTA->GetXaxis()->SetTitleOffset(0.9);
   TTA->GetXaxis()->SetTitleFont(42);
   TTA->GetYaxis()->SetLabelFont(42);
   TTA->GetYaxis()->SetLabelOffset(0.007);
   TTA->GetYaxis()->SetTitleSize(0.06);
   TTA->GetYaxis()->SetTitleOffset(1.1);
   TTA->GetYaxis()->SetTitleFont(42);
   TTA->GetZaxis()->SetLabelFont(42);
   TTA->GetZaxis()->SetLabelOffset(0.007);
   TTA->GetZaxis()->SetTitleSize(0.06);
   TTA->GetZaxis()->SetTitleFont(42);
   hs->Add(TTA,"");
   
   TH1D *VV = new TH1D("VV","",7,0,7);
   VV->SetBinContent(4,0.6357604);
   VV->SetBinError(4,0.4552445);
   VV->SetEntries(7);

   ci = TColor::GetColor("#3333ff");
   VV->SetFillColor(ci);

   ci = TColor::GetColor("#3333ff");
   VV->SetLineColor(ci);
   VV->SetLineStyle(0);
   VV->SetLineWidth(2);

   ci = TColor::GetColor("#3333ff");
   VV->SetMarkerColor(ci);
   VV->SetMarkerStyle(20);
   VV->GetXaxis()->SetLabelFont(42);
   VV->GetXaxis()->SetLabelOffset(0.007);
   VV->GetXaxis()->SetTitleSize(0.06);
   VV->GetXaxis()->SetTitleOffset(0.9);
   VV->GetXaxis()->SetTitleFont(42);
   VV->GetYaxis()->SetLabelFont(42);
   VV->GetYaxis()->SetLabelOffset(0.007);
   VV->GetYaxis()->SetTitleSize(0.06);
   VV->GetYaxis()->SetTitleOffset(1.1);
   VV->GetYaxis()->SetTitleFont(42);
   VV->GetZaxis()->SetLabelFont(42);
   VV->GetZaxis()->SetLabelOffset(0.007);
   VV->GetZaxis()->SetTitleSize(0.06);
   VV->GetZaxis()->SetTitleFont(42);
   hs->Add(VV,"");
   
   TH1D *WA = new TH1D("WA","",7,0,7);
   WA->SetEntries(7);

   ci = TColor::GetColor("#6666ff");
   WA->SetFillColor(ci);

   ci = TColor::GetColor("#6666ff");
   WA->SetLineColor(ci);
   WA->SetLineStyle(0);
   WA->SetLineWidth(2);

   ci = TColor::GetColor("#6666ff");
   WA->SetMarkerColor(ci);
   WA->SetMarkerStyle(20);
   WA->GetXaxis()->SetLabelFont(42);
   WA->GetXaxis()->SetLabelOffset(0.007);
   WA->GetXaxis()->SetTitleSize(0.06);
   WA->GetXaxis()->SetTitleOffset(0.9);
   WA->GetXaxis()->SetTitleFont(42);
   WA->GetYaxis()->SetLabelFont(42);
   WA->GetYaxis()->SetLabelOffset(0.007);
   WA->GetYaxis()->SetTitleSize(0.06);
   WA->GetYaxis()->SetTitleOffset(1.1);
   WA->GetYaxis()->SetTitleFont(42);
   WA->GetZaxis()->SetLabelFont(42);
   WA->GetZaxis()->SetLabelOffset(0.007);
   WA->GetZaxis()->SetTitleSize(0.06);
   WA->GetZaxis()->SetTitleFont(42);
   hs->Add(WA,"");
   
   TH1D *plj = new TH1D("plj","",7,0,7);
   plj->SetBinContent(1,19.44523);
   plj->SetBinContent(2,5.114975);
   plj->SetBinContent(3,0.626209);
   plj->SetBinContent(4,19.81653);
   plj->SetBinContent(5,6.563455);
   plj->SetBinContent(6,2.030094);
   plj->SetBinContent(7,6.902744);
   plj->SetBinError(1,2.075901);
   plj->SetBinError(2,1.043392);
   plj->SetBinError(3,0.3641932);
   plj->SetBinError(4,2.134622);
   plj->SetBinError(5,1.215343);
   plj->SetBinError(6,0.6642488);
   plj->SetEntries(7);

   ci = TColor::GetColor("#ffcc33");
   plj->SetFillColor(ci);

   ci = TColor::GetColor("#ffcc33");
   plj->SetLineColor(ci);
   plj->SetLineStyle(0);
   plj->SetLineWidth(2);

   ci = TColor::GetColor("#ffcc33");
   plj->SetMarkerColor(ci);
   plj->SetMarkerStyle(20);
   plj->GetXaxis()->SetLabelFont(42);
   plj->GetXaxis()->SetLabelOffset(0.007);
   plj->GetXaxis()->SetTitleSize(0.06);
   plj->GetXaxis()->SetTitleOffset(0.9);
   plj->GetXaxis()->SetTitleFont(42);
   plj->GetYaxis()->SetLabelFont(42);
   plj->GetYaxis()->SetLabelOffset(0.007);
   plj->GetYaxis()->SetTitleSize(0.06);
   plj->GetYaxis()->SetTitleOffset(1.1);
   plj->GetYaxis()->SetTitleFont(42);
   plj->GetZaxis()->SetLabelFont(42);
   plj->GetZaxis()->SetLabelOffset(0.007);
   plj->GetZaxis()->SetTitleSize(0.06);
   plj->GetZaxis()->SetTitleFont(42);
   hs->Add(plj,"");
   
   TH1D *t_ZA = new TH1D("t_ZA","",7,0,7);
   t_ZA->SetBinContent(1,26.24387);
   t_ZA->SetBinContent(2,11.33442);
   t_ZA->SetBinContent(3,2.158224);
   t_ZA->SetBinContent(4,23.28858);
   t_ZA->SetBinContent(5,11.4823);
   t_ZA->SetBinContent(6,3.285238);
   t_ZA->SetBinContent(7,8.587254);
   t_ZA->SetBinError(1,3.416479);
   t_ZA->SetBinError(2,1.76901);
   t_ZA->SetBinError(3,0.7641389);
   t_ZA->SetBinError(4,3.121985);
   t_ZA->SetBinError(5,2.144083);
   t_ZA->SetBinError(6,1.00377);
   t_ZA->SetEntries(7);

   ci = TColor::GetColor("#ff6666");
   t_ZA->SetFillColor(ci);

   ci = TColor::GetColor("#ff6666");
   t_ZA->SetLineColor(ci);
   t_ZA->SetLineStyle(0);
   t_ZA->SetLineWidth(2);

   ci = TColor::GetColor("#ff6666");
   t_ZA->SetMarkerColor(ci);
   t_ZA->SetMarkerStyle(20);
   t_ZA->GetXaxis()->SetLabelFont(42);
   t_ZA->GetXaxis()->SetLabelOffset(0.007);
   t_ZA->GetXaxis()->SetTitleSize(0.06);
   t_ZA->GetXaxis()->SetTitleOffset(0.9);
   t_ZA->GetXaxis()->SetTitleFont(42);
   t_ZA->GetYaxis()->SetLabelFont(42);
   t_ZA->GetYaxis()->SetLabelOffset(0.007);
   t_ZA->GetYaxis()->SetTitleSize(0.06);
   t_ZA->GetYaxis()->SetTitleOffset(1.1);
   t_ZA->GetYaxis()->SetTitleFont(42);
   t_ZA->GetZaxis()->SetLabelFont(42);
   t_ZA->GetZaxis()->SetLabelOffset(0.007);
   t_ZA->GetZaxis()->SetTitleSize(0.06);
   t_ZA->GetZaxis()->SetTitleFont(42);
   hs->Add(t_ZA,"");
   
   TH1D *ZA_sig = new TH1D("ZA_sig","",7,0,7);
   ZA_sig->SetBinContent(1,5.721851);
   ZA_sig->SetBinContent(2,3.535965);
   ZA_sig->SetBinContent(3,2.496502);
   ZA_sig->SetBinContent(4,1.025449);
   ZA_sig->SetBinContent(5,2.361989);
   ZA_sig->SetBinContent(6,3.819632);
   ZA_sig->SetBinContent(7,1.04584);
   ZA_sig->SetBinError(1,0.3210925);
   ZA_sig->SetBinError(2,0.2489989);
   ZA_sig->SetBinError(3,0.209458);
   ZA_sig->SetBinError(4,0.1385877);
   ZA_sig->SetBinError(5,0.205272);
   ZA_sig->SetBinError(6,0.2620673);
   ZA_sig->SetEntries(7);

   ci = TColor::GetColor("#ff0000");
   ZA_sig->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   ZA_sig->SetLineColor(ci);
   ZA_sig->SetLineStyle(0);
   ZA_sig->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   ZA_sig->SetMarkerColor(ci);
   ZA_sig->SetMarkerStyle(21);
   ZA_sig->GetXaxis()->SetLabelFont(42);
   ZA_sig->GetXaxis()->SetLabelOffset(0.007);
   ZA_sig->GetXaxis()->SetTitleSize(0.06);
   ZA_sig->GetXaxis()->SetTitleOffset(0.9);
   ZA_sig->GetXaxis()->SetTitleFont(42);
   ZA_sig->GetYaxis()->SetLabelFont(42);
   ZA_sig->GetYaxis()->SetLabelOffset(0.007);
   ZA_sig->GetYaxis()->SetTitleSize(0.06);
   ZA_sig->GetYaxis()->SetTitleOffset(1.1);
   ZA_sig->GetYaxis()->SetTitleFont(42);
   ZA_sig->GetZaxis()->SetLabelFont(42);
   ZA_sig->GetZaxis()->SetLabelOffset(0.007);
   ZA_sig->GetZaxis()->SetTitleSize(0.06);
   ZA_sig->GetZaxis()->SetTitleFont(42);
   hs->Add(ZA_sig,"");
   
   TH1D *ZA_sigout = new TH1D("ZA_sigout","",7,0,7);
   ZA_sigout->SetBinContent(1,0.3710536);
   ZA_sigout->SetBinContent(2,0.06871364);
   ZA_sigout->SetBinContent(3,0.04122818);
   ZA_sigout->SetBinContent(4,0.08245636);
   ZA_sigout->SetBinContent(5,0.1786555);
   ZA_sigout->SetBinContent(6,0.08245636);
   ZA_sigout->SetBinContent(7,0.06871364);
   ZA_sigout->SetBinError(1,0.07140931);
   ZA_sigout->SetBinError(2,0.03072967);
   ZA_sigout->SetBinError(3,0.0238031);
   ZA_sigout->SetBinError(4,0.03366267);
   ZA_sigout->SetBinError(5,0.04955011);
   ZA_sigout->SetBinError(6,0.03366267);
   ZA_sigout->SetEntries(7);
   ZA_sigout->SetFillColor(1);
   ZA_sigout->SetLineStyle(0);
   ZA_sigout->SetLineWidth(2);
   ZA_sigout->SetMarkerStyle(21);
   ZA_sigout->GetXaxis()->SetLabelFont(42);
   ZA_sigout->GetXaxis()->SetLabelOffset(0.007);
   ZA_sigout->GetXaxis()->SetTitleSize(0.06);
   ZA_sigout->GetXaxis()->SetTitleOffset(0.9);
   ZA_sigout->GetXaxis()->SetTitleFont(42);
   ZA_sigout->GetYaxis()->SetLabelFont(42);
   ZA_sigout->GetYaxis()->SetLabelOffset(0.007);
   ZA_sigout->GetYaxis()->SetTitleSize(0.06);
   ZA_sigout->GetYaxis()->SetTitleOffset(1.1);
   ZA_sigout->GetYaxis()->SetTitleFont(42);
   ZA_sigout->GetZaxis()->SetLabelFont(42);
   ZA_sigout->GetZaxis()->SetLabelOffset(0.007);
   ZA_sigout->GetZaxis()->SetTitleSize(0.06);
   ZA_sigout->GetZaxis()->SetTitleFont(42);
   hs->Add(ZA_sigout,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.62,0.45,0.85,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ZA_sig","EWK in fid.[20.01]","lpf");

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
   entry=leg->AddEntry("ZA_sigout","EWK out fid. [0.89]","lpf");
   entry->SetFillColor(1);
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("t_ZA","ZA [86.38]","lpf");

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
   entry=leg->AddEntry("plj","non-prompt [60.50]","lpf");

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
   entry=leg->AddEntry("WA","WA [0.00]","lpf");

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
   entry=leg->AddEntry("VV","VV [0.64]","lpf");

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
   entry=leg->AddEntry("TTA","TTA [1.56]","lpf");

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
   entry=leg->AddEntry("ST","ST  [0.39]","lpf");

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
      tex = new TLatex(0.76,0.92,"136 fb^{-1} (13 TeV)");
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
