// -*- C++ -*-
//
// Package:    EGamma_RunIII_Variables_Studies/PhotonAnalyzer
// Class:      PhotonAnalyzer
//
/**\class PhotonAnalyzer PhotonAnalyzer.cc EGamma_RunIII_Variables_Studies/PhotonAnalyzer/plugins/PhotonAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Arnab Purohit
//         Created:  Wed, 09 Oct 2019 09:34:33 GMT
//
//


#include "PhotonAnalyzer.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.
using namespace std;
using namespace edm;
void setbit(UShort_t& x, UShort_t bit) {
  UShort_t a = 1;
  x |= (a << bit);
}

PhotonAnalyzer::PhotonAnalyzer(const edm::ParameterSet& iConfig)
 :
  histContainer_(),
  //  tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))
  barrelClusterToken_(consumes<reco::BasicClusterCollection>(iConfig.getParameter<edm::InputTag>("barrelClusterCollection"))),
  endcapClusterToken_(consumes<reco::BasicClusterCollection>(iConfig.getParameter<edm::InputTag>("endcapClusterCollection"))),
  barrelRecHitToken_(consumes<EcalRecHitCollection>(iConfig.getParameter<edm::InputTag>("barrelRecHitCollection"))),
  endcapRecHitToken_(consumes<EcalRecHitCollection>(iConfig.getParameter<edm::InputTag>("endcapRecHitCollection"))),

  electronCollection_(consumes<edm::View<pat::Electron> >(iConfig.getUntrackedParameter<edm::InputTag>("electronSrc"))),
  photonSrcToken_(consumes<edm::View<pat::Photon> >(iConfig.getUntrackedParameter<edm::InputTag>("photonSrc")))

{
   //now do what ever initialization is needed
  doGenParticles_ = iConfig.getParameter<bool>("doGenParticles");
  runOnParticleGun_          = iConfig.getParameter<bool>("runOnParticleGun");
  runOnSherpa_ = iConfig.getParameter<bool>("runOnSherpa");
  puCollection_ = consumes<vector<PileupSummaryInfo> > (iConfig.getParameter<InputTag>("pileupCollection"));
  generatorLabel_ = consumes<GenEventInfoProduct> (iConfig.getParameter<InputTag>("generatorLabel"));
  vtxLabel_ = consumes<reco::VertexCollection> (iConfig.getParameter<InputTag>("VtxLabel"));
  rhoLabel_                  = consumes<double>(iConfig.getParameter<InputTag>("rhoLabel"));
  rhoCentralLabel_ = consumes<double> (iConfig.getParameter<InputTag>("rhoCentralLabel"));
  // lheEventLabel_ = consumes<LHEEventProduct> (iConfig.getParameter<edm::InputTag>("LHEEventLabel")); ///For QCD turned off as the collection is not present
  genParticlesCollection_ = consumes<vector<reco::GenParticle> > (iConfig.getParameter<edm::InputTag>("genParticleSrc"));
  
    ebReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (iConfig.getParameter<edm::InputTag>("ebReducedRecHitCollection"));
  eeReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (iConfig.getParameter<edm::InputTag>("eeReducedRecHitCollection"));
  esReducedRecHitCollection_ = consumes<EcalRecHitCollection> (iConfig.getParameter<edm::InputTag>("esReducedRecHitCollection")); 
  /*  eleVetoIdMapToken_       = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleVetoIdMap"));
  eleLooseIdMapToken_      = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleLooseIdMap"));
  eleMediumIdMapToken_     = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"));
  eleTightIdMapToken_      = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleTightIdMap"));
  phoLooseIdMapToken_             = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoLooseIdMap"));
  phoMediumIdMapToken_            = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoMediumIdMap"));
  phoTightIdMapToken_             = consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("phoTightIdMap"));
  */

  newparticles_ = iConfig.getParameter< vector<int > >("newParticles");
  usesResource("TFileService");
  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("PhotonAnalyzer_Tree", "Event data");
  branchesGlobalEvent(tree_, fs);
  if (doGenParticles_) {
    branchesGenInfo(tree_, fs);
    branchesGenPart(tree_);
  }

  
  branchesElectrons(tree_);
  branchesPhotons(tree_);

}


PhotonAnalyzer::~PhotonAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
PhotonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::Handle<reco::VertexCollection> vtxHandle;
   iEvent.getByToken(vtxLabel_, vtxHandle);

   reco::Vertex vtx;

   // best-known primary vertex coordinates
   math::XYZPoint pv(0, 0, 0);
   for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {
     // replace isFake() for miniAOD since it requires tracks while miniAOD vertices don't have tracks:
     // Vertex.h: bool isFake() const {return (chi2_==0 && ndof_==0 && tracks_.empty());}
     bool isFake = (v->chi2() == 0 && v->ndof() == 0);

     if (!isFake) {
       pv.SetXYZ(v->x(), v->y(), v->z());
       vtx = *v;
       break;
     }
   }
   fillGlobalEvent(iEvent, iSetup);

   if (!iEvent.isRealData()) {
     fillGenInfo(iEvent);
     if (doGenParticles_)
       fillGenPart(iEvent);
   }

   // get photon collection                                                                                    
   edm::Handle<edm::View<pat::Photon> > photons;
   iEvent.getByToken(photonSrcToken_,photons);

   //fillElectrons(iEvent,iSetup, pv); //Uncomment this to fill electron variables
   fillPhotons(iEvent,iSetup);

   tree_->Fill();

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
PhotonAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
PhotonAnalyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PhotonAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PhotonAnalyzer);
