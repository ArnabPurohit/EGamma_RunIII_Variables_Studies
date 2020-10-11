//############################################################################
// Date 6 Oct 2020
// Made by Arnab Purohit, Saha Institute of Nuclear Physics, Kolkata, India
// Following ggNtuplizer by cmkuo
//############################################################################

#include <TString.h>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "PhotonAnalyzer.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "GEDPhoIDTools.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"

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

using namespace std;
Int_t          nPho_;
vector<float>  phoE_;
vector<float>  phoEt_;
vector<float>  phoEta_;
vector<float> phoPhi_;
vector<int>  pho_genmatched_;
//vector<float>  phoCalibE_;
//vector<float> phoCalibEt_;
//vector<UShort_t> phoIDbit_;
vector<int>    phohasPixelSeed_;
vector<int>    phoEleVeto_;
vector<float>  phoR9_;
vector<float>  phoSCE_;
vector<float>  phoSCRawE_;
vector<float>  phoESEnP1_;
vector<float>  phoESEnP2_;
vector<float>  phoSCEta_;
vector<float>  phoSCPhi_;
vector<float>  phoSCEtaWidth_;
vector<float>  phoSCPhiWidth_;
vector<float>  phoSCBrem_;
vector<float>  phoE1x3_;
vector<float>  phoE1x5_;
vector<float>  phoE2x2_;
vector<float>  phoE2x5Max_;
vector<float>  phoE5x5_;
vector<float>  phoE3x3_;

vector<float>  phoE1x3Full5x5_;
vector<float>  phoE1x5Full5x5_;
vector<float>  phoE2x2Full5x5_;
vector<float>  phoE2x5MaxFull5x5_;
vector<float>  phoE5x5Full5x5_;
vector<float>  phoE3x3Full5x5_;
vector<float>  phoE3x3Full5x5_withPFThr_;
//ClusterTools
vector<float>  phoE1x3Full5x5_CT_;
vector<float>  phoE1x5Full5x5_CT_;
vector<float>  phoE2x2Full5x5_CT_;
vector<float>  phoE2x5MaxFull5x5_CT_;
vector<float>  phoE5x5Full5x5_CT_;
vector<float>  phoE3x3Full5x5_CT_;
//=================================

vector<float> phoHoverE_;
vector<float>  phoSigmaIEtaIEtaFull5x5_;
vector<float>  phoSigmaIEtaIPhiFull5x5_;
vector<float> phoSigmaIPhiIPhiFull5x5_;
vector<float> phoR9Full5x5_;

//Necessary for the Photon Footprint removal
template <class T, class U>
bool isInFootprint(const T& thefootprint, const U& theCandidate) {
  for ( auto itr = thefootprint.begin(); itr != thefootprint.end(); ++itr ) {

    if( itr.key() == theCandidate.key() ) return true;
    
  }
  return false;
}


