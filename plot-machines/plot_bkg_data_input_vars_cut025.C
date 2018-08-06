// Makes weighted background plots for input variables
// Superimposes hists from data with input vars
// Features:
// 	*- No stat box
// 	*- Red dashed line style
// 	*- Canvas size 200,106,600,600
//	*- Background magnified by factor 100
//	*- Restrict pT and eT range between 20 and 100 GeV
//	*- Write variable name and unit on x axis
//	*- Put legend that dashed line = 100xBackground
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"
#include "THStack.h"
#include "TAxis.h"

void plot_bkg_data_input_vars_cut025() {
  /// Get the file with all the weighted MC Background hists ///
  TFile* fMC = new TFile("HistRootFiles/MC_Background_hists_mu_ele_cut025.root") ; // For No_cut
  /// Get the muon hists ///
  TH1D* hgamma_eT_mu = (TH1D*)fMC->Get("muon/hgamma_eT_mu") ;
  TH1D* hpi_pT_mu = (TH1D*)fMC->Get("muon/hpi_pT_mu") ;
  TH1D* hlep_pT_mu = (TH1D*)fMC->Get("muon/hlep_pT_mu") ;
  TH1D* hnBjets_25_mu = (TH1D*)fMC->Get("muon/hnBjets_25_mu") ;
  TH1D* hpiRelIso_05_ch_mu = (TH1D*)fMC->Get("muon/hpiRelIso_05_ch_mu") ;
  TH1D* hMET_mu = (TH1D*)fMC->Get("muon/hMET_mu") ;

  /// Get the electron hists ///
  TH1D* hgamma_eT_ele = (TH1D*)fMC->Get("electron/hgamma_eT_ele") ;
  TH1D* hpi_pT_ele = (TH1D*)fMC->Get("electron/hpi_pT_ele") ;
  TH1D* hlep_pT_ele = (TH1D*)fMC->Get("electron/hlep_pT_ele") ;
  TH1D* hnBjets_25_ele = (TH1D*)fMC->Get("electron/hnBjets_25_ele") ;
  TH1D* hpiRelIso_05_ch_ele = (TH1D*)fMC->Get("electron/hpiRelIso_05_ch_ele") ;
  TH1D* hMET_ele = (TH1D*)fMC->Get("electron/hMET_ele") ;

  /// Get the file with all data hists ///
  TFile* fDATA = new TFile("HistRootFiles/Data_hists_mu_ele_cut025.root") ;

  /// Get the muon hists ///
  TH1D* dgamma_eT_mu = (TH1D*)fDATA->Get("muon/dgamma_eT_mu") ;
  TH1D* dpi_pT_mu = (TH1D*)fDATA->Get("muon/dpi_pT_mu") ;
  TH1D* dlep_pT_mu = (TH1D*)fDATA->Get("muon/dlep_pT_mu") ;
  TH1D* dnBjets_25_mu = (TH1D*)fDATA->Get("muon/dnBjets_25_mu") ;
  TH1D* dpiRelIso_05_ch_mu = (TH1D*)fDATA->Get("muon/dpiRelIso_05_ch_mu") ;
  TH1D* dMET_mu = (TH1D*)fDATA->Get("muon/dMET_mu") ;

  /// Get the electron hists ///
  TH1D* dgamma_eT_ele = (TH1D*)fDATA->Get("electron/dgamma_eT_ele") ;
  TH1D* dpi_pT_ele = (TH1D*)fDATA->Get("electron/dpi_pT_ele") ;
  TH1D* dlep_pT_ele = (TH1D*)fDATA->Get("electron/dlep_pT_ele") ;
  TH1D* dnBjets_25_ele = (TH1D*)fDATA->Get("electron/dnBjets_25_ele") ;
  TH1D* dpiRelIso_05_ch_ele = (TH1D*)fDATA->Get("electron/dpiRelIso_05_ch_ele") ;
  TH1D* dMET_ele = (TH1D*)fDATA->Get("electron/dMET_ele") ;

  /// Make a single canvas from which each plot will be saved as a PDF file ///
  TCanvas* c = new TCanvas("c","c",200,106,600,600) ;
  gStyle->SetOptStat(0) ;
  gStyle->SetOptTitle(kFALSE) ;
  THStack* hs = new THStack() ;
  
  /// Make a legend to clear after each is drawn and saved ///
  auto legend = new TLegend(0.6,0.74,0.86,0.87) ;
  legend->SetBorderSize(0) ;

  /// Plot and save Muon channel, cut=0.25 plots ///
  hgamma_eT_mu->SetLineColor(kRed) ;
  hgamma_eT_mu->SetLineStyle(kDashed) ;
  legend->AddEntry(hgamma_eT_mu,"Background","f") ;
  hs->Add(hgamma_eT_mu,"HIST") ;
  ////
  dgamma_eT_mu->SetLineColor(kBlue) ;
  legend->AddEntry(dgamma_eT_mu,"Data","f") ;
  hs->Add(dgamma_eT_mu) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,200) ;
  hs->GetXaxis()->SetTitle("E_{T}^{#gamma}(GeV)") ;
  legend->SetHeader("Muon channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf(","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hpi_pT_mu->SetLineColor(kRed) ;
  hpi_pT_mu->SetLineStyle(kDashed) ;
  legend->AddEntry(hpi_pT_mu,"Background","f") ;
  hs->Add(hpi_pT_mu,"HIST") ;
  ////
  dpi_pT_mu->SetLineColor(kBlue) ;
  legend->AddEntry(dpi_pT_mu,"Data","f") ;
  hs->Add(dpi_pT_mu) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,200) ;
  hs->GetXaxis()->SetTitle("p_{T}^{#pi}(GeV)") ;
  legend->SetHeader("Muon channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hlep_pT_mu->SetLineColor(kRed) ;
  hlep_pT_mu->SetLineStyle(kDashed) ;
  legend->AddEntry(hlep_pT_mu,"Background","f") ;
  hs->Add(hlep_pT_mu,"HIST") ;
  ////
  dlep_pT_mu->SetLineColor(kBlue) ;
  legend->AddEntry(dlep_pT_mu,"Data","f") ;
  hs->Add(dlep_pT_mu) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,400) ;
  hs->GetXaxis()->SetTitle("p_{T}^{#mu}(GeV)") ;
  legend->SetHeader("Muon channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ; 
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hnBjets_25_mu->SetLineColor(kRed) ;
  hnBjets_25_mu->SetLineStyle(kDashed) ;
  legend->AddEntry(hnBjets_25_mu,"Background","f") ;
  hs->Add(hnBjets_25_mu,"HIST") ;
  ////
  dnBjets_25_mu->SetLineColor(kBlue) ;
  legend->AddEntry(dnBjets_25_mu,"Data","f") ;
  hs->Add(dnBjets_25_mu) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,9) ;
  hs->GetXaxis()->SetTitle("N_{Bjets}") ;
  legend->SetHeader("Muon channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hpiRelIso_05_ch_mu->SetLineColor(kRed) ;
  hpiRelIso_05_ch_mu->SetLineStyle(kDashed) ;
  legend->AddEntry(hpiRelIso_05_ch_mu,"Background","f") ;
  hs->Add(hpiRelIso_05_ch_mu,"HIST") ;
  ////
  dpiRelIso_05_ch_mu->SetLineColor(kBlue) ;
  legend->AddEntry(dpiRelIso_05_ch_mu,"Data","f") ;
  hs->Add(dpiRelIso_05_ch_mu) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,1) ;
  hs->GetXaxis()->SetTitle("#Sigmap_{T}/p_{T}^{#pi}") ;
  legend->SetHeader("Muon channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hMET_mu->SetLineColor(kRed) ;
  hMET_mu->SetLineStyle(kDashed) ;
  legend->AddEntry(hMET_mu,"Background","f") ;
  hs->Add(hMET_mu,"HIST") ;
  ////
  dMET_mu->SetLineColor(kBlue) ;
  legend->AddEntry(dMET_mu,"Data","f") ;
  hs->Add(dMET_mu) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,400) ;
  hs->GetXaxis()->SetTitle("ME_{T}(GeV)") ;
  legend->SetHeader("Muon channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  /// Plot and save Electron channel, cut=0.25 plots ///
  hgamma_eT_ele->SetLineColor(kRed) ;
  hgamma_eT_ele->SetLineStyle(kDashed) ;
  legend->AddEntry(hgamma_eT_ele,"Background","f") ;
  hs->Add(hgamma_eT_ele,"HIST") ;
  ////
  dgamma_eT_ele->SetLineColor(kBlue) ;
  legend->AddEntry(dgamma_eT_ele,"Data","f") ;
  hs->Add(dgamma_eT_ele) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,200) ;
  hs->GetXaxis()->SetTitle("E_{T}^{#gamma}(GeV)") ;
  legend->SetHeader("Electron channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hpi_pT_ele->SetLineColor(kRed) ;
  hpi_pT_ele->SetLineStyle(kDashed) ;
  legend->AddEntry(hpi_pT_ele,"Background","f") ;
  hs->Add(hpi_pT_ele,"HIST") ;
  ////
  dpi_pT_ele->SetLineColor(kBlue) ;
  legend->AddEntry(dpi_pT_ele,"Data","f") ;
  hs->Add(dpi_pT_ele) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,200) ;
  hs->GetXaxis()->SetTitle("p_{T}^{#pi}(GeV)") ;
  legend->SetHeader("Electron channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hlep_pT_ele->SetLineColor(kRed) ;
  hlep_pT_ele->SetLineStyle(kDashed) ;
  legend->AddEntry(hlep_pT_ele,"Background","f") ;
  hs->Add(hlep_pT_ele,"HIST") ;
  ////
  dlep_pT_ele->SetLineColor(kBlue) ;
  legend->AddEntry(dlep_pT_ele,"Data","f") ;
  hs->Add(dlep_pT_ele) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,340) ;
  hs->GetXaxis()->SetTitle("p_{T}^{e}(GeV)") ;
  legend->SetHeader("Electron channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hnBjets_25_ele->SetLineColor(kRed) ;
  hnBjets_25_ele->SetLineStyle(kDashed) ;
  legend->AddEntry(hnBjets_25_ele,"Background","f") ;
  hs->Add(hnBjets_25_ele,"HIST") ;
  ////
  dnBjets_25_ele->SetLineColor(kBlue) ;
  legend->AddEntry(dnBjets_25_ele,"Data","f") ;
  hs->Add(dnBjets_25_ele) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,8) ;
  hs->GetXaxis()->SetTitle("N_{Bjets}") ;
  legend->SetHeader("Electron channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hpiRelIso_05_ch_ele->SetLineColor(kRed) ;
  hpiRelIso_05_ch_ele->SetLineStyle(kDashed) ;
  legend->AddEntry(hpiRelIso_05_ch_ele,"Background","f") ;
  hs->Add(hpiRelIso_05_ch_ele,"HIST") ;
  ////
  dpiRelIso_05_ch_ele->SetLineColor(kBlue) ;
  legend->AddEntry(dpiRelIso_05_ch_ele,"Data","f") ;
  hs->Add(dpiRelIso_05_ch_ele) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,1) ;
  hs->GetXaxis()->SetTitle("#Sigmap_{T}/p_{T}^{#pi}") ;
  legend->SetHeader("Electron channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;

  hMET_ele->SetLineColor(kRed) ;
  hMET_ele->SetLineStyle(kDashed) ;
  legend->AddEntry(hMET_ele,"Background","f") ;
  hs->Add(hMET_ele,"HIST") ;
  ////
  dMET_ele->SetLineColor(kBlue) ;
  legend->AddEntry(dMET_ele,"Data","f") ;
  hs->Add(dMET_ele) ;
  ////
  hs->Draw("NOSTACK") ;
  hs->GetXaxis()->SetLimits(0,300) ;
  hs->GetXaxis()->SetTitle("ME_{T}(GeV)") ;
  legend->SetHeader("Electron channel, cut=0.25") ;
  legend->Draw() ;
  c->Update() ;
  c->Print("Input_var_pdfs/Input_vars_bkg_data_cut025.pdf)","pdf") ;
  c->Clear() ;
  legend->Clear() ;
  hs->GetHists()->Clear() ;
}
