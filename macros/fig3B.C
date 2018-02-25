# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGaxis.h"
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
TH1D * h1;
TH1D * h2;
TGraphErrors * N1HFcSUB3;
TGraphErrors * N1HFdSUB3;
TGraphErrors * N1HFeSUB3;
TGraphErrors * N1HFfSUB3;

void fig3B() {

    fin = new TFile("../data/data_fig3B.root");

    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad1 = (TPad *) c->cd();
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, -2.15, 2.15);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    // TGaxis * gax1 = (TGaxis *) h1->GetYaxis();
    // gax1->SetMaxDigits(3);
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetRangeUser(-0.02, 0.02);
    h1->Draw();

    N1HFcSUB3 = (TGraphErrors *) fin->Get("N1HFcSUB3/-2.0_2.0/20_60/gint");
    N1HFcSUB3->SetMarkerStyle(24);
    N1HFcSUB3->SetMarkerSize(1.3);
    N1HFcSUB3->SetMarkerColor(kBlack);
    N1HFcSUB3->SetLineColor(kBlack);
    N1HFcSUB3->Draw("same p");

    N1HFdSUB3 = (TGraphErrors *) fin->Get("N1HFdSUB3/-2.0_2.0/20_60/gint");
    N1HFdSUB3->SetMarkerStyle(25);
    N1HFdSUB3->SetMarkerSize(1.2);
    N1HFdSUB3->SetMarkerColor(kRed);
    N1HFdSUB3->SetLineColor(kRed);
    N1HFdSUB3->Draw("same p");

    N1HFeSUB3 = (TGraphErrors *) fin->Get("N1HFeSUB3/-2.0_2.0/20_60/gint");
    N1HFeSUB3->SetMarkerStyle(24);
    N1HFeSUB3->SetMarkerSize(1.3);
    N1HFeSUB3->SetMarkerColor(kGreen+2);
    N1HFeSUB3->SetLineColor(kGreen+2);
    N1HFeSUB3->Draw("same p");

    N1HFfSUB3 = (TGraphErrors *) fin->Get("N1HFfSUB3/-2.0_2.0/20_60/gint");
    N1HFfSUB3->SetMarkerStyle(25);
    N1HFfSUB3->SetMarkerSize(1.2);
    N1HFfSUB3->SetMarkerColor(kBlue);
    N1HFfSUB3->SetLineColor(kBlue);
    N1HFfSUB3->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    // tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0->AddText("AMPT PbPb, 5.02 TeV, 0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.23, 0.76, 0.41, 0.88, "NDC");
    SetTPaveTxt(tx1, 28);
    tx1->AddText("#eta_{C} = 0");
    tx1->AddText("20 - 60%");
    tx1->Draw();

    TLegend * leg1 = new TLegend(0.19, 0.19, 0.50, 0.41);
    SetLegend(leg1, 26);
    leg1->AddEntry(N1HFcSUB3,"3.0 < |#eta_{EP}| < 3.5","p");
    leg1->AddEntry(N1HFdSUB3,"3.5 < |#eta_{EP}| < 4.0","p");
    leg1->AddEntry(N1HFeSUB3,"4.0 < |#eta_{EP}| < 4.5","p");
    leg1->AddEntry(N1HFfSUB3,"4.5 < |#eta_{EP}| < 5.0","p");
    // leg1->Draw();

    c->Print("../figures/fig3B.pdf","pdf");
    c->Print("../figures/fig3B.png","png");

}
