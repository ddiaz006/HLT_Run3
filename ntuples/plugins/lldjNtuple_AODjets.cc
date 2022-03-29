#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "HLT_Run3/Eff/ntuples/interface/lldjNtuple.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandGauss.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "HLT_Run3/Eff/ntuples/interface/GetTrackTrajInfo.h"

#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/GeomPropagators/interface/StateOnTrackerBound.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"

#include "PhysicsTools/RecoUtils/interface/CheckHitPattern.h"
#include "RecoVertex/ConfigurableVertexReco/interface/ConfigurableVertexReconstructor.h"
#include "RecoVertex/VertexTools/interface/VertexCompatibleWithBeam.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/VertexPrimitives/interface/ConvertToFromReco.h"
#include "RecoVertex/VertexPrimitives/interface/ConvertError.h"

#include "DataFormats/PatCandidates/interface/Jet.h"



using namespace std;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

// AOD Collection Handles
edm::Handle<edm::View<reco::CaloJet> >  AODak4CaloJetsHandle;
edm::Handle<edm::View<reco::CaloJet> >  AODak4CaloJetsCorrectedHandle;
//edm::Handle<edm::View<reco::PFJet>   >  AODak4PFJetsHandle;
//edm::Handle<edm::View<reco::PFJet>   >  AODak4PFJetsCHSHandle;
//edm::Handle<edm::View<pat::Jet>      >  selectedPatJetsHandle;
edm::Handle<edm::View<reco::Vertex>  >  AODVertexHandle;
edm::Handle<edm::View<reco::Track>   >  AODTrackHandle;
edm::Handle<reco::BeamSpot> beamspotHandle_;
edm::ESHandle<MagneticField> magneticField;
edm::ESHandle<JetCorrectorParametersCollection> JetCorrParColl_Handle;//Daniel
edm::Handle<reco::JetCorrector> JetCorrector;
// transient tracks
map<reco::TransientTrack,reco::TrackBaseRef> refMap;
vector<TrajectoryStateOnSurface> tsosList;

// Global stuff for displaced vertices
ConfigurableVertexReconstructor* vtxfitter_;
VertexDistanceXY vertexDistanceXY_;
VertexCompatibleWithBeam* vertexBeam_ = new VertexCompatibleWithBeam(vertexDistanceXY_,100);

// AOD ---------------------------------------------
// Calo Jets
Int_t          AODnCaloJet_;
vector<float>  AODCaloJetPt_;
std::vector<float>  AODCaloJetEnergy_;
std::vector<float>  AODCaloJetPtUncorrected_;
std::vector<float>  AODCaloJetEnergyUncorrected_;
vector<float>  AODCaloJetPt_JECUp_;
vector<float>  AODCaloJetPt_JECDown_;
vector<float>  AODCaloJetEta_;
vector<float>  AODCaloJetPhi_;

//new variables
std::vector<bool>  AODCaloJetID_;
std::vector<float>  AODCaloJet_emEnergyFraction_;
std::vector<float>  AODCaloJet_energyFractionHadronic_;
std::vector<float>  AODCaloJetMass_;
std::vector<float>  AODCaloJetArea_;
std::vector<float>  AODCaloJetPileup_;


vector<float>  AODCaloJetAlphaMax_;
vector<float>  AODCaloJetAlphaMax2_;
vector<float>  AODCaloJetAlphaMaxPrime_;
vector<float>  AODCaloJetAlphaMaxPrime2_;
vector<float>  AODCaloJetBeta_;
vector<float>  AODCaloJetBeta2_;

vector<float>  AODCaloJetSumIP_;
vector<float>  AODCaloJetSumIPSig_;
//vector<float>  AODCaloJetLog10IPSig_;
vector<float>  AODCaloJetMedianIP_;
vector<float>  AODCaloJetMedianLog10IPSig_;
vector<float>  AODCaloJetTrackAngle_;
vector<float>  AODCaloJetLogTrackAngle_;
vector<float>  AODCaloJetMedianLog10TrackAngle_;
vector<float>  AODCaloJetTotalTrackAngle_;

vector<float>  AODCaloJetAvfVx_;
vector<float>  AODCaloJetAvfVy_;
vector<float>  AODCaloJetAvfVz_;
vector<float>  AODCaloJetAvfVertexTotalChiSquared_;
vector<float>  AODCaloJetAvfVertexDegreesOfFreedom_;
vector<float>  AODCaloJetAvfVertexChi2NDoF_;
vector<float>  AODCaloJetAvfVertexDistanceToBeam_;
vector<float>  AODCaloJetAvfVertexTransverseError_;
vector<float>  AODCaloJetAvfVertexTransverseSig_;
vector<float>  AODCaloJetAvfVertexDeltaEta_;
vector<float>  AODCaloJetAvfVertexDeltaPhi_;
vector<float>  AODCaloJetAvfVertexRecoilPt_;
vector<float>  AODCaloJetAvfVertexTrackMass_;
vector<float>  AODCaloJetAvfVertexTrackEnergy_;
vector<float>  AODCaloJetAvfBeamSpotDeltaPhi_;
vector<float>  AODCaloJetAvfBeamSpotRecoilPt_;
vector<float>  AODCaloJetAvfBeamSpotMedianDeltaPhi_;
vector<float>  AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_;
vector<int>    AODCaloJetNMatchedTracks_;
vector<int>    AODCaloJetNCleanMatchedTracks_;
vector<int>    AODCaloJetSumHitsInFrontOfVert_;
vector<int>    AODCaloJetSumMissHitsAfterVert_;
vector<int>    AODCaloJetHitsInFrontOfVertPerTrack_;
vector<int>    AODCaloJetMissHitsAfterVertPerTrack_;
vector<float>  AODCaloJetAvfDistToPV_;
vector<float>  AODCaloJetAvfVertexDeltaZtoPV_;
vector<float>  AODCaloJetAvfVertexDeltaZtoPV2_;


//Corrected CaloJets:
Int_t          AODnCaloJetCorrected_;
vector<float>  AODCaloJetCorrectedPt_;
vector<float>  AODCaloJetCorrectedPt_JECUp_;
vector<float>  AODCaloJetCorrectedPt_JECDown_;
vector<float>  AODCaloJetCorrectedEta_;
vector<float>  AODCaloJetCorrectedPhi_;

vector<float>  AODCaloJetCorrectedAlphaMax_;
vector<float>  AODCaloJetCorrectedAlphaMax2_;
vector<float>  AODCaloJetCorrectedAlphaMaxPrime_;
vector<float>  AODCaloJetCorrectedAlphaMaxPrime2_;
vector<float>  AODCaloJetCorrectedBeta_;
vector<float>  AODCaloJetCorrectedBeta2_;

vector<float>  AODCaloJetCorrectedSumIP_;
vector<float>  AODCaloJetCorrectedSumIPSig_;
//vector<float>  AODCaloJetCorrectedLog10IPSig_;
vector<float>  AODCaloJetCorrectedMedianIP_;
vector<float>  AODCaloJetCorrectedMedianLog10IPSig_;
vector<float>  AODCaloJetCorrectedTrackAngle_;
vector<float>  AODCaloJetCorrectedLogTrackAngle_;
vector<float>  AODCaloJetCorrectedMedianLog10TrackAngle_;
vector<float>  AODCaloJetCorrectedTotalTrackAngle_;

