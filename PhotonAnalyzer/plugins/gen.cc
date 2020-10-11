#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "EGamma_RunIII_Variables_Studies/PhotonAnalyzer/plugins/PhotonAnalyzer.h"
#include "EGamma_RunIII_Variables_Studies/PhotonAnalyzer/plugins/genParticleParentage.h"

using namespace std;
float genWeight_;
Int_t            nPUInfo_;
vector<int>      nPU_;
vector<int>      puBX_;
vector<float>    puTrue_;
float            genPho1_;
float            genPho2_;
Int_t            nMC_;
vector<int>      mcPID;
vector<float>    mcVtx;
vector<float>    mcVty;
vector<float>    mcVtz;
vector<float>    mcPt;
vector<float>    mcMass;
vector<float>    mcEta;
vector<float>    mcPhi;
vector<float>    mcE;
vector<float>    mcEt;
vector<int>      mcGMomPID;
vector<int>      mcMomPID;
vector<float>    mcMomPt;
vector<float>    mcMomMass;
vector<float>    mcMomEta;
vector<float>    mcMomPhi;
//vector<int>      mcIndex;
vector<UShort_t> mcStatusFlag;
vector<int>      mcParentage;
vector<int> mcStatus;

void PhotonAnalyzer::branchesGenInfo(TTree* tree, edm::Service<TFileService> &fs) {
  //tree->Branch("genHT",         &genHT_);
  tree->Branch("genPho1",       &genPho1_);
  tree->Branch("genPho2", &genPho2_);
  tree->Branch("genWeight",     &genWeight_);
  tree->Branch("nPUInfo",       &nPUInfo_);
  tree->Branch("nPU",           &nPU_);
  tree->Branch("puBX",          &puBX_);
  tree->Branch("puTrue",        &puTrue_);

  hPU_        = fs->make<TH1F>("hPU",        "number of pileup",      200,  0, 200);
  hPUTrue_    = fs->make<TH1F>("hPUTrue",    "number of true pilepu", 1000, 0, 200);
  hGenWeight_ = fs->make<TH1F>("hGenWeight", "Gen weights",           2,    0, 2);
  hSumGenWeight_ = fs->make<TH1F>("hSumGenWeight", "Sum of Gen weights",1,  0, 1);
}

