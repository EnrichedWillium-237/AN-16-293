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


    // average sides of the HF
    Double_t xA[50], yA[50], xAerr[0], yAerr[50];
    Double_t xB[50], yB[50], xBerr[0], yBerr[50];
    Double_t xav[50], yav[50], yerrav[50];
    int numave = N1AHFfSUB3_10_15->GetN();
    for (int j = 0; j<numave; j++) {
        N1AHFfSUB3_10_15->GetPoint(j, xA[j], yA[j]);
        yA[j]*=-1.;
        xAerr[j] = 0.1;
        yAerr[j] = N1AHFfSUB3_10_15->GetErrorY(j);

        N1BHFfSUB3_10_15->GetPoint(j, xB[j], yB[j]);
        //yB[j]*=-1.;
        xBerr[j] = 0.1;
        yBerr[j] = N1AHFfSUB3_10_15->GetErrorY(j);

        xav[j] = xA[j];
        yav[j] = 0.5*(yA[j] + yB[j]);
        yerrav[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
    }
    TGraphErrors * N1AHFfSUB3_10_15_ave = new TGraphErrors(numave, xav, yav, xAerr, yerrav);
    N1AHFfSUB3_10_15_ave->SetMarkerStyle(21);
    N1AHFfSUB3_10_15_ave->SetMarkerSize(1.1);
    N1AHFfSUB3_10_15_ave->SetMarkerColor(kBlue);
    N1AHFfSUB3_10_15_ave->SetLineColor(kBlue);

    for (int j = 0; j<numave; j++) {
        N1AHFfSUB3_40_50->GetPoint(j, xA[j], yA[j]);
        yA[j]*=-1.;
        xAerr[j] = 0.1;
        yAerr[j] = N1AHFfSUB3_40_50->GetErrorY(j);

        N1BHFfSUB3_40_50->GetPoint(j, xB[j], yB[j]);
        //yB[j]*=-1.;
        xBerr[j] = 0.1;
        yBerr[j] = N1AHFfSUB3_40_50->GetErrorY(j);

        xav[j] = xA[j];
        yav[j] = 0.5*(yA[j] + yB[j]);
        yerrav[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
    }
    TGraphErrors * N1AHFfSUB3_40_50_ave = new TGraphErrors(numave, xav, yav, xAerr, yerrav);
    N1AHFfSUB3_40_50_ave->SetMarkerStyle(20);
    N1AHFfSUB3_40_50_ave->SetMarkerSize(1.2);
    N1AHFfSUB3_40_50_ave->SetMarkerColor(kRed);
    N1AHFfSUB3_40_50_ave->SetLineColor(kRed);


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
    N1AHFfSUB3_10_15_syst->SetLineColor(kBlue-10);
    N1AHFfSUB3_10_15_syst->SetFillColor(kBlue-10);

    num = N1BHFfSUB3_10_15->GetN();
    for (int j = 0; j<num; j++) {
        N1BHFfSUB3_10_15->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1BHFfSUB3_10_15_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1BHFfSUB3_10_15_syst->SetLineColor(kBlue-10);
    N1BHFfSUB3_10_15_syst->SetFillColor(kBlue-10);

    num = N1AHFfSUB3_40_50->GetN();
    for (int j = 0; j<num; j++) {
        N1AHFfSUB3_40_50->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1AHFfSUB3_40_50_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1AHFfSUB3_40_50_syst->SetLineColor(kBlue-10);
    N1AHFfSUB3_40_50_syst->SetFillColor(kBlue-10);

    num = N1BHFfSUB3_40_50->GetN();
    for (int j = 0; j<num; j++) {
        N1BHFfSUB3_40_50->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1BHFfSUB3_40_50_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1BHFfSUB3_40_50_syst->SetLineColor(kBlue-10);
    N1BHFfSUB3_40_50_syst->SetFillColor(kBlue-10);


    for (int j = 0; j<num; j++) {
        N1AHFfSUB3_10_15_ave->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1AHFfSUB3_10_15_ave_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1AHFfSUB3_10_15_ave_syst->SetLineColor(kBlue-10);
    N1AHFfSUB3_10_15_ave_syst->SetFillColor(kBlue-10);

    for (int j = 0; j<num; j++) {
        N1AHFfSUB3_40_50_ave->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_40_50");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1AHFfSUB3_40_50_ave_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1AHFfSUB3_40_50_ave_syst->SetLineColor(kBlue-10);
    N1AHFfSUB3_40_50_ave_syst->SetFillColor(kBlue-10);
    //--



    TCanvas * c = new TCanvas("c", "c", 650, 600);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.07);
    h1 = new TH1D("h1", "", 100, 0, 8.5);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetRangeUser(-0.04, 0.03);
    h1->Draw();
    // N1AHFfSUB3_10_15_syst->Draw("same 2");
    // N1BHFfSUB3_10_15_syst->Draw("same 2");
    N1AHFfSUB3_10_15_ave_syst->Draw("same 2");
    // N1AHFfSUB3_40_50_syst->Draw("same 2");
    // N1BHFfSUB3_40_50_syst->Draw("same 2");
    N1AHFfSUB3_40_50_ave_syst->Draw("same 2");
    // N1AHFfSUB3_10_15->Draw("same p");
    // N1BHFfSUB3_10_15->Draw("same p");
    N1AHFfSUB3_10_15_ave->Draw("same p");
    // N1AHFfSUB3_40_50->Draw("same p");
    // N1BHFfSUB3_40_50->Draw("same p");
    N1AHFfSUB3_40_50_ave->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.164, 0.933, 0.377, 0.973, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary}");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.20, 0.78, 0.47, 0.89, "NDC");
    SetTPaveTxt(tx1, 20);
    tx1->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    tx1->AddText("|#eta| < 2");
    tx1->Draw();

    TLegend * leg1 = new TLegend(0.71, 0.79, 0.87, 0.90);
    SetLegend(leg1, 20);
    // leg->SetNColumns(2);
    leg1->AddEntry(N1BHFfSUB3_10_15,"10-15%","p");
    leg1->AddEntry(N1BHFfSUB3_40_50,"40-50%","p");
    leg1->Draw();

    c->Print("../figures/fig1.pdf","pdf");

}
