#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "Geometry/Records/interface/CaloTopologyRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloEventSetup/plugins/CaloTopologyBuilder.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloTopology/interface/CaloSubdetectorTopology.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "CondFormats/EcalObjects/interface/EcalPFRecHitThresholds.h"
#include "CondFormats/DataRecord/interface/EcalPFRecHitThresholdsRcd.h"
#include "PhotonAnalyzer.h"
#include "DataFormats/Common/interface/ValueMap.h"
using namespace std;
using namespace reco;

// (local) variables associated with tree branches
Int_t          nEle_;
vector<int> eleCharge_;
vector<int>  ele_genmatched_;
vector<float> eleEn_;
vector<float>  elePt_;
vector<float>  eleEta_;
vector<float>  elePhi_;
vector<float>  eleR9_;
//vector<float>  eleCalibPt_;
//vector<float>  eleCalibEn_;
vector<float>  eleSCEta_;
vector<float>  eleSCPhi_;
vector<float>  eleSCRawEn_;
vector<float>  eleSCEtaWidth_;
vector<float>  eleSCPhiWidth_;
vector<float>  eleHoverE_;
vector<float>  eleEoverP_;
vector<float>  eleEoverPout_;
vector<float>  eleEoverPInv_;
vector<float> eleBrem_;
vector<float>  eleSigmaIEtaIEtaFull5x5_;
vector<float>  eleSigmaIPhiIPhiFull5x5_;
vector<int> eleConvVeto_;
vector<float> eleR9Full5x5_;
//vector<UShort_t> eleIDbit_;
vector<float>  eleE1x3_;
vector<float>  eleE1x5_;
vector<float>  eleE2x2_;
vector<float>  eleE2x5Max_;
vector<float>  eleE5x5_;
vector<float>  eleE3x3_;

vector<float>  eleE5x5_withPFThr_;
vector<float>  eleE3x3Full5x5_withPFThr_;


vector<float>  eleE1x3Full5x5_;
vector<float>  eleE1x5Full5x5_;
vector<float>  eleE2x2Full5x5_;
vector<float>  eleE2x5MaxFull5x5_;
vector<float>  eleE5x5Full5x5_;
vector<float>  eleE3x3Full5x5_;
//ClusterTools
vector<float>  eleE1x3Full5x5_CT_;
vector<float>  eleE1x5Full5x5_CT_;
vector<float>  eleE2x2Full5x5_CT_;
vector<float>  eleE2x5MaxFull5x5_CT_;
vector<float>  eleE5x5Full5x5_CT_;
vector<float>  eleE3x3Full5x5_CT_;
//=================================


