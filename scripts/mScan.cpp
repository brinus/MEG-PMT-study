#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

void mScan(){
    gStyle->SetOptStat(0);

    std::vector<TH1 *> vHist;
    std::string fName = "../scanPOT.";
    std::string fType = ".root";
    std::vector<std::string> vVals = {"302", "352", "406", "444",
                                      "497", "546", "606", "648",
                                      "717"};

    TH1 * h1 = new TH1F();
    TFile * f = new TFile();
    TTree * t = new TTree();

    for (std::string vals : vVals){
        f = new TFile((fName + vals + fType).c_str()); 
        t = (TTree *)f->Get("T");
        t->Draw("area >> hArea");
        h1 = (TH1F *)gDirectory->Get("hArea");
        vHist.push_back(h1);
    }

    TCanvas * c1 = new TCanvas("c1", "c1", 1);

    TLegend * legend = new TLegend(0.65, 0.7, 0.85, 0.85, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(22);
    legend->SetFillColorAlpha(0,0.0);

    for (Int_t i = 0; i < vHist.size(); i++){
        vHist[i]->Draw("same");
        vHist[i]->SetLineColor(i+2);
        legend->AddEntry(vHist[i], ("R_{POT} [#Omega] =  " + vVals[i]).c_str(), "PLF");
    }

    vHist[0]->SetTitle("Energy spectrum as a function of HV, entries = 1000; E [a.u.]; occurencies");

    legend->Draw();
}