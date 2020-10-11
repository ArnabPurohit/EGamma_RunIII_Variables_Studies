import FWCore.ParameterSet.Config as cms

process = cms.Process("photonanalyzer")
#isMC=False
isMC=True
isOpenData = False
is2017=False
is2018=False
is2021=False
is2023=True
process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )
#process.options.allowUnscheduled = cms.untracked.bool(True)
#f='/store/mc/Run3Summer19MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/130000/FD103F4C-8953-F445-A779-3F41F5C32A13.root'
#f='/store/mc/Run3Summer19MiniAOD/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v1/50000/F5D9503D-C766-5B44-8BA4-80CBDC07D42F.root'

#f='/store/mc/RunIIAutumn18MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/110000/872C85C0-F9B7-C34A-B51D-E0B3419B6658.root'
#f='/store/mc/RunIIAutumn18MiniAOD/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v2/110000/ED66CD74-BA8A-DD44-BB03-CD76897B4315.root'

#f='/store/mc/Run3Summer19MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2023Scenario_106X_mcRun3_2023_realistic_v3-v2/50000/F3F528DA-E27A-3540-883F-01953B51AF1B.root'
f='/store/mc/Run3Summer19MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2023Scenario_106X_mcRun3_2023_realistic_v3-v2/50000/FFAA01B2-D169-C24F-93CD-869CA3CDD6DF.root'
#f='/store/mc/Run3Summer19MiniAOD/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2023Scenario_106X_mcRun3_2023_realistic_v3-v1/270000/FEFCAC77-6FC3-684A-B3DE-76E3E3E1AE3B.root'
is2018="2018" in f
is2021="2021" in f
is2023="2023" in f
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load("Configuration.Geometry.GeometryIdeal_cff" )
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_2016SeptRepro_v7')
#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v8')
if(isMC):
    #process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v12')
    if(is2017):
        process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v13')
    if(is2018):
        process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v15')
    if(is2021):
        process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mcRun3_2021_realistic_v3')
    if(is2023):
        process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mcRun3_2023_realistic_v3')
    elif(isOpenData):
        process.GlobalTag = GlobalTag(process.GlobalTag, '80X_mcRun2_asymptotic_2016_TrancheIV_v8')
    else:
        process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')
#process.load("MET_Resp.G_Jet.METFilters_cff")
else: 
    if(is2017):
        process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v2')
    else:
        process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_2016SeptRepro_v7')
process.load("CondCore.DBCommon.CondDBCommon_cfi")



