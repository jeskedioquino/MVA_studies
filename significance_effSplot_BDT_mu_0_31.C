// Plots significance (S/sqrt(S+B))

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooPlot.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TGraph.h"
#include <cmath>
#include <iostream>

void significance_effSplot_BDT_mu_0_31() 
{

  /* Set the weighted number of signal and background events for the mu sample */
  Double_t nS = 14.2 ;
  Double_t nB = 85886.56 ;

  /********************* Make the canvas *************************/
  TCanvas* c = new TCanvas("c","c",900,675) ;
  c->SetTitle("Significance vs. Signal efficiency, BDT method, muon sample") ;
  c->Update() ;
  auto legend = new TLegend(0.5,0.7,0.9,0.9) ;
  legend->SetHeader("Significance vs. Signal efficiency, BDT, muon") ; 
 
  /****** Get plot of effB vs effS from ROOT file as graph *******/
  TFile* file31 = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/MultiMethodPlot/NewNtuples31718/BDT_training_mu.root") ;
  TGraph* g_BS31 = new TGraph((TH1D*)file31->Get("Method_BDT/BDT/MVA_BDT_effBvsS")) ;

  /*********** Get the points from effBvsS into arrays ***********/
  /**** Use these to calculate the points for the final graph ****/
  int N = g_BS31->GetN() ;
  Double_t x_BS31[N], y_BS31[N] ;
  Double_t x31[N], S31[N], B31[N], sig31[N] ;
  int returnVal = 0 ;
  int i = 0 ;
  for (i=0;i<N;i++) 
  {
    returnVal=g_BS31->GetPoint(i,x_BS31[i],y_BS31[i]) ;
  
    x31[i] = x_BS31[i] ;
    S31[i] = nS * x_BS31[i] ;
    B31[i] = nB * y_BS31[i] ;

    sig31[i] = S31[i]/sqrt(S31[i]+B31[i]) ; 
  }
  
  /************* Make graph plotting sig[] vs x[] **************/
  TGraph* g_sig31 = new TGraph(N,x31,sig31) ;
  g_sig31->SetLineColor(kBlue) ;
  g_sig31->SetLineWidth(2) ;
  g_sig31->SetTitle("Significance vs. Signal efficiency, BDT method, muon sample;effS;Significance") ;
  
  gPad->SetGrid() ;
  g_sig31->Draw("AC") ;
  legend->AddEntry(g_sig31,"New Ntuples (31/7/18)","l") ;
  c->Update() ;
  //TF1 fit("fit","pol6") ;
  //g_sig31->Fit(&fit) ;
  
  TFile* file0 = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/MultiMethodPlot/OriginalNtuples/BDT_training_mu.root") ;
  TGraph* g_BS0 = new TGraph((TH1D*)file0->Get("Method_BDT/BDT/MVA_BDT_effBvsS")) ;

  N = g_BS0->GetN() ;
  Double_t x_BS0[N], y_BS0[N] ;
  Double_t x0[N], S0[N], B0[N], sig0[N] ;
  returnVal = 0 ; 
  for (i=0;i<N;i++) 
  {
    returnVal=g_BS0->GetPoint(i,x_BS0[i],y_BS0[i]) ;

    x0[i] = x_BS0[i] ;
    S0[i] = nS * x_BS0[i] ;
    B0[i] = nB * y_BS0[i] ;

    sig0[i] = S0[i]/sqrt(S0[i]+B0[i]) ;
  }

  TGraph* g_sig0 = new TGraph(N,x0,sig0) ;
  g_sig0->SetLineColor(kRed) ;
  g_sig0->SetLineWidth(2) ;
  g_sig0->SetTitle("Significance vs. Signal efficiency, BDT method, muon sample;effS;Significance") ;

  gPad->SetGrid() ;
  g_sig0->Draw("SAME C") ;
  legend->AddEntry(g_sig0,"Old Ntuples","l") ;
  
  legend->Draw() ;
  c->Update() ;
  c->Print("Plots/significance_effS_BDT_mu_0_31.pdf") ;
}
  