void PhotonAnalyzer::branchesGenPart(TTree* tree) {

  tree->Branch("nMC",          &nMC_);
  tree->Branch("mcPID",        &mcPID);
  tree->Branch("mcVtx",        &mcVtx);
  tree->Branch("mcVty",        &mcVty);
  tree->Branch("mcVtz",        &mcVtz);
  tree->Branch("mcPt",         &mcPt);
  tree->Branch("mcMass",       &mcMass);
  tree->Branch("mcEta",        &mcEta);
  tree->Branch("mcPhi",        &mcPhi);
  tree->Branch("mcE",          &mcE);
  tree->Branch("mcEt",         &mcEt);
  tree->Branch("mcGMomPID",    &mcGMomPID);
  tree->Branch("mcMomPID",     &mcMomPID);
  tree->Branch("mcMomPt",      &mcMomPt);
  tree->Branch("mcMomMass",    &mcMomMass);
  tree->Branch("mcMomEta",     &mcMomEta);
  tree->Branch("mcMomPhi",     &mcMomPhi);
  //tree->Branch("mcIndex",      &mcIndex);
  tree->Branch("mcStatusFlag", &mcStatusFlag); //-999:non W or Z, 1:hardronic, 2:e, 3:mu, 4:tau
  tree->Branch("mcParentage",  &mcParentage);  // 16*lepton + 8*boson + 4*non-prompt + 2*qcd + exotics
  tree->Branch("mcStatus", &mcStatus); // status of the particle
}
void PhotonAnalyzer::fillGenInfo(const edm::Event& e) {

  // cleanup from previous execution
  genWeight_ = -99;
  nPUInfo_ = 0;
  nPU_          .clear();
  puBX_         .clear();
  puTrue_ .clear();

  edm::Handle<GenEventInfoProduct> genEventInfoHandle;
  e.getByToken(generatorLabel_, genEventInfoHandle);

  if (genEventInfoHandle.isValid()) {
    //if (genEventInfoHandle->hasBinningValues())
    genWeight_ = genEventInfoHandle->weight();
    if (genWeight_ >= 0) hGenWeight_->Fill(0.5);    
    else hGenWeight_->Fill(1.5);
    if (abs(genWeight_)>1) hSumGenWeight_->Fill(0.5,genWeight_/abs(genWeight_));
    else hSumGenWeight_->Fill(0.5,genWeight_);
  } else  edm::LogWarning("PhotonAnalyzer") << "no GenEventInfoProduct in event";
  /*//////////////////////////////////////////////////////For QCD it was turned of as LHE collection is not present
  // access generator level HT  
  edm::Handle<LHEEventProduct> lheEventProduct;
  e.getByToken(lheEventLabel_, lheEventProduct);
  
  //double lheHt   = 0.;
  double lhePho1 = 0.;
  double lhePho2 = 0.;
  const lhef::HEPEUP& lheEvent = lheEventProduct->hepeup();
  std::vector<lhef::HEPEUP::FiveVector> lheParticles = lheEvent.PUP;
  size_t numParticles = lheParticles.size();
  int nMCPho = 0;
  for ( size_t idxParticle = 0; idxParticle < numParticles; ++idxParticle ) {
    int absPdgId = TMath::Abs(lheEvent.IDUP[idxParticle]);
    int status = lheEvent.ISTUP[idxParticle];
    // if (status == 1 && ((absPdgId >= 1 && absPdgId <= 6) || absPdgId == 21) ) { // quarks and gluons
    //  lheHt += TMath::Sqrt(TMath::Power(lheParticles[idxParticle][0], 2.) + TMath::Power(lheParticles[idxParticle][1], 2.)); // first entry is px, second py
    // } 
    if (status == 1 && absPdgId == 22 && nMCPho == 0) { // first photon
      lhePho1 = TMath::Sqrt(TMath::Power(lheParticles[idxParticle][0], 2.) + TMath::Power(lheParticles[idxParticle][1], 2.));
      nMCPho++;
    }
    if (status == 1 && absPdgId == 22 && nMCPho == 1) { // first photon
      lhePho2 = TMath::Sqrt(TMath::Power(lheParticles[idxParticle][0], 2.) + TMath::Power(lheParticles[idxParticle][1], 2.));
      nMCPho++;
    }
  }
  // genHT_   = lheHt;  
  genPho1_ = lhePho1;  
  genPho2_ = lhePho2;  
  */
  //For QCD it was turned of//////////////////////////////////////////////////////////////
 
  edm::Handle<vector<PileupSummaryInfo> > genPileupHandle;
  e.getByToken(puCollection_, genPileupHandle);
  if (genPileupHandle.isValid()) {
    for (vector<PileupSummaryInfo>::const_iterator pu = genPileupHandle->begin(); pu != genPileupHandle->end(); ++pu) {
      if (pu->getBunchCrossing() == 0) {
        hPU_->Fill(pu->getPU_NumInteractions());
        hPUTrue_->Fill(pu->getTrueNumInteractions());
      }

      nPU_   .push_back(pu->getPU_NumInteractions());
      puTrue_.push_back(pu->getTrueNumInteractions());
      puBX_  .push_back(pu->getBunchCrossing());

      nPUInfo_++;
    }
  }
  else
    edm::LogWarning("PhotonAnalyzer") << "no PileupSummaryInfo in event";
}

