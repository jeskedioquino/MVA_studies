#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "TH1.h"
#include "TFile.h"

#include <iostream>

void relisolation_pipt_2dhists() {

  /// Get ROOT files with trees ///
  TFile* sigtreefilemu = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Signal_mu.root") ;
  TFile* bkgtreefilemu = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Background_mu.root") ;
  TFile* sigtreefileele = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Signal_ele.root") ;
  TFile* bkgtreefileele = TFile::Open("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Background_ele.root") ;
  
  /// Make TH2D for signal/background and mu/ele, get hists for pireliso and pipt in each channel ///
  TH2D* isolation_pipt_sig_mu = new TH2D("isolation_pipt_sig_mu","#Sigmap_{T}/p_{T}^{#pi} and p_{T}^{#pi} signal, muon channel;p_{T}^{#pi}(GeV);#Sigmap_{T}/p_{T}^{#pi}",50,20.,150.,50,0.,2) ;
  TH2D* isolation_pipt_bkg_mu = new TH2D("isolation_pipt_bkg_mu","#Sigmap_{T}/p_{T}^{#pi} and p_{T}^{#pi} background, muon channel;p_{T}^{#pi}(GeV);#Sigmap_{T}/p_{T}^{#pi}",50,20.,150.,50,0.,5) ;
  TH2D* isolation_pipt_sig_ele = new TH2D("isolation_pipt_sig_ele","#Sigmap_{T}/p_{T}^{#pi} and p_{T}^{#pi} signal, electron channel;p_{T}^{#pi}(GeV);#Sigmap_{T}/p_{T}^{#pi}",50,20.,150.,50,0.,1.2) ;
  TH2D* isolation_pipt_bkg_ele = new TH2D("isolation_pipt_bkg_ele","#Sigmap_{T}/p_{T}^{#pi} and p_{T}^{#pi} background, electron channel;p_{T}^{#pi}(GeV);#Sigmap_{T}/p_{T}^{#pi}",50,20.,150.,50,0.,5) ;

  /// Get the trees ///
  TTree* tsig_mu = (TTree*)sigtreefilemu->Get("minitree_signal_mu") ;
  TTree* tbkg_mu = (TTree*)bkgtreefilemu->Get("minitree_background_mu") ;
  TTree* tsig_ele = (TTree*)sigtreefileele->Get("minitree_signal_ele") ;
  TTree* tbkg_ele = (TTree*)bkgtreefileele->Get("minitree_background_ele") ;

  Double_t piRelIso_05_ch_sig_mu,piRelIso_05_ch_bkg_mu,piRelIso_05_ch_sig_ele,piRelIso_05_ch_bkg_ele,pi_pT_sig_mu,pi_pT_bkg_mu,pi_pT_sig_ele,pi_pT_bkg_ele,weight_sig_mu,weight_bkg_mu,weight_sig_ele,weight_bkg_ele ;

  tsig_mu->SetBranchAddress("piRelIso_05_ch",&piRelIso_05_ch_sig_mu) ;
  tsig_mu->SetBranchAddress("pi_pT",&pi_pT_sig_mu) ;
  tsig_mu->SetBranchAddress("weight",&weight_sig_mu) ;
  tbkg_mu->SetBranchAddress("piRelIso_05_ch",&piRelIso_05_ch_bkg_mu) ;
  tbkg_mu->SetBranchAddress("pi_pT",&pi_pT_bkg_mu) ;
  tbkg_mu->SetBranchAddress("weight",&weight_bkg_mu) ;
  tsig_ele->SetBranchAddress("piRelIso_05_ch",&piRelIso_05_ch_sig_ele) ;
  tsig_ele->SetBranchAddress("pi_pT",&pi_pT_sig_ele) ;
  tsig_ele->SetBranchAddress("weight",&weight_sig_ele) ;
  tbkg_ele->SetBranchAddress("piRelIso_05_ch",&piRelIso_05_ch_bkg_ele) ;
  tbkg_ele->SetBranchAddress("pi_pT",&pi_pT_bkg_ele) ;
  tbkg_ele->SetBranchAddress("weight",&weight_bkg_ele) ;

  /// Fill TH2D entries with tree entries ///
  Long64_t i,N;
 
  N=tsig_mu->GetEntries() ;
  for(i=0;i<N;i++) {
    tsig_mu->GetEntry(i) ;
    isolation_pipt_sig_mu->Fill(pi_pT_sig_mu,piRelIso_05_ch_sig_mu,weight_sig_mu) ;
  }
  N=tbkg_mu->GetEntries() ;
  for(i=0;i<N;i++) {
    tbkg_mu->GetEntry(i) ;
    isolation_pipt_bkg_mu->Fill(pi_pT_bkg_mu,piRelIso_05_ch_bkg_mu,weight_bkg_mu) ;
  }
  N=tsig_ele->GetEntries() ;
  for(i=0;i<N;i++) {
    tsig_ele->GetEntry(i) ;
    isolation_pipt_sig_ele->Fill(pi_pT_sig_ele,piRelIso_05_ch_sig_ele,weight_sig_ele) ;
  }
  N=tbkg_ele->GetEntries() ;
  for(i=0;i<N;i++) {
    tbkg_ele->GetEntry(i) ;
    isolation_pipt_bkg_ele->Fill(pi_pT_bkg_ele,piRelIso_05_ch_bkg_ele,weight_bkg_ele) ;
  }

  /// Create canvases split into 2 columns to draw the  hists ///
  TCanvas* c1 = new TCanvas("c1","Muon",1000,500) ;
  c1->Divide(2) ;
  c1->cd(1) ;
  gStyle->SetOptStat(0) ;
  isolation_pipt_sig_mu->Draw("BOX") ;
  c1->cd(2) ;
  isolation_pipt_bkg_mu->Draw("BOX") ;
  c1->Update() ;
  c1->Print("Isolation_pipt_pdfs/piRelIso_pT_2dhists.pdf(","pdf") ;

  TCanvas* c2 = new TCanvas("c2","Electron",1000,500) ;
  c2->Divide(2) ;
  c2->cd(1) ;
  isolation_pipt_sig_ele->Draw("BOX") ;
  c2->cd(2) ;
  isolation_pipt_bkg_ele->Draw("BOX") ;
  c2->Update() ;
  c2->Print("Isolation_pipt_pdfs/piRelIso_pT_2dhists.pdf)","pdf") ;
} 
