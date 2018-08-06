// Plots signal/background hists together from BDT output, for both muon and electron channels 

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooPlot.h"
#include "TCanvas.h"
#include "TH1.h"
#include <iostream>

void BDT_output_sigbkghists() {

  TCanvas* c1 = new TCanvas("c1","c1",675,675) ;
  c1->SetTitle("BDT output, muon channel") ;
  c1->Update() ;

  TCanvas* c2 = new TCanvas("c2","c2",675,675) ;
  c2->SetTitle("BDT output, electron channel") ;
  c2->Update() ;
  
  // Get TTree files
  TFile* fBDT_mu = new TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_mu.root") ;
  TFile* fBDT_ele = new TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_ele.root") ;

  // Get tree branches for BDT_output
  TTree* tsig_mu = (TTree*)fBDT_mu->Get("minitree_signal") ;
  TTree* tsig_ele = (TTree*)fBDT_ele->Get("minitree_signal") ;
  TTree* tbkg_mu = (TTree*)fBDT_mu->Get("minitree_background") ;
  TTree* tbkg_ele = (TTree*)fBDT_ele->Get("minitree_background") ;
   
  Double_t BDT_output_sig_mu, BDT_output_bkg_mu, BDT_output_sig_ele, BDT_output_bkg_ele ;
  tsig_mu->SetBranchAddress("BDT_output",&BDT_output_sig_mu) ;
  tbkg_mu->SetBranchAddress("BDT_output",&BDT_output_bkg_mu) ;
  tsig_ele->SetBranchAddress("BDT_output",&BDT_output_sig_ele) ;
  tbkg_ele->SetBranchAddress("BDT_output",&BDT_output_bkg_ele) ;

  Double_t weight_sig_mu, weight_bkg_mu, weight_sig_ele, weight_bkg_ele ;
  tsig_mu->SetBranchAddress("weight",&weight_sig_mu) ;
  tbkg_mu->SetBranchAddress("weight",&weight_bkg_mu) ;
  tsig_ele->SetBranchAddress("weight",&weight_sig_ele) ;
  tbkg_ele->SetBranchAddress("weight",&weight_bkg_ele) ;

  Long64_t i,N; // For the loops for filling hists

  // Make stacks that group sig and bkg hists together
  THStack* hall1 = new THStack("hall1","BDT output, muon channel") ;
  THStack* hall2 = new THStack("hall2","BDT output, electron channel") ;

  // For muon channel
  c1->cd() ;  

  TH1D* h11 = new TH1D("h11","Signal",100,-0.64,0.92) ; 
  Double_t norm = 1.0 ;
   
  N=tsig_mu->GetEntries() ;
  for (i=0;i<N;i++) {
    tsig_mu->GetEntry(i) ;
    h11->Fill(BDT_output_sig_mu,weight_sig_mu) ;
  }
  gStyle->SetOptStat(0) ;
  h11->SetLineColor(4) ;
  h11->SetFillColor(4) ;
  h11->SetFillStyle(3004) ;
  h11->SetLineWidth(2) ; 
  h11->Scale(norm/h11->Integral()) ;
  hall1->Add(h11,"hist") ;
  TH1D* h12 = new TH1D("h12","Background",100,-0.86,0.92) ;
  N=tbkg_mu->GetEntries() ;
  for (i=0;i<N;i++) {
    tbkg_mu->GetEntry(i) ;
    h12->Fill(BDT_output_bkg_mu,weight_bkg_mu) ;
  }
  h12->SetLineColor(2) ;
  h12->SetFillColor(2) ;
  h12->SetFillStyle(3005) ;
  h12->SetLineWidth(2) ;
  h12->Scale(norm/h12->Integral()) ;
  hall1->Add(h12,"hist") ;

  // For electron channel
  TH1D* h21 = new TH1D("h21","Signal",100,-0.5,0.74) ;
  N=tsig_ele->GetEntries() ;
  for (i=0;i<N;i++) {
    tsig_ele->GetEntry(i) ;
    h21->Fill(BDT_output_sig_ele,weight_sig_ele) ;
  }
  gStyle->SetOptStat(0) ;
  h21->SetLineColor(4) ;
  h21->SetFillColor(4) ;
  h21->SetFillStyle(3004) ;
  h21->SetLineWidth(2) ;
  h21->Scale(norm/h21->Integral()) ;
  hall2->Add(h21,"hist") ;
  TH1D* h22 = new TH1D("h22","Background",100,-0.76,0.7) ;
  N=tbkg_ele->GetEntries() ;
  for (i=0;i<N;i++) {
    tbkg_ele->GetEntry(i) ;
    h22->Fill(BDT_output_bkg_ele,weight_bkg_ele) ;
  }
  h22->SetLineColor(2) ;
  h22->SetFillColor(2) ;
  h22->SetFillStyle(3005) ;
  h22->SetLineWidth(2) ;
  h22->Scale(norm/h22->Integral()) ;
  hall2->Add(h22,"hist") ;

  c1->cd() ;
  hall1->Draw("nostack") ;
  gPad->BuildLegend() ;
  c1->Update() ;
  c1->Print("Plots/BDT_output_sigbkghists.pdf(","pdf") ;  

  c2->cd() ;
  hall2->Draw("nostack") ;
  gPad->BuildLegend() ;
  c2->Update() ;
  c2->Print("Plots/BDT_output_sigbkghists.pdf)","pdf") ;
}
