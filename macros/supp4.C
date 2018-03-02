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

static const int ncbins = 11;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};

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

TFile * finCMS;
TFile * finAMPT;

TH1D * h1;
TGraphErrors * N1SUB3;
TGraphErrors * N1SUB3_ampt;

void supp4() {

    // retrieve CMS results
    finCMS = new TFile("../data/data_fig2.root","read");
    N1SUB3 = (TGraphErrors *) finCMS->Get("N1HFfSUB3/-2.0_2.0/20_60/gint");
    N1SUB3->SetMarkerStyle(21);
    N1SUB3->SetMarkerSize(1.2);
    N1SUB3->SetMarkerColor(kBlue);
    N1SUB3->SetLineColor(kBlue);

    // retrieve AMPT results
    finAMPT = new TFile("../data/data_ampt.root","read");
    N1SUB3_ampt = (TGraphErrors *) finAMPT->Get("N1HFfSUB3/-2.0_2.0/20_60/gint");
    N1SUB3_ampt->SetMarkerStyle(20);
    N1SUB3_ampt->SetMarkerSize(0.01);
    N1SUB3_ampt->SetMarkerColor(kGreen-6);
    N1SUB3_ampt->SetLineColor(kGreen-6);
    N1SUB3_ampt->SetFillColor(kGreen-6);
    N1SUB3_ampt->SetFillStyle(1001);

    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad1 = (TPad *) c->cd();
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, -2.0, 2.0);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetRangeUser(-0.012, 0.012);
    h1->Draw();
    N1SUB3_ampt->Draw("same E3");
    N1SUB3->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.74, 0.81, 0.89, 0.88, "NDC");
    SetTPaveTxt(tx1, 26);
    tx1->AddText("20 - 60%");
    tx1->Draw();

    TLegend * leg1 = new TLegend(0.23, 0.21, 0.46, 0.32);
    SetLegend(leg1, 22);
    leg1->AddEntry(N1SUB3,"CMS","p");
    leg1->AddEntry(N1SUB3_ampt,"AMPT (string melting)");
    leg1->Draw();

    c->Print("../figures/supp4.pdf","pdf");
    // c->Print("../figures/supp4.png","png");

}