void PhotonAnalyzer::branchesPhotons(TTree* tree) {
  
  tree->Branch("nPho",   &nPho_);
  tree->Branch("phoE",   &phoE_);
  tree->Branch("phoEt",  &phoEt_);
  tree->Branch("phoEta", &phoEta_);
  tree->Branch("phoPhi", &phoPhi_);
  tree->Branch("pho_genmatched",         &pho_genmatched_);
  //tree->Branch("phoCalibE", &phoCalibE_);
  //tree->Branch("phoCalibEt", &phoCalibEt_);
  // tree->Branch("phoIDbit", &phoIDbit_);
  tree->Branch("phoSCE",                  &phoSCE_);
  tree->Branch("phoSCRawE",               &phoSCRawE_);
  tree->Branch("phoESEnP1",               &phoESEnP1_);
  tree->Branch("phoESEnP2",               &phoESEnP2_);
  tree->Branch("phoSCEta",                &phoSCEta_);
  tree->Branch("phoSCPhi",                &phoSCPhi_);
  tree->Branch("phoSCEtaWidth",           &phoSCEtaWidth_);
  tree->Branch("phoSCPhiWidth",           &phoSCPhiWidth_);
  tree->Branch("phoSCBrem",               &phoSCBrem_);
  tree->Branch("phoE1x3",                 &phoE1x3_);
  tree->Branch("phoE1x5",                 &phoE1x5_);
  tree->Branch("phoE2x2",                 &phoE2x2_);
  tree->Branch("phoE2x5Max",              &phoE2x5Max_);
  tree->Branch("phoE5x5",                 &phoE5x5_);
  tree->Branch("phoE3x3",                 &phoE3x3_);
  tree->Branch("phoE1x3Full5x5",          &phoE1x3Full5x5_);
  tree->Branch("phoE1x5Full5x5",          &phoE1x5Full5x5_);
  tree->Branch("phoE2x2Full5x5",          &phoE2x2Full5x5_);
  tree->Branch("phoE2x5MaxFull5x5",       &phoE2x5MaxFull5x5_);
  tree->Branch("phoE5x5Full5x5",          &phoE5x5Full5x5_);
  tree->Branch("phoE3x3Full5x5",          &phoE3x3Full5x5_);
  tree->Branch("phoE3x3Full5x5_withPFThr",                 &phoE3x3Full5x5_withPFThr_);
  //ClusterTools
  tree->Branch("phoE1x3Full5x5_CT",          &phoE1x3Full5x5_CT_);
  tree->Branch("phoE1x5Full5x5_CT",          &phoE1x5Full5x5_CT_);
  tree->Branch("phoE2x2Full5x5_CT",          &phoE2x2Full5x5_CT_);
  tree->Branch("phoE2x5MaxFull5x5_CT",       &phoE2x5MaxFull5x5_CT_);
  tree->Branch("phoE5x5Full5x5_CT",          &phoE5x5Full5x5_CT_);
  tree->Branch("phoE3x3Full5x5_CT",          &phoE3x3Full5x5_CT_);
  //===========================================================

  tree->Branch("phohasPixelSeed",         &phohasPixelSeed_);
  tree->Branch("phoEleVeto",              &phoEleVeto_);
  tree->Branch("phoR9",                   &phoR9_);
  tree->Branch("phoHoverE", &phoHoverE_);
  tree->Branch("phoSigmaIEtaIEtaFull5x5", &phoSigmaIEtaIEtaFull5x5_);
  tree->Branch("phoSigmaIEtaIPhiFull5x5", &phoSigmaIEtaIPhiFull5x5_);
  tree->Branch("phoSigmaIPhiIPhiFull5x5", &phoSigmaIPhiIPhiFull5x5_);
  tree->Branch("phoR9Full5x5", &phoR9Full5x5_);
}

float PhotonAnalyzer::applyBarrelThres(const EcalPFRecHitThresholds& thresholds,const EBDetId& detId, const EcalRecHitCollection& rechits)
{
  //EBDetId& tmpid(detId.ieta(),detId.iphi());
  //  for(detId.ieta() = -85; detId.ieta() <= 85; ++detId.ieta()){
  //std::cout<<"Seed Crystal iEta: "<<detId.ieta()<<"iPhi: "<<detId.iphi()<<std::endl;
  float thrTot = 0.0;
  for(int ie = -1;ie<2;ie++){
    for(int ip = -1;ip<2;ip++){
      //if(ie==0) continue;
      EBDetId tmpid(detId.ieta()+ie,detId.iphi()+ip);
      if(tmpid.iphi()<1 || tmpid.iphi()>360 || tmpid.ieta()<-85 || tmpid.ieta()>85){
	//std::cout<<"Not in Barrel ***************************************************************"<<std::endl;
	return -999;
      }
      EcalRecHitCollection::const_iterator theHit = rechits.find(tmpid);
      auto thresItr =  thresholds.find(tmpid);
      if(thresItr == thresholds.end()){
	std::cout <<"pfrechit thres "<<" warning missing threshold for "<<tmpid.ieta()<<" "<<tmpid.iphi()<<std::endl;
	return -999;
      }else{
	//std::cout <<"pfrechit thres "<<" detId.ieta(): "<<tmpid.ieta()<<" detId.iphi() "<<tmpid.iphi()<<" : "<<*thresItr<<std::endl;
	if (theHit != rechits.end()) {
	  if((*theHit).energy()>(*thresItr)){
	    thrTot = thrTot+(*theHit).energy();
	    //std::cout<<"Sum Thresold = "<<thrTot<<std::endl;
	  }
	  else{std::cout<<"Thresold = "<<(*thresItr)<<" Hit energy"<< (*theHit).energy()<<std::endl;}
	}
	else{return -999;}
      }
    }
  }
  return thrTot;
}

