// Plots the backround rejection vs. signal efficiency for BDT for muon and electron channels

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooPlot.h"
#include "TCanvas.h"
#include "TH1.h"
#include <iostream>

void rejBvsSplot_mu_ele() {

  TCanvas* c1 = new TCanvas("c1","c1",900,675) ;
  c1->SetTitle("ROC plot BDT") ;
  c1->Update() ;
  
  // Make a stack that groups both hists together
  THStack* hall = new THStack("hall1","ROC plot BDT") ;

  // For muon channel
  TFile* filemu = new TFile("Training/outputs/Nominal_training_mu.root") ;
  TH1D* hmu = (TH1D*)filemu->Get("Method_BDT/BDT/MVA_BDT_rejBvsS") ;
  gStyle->SetOptStat(0) ;
  hmu->SetLineColor(2) ;
  hmu->SetTitle("Muon channel") ;
  hmu->SetLineWidth(2) ; 
  hall->Add(hmu) ;

  // For electron channel
  TFile* fileele = new TFile("Training/outputs/Nominal_training_ele.root") ;
  TH1D* hele = (TH1D*)fileele->Get("Method_BDT/BDT/MVA_BDT_rejBvsS") ;
  hele->SetLineColor(8) ;
  hele->SetTitle("Electron channel") ;
  hele->SetLineWidth(2) ;
  hall->Add(hele) ;  

  hall->Draw("c nostack") ;
  gPad->BuildLegend(0.15,0.4,0.4,0.75) ;
  c1->Update() ;
  c1->Print("Plots/ROCplot_mu_ele.pdf") ;
}