vector<float>  AODCaloJetCorrectedAvfVx_;
vector<float>  AODCaloJetCorrectedAvfVy_;
vector<float>  AODCaloJetCorrectedAvfVz_;
vector<float>  AODCaloJetCorrectedAvfVertexTotalChiSquared_;
vector<float>  AODCaloJetCorrectedAvfVertexDegreesOfFreedom_;
vector<float>  AODCaloJetCorrectedAvfVertexChi2NDoF_;
vector<float>  AODCaloJetCorrectedAvfVertexDistanceToBeam_;
vector<float>  AODCaloJetCorrectedAvfVertexTransverseError_;
vector<float>  AODCaloJetCorrectedAvfVertexTransverseSig_;
vector<float>  AODCaloJetCorrectedAvfVertexDeltaEta_;
vector<float>  AODCaloJetCorrectedAvfVertexDeltaPhi_;
vector<float>  AODCaloJetCorrectedAvfVertexRecoilPt_;
vector<float>  AODCaloJetCorrectedAvfVertexTrackMass_;
vector<float>  AODCaloJetCorrectedAvfVertexTrackEnergy_;
vector<float>  AODCaloJetCorrectedAvfBeamSpotDeltaPhi_;
vector<float>  AODCaloJetCorrectedAvfBeamSpotRecoilPt_;
vector<float>  AODCaloJetCorrectedAvfBeamSpotMedianDeltaPhi_;
vector<float>  AODCaloJetCorrectedAvfBeamSpotLog10MedianDeltaPhi_;
vector<int>    AODCaloJetCorrectedNMatchedTracks_;
vector<int>    AODCaloJetCorrectedNCleanMatchedTracks_;
vector<int>    AODCaloJetCorrectedSumHitsInFrontOfVert_;
vector<int>    AODCaloJetCorrectedSumMissHitsAfterVert_;
vector<int>    AODCaloJetCorrectedHitsInFrontOfVertPerTrack_;
vector<int>    AODCaloJetCorrectedMissHitsAfterVertPerTrack_;
vector<float>  AODCaloJetCorrectedAvfDistToPV_;
vector<float>  AODCaloJetCorrectedAvfVertexDeltaZtoPV_;
vector<float>  AODCaloJetCorrectedAvfVertexDeltaZtoPV2_;

vector<TVector3> AODallTrackPositions; // x,y,z

vector<float>    AODallTrackPt;
vector<float>    AODallTrackEta;
vector<float>    AODallTrackPhi;
vector<float>    AODallTrackIFSPt;

vector<int>      AODallTracknMissingInner;
vector<int>      AODallTracknMissingOuter;
vector<float>    AODallTrackAngle;

vector<int>      AODwhichVertexByTrack;

vector<float>    AODallTrackdxy;
vector<float>    AODallTrackdxyerr;

// set parameters for tracks to be accepted
const float minTrackPt_ = 1.0;
const float maxDRtrackJet_ = 0.4;


// start functions ----------------------------------------

// initialize branches
void lldjNtuple::branchesAODJets(TTree* tree) {

  //CaloJets
  tree->Branch("AODnCaloJet"                   , &AODnCaloJet_);
  tree->Branch("AODCaloJetEnergy"              , &AODCaloJetEnergy_);
  tree->Branch("AODCaloJetPt"                  , &AODCaloJetPt_);
  tree->Branch("AODCaloJetEnergyUncorrected"   , &AODCaloJetEnergyUncorrected_);
  tree->Branch("AODCaloJetPtUncorrected"       , &AODCaloJetPtUncorrected_);
  tree->Branch("AODCaloJetPt_JECUp"            , &AODCaloJetPt_JECUp_);
  tree->Branch("AODCaloJetPt_JECDown"          , &AODCaloJetPt_JECDown_);
  tree->Branch("AODCaloJetEta"                 , &AODCaloJetEta_);
  tree->Branch("AODCaloJetPhi"                 , &AODCaloJetPhi_);
  tree->Branch("AODCaloJetID"                  , &AODCaloJetID_);
  tree->Branch("AODCaloJet_emEnergyFraction"   , &AODCaloJet_emEnergyFraction_);
  tree->Branch("AODCaloJet_energyFractionHadronic" , &AODCaloJet_energyFractionHadronic_);
  tree->Branch("AODCaloJetMass"                , &AODCaloJetMass_);
  tree->Branch("AODCaloJetArea"                , &AODCaloJetArea_);
  tree->Branch("AODCaloJetPileup"              , &AODCaloJetPileup_);

  tree->Branch("AODCaloJetAlphaMax"            , &AODCaloJetAlphaMax_);
  tree->Branch("AODCaloJetAlphaMax2"           , &AODCaloJetAlphaMax2_);
  tree->Branch("AODCaloJetAlphaMaxPrime"       , &AODCaloJetAlphaMaxPrime_);
  tree->Branch("AODCaloJetAlphaMaxPrime2"      , &AODCaloJetAlphaMaxPrime2_);
  tree->Branch("AODCaloJetBeta"                , &AODCaloJetBeta_);
  tree->Branch("AODCaloJetBeta2"               , &AODCaloJetBeta2_);

  tree->Branch("AODCaloJetSumIP"               , &AODCaloJetSumIP_);
  tree->Branch("AODCaloJetSumIPSig"            , &AODCaloJetSumIPSig_);
  tree->Branch("AODCaloJetMedianIP"            , &AODCaloJetMedianIP_);
  tree->Branch("AODCaloJetMedianLog10IPSig"    , &AODCaloJetMedianLog10IPSig_);
  tree->Branch("AODCaloJetTrackAngle"          , &AODCaloJetTrackAngle_);
  tree->Branch("AODCaloJetLogTrackAngle"       , &AODCaloJetLogTrackAngle_);
  tree->Branch("AODCaloJetMedianLog10TrackAngle" , &AODCaloJetMedianLog10TrackAngle_);
  tree->Branch("AODCaloJetTotalTrackAngle"     , &AODCaloJetTotalTrackAngle_);

  tree->Branch("AODCaloJetAvfVx", &AODCaloJetAvfVx_);
  tree->Branch("AODCaloJetAvfVy", &AODCaloJetAvfVy_);
  tree->Branch("AODCaloJetAvfVz", &AODCaloJetAvfVz_);
  tree->Branch("AODCaloJetAvfVertexTotalChiSquared", &AODCaloJetAvfVertexTotalChiSquared_);
  tree->Branch("AODCaloJetAvfVertexDegreesOfFreedom", &AODCaloJetAvfVertexDegreesOfFreedom_);
  tree->Branch("AODCaloJetAvfVertexChi2NDoF", &AODCaloJetAvfVertexChi2NDoF_);
  tree->Branch("AODCaloJetAvfVertexDistanceToBeam", &AODCaloJetAvfVertexDistanceToBeam_);
  tree->Branch("AODCaloJetAvfVertexTransverseError", &AODCaloJetAvfVertexTransverseError_);
  tree->Branch("AODCaloJetAvfVertexTransverseSig", &AODCaloJetAvfVertexTransverseSig_);
  tree->Branch("AODCaloJetAvfVertexDeltaEta", &AODCaloJetAvfVertexDeltaEta_);
  tree->Branch("AODCaloJetAvfVertexDeltaPhi", &AODCaloJetAvfVertexDeltaPhi_);
  tree->Branch("AODCaloJetAvfVertexRecoilPt", &AODCaloJetAvfVertexRecoilPt_);
  tree->Branch("AODCaloJetAvfVertexTrackMass", &AODCaloJetAvfVertexTrackMass_);
  tree->Branch("AODCaloJetAvfVertexTrackEnergy", &AODCaloJetAvfVertexTrackEnergy_);
  tree->Branch("AODCaloJetAvfBeamSpotDeltaPhi", &AODCaloJetAvfBeamSpotDeltaPhi_);
  tree->Branch("AODCaloJetAvfBeamSpotRecoilPt", &AODCaloJetAvfBeamSpotRecoilPt_);
  tree->Branch("AODCaloJetAvfBeamSpotMedianDeltaPhi", &AODCaloJetAvfBeamSpotMedianDeltaPhi_);
  tree->Branch("AODCaloJetAvfBeamSpotLog10MedianDeltaPhi", &AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_);
  tree->Branch("AODCaloJetNCleanMatchedTracks", &AODCaloJetNCleanMatchedTracks_);
  tree->Branch("AODCaloJetNMatchedTracks"      , &AODCaloJetNMatchedTracks_);
  tree->Branch("AODCaloJetSumHitsInFrontOfVert", &AODCaloJetSumHitsInFrontOfVert_);
  tree->Branch("AODCaloJetSumMissHitsAfterVert", &AODCaloJetSumMissHitsAfterVert_);
  tree->Branch("AODCaloJetHitsInFrontOfVertPerTrack", &AODCaloJetHitsInFrontOfVertPerTrack_);
  tree->Branch("AODCaloJetMissHitsAfterVertPerTrack", &AODCaloJetMissHitsAfterVertPerTrack_);
  tree->Branch("AODCaloJetAvfDistToPV", &AODCaloJetAvfDistToPV_);
  tree->Branch("AODCaloJetAvfVertexDeltaZtoPV", &AODCaloJetAvfVertexDeltaZtoPV_);
  tree->Branch("AODCaloJetAvfVertexDeltaZtoPV2", &AODCaloJetAvfVertexDeltaZtoPV2_);


}

