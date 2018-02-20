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

TFile * fin;
TFile * finSyst;
TH1D * h1;
TH1D * h2;
TGraphErrors * N1HFfSUB2[ncbins];
TGraphErrors * N1HFfSUB2_syst[ncbins];

void fig2() {

    fin = new TFile("../data/data_fig2.root");

    int col[6] = {kRed, kOrange+5, kBlue, kGreen+3, kCyan+2, kMagenta};
    int mrkstyle[6] = {20, 25, 28, 21, 31, 29};
    double mrksize[6] = {1.1, 1.0, 1.2, 1.0, 1.3, 1.4};

    for (int i = 0; i<=5; i++) {
        N1HFfSUB2[i] = (TGraphErrors *) fin->Get(Form("N1HFfSUB2/-2.0_2.0/%d_%d/gint",cmin[i],cmax[i]));
        N1HFfSUB2[i]->SetMarkerStyle(mrkstyle[i]);
        N1HFfSUB2[i]->SetMarkerSize(mrksize[i]);
        N1HFfSUB2[i]->SetMarkerColor(col[i]);
        N1HFfSUB2[i]->SetLineColor(col[i]);
    }
    for (int i = 6; i<ncbins; i++) {
        N1HFfSUB2[i] = (TGraphErrors *) fin->Get(Form("N1HFfSUB2/-2.0_2.0/%d_%d/gint",cmin[i],cmax[i]));
        N1HFfSUB2[i]->SetMarkerStyle(mrkstyle[i-6]);
        N1HFfSUB2[i]->SetMarkerSize(mrksize[i-6]);
        N1HFfSUB2[i]->SetMarkerColor(col[i-6]);
        N1HFfSUB2[i]->SetLineColor(col[i-6]);
    }


    //-- systematics
    finSyst = new TFile("../data/data_systematics.root","read");

    for (int i = 0; i<ncbins; i++) {
        Double_t x[50], y[50], xerr[50], ysyst[50];
        int num = N1HFfSUB2[i]->GetN();
        for (int j = 0; j<num; j++) {
            N1HFfSUB2[i]->GetPoint(j, x[j], y[j]);
            xerr[j] = 0.1;
            TH1D * hsyst = (TH1D *) finSyst->Get(Form("odd_errors/odd_%d_%d",cmin[i],cmax[i]));
            ysyst[j] = y[j] * hsyst->GetBinContent(1);
            hsyst->Delete();
        }
        N1HFfSUB2_syst[i] = new TGraphErrors(num, x, y, xerr, ysyst);
        N1HFfSUB2_syst[i]->SetLineColor(kBlue-10);
        N1HFfSUB2_syst[i]->SetFillColor(kBlue-10);
    }
    //--


    TCanvas * c = new TCanvas("c", "c", 1000, 600);
    c->Divide(2,1,0,0);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.07);
    h1 = new TH1D("h1", "", 100, -2.15, 2.15);
    h1->SetStats(0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->SetRangeUser(-0.042, 0.042);
    h1->Draw();
    for (int i = 0; i<=5; i++) {
        N1HFfSUB2_syst[i]->Draw("same 2");
    }
    for (int i = 0; i<=5; i++) {
        N1HFfSUB2[i]->Draw("same p");
    }

    TPaveText * tx0 = new TPaveText(0.184, 0.947, 0.399, 0.986, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary}");
    tx0->Draw();

    TPaveText * tx1 = new TPaveText(0.22, 0.80, 0.54, 0.90, "NDC");
    SetTPaveTxt(tx1, 18);
    tx1->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    tx1->AddText("0.3 < p_{T} < 3.0 GeV/c");
    tx1->Draw();

    TLegend * leg1 = new TLegend(0.23, 0.20, 0.48, 0.47);
    SetLegend(leg1, 18);
    for (int i = 0; i<=5; i++) {
        leg1->AddEntry(N1HFfSUB2[i],Form("%d-%d%%",cmin[i],cmax[i]),"p");
    }
    leg1->Draw();

    TPad * pad2 = (TPad *) c->cd(2);
    pad2->SetTopMargin(0.07);
    pad2->SetRightMargin(0.03);
    h2 = (TH1D *) h1->Clone("h2");
    h2->GetYaxis()->SetTitleSize(0.0);
    h2->GetYaxis()->SetLabelSize(0.0);
    h2->Draw();
    for (int i = 6; i<ncbins; i++) {
        N1HFfSUB2_syst[i]->Draw("same 2");
    }
    for (int i = 6; i<ncbins; i++) {
        N1HFfSUB2[i]->Draw("same p");
    }
    TLegend * leg2 = new TLegend(0.05, 0.23, 0.30, 0.47);
    SetLegend(leg2, 18);
    for (int i = 6; i<ncbins; i++) {
        leg2->AddEntry(N1HFfSUB2[i],Form("%d-%d%%",cmin[i],cmax[i]),"p");
    }
    leg2->Draw();

    c->Print("../figures/fig2.pdf","pdf");
    c->Print("../figures/fig2.png","png");

}
