# Takes result from BDT and creates trees from old ones that include this result #

import ROOT
import os
import argparse
import numpy as np
from ROOT import TFile, TTree, TBranch, TCanvas, TH1F
from array import array

#---------------------------------#
p = argparse.ArgumentParser(description='Specify whether the MVA was performed on the muon or the electron sample')
p.add_argument('isMuon_option', help='Type <<muon>> or <<electron>>')
args = p.parse_args()

# Switch from muon to electron channel
if args.isMuon_option == "muon":
  isMuon = True
if args.isMuon_option == "electron":
  isMuon = False
#---------------------------------#

# Get input trees (MC)
if isMuon:
  fIn_bkg = TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Background_mu.root")
  tbkg_in = fIn_bkg.Get("minitree_background_mu")

  fIn_sig = TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Signal_mu.root")
  tsig_in = fIn_sig.Get("minitree_signal_mu")
  
  fOut = TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_mu.root","RECREATE")
else:
  fIn_bkg = TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Background_ele.root")
  tbkg_in = fIn_bkg.Get("minitree_background_ele")

  fIn_sig = TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Signal_ele.root")
  tsig_in = fIn_sig.Get("minitree_signal_ele")

  fOut = TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_ele.root","RECREATE")

# Create arrays for the reader 
pi_pT_array = array("f",[0.])
gamma_eT_array = array("f",[0.])
nBjets_25_array = array("f",[0])
lep_pT_array = array("f",[0.])
piRelIso_05_ch_array = array("f",[0.])
MET_array = array("f",[0.])
weight_array = array("f",[0.])
Wmass_array = array("f",[0.])

# Prepare the reader
reader = ROOT.TMVA.Reader(":".join(["!Color","!Silent"]))

reader.AddVariable("pi_pT",pi_pT_array)
reader.AddVariable("gamma_eT",gamma_eT_array)
reader.AddVariable("nBjets_25",nBjets_25_array)
reader.AddVariable("lep_pT",lep_pT_array)
reader.AddVariable("piRelIso_05_ch",piRelIso_05_ch_array)
reader.AddVariable("MET",MET_array)
#reader.AddVariable("weight",weight_array) 
#reader.AddVariable("Wmass",Wmass_array)

# Create arrays for the input/output trees
_pi_pT = np.zeros(1,dtype=float)
_gamma_eT = np.zeros(1,dtype=float)
_nBjets_25 = np.zeros(1,dtype=int)
_lep_pT = np.zeros(1,dtype=float)
_piRelIso_05_ch = np.zeros(1,dtype=float)
_MET = np.zeros(1,dtype=float)
_BDT_output = np.zeros(1,dtype=float)
_weight = np.zeros(1,dtype=float)
_Wmass = np.zeros(1,dtype=float)

tsig_out = TTree("minitree_signal","tree with branches")
tsig_out.Branch("pi_pT",_pi_pT,"pi_pT/D")
tsig_out.Branch("gamma_eT",_gamma_eT,"gamma_eT/D")
tsig_out.Branch("nBjets_25",_nBjets_25,"nBjets_25/I")
tsig_out.Branch("lep_pT",_lep_pT,"lep_pT/D")
tsig_out.Branch("piRelIso_05_ch",_piRelIso_05_ch,"piRelIso_05_ch/D")
tsig_out.Branch("MET",_MET,"MET/D")
tsig_out.Branch("BDT_output",_BDT_output,"BDT_output/D")
tsig_out.Branch("weight",_weight,"weight/D")
tsig_out.Branch("Wmass",_Wmass,"Wmass/D")

tbkg_out = TTree("minitree_background","tree with branches")
tbkg_out.Branch("pi_pT",_pi_pT,"pi_pT/D")
tbkg_out.Branch("gamma_eT",_gamma_eT,"gamma_eT/D")
tbkg_out.Branch("nBjets_25",_nBjets_25,"nBjets_25/I")
tbkg_out.Branch("lep_pT",_lep_pT,"lep_pT/D")
tbkg_out.Branch("piRelIso_05_ch",_piRelIso_05_ch,"piRelIso_05_ch/D")
tbkg_out.Branch("MET",_MET,"MET/D")
tbkg_out.Branch("BDT_output",_BDT_output,"BDT_output/D")
tbkg_out.Branch("weight",_weight,"weight/D")
tbkg_out.Branch("Wmass",_Wmass,"Wmass/D")

# Event loop
if isMuon:
  reader.BookMVA("BDT_mu","Training/weights/TMVAClassification_BDT.weights_mu.xml")
else:
  reader.BookMVA("BDT_ele","Training/weights/TMVAClassification_BDT.weights_ele.xml")

# Prepare signal input tree
tsig_in.SetBranchAddress("pi_pT",_pi_pT)
tsig_in.SetBranchAddress("gamma_eT",_gamma_eT)
tsig_in.SetBranchAddress("nBjets_25",_nBjets_25)
tsig_in.SetBranchAddress("lep_pT",_lep_pT)
tsig_in.SetBranchAddress("piRelIso_05_ch",_piRelIso_05_ch)
tsig_in.SetBranchAddress("MET",_MET)
tsig_in.SetBranchAddress("weight",_weight)
tsig_in.SetBranchAddress("Wmass",_Wmass)

# Prepare background input tree
tbkg_in.SetBranchAddress("pi_pT",_pi_pT)
tbkg_in.SetBranchAddress("gamma_eT",_gamma_eT)
tbkg_in.SetBranchAddress("nBjets_25",_nBjets_25)
tbkg_in.SetBranchAddress("lep_pT",_lep_pT)
tbkg_in.SetBranchAddress("piRelIso_05_ch",_piRelIso_05_ch)
tbkg_in.SetBranchAddress("MET",_MET)
tbkg_in.SetBranchAddress("weight",_weight)
tbkg_in.SetBranchAddress("Wmass",_Wmass)

# looping through events:
# Signal:
for i in range(0,tsig_in.GetEntries()):
  tsig_in.GetEntry(i)
  pi_pT_array[0] = _pi_pT
  gamma_eT_array[0] = _gamma_eT
  nBjets_25_array[0] = _nBjets_25
  lep_pT_array[0] = _lep_pT
  piRelIso_05_ch_array[0] = _piRelIso_05_ch
  MET_array[0] = _MET
  weight_array[0] = _weight
  Wmass_array[0] = _Wmass

  if isMuon:
    _BDT_output[0] = reader.EvaluateMVA("BDT_mu")
  else:
    _BDT_output[0] = reader.EvaluateMVA("BDT_ele")

  tsig_out.Fill()
# Background:
for i in range(0,tbkg_in.GetEntries()):
  tbkg_in.GetEntry(i)
  pi_pT_array[0] = _pi_pT
  gamma_eT_array[0] = _gamma_eT
  nBjets_25_array[0] = _nBjets_25
  lep_pT_array[0] = _lep_pT
  piRelIso_05_ch_array[0] = _piRelIso_05_ch
  MET_array[0] = _MET
  weight_array[0] = _weight
  Wmass_array[0] = _Wmass

  if isMuon:
    _BDT_output[0] = reader.EvaluateMVA("BDT_mu")
  else:
    _BDT_output[0] = reader.EvaluateMVA("BDT_ele")

  tbkg_out.Fill()

# Write trees to root file
tsig_out.Print()
tbkg_out.Print()
fOut.Write()
fOut.Close()

del reader
