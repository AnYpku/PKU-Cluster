void draw_TGraph(TString op){
	ifstream file("./"+op+"_CLs.txt");
	cout<<"./"+op+"_CLs.txt"<<endl;
        TGraphErrors*gr=new TGraphErrors("./"+op+"_CLs.txt","%lg %lg %lg %lg"); 
        TCanvas*c1=new TCanvas(op,op,900,600);
        gr->Draw("AP");
        gr->GetXaxis()->SetTitle("POI(aC parameter)");
        gr->GetYaxis()->SetTitle("CLs(p_{#mu})");
        cout<<gr->GetN()<<endl; 
        const int num=gr->GetN();
        double xmin,xmax,ymin,ymax;
        gr->SetTitle("HybridNew --target CLs = 95%, opertator "+op);
        gr->GetPoint(0,xmin,ymin);
        gr->GetPoint(num-1,xmax,ymax);
        cout<<xmin<<" "<<xmax<<endl;
        TLine*line=new TLine(xmin,0.05,xmax,0.05);
        line->SetLineColor(kRed);
        line->SetLineStyle(2);
        line->Draw();
        c1->Print("CLs_"+op+".pdf"); 
}
int draw_CLs(){
draw_TGraph("fM0");
draw_TGraph("fM1");
draw_TGraph("fM2");
draw_TGraph("fM3");
draw_TGraph("fM4");
draw_TGraph("fM5");
draw_TGraph("fM6");
draw_TGraph("fM7");
draw_TGraph("fT0");
draw_TGraph("fT1");
draw_TGraph("fT2");
draw_TGraph("fT5");
draw_TGraph("fT6");
draw_TGraph("fT7");
return 0;
}
