void aa()
{
//=========Macro generated from canvas: /
//=========  (Sun Sep 30 02:17:25 2018) by ROOT version6.06/09
   TCanvas * = new TCanvas("", "",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   ->SetHighLightColor(2);
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
   pad1->Range(-1.6875,-4.956664,9.5625,33.17152);
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
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",9,0,9);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(29.73998);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 500~750");
   hs_stack_1->GetXaxis()->SetBinLabel(2,"Mjj 750~1000");
   hs_stack_1->GetXaxis()->SetBinLabel(3,"Mjj 1000~2000");
   hs_stack_1->GetXaxis()->SetBinLabel(4,"Mjj 500~750");
   hs_stack_1->GetXaxis()->SetBinLabel(5,"Mjj 750~1000");
   hs_stack_1->GetXaxis()->SetBinLabel(6,"Mjj 1000~2000");
   hs_stack_1->GetXaxis()->SetBinLabel(7,"Mjj 500~750");
   hs_stack_1->GetXaxis()->SetBinLabel(8,"Mjj 750~1000");
   hs_stack_1->GetXaxis()->SetBinLabel(9,"Mjj 1000~2000");
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
   
   
   TH1D *unrolledsPhist__1 = new TH1D("unrolledsPhist__1","unrolled hist",9,0,9);
   unrolledsPhist__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   unrolledsPhist__1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   unrolledsPhist__1->SetLineColor(ci);
   unrolledsPhist__1->SetLineStyle(0);
   unrolledsPhist__1->SetLineWidth(2);

   ci = TColor::GetColor("#00ff00");
   unrolledsPhist__1->SetMarkerColor(ci);
   unrolledsPhist__1->SetMarkerStyle(20);
   unrolledsPhist__1->GetXaxis()->SetBinLabel(1,"Mjj 500~750");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(2,"Mjj 750~1000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(3,"Mjj 1000~2000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(4,"Mjj 500~750");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(5,"Mjj 750~1000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(6,"Mjj 1000~2000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(7,"Mjj 500~750");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(8,"Mjj 750~1000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(9,"Mjj 1000~2000");
   unrolledsPhist__1->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__1->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__1->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__1->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__1->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__1->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__1->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__1->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__1->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__1->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__1->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__1->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__1->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__1->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__2 = new TH1D("unrolledsPhist__2","unrolled hist",9,0,9);
   unrolledsPhist__2->SetBinContent(1,0.9517157);
   unrolledsPhist__2->SetBinContent(2,0.590825);
   unrolledsPhist__2->SetBinContent(3,0.02811163);
   unrolledsPhist__2->SetBinContent(4,0.1680295);
   unrolledsPhist__2->SetBinContent(5,0.0884086);
   unrolledsPhist__2->SetBinContent(6,0.2897538);
   unrolledsPhist__2->SetBinContent(7,0.04746371);
   unrolledsPhist__2->SetBinContent(8,0.05438872);
   unrolledsPhist__2->SetBinContent(9,0.01144246);
   unrolledsPhist__2->SetBinError(1,0.3066204);
   unrolledsPhist__2->SetBinError(2,0.1739046);
   unrolledsPhist__2->SetBinError(3,0.1116001);
   unrolledsPhist__2->SetBinError(4,0.1361718);
   unrolledsPhist__2->SetBinError(5,0.1280358);
   unrolledsPhist__2->SetBinError(6,0.1251712);
   unrolledsPhist__2->SetBinError(7,0.03449135);
   unrolledsPhist__2->SetBinError(8,0.03847438);
   unrolledsPhist__2->SetBinError(9,0.07666832);
   unrolledsPhist__2->SetEntries(9);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist__2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist__2->SetLineColor(ci);
   unrolledsPhist__2->SetLineStyle(0);
   unrolledsPhist__2->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist__2->SetMarkerColor(ci);
   unrolledsPhist__2->SetMarkerStyle(20);
   unrolledsPhist__2->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__2->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__2->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__2->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__2->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__2->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__2->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__2->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__2->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__2->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__2->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__2->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__2->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__2->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__3 = new TH1D("unrolledsPhist__3","unrolled hist",9,0,9);
   unrolledsPhist__3->SetBinContent(1,1.122424);
   unrolledsPhist__3->SetBinContent(4,0.8084084);
   unrolledsPhist__3->SetBinContent(5,0.4231735);
   unrolledsPhist__3->SetBinContent(6,0.3915569);
   unrolledsPhist__3->SetBinContent(9,0.4161644);
   unrolledsPhist__3->SetBinError(1,0.6559604);
   unrolledsPhist__3->SetBinError(4,0.578793);
   unrolledsPhist__3->SetBinError(5,0.4231735);
   unrolledsPhist__3->SetBinError(6,0.3915569);
   unrolledsPhist__3->SetBinError(9,0.4161644);
   unrolledsPhist__3->SetEntries(9);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist__3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist__3->SetLineColor(ci);
   unrolledsPhist__3->SetLineStyle(0);
   unrolledsPhist__3->SetLineWidth(2);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist__3->SetMarkerColor(ci);
   unrolledsPhist__3->SetMarkerStyle(20);
   unrolledsPhist__3->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__3->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__3->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__3->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__3->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__3->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__3->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__3->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__3->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__3->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__3->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__3->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__3->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__3->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__4 = new TH1D("unrolledsPhist__4","unrolled hist",9,0,9);
   unrolledsPhist__4->SetEntries(9);

   ci = TColor::GetColor("#000099");
   unrolledsPhist__4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   unrolledsPhist__4->SetLineColor(ci);
   unrolledsPhist__4->SetLineStyle(0);
   unrolledsPhist__4->SetLineWidth(2);

   ci = TColor::GetColor("#000099");
   unrolledsPhist__4->SetMarkerColor(ci);
   unrolledsPhist__4->SetMarkerStyle(20);
   unrolledsPhist__4->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__4->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__4->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__4->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__4->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__4->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__4->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__4->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__4->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__4->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__4->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__4->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__4->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__4->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__5 = new TH1D("unrolledsPhist__5","unrolled hist",9,0,9);
   unrolledsPhist__5->SetBinContent(1,5.266168);
   unrolledsPhist__5->SetBinContent(2,0.645113);
   unrolledsPhist__5->SetBinContent(4,4.004382);
   unrolledsPhist__5->SetBinContent(5,5.258899);
   unrolledsPhist__5->SetBinContent(6,1.485617);
   unrolledsPhist__5->SetBinContent(8,0.401971);
   unrolledsPhist__5->SetBinContent(9,3.964139);
   unrolledsPhist__5->SetBinError(1,1.4028);
   unrolledsPhist__5->SetBinError(2,0.4697858);
   unrolledsPhist__5->SetBinError(4,1.159261);
   unrolledsPhist__5->SetBinError(5,1.390626);
   unrolledsPhist__5->SetBinError(6,0.7472511);
   unrolledsPhist__5->SetBinError(8,0.401971);
   unrolledsPhist__5->SetBinError(9,1.225092);
   unrolledsPhist__5->SetEntries(9);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist__5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist__5->SetLineColor(ci);
   unrolledsPhist__5->SetLineStyle(0);
   unrolledsPhist__5->SetLineWidth(2);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist__5->SetMarkerColor(ci);
   unrolledsPhist__5->SetMarkerStyle(20);
   unrolledsPhist__5->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__5->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__5->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__5->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__5->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__5->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__5->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__5->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__5->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__5->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__5->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__5->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__5->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__5->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__6 = new TH1D("unrolledsPhist__6","unrolled hist",9,0,9);
   unrolledsPhist__6->SetBinContent(1,15.3567);
   unrolledsPhist__6->SetBinContent(2,4.835412);
   unrolledsPhist__6->SetBinContent(3,0.2147374);
   unrolledsPhist__6->SetBinContent(4,14.57749);
   unrolledsPhist__6->SetBinContent(5,3.335531);
   unrolledsPhist__6->SetBinContent(6,2.508244);
   unrolledsPhist__6->SetBinContent(7,0.967376);
   unrolledsPhist__6->SetBinContent(8,2.222767);
   unrolledsPhist__6->SetBinContent(9,3.767624);
   unrolledsPhist__6->SetBinError(1,2.191786);
   unrolledsPhist__6->SetBinError(2,1.173908);
   unrolledsPhist__6->SetBinError(3,0.5071005);
   unrolledsPhist__6->SetBinError(4,2.471143);
   unrolledsPhist__6->SetBinError(5,1.446956);
   unrolledsPhist__6->SetBinError(6,0.9280911);
   unrolledsPhist__6->SetBinError(7,0.5322123);
   unrolledsPhist__6->SetBinError(8,1.24097);
   unrolledsPhist__6->SetBinError(9,1.490906);
   unrolledsPhist__6->SetEntries(9);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist__6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist__6->SetLineColor(ci);
   unrolledsPhist__6->SetLineStyle(0);
   unrolledsPhist__6->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist__6->SetMarkerColor(ci);
   unrolledsPhist__6->SetMarkerStyle(20);
   unrolledsPhist__6->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__6->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__6->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__6->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__6->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__6->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__6->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__6->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__6->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__6->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__6->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__6->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__6->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__6->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__7 = new TH1D("unrolledsPhist__7","unrolled hist",9,0,9);
   unrolledsPhist__7->SetBinContent(1,5.626787);
   unrolledsPhist__7->SetBinContent(2,3.812465);
   unrolledsPhist__7->SetBinContent(3,6.369677);
   unrolledsPhist__7->SetBinContent(4,0.9534583);
   unrolledsPhist__7->SetBinContent(5,1.717846);
   unrolledsPhist__7->SetBinContent(6,7.791648);
   unrolledsPhist__7->SetBinContent(7,0.01430418);
   unrolledsPhist__7->SetBinContent(8,0.04849102);
   unrolledsPhist__7->SetBinContent(9,2.533077);
   unrolledsPhist__7->SetBinError(1,0.2682269);
   unrolledsPhist__7->SetBinError(2,0.2219269);
   unrolledsPhist__7->SetBinError(3,0.2867861);
   unrolledsPhist__7->SetBinError(4,0.110178);
   unrolledsPhist__7->SetBinError(5,0.1489814);
   unrolledsPhist__7->SetBinError(6,0.3161907);
   unrolledsPhist__7->SetBinError(7,0.01430418);
   unrolledsPhist__7->SetBinError(8,0.02350286);
   unrolledsPhist__7->SetBinError(9,0.1793081);
   unrolledsPhist__7->SetEntries(9);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist__7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist__7->SetLineColor(ci);
   unrolledsPhist__7->SetLineStyle(0);
   unrolledsPhist__7->SetLineWidth(2);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist__7->SetMarkerColor(ci);
   unrolledsPhist__7->SetMarkerStyle(21);
   unrolledsPhist__7->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__7->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__7->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__7->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__7->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__7->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__7->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__7->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__7->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__7->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__7->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__7->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__7->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__7->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.82,0.7,0.95,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("unrolled hist","ZA_sig","lpf");

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
   entry=leg->AddEntry("unrolled hist","ZA","lpf");

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
   entry=leg->AddEntry("unrolled hist","non-prompt","lpf");

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
   entry=leg->AddEntry("unrolled hist","WA","lpf");

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
   entry=leg->AddEntry("unrolled hist","VV","lpf");

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
   entry=leg->AddEntry("unrolled hist","TTA","lpf");

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
   entry=leg->AddEntry("unrolled hist","ST","lpf");

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
