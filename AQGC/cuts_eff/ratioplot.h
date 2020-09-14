
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"

class MyRatioPlot{

	public:	
    TCanvas *canvas;
    void DrawDiffPlot(vector<TH1D*> h, vector<TString> leg, TString xtitle, TString ytitle, double miny, double maxy, double minratio, double maxratio);
    void DrawRatioPlot(vector<TH1D*> h, vector<TString> leg, TString xtitle, TString ytitle, double miny, double maxy, double minratio, double maxratio,bool line=0);
      
  private:	
    TLegend *legend;
		TLine *line;
		TLatex *laxtex_parameters;
		TLatex *laxtex_tag;
		TPad *top_pad;
		TPad *bottom_pad;

    vector<int> color = {1, 2, 7, 4, 5};

};
void MyRatioPlot::DrawDiffPlot(vector<TH1D*> h, vector<TString> leg, TString xtitle, TString ytitle, double miny, double maxy, double minratio, double maxratio){ 
    canvas=new TCanvas("ratio_plot","",700,500);
      gStyle->SetPadBorderMode(0);
      gStyle->SetOptStat(0);
      //gStyle->SetPadGridX(1);
      //gStyle->SetPadGridY(1);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetPadTopMargin(0.07);
      gStyle->SetPadBottomMargin(0.3);
      gStyle->SetPadRightMargin(0.05);
      gStyle->SetPadLeftMargin(0.14);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetAxisColor(1, "XYZ");
      gStyle->SetStripDecimals(kTRUE);
      gStyle->SetTickLength(0.01, "XYZ");
      gStyle->SetNdivisions(510, "XYZ");
      gStyle->SetOptTitle(0);
//top pad 
    top_pad=new TPad("top_pad", "top_pad",0,0.2, 1.0, 1.0);
    top_pad->SetLogy(1);	
    top_pad->Draw();
    top_pad->cd();
    top_pad->SetBottomMargin(0.2);

    legend=new TLegend(0.45,0.79,0.67,0.99);

    vector<TH1D*> h_clone;

    for(int i=0; i<h.size(); i++){
      h[i]->SetLineColor(color[i]);
      h[i]->SetMarkerColor(color[i]);

      legend->AddEntry(h[i],TString::Itoa(i+1,10)+"-"+leg[i]);
      if(i==0){
	h[i]->GetYaxis()->SetRangeUser(miny, maxy);
	h[i]->GetYaxis()->SetTitle(ytitle);
        h[i]->GetXaxis()->SetLabelSize(0);
        h[i]->Draw("E");
      }
      else{
        h_clone.push_back((TH1D*)h[i]->Clone("new_"+TString::Itoa(i,10)));
        h_clone.back()->Add(h[0], -1);
        h_clone.back()->SetLineColor(color[i]);
        h_clone.back()->SetMarkerColor(color[i]);
        h_clone.back()->SetTitle("");
        h_clone.back()->GetXaxis()->SetTitle(xtitle);
        h_clone.back()->GetYaxis()->SetTitle("[*]-[1]");
        h[i]->Draw("E same");
      }
    }

    legend->Draw();

    bottom_pad=new TPad("bottom_pad", "bottom_pad", 0, 0., 1.0, 0.18);
    //bottom_pad->SetGrid(1);
    bottom_pad->Draw(); 
    bottom_pad->cd();
    bottom_pad->SetTopMargin(0);   

    h_clone[0]->GetYaxis()->SetRangeUser(minratio,maxratio);    
    h_clone[0]->GetYaxis()->SetNdivisions(5);
    h_clone[0]->GetXaxis()->SetTitleOffset(0.9);
    h_clone[0]->GetYaxis()->SetTitleOffset(0.22);
    h_clone[0]->GetXaxis()->SetTitleSize(1.0);
    h_clone[0]->GetYaxis()->SetTitleSize(1.0);
    h_clone[0]->GetXaxis()->SetLabelSize(0.2);
//    h_clone[0]->GetXaxis()->LabelsOption("v");
    h_clone[0]->GetYaxis()->SetLabelSize(0.1);
    h_clone[0]->GetXaxis()->CenterTitle();
    h_clone[0]->GetYaxis()->CenterTitle();


    for(int i=0; i<h_clone.size(); i++){
      if(i==0) h_clone[i]->Draw("E");
      else h_clone[i]->Draw("E same");
    }
    
    canvas->RedrawAxis();
    canvas->Update();

}