//fills slimmedJets .clear() to empty vector of old data
void lldjNtuple::fillAODJets(const edm::Event& e, const edm::EventSetup& es) {

 // bool dodebug = false;
 // cleanup from previous execution

 AODnCaloJet_=0;
 AODCaloJetEnergy_.clear();
 AODCaloJetPt_.clear();
 AODCaloJetEnergyUncorrected_.clear();
 AODCaloJetPtUncorrected_.clear();
 AODCaloJetPt_JECUp_.clear();
 AODCaloJetPt_JECDown_.clear();
 AODCaloJetEta_.clear();
 AODCaloJetPhi_.clear();
 AODCaloJetID_.clear();
 AODCaloJet_emEnergyFraction_.clear();
 AODCaloJet_energyFractionHadronic_.clear();
 AODCaloJetMass_.clear();
 AODCaloJetArea_.clear();
 AODCaloJetPileup_.clear();

 //AODnTracksToCaloJet_.clear();
 AODCaloJetNMatchedTracks_.clear();
 AODCaloJetCorrectedNMatchedTracks_.clear();

 AODCaloJetAlphaMax_.clear();
 AODCaloJetAlphaMax2_.clear();
 AODCaloJetAlphaMaxPrime_.clear();
 AODCaloJetAlphaMaxPrime2_.clear();
 AODCaloJetBeta_.clear();
 AODCaloJetBeta2_.clear();

 AODCaloJetSumIP_.clear();
 AODCaloJetSumIPSig_.clear();
 AODCaloJetMedianIP_.clear();
 AODCaloJetMedianLog10IPSig_.clear();
 AODCaloJetTrackAngle_.clear();
 AODCaloJetLogTrackAngle_.clear();
 AODCaloJetMedianLog10TrackAngle_.clear();
 AODCaloJetTotalTrackAngle_.clear();

 AODCaloJetAvfVx_.clear();
 AODCaloJetAvfVy_.clear();
 AODCaloJetAvfVz_.clear();
 AODCaloJetAvfVertexTotalChiSquared_.clear();
 AODCaloJetAvfVertexDegreesOfFreedom_.clear();
 AODCaloJetAvfVertexChi2NDoF_.clear();
 AODCaloJetAvfVertexDistanceToBeam_.clear();
 AODCaloJetAvfVertexTransverseError_.clear();
 AODCaloJetAvfVertexTransverseSig_.clear();
 AODCaloJetAvfVertexDeltaEta_.clear();
 AODCaloJetAvfVertexDeltaPhi_.clear();
 AODCaloJetAvfVertexRecoilPt_.clear();
 AODCaloJetAvfVertexTrackMass_.clear();
 AODCaloJetAvfVertexTrackEnergy_.clear();
 AODCaloJetAvfBeamSpotDeltaPhi_.clear();
 AODCaloJetAvfBeamSpotRecoilPt_.clear();
 AODCaloJetAvfBeamSpotMedianDeltaPhi_.clear();
 AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_.clear();
 AODCaloJetNCleanMatchedTracks_.clear();
 AODCaloJetSumHitsInFrontOfVert_.clear();
 AODCaloJetSumMissHitsAfterVert_.clear();
 AODCaloJetHitsInFrontOfVertPerTrack_.clear();
 AODCaloJetMissHitsAfterVertPerTrack_.clear();
 AODCaloJetAvfDistToPV_.clear();
 AODCaloJetAvfVertexDeltaZtoPV_.clear();
 AODCaloJetAvfVertexDeltaZtoPV2_.clear();

 //------------------
 //Corrected CaloJets
 //------------------
 AODnCaloJetCorrected_=0;
 AODCaloJetCorrectedPt_.clear();
 AODCaloJetCorrectedPt_JECUp_.clear();
 AODCaloJetCorrectedPt_JECDown_.clear();
 AODCaloJetCorrectedEta_.clear();
 AODCaloJetCorrectedPhi_.clear();
 //AODnTracksToCaloJet_.clear();
 AODCaloJetCorrectedNMatchedTracks_.clear();

 AODCaloJetCorrectedAlphaMax_.clear();
 AODCaloJetCorrectedAlphaMax2_.clear();
 AODCaloJetCorrectedAlphaMaxPrime_.clear();
 AODCaloJetCorrectedAlphaMaxPrime2_.clear();
 AODCaloJetCorrectedBeta_.clear();
 AODCaloJetCorrectedBeta2_.clear();

 AODCaloJetCorrectedSumIP_.clear();
 AODCaloJetCorrectedSumIPSig_.clear();
 AODCaloJetCorrectedMedianIP_.clear();
 AODCaloJetCorrectedMedianLog10IPSig_.clear();
 AODCaloJetCorrectedTrackAngle_.clear();
 AODCaloJetCorrectedLogTrackAngle_.clear();
 AODCaloJetCorrectedMedianLog10TrackAngle_.clear();
 AODCaloJetCorrectedTotalTrackAngle_.clear();

 AODCaloJetCorrectedAvfVx_.clear();
 AODCaloJetCorrectedAvfVy_.clear();
 AODCaloJetCorrectedAvfVz_.clear();
 AODCaloJetCorrectedAvfVertexTotalChiSquared_.clear();
 AODCaloJetCorrectedAvfVertexDegreesOfFreedom_.clear();
 AODCaloJetCorrectedAvfVertexChi2NDoF_.clear();
 AODCaloJetCorrectedAvfVertexDistanceToBeam_.clear();
 AODCaloJetCorrectedAvfVertexTransverseError_.clear();
 AODCaloJetCorrectedAvfVertexTransverseSig_.clear();
 AODCaloJetCorrectedAvfVertexDeltaEta_.clear();
 AODCaloJetCorrectedAvfVertexDeltaPhi_.clear();
 AODCaloJetCorrectedAvfVertexRecoilPt_.clear();
 AODCaloJetCorrectedAvfVertexTrackMass_.clear();
 AODCaloJetCorrectedAvfVertexTrackEnergy_.clear();
 AODCaloJetCorrectedAvfBeamSpotDeltaPhi_.clear();
 AODCaloJetCorrectedAvfBeamSpotRecoilPt_.clear();
 AODCaloJetCorrectedAvfBeamSpotMedianDeltaPhi_.clear();
 AODCaloJetCorrectedAvfBeamSpotLog10MedianDeltaPhi_.clear();
 AODCaloJetCorrectedNCleanMatchedTracks_.clear();
 AODCaloJetCorrectedSumHitsInFrontOfVert_.clear();
 AODCaloJetCorrectedSumMissHitsAfterVert_.clear();
 AODCaloJetCorrectedHitsInFrontOfVertPerTrack_.clear();
 AODCaloJetCorrectedMissHitsAfterVertPerTrack_.clear();
 AODCaloJetCorrectedAvfDistToPV_.clear();
 AODCaloJetCorrectedAvfVertexDeltaZtoPV_.clear();
 AODCaloJetCorrectedAvfVertexDeltaZtoPV2_.clear();

 // ----------------------------------------------------------
 // AOD Section ----------------------------------------------

 bool verbose_AOD = false;

 // AOD Jet Handles
 e.getByToken( AODak4CaloJetsLabel_ ,  AODak4CaloJetsHandle  );
 e.getByToken( AODak4CaloCorrectedJetsLabel_,  AODak4CaloJetsCorrectedHandle  );
 e.getByToken( AODak4JetCorrectorLabel_, JetCorrector );

 //e.getByToken( AODak4PFJetsLabel_   ,  AODak4PFJetsHandle    );
 //e.getByToken( AODak4PFJetsCHSLabel_,  AODak4PFJetsCHSHandle );
 //e.getByToken( selectedPatJetsLabel_,  selectedPatJetsHandle );
 e.getByToken( AODVertexLabel_      ,  AODVertexHandle );
 e.getByToken( AODTrackLabel_       ,  AODTrackHandle );

 // Magnetic field
 es.get<IdealMagneticFieldRecord>().get(magneticField);
 magneticField_ = &*magneticField;

 //------------------------------
 //JEC uncertainties for CaloJets
 //------------------------------
 es.get<JetCorrectionsRecord>().get("AK4Calo", JetCorrParColl_Handle);
 JetCorrectorParameters const & JetCorrPar = (*JetCorrParColl_Handle)["Uncertainty"];
 JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty(JetCorrPar);

 // beamspot
 e.getByToken(beamspotLabel_, beamspotHandle_);

 // clear values
 int nMissingInner = 0;
 int nMissingOuter = 0;

 // propagator
 std::string thePropagatorName_ = "PropagatorWithMaterial";
 es.get<TrackingComponentsRecord>().get(thePropagatorName_,thePropagator_);
 StateOnTrackerBound stateOnTracker(thePropagator_.product());

 // Vertex
 vector<int> whichVertex_;
 whichVertex_.clear();
 whichVertex_ = vector<int>(AODTrackHandle->size(),-1);

 vtxfitter_ = new ConfigurableVertexReconstructor(lldj_pset_.getParameter<edm::ParameterSet>("vertexFitterConfig"));

 // clear master track vectors before starting track loop
 AODallTrackPositions       .clear();
 AODallTrackPt              .clear();
 AODallTrackEta             .clear();
 AODallTrackPhi             .clear();
 AODallTrackIFSPt           .clear();
 AODallTracknMissingInner   .clear();
 AODallTracknMissingOuter   .clear();
 AODallTrackAngle           .clear();
 AODwhichVertexByTrack      .clear();
 AODallTrackdxy             .clear();
 AODallTrackdxyerr          .clear();

 for(int j = 0; j < (int)AODTrackHandle->size(); j++){

  // get track j using the AOD track handle
  reco::TrackBaseRef tref(AODTrackHandle,j);
  // make transient track (unfolding effects of B field ?)
  reco::TransientTrack tt(AODTrackHandle->at(j),magneticField_);

  if(!tt.isValid())continue;

  // track pt first
  float trackpt  = tref->pt();

  // make selections on track
  // for alphaMax, track angle we use ttIFSpt, not tref->pt()
  //   ---------!!!!--------------
  if (trackpt < minTrackPt_) continue;  // minimum pT for track
  if (!tref->quality(reco::TrackBase::highPurity)) continue; // track must be highPurity

  // find where track (no B field) would hit outer tracker
  FreeTrajectoryState fts = trajectoryStateTransform::initialFreeState(AODTrackHandle->at(j),magneticField_);
  TrajectoryStateOnSurface outer = stateOnTracker(fts);
  if(!outer.isValid()) continue;
  GlobalPoint outerPos = outer.globalPosition();
  TVector3 trackPos(outerPos.x(),outerPos.y(),outerPos.z());

  // push back track position to save in master vector
  AODallTrackPositions.push_back(trackPos);

  // track basics (trackpt above)
  float tracketa = tref->eta();
  float trackphi = tref->phi();
  float ttIFSpt  = tt.initialFreeState().momentum().transverse();
  AODallTrackPt .push_back(trackpt );
  AODallTrackEta.push_back(tracketa);
  AODallTrackPhi.push_back(trackphi);
  AODallTrackIFSPt.push_back(ttIFSpt);

  /// Find best vertex associated with this track
  // we are on track j
  // loop over vertices
  // reassign index bestk if trackWeight is new max
  float maxWeight = 0;
  int bestk = -1;
  for(int k = 0; k < (int)AODVertexHandle->size();k++){
   if(AODVertexHandle->at(k).trackWeight(tref) > maxWeight){
    maxWeight = AODVertexHandle->at(k).trackWeight(tref);
    bestk = k;
   }
  }
  AODwhichVertexByTrack.push_back(bestk);

  // Number of missing tracker hits
  nMissingInner = tref->hitPattern().numberOfLostTrackerHits(reco::HitPattern::MISSING_INNER_HITS);
  nMissingOuter = tref->hitPattern().numberOfLostTrackerHits(reco::HitPattern::MISSING_OUTER_HITS);
  AODallTracknMissingInner.push_back(nMissingInner) ;
  AODallTracknMissingOuter.push_back(nMissingOuter) ;

  /// For track angle
  // get track trajectory info
  static GetTrackTrajInfo getTrackTrajInfo;
  vector<GetTrackTrajInfo::Result> trajInfo = getTrackTrajInfo.analyze(es, (*tref));
  if ( trajInfo.size() > 0 && trajInfo[0].valid) {
   // get inner tracker hit from trajectory state
   const TrajectoryStateOnSurface& tsosInnerHit = trajInfo[0].detTSOS;

   //  here's the track angle
   // find beamspot x,y coordinates
   const reco::BeamSpot& pat_beamspot = (*beamspotHandle_);
   TVector2 bmspot(pat_beamspot.x0(),pat_beamspot.y0());
   // find track trajectory state on surface inner hit
   GlobalPoint  innerPos = tsosInnerHit.globalPosition();
   GlobalVector innerMom = tsosInnerHit.globalMomentum();

   // calculate the difference between inner hit and beamspot
   TVector2 sv(innerPos.x(),innerPos.y());
   TVector2 diff = (sv-bmspot);
   TVector2 momentum(innerMom.x(),innerMom.y());
   float ta = fabs( diff.DeltaPhi(momentum) ) ;

   AODallTrackAngle.push_back(ta);
  }
  else{ AODallTrackAngle.push_back(0); }

  // beamspot info, track impact parameter
  float dxy = fabs(tref->dxy(*beamspotHandle_));
  float dxyerr = tref->dxyError();
  if(verbose_AOD) printf(" dxy dxyerr: %0.4f %0.4f\n", dxy, dxyerr);
  AODallTrackdxy   .push_back(dxy   ) ;
  AODallTrackdxyerr.push_back(dxyerr) ;

 }//end track loop


 //std::cout << "--- new event ----" << std::endl;
 //-----------------------------------------------------------
 // UNCorrected ak4CaloL1FastL2L3ResidualCorrector AOD Calo Jets
 //-----------------------------------------------------------
 // AOD Calo Jets -------------------------------------------
 for (edm::View<reco::CaloJet>::const_iterator iJet = AODak4CaloJetsHandle->begin(); iJet != AODak4CaloJetsHandle->end(); ++iJet) {

  if(verbose_AOD) printf("Calo %f \n",iJet->pt());

  float jet_energy_uncorrected = iJet->energy();
  float jet_pt_uncorrected     = iJet->pt();
  float jet_eta                = iJet->eta();
  float jet_phi                = iJet->phi();

  float jet_mass               = iJet->mass();
  float jet_area               = iJet->jetArea();
  float jet_pileup             = iJet->pileup();
  //----------------------------------------------
  //get corrector factor based on jet object
  //----------------------------------------------
  double corrfac = JetCorrector->correction(*iJet);
  //correct energy and pt
  float jet_energy = corrfac*iJet->energy();
  float jet_pt     = corrfac*iJet->pt();

  //--------------------------------------------
  //Get JEC
  //--------------------------------------------
  jecUnc->setJetEta(jet_eta);
  jecUnc->setJetPt(jet_pt); // here you must use the CORRECTED jet pt
  double unc = jecUnc->getUncertainty(true);
  double ptCor_shiftedUP = jet_pt*(1+(1)*unc) ; // shift = +1(up), or -1(down)
  double ptCor_shiftedDN = jet_pt*(1+(-1)*unc) ; // shift = +1(up), or -1(down)

  // ID and jet selections
  bool passID = false;
  float emEnergyFraction = -999.;
  emEnergyFraction = iJet->emEnergyFraction();
  float energyFractionHadronic = -999.;
  energyFractionHadronic = iJet->energyFractionHadronic();
  //check jet ID
  if( iJet->emEnergyFraction()>=0.0
   && iJet->emEnergyFraction()<=0.9
   && iJet->energyFractionHadronic()>=0.0
   && iJet->energyFractionHadronic()<=0.9)  passID = true;

  // caloJetTrackIDs is a vector of ints where each int is the
  // index of a track passing deltaR requirement to this jet
  // out of the master track record of tracks passing basic selections
  vector<int>   caloJetTrackIDs = getJetTrackIndexs( jet_eta, jet_phi );
  AODCaloJetNMatchedTracks_.push_back( caloJetTrackIDs.size() );

  if(caloJetTrackIDs.size()<1) continue;

  if(verbose_AOD){
   printf(" AOD Jet pt eta phi: %0.1f %0.1f %0.1f\n",jet_pt,jet_eta,jet_phi);
   for( int i=0; i<(int)AODallTrackPositions.size(); i++){
    printf("  allTrack %i %0.1f %0.1f %0.1f \n",i,
     AODallTrackPt [i] ,
     AODallTrackEta[i] ,
     AODallTrackPhi[i] );

   }
   for( int i=0; i<(int)caloJetTrackIDs.size(); i++){
    printf(" Track %i at %i \n",i,caloJetTrackIDs[i]);
    printf("  caloTrack %i=%i %0.1f %0.1f %0.1f \n",i,
     caloJetTrackIDs[i],
     AODallTrackPt [caloJetTrackIDs[i]] ,
     AODallTrackEta[caloJetTrackIDs[i]] ,
     AODallTrackPhi[caloJetTrackIDs[i]] );
   }
  }

  // initialize variables
  float alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2 = -1.;
  float totalTrackAngle, totalTrackAnglePt = 0.;
  float sumIP, sumIPSig = 0.;
  vector<float> caloJetTrackAngles;
  caloJetTrackAngles.clear();
  vector<float> caloJetIPs;
  caloJetIPs.clear();
  vector<float> caloJetIPSigs;
  caloJetIPSigs.clear();

  // do calculations
  calculateAlphaMax(caloJetTrackIDs,alphaMax,alphaMaxPrime,beta,alphaMax2,alphaMaxPrime2,beta2);
  calculateTrackAngle(caloJetTrackIDs, caloJetTrackAngles, totalTrackAngle, totalTrackAnglePt);
  calculateIP(caloJetTrackIDs, caloJetIPs, caloJetIPSigs, sumIP, sumIPSig);
  calculateDisplacedVertices(es, caloJetTrackIDs);

  // find medians
  float medianTrackAngle;
  medianTrackAngle = findMedian(caloJetTrackAngles);
  float medianIP;
  medianIP = findMedian(caloJetIPs);
  float medianIPSig;
  medianIPSig = findMedian(caloJetIPSigs);

  ////////////////////////
  // Fill tree
  /////////////////////////
  AODnCaloJet_++;

  //Pt, Eta, Phi
  AODCaloJetEnergy_.push_back(jet_energy);
  AODCaloJetPt_.push_back(jet_pt);
  AODCaloJetEnergyUncorrected_.push_back(jet_energy_uncorrected);
  AODCaloJetPtUncorrected_.push_back(jet_pt_uncorrected);
  AODCaloJetPt_JECUp_.push_back(ptCor_shiftedUP);
  AODCaloJetPt_JECDown_.push_back(ptCor_shiftedDN);
  AODCaloJetEta_.push_back(jet_eta);
  AODCaloJetPhi_.push_back(jet_phi);
  AODCaloJetID_.push_back(passID);
  AODCaloJet_emEnergyFraction_.push_back(emEnergyFraction);
  AODCaloJet_energyFractionHadronic_.push_back(energyFractionHadronic);
  AODCaloJetMass_.push_back(jet_mass);
  AODCaloJetArea_.push_back(jet_area);
  AODCaloJetPileup_.push_back(jet_pileup);

  //AlphaMax-type variables
  AODCaloJetAlphaMax_       .push_back(alphaMax      ) ;
  AODCaloJetAlphaMax2_      .push_back(alphaMax2     ) ;
  AODCaloJetAlphaMaxPrime_  .push_back(alphaMaxPrime ) ;
  AODCaloJetAlphaMaxPrime2_ .push_back(alphaMaxPrime2) ;
  AODCaloJetBeta_           .push_back(beta          ) ;
  AODCaloJetBeta2_          .push_back(beta2         ) ;

  //Totals
  AODCaloJetSumIP_.push_back(sumIP);
  AODCaloJetSumIPSig_.push_back(sumIPSig);

  AODCaloJetTotalTrackAngle_.push_back(totalTrackAngle);

  /////Medians
  AODCaloJetMedianIP_             .push_back(medianIP);
  AODCaloJetMedianLog10IPSig_     .push_back(log10(medianIPSig));
  AODCaloJetMedianLog10TrackAngle_.push_back(log10(medianTrackAngle));

 }

}//end fill jets


