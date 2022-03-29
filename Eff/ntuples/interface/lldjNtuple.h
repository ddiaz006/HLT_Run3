#ifndef lldjNtuple_h
#define lldjNtuple_h

#include "TTree.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
#include "RecoTracker/Record/interface/NavigationSchoolRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/GeomPropagators/interface/StateOnTrackerBound.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "SimDataFormats/GeneratorProducts/interface/GenLumiInfoHeader.h"

using namespace std;

void setbit(UShort_t& x, UShort_t bit);

class lldjNtuple : public edm::EDAnalyzer {
 public:

  explicit lldjNtuple(const edm::ParameterSet&);
  ~lldjNtuple();

  //   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

 private:

  edm::ParameterSet lldj_pset_;

//  //   virtual void beginJob() {};
  virtual void beginRun(edm::Run const &, edm::EventSetup const&);//for trigger
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
//  //   virtual void endJob() {};
//
//  void branchesGlobalEvent (TTree*);
//  void branchesMET         (TTree*);
//  void branchesAODMET      (TTree*);
//  void branchesPhotons     (TTree*);
//  void branchesAODPhotons  (TTree*);
//  void branchesElectrons   (TTree*);
//  void branchesAODElectrons(TTree*);
//  void branchesMuons       (TTree*);
//  void branchesAODMuons    (TTree*);
//  void branchesJets        (TTree*);
  void branchesAODJets     (TTree*);
  void branchesTrigger     (TTree*);
  void branchesAODTrigger  (TTree*);
//  void branchesGenPart     (TTree*);
  void branchesAODEvent    (TTree*);
//
//  void fillGlobalEvent (const edm::Event&, const edm::EventSetup&);
//  void fillMET         (const edm::Event&, const edm::EventSetup&);
//  void fillAODMET      (const edm::Event&, const edm::EventSetup&);
//  void fillPhotons     (const edm::Event&, const edm::EventSetup&);
//  void fillAODPhotons  (const edm::Event&, const edm::EventSetup&);
//  void fillElectrons   (const edm::Event&, const edm::EventSetup&);
//  void fillAODElectrons(const edm::Event&, const edm::EventSetup&, const reco::Vertex);
//  void fillMuons       (const edm::Event&, const reco::Vertex);
//  void fillAODMuons    (const edm::Event&, const reco::Vertex);
//  void fillJets        (const edm::Event&, const edm::EventSetup&);
  void fillAODJets     (const edm::Event&, const edm::EventSetup&);
  void fillTrigger     (const edm::Event&, const edm::EventSetup&);
  void fillAODTrigger  (const edm::Event&, const edm::EventSetup&);
//  void fillGenPart     (const edm::Event&);
  void fillAODEvent    (const edm::Event&, const edm::EventSetup&);
//
//  bool isMediumMuonBCDEF(const reco::Muon & recoMu);
//  bool isMediumMuonGH(const reco::Muon & recoMu);
//
  bool doAOD_     ;
  bool doMiniAOD_ ;
  bool is2016_    ;
//
//  // collections
//  // electrons
//  edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
  edm::EDGetTokenT<double>                         rhoLabel_;
//  // elecontr ID decisions objects
//  edm::EDGetTokenT<edm::ValueMap<bool> >  eleVetoIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  eleLooseIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  eleMediumIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  eleTightIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  eleHLTIdMapToken_;
//
//  // AOD electrons
//  edm::EDGetToken electronAODToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> > AOD_eleLooseIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> > AOD_eleMediumIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> > AOD_eleTightIdMapToken_;
//  edm::EDGetTokenT<reco::ConversionCollection> conversionsAODToken_;
//
//  // global event
  edm::EDGetTokenT<double>                         rhoCentralLabel_;
//  edm::EDGetTokenT<vector<PileupSummaryInfo> >     puCollection_;
//  edm::EDGetTokenT<vector<PileupSummaryInfo> >     AODpuCollection_;
  edm::EDGetTokenT<reco::VertexCollection>         vtxLabel_;
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  string                                           trgResultsProcess_;
//
//  // beamspot
  edm::EDGetTokenT<reco::BeamSpot>                 beamspotLabel_;
//
//   // AOD Jets
  edm::EDGetTokenT<edm::View<reco::CaloJet> >       AODak4CaloJetsLabel_;
  edm::EDGetTokenT<edm::View<reco::CaloJet> >       AODak4CaloCorrectedJetsLabel_;
  edm::EDGetTokenT<reco::JetCorrector >  AODak4JetCorrectorLabel_;
  edm::EDGetTokenT<edm::View<reco::Vertex>  >      AODVertexLabel_;
  edm::EDGetTokenT<edm::View<reco::Track>  >       AODTrackLabel_;
  const MagneticField*                             magneticField_;
  edm::ESHandle<Propagator>                        thePropagator_;
  edm::ESHandle<TransientTrackBuilder>             theBuilder_;

  // jet functions
  vector<int> getJetTrackIndexs( float jeteta, float jetphi);
  void calculateAlphaMax( vector<int> jetTrackIDs,
   float& alphaMax, float& alphaMaxP, float& beta,
   float& alphaMax2, float& alphaMaxP2, float& beta2);
  void calculateTrackAngle( vector<int> jetTrackIDs,
   vector<float> &allTrackAngles,
   float &totalTrackAngle, float &totalTrackAnglePt);
  void calculateIP( vector<int> jetTrackIDs,
   vector<float> &jetIPs, vector<float> &jetIPSigs,
   float &sumIP, float &sumIPSig);

