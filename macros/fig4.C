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
TH1D * h1;
TH1D * h2;
TGraphErrors * N1MCp22SUB3[ncbins];
TGraphErrors * N1MCm22SUB3[ncbins];
TGraphErrors * N1MC22SUB3[ncbins];

void fig4() {

    fin = new TFile("../data/data_fig4.root");

    // Average negative and positive side v1even
    for (int i = 0; i<ncbins; i++) {
        N1MCp22SUB3[i] = (TGraphErrors *) fin->Get(Form("N1MCp22SUB3/-2.4_0.0/%d_%d/gA",cmin[i],cmax[i]));
        N1MCm22SUB3[i] = (TGraphErrors *) fin->Get(Form("N1MCm22SUB3/0.0_2.4/%d_%d/gA",cmin[i],cmax[i]));
        Double_t xp[50], xm[50], yp[50], ym[50], yperr[50], ymerr[50], ypm[50], ypmerr[50];
        int num = N1MCp22SUB3[i]->GetN();
        for (int j = 0; j<num; j++) {
            N1MCp22SUB3[i]->GetPoint(j, xp[j], yp[j]);
            yperr[j] = N1MCp22SUB3[i]->GetErrorY(j);

            N1MCm22SUB3[i]->GetPoint(j, xm[j], ym[j]);
            ymerr[j] = N1MCm22SUB3[i]->GetErrorY(j);

            ypm[j] = 0.5*(yp[j] + ym[j]);
            ypmerr[j] = 0.5*sqrt( yperr[j]*yperr[j] + ymerr[j]*ymerr[j] );
        }
        N1MC22SUB3[i] = new TGraphErrors(num, xp, ypm, 0, ypmerr);
    }

    int col[6] = {kRed, kOrange+5, kBlue, kGreen+3, kCyan+2, kYellow+2};
    int mrkstyle[6] = {20, 25, 28, 21, 31, 29};
    double mrksize[6] = {1.1, 1.0, 1.2, 1.0, 1.3, 1.4};

    TCanvas * c = new TCanvas("c", "c", 1000, 600);
    c->Divide(2,1,0,0);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.07);
    h1 = new TH1D("h1", "", 100, 0, 12);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{even}");
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->SetRangeUser(-0.042, 0.27);
    h1->Draw();
    for (int i = 0; i<=5; i++) {
        N1MC22SUB3[i]->SetMarkerStyle(mrkstyle[i]);
        N1MC22SUB3[i]->SetMarkerSize(mrksize[i]);
        N1MC22SUB3[i]->SetMarkerColor(col[i]);
        N1MC22SUB3[i]->SetLineColor(col[i]);
        N1MC22SUB3[i]->Draw("same p");
    }
    TPaveText * tx0 = new TPaveText(0.193, 0.940, 0.409, 0.981, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary}");
    tx0->Draw();
    TPaveText * tx1 = new TPaveText(0.24, 0.84, 0.56, 0.90, "NDC");
    SetTPaveTxt(tx1, 20);
    tx1->AddText("|#eta| < 2.4");
    tx1->Draw();
    TLegend * leg1 = new TLegend(0.77, 0.62, 0.95, 0.89);
    SetLegend(leg1, 20);
    for (int i = 0; i<=5; i++) {
        leg1->AddEntry(N1MC22SUB3[i],Form("%d-%d%%",cmin[i],cmax[i]),"p");
    }
    leg1->Draw();

    TPad * pad2 = (TPad *) c->cd(2);
    pad2->SetTopMargin(0.07);
    pad2->SetRightMargin(0.03);
    h2 = (TH1D *) h1->Clone("h2");
    h2->Draw();
    for (int i = 6; i<ncbins; i++) {
        N1MC22SUB3[i]->SetMarkerStyle(mrkstyle[i-6]);
        N1MC22SUB3[i]->SetMarkerSize(mrksize[i-6]);
        N1MC22SUB3[i]->SetMarkerColor(col[i-6]);
        N1MC22SUB3[i]->SetLineColor(col[i-6]);
        N1MC22SUB3[i]->Draw("same p");
    }
    TLegend * leg2 = new TLegend(0.70, 0.64, 0.92, 0.90);
    SetLegend(leg2, 20);
    for (int i = 6; i<ncbins; i++) {
        leg2->AddEntry(N1MC22SUB3[i],Form("%d-%d%%",cmin[i],cmax[i]),"p");
    }
    leg2->Draw();

    c->Print("../figures/fig4.pdf","pdf");

}
