import FWCore.ParameterSet.Config as cms

gjet = cms.EDAnalyzer('G_Jet',
                      generatorLabel = cms.InputTag("generator"),
                      electronSrc          = cms.InputTag("slimmedElectrons"),
                      #calibelectronSrc = cms.InputTag("calibratedPatElectrons"),
                      calibelectronSrc = cms.InputTag("slimmedElectrons"),
                      photonSrc = cms.untracked.InputTag("slimmedPhotons"),
                      calibphotonSrc = cms.InputTag("calibratedPatPhotons"),
                      muonSrc = cms.InputTag("slimmedMuons"),
                      jetSrc = cms.untracked.InputTag("slimmedJets"),
                      #jetSrc = cms.untracked.InputTag("selectedUpdatedPatJetsUpdatedJEC"),
                      #jetSrc = cms.untracked.InputTag("selectedPatJetsAK4PFCHS"),
                      #jetSrc = cms.untracked.InputTag("selectedPatJets"),
                      metSrc = cms.untracked.InputTag("slimmedMETs"),
                      #eleVetoIdMap    = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto"),
                      #eleLooseIdMap   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
                      #eleMediumIdMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium"),
                      #eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight"),
                      eleVetoIdMap    = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-veto"),
                      eleLooseIdMap   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-loose"),
                      eleMediumIdMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-medium"),
                      eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight"),
                      #phoLooseIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-loose"),
                      #phoMediumIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-medium"),
                      #phoTightIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-tight")
                      doGenParticles = cms.bool(True),
                      pileupCollection = cms.InputTag("addPileupInfo"),
                      #phoLooseIdMap = cms.InputTag('reducedEgammaBeforeGSFix','PhotonCutBasedIDLoose'),
                      #phoTightIdMap = cms.InputTag('reducedEgammaBeforeGSFix','PhotonCutBasedIDTight'),
                      #phoMediumIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring16-V2p2-medium")

)