vector<int> lldjNtuple::getJetTrackIndexs( float jeteta, float jetphi )
{
 vector<int> idvector;
 // loop over all selected tracks, dR match to jet
 for( int i=0; i<(int)AODallTrackPositions.size(); i++){
  float tracketa = AODallTrackPositions[i].Eta();
  float trackphi = AODallTrackPositions[i].Phi();
  float drt = deltaR( jeteta, jetphi, tracketa, trackphi );
  if(drt < maxDRtrackJet_){ idvector.push_back(i); }
 }
 return idvector;
}


void lldjNtuple::calculateAlphaMax(vector<int> jetTrackIDs, float& aMax, float& aMaxP, float& beta, float& aMax2, float& aMaxP2, float& beta2)
{

  float trackSumPt = 0;
  float trackSumPt2 = 0;
  float trackSumPtVtxMatched = 0;
  float trackSumPtVtxMatched2 = 0;

  int nrvtxs = AODVertexHandle->size();
  vector<float> trackSumPtByVtx( nrvtxs,0);
  vector<float> trackSumPtByVtx2(nrvtxs,0);

  // printf(" jetTracksIDs size: %i \n",(int)jetTrackIDs.size() );
  // printf(" AODwhichVertexByTrack size: %i \n",(int)AODwhichVertexByTrack.size() );

  for(int t=0; t< (int)jetTrackIDs.size(); t++){
   int trackID = jetTrackIDs[t];

   // sum pt of all tracks passing dR cut
   float trackpt = AODallTrackIFSPt[trackID];
   trackSumPt += trackpt;
   trackSumPt2 += (trackpt*trackpt);

   // now only for tracks associated with a vertex
   // the index of best vertex for track j is AODwhichVertexByTrack[j]
   if(AODwhichVertexByTrack[trackID] < 0)continue;

   // technically we could get this by summing over trackSumPtByVtx later
   trackSumPtVtxMatched += trackpt;
   trackSumPtVtxMatched2 += trackpt*trackpt;

   //// trackSumPtByVtx are sorted by vertex
   //printf("  track %i to vtx %i TS %i\n",
   // trackID, AODwhichVertexByTrack[trackID],
   // (int)trackSumPtByVtx.size());
   trackSumPtByVtx[AODwhichVertexByTrack[trackID]] += trackpt;
   trackSumPtByVtx2[AODwhichVertexByTrack[trackID]] += (trackpt*trackpt);
  }

  // clear variables from previous execution
  double apMax =0;
  double apMax2 = 0;

  // calculate beta
  // beta = ratio of sum of track pt matched to any vertex / sum on all tracks
  beta = 1.0 - trackSumPtVtxMatched/trackSumPt;
  beta2 = 1.0 - trackSumPtVtxMatched2 / trackSumPt2;

  // calculate alpha
  // alpha[a] = sum pt tracks matched to vtx [a] / total track sum pt
  // ap[a] = sum pt tracks matched to vtx [a] / ( same sum + beta )
  float tmpMaxSumPt = -1.;
  for(int i = 0; i < nrvtxs; i++){
    // find vertex number of max pt sum
    if(trackSumPtByVtx[i] > tmpMaxSumPt){
     tmpMaxSumPt = trackSumPtByVtx[i];
    }
    // calculate and fill apMax
    double ap = trackSumPtByVtx[i] / (trackSumPtByVtx[i] + beta);
    double ap2 = trackSumPtByVtx2[i] / (trackSumPtByVtx2[i] + beta2);
    if(ap > apMax) apMax = ap;
    if(ap2 > apMax2) apMax2 = ap2;
  }
  aMax   = tmpMaxSumPt  / trackSumPt;
  aMax2  = ( tmpMaxSumPt * tmpMaxSumPt ) / trackSumPt2;
  aMaxP  = apMax;
  aMaxP2 = apMax2;
  return;

}

