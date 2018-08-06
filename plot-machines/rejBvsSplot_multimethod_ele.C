// Plots the backround rejection vs. signal efficiency for BDT, MLP, and PDE for ele sample

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooPlot.h"
#include "TCanvas.h"
#include "TH1.h"
#include <iostream>

void rejBvsSplot_multimethod_ele() {

  TCanvas* c = new TCanvas("c","c",900,675) ;
  c->SetTitle("ROC plot ele 4 methods") ;
  c->Update() ;

  // // ROC plot // //
  THStack* hall = new THStack("hall","ROC plots for BDT, MLP, PDE, and kNN methods, electron sample") ;
 
  TFile* file = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/MultiMethodPlot/NewNtuples31718/BDT_training_ele.root") ;
  TH1D* h = (TH1D*)file->Get("Method_BDT/BDT/MVA_BDT_rejBvsS") ;
  gStyle->SetOptStat(0) ;
  h->SetLineColor(8) ;
  h->SetTitle("BDT") ;
  h->SetLineWidth(2) ; 
  hall->Add(h) ;

  TFile* file1 = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/MultiMethodPlot/NewNtuples31718/MLP_training_ele.root") ;
  TH1D* h1 = (TH1D*)file1->Get("Method_MLP/MLP/MVA_MLP_rejBvsS") ;
  h1->SetLineColor(4) ;
  h1->SetTitle("MLP") ;
  h1->SetLineWidth(2) ;
  hall->Add(h1) ;

  TFile* file2 = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/MultiMethodPlot/NewNtuples31718/PDE_training_ele.root") ;
  TH1D* h2 = (TH1D*)file2->Get("Method_Likelihood/Likelihood/MVA_Likelihood_rejBvsS") ;
  h2->SetLineColor(2) ;
  h2->SetTitle("PDE") ;
  h2->SetLineWidth(2) ;
  hall->Add(h2) ;

  TFile* file3 = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/MultiMethodPlot/NewNtuples31718/kNN_training_ele.root") ;
  TH1D* h3 = (TH1D*)file3->Get("Method_KNN/KNN/MVA_KNN_rejBvsS") ;
  h3->SetLineColor(6) ;
  h3->SetTitle("kNN") ;
  h3->SetLineWidth(2) ;
  hall->Add(h3) ;
 
  hall->Draw("c nostack") ;
  gPad->BuildLegend(0.15,0.2,0.3,0.35) ;
  c->Update() ;
  c->Print("Plots/ROCplot_multimethod_ele.pdf") ;
}
