#include "FWCore/MessageLogger/interface/MessageLogger.h"
//#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
//#include "FWCore/Common/interface/TriggerNames.h"
#include "PhotonAnalyzer.h"


using namespace std;

// (local) variables associated with tree branches
Int_t       run_;
Long64_t    event_;
Int_t       lumis_;
Bool_t      isData_;
Int_t       nVtx_;
Int_t       nGoodVtx_;
Int_t       nTrksPV_;
Bool_t      isPVGood_;
float       vtx_;
float       vty_;
float       vtz_;
float       rho_;
float       rhoCentral_;


void PhotonAnalyzer::branchesGlobalEvent(TTree* tree, edm::Service<TFileService> &fs) {

  tree->Branch("run",     &run_);
  tree->Branch("event",   &event_);
  tree->Branch("lumis",   &lumis_);
  tree->Branch("isData",  &isData_);
  tree->Branch("nVtx",    &nVtx_);
  tree->Branch("nGoodVtx",&nGoodVtx_);
  tree->Branch("nTrksPV", &nTrksPV_);
  tree->Branch("isPVGood",&isPVGood_);
  tree->Branch("vtx",     &vtx_); 
  tree->Branch("vty",     &vty_); 
  tree->Branch("vtz",     &vtz_); 
  tree->Branch("rho",     &rho_);
  tree->Branch("rhoCentral", &rhoCentral_);
  hnVtx = fs->make<TH1F>("hnVtx", "number of RECO Vtx", 200, 0, 200);
}

void PhotonAnalyzer::fillGlobalEvent(const edm::Event& e, const edm::EventSetup& es) {

  edm::Handle<double> rhoHandle;
  e.getByToken(rhoLabel_, rhoHandle);

  edm::Handle<double> rhoCentralHandle;
  e.getByToken(rhoCentralLabel_, rhoCentralHandle);

  run_    = e.id().run();
  event_  = e.id().event();
  lumis_  = e.luminosityBlock();
  isData_ = e.isRealData();
  rho_    = *(rhoHandle.product());
  if (rhoCentralHandle.isValid()) rhoCentral_ = *(rhoCentralHandle.product());
  else rhoCentral_ = -99.;

  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);
  
  nVtx_     = -1;
  nGoodVtx_ = -1;
  if (vtxHandle.isValid()) {
    nVtx_     = 0;
    nGoodVtx_ = 0;    

    for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {

      if (nVtx_ == 0) {
	nTrksPV_ = v->nTracks();
	vtx_     = v->x();
	vty_     = v->y();
	vtz_     = v->z();

	isPVGood_ = false;
	if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) isPVGood_ = true;
      }

      if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) nGoodVtx_++;
      nVtx_++;

    }
    hnVtx->Fill(nVtx_);
  } else
    edm::LogWarning("PhotonAnalyzer") << "Primary vertices info not unavailable";

}
Double_t PhotonAnalyzer::deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2) {

  Double_t dEta, dPhi ;
  dEta = eta1 - eta2;
  dPhi = deltaPhi(phi1, phi2);

  return sqrt(dEta*dEta+dPhi*dPhi);
}
