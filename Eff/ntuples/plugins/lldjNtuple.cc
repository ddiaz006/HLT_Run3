#include "HLT_Run3/Eff/ntuples/interface/lldjNtuple.h"
#include <vector>


using namespace std;
using namespace edm;

void setbit(UShort_t& x, UShort_t bit) {
  UShort_t a = 1;
  x |= (a << bit);
}

lldjNtuple::lldjNtuple(const edm::ParameterSet& ps) :
  hltPrescale_(ps,consumesCollector(),*this)
{

  // choose AOD or miniAOD or both
  doAOD_                   = ps.getParameter<bool>("doAOD");
  doMiniAOD_               = ps.getParameter<bool>("doMiniAOD");
  is2016_                  = ps.getParameter<bool>("is2016");

  rhoLabel_                = consumes<double>               (ps.getParameter<InputTag>("rhoLabel"));
//  rhoCentralLabel_         = consumes<double>                        (ps.getParameter<InputTag>("rhoCentralLabel"));
  vtxLabel_                = consumes<reco::VertexCollection>        (ps.getParameter<InputTag>("VtxLabel"));
  AODVertexLabel_          = consumes<edm::View<reco::Vertex> >      (ps.getParameter<InputTag>("AODVertexSrc"));
  trgResultsLabel_         = consumes<edm::TriggerResults>           (ps.getParameter<InputTag>("triggerResults"));
  trgResultsProcess_       =                                          ps.getParameter<InputTag>("triggerResults").process();
//  // beamspot
//  beamspotLabel_           = consumes<reco::BeamSpot>                (ps.getParameter<InputTag>("beamspotLabel_"));
//
//  // jets
//  //jetsAK4Label_            = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak4JetSrc"));
//  //AODjetsAK4Label_         = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak4JetSrc"));
//  AODak4CaloJetsLabel_              = consumes<View<reco::CaloJet> >         (ps.getParameter<InputTag>("AODak4CaloJetsSrc"));
//  AODak4CaloCorrectedJetsLabel_     = consumes<View<reco::CaloJet> >         (ps.getParameter<InputTag>("AODak4CorrCaloJetsSrc"));
//  AODak4JetCorrectorLabel_          = consumes< reco::JetCorrector >   (ps.getParameter<InputTag>("AODak4CorrectorLabelName"));
//  //AODak4PFJetsLabel_       = consumes<View<reco::PFJet>   >          (ps.getParameter<InputTag>("AODak4PFJetsSrc"));
//  //AODak4PFJetsCHSLabel_    = consumes<View<reco::PFJet>   >          (ps.getParameter<InputTag>("AODak4PFJetsCHSSrc"));
//  //selectedPatJetsLabel_    = consumes<edm::View<pat::Jet> >          (ps.getParameter<InputTag>("selectedPatJetsSrc"));
//  AODTrackLabel_           = consumes<edm::View<reco::Track> >       (ps.getParameter<InputTag>("AODTrackSrc"));
  // trigger
  triggerBits_                    = consumes <edm::TriggerResults>                     (ps.getParameter<edm::InputTag>("bits"));
  triggerObjects_                 = consumes <edm::View<pat::TriggerObjectStandAlone>> (ps.getParameter<edm::InputTag>("objects"));
  triggerPrescales_               = consumes <pat::PackedTriggerPrescales>             (ps.getParameter<edm::InputTag>("prescales"));
  //AOD
  AODTriggerLabel_                =                                                     ps.getParameter<InputTag>("AODTriggerInputTag");
  AODTriggerToken_                = consumes<edm::TriggerResults>(AODTriggerLabel_);
  AODTriggerEventLabel_           =                                                     ps.getParameter<InputTag>("AODTriggerEventInputTag");
  AODTriggerEventToken_           = consumes<trigger::TriggerEvent>(AODTriggerEventLabel_);
//
//  // gen
//  genParticlesCollection_    = consumes<vector<reco::GenParticle> >    (ps.getParameter<InputTag>("genParticleSrc"));
//  AODGenEventInfoLabel_           = consumes <GenEventInfoProduct> (edm::InputTag(std::string("generator")));
//  genLumiHeaderToken_             = consumes <GenLumiInfoHeader,edm::InLumi> (edm::InputTag(std::string("generator")));

  Service<TFileService> fs;
  tree_    = fs->make<TTree>("EventTree", "Event data");
  hEvents_ = fs->make<TH1F>("hEvents",    "total processed events",   1,  0,   2);

 if(doAOD_){
//  branchesAODEvent(tree_);
//  branchesGenPart(tree_);
  branchesAODTrigger(tree_);
//  branchesAODJets(tree_);
 }
//
}

lldjNtuple::~lldjNtuple() {
}


void lldjNtuple::beginRun(edm::Run const& run, edm::EventSetup const& eventsetup) {

  bool changed(true);
  if(hltConfig_.init(run,eventsetup,"HLT",changed)){
  }
  hltPrescale_.init(run,eventsetup,"HLT",changed);

}

void lldjNtuple::analyze(const edm::Event& e, const edm::EventSetup& es) {

// if(doAOD_){
  //if (!e.isRealData()) fillGenPart(e);
  //fillAODEvent(e, es);
  fillAODTrigger(e, es);
  //fillAODJets(e, es);

 hEvents_->Fill(1.);
 tree_->Fill();
}

DEFINE_FWK_MODULE(lldjNtuple);
