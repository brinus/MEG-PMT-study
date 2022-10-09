#include <vector>

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TMath.h"
#include "TLegend.h"
#include "TF1.h"
#include "TStyle.h"

/**
 * @brief Square sum of variables
 *
 * @details Performs the squareroot of the sum of the square of the inputs.
 *
 * @param x First value
 * @param y Second value
 * @return Sqrt(x^2 + y^2)
 */
Double_t SqrtSquareSum(Double_t x, Double_t y)
{
    return TMath::Sqrt(x * x + y * y);
}

/**
 * @brief Draws the legend
 * 
 * @param leg_plot1 
 * @param leg_plot2 
 * @param leg_func_linear 
 * @return TLegend* 
 */
TLegend * drawLegend(TGraphErrors * leg_plot1, TGraphErrors * leg_plot2, TF1 * leg_func_linear = 0){
    TLegend * legend = new TLegend(0.15, 0.7, 0.35, 0.87, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(22);
    legend->SetFillColorAlpha(0,0.0);
    legend->AddEntry(leg_plot1, "Two-layers tape #oslash = 2.50 #pm 0.01 cm", "EP");
    legend->AddEntry(leg_plot2, "One-layer tape #oslash = 1.50 #pm 0.01 cm", "EP");
    if (leg_func_linear)
    {
        legend->AddEntry(leg_func_linear, "best-fit", "L");
    }
    legend->Draw();
    return legend;
}

void XvsB()
{
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);

    // Variables

    Double_t offsetX = 1.60;             // X offset [cm]
    Double_t offseteX = 0.05;            // X offset error [cm]
    Double_t eX = 0.1 / TMath::Sqrt(12); // X scale error [cm]

    // Big cylinder (B)
    std::vector<Double_t> vX_B = {1, 2, 3, 4, 5,
                                  6, 7, 8, 9, 10}; // X data [cm]
    std::vector<Double_t> vB_B = {-53.14, -28.93, -18.524, -12.445, -7.797,
                                  -5.404, -3.951, -2.971, -2.120, -1.521}; // B data [mT]

    std::vector<Double_t> veX_B; // X errors [cm]
    std::vector<Double_t> veB_B = {0.01, 0.01, 0.001, 0.001, 0.001,
                                   0.001, 0.001, 0.001, 0.001, 0.001}; // B errors [mT]

    // Small cylinder (b)
    std::vector<Double_t> vX_b = {1, 2, 3, 4, 5,
                                  6, 7, 8, 9, 10}; // X data [cm]
    std::vector<Double_t> vB_b = {-68.68, -39.90, -24.27, -15.370, -10.327,
                                  -7.236, -5.240, -3.748, -2.775, -2.038}; // B data [mT]

    std::vector<Double_t> veX_b; // X errors [cm]
    std::vector<Double_t> veB_b = {0.01, 0.01, 0.01, 0.001, 0.001,
                                   0.001, 0.001, 0.001, 0.001, 0.001}; // B errors [mT]

    // Adjusting the vectors
    for (Int_t i = 0; i < vX_B.size(); i++)
    {
        veX_B.push_back(SqrtSquareSum(eX, offseteX));
        vX_B.at(i) += offsetX;
    }

    vX_b = vX_B;
    veX_b = veX_B;

    // ROOT Variables
    TCanvas *c1 = new TCanvas("c1", "c1", 1);
    TMultiGraph *mg = new TMultiGraph();

    TGraphErrors *grB = new TGraphErrors(vX_B.size(), &vX_B[0], &vB_B[0],
                                         &veX_B[0], &veB_B[0]);

    TGraphErrors *grb = new TGraphErrors(vX_B.size(), &vX_b[0], &vB_b[0],
                                         &veX_b[0], &veB_b[0]);

    TF1 * funcB = new TF1("fB", "[0] + [1] / (x * x)", 0, 10);
    TF1 * funcb = new TF1("fb", "[0] + [1] / (x * x)", 0, 10);

    funcB->SetParNames("q_{B}", "a_{B}");
    funcb->SetParNames("q_{b}", "a_{b}");

    grB->SetMarkerStyle(20);
    grB->SetMarkerColor(kRed);
    grB->SetMarkerSize(0.7);
    grb->SetMarkerStyle(21);
    grb->SetMarkerColor(kGreen);
    grb->SetMarkerSize(0.7);

    // Draw the graph
    grB->Fit(funcB);
    grb->Fit(funcb);

    mg->Add(grB);
    mg->Add(grb);
    mg->Draw("AP");
    mg->SetTitle("#vec{B} as function of distance, fit model = q + a / x^{2};Distance [cm];#vec{B} [mT]");

    TLegend * legend = drawLegend(grB, grb);
}