void MyRatioPlot::DrawRatioPlot(vector<TH1D*> h, vector<TString> leg, TString xtitle, TString ytitle, double miny, double maxy,double minratio, double maxratio,bool line=0){ 
    canvas=new TCanvas("ratio_plot","",700,600);
      gStyle->SetPadBorderMode(0);
      gStyle->SetOptStat(0);
      //gStyle->SetPadGridX(1);
      //gStyle->SetPadGridY(1);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetPadTopMargin(0.07);
      gStyle->SetPadBottomMargin(0.3);
      gStyle->SetPadRightMargin(0.05);
      gStyle->SetPadLeftMargin(0.14);
      gStyle->SetPadTickX(1);
      gStyle->SetPadTickY(1);
      gStyle->SetAxisColor(1, "XYZ");
      gStyle->SetStripDecimals(kTRUE);
      gStyle->SetTickLength(0.01, "XYZ");
      gStyle->SetNdivisions(510, "XYZ");
      gStyle->SetOptTitle(0);
//top pad 
    top_pad=new TPad("top_pad", "top_pad",0,0.2, 1.0, 1.0);
    top_pad->SetLogy(1);
    top_pad->Draw();
    top_pad->cd();
    top_pad->SetBottomMargin(0.2);

    legend=new TLegend(0.45,0.79,0.67,0.99);

    vector<TH1D*> h_clone;

    for(int i=0; i<h.size(); i++){
      h[i]->SetLineColor(color[i]);
      h[i]->SetMarkerColor(color[i]);

      legend->AddEntry(h[i],TString::Itoa(i+1,10)+"-"+leg[i]);
      if(i==0){
	h[i]->GetYaxis()->SetRangeUser(miny, maxy);
        h[i]->GetYaxis()->SetTitle(ytitle);
        h[i]->GetXaxis()->SetLabelSize(0);
        h[i]->Draw("E");
      }
      else{
        h_clone.push_back((TH1D*)h[i]->Clone("new_"+TString::Itoa(i,10)));
        h_clone.back()->Divide(h[0]);
        h_clone.back()->SetLineColor(color[i]);
        h_clone.back()->SetMarkerColor(color[i]);
        h_clone.back()->SetTitle("");
        h_clone.back()->GetXaxis()->SetTitle(xtitle);
        h_clone.back()->GetYaxis()->SetTitle("[*]/[1]");
        h[i]->Draw("E same");
      }
    }

    legend->Draw();

    bottom_pad=new TPad("bottom_pad", "bottom_pad", 0, 0., 1.0, 0.18);
    //bottom_pad->SetGrid(1);	
    bottom_pad->Draw();
    bottom_pad->cd();
    bottom_pad->SetTopMargin(0);   

    h_clone[0]->GetYaxis()->SetRangeUser(minratio,maxratio);    
    h_clone[0]->GetYaxis()->SetNdivisions(5);
    h_clone[0]->GetXaxis()->SetTitleOffset(0.9);
    h_clone[0]->GetYaxis()->SetTitleOffset(0.22);
    h_clone[0]->GetXaxis()->SetTitleSize(1.);
    h_clone[0]->GetYaxis()->SetTitleSize(1.);
    h_clone[0]->GetXaxis()->SetLabelSize(0.2);
//    h_clone[0]->GetXaxis()->LabelsOption("v");
    h_clone[0]->GetYaxis()->SetLabelSize(0.1);
    h_clone[0]->GetXaxis()->CenterTitle();
    h_clone[0]->GetYaxis()->CenterTitle();


    for(int i=0; i<h_clone.size(); i++){
      if(i==0) h_clone[i]->Draw("E");
      else h_clone[i]->Draw("E same");
    }

// temporary adding structures
    if(line){
	    TLine *l1 = new TLine(h_clone[0]->GetBinLowEdge(1),58.7/35.86,h_clone[0]->GetBinLowEdge(h_clone[0]->GetNbinsX()+1),58.7/35.86);
	    TLine *l2 = new TLine(h_clone[0]->GetBinLowEdge(1),41.52/35.86,h_clone[0]->GetBinLowEdge(h_clone[0]->GetNbinsX()+1),41.52/35.86);

	    l1->SetLineColor(color[2]);
	    l2->SetLineColor(color[1]);
	    l1->SetLineStyle(2);
	    l2->SetLineStyle(2);

	    l1->Draw(); l2->Draw();		
    }

    canvas->RedrawAxis();
    canvas->Update();

}




