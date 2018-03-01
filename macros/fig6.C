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
TFile * finSyst;

TH1D * h1;
TGraphErrors * N1HFfSUB3;
TGraphErrors * N1HFfSUB3_syst;
TH1D * ALICE_v1odd_eta_c10_60;
TGraphErrors * STAR_v1_3PC_62GeV_eta;
TGraphErrors * STAR_v1_mix_62GeV_eta;
TGraphErrors * STAR_v1_ZDC_62GeV_eta;


void fig6() {

    // retrieve CMS results
    finCMS = new TFile("../data/data_fig6.root","read");
    N1HFfSUB3 = (TGraphErrors *) finCMS->Get("N1HFfSUB3/-2.0_2.0/10_60/gint");
    N1HFfSUB3->SetMarkerStyle(21);
    N1HFfSUB3->SetMarkerSize(1.2);
    N1HFfSUB3->SetMarkerColor(kBlue);
    N1HFfSUB3->SetLineColor(kBlue);

    // retrieve ALICE results
    finALICE = new TFile("../data/PRL_111_232302.root","read");
    ALICE_v1odd_eta_c10_60 = (TH1D *) finALICE->Get("ALICE_v1odd_eta_c10_60");
    ALICE_v1odd_eta_c10_60->SetMarkerColor(kMagenta);
    ALICE_v1odd_eta_c10_60->SetLineColor(kMagenta);
    ALICE_v1odd_eta_c10_60->SetMarkerStyle(25);
    ALICE_v1odd_eta_c10_60->SetMarkerSize(1.2);

    // retrieve STAR results
    finSTAR = new TFile("../data/PRC_73_034903.root","read");
    STAR_v1_3PC_62GeV_eta = (TGraphErrors *) finSTAR->Get("STAR_v1odd_3PC_62GeV_eta_c_10_70");
    STAR_v1_3PC_62GeV_eta->SetMarkerColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetLineColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetMarkerStyle(20);
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.3);

    STAR_v1_mix_62GeV_eta = (TGraphErrors *) finSTAR->Get("STAR_v1odd_mix_62GeV_eta_c_10_70");
    STAR_v1_mix_62GeV_eta->SetMarkerColor(kTeal-7);
    STAR_v1_mix_62GeV_eta->SetLineColor(kTeal-7);
    STAR_v1_mix_62GeV_eta->SetMarkerStyle(33);
    STAR_v1_mix_62GeV_eta->SetMarkerSize(1.9);

    STAR_v1_ZDC_62GeV_eta = (TGraphErrors *) finSTAR->Get("STAR_v1odd_ZDC_62GeV_eta_c_10_70");
    STAR_v1_ZDC_62GeV_eta->SetMarkerColor(kBlack);
    STAR_v1_ZDC_62GeV_eta->SetLineColor(kBlack);
    STAR_v1_ZDC_62GeV_eta->SetMarkerStyle(28);
    STAR_v1_ZDC_62GeV_eta->SetMarkerSize(1.8);


    //-- systematics
    finSyst = new TFile("../data/data_systematics.root","read");

    Double_t x[50], y[50], xerr[50], ysyst[50];
    int num = N1HFfSUB3->GetN();
    for (int j = 0; j<num; j++) {
        N1HFfSUB3->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_20_60"); // no significant difference between 10-60% and 20-60%
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1HFfSUB3_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1HFfSUB3_syst->SetLineColor(kBlue-10);
    N1HFfSUB3_syst->SetFillColor(kBlue-10);
    //--


    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad1 = (TPad *) c->cd();
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, -2.15, 2.15);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetRangeUser(-0.015, 0.020);
    h1->Draw();
    N1HFfSUB3_syst->Draw("2");
    ALICE_v1odd_eta_c10_60->Draw("same");
    STAR_v1_3PC_62GeV_eta->Draw("same p");
    STAR_v1_mix_62GeV_eta->Draw("same p");
    STAR_v1_ZDC_62GeV_eta->Draw("same p");
    N1HFfSUB3->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TLegend * leg1 = new TLegend(0.38, 0.70, 0.59, 0.88);
    SetLegend(leg1, 19);
    leg1->SetHeader("Participant v_{1}^{odd}");
    leg1->AddEntry(N1HFfSUB3,"CMS (10-60%)","p");
    leg1->AddEntry(STAR_v1_3PC_62GeV_eta,"STAR 3PC, AuAu 62.4 GeV, (10-70%)","p");
    leg1->AddEntry(STAR_v1_mix_62GeV_eta,"STAR Mix, AuAu 62.4 GeV, (10-70%)","p");
    leg1->Draw();

    TLegend * leg2 = new TLegend(0.20, 0.18, 0.40, 0.32);
    SetLegend(leg2, 19);
    leg2->SetHeader("Spectator v_{1}^{odd}");
    leg2->AddEntry(ALICE_v1odd_eta_c10_60,"ALICE ZDC, PbPb 2.76 TeV (10-60%)","p");
    leg2->AddEntry(STAR_v1_ZDC_62GeV_eta,"STAR ZDC, AuAu 62.4 GeV (10-70%)","p");
    leg2->Draw();

    c->Print("../figures/fig6.pdf","pdf");
    // c->Print("../figures/fig6.png","png");

}
