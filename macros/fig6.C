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
TFile * finALICE;
TFile * finSTAR;

TH1D * h1;
TGraphErrors * N1HFfSUB3;
TH1D * ALICE_v1odd_eta_c10_60;
TGraphErrors * STAR_v1_3PC_62GeV_eta;
TGraphErrors * STAR_v1_mix_62GeV_eta;
TGraphErrors * STAR_v1_ZDC_62GeV_eta;


void fig6() {

    // retrieve ALICE results
    finALICE = new TFile("../data/PRL_111_232302.root","read");
    ALICE_v1odd_eta_c10_60 = (TH1D *) finALICE->Get("ALICE_v1odd_eta_c10_60");
    ALICE_v1odd_eta_c10_60->SetMarkerColor(kMagenta);
    ALICE_v1odd_eta_c10_60->SetLineColor(kMagenta);
    ALICE_v1odd_eta_c10_60->SetMarkerStyle(21);
    ALICE_v1odd_eta_c10_60->SetMarkerSize(1.2);

    // retrieve STAR results
    finSTAR = new TFile("../data/PRC_73_034903.root","read");
    STAR_v1_3PC_62GeV_eta = (TGraphErrors *) finSTAR->Get("STAR_v1odd_3PC_62GeV_eta_c_10_70");
    STAR_v1_3PC_62GeV_eta->SetMarkerColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetLineColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetMarkerStyle(29);
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.5);

    STAR_v1_mix_62GeV_eta = (TGraphErrors *) finSTAR->Get("STAR_v1odd_mix_62GeV_eta_c_10_70");
    STAR_v1_mix_62GeV_eta->SetMarkerColor(kCyan+2);
    STAR_v1_mix_62GeV_eta->SetLineColor(kCyan+2);
    STAR_v1_mix_62GeV_eta->SetMarkerStyle(24);
    STAR_v1_mix_62GeV_eta->SetMarkerSize(1.2);

    STAR_v1_ZDC_62GeV_eta = (TGraphErrors *) finSTAR->Get("STAR_v1odd_ZDC_62GeV_eta_c_10_70");
    STAR_v1_ZDC_62GeV_eta->SetMarkerColor(kBlue);
    STAR_v1_ZDC_62GeV_eta->SetLineColor(kBlue);
    STAR_v1_ZDC_62GeV_eta->SetMarkerStyle(25);
    STAR_v1_ZDC_62GeV_eta->SetMarkerSize(1.1);


    finCMS = new TFile("../data/data_fig6.root","read");

    TCanvas * c = new TCanvas("c", "c", 650, 600);
    TPad * pad1 = (TPad *) c->cd();
    pad1->SetTopMargin(0.07);
    h1 = new TH1D("h1", "", 100, -2.15, 2.15);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->SetRangeUser(-0.025, 0.025);
    h1->Draw();
    ALICE_v1odd_eta_c10_60->Draw("same");
    STAR_v1_3PC_62GeV_eta->Draw("same p");
    STAR_v1_mix_62GeV_eta->Draw("same p");
    STAR_v1_ZDC_62GeV_eta->Draw("same p");
    N1HFfSUB3 = (TGraphErrors *) finCMS->Get("N1HFfSUB3/-2.0_2.0/10_60/gint");
    N1HFfSUB3->SetMarkerStyle(21);
    N1HFfSUB3->SetMarkerSize(1.2);
    N1HFfSUB3->SetMarkerColor(kBlue);
    N1HFfSUB3->SetLineColor(kBlue);
    N1HFfSUB3->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.164, 0.930, 0.377, 0.97, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary}");
    tx0->Draw();

    // TPaveText * tx1 = new TPaveText(0.22, 0.83, 0.54, 0.89, "NDC");
    // SetTPaveTxt(tx1, 20);
    // tx1->AddText("0.3 < p_{T} < 3.0 GeV/c");
    // tx1->Draw();

    TLegend * leg1 = new TLegend(0.20, 0.18, 0.45, 0.38);
    SetLegend(leg1, 18);
    leg1->AddEntry(N1HFfSUB3,"v_{1}^{part} CMS PbPb #sqrt{s_{NN}} = 5.02 TeV (10-60%)","p");
    leg1->AddEntry(ALICE_v1odd_eta_c10_60,"v_{1}^{spec} ALICE PbPb #sqrt{s_{NN}} = 2.76 TeV (10-60%)","p");
    leg1->AddEntry(STAR_v1_3PC_62GeV_eta,"v_{1}^{part} STAR 3PC AuAu #sqrt{s_{NN}} = 62.4 GeV (10-70%)","p");
    leg1->AddEntry(STAR_v1_mix_62GeV_eta,"v_{1}^{part} STAR Mix AuAu #sqrt{s_{NN}} = 62.4 GeV (10-70%)","p");
    leg1->AddEntry(STAR_v1_ZDC_62GeV_eta,"v_{1}^{spec} STAR ZDC AuAu #sqrt{s_{NN}} = 62.4 GeV (10-70%)","p");
    leg1->Draw();

    c->Print("../figures/fig6.pdf","pdf");

}
