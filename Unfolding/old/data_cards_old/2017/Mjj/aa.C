void aa()
{
//=========Macro generated from canvas: /
//=========  (Tue Jan 21 11:51:44 2020) by ROOT version6.06/09
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
   pad1->Range(218.75,-47.01568,2093.75,314.6434);
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
   Double_t xAxis1[4] = {500, 1000, 1500, 2000}; 
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",3, xAxis1);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(282.0941);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"100~150");
   hs_stack_1->GetXaxis()->SetBinLabel(2,"150~200");
   hs_stack_1->GetXaxis()->SetBinLabel(3,"200~400");
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
   
   Double_t xAxis2[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist__1 = new TH1D("hist__1","ST		 500<leading p_{T}^{reco}<2000  reco && gen",3, xAxis2);
   hist__1->SetBinContent(1,0.5240936);
   hist__1->SetBinError(1,0.3025906);
   hist__1->SetEntries(3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   hist__1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist__1->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist__1->SetMarkerColor(ci);
   hist__1->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist__1->GetXaxis()->SetBinLabel(1,"100~150");
   hist__1->GetXaxis()->SetBinLabel(2,"150~200");
   hist__1->GetXaxis()->SetBinLabel(3,"200~400");
   hist__1->GetXaxis()->SetLabelFont(42);
   hist__1->GetXaxis()->SetLabelSize(0.035);
   hist__1->GetXaxis()->SetTitleSize(0.035);
   hist__1->GetXaxis()->SetTitleFont(42);
   hist__1->GetYaxis()->SetTitle("yields");
   hist__1->GetYaxis()->SetLabelFont(42);
   hist__1->GetYaxis()->SetLabelSize(0.035);
   hist__1->GetYaxis()->SetTitleSize(0.035);
   hist__1->GetYaxis()->SetTitleFont(42);
   hist__1->GetZaxis()->SetLabelFont(42);
   hist__1->GetZaxis()->SetLabelSize(0.035);
   hist__1->GetZaxis()->SetTitleSize(0.035);
   hist__1->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis3[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist__2 = new TH1D("hist__2","TTA		 500<leading p_{T}^{reco}<2000  reco && gen",3, xAxis3);
   hist__2->SetBinContent(1,4.581866);
   hist__2->SetBinContent(2,0.5933724);
   hist__2->SetBinContent(3,0.3761974);
   hist__2->SetBinError(1,0.8185492);
   hist__2->SetBinError(2,0.387988);
   hist__2->SetBinError(3,0.2074295);
   hist__2->SetEntries(407);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetLineColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetMarkerColor(ci);
   hist__2->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist__2->GetXaxis()->SetBinLabel(1,"100~150");
   hist__2->GetXaxis()->SetBinLabel(2,"150~200");
   hist__2->GetXaxis()->SetBinLabel(3,"200~400");
   hist__2->GetXaxis()->SetLabelFont(42);
   hist__2->GetXaxis()->SetLabelSize(0.035);
   hist__2->GetXaxis()->SetTitleSize(0.035);
   hist__2->GetXaxis()->SetTitleFont(42);
   hist__2->GetYaxis()->SetTitle("yields");
   hist__2->GetYaxis()->SetLabelFont(42);
   hist__2->GetYaxis()->SetLabelSize(0.035);
   hist__2->GetYaxis()->SetTitleSize(0.035);
   hist__2->GetYaxis()->SetTitleFont(42);
   hist__2->GetZaxis()->SetLabelFont(42);
   hist__2->GetZaxis()->SetLabelSize(0.035);
   hist__2->GetZaxis()->SetTitleSize(0.035);
   hist__2->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis4[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist__3 = new TH1D("hist__3","VV		 500<leading p_{T}^{reco}<2000  reco && gen",3, xAxis4);
   hist__3->SetBinContent(1,4.46068);
   hist__3->SetBinContent(2,0.7613676);
   hist__3->SetBinContent(3,0.9327001);
   hist__3->SetBinError(1,1.083701);
   hist__3->SetBinError(2,0.4410936);
   hist__3->SetBinError(3,0.4670507);
   hist__3->SetEntries(24);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetLineColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetMarkerColor(ci);
   hist__3->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist__3->GetXaxis()->SetBinLabel(1,"100~150");
   hist__3->GetXaxis()->SetBinLabel(2,"150~200");
   hist__3->GetXaxis()->SetBinLabel(3,"200~400");
   hist__3->GetXaxis()->SetLabelFont(42);
   hist__3->GetXaxis()->SetLabelSize(0.035);
   hist__3->GetXaxis()->SetTitleSize(0.035);
   hist__3->GetXaxis()->SetTitleFont(42);
   hist__3->GetYaxis()->SetTitle("yields");
   hist__3->GetYaxis()->SetLabelFont(42);
   hist__3->GetYaxis()->SetLabelSize(0.035);
   hist__3->GetYaxis()->SetTitleSize(0.035);
   hist__3->GetYaxis()->SetTitleFont(42);
   hist__3->GetZaxis()->SetLabelFont(42);
   hist__3->GetZaxis()->SetLabelSize(0.035);
   hist__3->GetZaxis()->SetTitleSize(0.035);
   hist__3->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis5[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist__4 = new TH1D("hist__4","WA		 500<leading p_{T}^{reco}<2000  reco && gen",3, xAxis5);

   ci = TColor::GetColor("#000099");
   hist__4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   hist__4->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   hist__4->SetMarkerColor(ci);
   hist__4->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist__4->GetXaxis()->SetBinLabel(1,"100~150");
   hist__4->GetXaxis()->SetBinLabel(2,"150~200");
   hist__4->GetXaxis()->SetBinLabel(3,"200~400");
   hist__4->GetXaxis()->SetLabelFont(42);
   hist__4->GetXaxis()->SetLabelSize(0.035);
   hist__4->GetXaxis()->SetTitleSize(0.035);
   hist__4->GetXaxis()->SetTitleFont(42);
   hist__4->GetYaxis()->SetTitle("yields");
   hist__4->GetYaxis()->SetLabelFont(42);
   hist__4->GetYaxis()->SetLabelSize(0.035);
   hist__4->GetYaxis()->SetTitleSize(0.035);
   hist__4->GetYaxis()->SetTitleFont(42);
   hist__4->GetZaxis()->SetLabelFont(42);
   hist__4->GetZaxis()->SetLabelSize(0.035);
   hist__4->GetZaxis()->SetTitleSize(0.035);
   hist__4->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis6[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist__5 = new TH1D("hist__5","plj		 500<leading p_{T}^{reco}<2000  reco && gen",3, xAxis6);
   hist__5->SetBinContent(1,5.31787);
   hist__5->SetBinContent(2,1.433952);
   hist__5->SetBinError(1,1.298439);
   hist__5->SetBinError(2,0.6249081);
   hist__5->SetEntries(24);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetLineColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetMarkerColor(ci);
   hist__5->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist__5->GetXaxis()->SetBinLabel(1,"100~150");
   hist__5->GetXaxis()->SetBinLabel(2,"150~200");
   hist__5->GetXaxis()->SetBinLabel(3,"200~400");
   hist__5->GetXaxis()->SetLabelFont(42);
   hist__5->GetXaxis()->SetLabelSize(0.035);
   hist__5->GetXaxis()->SetTitleSize(0.035);
   hist__5->GetXaxis()->SetTitleFont(42);
   hist__5->GetYaxis()->SetTitle("yields");
   hist__5->GetYaxis()->SetLabelFont(42);
   hist__5->GetYaxis()->SetLabelSize(0.035);
   hist__5->GetYaxis()->SetTitleSize(0.035);
   hist__5->GetYaxis()->SetTitleFont(42);
   hist__5->GetZaxis()->SetLabelFont(42);
   hist__5->GetZaxis()->SetLabelSize(0.035);
   hist__5->GetZaxis()->SetTitleSize(0.035);
   hist__5->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis7[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist__6 = new TH1D("hist__6","ZA		 500<leading p_{T}^{reco}<2000  reco && gen",3, xAxis7);
   hist__6->SetBinContent(1,212.9773);
   hist__6->SetBinContent(2,36.95134);
   hist__6->SetBinContent(3,13.61467);
   hist__6->SetBinError(1,6.350752);
   hist__6->SetBinError(2,2.655556);
   hist__6->SetBinError(3,1.566845);
   hist__6->SetEntries(3973);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetLineColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetMarkerColor(ci);
   hist__6->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist__6->GetXaxis()->SetBinLabel(1,"100~150");
   hist__6->GetXaxis()->SetBinLabel(2,"150~200");
   hist__6->GetXaxis()->SetBinLabel(3,"200~400");
   hist__6->GetXaxis()->SetLabelFont(42);
   hist__6->GetXaxis()->SetLabelSize(0.035);
   hist__6->GetXaxis()->SetTitleSize(0.035);
   hist__6->GetXaxis()->SetTitleFont(42);
   hist__6->GetYaxis()->SetTitle("yields");
   hist__6->GetYaxis()->SetLabelFont(42);
   hist__6->GetYaxis()->SetLabelSize(0.035);
   hist__6->GetYaxis()->SetTitleSize(0.035);
   hist__6->GetYaxis()->SetTitleFont(42);
   hist__6->GetZaxis()->SetLabelFont(42);
   hist__6->GetZaxis()->SetLabelSize(0.035);
   hist__6->GetZaxis()->SetTitleSize(0.035);
   hist__6->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis8[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist__7 = new TH1D("hist__7","ZA-EWK		 500<leading p_{T}^{reco}<2000  reco && gen",3, xAxis8);
   hist__7->SetBinContent(1,35.20639);
   hist__7->SetBinContent(2,21.51253);
   hist__7->SetBinContent(3,22.81214);
   hist__7->SetBinError(1,0.706499);
   hist__7->SetBinError(2,0.5524735);
   hist__7->SetBinError(3,0.5734918);
   hist__7->SetEntries(5658);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetLineColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetMarkerColor(ci);
   hist__7->SetMarkerStyle(21);
   hist__7->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist__7->GetXaxis()->SetBinLabel(1,"100~150");
   hist__7->GetXaxis()->SetBinLabel(2,"150~200");
   hist__7->GetXaxis()->SetBinLabel(3,"200~400");
   hist__7->GetXaxis()->SetLabelFont(42);
   hist__7->GetXaxis()->SetLabelSize(0.035);
   hist__7->GetXaxis()->SetTitleSize(0.035);
   hist__7->GetXaxis()->SetTitleFont(42);
   hist__7->GetYaxis()->SetTitle("yields");
   hist__7->GetYaxis()->SetLabelFont(42);
   hist__7->GetYaxis()->SetLabelSize(0.035);
   hist__7->GetYaxis()->SetTitleSize(0.035);
   hist__7->GetYaxis()->SetTitleFont(42);
   hist__7->GetZaxis()->SetLabelFont(42);
   hist__7->GetZaxis()->SetLabelSize(0.035);
   hist__7->GetZaxis()->SetTitleSize(0.035);
   hist__7->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis9[4] = {500, 1000, 1500, 2000}; 
   
   TH1D *hist3__8 = new TH1D("hist3__8","ZA-EWK		 500<leading p_{T}^{reco}<2000 reco out of gen",3, xAxis9);
   hist3__8->SetBinContent(1,5.592814);
   hist3__8->SetBinContent(2,1.748351);
   hist3__8->SetBinContent(3,1.019309);
   hist3__8->SetBinError(1,0.2815162);
   hist3__8->SetBinError(2,0.1577202);
   hist3__8->SetBinError(3,0.123602);
   hist3__8->SetEntries(594);

   ci = TColor::GetColor("#ffcc00");
   hist3__8->SetFillColor(ci);

   ci = TColor::GetColor("#ffcc00");
   hist3__8->SetLineColor(ci);

   ci = TColor::GetColor("#ffcc00");
   hist3__8->SetMarkerColor(ci);
   hist3__8->SetMarkerStyle(21);
   hist3__8->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist3__8->GetXaxis()->SetBinLabel(1,"100~150");
   hist3__8->GetXaxis()->SetBinLabel(2,"150~200");
   hist3__8->GetXaxis()->SetBinLabel(3,"200~400");
   hist3__8->GetXaxis()->SetLabelFont(42);
   hist3__8->GetXaxis()->SetLabelSize(0.035);
   hist3__8->GetXaxis()->SetTitleSize(0.035);
   hist3__8->GetXaxis()->SetTitleFont(42);
   hist3__8->GetYaxis()->SetTitle("yields");
   hist3__8->GetYaxis()->SetLabelFont(42);
   hist3__8->GetYaxis()->SetLabelSize(0.035);
   hist3__8->GetYaxis()->SetTitleSize(0.035);
   hist3__8->GetYaxis()->SetTitleFont(42);
   hist3__8->GetZaxis()->SetLabelFont(42);
   hist3__8->GetZaxis()->SetLabelSize(0.035);
   hist3__8->GetZaxis()->SetTitleSize(0.035);
   hist3__8->GetZaxis()->SetTitleFont(42);
   hs->Add(hist3,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.82,0.7,0.95,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hist","ST","lpf");

   ci = TColor::GetColor("#00ff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist","TTA","lpf");

   ci = TColor::GetColor("#00ffff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ffff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist","VV","lpf");

   ci = TColor::GetColor("#6666cc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#6666cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#6666cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist","WA","lpf");

   ci = TColor::GetColor("#000099");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist","non-prompt","lpf");

   ci = TColor::GetColor("#ffff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ffff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist","ZA","lpf");

   ci = TColor::GetColor("#ff00ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff00ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff00ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist","ZA_sig","lpf");

   ci = TColor::GetColor("#ff3333");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff3333");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff3333");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist3","ZA_sig_out","lpf");

   ci = TColor::GetColor("#ffcc00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffcc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ffcc00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
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
      tex = new TLatex(0.76,0.92,"35.862 fb^{-1} (13 TeV)");
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