void lldjNtuple::calculateTrackAngle(vector<int> jetTrackIDs, vector<float> &allTrackAngles,
 float &totalTrackAngle, float &totalTrackAnglePt)
{

  for(int t=0; t< (int)jetTrackIDs.size(); t++){
    int trackID = jetTrackIDs[t];
    // sum pt of all tracks passing dR cut
    float trackpt    = AODallTrackIFSPt[trackID];
    float trackangle = AODallTrackAngle[trackID];

    totalTrackAngle   += trackangle;
    totalTrackAnglePt += trackangle*trackpt;

    allTrackAngles.push_back(trackangle);
  }

  return;

}

void lldjNtuple::calculateIP(vector<int> jetTrackIDs, vector<float> &jetIPs, vector<float> &jetIPSigs, float &tsumIP, float &tsumIPSig)
{

  for(int t=0; t< (int)jetTrackIDs.size(); t++){

    int trackID = jetTrackIDs[t];
    // sum pt of all tracks passing dR cut
    float trackdxy    = AODallTrackdxy   [trackID];
    float trackdxyerr = AODallTrackdxyerr[trackID];
    float trackIPSig  = 0;
    if(trackdxyerr>0.) trackIPSig = trackdxy/trackdxyerr;

    tsumIP    += trackdxy;
    tsumIPSig += trackIPSig;

    //printf(" aa trackdyx: %0.4f %0.4f \n", trackdxy, trackIPSig);

    jetIPs.push_back(trackdxy);
    jetIPSigs.push_back(trackIPSig);

  }

  return;

}


