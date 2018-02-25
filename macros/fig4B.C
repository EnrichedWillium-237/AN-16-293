# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include <iostream>

using namespace std;

void SetTPaveTxt( TPaveText * txtemplate, int txtsize ) {
  txtemplate->SetFillColor(0);
  txtemplate->SetBorderSize(0);
  txtemplate->SetTextFont(43);
  txtemplate->SetTextAlign(12);
  txtemplate->SetTextSize(txtsize);
}

void SetLegend( TLegend * legtemplate, int legsize ) {
  legtemplate->SetFillColor(0);
  legtemplate->SetBorderSize(0);
  legtemplate->SetTextFont(43);
  legtemplate->SetTextSize(legsize);
}

TFile * fin;
TFile * finA;
TFile * finSyst;
TH1D * h1;
TH1D * h2;
TGraphErrors * N1EVENSUB3_10_15;
TGraphErrors * N1BHFfSUB3_10_15;
TGraphErrors * N1EVENSUB3_40_50;
TGraphErrors * N1BHFfSUB3_40_50;
TGraphErrors * N1EVENSUB3A_10_15;
TGraphErrors * N1BHFfSUB3A_10_15;
TGraphErrors * N1EVENSUB3A_40_50;
TGraphErrors * N1BHFfSUB3A_40_50;

TGraphErrors * N1EVENSUB3_10_15_syst;
TGraphErrors * N1BHFfSUB3_10_15_syst;
TGraphErrors * N1EVENSUB3_40_50_syst;
TGraphErrors * N1BHFfSUB3_40_50_syst;
TGraphErrors * N1EVENSUB3A_10_15_syst;
TGraphErrors * N1BHFfSUB3A_10_15_syst;
TGraphErrors * N1EVENSUB3A_40_50_syst;
TGraphErrors * N1BHFfSUB3A_40_50_syst;