float PhotonAnalyzer::applyEndcapThres(const EcalPFRecHitThresholds& thresholds,const EEDetId& detId, const EcalRecHitCollection& rechits)
{
  float thrTot = 0.0;
  for(int iX = -1; iX <= 1; iX++){
    for(int iY = -1; iY <= 1; iY++){
      EEDetId tmpid(detId.ix()+iX,detId.iy()+iY,detId.zside());
      if(!EEDetId::validDetId(tmpid.ix(),tmpid.iy(),tmpid.zside())){
	std::cout<<"This detId is not valid ***********************************************"<<std::endl;
	return -999.;
      }
      if(tmpid.iy()<1 || tmpid.iy()>100 ||tmpid.ix()<1 || tmpid.ix()>100 ){
	return -999.;
      }
      EcalRecHitCollection::const_iterator theHit = rechits.find(tmpid);
      auto thresItr =  thresholds.find(tmpid);
      if(thresItr == thresholds.end()){
	std::cout <<"pfrechit thres "<<"warning missing threshold for "<<tmpid.ix()<<" "<<tmpid.iy()<<" "<<tmpid.zside()<<std::endl;
	return -999;
      }else{
	//std::cout <<"pfrechit thres "<<"tmpid.ix(): "<<tmpid.ix()<<" tmpid.iy() "<<tmpid.iy()<<" tmpid.zside() "<<tmpid.zside()<<" : "<<*thresItr<<std::endl;
	if (theHit != rechits.end()) {
	  if((*theHit).energy()>(*thresItr)){
	    thrTot = thrTot+(*theHit).energy();
	    //std::cout<<"Sum Thresold = "<<thrTot<<std::endl;
	  }
	  else{std::cout<<"Thresold = "<<(*thresItr)<<" Hit energy"<< (*theHit).energy()<<std::endl;}
	}
	else{return -999;}
      }
    }
  }
  return thrTot;
}


