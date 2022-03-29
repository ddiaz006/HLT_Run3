#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "HLT_Run3/Eff/ntuples/interface/lldjNtuple.h"
#include <iomanip>
#include <bitset>
using namespace std;

// (local) variables associated with tree branches
Int_t       AODrun_;
Long64_t    AODevent_;
Int_t       AODlumis_;
Bool_t      AODisData_;

Int_t       AODnTruePU_;
Int_t       AODnVtx_;
Int_t       AODnGoodVtx_;
Int_t       AODnTrksPV_;
Bool_t      AODisPVGood_;
Float_t     AODGenEventWeight_;
//new variables
float                 AODfixedGridRhoFastjetAll_;
int                   AODnBunchXing_;
std::vector<int>      AODBunchXing_;
std::vector<int>      AODnPU_;
std::vector<float>      AODnPUmean_;

void ResetEventBranches()
{
  AODfixedGridRhoFastjetAll_ = -999.;
  AODnBunchXing_ = 0;
  AODBunchXing_.clear();
  AODnPU_.clear();
  AODnPUmean_.clear();
};

TString     model_;
Int_t       AOD0thnPU_;

void lldjNtuple::branchesAODEvent(TTree* tree) {

  tree->Branch("run",     	       &AODrun_);
  tree->Branch("event",    	       &AODevent_);
  tree->Branch("lumis",   	       &AODlumis_);
  tree->Branch("isData",  	       &AODisData_);

  tree->Branch("AODnVtx",                 &AODnVtx_);
  tree->Branch("AODnGoodVtx",             &AODnGoodVtx_);
  tree->Branch("AODnTrksPV",              &AODnTrksPV_);
  tree->Branch("AODisPVGood",             &AODisPVGood_);

  //new variables
}

void lldjNtuple::fillAODEvent(const edm::Event& e, const edm::EventSetup& es) {

  //reset local variables
  ResetEventBranches();

  AODrun_    = e.id().run();
  AODevent_  = e.id().event();
  AODlumis_  = e.luminosityBlock();
  AODisData_ = e.isRealData();

  edm::Handle<edm::View<reco::Vertex>  >  AODVertexHandle;
  e.getByToken( AODVertexLabel_      ,  AODVertexHandle );

  AODnVtx_     = 0;
  AODnGoodVtx_ = 0;
  for(int k = 0; k < (int)AODVertexHandle->size();k++){
  if (AODVertexHandle->at(k).isValid())
  {
   if (AODnVtx_ == 0) // assumes leading vtx in collection is PV
   {
    AODnTrksPV_ = AODVertexHandle->at(k).nTracks();
    AODisPVGood_ = false;
    if (!AODVertexHandle->at(k).isFake() &&
         AODVertexHandle->at(k).ndof() > 4. &&
         fabs(AODVertexHandle->at(k).z()) <= 24. &&
         fabs(AODVertexHandle->at(k).position().rho()) <= 2.)  AODisPVGood_ = true;
   } // if AODnVtx_ == 0

   // all vertices
   if (!AODVertexHandle->at(k).isFake() &&
        AODVertexHandle->at(k).ndof() > 4. &&
        fabs(AODVertexHandle->at(k).z()) <= 24. &&
        fabs(AODVertexHandle->at(k).position().rho()) <= 2.)  AODnGoodVtx_++;

   AODnVtx_++;
  } // if AODVertexHandle->at(k).isValid()
  else {edm::LogWarning("lldjNtuple") << "Primary vertices info not unavailable";}
  }

  e.getByToken(rhoLabel_, rhoHandle);
  AODfixedGridRhoFastjetAll_ = *rhoHandle;
}
