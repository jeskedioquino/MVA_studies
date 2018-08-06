# MVA_studies

--- train_trees.py ---
need to have directory called 'outputs' OR save Nominal_training .root files to an /eos/ folder
creates training and weight files for BDT

--- BDT_result_trees.py ---
need access to weight.xml files created by train_trees.py, as well as original trees
creates new trees that include original variables as well as BDT_output

--- make_hists_cut025.C ---
need access to BDT_result_trees for the BDT_output cut value
creates .root files with input variable histograms (TH1D) from the BDT result trees

--- 
