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

double ErrDiffCalc( double x, double y, double delx, double dely ) {
    double f = x;
    f-=y;
    double delf = sqrt( fabs(delx*delx - dely*dely) );
    return delf;
}

TFile * fin;
TH1D * hA;
TH1D * hB;
TH1D * hAB;
TGraphErrors * g1A;
TGraphErrors * g2A;
TGraphErrors * g3A;
TGraphErrors * g4A;
TGraphErrors * g5A;
TGraphErrors * g1B;
TGraphErrors * g2B;
TGraphErrors * g3B;
TGraphErrors * g4B;
TGraphErrors * g5B;
TGraphErrors * g1AB;
TGraphErrors * g2AB;
TGraphErrors * g3AB;
TGraphErrors * g4AB;
TGraphErrors * g5AB;

void fig3() {

    fin = new TFile("../data/data_fig3.root");

    g1A = (TGraphErrors *) fin->Get("default/N1HFcSUB2/-2.0_2.0/20_60/gintA");
    g1A->RemovePoint(0);
    g1A->RemovePoint(g1A->GetN()-1);

    g2A = (TGraphErrors *) fin->Get("default/N1HFdSUB2/-2.0_2.0/20_60/gintA");
    g2A->RemovePoint(0);
    g2A->RemovePoint(g2A->GetN()-1);

    g3A = (TGraphErrors *) fin->Get("default/N1HFeSUB2/-2.0_2.0/20_60/gintA");
    g3A->RemovePoint(0);
    g3A->RemovePoint(g3A->GetN()-1);

    g4A = (TGraphErrors *) fin->Get("default/N1HFfSUB2/-2.0_2.0/20_60/gintA");
    g4A->RemovePoint(0);
    g4A->RemovePoint(g4A->GetN()-1);

    g5A = (TGraphErrors *) fin->Get("default/N1HFgSUB2/-2.0_2.0/20_60/gintA");
    g5A->RemovePoint(0);
    g5A->RemovePoint(g5A->GetN()-1);

    g1B = (TGraphErrors *) fin->Get("default/N1HFcSUB2/-2.0_2.0/20_60/gintB");
    g1B->RemovePoint(0);
    g1B->RemovePoint(g1B->GetN()-1);

    g2B = (TGraphErrors *) fin->Get("default/N1HFdSUB2/-2.0_2.0/20_60/gintB");
    g2B->RemovePoint(0);
    g2B->RemovePoint(g2B->GetN()-1);

    g3B = (TGraphErrors *) fin->Get("default/N1HFeSUB2/-2.0_2.0/20_60/gintB");
    g3B->RemovePoint(0);
    g3B->RemovePoint(g3B->GetN()-1);

    g4B = (TGraphErrors *) fin->Get("default/N1HFfSUB2/-2.0_2.0/20_60/gintB");
    g4B->RemovePoint(0);
    g4B->RemovePoint(g4B->GetN()-1);

    g5B = (TGraphErrors *) fin->Get("default/N1HFgSUB2/-2.0_2.0/20_60/gintB");
    g5B->RemovePoint(0);
    g5B->RemovePoint(g5B->GetN()-1);

    g1AB = (TGraphErrors *) fin->Get("default/N1HFcSUB2/-2.0_2.0/20_60/gint");
    g1AB->RemovePoint(0);
    g1AB->RemovePoint(g1AB->GetN()-1);

    g2AB = (TGraphErrors *) fin->Get("default/N1HFdSUB2/-2.0_2.0/20_60/gint");
    g2AB->RemovePoint(0);
    g2AB->RemovePoint(g2AB->GetN()-1);

    g3AB = (TGraphErrors *) fin->Get("default/N1HFeSUB2/-2.0_2.0/20_60/gint");
    g3AB->RemovePoint(0);
    g3AB->RemovePoint(g3AB->GetN()-1);

    g4AB = (TGraphErrors *) fin->Get("default/N1HFfSUB2/-2.0_2.0/20_60/gint");
    g4AB->RemovePoint(0);
    g4AB->RemovePoint(g4AB->GetN()-1);

    g5AB = (TGraphErrors *) fin->Get("default/N1HFgSUB2/-2.0_2.0/20_60/gint");
    g5AB->RemovePoint(0);
    g5AB->RemovePoint(g5AB->GetN()-1);


    g1A->SetMarkerStyle(20);
    g1A->SetMarkerSize(1.3);
    g1A->SetMarkerColor(kMagenta);
    g1A->SetLineColor(kMagenta);

    g2A->SetMarkerStyle(25);
    g2A->SetMarkerSize(1.2);
    g2A->SetMarkerColor(kRed);
    g2A->SetLineColor(kRed);

    g3A->SetMarkerStyle(20);
    g3A->SetMarkerSize(1.3);
    g3A->SetMarkerColor(kGreen+2);
    g3A->SetLineColor(kGreen+2);

    g4A->SetMarkerStyle(21);
    g4A->SetMarkerSize(1.2);
    g4A->SetMarkerColor(kBlue);
    g4A->SetLineColor(kBlue);

    g5A->SetMarkerStyle(24);
    g5A->SetMarkerSize(1.3);
    g5A->SetMarkerColor(kBlack);
    g5A->SetLineColor(kBlack);


    g1B->SetMarkerStyle(20);
    g1B->SetMarkerSize(1.3);
    g1B->SetMarkerColor(kMagenta);
    g1B->SetLineColor(kMagenta);

    g2B->SetMarkerStyle(25);
    g2B->SetMarkerSize(1.2);
    g2B->SetMarkerColor(kRed);
    g2B->SetLineColor(kRed);

    g3B->SetMarkerStyle(20);
    g3B->SetMarkerSize(1.3);
    g3B->SetMarkerColor(kGreen+2);
    g3B->SetLineColor(kGreen+2);

    g4B->SetMarkerStyle(21);
    g4B->SetMarkerSize(1.2);
    g4B->SetMarkerColor(kBlue);
    g4B->SetLineColor(kBlue);

    g5B->SetMarkerStyle(24);
    g5B->SetMarkerSize(1.3);
    g5B->SetMarkerColor(kBlack);
    g5B->SetLineColor(kBlack);


    g1AB->SetMarkerStyle(20);
    g1AB->SetMarkerSize(1.3);
    g1AB->SetMarkerColor(kMagenta);
    g1AB->SetLineColor(kMagenta);

    g2AB->SetMarkerStyle(25);
    g2AB->SetMarkerSize(1.2);
    g2AB->SetMarkerColor(kRed);
    g2AB->SetLineColor(kRed);

    g3AB->SetMarkerStyle(20);
    g3AB->SetMarkerSize(1.3);
    g3AB->SetMarkerColor(kGreen+2);
    g3AB->SetLineColor(kGreen+2);

    g4AB->SetMarkerStyle(21);
    g4AB->SetMarkerSize(1.2);
    g4AB->SetMarkerColor(kBlue);
    g4AB->SetLineColor(kBlue);

    g5AB->SetMarkerStyle(24);
    g5AB->SetMarkerSize(1.3);
    g5AB->SetMarkerColor(kBlack);
    g5AB->SetLineColor(kBlack);


    //-- --//

    TCanvas * cA = new TCanvas("cA", "cA", 620, 600);
    TPad * padA = (TPad *) cA->cd();
    padA->SetTopMargin(0.08);
    padA->SetLeftMargin(0.18);
    hA = new TH1D("hA", "", 100, -2.5, 2.5);
    hA->SetStats(0);
    hA->SetXTitle("#eta");
    hA->SetYTitle("v_{1}{HF+}");
    hA->GetYaxis()->SetDecimals();
    hA->GetYaxis()->SetNdivisions(509);
    hA->GetXaxis()->CenterTitle();
    hA->GetYaxis()->CenterTitle();
    hA->GetXaxis()->SetTitleOffset(1.15);
    hA->GetYaxis()->SetTitleOffset(1.70);
    hA->GetYaxis()->SetRangeUser(-0.0475, 0.0);
    hA->Draw();
    g1A->Draw("same p");
    g2A->Draw("same p");
    g3A->Draw("same p");
    g4A->Draw("same p");
    g5A->Draw("same p");

    TPaveText * txA0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(txA0, 20);
    txA0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    txA0->Draw();

    TPaveText * txA1 = new TPaveText(0.26, 0.79, 0.41, 0.87, "NDC");
    SetTPaveTxt(txA1, 26);
    txA1->AddText("20 - 60%");
    txA1->Draw();

    TLegend * legA = new TLegend(0.61, 0.63, 0.85, 0.88);
    SetLegend(legA, 20);
    legA->AddEntry(g5A,"4.0 < |#eta_{A,B}| < 5.0","p");
    legA->AddEntry(g4A,"4.5 < |#eta_{A,B}| < 5.0","p");
    legA->AddEntry(g3A,"4.0 < |#eta_{A,B}| < 4.5","p");
    legA->AddEntry(g2A,"3.5 < |#eta_{A,B}| < 4.0","p");
    legA->AddEntry(g1A,"3.0 < |#eta_{A,B}| < 3.5","p");
    // legA->Draw();

    // cA->Print("c_EtaGap_v1HFp.pdf","pdf");
    // cA->Print("c_EtaGap_v1HFp.png","png");


    //--  --//

    TCanvas * cB = new TCanvas("cB", "cB", 620, 600);
    TPad * padB = (TPad *) cB->cd();
    padB->SetTopMargin(0.08);
    padB->SetLeftMargin(0.18);
    hB = new TH1D("hB", "", 100, -2.5, 2.5);
    hB->SetStats(0);
    hB->SetXTitle("#eta");
    hB->SetYTitle("v_{1}{HF-}");
    hB->GetYaxis()->SetDecimals();
    hB->GetYaxis()->SetNdivisions(509);
    hB->GetXaxis()->CenterTitle();
    hB->GetYaxis()->CenterTitle();
    hB->GetXaxis()->SetTitleOffset(1.15);
    hB->GetYaxis()->SetTitleOffset(1.70);
    hB->GetYaxis()->SetRangeUser(-0.065, 0.0);
    hB->Draw();
    g1B->Draw("same p");
    g2B->Draw("same p");
    g3B->Draw("same p");
    g4B->Draw("same p");
    g5B->Draw("same p");

    TPaveText * txB0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(txB0, 20);
    txB0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    txB0->Draw();

    TPaveText * txB1 = new TPaveText(0.22, 0.82, 0.37, 0.89, "NDC");
    SetTPaveTxt(txB1, 22);
    txB1->AddText("20 - 60%");
    txB1->Draw();

    // cB->Print("c_EtaGap_v1HFm.pdf","pdf");
    // cB->Print("c_EtaGap_v1HFm.png","png");


    //--  --//

    TCanvas * cAB = new TCanvas("cAB", "cAB", 620, 600);
    TPad * padAB = (TPad *) cAB->cd();
    padAB->SetTopMargin(0.08);
    padAB->SetLeftMargin(0.18);
    hAB = new TH1D("hAB", "", 100, -2.5, 2.5);
    hAB->SetStats(0);
    hAB->SetXTitle("#eta");
    hAB->SetYTitle("v_{1}^{odd}");
    hAB->GetYaxis()->SetDecimals();
    hAB->GetYaxis()->SetNdivisions(509);
    hAB->GetXaxis()->CenterTitle();
    hAB->GetYaxis()->CenterTitle();
    hAB->GetXaxis()->SetTitleOffset(1.15);
    hAB->GetYaxis()->SetTitleOffset(1.70);
    hAB->GetYaxis()->SetRangeUser(-0.015, 0.015);
    hAB->Draw();
    g1AB->Draw("same p");
    g2AB->Draw("same p");
    g3AB->Draw("same p");
    g4AB->Draw("same p");
    g5AB->Draw("same p");

    TPaveText * txAB0 = new TPaveText(0.178, 0.934, 0.420, 0.979, "NDC");
    SetTPaveTxt(txAB0, 20);
    txAB0->AddText("#bf{CMS} #it{Preliminary},  PbPb 5.02 TeV,  0.3 < p_{T} < 3.0 GeV/c");
    // txAB0->Draw();

    TPaveText * txAB1 = new TPaveText(0.64, 0.75, 0.79, 0.90, "NDC");
    SetTPaveTxt(txAB1, 22);
    txAB1->AddText("20 - 60%");
    // txAB1->Draw();

    TLegend * legAB = new TLegend(0.23, 0.20, 0.47, 0.46);
    SetLegend(legAB, 20);
    legAB->AddEntry(g5AB,"4.0 < |#eta_{A,B}| < 5.0","p");
    legAB->AddEntry(g4AB,"4.5 < |#eta_{A,B}| < 5.0","p");
    legAB->AddEntry(g3AB,"4.0 < |#eta_{A,B}| < 4.5","p");
    legAB->AddEntry(g2AB,"3.5 < |#eta_{A,B}| < 4.0","p");
    legAB->AddEntry(g1AB,"3.0 < |#eta_{A,B}| < 3.5","p");
    // legAB->Draw();

    // cAB->Print("c_EtaGap_v1odd.pdf","pdf");
    // cAB->Print("c_EtaGap_v1odd.png","png");


    //--  --//

    TCanvas * cAB2 = new TCanvas("cAB2", "cAB2", 1240, 600);
    cAB2->Divide(2,1);
    TPad * pad_AB2_1 = (TPad *) cAB2->cd(1);
    pad_AB2_1->SetTopMargin(0.08);
    pad_AB2_1->SetLeftMargin(0.18);
    hA->Draw();
    g1A->Draw("same p");
    g2A->Draw("same p");
    g3A->Draw("same p");
    g4A->Draw("same p");
    g5A->Draw("same p");
    txA0->Draw();
    txA1->Draw();
    legA->Draw();

    TPad * padAB2_2 = (TPad *) cAB2->cd(2);
    padAB2_2->SetTopMargin(0.08);
    padAB2_2->SetLeftMargin(0.18);
    hAB->Draw();
    g1AB->Draw("same p");
    g2AB->Draw("same p");
    g3AB->Draw("same p");
    g4AB->Draw("same p");
    g5AB->Draw("same p");
    // legAB->Draw();

    cAB2->Print("../figures/fig3.pdf","pdf");
    // cAB2->Print("../figures/fig3.png","png");

}
