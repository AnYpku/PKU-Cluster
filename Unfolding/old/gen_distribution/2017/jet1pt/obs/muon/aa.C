void aa()
{
//=========Macro generated from canvas: /
//=========  (Sat Oct 12 03:13:04 2019) by ROOT version6.06/01
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
   pad1->Range(-51.25,-20.72017,423.75,138.6657);
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
   Double_t xAxis1[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",5, xAxis1);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(124.321);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"20~50");
   hs_stack_1->GetXaxis()->SetBinLabel(2,"50~80");
   hs_stack_1->GetXaxis()->SetBinLabel(3,"80~120");
   hs_stack_1->GetXaxis()->SetBinLabel(4,"120~200");
   hs_stack_1->GetXaxis()->SetBinLabel(5,"200~400");
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
   
   Double_t xAxis2[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__1 = new TH1D("hist__1","ST		 20<leading p_{T}^{reco}<400",5, xAxis2);
   hist__1->SetBinContent(1,0.1849056);
   hist__1->SetBinContent(3,0.1849056);
   hist__1->SetBinContent(4,0.1849056);
   hist__1->SetBinError(1,0.1849056);
   hist__1->SetBinError(3,0.1849056);
   hist__1->SetBinError(4,0.1849056);
   hist__1->SetEntries(3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   hist__1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist__1->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist__1->SetMarkerColor(ci);
   hist__1->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__1->GetXaxis()->SetBinLabel(1,"20~50");
   hist__1->GetXaxis()->SetBinLabel(2,"50~80");
   hist__1->GetXaxis()->SetBinLabel(3,"80~120");
   hist__1->GetXaxis()->SetBinLabel(4,"120~200");
   hist__1->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis3[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__2 = new TH1D("hist__2","TTA		 20<leading p_{T}^{reco}<400",5, xAxis3);
   hist__2->SetBinContent(1,1.387669);
   hist__2->SetBinContent(2,1.304409);
   hist__2->SetBinContent(3,0.7215877);
   hist__2->SetBinContent(4,0.3885472);
   hist__2->SetBinContent(5,0.1110135);
   hist__2->SetBinError(1,0.3575772);
   hist__2->SetBinError(2,0.4326323);
   hist__2->SetBinError(3,0.2690789);
   hist__2->SetBinError(4,0.1618286);
   hist__2->SetBinError(5,0.0679816);
   hist__2->SetEntries(543);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetLineColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetMarkerColor(ci);
   hist__2->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__2->GetXaxis()->SetBinLabel(1,"20~50");
   hist__2->GetXaxis()->SetBinLabel(2,"50~80");
   hist__2->GetXaxis()->SetBinLabel(3,"80~120");
   hist__2->GetXaxis()->SetBinLabel(4,"120~200");
   hist__2->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis4[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__3 = new TH1D("hist__3","VV		 20<leading p_{T}^{reco}<400",5, xAxis4);
   hist__3->SetBinContent(1,0.7210022);
   hist__3->SetBinContent(2,2.835837);
   hist__3->SetBinContent(3,1.268901);
   hist__3->SetBinContent(4,1.864971);
   hist__3->SetBinContent(5,0.4229669);
   hist__3->SetBinError(1,0.5174225);
   hist__3->SetBinError(2,1.078068);
   hist__3->SetBinError(3,0.7326001);
   hist__3->SetBinError(4,0.8451941);
   hist__3->SetBinError(5,0.4229669);
   hist__3->SetEntries(18);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetLineColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetMarkerColor(ci);
   hist__3->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__3->GetXaxis()->SetBinLabel(1,"20~50");
   hist__3->GetXaxis()->SetBinLabel(2,"50~80");
   hist__3->GetXaxis()->SetBinLabel(3,"80~120");
   hist__3->GetXaxis()->SetBinLabel(4,"120~200");
   hist__3->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis5[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__4 = new TH1D("hist__4","WA		 20<leading p_{T}^{reco}<400",5, xAxis5);

   ci = TColor::GetColor("#000099");
   hist__4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   hist__4->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   hist__4->SetMarkerColor(ci);
   hist__4->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__4->GetXaxis()->SetBinLabel(1,"20~50");
   hist__4->GetXaxis()->SetBinLabel(2,"50~80");
   hist__4->GetXaxis()->SetBinLabel(3,"80~120");
   hist__4->GetXaxis()->SetBinLabel(4,"120~200");
   hist__4->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis6[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__5 = new TH1D("hist__5","plj_mu		 20<leading p_{T}^{reco}<400",5, xAxis6);
   hist__5->SetBinContent(1,54.31445);
   hist__5->SetBinContent(2,78.03556);
   hist__5->SetBinContent(3,30.60686);
   hist__5->SetBinContent(4,20.9994);
   hist__5->SetBinContent(5,7.736059);
   hist__5->SetBinError(1,4.913999);
   hist__5->SetBinError(2,5.889867);
   hist__5->SetBinError(3,3.742454);
   hist__5->SetBinError(4,3.060595);
   hist__5->SetBinError(5,1.862131);
   hist__5->SetEntries(450);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetLineColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetMarkerColor(ci);
   hist__5->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__5->GetXaxis()->SetBinLabel(1,"20~50");
   hist__5->GetXaxis()->SetBinLabel(2,"50~80");
   hist__5->GetXaxis()->SetBinLabel(3,"80~120");
   hist__5->GetXaxis()->SetBinLabel(4,"120~200");
   hist__5->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis7[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__6 = new TH1D("hist__6","ZA_total		 20<leading p_{T}^{reco}<400",5, xAxis7);
   hist__6->SetBinContent(1,8.720852);
   hist__6->SetBinContent(2,28.64007);
   hist__6->SetBinContent(3,12.78398);
   hist__6->SetBinContent(4,8.52265);
   hist__6->SetBinContent(5,5.747834);
   hist__6->SetBinError(1,1.237766);
   hist__6->SetBinError(2,2.13239);
   hist__6->SetBinError(3,1.582509);
   hist__6->SetBinError(4,1.229806);
   hist__6->SetBinError(5,0.919021);
   hist__6->SetEntries(1114);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetLineColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetMarkerColor(ci);
   hist__6->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__6->GetXaxis()->SetBinLabel(1,"20~50");
   hist__6->GetXaxis()->SetBinLabel(2,"50~80");
   hist__6->GetXaxis()->SetBinLabel(3,"80~120");
   hist__6->GetXaxis()->SetBinLabel(4,"120~200");
   hist__6->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis8[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__7 = new TH1D("hist__7","ZA-EWK		 20<leading p_{T}^{reco}<400",5, xAxis8);
   hist__7->SetBinContent(1,0.1524876);
   hist__7->SetBinContent(2,0.6088533);
   hist__7->SetBinContent(3,0.401514);
   hist__7->SetBinContent(4,0.2987586);
   hist__7->SetBinContent(5,0.1363978);
   hist__7->SetBinError(1,0.007467349);
   hist__7->SetBinError(2,0.01492126);
   hist__7->SetBinError(3,0.01211712);
   hist__7->SetBinError(4,0.01045224);
   hist__7->SetBinError(5,0.007062408);
   hist__7->SetEntries(4370);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetLineColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetMarkerColor(ci);
   hist__7->SetMarkerStyle(21);
   hist__7->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__7->GetXaxis()->SetBinLabel(1,"20~50");
   hist__7->GetXaxis()->SetBinLabel(2,"50~80");
   hist__7->GetXaxis()->SetBinLabel(3,"80~120");
   hist__7->GetXaxis()->SetBinLabel(4,"120~200");
   hist__7->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis9[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist3__8 = new TH1D("hist3__8","ZA-EWK		 20<leading p_{T}^{reco}<400 reco out of gen",5, xAxis9);
   hist3__8->SetBinContent(1,1.101509);
   hist3__8->SetBinContent(2,6.976222);
   hist3__8->SetBinContent(3,6.359902);
   hist3__8->SetBinContent(4,6.005846);
   hist3__8->SetBinContent(5,3.540564);
   hist3__8->SetBinError(1,0.1201845);
   hist3__8->SetBinError(2,0.3024576);
   hist3__8->SetBinError(3,0.2887883);
   hist3__8->SetBinError(4,0.2806347);
   hist3__8->SetBinError(5,0.2154719);
   hist3__8->SetEntries(1829);

   ci = TColor::GetColor("#ffcc00");
   hist3__8->SetFillColor(ci);

   ci = TColor::GetColor("#ffcc00");
   hist3__8->SetLineColor(ci);

   ci = TColor::GetColor("#ffcc00");
   hist3__8->SetMarkerColor(ci);
   hist3__8->SetMarkerStyle(21);
   hist3__8->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist3__8->GetXaxis()->SetBinLabel(1,"20~50");
   hist3__8->GetXaxis()->SetBinLabel(2,"50~80");
   hist3__8->GetXaxis()->SetBinLabel(3,"80~120");
   hist3__8->GetXaxis()->SetBinLabel(4,"120~200");
   hist3__8->GetXaxis()->SetBinLabel(5,"200~400");
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
   Double_t xAxis10[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__9 = new TH1D("hist__9","DMuon		 20<leading p_{T}^{reco}<400",5, xAxis10);
   hist__9->SetBinContent(1,58);
   hist__9->SetBinContent(2,107);
   hist__9->SetBinContent(3,59);
   hist__9->SetBinContent(4,28);
   hist__9->SetBinContent(5,10);
   hist__9->SetEntries(262);

   ci = TColor::GetColor("#000099");
   hist__9->SetLineColor(ci);
   hist__9->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist__9->GetXaxis()->SetLabelFont(42);
   hist__9->GetXaxis()->SetLabelSize(0.035);
   hist__9->GetXaxis()->SetTitleSize(0.035);
   hist__9->GetXaxis()->SetTitleFont(42);
   hist__9->GetYaxis()->SetTitle("yields");
   hist__9->GetYaxis()->SetLabelFont(42);
   hist__9->GetYaxis()->SetLabelSize(0.035);
   hist__9->GetYaxis()->SetTitleSize(0.035);
   hist__9->GetYaxis()->SetTitleFont(42);
   hist__9->GetZaxis()->SetLabelFont(42);
   hist__9->GetZaxis()->SetLabelSize(0.035);
   hist__9->GetZaxis()->SetTitleSize(0.035);
   hist__9->GetZaxis()->SetTitleFont(42);
   hist__9->Draw("EP SAME");
   
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
   entry=leg->AddEntry("hist","Data","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
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
