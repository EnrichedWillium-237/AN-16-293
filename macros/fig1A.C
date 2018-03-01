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
TGraphErrors * N1AHFfSUB3_10_15;
TGraphErrors * N1BHFfSUB3_10_15;
TGraphErrors * N1AHFfSUB3_40_50;
TGraphErrors * N1BHFfSUB3_40_50;
TGraphErrors * N1AHFfSUB3A_10_15;
TGraphErrors * N1BHFfSUB3A_10_15;
TGraphErrors * N1AHFfSUB3A_40_50;
TGraphErrors * N1BHFfSUB3A_40_50;

TGraphErrors * N1AHFfSUB3_10_15_syst;
TGraphErrors * N1BHFfSUB3_10_15_syst;
TGraphErrors * N1AHFfSUB3_40_50_syst;
TGraphErrors * N1BHFfSUB3_40_50_syst;
TGraphErrors * N1AHFfSUB3A_10_15_syst;
TGraphErrors * N1BHFfSUB3A_10_15_syst;
TGraphErrors * N1AHFfSUB3A_40_50_syst;
TGraphErrors * N1BHFfSUB3A_40_50_syst;

void fig1A() {

    fin = new TFile("../data/data_fig1.root","read");

    N1AHFfSUB3_10_15 = (TGraphErrors *) fin->Get("N1HFfSUB3/-1.6_-1.2/10_15/g");
    N1BHFfSUB3_10_15 = (TGraphErrors *) fin->Get("N1HFfSUB3/1.2_1.6/10_15/g");
    N1AHFfSUB3_40_50 = (TGraphErrors *) fin->Get("N1HFfSUB3/-1.6_-1.2/40_50/g");
    N1BHFfSUB3_40_50 = (TGraphErrors *) fin->Get("N1HFfSUB3/1.2_1.6/40_50/g");

    finA = new TFile("../data/data_fig1A.root","read");

    N1AHFfSUB3A_10_15 = (TGraphErrors *) finA->Get("N1HFfSUB3/-1.6_-1.2/10_15/g");
    N1BHFfSUB3A_10_15 = (TGraphErrors *) finA->Get("N1HFfSUB3/1.2_1.6/10_15/g");
    N1AHFfSUB3A_40_50 = (TGraphErrors *) finA->Get("N1HFfSUB3/-1.6_-1.2/40_50/g");
    N1BHFfSUB3A_40_50 = (TGraphErrors *) finA->Get("N1HFfSUB3/1.2_1.6/40_50/g");


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
    TGraphErrors * N1HFfSUB3_10_15_ave = new TGraphErrors(numave, xav, yav, xAerr, yerrav);
    N1HFfSUB3_10_15_ave->SetMarkerStyle(21);
    N1HFfSUB3_10_15_ave->SetMarkerSize(1.2);
    N1HFfSUB3_10_15_ave->SetMarkerColor(kBlue);
    N1HFfSUB3_10_15_ave->SetLineColor(kBlue);

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
    TGraphErrors * N1HFfSUB3_40_50_ave = new TGraphErrors(numave, xav, yav, xAerr, yerrav);
    N1HFfSUB3_40_50_ave->SetMarkerStyle(20);
    N1HFfSUB3_40_50_ave->SetMarkerSize(1.3);
    N1HFfSUB3_40_50_ave->SetMarkerColor(kRed);
    N1HFfSUB3_40_50_ave->SetLineColor(kRed);


    //-- with decorrelation correction
    for (int j = 0; j<numave; j++) {
        N1AHFfSUB3A_10_15->GetPoint(j, xA[j], yA[j]);
        yA[j]*=-1.;
        xAerr[j] = 0.1;
        yAerr[j] = N1AHFfSUB3A_10_15->GetErrorY(j);

        N1BHFfSUB3A_10_15->GetPoint(j, xB[j], yB[j]);
        //yB[j]*=-1.;
        xBerr[j] = 0.1;
        yBerr[j] = N1AHFfSUB3A_10_15->GetErrorY(j);

        xav[j] = xA[j];
        yav[j] = 0.5*(yA[j] + yB[j]);
        yerrav[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
    }
    TGraphErrors * N1AHFfSUB3A_10_15_ave = new TGraphErrors(numave, xav, yav, xAerr, yerrav);
    N1AHFfSUB3A_10_15_ave->SetMarkerStyle(21);
    N1AHFfSUB3A_10_15_ave->SetMarkerSize(1.2);
    N1AHFfSUB3A_10_15_ave->SetMarkerColor(kBlue);
    N1AHFfSUB3A_10_15_ave->SetLineColor(kBlue);

    for (int j = 0; j<numave; j++) {
        N1AHFfSUB3A_40_50->GetPoint(j, xA[j], yA[j]);
        yA[j]*=-1.;
        xAerr[j] = 0.1;
        yAerr[j] = N1AHFfSUB3A_40_50->GetErrorY(j);

        N1BHFfSUB3A_40_50->GetPoint(j, xB[j], yB[j]);
        //yB[j]*=-1.;
        xBerr[j] = 0.1;
        yBerr[j] = N1AHFfSUB3A_40_50->GetErrorY(j);

        xav[j] = xA[j];
        yav[j] = 0.5*(yA[j] + yB[j]);
        yerrav[j] = 0.5*sqrt( pow(yAerr[j],2) + pow(yBerr[j],2) );
    }
    TGraphErrors * N1AHFfSUB3A_40_50_ave = new TGraphErrors(numave, xav, yav, xAerr, yerrav);
    N1AHFfSUB3A_40_50_ave->SetMarkerStyle(20);
    N1AHFfSUB3A_40_50_ave->SetMarkerSize(1.3);
    N1AHFfSUB3a_40_50_ave->SetMarkerColor(kRed);
    N1AHFfSUB3A_40_50_ave->SetLineColor(kRed);


    //-- systematics
    finSyst = new TFile("../data/data_systematics.root","read");

    Double_t x[50], y[50], xerr[50], ysyst[50];
    int num = N1HFfSUB3_10_15_ave->GetN();
    for (int j = 0; j<num; j++) {
        N1HFfSUB3_10_15_ave->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1HFfSUB3_10_15_ave_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1HFfSUB3_10_15_ave_syst->SetLineColor(kBlue-10);
    N1HFfSUB3_10_15_ave_syst->SetFillColor(kBlue-10);

    for (int j = 0; j<num; j++) {
        N1HFfSUB3_40_50_ave->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_40_50");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1HFfSUB3_40_50_ave_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1HFfSUB3_40_50_ave_syst->SetLineColor(kBlue-10);
    N1HFfSUB3_40_50_ave_syst->SetFillColor(kBlue-10);

    //-- with decorrelation correction

    for (int j = 0; j<num; j++) {
        N1HFfSUB3A_10_15_ave->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_10_15");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1HFfSUB3A_10_15_ave_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1HFfSUB3A_10_15_ave_syst->SetLineColor(kBlue-10);
    N1HFfSUB3A_10_15_ave_syst->SetFillColor(kBlue-10);

    for (int j = 0; j<num; j++) {
        N1HFfSUB3A_40_50_ave->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("odd_errors/odd_40_50");
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    TGraphErrors * N1HFfSUB3A_40_50_ave_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1HFfSUB3A_40_50_ave_syst->SetLineColor(kBlue-10);
    N1HFfSUB3A_40_50_ave_syst->SetFillColor(kBlue-10);
    //--



    TCanvas * c = new TCanvas("c", "c", 1000, 600);
    c->Divide(2,1,0,0);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, 0, 7);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.80);
    h1->GetYaxis()->SetRangeUser(-0.06, 0.04);
    h1->Draw();
    N1HFfSUB3_10_15_ave_syst->Draw("same 2");
    N1HFfSUB3_40_50_ave_syst->Draw("same 2");
    N1HFfSUB3_10_15_ave->Draw("same p");
    N1HFfSUB3_40_50_ave->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  1.2 < |#eta| < 1.6");
    tx0->Draw();

    TLegend * leg1 = new TLegend(0.25, 0.21, 0.41, 0.39);
    SetLegend(leg1, 22);
    leg1->SetHeader("#eta_{C} = #eta_{ROI}");
    leg1->AddEntry(N1BHFfSUB3_10_15,"10-15%","p");
    leg1->AddEntry(N1BHFfSUB3_40_50,"40-50%","p");
    leg1->Draw();

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
    N1HFfSUB3A_10_15_ave_syst->Draw("same 2");
    N1HFfSUB3A_40_50_ave_syst->Draw("same 2");
    N1HFfSUB3A_10_15_ave->Draw("same p");
    N1HFfSUB3A_40_50_ave->Draw("same p");

    c->Print("../figures/fig1A.pdf","pdf");
    c->Print("../figures/fig1A.png","png");

}
