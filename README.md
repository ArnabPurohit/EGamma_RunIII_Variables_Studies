# Shower-shape Variable Redefinition for Run-III

This repository contains the CMSSW analyser which can be used to study different definitions of photon R9 or other shower-shape variables for Run-III of LHC in CMS EGamma-POG. The purpose of the redefinition is to make them unaffected by the change in PF-RecHit-Thresold or PU as much as possible.

## Instructions
Below are the instructions for preparing the environment, producing the flat nTuples and finally making the plots from those nTuples.

### Setup
* cmsrel CMSSW_10_6_1_patch1
* cd CMSSW_10_6_1_patch1/src
* cmsenv
* git clone https://github.com/ArnabPurohit/EGamma_RunIII_Variables_Studies
* scram b -j 4

### Flat nTuple production

#### To test on few events ->
cmsRun ConfFile_cfg_10_6_1.py

#### To run on full samples ->
Submit jobs with crabConfig_25ns.py
First Change the,
 1. storageSite
 2. inputDataset

Now, submit the jobs by running,
python crabConfig_25ns.py

### Making the final plots

After producing the nTuples use the following files to make the histograms (using 1 and 2) and plots (using 3-6). 
 1. test/tree_analyser.C
 2. test/bkgtree_analyser.C
 3. test/plots_from_histos_forsig_vs_bkg.py
 4. test/plots_from_histos.py
 5. test/myROC_maker.C
 6. test/myROC_maker_alltogether.C