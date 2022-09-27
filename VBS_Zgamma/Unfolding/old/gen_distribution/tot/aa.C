void aa()
{
//=========Macro generated from canvas: /
//=========  (Thu Nov 14 02:24:56 2019) by ROOT version6.06/09
   TCanvas * = new TCanvas("", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c1->Range(-27.5,-298.0344,447.5,2682.309);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   THStack *hs = new THStack();
   hs->SetName("hs");
   hs->SetTitle("");
   Double_t xAxis1[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",5, xAxis1);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(2384.275);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_1->SetLineColor(ci);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"20~50");
   hs_stack_1->GetXaxis()->SetBinLabel(2,"50~80");
   hs_stack_1->GetXaxis()->SetBinLabel(3,"80~120");
   hs_stack_1->GetXaxis()->SetBinLabel(4,"120~200");
   hs_stack_1->GetXaxis()->SetBinLabel(5,"200~400");
   hs_stack_1->GetXaxis()->SetLabelFont(42);
   hs_stack_1->GetXaxis()->SetLabelSize(0.035);
   hs_stack_1->GetXaxis()->SetTitleSize(0.035);
   hs_stack_1->GetXaxis()->SetTitleFont(42);
   hs_stack_1->GetYaxis()->SetTitle("Events /bin");
   hs_stack_1->GetYaxis()->SetLabelFont(42);
   hs_stack_1->GetYaxis()->SetLabelSize(0.035);
   hs_stack_1->GetYaxis()->SetTitleSize(0.035);
   hs_stack_1->GetYaxis()->SetTitleOffset(0.8);
   hs_stack_1->GetYaxis()->SetTitleFont(42);
   hs_stack_1->GetZaxis()->SetLabelFont(42);
   hs_stack_1->GetZaxis()->SetLabelSize(0.035);
   hs_stack_1->GetZaxis()->SetTitleSize(0.035);
   hs_stack_1->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_1);
   
   Double_t xAxis2[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__1 = new TH1D("hist__1","ST		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis2);
   hist__1->SetBinContent(1,0.9638156);
   hist__1->SetBinContent(2,0.5606294);
   hist__1->SetBinContent(3,0.6699135);
   hist__1->SetBinContent(4,0.4554236);
   hist__1->SetBinError(1,0.432932);
   hist__1->SetBinError(2,0.3254452);
   hist__1->SetBinError(3,0.3916325);
   hist__1->SetBinError(4,0.3276737);
   hist__1->SetEntries(13);

   ci = TColor::GetColor("#00ff00");
   hist__1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist__1->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist__1->SetMarkerColor(ci);
   hist__1->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   
   TH1D *hist__2 = new TH1D("hist__2","TTA		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis3);
   hist__2->SetBinContent(1,5.22514);
   hist__2->SetBinContent(2,10.5285);
   hist__2->SetBinContent(3,3.570055);
   hist__2->SetBinContent(4,1.19334);
   hist__2->SetBinContent(5,0.2135688);
   hist__2->SetBinError(1,1.257757);
   hist__2->SetBinError(2,1.568942);
   hist__2->SetBinError(3,1.08725);
   hist__2->SetBinError(4,0.5830126);
   hist__2->SetBinError(5,0.2246982);
   hist__2->SetEntries(1227);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetLineColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist__2->SetMarkerColor(ci);
   hist__2->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   
   TH1D *hist__3 = new TH1D("hist__3","VV		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis4);
   hist__3->SetBinContent(1,2.214078);
   hist__3->SetBinContent(2,12.77324);
   hist__3->SetBinContent(3,10.68554);
   hist__3->SetBinContent(4,5.700646);
   hist__3->SetBinContent(5,3.910991);
   hist__3->SetBinError(1,1.565236);
   hist__3->SetBinError(2,3.546385);
   hist__3->SetBinError(3,3.547322);
   hist__3->SetBinError(4,2.446715);
   hist__3->SetBinError(5,1.718364);
   hist__3->SetEntries(59);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetLineColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist__3->SetMarkerColor(ci);
   hist__3->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   
   TH1D *hist__4 = new TH1D("hist__4","WA		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis5);

   ci = TColor::GetColor("#000099");
   hist__4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   hist__4->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   hist__4->SetMarkerColor(ci);
   hist__4->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   
   TH1D *hist__5 = new TH1D("hist__5","plj		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis6);
   hist__5->SetBinContent(1,619.6539);
   hist__5->SetBinContent(2,755.0196);
   hist__5->SetBinContent(3,260.8201);
   hist__5->SetBinContent(4,109.6678);
   hist__5->SetBinContent(5,34.72573);
   hist__5->SetBinError(1,14.42633);
   hist__5->SetBinError(2,15.81235);
   hist__5->SetBinError(3,9.038101);
   hist__5->SetBinError(4,5.927172);
   hist__5->SetBinError(5,3.463159);
   hist__5->SetEntries(6038);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetLineColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist__5->SetMarkerColor(ci);
   hist__5->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   hist__5->GetYaxis()->SetTitleOffset(0);
   hist__5->GetYaxis()->SetTitleFont(42);
   hist__5->GetZaxis()->SetLabelFont(42);
   hist__5->GetZaxis()->SetLabelSize(0.035);
   hist__5->GetZaxis()->SetTitleSize(0.035);
   hist__5->GetZaxis()->SetTitleFont(42);
   hs->Add(hist,"");
   Double_t xAxis7[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__6 = new TH1D("hist__6","ZA		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis7);
   hist__6->SetBinContent(1,162.7269);
   hist__6->SetBinContent(2,415.8647);
   hist__6->SetBinContent(3,211.3666);
   hist__6->SetBinContent(4,128.6243);
   hist__6->SetBinContent(5,57.75764);
   hist__6->SetBinError(1,7.389332);
   hist__6->SetBinError(2,11.9019);
   hist__6->SetBinError(3,8.914952);
   hist__6->SetBinError(4,7.143606);
   hist__6->SetBinError(5,4.602574);
   hist__6->SetEntries(10821);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetLineColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist__6->SetMarkerColor(ci);
   hist__6->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   
   TH1D *hist__7 = new TH1D("hist__7","ZA-EWK		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis8);
   hist__7->SetBinContent(1,26.87927);
   hist__7->SetBinContent(2,106.5966);
   hist__7->SetBinContent(3,72.31504);
   hist__7->SetBinContent(4,53.57593);
   hist__7->SetBinContent(5,24.52539);
   hist__7->SetBinError(1,0.6808717);
   hist__7->SetBinError(2,1.359903);
   hist__7->SetBinError(3,1.122353);
   hist__7->SetBinError(4,0.9657239);
   hist__7->SetBinError(5,0.6532223);
   hist__7->SetEntries(17524);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetLineColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist__7->SetMarkerColor(ci);
   hist__7->SetMarkerStyle(21);
   hist__7->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   hist3__8->SetBinContent(1,4.309133);
   hist3__8->SetBinContent(2,11.39496);
   hist3__8->SetBinContent(3,7.409641);
   hist3__8->SetBinContent(4,4.979107);
   hist3__8->SetBinContent(5,2.23584);
   hist3__8->SetBinError(1,0.2757796);
   hist3__8->SetBinError(2,0.444443);
   hist3__8->SetBinError(3,0.3544891);
   hist3__8->SetBinError(4,0.2917299);
   hist3__8->SetBinError(5,0.1975135);
   hist3__8->SetEntries(1876);

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
   Double_t xAxis10[6] = {20, 50, 80, 120, 200, 400}; 
   
   TH1D *hist__9 = new TH1D("hist__9","Data16		 20<leading p_{T}^{reco}<400  reco && gen",5, xAxis10);
   hist__9->SetBinContent(1,598);
   hist__9->SetBinContent(2,958);
   hist__9->SetBinContent(3,377);
   hist__9->SetBinContent(4,177);
   hist__9->SetBinContent(5,86);
   hist__9->SetEntries(2196);

   ci = TColor::GetColor("#000099");
   hist__9->SetLineColor(ci);
   hist__9->GetXaxis()->SetTitle("leding p_{T}^{reco}");
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
   hs->Add(hist,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.82,0.7,0.95,0.88,NULL,"brNDC");
   leg->SetBorderSize(1);
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
   c1->Modified();
   ->cd();
   ->SetSelected();
}