float lldjNtuple::findMedian( vector<float> thevector){

 float themedian = -999. ;

 //printf(" thevector: ");
 //for ( int i=0; i<(int)thevector.size(); i++ ){
 // printf(" %0.4f ",thevector.at(i));
 //}
 //printf("\n");
 std::sort (thevector.begin(), thevector.end());
 //printf(" sorted thevector: ");
 //for ( int i=0; i<(int)thevector.size(); i++ ){
 // printf(" %0.4f ",thevector.at(i));
 //}
 //printf("\n");

 if(thevector.size() > 0){
  if((thevector.size()%2 == 0)){
   themedian = (
    thevector.at( (thevector.size() / 2) - 1 )
  + thevector.at( (thevector.size() / 2)     )
   ) / 2 ;
  } else {
   themedian = thevector.at( ( thevector.size() - 1 ) / 2 ) ;
  }
 }

 return themedian;

}

void lldjNtuple::deltaVertex3D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dEta, double& dPhi, double& pt, double& m, double& energy)
{
  TVector3 pv(AODVertexHandle->at(0).x(),AODVertexHandle->at(0).y(),AODVertexHandle->at(0).z());
  TVector3 sv(secVert.x(),secVert.y(),secVert.z());
  TVector3 diff = (sv-pv);
  TVector3 trackPt(0,0,0);
  TLorentzVector trackP4(0,0,0,0);
  for(int i = 0; i < (int)tracks.size(); i++){
    TVector3 tt;
    tt.SetPtEtaPhi(tracks[i].trajectoryStateClosestToPoint(secVert).momentum().transverse(),tracks[i].trajectoryStateClosestToPoint(secVert).momentum().eta(),tracks[i].trajectoryStateClosestToPoint(secVert).momentum().phi());
    trackPt += tt;
    trackP4 += TLorentzVector(tt,tracks[i].trajectoryStateClosestToPoint(secVert).momentum().mag());
  }
  dEta = diff.Eta()-trackPt.Eta();
  dPhi = diff.DeltaPhi(trackPt);
  pt = (trackPt - ((trackPt * diff)/(diff * diff) * diff)).Mag();
  m = trackP4.M();
  energy = trackP4.E();
}

