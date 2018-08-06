#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "TH1.h"
#include "TFile.h"

void make_MC_bkg_hists_cut025() {

  ///// Create ROOT file to save histograms to /////
  TFile f("HistRootFiles/MC_Background_hists_mu_ele_cut025.root", "RECREATE") ;
  f.cd() ;
  f.mkdir("muon/") ;
  f.mkdir("electron/") ;

  ///// Access tree files /////
  TFile* mufile = new TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_mu.root") ;
  TFile* elefile = new TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_ele.root") ;

  /// Get the muon tree branches ///
  TTree* tree_mu = (TTree*)mufile->Get("minitree_background") ;
  Double_t gamma_eT_mu,pi_pT_mu,lep_pT_mu,piRelIso_05_ch_mu,MET_mu,weight_mu,BDT_output_mu ;
  Int_t nBjets_25_mu ;
  tree_mu->SetBranchAddress("gamma_eT",&gamma_eT_mu) ;
  tree_mu->SetBranchAddress("pi_pT",&pi_pT_mu) ;
  tree_mu->SetBranchAddress("lep_pT",&lep_pT_mu) ;
  tree_mu->SetBranchAddress("nBjets_25",&nBjets_25_mu) ;
  tree_mu->SetBranchAddress("piRelIso_05_ch",&piRelIso_05_ch_mu) ;
  tree_mu->SetBranchAddress("MET",&MET_mu) ;
  tree_mu->SetBranchAddress("weight",&weight_mu) ;
  tree_mu->SetBranchAddress("BDT_output",&BDT_output_mu) ;

  /// Make histograms for variables for muon channel ///
  TH1D* hgamma_eT_mu = new TH1D("hgamma_eT_mu","gamma_eT",30,20,200) ;
  TH1D* hpi_pT_mu = new TH1D("hpi_pT_mu","pi_pT",30,20,200) ;
  TH1D* hlep_pT_mu = new TH1D("hlep_pT_mu","lep_pT",30,20,400) ;
  TH1D* hnBjets_25_mu = new TH1D("hnBjets_25_mu","nBjets_25",9,0,9) ;
  TH1D* hpiRelIso_05_ch_mu = new TH1D("hpiRelIso_05_ch_mu","piRelIso_05_ch",30,0,2) ;
  TH1D* hMET_mu = new TH1D("hMET_mu", "MET",30,0,400) ;

  for (Long64_t i=0,N=tree_mu->GetEntries();i<N;++i) {
    tree_mu->GetEntry(i) ;
    if (BDT_output_mu >= 0.25) {
      hgamma_eT_mu->Fill(gamma_eT_mu,weight_mu) ;
      hpi_pT_mu->Fill(pi_pT_mu,weight_mu) ;
      hlep_pT_mu->Fill(lep_pT_mu,weight_mu) ;
      hnBjets_25_mu->Fill(nBjets_25_mu,weight_mu) ;
      hpiRelIso_05_ch_mu->Fill(piRelIso_05_ch_mu,weight_mu) ;
      hMET_mu->Fill(MET_mu,weight_mu) ; 
    }
  }
  
  /// Save muon channel histograms to the file ///  
  f.cd("muon/") ;
  hgamma_eT_mu->Write() ;
  hpi_pT_mu->Write() ;
  hlep_pT_mu->Write() ;
  hnBjets_25_mu->Write() ;
  hpiRelIso_05_ch_mu->Write() ;
  hMET_mu->Write() ;

  /// Get the electron tree branches ///
  TTree* tree_ele = (TTree*)elefile->Get("minitree_background") ;
  Double_t gamma_eT_ele,pi_pT_ele,lep_pT_ele,piRelIso_05_ch_ele,MET_ele,weight_ele,BDT_output_ele ;
  Int_t nBjets_25_ele ;
  tree_ele->SetBranchAddress("gamma_eT",&gamma_eT_ele) ;
  tree_ele->SetBranchAddress("pi_pT",&pi_pT_ele) ;
  tree_ele->SetBranchAddress("lep_pT",&lep_pT_ele) ;
  tree_ele->SetBranchAddress("nBjets_25",&nBjets_25_ele) ;
  tree_ele->SetBranchAddress("piRelIso_05_ch",&piRelIso_05_ch_ele) ;
  tree_ele->SetBranchAddress("MET",&MET_ele) ;
  tree_ele->SetBranchAddress("weight",&weight_ele) ;
  tree_ele->SetBranchAddress("BDT_output",&BDT_output_ele) ;

  /// Make histograms for variables for electron channel ///
  TH1D* hgamma_eT_ele = new TH1D("hgamma_eT_ele","gamma_eT",30,20,200) ;
  TH1D* hpi_pT_ele = new TH1D("hpi_pT_ele","pi_pT",30,20,200) ;
  TH1D* hlep_pT_ele = new TH1D("hlep_pT_ele","lep_pT",30,20,340) ;
  TH1D* hnBjets_25_ele = new TH1D("hnBjets_25_ele","nBjets_25",8,0,8) ;
  TH1D* hpiRelIso_05_ch_ele = new TH1D("hpiRelIso_05_ch_ele","piRelIso_05_ch",30,0,2) ;
  TH1D* hMET_ele = new TH1D("hMET_ele", "MET",30,0,300) ;

  for (Long64_t j=0,M=tree_ele->GetEntries();j<M;++j) {
    tree_ele->GetEntry(j) ;
    if (BDT_output_ele >= 0.25) {
      hgamma_eT_ele->Fill(gamma_eT_ele,weight_ele) ;
      hpi_pT_ele->Fill(pi_pT_ele,weight_ele) ;
      hlep_pT_ele->Fill(lep_pT_ele,weight_ele) ;
      hnBjets_25_ele->Fill(nBjets_25_ele,weight_ele) ;
      hpiRelIso_05_ch_ele->Fill(piRelIso_05_ch_ele,weight_ele) ;
      hMET_ele->Fill(MET_ele,weight_ele) ;
    }
  }

  /// Save the electron channel histograms to the file ///
  f.cd("electron/") ;
  hgamma_eT_ele->Write() ;
  hpi_pT_ele->Write() ;
  hlep_pT_ele->Write() ;
  hnBjets_25_ele->Write() ;
  hpiRelIso_05_ch_ele->Write() ;
  hMET_ele->Write() ;
  
}