#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(50000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'/store/data/Run2017F/DoubleEG/MINIAOD/17Nov2017-v1/50000/00105BAD-63E0-E711-8640-02163E0146C5.root'
        #'/store/data/Run2017C/SinglePhoton/MINIAOD/17Nov2017-v1/20000/0015918D-37D3-E711-9199-0025904B7C42.root'
        #'/store/data/Run2017B/SinglePhoton/MINIAOD/17Nov2017-v1/20000/00D960EC-7BD3-E711-A054-008CFAFBE880.root'
        #'/store/mc/RunIIFall17MiniAOD/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v1/50000/0024A35F-86EB-E711-A5BC-A4BF0112BC06.root'
        #'file:pickevents.root'
        #'/store/data/Run2016C/SinglePhoton/MINIAOD/23Sep2016-v1/70000/0E03274A-248A-E611-96AF-0025905A613C.root'
        #'/store/mc/RunIISummer16MiniAODv2/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/60000/022ABCCF-C0D5-E611-8FD2-FA163E9988DA.root'
        #'/store/data/Run2016B/SinglePhoton/MINIAOD/03Feb2017_ver2-v2/100000/000C0045-12EB-E611-9BEC-008CFA197C34.root'
        #'/store/data/Run2016C/SinglePhoton/MINIAOD/03Feb2017-v1/110000/00A16B0C-72EB-E611-9114-002590E7DE24.root'
        #'/store/mc/RunIISpring16MiniAODv2/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/00455E99-5021-E611-998E-003048CF5C10.root'
        #'/store/mc/RunIISummer16MiniAODv2/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/0C609159-90CB-E611-88B5-0CC47A4D7692.root'
        #'/store/data/Run2016B/SingleElectron/MINIAOD/23Sep2016-v2/80000/5A4402F5-638C-E611-A471-0025905A60AA.root'
        #'/store/mc/Run3Summer19DRPremix/DYToEE_M-50_NNPDF31_TuneCP5_14TeV-powheg-pythia8/AODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/270000/FFA6A719-AD74-1142-A198-B156CA209F64.root'
        #'/store/mc/Run3Summer19MiniAOD/DYToEE_M-50_NNPDF31_TuneCP5_14TeV-powheg-pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/270000/FC2E1C55-35CE-4847-91C4-0E288C41178F.root'
        #'/store/mc/Run3Summer19MiniAOD/TTToSemiLeptonic_TuneCP5_14TeV-powheg-pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/130000/7745BA80-495A-E04B-BB55-AEB01E844411.root'
        #'/store/mc/Run3Summer19MiniAOD/TTToSemiLeptonic_TuneCP5_14TeV-powheg-pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/130000/19B161A5-BFA4-7847-9680-150196E2270B.root'
        #'/store/mc/RunIIAutumn18MiniAOD/DYToEE_M-50_NNPDF31_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/120000/006F8DAD-115F-BC47-915A-15A0B817EED3.root'
        
        #'/store/mc/Run3Summer19MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v2/130000/FD103F4C-8953-F445-A779-3F41F5C32A13.root'
        #'/store/mc/Run3Summer19MiniAOD/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2021Scenario_106X_mcRun3_2021_realistic_v3-v1/50000/F5D9503D-C766-5B44-8BA4-80CBDC07D42F.root'
        
        #'/store/mc/RunIIAutumn18MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/110000/872C85C0-F9B7-C34A-B51D-E0B3419B6658.root'
        #'/store/mc/RunIIAutumn18MiniAOD/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v2/110000/ED66CD74-BA8A-DD44-BB03-CD76897B4315.root'

        f
        #'/store/mc/RunIIAutumn18MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/110000/872C85C0-F9B7-C34A-B51D-E0B3419B6658.root'
        #'/store/mc/RunIIAutumn18MiniAOD/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v2/10000/37905AE1-A70B-DC48-977A-25CE0FDD08C9.root'
        #'/store/mc/Run3Summer19MiniAOD/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2023Scenario_106X_mcRun3_2023_realistic_v3-v2/50000/F3F528DA-E27A-3540-883F-01953B51AF1B.root'
        #'/store/mc/Run3Summer19MiniAOD/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_14TeV_Pythia8/MINIAODSIM/2023Scenario_106X_mcRun3_2023_realistic_v3-v1/270000/FEFCAC77-6FC3-684A-B3DE-76E3E3E1AE3B.root'

        #'/store/mc/Run3Summer19MiniAOD/QCD_Pt_15to7000_TuneCP5_Flat_14TeV_pythia8/MINIAODSIM/106X_mcRun3_2021_realistic_v3-v2/130000/E25CBB24-21B7-3A40-99E5-BFD3CB845C7D.root'
        #'/store/mc/RunIISummer16MiniAODv2/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/PUMoriond17_magnetOn_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/80000/FA7A80D9-6CEF-E611-9933-FA163E036391.root'
        #'/store/mc/RunIISummer16MiniAODv2/GluGluHToGG_M-125_13TeV_powheg_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/70000/DCCBCD86-2BBD-E611-B97D-20CF307C98C9.root'
    )
)
process.load( "PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff" )

if isMC==False:
    process.load( "PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff" )

process.load( "PhysicsTools.PatAlgos.selectionLayer1.selectedPatCandidates_cff" )

