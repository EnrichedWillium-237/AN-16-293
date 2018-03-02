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
TFile * finA;
TH1D * h;
TGraphErrors * N1HFfSUB3;
TGraphErrors * N1HFm1fSUB3;
TGraphErrors * N1HFp1fSUB3;
TGraphErrors * N1HFfSUB3A;
TGraphErrors * N1HFm1fSUB3A;
TGraphErrors * N1HFp1fSUB3A;

void supp3() {

    fin = new TFile("../data/data_supp2.root");

    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad = (TPad *) c->cd();
    pad->SetTopMargin(0.08);
    pad->SetLeftMargin(0.18);
    h = new TH1D("h", "", 100, -2.15, 2.15);
    h->SetStats(0);
    h->SetXTitle("#eta");
    h->SetYTitle("v_{1}");
    h->GetYaxis()->SetDecimals();
    h->GetYaxis()->SetNdivisions(509);
    h->GetXaxis()->CenterTitle();
    h->GetYaxis()->CenterTitle();
    h->GetXaxis()->SetTitleOffset(1.15);
    h->GetYaxis()->SetTitleOffset(1.65);
    h->GetYaxis()->SetRangeUser(-0.042, 0.042);
    h->Draw();

    N1HFfSUB3 = (TGraphErrors *) fin->Get("N1HFfSUB3/-2.0_2.0/20_60/gint");
    N1HFfSUB3->SetMarkerStyle(20);
    N1HFfSUB3->SetMarkerSize(1.3);
    N1HFfSUB3->SetMarkerColor(kBlack);
    N1HFfSUB3->SetLineColor(kBlack);
    N1HFfSUB3->Draw("same p");

    N1HFm1fSUB3 = (TGraphErrors *) fin->Get("N1HFm1fSUB3/-2.0_2.0/20_60/A_N1HFm1fSUB3");
    N1HFm1fSUB3->SetMarkerStyle(20);
    N1HFm1fSUB3->SetMarkerSize(1.3);
    N1HFm1fSUB3->SetMarkerColor(kRed);
    N1HFm1fSUB3->SetLineColor(kRed);
    N1HFm1fSUB3->Draw("same p");

    N1HFp1fSUB3 = (TGraphErrors *) fin->Get("N1HFp1fSUB3/-2.0_2.0/20_60/A_N1HFp1fSUB3");
    N1HFp1fSUB3->SetMarkerStyle(20);
    N1HFp1fSUB3->SetMarkerSize(1.3);
    N1HFp1fSUB3->SetMarkerColor(kBlue);
    N1HFp1fSUB3->SetLineColor(kBlue);
    N1HFp1fSUB3->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.72, 0.80, 0.87, 0.87, "NDC");
    SetTPaveTxt(tx1, 26);
    tx1->AddText("20 - 60%");
    tx1->Draw();

    TLegend * leg1 = new TLegend(0.19, 0.19, 0.50, 0.35);
    SetLegend(leg1, 22);
    leg1->AddEntry(N1HFfSUB3,"Average v_{1}","p");
    leg1->AddEntry(N1HFp1fSUB3,"v_{1}{HF+} {4.5 < #eta_{EP} < 5.0}","p");
    leg1->AddEntry(N1HFm1fSUB3,"v_{1}{HF-} {-5.0 < #eta_{EP} < -4.5}","p");
    leg1->Draw();

    c->Print("../figures/supp3.pdf","pdf");
    // c->Print("../figures/supp3.png","png");

}