void PhotonAnalyzer::fillPhotons(const edm::Event& e, const edm::EventSetup& es) {
  phoE_.clear();
  phoEt_.clear();
  phoEta_.clear();
  phoPhi_.clear();
  pho_genmatched_.clear();
  // phoCalibE_.clear();
  // phoCalibEt_.clear();
  // phoIDbit_.clear();
  phoSCE_               .clear();
  phoSCRawE_            .clear();
  phoESEnP1_            .clear();
  phoESEnP2_            .clear();
  phoSCEta_             .clear();
  phoSCPhi_             .clear();
  phoSCEtaWidth_        .clear();
  phoSCPhiWidth_        .clear();
  phoSCBrem_            .clear();
  phoE1x3_              .clear();
  phoE1x5_              .clear();
  phoE2x2_              .clear();
  phoE2x5Max_           .clear();
  phoE5x5_              .clear();
  phoE3x3_              .clear();
  phoE1x3Full5x5_       .clear();
  phoE1x5Full5x5_       .clear();
  phoE2x2Full5x5_       .clear();
  phoE2x5MaxFull5x5_    .clear();
  phoE5x5Full5x5_       .clear();
  phoE3x3Full5x5_       .clear();
  phoE3x3Full5x5_withPFThr_    .clear();
  //ClusterTools
  phoE1x3Full5x5_CT_       .clear();
  phoE1x5Full5x5_CT_       .clear();
  phoE2x2Full5x5_CT_       .clear();
  phoE2x5MaxFull5x5_CT_    .clear();
  phoE5x5Full5x5_CT_       .clear();
  phoE3x3Full5x5_CT_       .clear();
  //===================================
  phohasPixelSeed_      .clear();
  phoEleVeto_           .clear();
  phoR9_                .clear();
  phoHoverE_ .clear();
  phoSigmaIEtaIEtaFull5x5_.clear();
  phoSigmaIEtaIPhiFull5x5_.clear();
  phoSigmaIPhiIPhiFull5x5_.clear();
  phoR9Full5x5_ .clear();

  nPho_ = 0;
  edm::Handle<edm::View<pat::Photon> > photonHandle;
  e.getByToken(photonSrcToken_, photonHandle);




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
  // edm::Handle<edm::View<pat::Photon> > calibphotonHandle;
  // e.getByToken(calibphotonCollection_, calibphotonHandle);
  /*  
  edm::Handle<edm::ValueMap<bool> >  loose_id_decisions;
  edm::Handle<edm::ValueMap<bool> >  medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> > tight_id_decisions;

  e.getByToken(phoLooseIdMapToken_ ,  loose_id_decisions);
  e.getByToken(phoMediumIdMapToken_,  medium_id_decisions);
  e.getByToken(phoTightIdMapToken_ , tight_id_decisions);
  */
  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  e.getByToken(genParticlesCollection_, genParticlesHandle);

  EcalClusterLazyTools       lazyTool    (e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  GEDPhoIDTools* GEDIdTool = NULL;


  for (edm::View<pat::Photon>::const_iterator iPho = photonHandle->begin(); iPho != photonHandle->end(); ++iPho) {
    //if (iPho->et()<50) continue;
    //Float_t corrPt = -1;
    //Float_t corrEn = -1;

    /*    for (edm::View<pat::Photon>::const_iterator iCPho = calibphotonHandle->begin(); iCPho != calibphotonHandle->end(); ++iCPho) {
      if (fabs(iPho->eta() - iCPho->eta()) < 0.001 && fabs(iPho->phi() - iCPho->phi()) < 0.001) {
	corrPt = iCPho->pt();
	corrEn = iCPho->energy();
      }
    }
    phoCalibEt_       .push_back(corrPt);
    phoCalibE_ .push_back(corrEn);
    */
    const auto pho = photonHandle->ptrAt(nPho_);

    int genmatched=0;
    float PFthrE3x3=0.0;
    if (genParticlesHandle.isValid()) {
      for (std::vector<reco::GenParticle>::const_iterator ip = genParticlesHandle->begin(); ip != genParticlesHandle->end(); ++ip) {
	const reco::Candidate *p = (const reco::Candidate*)&(*ip);
	//      if ( (p->status()==1) && abs(p->pdgId() == 11) ) std::cout << "dR = " << reco::deltaR(ele,*p) << " ele pt = " << ele.pt() << " gen pt = " << p->pt() <<std::endl;
	if ( (p->status()==1) && (ip->isPromptFinalState()) && abs(p->pdgId()) == 22 ) {
	  if ( ((reco::deltaR(*iPho,*p))<0.04) && ((iPho->pt()/p->pt())>0.7) &&   ((iPho->pt()/p->pt())<1.3) ) genmatched=1;
	}  
      }
    }
    pho_genmatched_.push_back(genmatched);

    const reco::SuperCluster& superClus = *((*iPho).superCluster());
    const reco::CaloCluster &seedCluster = *superClus.seed();
    const bool iseb = seedCluster.hitsAndFractions()[0].first.subdetId() == EcalBarrel;
    const bool isee = seedCluster.hitsAndFractions()[0].first.subdetId() == EcalEndcap;
    const DetId seedId = superClus.seed()->seed();
    /* float n_Cluster = 0;
    //    for (reco::CaloCluster_iterator cluster = superClus.clustersBegin(); cluster != superClus.clustersEnd(); cluster++) {
    //    for(CaloClusterPtrVector::const_iterator cluster = superClus.clustersBegin(); cluster != superClus.clustersEnd(); ++cluster){
    for(reco::CaloCluster_iterator clusterit = superClus.clustersBegin(); clusterit != superClus.clustersEnd(); ++clusterit){
      n_Cluster = n_Cluster+1;
      //const CaloClusterPtr cluster = *clusterit; //was working but giving ptrVector error for a event and crashing
      reco::CaloClusterPtr cluster = *clusterit;
      std::cout << "----- new cluster -----" << std::endl;
      //std::cout << "----------------- size: " << cluster.size() << " energy: " << cluster.energy() << std::endl;
      std::cout<<cluster->energy()<<" is the energy of the "<<nPho_<<"th photon in cluster "<<n_Cluster<<std::endl;
    }
    */

    /*
    reco::CaloCluster_iterator it = superClus.clustersBegin();
    reco::CaloCluster_iterator itend = superClus.clustersEnd();
    for (; it != itend; ++it) {
      reco::CaloCluster cluster(**it);
      std::cout << "----- new cluster -----" << std::endl;
      //std::cout << "----------------- size: " << cluster.size() << " energy: " << cluster.energy() << std::endl;
      std::cout<<cluster.energy()<<" is the energy of the "<<nPho_<<"th photon in cluster "<<n_Cluster<<std::endl;
      
    }
    */
    if(iseb){
      PFthrE3x3=applyBarrelThres(*thresHandle,seedId,*ebRecHits);
      // std::cout<<"This electron PF rechit Thresold in 3x3 is "<<PFthrE3x3<<std::endl;

    }

    if(isee){
      PFthrE3x3=applyEndcapThres(*thresHandle,seedId,*eeRecHits);
      //std::cout<<"This electron PF rechit Thresold in 3x3 is "<<PFthrE3x3<<std::endl;

    }



    // UShort_t tmpphoIDbit = 0;
    phoE_             .push_back(iPho->energy());
    phoEt_            .push_back(iPho->et());
    phoEta_           .push_back(iPho->eta());
    phoPhi_           .push_back(iPho->phi());
    phoSCE_           .push_back((*iPho).superCluster()->energy());
    phoSCRawE_        .push_back((*iPho).superCluster()->rawEnergy());
    phoESEnP1_        .push_back((*iPho).superCluster()->preshowerEnergyPlane1());
    phoESEnP2_        .push_back((*iPho).superCluster()->preshowerEnergyPlane2());
    phoSCEta_         .push_back((*iPho).superCluster()->eta());
    phoSCPhi_         .push_back((*iPho).superCluster()->phi());
    phoSCEtaWidth_    .push_back((*iPho).superCluster()->etaWidth());
    phoSCPhiWidth_    .push_back((*iPho).superCluster()->phiWidth());
    phoSCBrem_        .push_back((*iPho).superCluster()->phiWidth()/(*iPho).superCluster()->etaWidth());
    phoE1x3_          .push_back(lazyTool.e1x3(*((*iPho).superCluster()->seed())));
    phoE1x5_          .push_back(iPho->e1x5());
    phoE2x2_          .push_back(lazyTool.e2x2(*((*iPho).superCluster()->seed())));
    phoE2x5Max_       .push_back(iPho->e2x5());
    phoE5x5_          .push_back(iPho->e5x5());
    phoE3x3_          .push_back(iPho->e3x3());
    phohasPixelSeed_  .push_back((Int_t)iPho->hasPixelSeed());
    phoEleVeto_       .push_back((Int_t)iPho->passElectronVeto());
    phoR9_            .push_back(iPho->r9());
    phoHoverE_ .push_back(iPho->hadTowOverEm());

    std::vector<float> vCov = lazyToolnoZS.localCovariances( *((*iPho).superCluster()->seed()) );
    //const float see = (isnan(vCov[0]) ? 0. : sqrt(vCov[0]));
    const float spp = (isnan(vCov[2]) ? 0. : sqrt(vCov[2]));
    const float sep = vCov[1];
    phoE1x3Full5x5_          .push_back(lazyToolnoZS.e1x3(*((*iPho).superCluster()->seed())));
    phoE1x5Full5x5_          .push_back(iPho->full5x5_e1x5());
    phoE2x2Full5x5_          .push_back(lazyToolnoZS.e2x2(*((*iPho).superCluster()->seed())));
    phoE2x5MaxFull5x5_       .push_back(iPho->full5x5_e2x5());
    phoE5x5Full5x5_          .push_back(iPho->full5x5_e5x5());
    phoE3x3Full5x5_          .push_back(iPho->full5x5_e3x3());
    //phoE3x3Full5x5_withPFThr_       .push_back(lazyToolnoZS.e3x3(*((*iPho).superCluster()->seed()))-PFthrE3x3);
    std::cout<<"CMSSW Full5x5 E3x3 = "<<iPho->full5x5_e3x3()<<" and CMSSW E3x3 = "<< iPho->e3x3() <<" My Full5x5 E3x3 woth PF Rechit thresold "<<PFthrE3x3<<std::endl;
    phoE3x3Full5x5_withPFThr_       .push_back(PFthrE3x3);
   //Clustertools version
    if(iseb){
      phoE1x3Full5x5_CT_          .push_back(ClusterTools::e1x3(seedCluster, ebRecHits, topology));
      phoE1x5Full5x5_CT_       .push_back(ClusterTools::e1x5(seedCluster, ebRecHits, topology));
      phoE2x2Full5x5_CT_          .push_back(ClusterTools::e2x2(seedCluster, ebRecHits, topology));
      phoE2x5MaxFull5x5_CT_       .push_back(ClusterTools::e2x5Max(seedCluster, ebRecHits, topology));
      phoE5x5Full5x5_CT_          .push_back(ClusterTools::e5x5(seedCluster, ebRecHits, topology));
      phoE3x3Full5x5_CT_          .push_back(ClusterTools::e3x3(seedCluster, ebRecHits, topology));
    }
    else{
      phoE1x3Full5x5_CT_          .push_back(ClusterTools::e1x3(seedCluster, eeRecHits, topology));
      phoE1x5Full5x5_CT_       .push_back(ClusterTools::e1x5(seedCluster, eeRecHits, topology));
      phoE2x2Full5x5_CT_          .push_back(ClusterTools::e2x2(seedCluster, eeRecHits, topology));
      phoE2x5MaxFull5x5_CT_       .push_back(ClusterTools::e2x5Max(seedCluster, eeRecHits, topology));
      phoE5x5Full5x5_CT_          .push_back(ClusterTools::e5x5(seedCluster, eeRecHits, topology));
      phoE3x3Full5x5_CT_          .push_back(ClusterTools::e3x3(seedCluster, eeRecHits, topology));
    }
    //==============================================================
    phoSigmaIEtaIEtaFull5x5_ .push_back(iPho->full5x5_sigmaIetaIeta());
    phoSigmaIEtaIPhiFull5x5_ .push_back(sep);
    phoSigmaIPhiIPhiFull5x5_ .push_back(spp);
    phoR9Full5x5_ .push_back(iPho->full5x5_r9());
    /*  
    bool isPassLoose  = (*loose_id_decisions)[pho];
    if(isPassLoose) setbit(tmpphoIDbit, 0);
    
    bool isPassMedium = (*medium_id_decisions)[pho];
    if(isPassMedium) setbit(tmpphoIDbit, 1);
    
    bool isPassTight  = (*tight_id_decisions)[pho];
    if(isPassTight) setbit(tmpphoIDbit, 2);
    phoIDbit_.push_back(tmpphoIDbit); 
    */
    nPho_++; 
  }
  if (GEDIdTool) delete GEDIdTool;
}