if(isMC):
### EGM scale and smearing correction         
    """
    process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
                                                       calibratedPatElectrons = cms.PSet(
            initialSeed = cms.untracked.uint32(12345),
            engineName = cms.untracked.string('TRandom3')
            ),
                                                       calibratedPatPhotons = cms.PSet(
            initialSeed = cms.untracked.uint32(12345),
            engineName = cms.untracked.string('TRandom3')
            ),
                                                       gjet = cms.PSet(
            initialSeed = cms.untracked.uint32(67890),
            engineName = cms.untracked.string('TRandom3')
            )
                                                       )


    from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
    setupEgammaPostRecoSeq(process,
                           runVID=True,
                           era='2018-Prompt',
                           eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                                         'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
                                         'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
                                         'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff'],
                           phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
                                         'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
    )

 
### EGM scale and smearing correction
#process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')
#process.load('EgammaAnalysis.ElectronTools.calibratedPatPhotonsRun2_cfi')
#if(isMC):
#    process.calibratedPatElectrons.isMC = cms.bool(True)
#    process.calibratedPatPhotons.isMC = cms.bool(True)
#if(isMC==False):
#    from PhysicsTools.PatAlgos.tools.coreTools import *
#    runOnData( process, names=['Photons', 'Electrons','Muons','Taus','Jets'], outputModules = [] )

print "-> Updating the jets collection to run on to 'updatedPatJetsUpdatedJEC' with the new jec in the GT/or DB"

if(isMC):
    #process.calibratedPatPhotons.isMC = cms.bool(True)

    from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
    
    updateJetCollection(
        process,
        jetSource = cms.InputTag('slimmedJets'),
        labelName = 'UpdatedJEC',
        jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
        )
    process.jecSequence = cms.Sequence(process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC)
    #process.jecSequence = cms.Sequence(process.patAlgosToolsTask)
# MET correction and uncertainties
#if(isMC):
    from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
    runMetCorAndUncFromMiniAOD(process,
                               isData=False,
                               #jetCollUnskimmed='selectedUpdatedPatJetsUpdatedJEC',#'updatedPatJetsUpdatedJEC',
                               #reapplyJEC=False
                               )

   # from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD
   # makePuppiesFromMiniAOD( process, True );
 
   # runMetCorAndUncFromMiniAOD(process,
   #                            isData=False,
   #                            metType="Puppi",
   #                            pfCandColl=cms.InputTag("packedPFCandidates"),
   #                            recoMetFromPFCs=True,
   #                            jetFlavor="AK4PFPuppi",
   #                            postfix="Puppi"
   #                            )

else:
    from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
    
    updateJetCollection(
        process,
        jetSource = cms.InputTag('slimmedJets'),
        labelName = 'UpdatedJEC',
        jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute','L2L3Residual']), 'None')  # Update: Safe to always add 'L2L3Residual' as MC contains dummy L2L3Residual corrections (always set to 1)
        )
    process.jecSequence = cms.Sequence(process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC)
    #process.jecSequence = cms.Sequence(process.patAlgosToolsTask)
# MET correction and uncertainties
    from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
    runMetCorAndUncFromMiniAOD(process,
                               isData=True,
                               #jetCollUnskimmed='updatedPatJetsUpdatedJEC',
                               #reapplyJEC=False
                               )

    #from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD
    #makePuppiesFromMiniAOD( process, True );
 
    #runMetCorAndUncFromMiniAOD(process,
    #                           isData=True,
    #                           metType="Puppi",
    #                           pfCandColl=cms.InputTag("puppiForMET"),
    #                           recoMetFromPFCs=True,
    #                           jetFlavor="AK4PFPuppi",
    #                           postfix="Puppi"
    #                           )

########### MET Filter ################
process.load("MET_Resp.G_Jet.METFilters_cff") #new

#####VID framework####################
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
dataFormat = DataFormat.MiniAOD
switchOnVIDElectronIdProducer(process, dataFormat)
switchOnVIDPhotonIdProducer(process, dataFormat)

#from RecoEgamma.PhotonIdentification.egmPhotonIDs_cfi import *
#from RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cff import *
#from PhysicsTools.SelectorUtils.centralIDRegistry import central_id_registry

# Load the producer module to build full 5x5 cluster shapes and whatever 
# else is needed for IDs
#process.load("RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi")
#from RecoEgamma.PhotonIdentification.PhotonIDValueMapProducer_cfi import *

process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")
process.load("RecoEgamma/ElectronIdentification/ElectronIDValueMapProducer_cfi")

# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V1_cff']
#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

my_phoid_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_TrueVtx_cff']
#my_phoid_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring16_V2p2_cff']#,
                    #'RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Spring16_nonTrig_V1_cff']

#process.load("RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi")
process.load("RecoEgamma.ElectronIdentification.egmGsfElectronIDs_cff")
process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedElectrons')
process.photonIDValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')

for idmod in my_phoid_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)



#process.photonMVAValueMapProducer.srcMiniAOD = cms.InputTag('slimmedPhotons')

# MET correction and uncertainties
#from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD  #new
#runMetCorAndUncFromMiniAOD(process,  #new
 #                          isData=True                           
#)

# Now you are creating the e/g corrected MET on top of the bad muon corrected MET (on re-miniaod)
#from PhysicsTools.PatUtils.tools.corMETFromMuonAndEG import corMETFromMuonAndEG  #new
#corMETFromMuonAndEG(process,  #new
 #                   pfCandCollection="", #not needed                        
 #                   electronCollection="slimmedElectrons",
 #                   photonCollection="slimmedPhotons",
 #                   corElectronCollection="slimmedElectrons",
 #                   corPhotonCollection="slimmedPhotons",
 #                   allMETEGCorrected=True,
 #                   muCorrection=False,
 #                   eGCorrection=True,
 #                   runOnMiniAOD=True,
 #                   postfix="MuEGClean"
 #                   )
#process.slimmedMETsMuEGClean = process.slimmedMETs.clone() #new
#process.slimmedMETsMuEGClean.src = cms.InputTag("patPFMetT1MuEGClean")  #new
#process.slimmedMETsMuEGClean.rawVariation =  cms.InputTag("patPFMetRawMuEGClean")  #new
#process.slimmedMETsMuEGClean.t1Uncertainties = cms.InputTag("patPFMetT1%sMuEGClean")  #new
#del process.slimmedMETsMuEGClean.caloMET

#process.egcorrMET = cms.Sequence(  #new
#        process.cleanedPhotonsMuEGClean+process.cleanedCorPhotonsMuEGClean+
 #       process.matchedPhotonsMuEGClean + process.matchedElectronsMuEGClean +
  #      process.corMETPhotonMuEGClean+process.corMETElectronMuEGClean+
   #     process.patPFMetT1MuEGClean+process.patPFMetRawMuEGClean+
    #    process.patPFMetT1SmearMuEGClean+process.patPFMetT1TxyMuEGClean+
    #    process.patPFMetTxyMuEGClean+process.patPFMetT1JetEnUpMuEGClean+
    #    process.patPFMetT1JetResUpMuEGClean+process.patPFMetT1SmearJetResUpMuEGClean+
    #    process.patPFMetT1ElectronEnUpMuEGClean+process.patPFMetT1PhotonEnUpMuEGClean+
    #    process.patPFMetT1MuonEnUpMuEGClean+process.patPFMetT1TauEnUpMuEGClean+
    #    process.patPFMetT1UnclusteredEnUpMuEGClean+process.patPFMetT1JetEnDownMuEGClean+
    #    process.patPFMetT1JetResDownMuEGClean+process.patPFMetT1SmearJetResDownMuEGClean+
    #    process.patPFMetT1ElectronEnDownMuEGClean+process.patPFMetT1PhotonEnDownMuEGClean+
    #    process.patPFMetT1MuonEnDownMuEGClean+process.patPFMetT1TauEnDownMuEGClean+
    #    process.patPFMetT1UnclusteredEnDownMuEGClean+process.slimmedMETsMuEGClean)
"""
process.photonanalyzer = cms.EDAnalyzer('PhotonAnalyzer',
                              #doGenParticles = cms.bool(False),
                              doGenParticles = cms.bool(True),
                              runOnParticleGun     = cms.bool(False),
                              runOnSherpa = cms.bool(False),
                              genParticleSrc = cms.InputTag("prunedGenParticles"),
                              #LHEEventLabel = cms.InputTag("externalLHEProducer"),##Turned off due to QCD sample dows not have this collection
                              #pileupCollection = cms.InputTag("addPileupInfo"),
                              pileupCollection = cms.InputTag("slimmedAddPileupInfo"),
                              #vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
                              #barrelRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
                              barrelRecHitCollection = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
                              #endcapRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
                              endcapRecHitCollection = cms.InputTag("reducedEgamma", "reducedEERecHits"),
                              #barrelClusterCollection = cms.InputTag("hybridSuperClusters:hybridBarrelBasicClusters"),
                              barrelClusterCollection = cms.InputTag("reducedEgamma","reducedEBEEClusters"),
                              #endcapClusterCollection = cms.InputTag("multi5x5SuperClusters:multi5x5EndcapBasicClusters"),
                              endcapClusterCollection = cms.InputTag("reducedEgamma","reducedEBEEClusters"),
                              electronSrc          = cms.untracked.InputTag("slimmedElectrons"),
                              #calibelectronSrc = cms.untracked.InputTag("slimmedElectrons"),
                              photonSrc = cms.untracked.InputTag("slimmedPhotons"),
                              #calibphotonSrc       = cms.untracked.InputTag("calibratedPatPhotons"),
                              #muonSrc = cms.untracked.InputTag("slimmedMuons"),
                              #jetSrc = cms.untracked.InputTag("slimmedJets"),
                              #jetSrc = cms.untracked.InputTag("selectedUpdatedPatJetsUpdatedJEC"),
                              #jetSrc = cms.untracked.InputTag("updatedPatJetsUpdatedJEC"),#following nero
                              #metSrc = cms.untracked.InputTag("slimmedMETs"),
                              #puppiMETLabel = cms.InputTag("slimmedMETsPuppi"),
                              #metSrc = cms.untracked.InputTag("slimmedMETsMuEGClean"),
                              #metSrc = cms.untracked.InputTag("slimmedMETsMuEGClean","","gjet"),  #new
                              VtxLabel             = cms.InputTag("offlineSlimmedPrimaryVertices"),
                              rhoLabel             = cms.InputTag("fixedGridRhoFastjetAll"),
                              rhoCentralLabel = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                              #triggerResults       = cms.InputTag("TriggerResults", "", "HLT"),
                              #triggerResults = cms.InputTag("TriggerResults","","RECO"),
                              #prescales = cms.InputTag("patTrigger","","PAT"), #PAT
                              #prescales = cms.InputTag("patTrigger","","RECO"), #RECO
                              ebReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
                              eeReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedEERecHits"),
                              esReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedESRecHits"),
                              objects = cms.InputTag("selectedPatTrigger"),
                              generatorLabel = cms.InputTag("generator"),
                              newParticles = cms.vint32(1000006, 1000021, 1000022, 1000024, 1000025, 1000039, 3000001, 3000002, 35),
                              #phoLooseIdMap=cms.InputTag("reducedEgammaBeforeGSFix","PhotonCutBasedIDLoose"),
                              #eleVetoIdMap    = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-veto"),
                              #eleLooseIdMap   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-loose"),
                              #eleMediumIdMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-medium"),
                              #eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-tight"),
                              #phoLooseIdMap   = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Fall17-94X-V2-loose"),
                              #phoMediumIdMap  = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Fall17-94X-V2-medium"),
                              #phoTightIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Fall17-94X-V2-tight"),
                              )
