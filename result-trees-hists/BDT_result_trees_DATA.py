# Takes result from BDT and creates tree from data tree that include this result #

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
  fIn = TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_mu_DATA.root")
  t_in = fIn.Get("minitree_mu_DATA")

  fOut = TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_mu_DATA.root","RECREATE")
else:
  fIn = TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_ele_DATA.root")
  t_in = fIn.Get("minitree_ele_DATA")

  fOut = TFile("/eos/user/j/jdioquin/www/MVA_studies/BDTeval2818/BDTeval_ele_DATA.root","RECREATE")

# Create arrays for the reader 
pi_pT_array = array("f",[0.])
gamma_eT_array = array("f",[0.])
nBjets_25_array = array("f",[0])
lep_pT_array = array("f",[0.])
piRelIso_05_ch_array = array("f",[0.])
MET_array = array("f",[0.])
weight_array = array("f",[0.])
#Wmass_array = array("f",[0.])

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
#_Wmass = np.zeros(1,dtype=float)

t_out = TTree("minitree","tree with branches")
t_out.Branch("pi_pT",_pi_pT,"pi_pT/D")
t_out.Branch("gamma_eT",_gamma_eT,"gamma_eT/D")
t_out.Branch("nBjets_25",_nBjets_25,"nBjets_25/I")
t_out.Branch("lep_pT",_lep_pT,"lep_pT/D")
t_out.Branch("piRelIso_05_ch",_piRelIso_05_ch,"piRelIso_05_ch/D")
t_out.Branch("MET",_MET,"MET/D")
t_out.Branch("BDT_output",_BDT_output,"BDT_output/D")
t_out.Branch("weight",_weight,"weight/D")
#t_out.Branch("Wmass",_Wmass,"Wmass/D")

# Event loop
if isMuon:
  reader.BookMVA("BDT_mu","Training/weights/TMVAClassification_BDT.weights_mu.xml")
else:
  reader.BookMVA("BDT_ele","Training/weights/TMVAClassification_BDT.weights_ele.xml")

# Prepare input tree
t_in.SetBranchAddress("pi_pT",_pi_pT)
t_in.SetBranchAddress("gamma_eT",_gamma_eT)
t_in.SetBranchAddress("nBjets_25",_nBjets_25)
t_in.SetBranchAddress("lep_pT",_lep_pT)
t_in.SetBranchAddress("piRelIso_05_ch",_piRelIso_05_ch)
t_in.SetBranchAddress("MET",_MET)
t_in.SetBranchAddress("weight",_weight)
#t_in.SetBranchAddress("Wmass",_Wmass)

# looping through events:
# Signal:
for i in range(0,t_in.GetEntries()):
  t_in.GetEntry(i)
  pi_pT_array[0] = _pi_pT
  gamma_eT_array[0] = _gamma_eT
  nBjets_25_array[0] = _nBjets_25
  lep_pT_array[0] = _lep_pT
  piRelIso_05_ch_array[0] = _piRelIso_05_ch
  MET_array[0] = _MET
  weight_array[0] = _weight
 # Wmass_array[0] = _Wmass

  if isMuon:
    _BDT_output[0] = reader.EvaluateMVA("BDT_mu")
  else:
    _BDT_output[0] = reader.EvaluateMVA("BDT_ele")

  t_out.Fill()

# Write trees to root file
t_out.Print()
fOut.Write()
fOut.Close()

del reader
