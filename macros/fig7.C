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

static const int ncbins = 16;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 10, 10, 10, 20, 30};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 60, 70, 20, 30, 40};

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
TFile * finATLAS;
TFile * finALICE;
TFile * finSyst;
TH1D * h1;
TGraphErrors * N1MCp22SUB3;
TGraphErrors * N1MCm22SUB3;
TGraphErrors * N1MC22SUB3;
TH1D * ATLAS_v1even_2PC_PbPb_30_40;
TH1D * ALICE_v1even_eta_c5_80;


void fig7() {

    finCMS = new TFile("../data/data_fig7.root","read");

    // select centrality bin
    int cminREF = 30;
    int cmaxREF = 40;

    // retrieve ATLAS results
    finATLAS = new TFile("../data/PRC_86_014907.root","read");
    ATLAS_v1even_2PC_PbPb_30_40 = (TH1D *) finATLAS->Get("ATLAS_v1even_2PC_PbPb_30_40");
    ATLAS_v1even_2PC_PbPb_30_40->SetMarkerColor(kBlack);
    ATLAS_v1even_2PC_PbPb_30_40->SetMarkerStyle(27);
    ATLAS_v1even_2PC_PbPb_30_40->SetMarkerSize(0.2);
    ATLAS_v1even_2PC_PbPb_30_40->SetLineColor(kGray);
    ATLAS_v1even_2PC_PbPb_30_40->SetLineWidth(5);
    ATLAS_v1even_2PC_PbPb_30_40->SetFillColor(kGray);
    ATLAS_v1even_2PC_PbPb_30_40->SetFillStyle(1001);
    ATLAS_v1even_2PC_PbPb_30_40->SetLineWidth(2);

    // retrieve ALICE results
    finALICE = new TFile("../data/PRL_111_232302.root","read");
    ALICE_v1even_eta_c5_80 = (TH1D *) finALICE->Get("ALICE_v1even_pT_5_80");
    ALICE_v1even_eta_c5_80->SetMarkerColor(kMagenta);
    ALICE_v1even_eta_c5_80->SetLineColor(kMagenta);
    ALICE_v1even_eta_c5_80->SetMarkerStyle(21);
    ALICE_v1even_eta_c5_80->SetMarkerSize(1.2);

    // Average negative and positive side v1even
    N1MCp22SUB3 = (TGraphErrors *) finCMS->Get(Form("N1MCp22SUB3/-2.4_0.0/%d_%d/gA",cminREF,cmaxREF));
    N1MCm22SUB3 = (TGraphErrors *) finCMS->Get(Form("N1MCm22SUB3/0.0_2.4/%d_%d/gA",cminREF,cmaxREF));
    Double_t xp[50], xm[50], yp[50], ym[50], yperr[50], ymerr[50], ypm[50], ypmerr[50];
    int num = N1MCp22SUB3->GetN();
    for (int j = 0; j<num; j++) {
        N1MCp22SUB3->GetPoint(j, xp[j], yp[j]);
        yperr[j] = N1MCp22SUB3->GetErrorY(j);

        N1MCm22SUB3->GetPoint(j, xm[j], ym[j]);
        ymerr[j] = N1MCm22SUB3->GetErrorY(j);

        ypm[j] = 0.5*(yp[j] + ym[j]);
        ypmerr[j] = 0.5*sqrt( yperr[j]*yperr[j] + ymerr[j]*ymerr[j] );
    }
    N1MC22SUB3 = new TGraphErrors(num, xp, ypm, 0, ypmerr);



    TCanvas * c = new TCanvas("c", "c", 650, 600);
    TPad * pad1 = (TPad *) c->cd();
    pad1->SetTopMargin(0.07);
    h1 = new TH1D("h1", "", 100, 0, 8.5);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{even}");
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->SetRangeUser(-0.04, 0.2);
    h1->Draw();
    ATLAS_v1even_2PC_PbPb_30_40->Draw("same E3");
    ATLAS_v1even_2PC_PbPb_30_40->Draw("same p");
    ALICE_v1even_eta_c5_80->Draw("same p");
    N1MC22SUB3->SetMarkerStyle(21);
    N1MC22SUB3->SetMarkerSize(1.2);
    N1MC22SUB3->SetMarkerColor(kBlue);
    N1MC22SUB3->SetLineColor(kBlue);
    N1MC22SUB3->Draw("same p");

    TPaveText * tx0 = new TPaveText(0.164, 0.933, 0.377, 0.973, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary}, PbPb #sqrt{s_{NN}} = 5.02 TeV, |#eta| < 2.4");
    tx0->Draw();

    // TPaveText * tx1 = new TPaveText(0.20, 0.85, 0.52, 0.91, "NDC");
    // SetTPaveTxt(tx1, 18);
    // tx1->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    // tx1->AddText("|#eta| < 2.4");
    // tx1->Draw();

    TLegend * leg1 = new TLegend(0.20, 0.76, 0.42, 0.90);
    SetLegend(leg1, 16);
    leg1->AddEntry(N1MC22SUB3,Form("v_{1}^{part} CMS PbPb #sqrt{s_{NN}}=5.02 TeV (%d-%d%%)",cminREF,cmaxREF),"p");
    leg1->AddEntry(ATLAS_v1even_2PC_PbPb_30_40,Form("v_{1}^{part} ATLAS 2PC PbPb #sqrt{s_{NN}}=2.76 TeV (%d-%d%%)",cminREF,cmaxREF),"lp");
    leg1->AddEntry(ALICE_v1even_eta_c5_80,"v_{1}^{spec} ALICE ZDC PbPb  #sqrt{s_{NN}}=2.76 TeV (5-80%)","p");
    leg1->Draw();

    c->Print("../figures/fig7.pdf","pdf");

}
