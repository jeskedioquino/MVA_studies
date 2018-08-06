# MVA_studies
*many of these macros require the presence of output directories*

# Training
--- train_trees.py ---
need *original trees*
need to have *directory* called 'outputs' OR save Nominal_training (.root) files to an /eos/ folder
creates training and weight files for BDT

# result-trees-hists
--- BDT_result_trees (.py) ---
need access to *weightfiles* (.xml) created by train_trees.py, as well as *original trees*
creates new trees that include original variables as well as BDT_output (BDTeval (.root))

--- make_hists_cut025 (.C) ---
need access to *BDTeval* ROOT files for the BDT_output cut value
creates .root files with input variable histograms (TH1D) from the BDT result trees

# plot-machines
--- rejBvsSplot (.C) ---
need access to *Nominal_training* ROOT files
creates one or more ROC plots

--- rel/isolation_pipt_2dhists (.C) ---
only require *original trees*
compares piRelIso or piIso to pi_pT with 2D histograms for both muon & electron channels

--- plot_bkg_data_input_vars_cut025 (.C) ---
need access to *histogram ROOT files* made by make_hists_cut025 (.C)
creates .pdf file with input variable histograms (total of 12) from both channels with a BDT score cut >= 0.25

--- BDT_output_sigbkghists (.C) ---
need access to *BDTeval* ROOT files to get distributions of BDT_output
plots BDT_output histograms for each channel, superimposing signal and background on same plot
