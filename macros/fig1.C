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
TFile * finSyst;
TH1D * h1;
TGraphErrors * N1AHFfSUB3_10_15;
TGraphErrors * N1BHFfSUB3_10_15;
TGraphErrors * N1AHFfSUB3_40_50;
TGraphErrors * N1BHFfSUB3_40_50;

TGraphErrors * N1AHFfSUB3_10_15_syst;
TGraphErrors * N1BHFfSUB3_10_15_syst;
TGraphErrors * N1AHFfSUB3_40_50_syst;
TGraphErrors * N1BHFfSUB3_40_50_syst;

void fig1() {

    fin = new TFile("../data/data_fig1.root","read");

    N1AHFfSUB3_10_15 = (TGraphErrors *) fin->Get("N1HFfSUB3/-2.0_0.0/10_15/g");
    N1AHFfSUB3_10_15->SetMarkerStyle(25);
    N1AHFfSUB3_10_15->SetMarkerSize(1.1);
    N1AHFfSUB3_10_15->SetMarkerColor(kBlue);
    N1AHFfSUB3_10_15->SetLineColor(kBlue);

    N1BHFfSUB3_10_15 = (TGraphErrors *) fin->Get("N1HFfSUB3/0.0_2.0/10_15/g");
    N1BHFfSUB3_10_15->SetMarkerStyle(21);
    N1BHFfSUB3_10_15->SetMarkerSize(1.1);
    N1BHFfSUB3_10_15->SetMarkerColor(kBlue);
    N1BHFfSUB3_10_15->SetLineColor(kBlue);

    N1AHFfSUB3_40_50 = (TGraphErrors *) fin->Get("N1HFfSUB3/-2.0_0.0/40_50/g");
    N1AHFfSUB3_40_50->SetMarkerStyle(24);
    N1AHFfSUB3_40_50->SetMarkerSize(1.2);
    N1AHFfSUB3_40_50->SetMarkerColor(kRed);
    N1AHFfSUB3_40_50->SetLineColor(kRed);

    N1BHFfSUB3_40_50 = (TGraphErrors *) fin->Get("N1HFfSUB3/0.0_2.0/40_50/g");
    N1BHFfSUB3_40_50->SetMarkerStyle(20);
    N1BHFfSUB3_40_50->SetMarkerSize(1.2);
    N1BHFfSUB3_40_50->SetMarkerColor(kRed);
    N1BHFfSUB3_40_50->SetLineColor(kRed);


    //-- systematics
    finSyst = new TFile("../data/data_systematics.root","read");

    Double_t x[50], y[50], xerr[50], ysyst[50];
    int num = N1AHFfSUB3_10_15->GetN();
    for (int j = 0; j<num; j++) {
        N1AHFfSUB3_10_15->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1AHFfSUB3_10_15_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1AHFfSUB3_10_15_syst->SetLineColor(kGray);
    N1AHFfSUB3_10_15_syst->SetFillColor(kGray);

    num = N1BHFfSUB3_10_15->GetN();
    for (int j = 0; j<num; j++) {
        N1BHFfSUB3_10_15->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1BHFfSUB3_10_15_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1BHFfSUB3_10_15_syst->SetLineColor(kGray);
    N1BHFfSUB3_10_15_syst->SetFillColor(kGray);

    num = N1AHFfSUB3_40_50->GetN();
    for (int j = 0; j<num; j++) {
        N1AHFfSUB3_40_50->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1AHFfSUB3_40_50_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1AHFfSUB3_40_50_syst->SetLineColor(kGray);
    N1AHFfSUB3_40_50_syst->SetFillColor(kGray);

    num = N1BHFfSUB3_40_50->GetN();
    for (int j = 0; j<num; j++) {
        N1BHFfSUB3_40_50->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1BHFfSUB3_40_50_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1BHFfSUB3_40_50_syst->SetLineColor(kGray);
    N1BHFfSUB3_40_50_syst->SetFillColor(kGray);
    //--


    TCanvas * c = new TCanvas("c", "c", 650, 600);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.07);
    h1 = new TH1D("h1", "", 100, 0, 8.5);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetRangeUser(-0.08, 0.08);
    h1->Draw();
    N1AHFfSUB3_10_15_syst->Draw("same 2");
    N1BHFfSUB3_10_15_syst->Draw("same 2");
    N1AHFfSUB3_40_50_syst->Draw("same 2");
    N1BHFfSUB3_40_50_syst->Draw("same 2");
    N1AHFfSUB3_10_15->Draw("same p");
    N1BHFfSUB3_10_15->Draw("same p");
    N1AHFfSUB3_40_50->Draw("same p");
    N1BHFfSUB3_40_50->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.164, 0.930, 0.377, 0.97, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary}");
    tx0->Draw();

    TLegend * leg1 = new TLegend(0.19, 0.18, 0.39, 0.34);
    SetLegend(leg1, 20);
    // leg->SetNColumns(2);
    leg1->AddEntry(N1AHFfSUB3_10_15,"-2 < #eta < 0 (10-15%)","p");
    leg1->AddEntry(N1BHFfSUB3_10_15,"0 < #eta < 2 (10-15%)","p");
    leg1->AddEntry(N1AHFfSUB3_40_50,"-2 < #eta < 0 (40-50%)","p");
    leg1->AddEntry(N1BHFfSUB3_40_50,"0 < #eta < 2 (40-50%)","p");
    leg1->Draw();

    c->Print("../figures/fig1.pdf","pdf");

}