void lldjNtuple::deltaVertex2D(GlobalPoint secVert, std::vector<reco::TransientTrack> tracks, double& dPhi, double& pt, double& mediandPhi)
{

  //edm::Handle<reco::BeamSpot> beamspotHandle_;//make this global??? BENTODO
  //e.getByToken(beamspotLabel_, beamspotHandle_);

  const reco::BeamSpot& pat_beamspot = (*beamspotHandle_);
  TVector2 bmspot(pat_beamspot.x0(),pat_beamspot.y0());
  TVector2 sv(secVert.x(),secVert.y());
  TVector2 diff = (sv-bmspot);
  TVector2 trackPt(0,0);
  vector<double> trackAngles;
  for(int i = 0; i < (int)tracks.size(); i++){
    TVector2 tt;
    tt.SetMagPhi(tracks[i].trajectoryStateClosestToPoint(secVert).momentum().transverse(),tracks[i].trajectoryStateClosestToPoint(secVert).momentum().phi());
    trackPt += tt;
    trackAngles.push_back(fabs(diff.DeltaPhi(tt)));
  }
  sort(trackAngles.begin(), trackAngles.end());

  if(trackAngles.size() == 0){
    //do nothing
  }else if((trackAngles.size()%2 == 0)){
    mediandPhi = trackAngles.at(trackAngles.size()/2-1);
  }else{
    mediandPhi = trackAngles.at((trackAngles.size()-1)/2);
  }

  dPhi = diff.DeltaPhi(trackPt);
  pt = (trackPt - ((trackPt * diff)/(diff * diff) * diff)).Mod();

}


vector<reco::TransientTrack> lldjNtuple::cleanTracks(vector<reco::TransientTrack> tracks, GlobalPoint vertPos)
{
  vector<reco::TransientTrack> cleanTracks;
  for(int i = 0; i < (int)tracks.size(); i++){
    if(tracks[i].trajectoryStateClosestToPoint(vertPos).perigeeError().transverseImpactParameterError() > 0 && tracks[i].trajectoryStateClosestToPoint(vertPos).perigeeParameters().transverseImpactParameter() / tracks[i].trajectoryStateClosestToPoint(vertPos).perigeeError().transverseImpactParameterError() > 3.0)continue;
    cleanTracks.push_back(tracks[i]);
  }
  return cleanTracks;
}