void PhotonAnalyzer::branchesElectrons(TTree* tree) {

  tree->Branch("nEle",                    &nEle_);
  tree->Branch("eleCharge", &eleCharge_);
  tree->Branch("eleEn", &eleEn_);
  tree->Branch("elePt",                   &elePt_);
  tree->Branch("eleEta",                  &eleEta_);
  tree->Branch("elePhi",                  &elePhi_);
  tree->Branch("eleR9",                   &eleR9_);
  // tree->Branch("eleCalibPt",              &eleCalibPt_);
  // tree->Branch("eleCalibEn",              &eleCalibEn_);
  tree->Branch("ele_genmatched",         &ele_genmatched_);
  tree->Branch("eleSCEta",                &eleSCEta_);
  tree->Branch("eleSCPhi",                &eleSCPhi_);
  tree->Branch("eleSCRawEn",              &eleSCRawEn_);
  tree->Branch("eleSCEtaWidth",           &eleSCEtaWidth_);
  tree->Branch("eleSCPhiWidth",           &eleSCPhiWidth_);
  tree->Branch("eleHoverE",               &eleHoverE_);
  tree->Branch("eleEoverP",               &eleEoverP_);
  tree->Branch("eleEoverPout",            &eleEoverPout_);
  tree->Branch("eleEoverPInv",            &eleEoverPInv_);
  tree->Branch("eleBrem", &eleBrem_);
  tree->Branch("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5_);
  tree->Branch("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5_);
  tree->Branch("eleConvVeto", &eleConvVeto_);
  tree->Branch("eleR9Full5x5", &eleR9Full5x5_);
  //tree->Branch("eleIDbit", &eleIDbit_);
  tree->Branch("eleE1x3",                 &eleE1x3_);
  tree->Branch("eleE1x5",                 &eleE1x5_);
  tree->Branch("eleE2x2",                 &eleE2x2_);
  tree->Branch("eleE2x5Max",              &eleE2x5Max_);
  tree->Branch("eleE5x5",                 &eleE5x5_);
  tree->Branch("eleE3x3",                 &eleE3x3_);

  tree->Branch("eleE5x5_withPFThr",                 &eleE5x5_withPFThr_);
  tree->Branch("eleE3x3Full5x5_withPFThr",                 &eleE3x3Full5x5_withPFThr_);

  tree->Branch("eleE1x3Full5x5",          &eleE1x3Full5x5_);
  tree->Branch("eleE1x5Full5x5",          &eleE1x5Full5x5_);
  tree->Branch("eleE2x2Full5x5",          &eleE2x2Full5x5_);
  tree->Branch("eleE2x5MaxFull5x5",       &eleE2x5MaxFull5x5_);
  tree->Branch("eleE5x5Full5x5",          &eleE5x5Full5x5_);
  tree->Branch("eleE3x3Full5x5",          &eleE3x3Full5x5_);
  //ClusterTools
  tree->Branch("eleE1x3Full5x5_CT",          &eleE1x3Full5x5_CT_);
  tree->Branch("eleE1x5Full5x5_CT",          &eleE1x5Full5x5_CT_);
  tree->Branch("eleE2x2Full5x5_CT",          &eleE2x2Full5x5_CT_);
  tree->Branch("eleE2x5MaxFull5x5_CT",       &eleE2x5MaxFull5x5_CT_);
  tree->Branch("eleE5x5Full5x5_CT",          &eleE5x5Full5x5_CT_);
  tree->Branch("eleE3x3Full5x5_CT",          &eleE3x3Full5x5_CT_);
  //===========================================================

}


void PhotonAnalyzer::fillElectrons(const edm::Event &e, const edm::EventSetup &es, math::XYZPoint &pv) {
    
  // cleanup from previous execution
  eleCharge_ .clear();
  ele_genmatched_.clear();
  eleEn_ .clear();
  elePt_                      .clear();
  eleEta_                     .clear();
  elePhi_                     .clear();
  eleR9_                      .clear();
  // eleCalibPt_                 .clear();
  // eleCalibEn_                 .clear();
  eleSCEta_                   .clear();
  eleSCPhi_                   .clear();
  eleSCRawEn_                 .clear();
  eleSCEtaWidth_              .clear();
  eleSCPhiWidth_              .clear();
  eleHoverE_                  .clear();
  eleEoverP_                  .clear();
  eleEoverPout_               .clear();
  eleEoverPInv_               .clear();
  eleBrem_ .clear();
  eleSigmaIEtaIEtaFull5x5_    .clear();
  eleSigmaIPhiIPhiFull5x5_    .clear();
  eleConvVeto_ .clear();
  eleR9Full5x5_ .clear();
  // eleIDbit_ .clear();
  eleE1x3_              .clear();
  eleE1x5_              .clear();
  eleE2x2_              .clear();
  eleE2x5Max_           .clear();
  eleE5x5_              .clear();
  eleE3x3_              .clear();

  eleE5x5_withPFThr_    .clear();
  eleE3x3Full5x5_withPFThr_    .clear();


  eleE1x3Full5x5_       .clear();
  eleE1x5Full5x5_       .clear();
  eleE2x2Full5x5_       .clear();
  eleE2x5MaxFull5x5_    .clear();
  eleE5x5Full5x5_       .clear();
  eleE3x3Full5x5_       .clear();
  //ClusterTools
  eleE1x3Full5x5_CT_       .clear();
  eleE1x5Full5x5_CT_       .clear();
  eleE2x2Full5x5_CT_       .clear();
  eleE2x5MaxFull5x5_CT_    .clear();
  eleE5x5Full5x5_CT_       .clear();
  eleE3x3Full5x5_CT_       .clear();
  //===================================


  nEle_ = 0;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++






  using ClusterTools = noZS::EcalClusterTools;



  edm::Handle<EcalRecHitCollection> pEBRecHits;
  e.getByToken(barrelRecHitToken_, pEBRecHits);
  const EcalRecHitCollection* ebRecHits = pEBRecHits.product();

  edm::Handle<EcalRecHitCollection> pEERecHits;
  e.getByToken(endcapRecHitToken_, pEERecHits);
  const EcalRecHitCollection* eeRecHits = pEERecHits.product();

  edm::Handle<reco::BasicClusterCollection> pEBClusters;
  e.getByToken(barrelClusterToken_, pEBClusters);
  const reco::BasicClusterCollection* ebClusters = pEBClusters.product();

  edm::Handle<reco::BasicClusterCollection> pEEClusters;
  e.getByToken(endcapClusterToken_, pEEClusters);
  const reco::BasicClusterCollection* eeClusters = pEEClusters.product();

  edm::ESHandle<CaloGeometry> pGeometry;
  es.get<CaloGeometryRecord>().get(pGeometry);
  const CaloGeometry* geometry = pGeometry.product();

  edm::ESHandle<CaloTopology> pTopology;
  es.get<CaloTopologyRecord>().get(pTopology);
  const CaloTopology* topology = pTopology.product();

  edm::ESHandle<EcalPFRecHitThresholds> thresHandle;
  es.get<EcalPFRecHitThresholdsRcd>().get(thresHandle);
  /*
  dumpBarrelThres(*thresHandle,1);
  dumpEndcapThres(*thresHandle,50,1);
  */

  /*
  std::cout << "========== BARREL ==========" << std::endl;
  for (auto const& clus : *ebClusters) {
    DetId maxId = ClusterTools::getMaximum(clus, eeRecHits).first;

    std::cout << "----- new cluster -----" << std::endl;
    std::cout << "----------------- size: " << clus.size() << " energy: " << clus.energy() << std::endl;

    std::cout << "e1x3..................... " << ClusterTools::e1x3(clus, ebRecHits, topology) << std::endl;
    std::cout << "e3x1..................... " << ClusterTools::e3x1(clus, ebRecHits, topology) << std::endl;
    std::cout << "e1x5..................... " << ClusterTools::e1x5(clus, ebRecHits, topology) << std::endl;
    std::cout << "e5x1..................... " << ClusterTools::e5x1(clus, ebRecHits, topology) << std::endl;
    std::cout << "e2x2..................... " << ClusterTools::e2x2(clus, ebRecHits, topology) << std::endl;
    std::cout << "e3x3..................... " << ClusterTools::e3x3(clus, ebRecHits, topology) << std::endl;
    std::cout << "e4x4..................... " << ClusterTools::e4x4(clus, ebRecHits, topology) << std::endl;
    std::cout << "e5x5..................... " << ClusterTools::e5x5(clus, ebRecHits, topology) << std::endl;
    std::cout << "n5x5..................... " << ClusterTools::n5x5(clus, eeRecHits, topology) << std::endl;
    std::cout << "e2x5Right................ " << ClusterTools::e2x5Right(clus, ebRecHits, topology) << std::endl;
    std::cout << "e2x5Left................. " << ClusterTools::e2x5Left(clus, ebRecHits, topology) << std::endl;
    std::cout << "e2x5Top.................. " << ClusterTools::e2x5Top(clus, ebRecHits, topology) << std::endl;
    std::cout << "e2x5Bottom............... " << ClusterTools::e2x5Bottom(clus, ebRecHits, topology) << std::endl;
    std::cout << "e2x5Max.................. " << ClusterTools::e2x5Max(clus, ebRecHits, topology) << std::endl;
    std::cout << "eMax..................... " << ClusterTools::eMax(clus, ebRecHits) << std::endl;
    std::cout << "e2nd..................... " << ClusterTools::e2nd(clus, ebRecHits) << std::endl;
    std::vector<float> vEta = ClusterTools::energyBasketFractionEta(clus, ebRecHits);
    std::cout << "energyBasketFractionEta..";
    for (auto const& eta : vEta)
      std::cout << " " << eta;
    std::cout << std::endl;
    std::vector<float> vPhi = ClusterTools::energyBasketFractionPhi(clus, ebRecHits);
    std::cout << "energyBasketFractionPhi..";
    for (auto const& phi : vPhi)
      std::cout << " " << phi;
    std::cout << std::endl;
    std::vector<float> vLat = ClusterTools::lat(clus, ebRecHits, geometry);
    std::cout << "lat...................... " << vLat[0] << " " << vLat[1] << " " << vLat[2] << std::endl;
    std::vector<float> vCov = ClusterTools::covariances(clus, ebRecHits, topology, geometry);
    std::cout << "covariances.............. " << vCov[0] << " " << vCov[1] << " " << vCov[2] << std::endl;
    std::vector<float> vLocCov = ClusterTools::localCovariances(clus, ebRecHits, topology);
    std::cout << "local covariances........ " << vLocCov[0] << " " << vLocCov[1] << " " << vLocCov[2] << std::endl;
    std::cout << "zernike20................ " << ClusterTools::zernike20(clus, ebRecHits, geometry) << std::endl;
    std::cout << "zernike42................ " << ClusterTools::zernike42(clus, ebRecHits, geometry) << std::endl;
    std::cout << "nrSaturatedCrysIn5x5..... " << ClusterTools::nrSaturatedCrysIn5x5(maxId, ebRecHits, topology)
              << std::endl;
  }

  std::cout << "========== ENDCAPS ==========" << std::endl;
  for (auto const& clus : *eeClusters) {
    DetId maxId = ClusterTools::getMaximum(clus, eeRecHits).first;

    std::cout << "----- new cluster -----" << std::endl;
    std::cout << "----------------- size: " << clus.size() << " energy: " << clus.energy() << std::endl;

    std::cout << "e1x3..................... " << ClusterTools::e1x3(clus, eeRecHits, topology) << std::endl;
    std::cout << "e3x1..................... " << ClusterTools::e3x1(clus, eeRecHits, topology) << std::endl;
    std::cout << "e1x5..................... " << ClusterTools::e1x5(clus, eeRecHits, topology) << std::endl;
    std::cout << "e5x1..................... " << ClusterTools::e5x1(clus, eeRecHits, topology) << std::endl;
    std::cout << "e2x2..................... " << ClusterTools::e2x2(clus, eeRecHits, topology) << std::endl;
    std::cout << "e3x3..................... " << ClusterTools::e3x3(clus, eeRecHits, topology) << std::endl;
    std::cout << "e4x4..................... " << ClusterTools::e4x4(clus, eeRecHits, topology) << std::endl;
    std::cout << "e5x5..................... " << ClusterTools::e5x5(clus, eeRecHits, topology) << std::endl;
    std::cout << "n5x5..................... " << ClusterTools::n5x5(clus, eeRecHits, topology) << std::endl;
    std::cout << "e2x5Right................ " << ClusterTools::e2x5Right(clus, eeRecHits, topology) << std::endl;
    std::cout << "e2x5Left................. " << ClusterTools::e2x5Left(clus, eeRecHits, topology) << std::endl;
    std::cout << "e2x5Top.................. " << ClusterTools::e2x5Top(clus, eeRecHits, topology) << std::endl;
    std::cout << "e2x5Bottom............... " << ClusterTools::e2x5Bottom(clus, eeRecHits, topology) << std::endl;
    std::cout << "eMax..................... " << ClusterTools::eMax(clus, eeRecHits) << std::endl;
    std::cout << "e2nd..................... " << ClusterTools::e2nd(clus, eeRecHits) << std::endl;
    std::vector<float> vLat = ClusterTools::lat(clus, eeRecHits, geometry);
    std::cout << "lat...................... " << vLat[0] << " " << vLat[1] << " " << vLat[2] << std::endl;
    std::vector<float> vCov = ClusterTools::covariances(clus, eeRecHits, topology, geometry);
    std::cout << "covariances.............. " << vCov[0] << " " << vCov[1] << " " << vCov[2] << std::endl;
    std::vector<float> vLocCov = ClusterTools::localCovariances(clus, eeRecHits, topology);
    std::cout << "local covariances........ " << vLocCov[0] << " " << vLocCov[1] << " " << vLocCov[2] << std::endl;
    std::cout << "zernike20................ " << ClusterTools::zernike20(clus, eeRecHits, geometry) << std::endl;
    std::cout << "zernike42................ " << ClusterTools::zernike42(clus, eeRecHits, geometry) << std::endl;
    std::cout << "nrSaturatedCrysIn5x5..... " << ClusterTools::nrSaturatedCrysIn5x5(maxId, eeRecHits, topology)
              << std::endl;
  }
  */




















  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  EcalClusterLazyTools       lazyTool    (e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  
  //using ClusterTools = EcalClusterToolsT<true>;
  noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  //  ClusterTools = EcalClusterToolsT<true>;     std::vector<float> localCovariances = ClusterTools::localCovariances(seedCluster, recHits, topology);
  edm::Handle<edm::View<pat::Electron> > electronHandle;
  e.getByToken(electronCollection_, electronHandle);

  // edm::Handle<edm::View<pat::Electron> > calibelectronHandle;
  // e.getByToken(calibelectronCollection_, calibelectronHandle);
  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  e.getByToken(genParticlesCollection_, genParticlesHandle);


  /*
   edm::Handle<edm::ValueMap<bool> >  veto_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  loose_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> > tight_id_decisions;

  e.getByToken(eleVetoIdMapToken_ ,         veto_id_decisions);
  e.getByToken(eleLooseIdMapToken_ ,        loose_id_decisions);
  e.getByToken(eleMediumIdMapToken_,        medium_id_decisions);
  e.getByToken(eleTightIdMapToken_, tight_id_decisions);
  */

  for (edm::View<pat::Electron>::const_iterator iEle = electronHandle->begin(); iEle != electronHandle->end(); ++iEle) {
    //  Float_t corrPt = -1;
    // Float_t corrEn = -1;
    /* for (edm::View<pat::Electron>::const_iterator iCEle = calibelectronHandle->begin(); iCEle != calibelectronHandle->end(); ++iCEle) {

      if (fabs(iEle->eta() - iCEle->eta()) < 0.001 && fabs(iEle->phi() - iCEle->phi()) < 0.001) {
	corrPt = iCEle->pt();
	corrEn = iCEle->energy();
      }
    }
    
    eleCalibPt_        .push_back(corrPt);
    eleCalibEn_        .push_back(corrEn);
    */
    int genmatched=0;
    float PFthrE3x3=0.0;
    if (genParticlesHandle.isValid()) {
      for (std::vector<reco::GenParticle>::const_iterator ip = genParticlesHandle->begin(); ip != genParticlesHandle->end(); ++ip) {
	const reco::Candidate *p = (const reco::Candidate*)&(*ip);
	//      if ( (p->status()==1) && abs(p->pdgId() == 11) ) std::cout << "dR = " << reco::deltaR(ele,*p) << " ele pt = " << ele.pt() << " gen pt = " << p->pt() <<std::endl;
	if ( (p->status()==1) && abs(p->pdgId()) == 11 ) {
	  if ( ((reco::deltaR(*iEle,*p))<0.04) && ((iEle->pt()/p->pt())>0.7) &&   ((iEle->pt()/p->pt())<1.3) ) genmatched=1;
	}  
      }
    }
    ele_genmatched_.push_back(genmatched);

    const reco::SuperCluster& superClus = *((*iEle).superCluster());
    const reco::CaloCluster &seedCluster = *superClus.seed();
    const bool iseb = seedCluster.hitsAndFractions()[0].first.subdetId() == EcalBarrel;
    const bool isee = seedCluster.hitsAndFractions()[0].first.subdetId() == EcalEndcap;
    const DetId seedId = superClus.seed()->seed();
    if(iseb){
      PFthrE3x3=applyBarrelThres(*thresHandle,seedId, *ebRecHits);
      //std::cout<<"This electron PF rechit Thresold in 3x3 is "<<PFthrE3x3<<std::endl;

    }

    if(isee){
      PFthrE3x3=applyEndcapThres(*thresHandle,seedId, *eeRecHits);
      // std::cout<<"This electron PF rechit Thresold in 3x3 is "<<PFthrE3x3<<std::endl;

    }

    eleCharge_.push_back(iEle->charge());
    eleEn_.push_back(iEle->energy());
    elePt_              .push_back(iEle->pt());
    eleEta_             .push_back(iEle->eta());
    elePhi_             .push_back(iEle->phi());
    eleR9_              .push_back(iEle->r9());

    eleSCEta_           .push_back(iEle->superCluster()->eta());
    eleSCPhi_           .push_back(iEle->superCluster()->phi());
    eleSCRawEn_         .push_back(iEle->superCluster()->rawEnergy());
    eleSCEtaWidth_      .push_back(iEle->superCluster()->etaWidth());
    eleSCPhiWidth_      .push_back(iEle->superCluster()->phiWidth());
    eleHoverE_ .push_back(iEle->hcalOverEcal());
    eleEoverP_          .push_back(iEle->eSuperClusterOverP());
    eleEoverPout_       .push_back(iEle->eEleClusterOverPout());
    eleBrem_ .push_back(iEle->fbrem());
    eleConvVeto_ .push_back((Int_t)iEle->passConversionVeto()); // ConvVtxFit || missHit == 0
    eleE1x3_          .push_back(lazyTool.e1x3(*((*iEle).superCluster()->seed())));
    eleE1x5_          .push_back(iEle->e1x5());
    eleE2x2_          .push_back(lazyTool.e2x2(*((*iEle).superCluster()->seed())));
    eleE2x5Max_       .push_back(iEle->e2x5Max());
    eleE5x5_          .push_back(iEle->e5x5());
    //eleE3x3_          .push_back(iEle->e3x3());
    eleE3x3_          .push_back(lazyTool.e3x3(*((*iEle).superCluster()->seed())));
    //eleE3x3_          .push_back();
    eleE1x3Full5x5_          .push_back(lazyToolnoZS.e1x3(*((*iEle).superCluster()->seed())));
    eleE1x5Full5x5_          .push_back(iEle->full5x5_e1x5());
    eleE2x2Full5x5_          .push_back(lazyToolnoZS.e2x2(*((*iEle).superCluster()->seed())));
    eleE2x5MaxFull5x5_       .push_back(iEle->full5x5_e2x5Max());
    eleE5x5Full5x5_          .push_back(iEle->full5x5_e5x5());
    //eleE3x3Full5x5_          .push_back(iEle->full5x5_e3x3());
    eleE3x3Full5x5_          .push_back(lazyToolnoZS.e3x3(*((*iEle).superCluster()->seed())));
    eleE3x3Full5x5_withPFThr_       .push_back(lazyToolnoZS.e3x3(*((*iEle).superCluster()->seed()))-PFthrE3x3);
    //Clustertools version
    if(iseb){
      eleE1x3Full5x5_CT_          .push_back(ClusterTools::e1x3(seedCluster, ebRecHits, topology));
      eleE1x5Full5x5_CT_       .push_back(ClusterTools::e1x5(seedCluster, ebRecHits, topology));
      eleE2x2Full5x5_CT_          .push_back(ClusterTools::e2x2(seedCluster, ebRecHits, topology));
      eleE2x5MaxFull5x5_CT_       .push_back(ClusterTools::e2x5Max(seedCluster, ebRecHits, topology));
      eleE5x5Full5x5_CT_          .push_back(ClusterTools::e5x5(seedCluster, ebRecHits, topology));
      eleE3x3Full5x5_CT_          .push_back(ClusterTools::e3x3(seedCluster, ebRecHits, topology));
    }
    else{
      eleE1x3Full5x5_CT_          .push_back(ClusterTools::e1x3(seedCluster, eeRecHits, topology));
      eleE1x5Full5x5_CT_       .push_back(ClusterTools::e1x5(seedCluster, eeRecHits, topology));
      eleE2x2Full5x5_CT_          .push_back(ClusterTools::e2x2(seedCluster, eeRecHits, topology));
      eleE2x5MaxFull5x5_CT_       .push_back(ClusterTools::e2x5Max(seedCluster, eeRecHits, topology));
      eleE5x5Full5x5_CT_          .push_back(ClusterTools::e5x5(seedCluster, eeRecHits, topology));
      eleE3x3Full5x5_CT_          .push_back(ClusterTools::e3x3(seedCluster, eeRecHits, topology));
    }
    // VID calculation of (1/E - 1/p)
    if (iEle->ecalEnergy() == 0)   eleEoverPInv_.push_back(1e30);
    else if (!std::isfinite(iEle->ecalEnergy()))  eleEoverPInv_.push_back(1e30);
    else eleEoverPInv_.push_back((1.0 - iEle->eSuperClusterOverP())/iEle->ecalEnergy());

    eleSigmaIEtaIEtaFull5x5_    .push_back(iEle->full5x5_sigmaIetaIeta());
    eleSigmaIPhiIPhiFull5x5_ .push_back(iEle->full5x5_sigmaIphiIphi());
    eleR9Full5x5_ .push_back(iEle->full5x5_r9());
    /*
      const auto el = electronHandle->ptrAt(nEle_);
    
    UShort_t tmpeleIDbit = 0;
    
    ///el->electronID("cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-veto") also works

    bool isPassVeto  = (*veto_id_decisions)[el];
    if (isPassVeto) setbit(tmpeleIDbit, 0);
    
    bool isPassLoose  = (*loose_id_decisions)[el];
    if (isPassLoose) setbit(tmpeleIDbit, 1);
    
    bool isPassMedium = (*medium_id_decisions)[el];
    if (isPassMedium) setbit(tmpeleIDbit, 2);
    
    bool isPassTight  = (*tight_id_decisions)[el];
    if (isPassTight) setbit(tmpeleIDbit, 3);
    eleIDbit_.push_back(tmpeleIDbit);
    */
    nEle_++;
  }

}
