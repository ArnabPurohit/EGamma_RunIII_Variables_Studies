if __name__ == '__main__':

# Usage : python crabConfig.py (to create jobs)
#         ./multicrab -c status -d <work area> (to check job status)

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    from CRABClient.UserUtilities import config
    config = config()
    
    from multiprocessing import Process

    # Common configuration

    #config.General.workArea     = 'crab_projects_2017Data_MET_Resp_April2018_2018ReRecoSinglePhotonSamples'
    #config.General.workArea     = 'crab_projects_DYToEE_M-50_Run3Summer19MiniAOD-2021Scenario'
    #config.General.workArea     = 'crab_projects_DYToEE_M-50_Run3Summer19MiniAOD-2023Scenario'
    #config.General.workArea     = 'crab_projects_DYToEE_M-50_Run3Summer19MiniAOD-2024Scenario'
    #config.General.workArea     = 'crab_projects_DYToEE_M-50_Run3Summer19MiniAOD-2018Scenario'
    #config.General.workArea     = 'crab_projects_QCD_Pt-15to7000_TuneCP5_Flat2018'
    #config.General.workArea     = 'crab_projects_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV'
    #config.General.workArea     = 'crab_projects_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV'
    #config.General.workArea     = 'crab_projects_2018_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV'
    #config.General.workArea     = 'crab_projects_2018_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV'
    #config.General.workArea     = 'crab_projects_2021_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV'
    config.General.workArea     = 'crab_projects_2023_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV'
    #config.General.workArea     = 'crab_projects_TTToSemiLeptonic_TuneCP5_Run3Summer19DRPremix-2024Scenario'
    #config.General.workArea     = 'crab_projects_QCD_Pt_15to7000_TuneCP5_Flat_Run3Summer19DRPremix-2024Scenario'
    config.General.transferLogs = False
    config.JobType.pluginName   = 'Analysis' # PrivateMC
    #config.JobType.psetName     = 'ConfFile_cfg.py'
    #config.JobType.psetName     = 'ConfFile_cfg_944.py'
    config.JobType.psetName     = 'ConfFile_cfg_10_6_1.py'
    #config.JobType.psetName     = 'run_mc_80X.py'
    #config.JobType.inputFiles   = ['Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt', 'Summer16_23Sep2016AllV4_DATA.db']

    #config.JobType.inputFiles   =  ['Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC.db']
    #config.JobType.inputFiles   =  ['Fall17_17Nov2017BCDEF_V6_DATA.db','Fall17_17Nov2017_V6_MC.db']
    #config.JobType.sendExternalFolder = True
    config.Data.inputDBS        = 'global'    
    config.Data.splitting       =  'FileBased'#for MC #'LumiBased'For data EventBased, FileBased, LumiBased (1 lumi ~= 300 events)
    config.Data.totalUnits      = -1
    config.Data.ignoreLocality  = True #For GJet20to402021
    #config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'
    #config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
    config.Data.publication     = False
    #config.Site.storageSite     = 'T2_CH_CERN'
    config.Site.storageSite     = 'T2_US_UCSD'
    config.Site.whitelist       = ['T2_US_*'] #For GJet20to402021 ['T2_US_*']

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    # dataset dependent configuration
    #config.General.requestName = 'job_March_data_2016B_ver2-v2_MET_Resp_lumimask'
    #config.General.requestName = 'job_May_data_2017F_v1_MET_Resp_31March2018'


    #config.General.requestName = 'job_Nov_MC_2021_DY_10Nov2019'
    #config.General.requestName = 'job_DEC_MC_2023_DY_10Nov2019'
    #config.General.requestName = 'job_DEC_MC_2024_DY_5Dec2019'
    #config.General.requestName = 'job_DEC_MC_2018_DY_29Jan2020'
    #config.General.requestName = 'job_DEC_MC_2018_QCD_29Jan2020'
    #config.General.requestName = 'job_Feb_MC_2021_GJet_Pt-40toInf'
    #config.General.requestName = 'job_May_MC_2021_GJet_Pt-20to40'
    #config.General.requestName = 'job_May_MC_2018_GJet_Pt-20to40'
    config.General.requestName = 'job_May_MC_2023_GJet_Pt-40toInf'
    #config.General.requestName = 'job_Feb_MC_2018_GJet_Pt-20to40'
    #config.General.requestName = 'job_Feb_MC_2018_GJet_Pt-40toInf'
    #config.General.requestName = 'job_Feb_MC_2023_GJet_Pt-20to40'
    #config.General.requestName = 'job_Feb_MC_2023_GJet_Pt-40toInf'
    #config.General.requestName = 'job_DEC_MC_2024_TTToSemiLeptonic_5Dec2019'
    #config.General.requestName = 'job_DEC_MC_2024_QCD_6Dec2019'




    #config.General.requestName = 'job_March_MC_QCD2000toInf'
    #config.General.requestName = 'job_March_MC_GJets400to600'
    #config.General.requestName = 'job_March_MC_G600toInf'
    
    #config.General.requestName = 'job_July_data_2016G'
    #config.General.requestName = 'job_Febv2_data_Run2016C_MET_Resp'
    #config.General.requestName = 'job_March_MC_MET_Resp_WJetsToLNu_HT2500toInf'
    #config.General.requestName = 'job_Oct_MC_MET_Resp_WGToLNuG'
    #config.General.requestName = 'job_Oct_MC_MET_Resp_WGJets_MonoPhoton'
    #config.General.requestName = 'job_Oct_MC_MET_Resp_ZNuNuGJets_MonoPhoton_PtG-40to130'
    #config.General.requestName = 'job_Oct_MC_MET_Resp_ZNuNuGJets_MonoPhoton_PtG-130'
    #config.General.requestName = 'job_Oct_MC_MET_Resp_ZGTo2LG'
    #config.General.requestName = 'job_March_MC_MET_Resp_GJets400to600'
    #config.General.requestName = 'job_March_MC_MET_Resp_QCD2000toInf'
    #config.General.requestName = 'job_March_MC_MET_Resp_TGJets'
    config.Data.unitsPerJob    = 100 #2
    #config.Data.inputDataset   = '/SinglePhoton/Run2016B-03Feb2017_ver2-v2/MINIAOD'
    #config.Data.inputDataset   = '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/SinglePhoton/Run2016B-03Feb2017_ver1-v1/MINIAOD'
    #config.Data.inputDataset   = '/SinglePhoton/Run2016C-03Feb2017-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017B-17Nov2017-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017C-17Nov2017-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017D-17Nov2017-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017E-17Nov2017-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017F-17Nov2017-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017B-31Mar2018-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017C-31Mar2018-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017D-31Mar2018-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017E-31Mar2018-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/SinglePhoton/Run2017F-31Mar2018-v1/MINIAOD' #latest
    #config.Data.inputDataset   = '/DYToEE_M-50_NNPDF31_TuneCP5_14TeV-powheg-pythia8/Run3Summer19MiniAOD-2021Scenario_106X_mcRun3_2021_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/DYToEE_M-50_NNPDF31_TuneCP5_14TeV-powheg-pythia8/Run3Summer19MiniAOD-2023Scenario_106X_mcRun3_2023_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/DYToEE_M-50_NNPDF31_TuneCP5_14TeV-powheg-pythia8/Run3Summer19MiniAOD-2024Scenario_106X_mcRun3_2024_realistic_v4-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/TTToSemiLeptonic_TuneCP5_14TeV-powheg-pythia8/Run3Summer19MiniAOD-2021Scenario_106X_mcRun3_2021_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_Pt_15to7000_TuneCP5_Flat_14TeV_pythia8/Run3Summer19MiniAOD-106X_mcRun3_2021_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_Pt_15to7000_TuneCP5_Flat_14TeV_pythia8/Run3Summer19MiniAOD-106X_mcRun3_2023_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_Pt_15to7000_TuneCP5_Flat_14TeV_pythia8/Run3Summer19MiniAOD-106X_mcRun3_2024_realistic_v4-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/TTToSemiLeptonic_TuneCP5_14TeV-powheg-pythia8/Run3Summer19MiniAOD-2023Scenario_106X_mcRun3_2023_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/TTToSemiLeptonic_TuneCP5_14TeV-powheg-pythia8/Run3Summer19MiniAOD-2024Scenario_106X_mcRun3_2024_realistic_v4-v3/MINIAODSIM'
    #config.Data.inputDataset   = '/DYToEE_M-50_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_Pt-15to7000_TuneCP5_Flat2018_13TeV_pythia8/RunIIAutumn18MiniAOD-FlatPU0to70RAW_102X_upgrade2018_realistic_v15-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/Run3Summer19MiniAOD-2021Scenario_106X_mcRun3_2021_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/Run3Summer19MiniAOD-2021Scenario_106X_mcRun3_2021_realistic_v3-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/Run3Summer19MiniAOD-2023Scenario_106X_mcRun3_2023_realistic_v3-v1/MINIAODSIM'
    config.Data.inputDataset   = '/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/Run3Summer19MiniAOD-2023Scenario_106X_mcRun3_2023_realistic_v3-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/Run3Summer19MiniAOD-2021Scenario_106X_mcRun3_2021_realistic_v3-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM' #latest
    #config.Data.inputDataset   = '/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/Run3Summer19MiniAOD-2021Scenario_106X_mcRun3_2021_realistic_v3-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/SinglePhoton/Run2016H-03Feb2017_ver3-v1/MINIAOD'
    #config.Data.inputDataset   = '/SinglePhoton/Run2016G-03Feb2017-v1/MINIAOD'
    #config.Data.inputDataset   = '/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/ZNuNuGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/ZNuNuGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/ZNuNuGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'
    #config.Data.inputDataset   = '/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'
    #config.Data.outLFNDirBase  = '/store/user/arpurohi/'
    p = Process(target=submit, args=(config,))
    p.start()
    #p.join()
