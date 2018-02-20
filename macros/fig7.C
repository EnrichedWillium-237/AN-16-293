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
TGraphErrors * N1MCp22SUB2;
TGraphErrors * N1MCm22SUB2;
TGraphErrors * N1MC22SUB2;
TGraphErrors * N1MC22SUB2_syst;
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
    ALICE_v1even_eta_c5_80->SetMarkerStyle(25);
    ALICE_v1even_eta_c5_80->SetMarkerSize(1.2);

    // Average negative and positive side v1even
    N1MCp22SUB2 = (TGraphErrors *) finCMS->Get(Form("N1MCp22SUB2/-2.4_-0.4/%d_%d/gA",cminREF,cmaxREF));
    N1MCm22SUB2 = (TGraphErrors *) finCMS->Get(Form("N1MCm22SUB2/0.4_2.4/%d_%d/gA",cminREF,cmaxREF));
    Double_t xp[50], xm[50], yp[50], ym[50], yperr[50], ymerr[50], ypm[50], ypmerr[50];
    int num = N1MCp22SUB2->GetN();
    for (int j = 0; j<num; j++) {
        N1MCp22SUB2->GetPoint(j, xp[j], yp[j]);
        yperr[j] = N1MCp22SUB2->GetErrorY(j);

        N1MCm22SUB2->GetPoint(j, xm[j], ym[j]);
        ymerr[j] = N1MCm22SUB2->GetErrorY(j);

        ypm[j] = 0.5*(yp[j] + ym[j]);
        ypmerr[j] = 0.5*sqrt( yperr[j]*yperr[j] + ymerr[j]*ymerr[j] );
    }
    N1MC22SUB2 = new TGraphErrors(num, xp, ypm, 0, ypmerr);
    N1MC22SUB2->SetMarkerStyle(21);
    N1MC22SUB2->SetMarkerSize(1.2);
    N1MC22SUB2->SetMarkerColor(kBlue);
    N1MC22SUB2->SetLineColor(kBlue);


    //-- systematics
    finSyst = new TFile("../data/data_systematics.root","read");

    Double_t x[50], y[50], xerr[50], ysyst[50];
    num = N1MC22SUB2->GetN();
    for (int j = 0; j<num; j++) {
        N1MC22SUB2->GetPoint(j, x[j], y[j]);
        xerr[j] = 0.1;
        TH1D * hsyst = (TH1D *) finSyst->Get("even_errors/even_30_35"); // not significantly different from 30-40
        ysyst[j] = y[j] * hsyst->GetBinContent(1);
        hsyst->Delete();
    }
    N1MC22SUB2_syst = new TGraphErrors(num, x, y, xerr, ysyst);
    N1MC22SUB2_syst->SetLineColor(kBlue-10);
    N1MC22SUB2_syst->SetFillColor(kBlue-10);
    //--


    TCanvas * c = new TCanvas("c", "c", 620, 600);
    TPad * pad1 = (TPad *) c->cd(1);
    pad1->SetTopMargin(0.08);
    pad1->SetLeftMargin(0.18);
    h1 = new TH1D("h1", "", 100, 0, 8.5);
    h1->SetStats(0);
    h1->SetXTitle("p_{T} (GeV/c)");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetDecimals();
    h1->GetXaxis()->CenterTitle();
    h1->GetYaxis()->CenterTitle();
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetYaxis()->SetTitleOffset(1.65);
    h1->GetYaxis()->SetRangeUser(-0.04, 0.2);
    h1->Draw();
    ATLAS_v1even_2PC_PbPb_30_40->Draw("same E3");
    ATLAS_v1even_2PC_PbPb_30_40->Draw("same p");
    ALICE_v1even_eta_c5_80->Draw("same p");
    N1MC22SUB2_syst->Draw("same 2");
    N1MC22SUB2->Draw("same p");
    cout<<"here"<<endl;

    TPaveText * tx0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(tx0, 20);
    tx0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.4 < |#eta| < 2.4");
    tx0->Draw();

    TLegend * leg1 = new TLegend(0.22, 0.73, 0.44, 0.88);
    SetLegend(leg1, 20);
    leg1->AddEntry(N1MC22SUB2,Form("CMS (%d-%d%%)",cminREF,cmaxREF),"p");
    leg1->AddEntry(ATLAS_v1even_2PC_PbPb_30_40,Form("ATLAS 2PC fit, PbPb 2.76 TeV (%d-%d%%)",cminREF,cmaxREF),"lp");
    leg1->AddEntry(ALICE_v1even_eta_c5_80,"ALICE ZDC, PbPb 2.76 TeV (5-80%)","p");
    leg1->Draw();

    c->Print("../figures/fig7.pdf","pdf");
    c->Print("../figures/fig7.png","png");


    // alternate version
    TCanvas * c_v2 = new TCanvas("c1_v2", "c_v2", 620, 600);
    TPad * pad1_v2 = (TPad *) c_v2->cd(1);
    pad1_v2->SetTopMargin(0.08);
    pad1_v2->SetLeftMargin(0.18);
    TH1D * h1_v2 = (TH1D *) h1->Clone("h1_v2");
    h1_v2->SetStats(0);
    h1_v2->SetXTitle("p_{T} (GeV/c)");
    h1_v2->SetYTitle("v_{1}^{odd}");
    h1_v2->GetYaxis()->SetRangeUser(-0.04, 0.25);
    h1_v2->Draw();
    ATLAS_v1even_2PC_PbPb_30_40->Draw("same E3");
    ATLAS_v1even_2PC_PbPb_30_40->Draw("same p");
    ALICE_v1even_eta_c5_80->Draw("same p");
    N1MC22SUB2_syst->Draw("same 2");
    N1MC22SUB2->Draw("same p");
    cout<<"here"<<endl;

    tx0->Draw();

    TLegend * leg1_v2 = new TLegend(0.22, 0.75, 0.44, 0.89);
    SetLegend(leg1_v2, 18);
    leg1_v2->SetHeader("Participant v_{1}^{even}");
    leg1_v2->AddEntry(N1MC22SUB2,Form("CMS (%d-%d%%)",cminREF,cmaxREF),"p");
    leg1_v2->AddEntry(ATLAS_v1even_2PC_PbPb_30_40,Form("ATLAS 2PC fit, PbPb 2.76 TeV (%d-%d%%)",cminREF,cmaxREF),"lp");
    leg1_v2->Draw();

    TLegend * leg2_v2 = new TLegend(0.22, 0.65, 0.44, 0.75);
    SetLegend(leg2_v2, 18);
    leg2_v2->SetHeader("Spectator v_{1}^{even}");
    leg2_v2->AddEntry(ALICE_v1even_eta_c5_80,"ALICE ZDC, PbPb 2.76 TeV (5-80%)","p");
    leg2_v2->Draw();

    c_v2->Print("../figures/fig7_v2.pdf","pdf");
    c_v2->Print("../figures/fig7_v2.png","png");

}
