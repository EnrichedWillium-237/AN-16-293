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
static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
    3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4};

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
TFile * finDecor;
TFile * finSyst;
TFile * finALICE;
TFile * finAMPT;
TH1D * h1;
TH1D * h2;
TGraphErrors * N1HFfSUB3;
TGraphErrors * N1HFfSUB3_syst;
TGraphErrors * N1HFfSUB3_decor;
TGraphErrors * N1HFfSUB3_decor_syst;
TH1D * ALICE_v1odd_eta_c10_60;

TH2D * v1true2D;
TH2D * v2true2D;
TH2D * v1raw2D;
TH2D * v2raw2D;
TH2D * qcnt;
TH1D * v1_pT[netabins];
TH1D * v2_pT[netabins];
TH1D * v1true_eta;
TH1D * v2true_eta;

TH1D * v1_pT_eta_0_8_neg;
TH1D * v1_pT_eta_0_8_pos;
TH1D * v1_pT_eta_0_24_neg;
TH1D * v1_pT_eta_0_24_pos;
TH1D * v1_pT_eta_0_8_av;
TH1D * v1_pT_eta_0_24_av;
TH1D * v2_pT_eta_0_8_av;
TH1D * v2_pT_eta_0_24_av;

void fig2_v2() {

    fin = new TFile("../data/data_fig2_v2.root");
    finDecor = new TFile("../data/data_fig2_v2_decor.root");

    int col[] = {kRed, kOrange+5, kBlue, kGreen+2, kCyan+2, kMagenta, kBlack, kRed, kBlue, kGreen+2, kCyan+2};
    int mrkstyle[] =   {20,  25,  21,  28,  33,  27,  24,  34, 27,  20,  31};
    double mrksize[] = {1.3, 1.2, 1.2, 1.6, 1.8, 1.8, 1.2, 1.6, 1.8, 1.2, 1.4};

    // get AMPT results
    finAMPT = new TFile("../data/amptVN_10_70.root","read");
    v1true2D = (TH2D *) finAMPT->Get("10_70/v1true_10_70");
    v2true2D = (TH2D *) finAMPT->Get("10_70/v2true_10_70");
    v1raw2D = (TH2D *) finAMPT->Get("10_70/v1raw_10_70");
    v2raw2D = (TH2D *) finAMPT->Get("10_70/v2raw_10_70");
    qcnt = (TH2D *) finAMPT->Get("10_70/qcnt_10_70");

    // v1true2D = (TH2D *) finAMPT->Get("5_10/v1true_5_10");
    // v2true2D = (TH2D *) finAMPT->Get("5_10/v2true_5_10");
    // v1raw2D = (TH2D *) finAMPT->Get("5_10/v1raw_5_10");
    // v2raw2D = (TH2D *) finAMPT->Get("5_10/v2raw_5_10");
    // qcnt = (TH2D *) finAMPT->Get("5_10/qcnt_5_10");

    v1true_eta = new TH1D("v1true_eta", "", netabins, etabins);
    v2true_eta = new TH1D("v2true_eta", "", netabins, etabins);

    v1_pT_eta_0_8_neg = v1true2D->ProjectionX("v1_pT_eta_0_8_neg", 5, 6);
    v1_pT_eta_0_8_pos = v1true2D->ProjectionX("v1_pT_eta_0_8_pos", 7, 8);
    v1_pT_eta_0_24_neg = v1true2D->ProjectionX("v1_pT_eta_0_24_neg", 1, 6);
    v1_pT_eta_0_24_pos = v1true2D->ProjectionX("v1_pT_eta_0_24_pos", 7, 12);
    v2_pT_eta_0_8_av = v2true2D->ProjectionX("v2_pT_eta_0_8_av", 5, 8);
    v2_pT_eta_0_24_av = v2true2D->ProjectionX("v2_pT_eta_0_24_av", 1, 12);

    v1_pT_eta_0_8_neg->Scale(1/2.);
    v1_pT_eta_0_8_pos->Scale(1/2.);
    v1_pT_eta_0_24_neg->Scale(1/6.);
    v1_pT_eta_0_24_pos->Scale(1/6.);
    v2_pT_eta_0_8_av->Scale(1/4.);
    v2_pT_eta_0_24_av->Scale(1/12.);

    v1_pT_eta_0_8_av = (TH1D *) v1_pT_eta_0_8_pos->Clone("v1_pT_eta_0_8_av");
    v1_pT_eta_0_8_av->Add(v1_pT_eta_0_8_neg,-1);
    v1_pT_eta_0_8_av->Scale(0.5);

    v1_pT_eta_0_24_av = (TH1D *) v1_pT_eta_0_24_pos->Clone("v1_pT_eta_0_24_av");
    v1_pT_eta_0_24_av->Add(v1_pT_eta_0_24_neg,-1);
    v1_pT_eta_0_24_av->Scale(0.5);

    for (int ebin = 0; ebin<netabins; ebin++) {
        v1_pT[ebin] = v1true2D->ProjectionX(Form("v1_pT_eta_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]), ebin+1, ebin+1);
        v2_pT[ebin] = v2true2D->ProjectionX(Form("v2_pT_eta_%1.1f_%1.1f",etabins[ebin],etabins[ebin+1]), ebin+1, ebin+1);

        // compute integral v1(eta)
        double v1int = 0;
        double v1inte = 0;
        double v2int = 0;
        double v2inte = 0;
        TH1D * yld = (TH1D *) qcnt->ProjectionX("yld", ebin+1, ebin+1);
        double y1[20];
        double y2[20];
        double ey1[20];
        double ey2[20];
        for (int i = 0; i<20; i++) {
            y1[20] = 0;
            y2[20] = 0;
            ey1[20] = 0;
            ey2[20] = 0;
        }
        int npt = 0;
        double wv1 = 0;
        double wv1e = 0;
        double wv2 = 0;
        double wv2e = 0;
        double w = 0;
        for (int i = 1; i<=10; i++) {
            y1[npt] = v1_pT[ebin]->GetBinContent(i);
            y2[npt] = v2_pT[ebin]->GetBinContent(i);
            ey1[npt] = v1_pT[ebin]->GetBinError(i);
            ey2[npt] = v2_pT[ebin]->GetBinError(i);
            wv1  += y1[npt]*yld->GetBinContent(i);
            wv1e += ey1[npt]*yld->GetBinContent(i);
            wv2  += y2[npt]*yld->GetBinContent(i);
            wv2e += ey2[npt]*yld->GetBinContent(i);
            w    += yld->GetBinContent(i);
            ++npt;
        }
        yld->Delete();
        v1int = wv1/w;
        v1inte = wv1e/w;
        v2int = wv2/w;
        v2inte = wv2e/w;

        v1true_eta->SetBinContent(ebin+1, v1int);
        v1true_eta->SetBinError(ebin+1, v1inte);
        v2true_eta->SetBinContent(ebin+1, v2int);
        v2true_eta->SetBinError(ebin+1, v2inte);
    }
    v1true_eta->SetMarkerStyle(28);
    v1true_eta->SetMarkerSize(1.5);
    v1true_eta->SetMarkerColor(kOrange+7);
    v1true_eta->SetLineColor(kOrange+7);

    // retrieve ALICE results
    finALICE = new TFile("../data/PRL_111_232302.root","read");
    ALICE_v1odd_eta_c10_60 = (TH1D *) finALICE->Get("ALICE_v1odd_eta_c10_60");
    ALICE_v1odd_eta_c10_60->SetMarkerColor(kMagenta);
    ALICE_v1odd_eta_c10_60->SetLineColor(kMagenta);
    ALICE_v1odd_eta_c10_60->SetMarkerStyle(33);
    ALICE_v1odd_eta_c10_60->SetMarkerSize(1.7);

    // retrieve CMS results
    N1HFfSUB3 = (TGraphErrors *) fin->Get("N1HFfSUB3/-2.0_2.0/5_10/gint");
    N1HFfSUB3->SetMarkerStyle(24);
    N1HFfSUB3->SetMarkerSize(1.3);
    N1HFfSUB3->SetMarkerColor(kRed);
    N1HFfSUB3->SetLineColor(kRed);

    N1HFfSUB3_decor = (TGraphErrors *) finDecor->Get("N1HFfSUB3/-2.0_2.0/5_10/gint");
    N1HFfSUB3_decor->SetMarkerStyle(21);
    N1HFfSUB3_decor->SetMarkerSize(1.2);
    N1HFfSUB3_decor->SetMarkerColor(kBlue);
    N1HFfSUB3_decor->SetLineColor(kBlue);


    //-- systematics
    finSyst = new TFile("../data/data_systematics.root","read");

    Double_t x[50], y[50], xerr[50], ysyst[50];
    int num = N1HFfSUB3->GetN();
    for (int j = 0; j<num; j++) {
        N1HFfSUB3->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_20_60");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1HFfSUB3_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1HFfSUB3_syst->SetLineColor(kBlue-10);
    N1HFfSUB3_syst->SetFillColor(kBlue-10);

    for (int j = 0; j<num; j++) {
        N1HFfSUB3_decor->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_20_60");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1HFfSUB3_decor_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1HFfSUB3_decor_syst->SetLineColor(kBlue-10);
    N1HFfSUB3_decor_syst->SetFillColor(kBlue-10);
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
    h1->GetYaxis()->SetRangeUser(-0.01, 0.01);
    h1->Draw();
    N1HFfSUB3_syst->Draw("same 2");
    N1HFfSUB3_decor_syst->Draw("same 2");
    v1true_eta->Draw("same");
    ALICE_v1odd_eta_c10_60->Draw("same");
    N1HFfSUB3->Draw("same p");
    N1HFfSUB3_decor->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.184, 0.947, 0.399, 0.986, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary}, PbPb 5.05 TeV, 0.3 < p_{T} < 3.0 GeV/c");
    tx0->Draw();

    TLegend * leg1 = new TLegend(0.20, 0.19, 0.47, 0.40);
    SetLegend(leg1, 20);
    //leg1->SetHeader("10 - 70%");
    leg1->AddEntry(N1HFfSUB3,"CMS {#eta_{C} = 0}","p");
    leg1->AddEntry(N1HFfSUB3_decor,"CMS {#eta_{C} = #eta_{ROI}}","p");
    leg1->AddEntry(v1true_eta,"AMPT <cos(#phi - #Psi_{RP})>","p");
    leg1->AddEntry(ALICE_v1odd_eta_c10_60,"ALICE PbPb 2.76 TeV","p");
    leg1->Draw();

    c->Print("../figures/fig2_v2.pdf","pdf");
    c->Print("../figures/fig2_v2.png","png");

}