  float findMedian(vector<float> thevector);

  void calculateDisplacedVertices(const edm::EventSetup& es, vector<int> jetTrackIDs);

  void deltaVertex3D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dEta, double& dPhi, double& pt, double& m, double& energy);
  void deltaVertex2D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dPhi, double& pt, double& mediandPhi);
  vector<reco::TransientTrack> cleanTracks(vector<reco::TransientTrack> tracks, GlobalPoint vertPos);

//  //ctauWeight
//  Float_t calculatectauEventWeight(float dist);
//  // met
//  edm::EDGetTokenT<edm::TriggerResults>            patTrgResultsLabel_;
//  // for MET filters
//  edm::EDGetTokenT<bool> BadChCandFilterToken_;
//  edm::EDGetTokenT<bool> BadPFMuonFilterToken_;
//  edm::EDGetTokenT<edm::View<reco::CaloMET> >      AODCaloMETlabel_;
//
//  // muons
//  edm::EDGetTokenT<edm::View<pat::Muon> >          muonCollection_;
//  edm::EDGetTokenT<edm::View<pat::Muon> >          muonAODCollection_;
//
//
//  edm::EDGetToken photonAODCollection_;
//
//  // photon ID decision objects and isolations
//  edm::EDGetTokenT<edm::ValueMap<bool> >  phoLooseIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  phoMediumIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<bool> >  phoTightIdMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<float> > phoMVAValuesMapToken_;
//  edm::EDGetTokenT<edm::ValueMap<float> > phoChargedIsolationToken_;
//  edm::EDGetTokenT<edm::ValueMap<float> > phoNeutralHadronIsolationToken_;
//  edm::EDGetTokenT<edm::ValueMap<float> > phoPhotonIsolationToken_;
//  edm::EDGetTokenT<edm::ValueMap<float> > phoWorstChargedIsolationToken_;
//
//  // AOD photon ID
//  edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
//  edm::EDGetTokenT<edm::ValueMap<bool> > AOD_phoLooseIdMapToken_;
//  edm::InputTag AOD_phoLooseIdLabel_;
//
//  edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
//  edm::EDGetTokenT<edm::ValueMap<bool> > AOD_phoMediumIdMapToken_;
//  edm::InputTag AOD_phoMediumIdLabel_;
//
//  edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
//  edm::EDGetTokenT<edm::ValueMap<bool> > AOD_phoTightIdMapToken_;
//  edm::InputTag AOD_phoTightIdLabel_;
//
//  edm::Handle<edm::ValueMap<float> > AOD_phoChargedIsolationHandle_;
//  edm::EDGetTokenT<edm::ValueMap<float> > AOD_phoChargedIsolationMapToken_;
//  edm::InputTag AOD_phoChargedIsolationLabel_;
//
//  edm::Handle<edm::ValueMap<float> > AOD_phoNeutralHadronIsolationHandle_;
//  edm::EDGetTokenT<edm::ValueMap<float> > AOD_phoNeutralHadronIsolationMapToken_;
//  edm::InputTag AOD_phoNeutralHadronIsolationLabel_;
//
//  edm::Handle<edm::ValueMap<float> > AOD_phoPhotonIsolationHandle_;
//  edm::EDGetTokenT<edm::ValueMap<float> > AOD_phoPhotonIsolationMapToken_;
//  edm::InputTag AOD_phoPhotonIsolationLabel_;
//
//  edm::Handle<edm::ValueMap<float> > AOD_phoWorstChargedIsolationHandle_;
//  edm::EDGetTokenT<edm::ValueMap<float> > AOD_phoWorstChargedIsolationMapToken_;
//  edm::InputTag AOD_phoWorstChargedIsolationLabel_;
//
//
//  // trigger
  edm::EDGetTokenT<edm::TriggerResults>                     triggerBits_;
  edm::EDGetTokenT<edm::View<pat::TriggerObjectStandAlone>> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales>             triggerPrescales_;
  edm::InputTag AODTriggerLabel_;
  edm::EDGetTokenT<edm::TriggerResults> AODTriggerToken_;
  edm::InputTag AODTriggerEventLabel_;
  edm::EDGetTokenT<trigger::TriggerEvent> AODTriggerEventToken_;
  edm::Handle<edm::TriggerResults> AODTriggerHandle_;
  edm::Handle<trigger::TriggerEvent> AODTriggerEventHandle_;
  HLTConfigProvider hltConfig_;
  HLTPrescaleProvider hltPrescale_;
//
//
//  //gen
//  edm::EDGetTokenT<vector<reco::GenParticle> >     genParticlesCollection_;
//  edm::EDGetTokenT<GenEventInfoProduct> AODGenEventInfoLabel_;
//
//  edm::EDGetTokenT<GenLumiInfoHeader> genLumiHeaderToken_;
//
  TTree   *tree_;
  TH1F    *hEvents_;
//  TH1F    *hTTSF_;
//  TH1F    *hGenEventWeightSum_;
//  float   GenEventWeight;
//
//  JME::JetResolution            slimmedJetResolution_;
//  JME::JetResolutionScaleFactor slimmedJetResolutionSF_;
//
//  // shared between miniAOD jets and AOD jets modules
  edm::Handle<double>                 rhoHandle;
  edm::Handle<reco::VertexCollection> vtxHandle;
//
};

#endif
