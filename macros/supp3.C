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

TH1D * h1;
TGraphErrors * N1AEVENSUB3;
TGraphErrors * N1BEVENSUB3;


void supp3() {

    // retrieve CMS results
    finCMS = new TFile("../data/data_fig5.root","read");
    N1AEVENSUB3 = (TGraphErrors *) finCMS->Get("N1EVENSUB3/-2.4_-0.4/20_60/gintA");
    N1AEVENSUB3->SetMarkerStyle(20);
    N1AEVENSUB3->SetMarkerSize(1.3);
    N1AEVENSUB3->SetMarkerColor(kBlue);
    N1AEVENSUB3->SetLineColor(kBlue);

    N1BEVENSUB3 = (TGraphErrors *) finCMS->Get("N1EVENSUB3/-2.4_-0.4/20_60/gintB");
    N1BEVENSUB3->SetMarkerStyle(20);
    N1BEVENSUB3->SetMarkerSize(1.3);
    N1BEVENSUB3->SetMarkerColor(kRed);
    N1BEVENSUB3->SetLineColor(kRed);

    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad1 = (TPad *) c->cd();
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, -2.5, 2.5);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{even}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetRangeUser(-0.040, 0.015);
    h1->Draw();
    N1AEVENSUB3->Draw("same p");
    N1BEVENSUB3->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.74, 0.81, 0.89, 0.88, "NDC");
    SetTPaveTxt(tx1, 26);
    tx1->AddText("20 - 60%");
    tx1->Draw();

    TLegend * leg1 = new TLegend(0.21, 0.77, 0.44, 0.88);
    SetLegend(leg1, 22);
    leg1->AddEntry(N1AEVENSUB3,"v_{1}{track+} {2.0 < #eta_{EP} < 2.4}","p");
    leg1->AddEntry(N1BEVENSUB3,"v_{1}{track-} {-2.4 < #eta_{EP} < -2.0}","p");
    leg1->Draw();

    c->Print("../figures/supp3.pdf","pdf");
    // c->Print("../figures/supp3.png","png");

}