void PhotonAnalyzer::fillGenPart(const edm::Event& e) {

  // Fills tree branches with generated particle info.

  // cleanup from previous execution
  mcPID       .clear();
  mcVtx       .clear();
  mcVty       .clear();
  mcVtz       .clear();
  mcPt        .clear();
  mcMass      .clear();
  mcEta       .clear();
  mcPhi       .clear();
  mcE         .clear();
  mcEt        .clear();
  mcGMomPID   .clear();
  mcMomPID    .clear();
  mcMomPt     .clear();
  mcMomMass   .clear();
  mcMomEta    .clear();
  mcMomPhi    .clear();
  //mcIndex     .clear();
  mcStatusFlag.clear();
  mcParentage .clear();
  mcStatus .clear();
  nMC_ = 0;

  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  e.getByToken(genParticlesCollection_, genParticlesHandle);

  if (!genParticlesHandle.isValid()) {
    edm::LogWarning("PhotonAnalyzer") << "no reco::GenParticles in event";
    return;
  }

  int genIndex = 0;

  for (vector<reco::GenParticle>::const_iterator ip = genParticlesHandle->begin(); ip != genParticlesHandle->end(); ++ip) {
    genIndex++;

    int status = ip->status();
    //bool stableFinalStateParticle = status == 1 && ip->pt() > 5.0;
    
    bool quarks = abs(ip->pdgId())<7;

    // keep non-FSR photons with pT > 5.0 and all leptons with pT > 3.0;
    bool photonOrLepton =
      (ip->pdgId() == 22 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
      (status == 1 && abs(ip->pdgId()) == 11 && (ip->isPromptFinalState() || ip->isLastCopy())) || 
      (status == 1 && abs(ip->pdgId()) == 13 && (ip->isPromptFinalState() || ip->isLastCopy())) ||
      (status == 1 && (abs(ip->pdgId()) == 12 || abs(ip->pdgId()) == 14 || abs(ip->pdgId()) == 16)) ||
      (status == 1 && ( abs(ip->pdgId()) >= 11 && abs(ip->pdgId()) <= 16 ) && ip->pt() > 3.0)  ||
      (status < 10 && abs(ip->pdgId()) == 15 && ip->pt() > 3.0);
      
    // select also Z, W, H, top and b 
    bool heavyParticle =
      ((    ip->pdgId()  == 23 && ip->isHardProcess()) || 
       (abs(ip->pdgId()) == 24 && ip->isHardProcess()) || 
       (    ip->pdgId()  == 25 && ip->isHardProcess()) ||
       (abs(ip->pdgId()) ==  6 && ip->isHardProcess()) || 
       (abs(ip->pdgId()) ==  5 && ip->isHardProcess()));
    
    bool newParticle = false;
    for (size_t inp = 0; inp < newparticles_.size(); ++inp) {
      if (abs(ip->pdgId()) == newparticles_[inp]) newParticle = true;
    }
    
    if ( heavyParticle || photonOrLepton || quarks || newParticle ) {
      
      const reco::Candidate *p = (const reco::Candidate*)&(*ip);
      if (!runOnParticleGun_ && !p->mother()) continue;

      mcPID    .push_back(p->pdgId());
      mcVtx    .push_back(p->vx());
      mcVty    .push_back(p->vy());
      mcVtz    .push_back(p->vz());
      mcPt     .push_back(p->pt());
      mcMass   .push_back(p->mass());
      mcEta    .push_back(p->eta());
      mcPhi    .push_back(p->phi());
      mcE      .push_back(p->energy());
      mcEt     .push_back(p->et());
      mcStatus .push_back(p->status());
      
      UShort_t tmpStatusFlag = 0;
      if (ip->fromHardProcessFinalState()) setbit(tmpStatusFlag, 0);
      if (ip->isPromptFinalState())        setbit(tmpStatusFlag, 1);
      if (ip->isHardProcess())  setbit(tmpStatusFlag, 2);

      // if genParticle is W or Z, check its decay type
      if ( ip->pdgId() == 23 || abs(ip->pdgId()) == 24 ) {
        for (size_t k=0; k < p->numberOfDaughters(); ++k) {
          const reco::Candidate *dp = p->daughter(k);
          if (abs(dp->pdgId())<=6)                               setbit(tmpStatusFlag, 4);
          else if (abs(dp->pdgId())==11 || abs(dp->pdgId())==12) setbit(tmpStatusFlag, 5);
          else if (abs(dp->pdgId())==13 || abs(dp->pdgId())==14) setbit(tmpStatusFlag, 6);
          else if (abs(dp->pdgId())==15 || abs(dp->pdgId())==16) setbit(tmpStatusFlag, 7);
        }
      }
      if (ip->isLastCopy())  setbit(tmpStatusFlag, 8);
      mcStatusFlag.push_back(tmpStatusFlag);

      int mcGMomPID_ = -999;
      int mcMomPID_  = -999;
      float mcMomPt_    = -999.;
      float mcMomMass_  = -999.;
      float mcMomEta_   = -999.;
      float mcMomPhi_   = -999.;
      if (!runOnSherpa_) {
	
	reco::GenParticleRef partRef = reco::GenParticleRef(genParticlesHandle,
							    ip-genParticlesHandle->begin());
	genpartparentage::GenParticleParentage particleHistory(partRef);
	
	mcParentage.push_back(particleHistory.hasLeptonParent()*16   +
			      particleHistory.hasBosonParent()*8     +
			      particleHistory.hasNonPromptParent()*4 +
			      particleHistory.hasQCDParent()*2       +
			      particleHistory.hasExoticParent());      
	
	if ( particleHistory.hasRealParent() ) {
	  reco::GenParticleRef momRef = particleHistory.parent();
	  if ( momRef.isNonnull() && momRef.isAvailable() ) {
	    mcMomPID_  = momRef->pdgId();
	    mcMomPt_   = momRef->pt();
	    mcMomMass_ = momRef->mass();
	    mcMomEta_  = momRef->eta();
	    mcMomPhi_  = momRef->phi();
	        
	    // get Granny
	    genpartparentage::GenParticleParentage motherParticle(momRef);
	    if ( motherParticle.hasRealParent() ) {
	      reco::GenParticleRef granny = motherParticle.parent();
	      mcGMomPID_ = granny->pdgId();
	    }
	  }
	}
	mcGMomPID.push_back(mcGMomPID_);
	mcMomPID.push_back(mcMomPID_);
	mcMomPt.push_back(mcMomPt_);
	mcMomMass.push_back(mcMomMass_);
	mcMomEta.push_back(mcMomEta_);
	mcMomPhi.push_back(mcMomPhi_);
      }
      nMC_++;
    } // save info on particles of interest
  } // loop over gen-level particles

}
