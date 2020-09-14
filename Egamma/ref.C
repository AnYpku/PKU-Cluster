void ref()
{
//=========Macro generated from canvas: 120_200_seed0/
//=========  (Tue May 21 18:05:34 2019) by ROOT version6.06/01
   TCanvas *120_200_seed0 = new TCanvas("120_200_seed0", "",40,63,900,602);
   120_200_seed0->Range(-0.3128125,0.2125,2.815313,1.0875);
   120_200_seed0->SetFillColor(0);
   120_200_seed0->SetBorderMode(0);
   120_200_seed0->SetBorderSize(2);
   120_200_seed0->SetFrameBorderMode(0);
   120_200_seed0->SetFrameBorderMode(0);
   
   Double_t Graph0_fx3001[10] = {
   0.125,
   0.375,
   0.625,
   0.875,
   1.125,
   1.375,
   1.625,
   1.875,
   2.125,
   2.375};
   Double_t Graph0_fy3001[10] = {
   0.7028672,
   0.7072556,
   0.7150138,
   0.6966106,
   0.6750811,
   0.6503274,
   0,
   0,
   0,
   0};
   Double_t Graph0_felx3001[10] = {
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125};
   Double_t Graph0_fely3001[10] = {
   0.005409705,
   0.005334385,
   0.005396414,
   0.00549217,
   0.005656901,
   0.006644116,
   0,
   0,
   0,
   0};
   Double_t Graph0_fehx3001[10] = {
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125};
   Double_t Graph0_fehy3001[10] = {
   0.005354137,
   0.005278712,
   0.005336417,
   0.005437305,
   0.005606898,
   0.006587066,
   1,
   1,
   1,
   1};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(10,Graph0_fx3001,Graph0_fy3001,Graph0_felx3001,Graph0_fehx3001,Graph0_fely3001,Graph0_fehy3001);
   grae->SetName("Graph0");
   grae->SetTitle("seed/gen efficiency vs eleTruthEta 120_200");
   grae->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff6666");
   grae->SetLineColor(ci);
   grae->SetLineWidth(4);
   
   TH1F *Graph_Graph3001 = new TH1F("Graph_Graph3001","seed/gen efficiency vs eleTruthEta 120_200",100,0,2.75);
   Graph_Graph3001->SetMinimum(0.3);
   Graph_Graph3001->SetMaximum(1);
   Graph_Graph3001->SetDirectory(0);
   Graph_Graph3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3001->SetLineColor(ci);
   Graph_Graph3001->GetXaxis()->SetRange(1,91);
   Graph_Graph3001->GetXaxis()->SetLabelFont(42);
   Graph_Graph3001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph3001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph3001->GetXaxis()->SetTitleFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph3001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph3001->GetYaxis()->SetTitleFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph3001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3001);
   
   grae->Draw("ape");
   
   Double_t Graph1_fx3002[10] = {
   0.1226169,
   0.3734243,
   0.6242316,
   0.8715555,
   1.122363,
   1.37317,
   1.623978,
   1.874785,
   2.122109,
   2.372916};
   Double_t Graph1_fy3002[10] = {
   0.7033537,
   0.7079268,
   0.7155488,
   0.6972561,
   0.6759146,
   0.6042683,
   0.3969512,
   0.0006097464,
   0.0006097464,
   0.0006097464};
   Double_t Graph1_felx3002[10] = {
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125};
   Double_t Graph1_fely3002[10] = {
   0.005409705,
   0.005334385,
   0.005396414,
   0.00549217,
   0.005656901,
   0.005993678,
   0.01175079,
   0,
   0,
   0};
   Double_t Graph1_fehx3002[10] = {
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125,
   0.125};
   Double_t Graph1_fehy3002[10] = {
   0.005354137,
   0.005278712,
   0.005336417,
   0.005437305,
   0.005606898,
   0.00596306,
   0.01186968,
   1,
   1,
   1};
   grae = new TGraphAsymmErrors(10,Graph1_fx3002,Graph1_fy3002,Graph1_felx3002,Graph1_fehx3002,Graph1_fely3002,Graph1_fehy3002);
   grae->SetName("Graph1");
   grae->SetTitle("Graph");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);
   grae->SetLineStyle(2);
   grae->SetLineWidth(2);
   
   TH1F *Graph_Graph3002 = new TH1F("Graph_Graph3002","Graph",100,0,2.75);
   Graph_Graph3002->SetMinimum(0);
   Graph_Graph3002->SetMaximum(1.1);
   Graph_Graph3002->SetDirectory(0);
   Graph_Graph3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3002->SetLineColor(ci);
   Graph_Graph3002->GetXaxis()->SetLabelFont(42);
   Graph_Graph3002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph3002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph3002->GetXaxis()->SetTitleFont(42);
   Graph_Graph3002->GetYaxis()->SetLabelFont(42);
   Graph_Graph3002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph3002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph3002->GetYaxis()->SetTitleFont(42);
   Graph_Graph3002->GetZaxis()->SetLabelFont(42);
   Graph_Graph3002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph3002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3002);
   
   grae->Draw("P");
   
   TLegend *leg = new TLegend(0.1948775,0.21777,0.3942094,0.4181185,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(30);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph0","Barrel","l");

   ci = TColor::GetColor("#ff6666");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(4);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(30);
   entry=leg->AddEntry("Graph1","Endcap","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(30);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.1581514,0.9343728,0.8418486,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *AText = pt->AddText("seed/gen efficiency vs eleTruthEta 120_200");
   pt->Draw();
   120_200_seed0->Modified();
   120_200_seed0->cd();
   120_200_seed0->SetSelected(120_200_seed0);
}
