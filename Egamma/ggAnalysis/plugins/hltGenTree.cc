#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;
using namespace edm;
ggNtuplizer::ggNtuplizer(const edm::ParameterSet& ps) //:
//  hltPrescaleProvider_(ps, consumesCollector(), *this)
{
  vtxLabel_             = consumes<reco::VertexCollection>(ps.getParameter<InputTag>("VtxLabel"));
  vtxBSLabel_           = consumes<reco::VertexCollection>(ps.getParameter<InputTag>("VtxBSLabel"));
  rhoLabel_             = consumes<double>                (ps.getParameter<InputTag>("rhoLabel"));
  rhoCentralLabel_      = consumes<double>                (ps.getParameter<InputTag>("rhoCentralLabel"));
  trgEventLabel_        = consumes<trigger::TriggerEvent> (ps.getParameter<InputTag>("triggerEvent"));
  triggerObjectsLabel_  = consumes<pat::TriggerObjectStandlection>(ps.getParameter<edm::InputTag>("triggerEvent"));
  trgResultsLabel_      = consumes<edm::TriggerResults>   (ps.getParameter<InputTag>("triggerResults"));
  patTrgResultsLabel_   = consumes<edm::TriggerResults>   (ps.getParameter<InputTag>("patTriggerResults"));
  trgResultsProcess_    =                                  ps.getParameter<InputTag>("triggerResults").process();
  generatorLabel_       = consumes<GenEventInfoProduct>   (ps.getParameter<InputTag>("generatorLabel"));
  lheEventLabel_        = consumes<LHEEventProduct>       (ps.getParameter<InputTag>("LHEEventLabel"));
  puCollection_         = consumes<vector<PileupSummaryInfo> >(ps.getParameter<InputTag>("pileupCollection"));
  genParticlesCollection_ = consumes<vector<reco::GenParticle> >(ps.getParameter<InputTag>("genParticleSrc"));
  pfMETlabel_             = consumes<View<pat::MET> >           (ps.getParameter<InputTag>("pfMETLabel"));
  electronCollection_     = consumes<View<pat::Electron> >      (ps.getParameter<InputTag>("electronSrc"));
  gsfTracks_              = consumes<View<reco::GsfTrack>>      (ps.getParameter<InputTag>("gsfTrackSrc"));
  BadChCandFilterToken_   = consumes<bool>        (ps.getParameter<InputTag>("BadChargedCandidateFilter"));
  BadPFMuonFilterToken_   = consumes<bool>       (ps.getParameter<edm::InputTag>("BadPFMuonFilter"));

  photonCollection_       = consumes<View<pat::Photon> >  (ps.getParameter<InputTag>("photonSrc"));
  muonCollection_         = consumes<View<pat::Muon> >    (ps.getParameter<InputTag>("muonSrc"));
ebReducedRecHitCollection_= consumes<EcalRecHitCollection>(ps.getParameter<InputTag>("ebReducedRecHitCollection"));
eeReducedRecHitCollection_= consumes<EcalRecHitCollection>(ps.getParameter<InputTag>("eeReducedRecHitCollection"));
esReducedRecHitCollection_= consumes<EcalRecHitCollection>(ps.getParameter<InputTag>("esReducedRecHitCollection"));
  recophotonCollection_   = consumes<reco::PhotonCollection>     (ps.getParameter<InputTag>("recoPhotonSrc"));
  tracklabel_             = consumes<reco::TrackCollection>      (ps.getParameter<InputTag>("TrackLabel"));
  gsfElectronlabel_       = consumes<reco::GsfElectronCollection>(ps.getParameter<InputTag>("gsfElectronLabel"));
  tauCollection_          = consumes<vector<pat::Tau> >          (ps.getParameter<InputTag>("tauSrc"));
  pfAllParticles_         = consumes<reco::PFCandidateCollection>(ps.getParameter<InputTag>("PFAllCandidates"));
pckPFCandidateCollection_ = consumes<pat::PackedCandidateCollection>(ps.getParameter<InputTag>("packedPFCands"));
  pckPFCdsLabel_          = consumes<vector<pat::PackedCandidate>>  (ps.getParameter<InputTag>("packedPFCands"));
  recoCdsLabel_           = consumes<View<reco::Candidate>>         (ps.getParameter<InputTag>("packedPFCands"));
  jetsAK4Label_           = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak4JetSrc"));
  jetsAK8Label_           = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak8JetSrc"));
  //boostedDoubleSVLabel_ = consumes<reco::JetTagCollection>        (ps.getParameter<InputTag>("boostedDoubleSVLabel"));

  Service<TFileService> fs;
  tree_    = fs->make<TTree>("hltGenTree", "reco vs hlt");
  branchesGlobalEvent(tree_);

  if (doGenParticles_) {
    branchesGenInfo(tree_, fs);
    branchesGenPart(tree_);
  }
  branchesElectrons(tree_);
}
ggNtuplizer::~ggNtuplizer() {}

void ggNtuplizer::analyze(const edm::Event& e, const edm::EventSetup& es) {
  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);

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
  initTriggerFilters(e);
  fillGlobalEvent(e, es);

  if (!e.isRealData()) {
    fillGenInfo(e);
    if (doGenParticles_)
      fillGenPart(e);
  }
  fillElectrons(e, es, pv);
  tree_->Fill();
}

DEFINE_FWK_MODULE(hltGenTree);