process.TFileService = cms.Service("TFileService",
  #fileName = cms.string('PhotonAnalyzer_MC_TTToSemoleptonic.root')
                                   #fileName = cms.string('PhotonAnalyzer_MCwithgenmatchingTTToSemileptonic.root')
                                   #fileName = cms.string('PhotonAnalyzer_MCwithgenmatchingQCD.root')
                                   #fileName = cms.string('PhotonAnalyzer_MCwithgenmatching.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_PFThr_new.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_PFThr_2018_new.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_PFThr_2018_20to40_new.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_PFThr_2018_20to40_new.root')
                                   fileName = cms.string('PhotonAnalyzer_MC_PFThr_2023_GJet40toInf_corrThr_7thJune.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_PFThr_2021_GJet40toInf_corrThr_7thJune.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_PFThr_2018_GJet40toInf_corrThr_7thJune.root')
                                   #fileName = cms.string('PhotonAnal_QCD_opendata_8thMay.root')
                                   #fileName = cms.string('PhotonAnalyzer_MCGJet_Pt-40toInf_DoubleEMEnriched_PFThr.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_lazytools.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_lazytools_true.root')
                                   #fileName = cms.string('PhotonAnalyzer_MC_lazytools_true_withtopology.root')
                                   #fileName = cms.string('PhotonAnalyzer_TTToSemileptonic_MC_lazytools_true_withtopology.root')
                                   #fileName = cms.string('PhotonAnalyzer_QCD_MC_lazytools_true_withtopology.root')
                                   #fileName = cms.string('PhotonAnalyzer_GGHtoGG_M125.root')
                                   
)
#process.dump = cms.EDAnalyzer("EventContentAnalyzer")
#process.Tracer = cms.Service("Tracer")
#process.load("MET_Resp.G_Jet.METFilters_cff") #new

process.p = cms.Path(
    #process.photonIDValueMapProducer *
    #process.fullPatMetSequence* #new
    #process.egcorrMET*  #new
    #process.calibratedPatElectrons*
    #process.calibratedPatPhotons* #from gganalyser
    #process.egmGsfElectronIDSequence *
    #process.egmPhotonIDSequence*
    #process.jecSequence*
    #process.fullPatMetSequence*
    #process.fullPatMetSequencePuppi*
    #process.gjetMETFiltersSequence*  #new
    process.photonanalyzer
    #process.dump*
    )
#
#print process.dumpPython()