void lldjNtuple::calculateDisplacedVertices(const edm::EventSetup& es, vector<int> jetTrackIDs){

  //Select transient tracks for this jet
  vector<reco::TransientTrack> transientTracks;
  for(unsigned int j = 0; j < jetTrackIDs.size(); j++){
    reco::TransientTrack tt(AODTrackHandle->at( jetTrackIDs.at(j) ),magneticField_);
    transientTracks.push_back(tt);
  }

  if(transientTracks.size() > 1){
    vector<TransientVertex> avfVerts = vtxfitter_->vertices(transientTracks);
    if(avfVerts.size() > 0 && avfVerts[0].isValid()){
      GlobalPoint vertPos = avfVerts[0].position();
      GlobalError vertErr = avfVerts[0].positionError();

      AODCaloJetAvfVx_.push_back( vertPos.x() );
      AODCaloJetAvfVy_.push_back( vertPos.y() );
      AODCaloJetAvfVz_.push_back( vertPos.z() );

      float vertBeamXY = vertexBeam_->distanceToBeam(reco::Vertex(RecoVertex::convertPos(vertPos),RecoVertex::convertError(vertErr)));

      AODCaloJetAvfVertexTotalChiSquared_.push_back( avfVerts[0].totalChiSquared() );
      AODCaloJetAvfVertexDegreesOfFreedom_.push_back( avfVerts[0].degreesOfFreedom() );
      if(avfVerts[0].degreesOfFreedom() > 0) AODCaloJetAvfVertexChi2NDoF_.push_back( avfVerts[0].totalChiSquared()/avfVerts[0].degreesOfFreedom() );
       else AODCaloJetAvfVertexChi2NDoF_.push_back( 0. );
      AODCaloJetAvfVertexDistanceToBeam_.push_back( vertBeamXY );
      double rerr = vertErr.rerr(vertPos);
      AODCaloJetAvfVertexTransverseError_.push_back( rerr );
      if(rerr > 0) AODCaloJetAvfVertexTransverseSig_.push_back( vertBeamXY/rerr );
       else AODCaloJetAvfVertexTransverseSig_.push_back( 0. );

      vector<reco::TransientTrack> cleanTrackColl = cleanTracks(avfVerts[0].refittedTracks(),vertPos);

      double d3deta = 0, d3dphi = 0, d3dpt = 0, d3m = 0, d3en;
      deltaVertex3D(vertPos, cleanTrackColl,d3deta,d3dphi,d3dpt,d3m,d3en);
      AODCaloJetAvfVertexDeltaEta_.push_back( d3deta );
      AODCaloJetAvfVertexDeltaPhi_.push_back( d3dphi );
      AODCaloJetAvfVertexRecoilPt_.push_back( d3dpt );
      AODCaloJetAvfVertexTrackMass_.push_back( d3m );
      AODCaloJetAvfVertexTrackEnergy_.push_back( d3en );
      double d2dphi = 0,d2dpt = 0,d2dphiMed=1e-6;
      deltaVertex2D(vertPos,cleanTrackColl,d2dphi,d2dpt,d2dphiMed);
      AODCaloJetAvfBeamSpotDeltaPhi_.push_back( d2dphi );
      AODCaloJetAvfBeamSpotRecoilPt_.push_back( d2dpt );
      AODCaloJetAvfBeamSpotMedianDeltaPhi_.push_back( d2dphiMed );
      AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_.push_back( log10(d2dphiMed) );
      AODCaloJetNCleanMatchedTracks_.push_back( (int)cleanTrackColl.size() );

      int nHitsInFront = 0;
      int nMissingAfter = 0;
      CheckHitPattern checkHitPattern_;
      checkHitPattern_.init(es);
      for(int j = 0; j < (int)cleanTrackColl.size(); j++){
        const CheckHitPattern::Result res = checkHitPattern_.operator()(cleanTrackColl[j].track(),avfVerts[0].vertexState());
        nHitsInFront += res.hitsInFrontOfVert;
        nMissingAfter += res.missHitsAfterVert;
      }
      AODCaloJetSumHitsInFrontOfVert_.push_back( nHitsInFront );
      AODCaloJetSumMissHitsAfterVert_.push_back( nMissingAfter );
      AODCaloJetHitsInFrontOfVertPerTrack_.push_back( double(nHitsInFront)/double(transientTracks.size()) );
      AODCaloJetMissHitsAfterVertPerTrack_.push_back( double(nMissingAfter)/double(transientTracks.size()) );

      AODCaloJetAvfDistToPV_.push_back(
				       sqrt(pow((AODVertexHandle->at(0).x() - avfVerts[0].position().x())/AODVertexHandle->at(0).x(),2)
					    +pow((AODVertexHandle->at(0).y() - avfVerts[0].position().y())/AODVertexHandle->at(0).y(),2)
					    +pow((AODVertexHandle->at(0).z() - avfVerts[0].position().z())/AODVertexHandle->at(0).z(),2)) );
      if(AODVertexHandle->size() > 0)AODCaloJetAvfVertexDeltaZtoPV_.push_back( AODVertexHandle->at(0).z() - avfVerts[0].position().z() );
       else AODCaloJetAvfVertexDeltaZtoPV_.push_back( 0. );
      if(AODVertexHandle->size() > 1)AODCaloJetAvfVertexDeltaZtoPV2_.push_back( AODVertexHandle->at(1).z() - avfVerts[0].position().z() );
       else AODCaloJetAvfVertexDeltaZtoPV2_.push_back( 0. );


    }//end valid avf vertex
    else{
     AODCaloJetAvfVx_.push_back( 0. );
     AODCaloJetAvfVy_.push_back( 0. );
     AODCaloJetAvfVz_.push_back( 0. );
     AODCaloJetAvfVertexTotalChiSquared_.push_back( 0. );
     AODCaloJetAvfVertexDegreesOfFreedom_.push_back( 0. );
     AODCaloJetAvfVertexChi2NDoF_.push_back( 0. );
     AODCaloJetAvfVertexDistanceToBeam_.push_back( 0. );
     AODCaloJetAvfVertexTransverseError_.push_back( 0. );
     AODCaloJetAvfVertexTransverseSig_.push_back( 0. );
     AODCaloJetAvfVertexDeltaEta_.push_back( 0. );
     AODCaloJetAvfVertexDeltaPhi_.push_back( 0. );
     AODCaloJetAvfVertexRecoilPt_.push_back( 0. );
     AODCaloJetAvfVertexTrackMass_.push_back( 0. );
     AODCaloJetAvfVertexTrackEnergy_.push_back( 0. );
     AODCaloJetAvfBeamSpotDeltaPhi_.push_back( 0. );
     AODCaloJetAvfBeamSpotRecoilPt_.push_back( 0. );
     AODCaloJetAvfBeamSpotMedianDeltaPhi_.push_back( 0. );
     AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_.push_back( 0. );
     AODCaloJetNCleanMatchedTracks_.push_back( 0. );
     AODCaloJetSumHitsInFrontOfVert_.push_back( 0. );
     AODCaloJetSumMissHitsAfterVert_.push_back( 0. );
     AODCaloJetHitsInFrontOfVertPerTrack_.push_back( 0. );
     AODCaloJetMissHitsAfterVertPerTrack_.push_back( 0. );
     AODCaloJetAvfDistToPV_.push_back( 0. );
     AODCaloJetAvfVertexDeltaZtoPV_.push_back( 0. );
     AODCaloJetAvfVertexDeltaZtoPV2_.push_back( 0. );
    }

  }//end if transientTracks
  else{
   AODCaloJetAvfVx_.push_back( 0. );
   AODCaloJetAvfVy_.push_back( 0. );
   AODCaloJetAvfVz_.push_back( 0. );
   AODCaloJetAvfVertexTotalChiSquared_.push_back( 0. );
   AODCaloJetAvfVertexDegreesOfFreedom_.push_back( 0. );
   AODCaloJetAvfVertexChi2NDoF_.push_back( 0. );
   AODCaloJetAvfVertexDistanceToBeam_.push_back( 0. );
   AODCaloJetAvfVertexTransverseError_.push_back( 0. );
   AODCaloJetAvfVertexTransverseSig_.push_back( 0. );
   AODCaloJetAvfVertexDeltaEta_.push_back( 0. );
   AODCaloJetAvfVertexDeltaPhi_.push_back( 0. );
   AODCaloJetAvfVertexRecoilPt_.push_back( 0. );
   AODCaloJetAvfVertexTrackMass_.push_back( 0. );
   AODCaloJetAvfVertexTrackEnergy_.push_back( 0. );
   AODCaloJetAvfBeamSpotDeltaPhi_.push_back( 0. );
   AODCaloJetAvfBeamSpotRecoilPt_.push_back( 0. );
   AODCaloJetAvfBeamSpotMedianDeltaPhi_.push_back( 0. );
   AODCaloJetAvfBeamSpotLog10MedianDeltaPhi_.push_back( 0. );
   AODCaloJetNCleanMatchedTracks_.push_back( 0. );
   AODCaloJetSumHitsInFrontOfVert_.push_back( 0. );
   AODCaloJetSumMissHitsAfterVert_.push_back( 0. );
   AODCaloJetHitsInFrontOfVertPerTrack_.push_back( 0. );
   AODCaloJetMissHitsAfterVertPerTrack_.push_back( 0. );
   AODCaloJetAvfDistToPV_.push_back( 0. );
   AODCaloJetAvfVertexDeltaZtoPV_.push_back( 0. );
   AODCaloJetAvfVertexDeltaZtoPV2_.push_back( 0. );
  }

}//end calculateDisplacedVertices
