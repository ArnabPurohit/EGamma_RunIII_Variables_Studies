#ifndef PhotonAnalyzer_h
#define PhotonAnalyzer_h
//############################################################################
// Date 6 Oct 2020
// Made by Arnab Purohit, Saha Institute of Nuclear Physics, Kolkata, India
// Following ggNtuplizer by cmkuo
//############################################################################


// system include files
#include <memory>
#include "TH1.h"//New
#include <string>
#include "TTree.h"
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "TMath.h"
#include "CondFormats/EcalObjects/interface/EcalPFRecHitThresholds.h"
#include "CondFormats/DataRecord/interface/EcalPFRecHitThresholdsRcd.h"


 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"
 #include "DataFormats/PatCandidates/interface/Photon.h"
 #include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.
using namespace std;
using namespace edm;

void setbit(UShort_t& x, UShort_t bit);
//using reco::TrackCollection;

class PhotonAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit PhotonAnalyzer(const edm::ParameterSet&);
      ~PhotonAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
      std::map<std::string,TH1F*> histContainer_;
      Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);

      const edm::EDGetToken barrelClusterToken_;
      const edm::EDGetToken endcapClusterToken_;
      const edm::EDGetToken barrelRecHitToken_;
      const edm::EDGetToken endcapRecHitToken_;

      edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
      edm::EDGetTokenT<edm::View<pat::Photon> > photonSrcToken_;
      //edm::EDGetTokenT<edm::ValueMap<bool> >  eleVetoIdMapToken_;
      //edm::EDGetTokenT<edm::ValueMap<bool> >  eleLooseIdMapToken_;
      //edm::EDGetTokenT<edm::ValueMap<bool> >  eleMediumIdMapToken_;
      //edm::EDGetTokenT<edm::ValueMap<bool> > eleTightIdMapToken_;
      
      //edm::EDGetTokenT<edm::ValueMap<bool> >  phoLooseIdMapToken_;
      //edm::EDGetTokenT<edm::ValueMap<bool> >  phoMediumIdMapToken_;
      //edm::EDGetTokenT<edm::ValueMap<bool> > phoTightIdMapToken_;
      


      //  edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
  //  edm::EDGetTokenT<edm::View<reco::GsfElectron> > eleToken_;
      //  edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
  //edm::EDGetTokenT<EcalRecHitCollection> EBRecHitCollectionT_;
  //edm::EDGetTokenT<EcalRecHitCollection> EERecHitCollectionT_;
  //edm::ESHandle<CaloTopology> theCaloTopology;
  //edm::EDGetTokenT<std::vector<PileupSummaryInfo> >     puCollection_;
      edm::EDGetTokenT<reco::VertexCollection> vtxLabel_;
      edm::EDGetTokenT<double>                         rhoLabel_;
      edm::EDGetTokenT<double> rhoCentralLabel_;
      TTree *tree_;
      TH1F    *hPU_;
      TH1F    *hPUTrue_;
      TH1F    *hGenWeight_;
      TH1F *hSumGenWeight_;
      TH1F *hnVtx;
      
      void branchesPhotons (TTree*);
      void branchesElectrons (TTree*);
      void branchesGlobalEvent (TTree*, edm::Service<TFileService>&);
      void branchesGenInfo (TTree*, edm::Service<TFileService>&);
      void branchesGenPart (TTree*);
      void fillGenPart (const edm::Event&);
      void fillGenInfo (const edm::Event&);
      void fillPhotons (const edm::Event&, const edm::EventSetup&);
      //void dumpBarrelThres(const EcalPFRecHitThresholds& thresholds,int iPhi);
      // void dumpEndcapThres(const EcalPFRecHitThresholds& thresholds,int iY, int iZ);
      //float applyBarrelThres(const EcalPFRecHitThresholds& thresholds,const EBDetId& detId);
      float applyBarrelThres(const EcalPFRecHitThresholds& thresholds,const EBDetId& detId, const EcalRecHitCollection& rechits);
      //float applyEndcapThres(const EcalPFRecHitThresholds& thresholds,const EEDetId& detId);
      float applyEndcapThres(const EcalPFRecHitThresholds& thresholds,const EEDetId& detId, const EcalRecHitCollection& rechits);
      void fillElectrons (const edm::Event&, const edm::EventSetup&, math::XYZPoint&);
      void fillGlobalEvent (const edm::Event&, const edm::EventSetup&);
      vector<int> newparticles_;
      bool doGenParticles_;
      bool runOnParticleGun_;
      bool runOnSherpa_;
      edm::EDGetTokenT<GenEventInfoProduct> generatorLabel_;
      edm::EDGetTokenT<LHEEventProduct>                lheEventLabel_;
      edm::EDGetTokenT<vector<reco::GenParticle> > genParticlesCollection_;
      edm::EDGetTokenT<vector<PileupSummaryInfo> > puCollection_;
      edm::EDGetTokenT<EcalRecHitCollection>           ebReducedRecHitCollection_;
      edm::EDGetTokenT<EcalRecHitCollection>           eeReducedRecHitCollection_;
      edm::EDGetTokenT<EcalRecHitCollection> esReducedRecHitCollection_;

};
#endif