void fig4B() {

    fin = new TFile("../data/data_fig4.root","read");

    N1EVENSUB3_10_15 = (TGraphErrors *) fin->Get("N1EVENSUB3/-1.6_-1.2/10_15/g");
    N1EVENSUB3_40_50 = (TGraphErrors *) fin->Get("N1EVENSUB3/-1.6_-1.2/40_50/g");

    finA = new TFile("../data/data_fig4A.root","read");

    N1EVENSUB3A_10_15 = (TGraphErrors *) finA->Get("N1EVENSUB3/-1.6_-1.2/10_15/g");
    N1EVENSUB3A_40_50 = (TGraphErrors *) finA->Get("N1EVENSUB3/-1.6_-1.2/40_50/g");


    // average sides of the tracker
    N1EVENSUB3_10_15->SetMarkerStyle(21);
    N1EVENSUB3_10_15->SetMarkerSize(1.2);
    N1EVENSUB3_10_15->SetMarkerColor(kBlue);
    N1EVENSUB3_10_15->SetLineColor(kBlue);

    N1EVENSUB3_40_50->SetMarkerStyle(20);
    N1EVENSUB3_40_50->SetMarkerSize(1.3);
    N1EVENSUB3_40_50->SetMarkerColor(kRed);
    N1EVENSUB3_40_50->SetLineColor(kRed);


    //-- with decorrelation correction
    N1EVENSUB3A_10_15->SetMarkerStyle(21);
    N1EVENSUB3A_10_15->SetMarkerSize(1.2);
    N1EVENSUB3A_10_15->SetMarkerColor(kBlue);
    N1EVENSUB3A_10_15->SetLineColor(kBlue);

    N1EVENSUB3A_40_50->SetMarkerStyle(20);
    N1EVENSUB3A_40_50->SetMarkerSize(1.3);
    N1EVENSUB3A_40_50->SetMarkerColor(kRed);
    N1EVENSUB3A_40_50->SetLineColor(kRed);



    //-- systematics
    finSyst = new TFile("../data/data_systematics.root","read");

    Double_t x[50], y[50], xerr[50], ysyst[50];
    int num = N1EVENSUB3_10_15->GetN();
    for (int j = 0; j<num; j++) {
        N1EVENSUB3_10_15->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("even_errors/even_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1EVENSUB3_10_15_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1EVENSUB3_10_15_syst->SetLineColor(kBlue-10);
    N1EVENSUB3_10_15_syst->SetFillColor(kBlue-10);

    for (int j = 0; j<num; j++) {
        N1EVENSUB3_40_50->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("even_errors/even_40_50");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1EVENSUB3_40_50_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1EVENSUB3_40_50_syst->SetLineColor(kBlue-10);
    N1EVENSUB3_40_50_syst->SetFillColor(kBlue-10);

    //-- with decorrelation correction

    for (int j = 0; j<num; j++) {
        N1EVENSUB3A_10_15->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("even_errors/even_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1EVENSUB3A_10_15_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1EVENSUB3A_10_15_syst->SetLineColor(kBlue-10);
    N1EVENSUB3A_10_15_syst->SetFillColor(kBlue-10);

    for (int j = 0; j<num; j++) {
        N1EVENSUB3A_40_50->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("even_errors/even_40_50");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1EVENSUB3A_40_50_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1EVENSUB3A_40_50_syst->SetLineColor(kBlue-10);
    N1EVENSUB3A_40_50_syst->SetFillColor(kBlue-10);
    //--



    TCanvas * c = new TCanvas("c", "c", 1000, 600);
    c->Divide(2,1,0,0);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.07);
    h1 = new TH1D("h1", "", 100, 0.001, 7.3);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.80);
    h1->GetYaxis()->SetRangeUser(-0.042, 0.18);
    h1->Draw();
    N1EVENSUB3_10_15_syst->Draw("same 2");
    N1EVENSUB3_40_50_syst->Draw("same 2");
    N1EVENSUB3_10_15->Draw("same p");
    N1EVENSUB3_40_50->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.188, 0.938, 0.431, 0.984, "NDC");
    SetTPaveTxt(tx0, 22);
    tx0->AddText("#bf{CMS} #it{Preliminary}");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.52, 0.80, 0.67, 0.89, "NDC");
    SetTPaveTxt(tx1, 28);
    tx1->AddText("#eta_{C} = 0");
    tx1->Draw();

    TPad * pad2 = (TPad *) c->cd(2);
    pad2->SetTopMargin(0.07);
    pad2->SetRightMargin(0.01);
    h2 = (TH1D *) h1->Clone("h2");
    h2->GetYaxis()->SetTitleSize(0.0);
    h2->GetYaxis()->SetLabelSize(0.0);
    h2->GetXaxis()->SetTitleSize(0.07);
    h2->GetXaxis()->SetTitleOffset(0.90);
    h2->GetXaxis()->SetLabelSize(0.06);
    h2->GetXaxis()->SetLabelOffset(0.00);
    h2->Draw();
    N1EVENSUB3A_10_15_syst->Draw("same 2");
    N1EVENSUB3A_40_50_syst->Draw("same 2");
    N1EVENSUB3A_10_15->Draw("same p");
    N1EVENSUB3A_40_50->Draw("same p");

    TPaveText * tx2 = new TPaveText(0.001, 0.938, 0.219, 0.984, "NDC");
    SetTPaveTxt(tx2, 22);
    tx2->AddText("PbPb 5.02 TeV,  1.2 < |#eta| < 1.6");
    tx2->Draw();

    TPaveText * tx3 = new TPaveText(0.42, 0.80, 0.57, 0.89, "NDC");
    SetTPaveTxt(tx3, 28);
    tx3->AddText("#eta_{C} = #eta_{ROI}");
    tx3->Draw();

    TLegend * leg1 = new TLegend(0.07, 0.75, 0.34, 0.88);
    SetLegend(leg1, 26);
    leg1->AddEntry(N1EVENSUB3_10_15,"10-15%","p");
    leg1->AddEntry(N1EVENSUB3_40_50,"40-50%","p");
    leg1->Draw();

    c->Print("../figures/fig4B.pdf","pdf");
    c->Print("../figures/fig4B.png","png");

}
