# So far this is the best method for the BDT #

import ROOT
import os
import argparse
#---------------------------------#
p = argparse.ArgumentParser(description='Select whether the MVA will be performed on the muon or the electron sample')
p.add_argument('isMuon_option', help='Type <<muon>> or <<electron>>')
args = p.parse_args()

# Switch from muon to electron channel
if args.isMuon_option == "muon":
    isMuon = True
if args.isMuon_option == "electron":
    isMuon = False
#---------------------------------#

if isMuon:
    fIn_bkg = ROOT.TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Background_mu.root")
    tree_bkg = fIn_bkg.Get("minitree_background_mu")
    fIn_sig = ROOT.TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Signal_mu.root")
    tree_sig = fIn_sig.Get("minitree_signal_mu")
    fOut = ROOT.TFile("outputs/Nominal_training_mu.root","RECREATE")
else:
    fIn_bkg = ROOT.TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Background_ele.root")
    tree_bkg = fIn_bkg.Get("minitree_background_ele")
    fIn_sig = ROOT.TFile("/eos/user/j/jdioquin/www/MVA_studies/TreeFiles_31718/Tree_MC_Signal_ele.root")
    tree_sig = fIn_sig.Get("minitree_signal_ele")
    fOut = ROOT.TFile("outputs/Nominal_training_ele.root","RECREATE")


#--------------------------- Here starts the MVA-----------------------------#
ROOT.TMVA.Tools.Instance()

factory = ROOT.TMVA.Factory("TMVAClassification", fOut,":".join(["!V","Transformations=I;D;P;G,D;N","AnalysisType=Classification"]))

# Choose the variables to be part of the MVA
factory.AddVariable("pi_pT","F")
factory.AddVariable("gamma_eT","F")
factory.AddVariable("nBjets_25","I")
#factory.AddVariable("deltaphi_lep_pi","F")
factory.AddVariable("lep_pT","F")
factory.AddVariable("piRelIso_05_ch","F")
#factory.AddVariable("Wmass")
factory.AddVariable("MET","F")


factory.AddSignalTree(tree_sig)
factory.AddBackgroundTree(tree_bkg)

factory.SetWeightExpression("weight")

mycuts = ROOT.TCut("weight > 0.")
mycutb = ROOT.TCut("weight > 0.")

if isMuon:
    factory.PrepareTrainingAndTestTree(mycuts, mycutb, ":".join(["!V","nTrain_Signal=9227","nTest_Signal=3076","nTrain_Background=117531","nTest_Background=39177"]) )
    # Choose the MVA method
    method_bdt = factory.BookMethod(ROOT.TMVA.Types.kBDT, "BDT", ":".join(["H","!V","NTrees=800", "MinNodeSize=2.5%","MaxDepth=3","BoostType=AdaBoost","AdaBoostBeta=0.25","nCuts=20"]))

else:
    factory.PrepareTrainingAndTestTree(mycuts, mycutb, ":".join(["!V","nTrain_Signal=6398","nTest_Signal=2133","nTrain_Background=82689","nTest_Background=27563"]) )

    # To split electron channel 75/25 add:
    #,"nTrain_Signal=9227","nTest_Signal=3076","nTrain_Background=117531","nTest_Background=39177"]) )

    # Choose the MVA method
    method_bdt = factory.BookMethod(ROOT.TMVA.Types.kBDT, "BDT", ":".join(["H","!V","NTrees=1100","MinNodeSize=2.5%","MaxDepth=2","BoostType=AdaBoost","AdaBoostBeta=0.25","nCuts=40"]))

factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()

fOut.Close()

# Define the position of the weightfiles
weightfile_dir = "weights/TMVAClassification_BDT.weights.xml"

weightfile_mu = "weights/TMVAClassification_BDT.weights_mu.xml"
weightfile_ele = "weights/TMVAClassification_BDT.weights_ele.xml"

# Rename the weightfiles for the two different channels
if isMuon:
    rename_weightfile = "mv " + weightfile_dir + " " + weightfile_mu
    os.system(rename_weightfile)
else:
    rename_weightfile = "mv " + weightfile_dir + " " + weightfile_ele
    os.system(rename_weightfile)

exit()
