//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 31 23:40:57 2022 by ROOT version 6.22/09
// from TTree llp/selected AOD information for llp analyses
// found on file: ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root
//////////////////////////////////////////////////////////

#ifndef TrigTrigEff_h
#define TrigEff_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include "TROOT.h"
#include <TString.h>
#include <vector>
#include <string>

// Header file for the classes stored in the TTree if any.
//#include "string"

class TrigEff {
public :
   TString file =   "";
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.


   // Declaration of leaf types
//   UInt_t          lumiNum;
   UInt_t          eventNum;
//   UInt_t          eventTime;
//   UInt_t          nPFCandidates;
//   Int_t           PFCandidatePdgId[1000];   //[nPFCandidates]
//   Float_t         PFCandidatePt[1000];   //[nPFCandidates]
//   Float_t         PFCandidateEta[1000];   //[nPFCandidates]
//   Float_t         PFCandidatePhi[1000];   //[nPFCandidates]
//   Int_t           PFCandidateTrackIndex[1000];   //[nPFCandidates]
//   Int_t           PFCandidatePVIndex[1000];   //[nPFCandidates]
//   Int_t           nJets;
//   Float_t         jetE[1000];   //[nJets]
//   Float_t         jetPt[1000];   //[nJets]
//   Float_t         jetEta[1000];   //[nJets]
//   Float_t         jetPhi[1000];   //[nJets]
//   Float_t         jetCSV[1000];   //[nJets]
//   Float_t         jetCISV[1000];   //[nJets]
//   Float_t         jetCMVA[1000];   //[nJets]
//   Float_t         jetProbb[1000];   //[nJets]
//   Float_t         jetProbc[1000];   //[nJets]
//   Float_t         jetProbudsg[1000];   //[nJets]
//   Float_t         jetProbbb[1000];   //[nJets]
//   Float_t         jetMass[1000];   //[nJets]
//   Float_t         jetJetArea[1000];   //[nJets]
//   Float_t         jetPileupE[1000];   //[nJets]
//   Float_t         jetPileupId[1000];   //[nJets]
//   Int_t           jetPileupIdFlag[1000];   //[nJets]
//   Bool_t          jetPassIDLoose[1000];   //[nJets]
//   Bool_t          jetPassIDTight[1000];   //[nJets]
//   Bool_t          jetPassMuFrac[1000];   //[nJets]
//   Bool_t          jetPassEleFrac[1000];   //[nJets]
//   Int_t           jetPartonFlavor[1000];   //[nJets]
//   Int_t           jetHadronFlavor[1000];   //[nJets]
//   Float_t         jetElectronEnergyFraction[1000];   //[nJets]
//   Float_t         jetPhotonEnergyFraction[1000];   //[nJets]
//   Float_t         jetChargedHadronEnergyFraction[1000];   //[nJets]
//   Float_t         jetNeutralHadronEnergyFraction[1000];   //[nJets]
//   Float_t         jetMuonEnergyFraction[1000];   //[nJets]
//   Float_t         jetHOEnergyFraction[1000];   //[nJets]
//   Float_t         jetHFHadronEnergyFraction[1000];   //[nJets]
//   Float_t         jetHFEMEnergyFraction[1000];   //[nJets]
//   Int_t           jetChargedHadronMultiplicity[1000];   //[nJets]
//   Int_t           jetNeutralHadronMultiplicity[1000];   //[nJets]
//   Int_t           jetPhotonMultiplicity[1000];   //[nJets]
//   Int_t           jetElectronMultiplicity[1000];   //[nJets]
//   Int_t           jetMuonMultiplicity[1000];   //[nJets]
//   Int_t           jetNSV[1000];   //[nJets]
//   Int_t           jetNSVCand[1000];   //[nJets]
//   Int_t           jetNVertexTracks[1000];   //[nJets]
//   Int_t           jetNSelectedTracks[1000];   //[nJets]
//   Float_t         jetDRSVJet[1000];   //[nJets]
//   Float_t         jetFlightDist2D[1000];   //[nJets]
//   Float_t         jetFlightDist2DError[1000];   //[nJets]
//   Float_t         jetFlightDist3D[1000];   //[nJets]
//   Float_t         jetFlightDist3DError[1000];   //[nJets]
//   Float_t         jetSV_x[1000];   //[nJets]
//   Float_t         jetSV_y[1000];   //[nJets]
//   Float_t         jetSV_z[1000];   //[nJets]
//   Int_t           jetSVNTracks[1000];   //[nJets]
//   Float_t         jetSVMass[1000];   //[nJets]
//   Float_t         jetAllMuonPt[1000];   //[nJets]
//   Float_t         jetAllMuonEta[1000];   //[nJets]
//   Float_t         jetAllMuonPhi[1000];   //[nJets]
//   Float_t         jetAllMuonM[1000];   //[nJets]
//   Float_t         jetPtWeightedDZ[1000];   //[nJets]
//   Int_t           jetNRechits[1000];   //[nJets]
//   Float_t         jetRechitE[1000];   //[nJets]
//   Float_t         jetRechitT[1000];   //[nJets]
//   Float_t         jetRechitT_rms[1000];   //[nJets]
//   Float_t         jetRechitE_Error[1000];   //[nJets]
//   Float_t         jetRechitT_Error[1000];   //[nJets]
//   Float_t         jetAlphaMax[1000];   //[nJets]
//   Float_t         jetBetaMax[1000];   //[nJets]
//   Float_t         jetGammaMax_ET[1000];   //[nJets]
//   Float_t         jetGammaMax_EM[1000];   //[nJets]
//   Float_t         jetGammaMax_Hadronic[1000];   //[nJets]
//   Float_t         jetGammaMax[1000];   //[nJets]
//   Float_t         jetPtAllTracks[1000];   //[nJets]
//   Float_t         jetPtAllPVTracks[1000];   //[nJets]
//   Float_t         jetMedianTheta2D[1000];   //[nJets]
//   Float_t         jetMedianIP[1000];   //[nJets]
//   Float_t         jetMinDeltaRAllTracks[1000];   //[nJets]
//   Float_t         jetMinDeltaRPVTracks[1000];   //[nJets]
//   Float_t         jet_sig_et1[1000];   //[nJets]
//   Float_t         jet_sig_et2[1000];   //[nJets]
//   Float_t         jet_energy_frac[1000];   //[nJets]
//   Float_t         jetAlphaMax_wp[1000];   //[nJets]
//   Float_t         jetBetaMax_wp[1000];   //[nJets]
//   Float_t         jetGammaMax_ET_wp[1000];   //[nJets]
//   Float_t         jetGammaMax_EM_wp[1000];   //[nJets]
//   Float_t         jetGammaMax_Hadronic_wp[1000];   //[nJets]
//   Float_t         jetGammaMax_wp[1000];   //[nJets]
//   Float_t         jetPtAllTracks_wp[1000];   //[nJets]
//   Float_t         jetPtAllPVTracks_wp[1000];   //[nJets]
//   Float_t         jetMedianTheta2D_wp[1000];   //[nJets]
//   Float_t         jetMedianIP_wp[1000];   //[nJets]
//   Float_t         jetMinDeltaRAllTracks_wp[1000];   //[nJets]
//   Float_t         jetMinDeltaRPVTracks_wp[1000];   //[nJets]
//   Int_t           jetNPFCands[1000];   //[nJets]
//   Int_t           jetPFCandIndex[1000][5000];   //[nJets]
   UInt_t          nFatJets;
//   Float_t         fatJetE[1000];   //[nFatJets]
   Float_t         fatJetPt[1000];   //[nFatJets]
//   Float_t         fatJetEta[1000];   //[nFatJets]
//   Float_t         fatJetPhi[1000];   //[nFatJets]
//   Float_t         fatJetCorrectedPt[1000];   //[nFatJets]
//   Float_t         fatJetPrunedM[1000];   //[nFatJets]
//   Float_t         fatJetTrimmedM[1000];   //[nFatJets]
//   Float_t         fatJetFilteredM[1000];   //[nFatJets]
//   Float_t         fatJetSoftDropM[1000];   //[nFatJets]
//   Float_t         fatJetCorrectedSoftDropM[1000];   //[nFatJets]
//   Float_t         fatJetUncorrectedSoftDropM[1000];   //[nFatJets]
//   Float_t         fatJetTau1[1000];   //[nFatJets]
//   Float_t         fatJetTau2[1000];   //[nFatJets]
//   Float_t         fatJetTau3[1000];   //[nFatJets]
//   Float_t         fatJetMaxSubjetCSV[1000];   //[nFatJets]
//   Bool_t          fatJetPassIDLoose[1000];   //[nFatJets]
//   Bool_t          fatJetPassIDTight[1000];   //[nFatJets]
//   Int_t           fatJetNPFCands[1000];   //[nFatJets]
//   Int_t           fatJetPFCandIndex[1000][5000];   //[nFatJets]
//   //std::vector<Bool_t>          *HLTDecision;
   Bool_t          HLTDecision[1201];
   Int_t           HLTPrescale[1201];
//   Int_t           nGenJets;
//   Float_t         genJetE[1000];   //[nGenJets]
//   Float_t         genJetPt[1000];   //[nGenJets]
//   Float_t         genJetEta[1000];   //[nGenJets]
//   Float_t         genJetPhi[1000];   //[nGenJets]
//   Float_t         genMetPtCalo;
//   Float_t         genMetPhiCalo;
//   Float_t         genMetPtTrue;
//   Float_t         genMetPhiTrue;
//   Float_t         genVertexX;
//   Float_t         genVertexY;
//   Float_t         genVertexZ;
//   Float_t         genVertexT;
//   Float_t         genWeight;
//   UInt_t          genSignalProcessID;
//   Float_t         genQScale;
//   Float_t         genAlphaQCD;
//   Float_t         genAlphaQED;
//   Int_t           nGenParticle;
//   Int_t           gParticleMotherId[1000];   //[nGenParticle]
//   Int_t           gParticleMotherIndex[1000];   //[nGenParticle]
//   Int_t           gParticleId[1000];   //[nGenParticle]
//   Int_t           gParticleStatus[1000];   //[nGenParticle]
//   Float_t         gParticleE[1000];   //[nGenParticle]
//   Float_t         gParticlePt[1000];   //[nGenParticle]
//   Float_t         gParticleEta[1000];   //[nGenParticle]
//   Float_t         gParticlePhi[1000];   //[nGenParticle]
//   Float_t         gParticleProdVertexX[1000];   //[nGenParticle]
//   Float_t         gParticleProdVertexY[1000];   //[nGenParticle]
//   Float_t         gParticleProdVertexZ[1000];   //[nGenParticle]
//   Float_t         gParticleDecayVertexX[1000];   //[nGenParticle]
//   Float_t         gParticleDecayVertexY[1000];   //[nGenParticle]
//   Float_t         gParticleDecayVertexZ[1000];   //[nGenParticle]
//
//   // List of branches
//   TBranch        *b_lumiNum;   //!
   TBranch        *b_eventNum;   //!
//   TBranch        *b_eventTime;   //!
//   TBranch        *b_nPFCandidates;   //!
//   TBranch        *b_PFCandidatePdgId;   //!
//   TBranch        *b_PFCandidatePt;   //!
//   TBranch        *b_PFCandidateEta;   //!
//   TBranch        *b_PFCandidatePhi;   //!
//   TBranch        *b_PFCandidateTrackIndex;   //!
//   TBranch        *b_PFCandidatePVIndex;   //!
//   TBranch        *b_nJets;   //!
//   TBranch        *b_jetE;   //!
//   TBranch        *b_jetPt;   //!
//   TBranch        *b_jetEta;   //!
//   TBranch        *b_jetPhi;   //!
//   TBranch        *b_jetCSV;   //!
//   TBranch        *b_jetCISV;   //!
//   TBranch        *b_jetCMVA;   //!
//   TBranch        *b_jetProbb;   //!
//   TBranch        *b_jetProbc;   //!
//   TBranch        *b_jetProbudsg;   //!
//   TBranch        *b_jetProbbb;   //!
//   TBranch        *b_jetMass;   //!
//   TBranch        *b_jetJetArea;   //!
//   TBranch        *b_jetPileupE;   //!
//   TBranch        *b_jetPileupId;   //!
//   TBranch        *b_jetPileupIdFlag;   //!
//   TBranch        *b_jetPassIDLoose;   //!
//   TBranch        *b_jetPassIDTight;   //!
//   TBranch        *b_jetPassMuFrac;   //!
//   TBranch        *b_jetPassEleFrac;   //!
//   TBranch        *b_jetPartonFlavor;   //!
//   TBranch        *b_jetHadronFlavor;   //!
//   TBranch        *b_jetElectronEnergyFraction;   //!
//   TBranch        *b_jetPhotonEnergyFraction;   //!
//   TBranch        *b_jetChargedHadronEnergyFraction;   //!
//   TBranch        *b_jetNeutralHadronEnergyFraction;   //!
//   TBranch        *b_jetMuonEnergyFraction;   //!
//   TBranch        *b_jetHOEnergyFraction;   //!
//   TBranch        *b_jetHFHadronEnergyFraction;   //!
//   TBranch        *b_jetHFEMEnergyFraction;   //!
//   TBranch        *b_jetChargedHadronMultiplicity;   //!
//   TBranch        *b_jetNeutralHadronMultiplicity;   //!
//   TBranch        *b_jetPhotonMultiplicity;   //!
//   TBranch        *b_jetElectronMultiplicity;   //!
//   TBranch        *b_jetMuonMultiplicity;   //!
//   TBranch        *b_jetNSV;   //!
//   TBranch        *b_jetNSVCand;   //!
//   TBranch        *b_jetNVertexTracks;   //!
//   TBranch        *b_jetNSelectedTracks;   //!
//   TBranch        *b_jetDRSVJet;   //!
//   TBranch        *b_jetFlightDist2D;   //!
//   TBranch        *b_jetFlightDist2DError;   //!
//   TBranch        *b_jetFlightDist3D;   //!
//   TBranch        *b_jetFlightDist3DError;   //!
//   TBranch        *b_jetSV_x;   //!
//   TBranch        *b_jetSV_y;   //!
//   TBranch        *b_jetSV_z;   //!
//   TBranch        *b_jetSVNTracks;   //!
//   TBranch        *b_jetSVMass;   //!
//   TBranch        *b_jetAllMuonPt;   //!
//   TBranch        *b_jetAllMuonEta;   //!
//   TBranch        *b_jetAllMuonPhi;   //!
//   TBranch        *b_jetAllMuonM;   //!
//   TBranch        *b_jetPtWeightedDZ;   //!
//   TBranch        *b_jetNRechits;   //!
//   TBranch        *b_jetRechitE;   //!
//   TBranch        *b_jetRechitT;   //!
//   TBranch        *b_jetRechitT_rms;   //!
//   TBranch        *b_jetRechitE_Error;   //!
//   TBranch        *b_jetRechitT_Error;   //!
//   TBranch        *b_jetAlphaMax;   //!
//   TBranch        *b_jetBetaMax;   //!
//   TBranch        *b_jetGammaMax_ET;   //!
//   TBranch        *b_jetGammaMax_EM;   //!
//   TBranch        *b_jetGammaMax_Hadronic;   //!
//   TBranch        *b_jetGammaMax;   //!
//   TBranch        *b_jetPtAllTracks;   //!
//   TBranch        *b_jetPtAllPVTracks;   //!
//   TBranch        *b_jetMedianTheta2D;   //!
//   TBranch        *b_jetMedianIP;   //!
//   TBranch        *b_jetMinDeltaRAllTracks;   //!
//   TBranch        *b_jetMinDeltaRPVTracks;   //!
//   TBranch        *b_jet_sig_et1;   //!
//   TBranch        *b_jet_sig_et2;   //!
//   TBranch        *b_jet_energy_frac;   //!
//   TBranch        *b_jetAlphaMax_wp;   //!
//   TBranch        *b_jetBetaMax_wp;   //!
//   TBranch        *b_jetGammaMax_ET_wp;   //!
//   TBranch        *b_jetGammaMax_EM_wp;   //!
//   TBranch        *b_jetGammaMax_Hadronic_wp;   //!
//   TBranch        *b_jetGammaMax_wp;   //!
//   TBranch        *b_jetPtAllTracks_wp;   //!
//   TBranch        *b_jetPtAllPVTracks_wp;   //!
//   TBranch        *b_jetMedianTheta2D_wp;   //!
//   TBranch        *b_jetMedianIP_wp;   //!
//   TBranch        *b_jetMinDeltaRAllTracks_wp;   //!
//   TBranch        *b_jetMinDeltaRPVTracks_wp;   //!
//   TBranch        *b_jetNPFCands;   //!
//   TBranch        *b_jetPFCandIndex;   //!
   TBranch        *b_nFatJets;   //!
//   TBranch        *b_fatJetE;   //!
   TBranch        *b_fatJetPt;   //!
//   TBranch        *b_fatJetEta;   //!
//   TBranch        *b_fatJetPhi;   //!
//   TBranch        *b_fatJetCorrectedPt;   //!
//   TBranch        *b_fatJetPrunedM;   //!
//   TBranch        *b_fatJetTrimmedM;   //!
//   TBranch        *b_fatJetFilteredM;   //!
//   TBranch        *b_fatJetSoftDropM;   //!
//   TBranch        *b_fatJetCorrectedSoftDropM;   //!
//   TBranch        *b_fatJetUncorrectedSoftDropM;   //!
//   TBranch        *b_fatJetTau1;   //!
//   TBranch        *b_fatJetTau2;   //!
//   TBranch        *b_fatJetTau3;   //!
//   TBranch        *b_fatJetMaxSubjetCSV;   //!
//   TBranch        *b_fatJetPassIDLoose;   //!
//   TBranch        *b_fatJetPassIDTight;   //!
//   TBranch        *b_fatJetNPFCands;   //!
//   TBranch        *b_fatJetPFCandIndex;   //!
   TBranch        *b_HLTDecision;   //!
//   TBranch        *b_HLTPrescale;   //!
//   TBranch        *b_nGenJets;   //!
//   TBranch        *b_genJetE;   //!
//   TBranch        *b_genJetPt;   //!
//   TBranch        *b_genJetEta;   //!
//   TBranch        *b_genJetPhi;   //!
//   TBranch        *b_genMetPtCalo;   //!
//   TBranch        *b_genMetPhiCalo;   //!
//   TBranch        *b_genMetPtTrue;   //!
//   TBranch        *b_genMetPhiTrue;   //!
//   TBranch        *b_genVertexX;   //!
//   TBranch        *b_genVertexY;   //!
//   TBranch        *b_genVertexZ;   //!
//   TBranch        *b_genVertexT;   //!
//   TBranch        *b_genWeight;   //!
//   TBranch        *b_genSignalProcessID;   //!
//   TBranch        *b_genQScale;   //!
//   TBranch        *b_genAlphaQCD;   //!
//   TBranch        *b_genAlphaQED;   //!
//   TBranch        *b_nGenParticle;   //!
//   TBranch        *b_gParticleMotherId;   //!
//   TBranch        *b_gParticleMotherIndex;   //!
//   TBranch        *b_gParticleId;   //!
//   TBranch        *b_gParticleStatus;   //!
//   TBranch        *b_gParticleE;   //!
//   TBranch        *b_gParticlePt;   //!
//   TBranch        *b_gParticleEta;   //!
//   TBranch        *b_gParticlePhi;   //!
//   TBranch        *b_gParticleProdVertexX;   //!
//   TBranch        *b_gParticleProdVertexY;   //!
//   TBranch        *b_gParticleProdVertexZ;   //!
//   TBranch        *b_gParticleDecayVertexX;   //!
//   TBranch        *b_gParticleDecayVertexY;   //!
//   TBranch        *b_gParticleDecayVertexZ;   //!
//   TBranch        *b_gLLP_decay_vertex_x;   //!
//   TBranch        *b_gLLP_decay_vertex_y;   //!
//   TBranch        *b_gLLP_decay_vertex_z;   //!
//   TBranch        *b_gLLP_beta;   //!

   TrigEff(TTree *tree=0);
   virtual ~TrigEff();
   virtual void     FileName(TString fileName);
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TrigEff_cxx
void TrigEff::FileName(TString fileName)
{
 file = fileName;
}


TrigEff::TrigEff(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("ntupleFromHLTX.GluGluToHHTo2B2Tau_node_cHHH1_TuneCP5_14TeV-powheg-pythia8.root:/ntuples");
      dir->GetObject("llp",tree);

   }
   Init(tree);
}

TrigEff::~TrigEff()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TrigEff::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TrigEff::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TrigEff::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);


//   fChain->SetBranchAddress("lumiNum", &lumiNum, &b_lumiNum);
   fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
//   fChain->SetBranchAddress("nPFCandidates", &nPFCandidates, &b_nPFCandidates);
//   fChain->SetBranchAddress("PFCandidatePdgId", &PFCandidatePdgId, &b_PFCandidatePdgId);
//   fChain->SetBranchAddress("PFCandidatePt", &PFCandidatePt, &b_PFCandidatePt);
//   fChain->SetBranchAddress("PFCandidateEta", &PFCandidateEta, &b_PFCandidateEta);
//   fChain->SetBranchAddress("PFCandidatePhi", &PFCandidatePhi, &b_PFCandidatePhi);
//   fChain->SetBranchAddress("PFCandidateTrackIndex", &PFCandidateTrackIndex, &b_PFCandidateTrackIndex);
//   fChain->SetBranchAddress("PFCandidatePVIndex", &PFCandidatePVIndex, &b_PFCandidatePVIndex);
//   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
//   fChain->SetBranchAddress("jetE", &jetE, &b_jetE);
//   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
//   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
//   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
//   fChain->SetBranchAddress("jetCSV", &jetCSV, &b_jetCSV);
//   fChain->SetBranchAddress("jetCISV", &jetCISV, &b_jetCISV);
//   fChain->SetBranchAddress("jetCMVA", &jetCMVA, &b_jetCMVA);
//   fChain->SetBranchAddress("jetProbb", &jetProbb, &b_jetProbb);
//   fChain->SetBranchAddress("jetProbc", &jetProbc, &b_jetProbc);
//   fChain->SetBranchAddress("jetProbudsg", &jetProbudsg, &b_jetProbudsg);
//   fChain->SetBranchAddress("jetProbbb", &jetProbbb, &b_jetProbbb);
//   fChain->SetBranchAddress("jetMass", &jetMass, &b_jetMass);
//   fChain->SetBranchAddress("jetJetArea", &jetJetArea, &b_jetJetArea);
//   fChain->SetBranchAddress("jetPileupE", &jetPileupE, &b_jetPileupE);
//   fChain->SetBranchAddress("jetPileupId", &jetPileupId, &b_jetPileupId);
//   fChain->SetBranchAddress("jetPileupIdFlag", &jetPileupIdFlag, &b_jetPileupIdFlag);
//   fChain->SetBranchAddress("jetPassIDLoose", &jetPassIDLoose, &b_jetPassIDLoose);
//   fChain->SetBranchAddress("jetPassIDTight", &jetPassIDTight, &b_jetPassIDTight);
//   fChain->SetBranchAddress("jetPassMuFrac", &jetPassMuFrac, &b_jetPassMuFrac);
//   fChain->SetBranchAddress("jetPassEleFrac", &jetPassEleFrac, &b_jetPassEleFrac);
//   fChain->SetBranchAddress("jetPartonFlavor", &jetPartonFlavor, &b_jetPartonFlavor);
//   fChain->SetBranchAddress("jetHadronFlavor", &jetHadronFlavor, &b_jetHadronFlavor);
//   fChain->SetBranchAddress("jetElectronEnergyFraction", &jetElectronEnergyFraction, &b_jetElectronEnergyFraction);
//   fChain->SetBranchAddress("jetPhotonEnergyFraction", &jetPhotonEnergyFraction, &b_jetPhotonEnergyFraction);
//   fChain->SetBranchAddress("jetChargedHadronEnergyFraction", &jetChargedHadronEnergyFraction, &b_jetChargedHadronEnergyFraction);
//   fChain->SetBranchAddress("jetNeutralHadronEnergyFraction", &jetNeutralHadronEnergyFraction, &b_jetNeutralHadronEnergyFraction);
//   fChain->SetBranchAddress("jetMuonEnergyFraction", &jetMuonEnergyFraction, &b_jetMuonEnergyFraction);
//   fChain->SetBranchAddress("jetHOEnergyFraction", &jetHOEnergyFraction, &b_jetHOEnergyFraction);
//   fChain->SetBranchAddress("jetHFHadronEnergyFraction", &jetHFHadronEnergyFraction, &b_jetHFHadronEnergyFraction);
//   fChain->SetBranchAddress("jetHFEMEnergyFraction", &jetHFEMEnergyFraction, &b_jetHFEMEnergyFraction);
//   fChain->SetBranchAddress("jetChargedHadronMultiplicity", &jetChargedHadronMultiplicity, &b_jetChargedHadronMultiplicity);
//   fChain->SetBranchAddress("jetNeutralHadronMultiplicity", &jetNeutralHadronMultiplicity, &b_jetNeutralHadronMultiplicity);
//   fChain->SetBranchAddress("jetPhotonMultiplicity", &jetPhotonMultiplicity, &b_jetPhotonMultiplicity);
//   fChain->SetBranchAddress("jetElectronMultiplicity", &jetElectronMultiplicity, &b_jetElectronMultiplicity);
//   fChain->SetBranchAddress("jetMuonMultiplicity", &jetMuonMultiplicity, &b_jetMuonMultiplicity);
//   fChain->SetBranchAddress("jetNSV", &jetNSV, &b_jetNSV);
//   fChain->SetBranchAddress("jetNSVCand", &jetNSVCand, &b_jetNSVCand);
//   fChain->SetBranchAddress("jetNVertexTracks", &jetNVertexTracks, &b_jetNVertexTracks);
//   fChain->SetBranchAddress("jetNSelectedTracks", &jetNSelectedTracks, &b_jetNSelectedTracks);
//   fChain->SetBranchAddress("jetDRSVJet", &jetDRSVJet, &b_jetDRSVJet);
//   fChain->SetBranchAddress("jetFlightDist2D", &jetFlightDist2D, &b_jetFlightDist2D);
//   fChain->SetBranchAddress("jetFlightDist2DError", &jetFlightDist2DError, &b_jetFlightDist2DError);
//   fChain->SetBranchAddress("jetFlightDist3D", &jetFlightDist3D, &b_jetFlightDist3D);
//   fChain->SetBranchAddress("jetFlightDist3DError", &jetFlightDist3DError, &b_jetFlightDist3DError);
//   fChain->SetBranchAddress("jetSV_x", &jetSV_x, &b_jetSV_x);
//   fChain->SetBranchAddress("jetSV_y", &jetSV_y, &b_jetSV_y);
//   fChain->SetBranchAddress("jetSV_z", &jetSV_z, &b_jetSV_z);
//   fChain->SetBranchAddress("jetSVNTracks", &jetSVNTracks, &b_jetSVNTracks);
//   fChain->SetBranchAddress("jetSVMass", &jetSVMass, &b_jetSVMass);
//   fChain->SetBranchAddress("jetAllMuonPt", &jetAllMuonPt, &b_jetAllMuonPt);
//   fChain->SetBranchAddress("jetAllMuonEta", &jetAllMuonEta, &b_jetAllMuonEta);
//   fChain->SetBranchAddress("jetAllMuonPhi", &jetAllMuonPhi, &b_jetAllMuonPhi);
//   fChain->SetBranchAddress("jetAllMuonM", &jetAllMuonM, &b_jetAllMuonM);
//   fChain->SetBranchAddress("jetPtWeightedDZ", &jetPtWeightedDZ, &b_jetPtWeightedDZ);
//   fChain->SetBranchAddress("jetNRechits", &jetNRechits, &b_jetNRechits);
//   fChain->SetBranchAddress("jetRechitE", &jetRechitE, &b_jetRechitE);
//   fChain->SetBranchAddress("jetRechitT", &jetRechitT, &b_jetRechitT);
//   fChain->SetBranchAddress("jetRechitT_rms", &jetRechitT_rms, &b_jetRechitT_rms);
//   fChain->SetBranchAddress("jetRechitE_Error", &jetRechitE_Error, &b_jetRechitE_Error);
//   fChain->SetBranchAddress("jetRechitT_Error", &jetRechitT_Error, &b_jetRechitT_Error);
//   fChain->SetBranchAddress("jetAlphaMax", &jetAlphaMax, &b_jetAlphaMax);
//   fChain->SetBranchAddress("jetBetaMax", &jetBetaMax, &b_jetBetaMax);
//   fChain->SetBranchAddress("jetGammaMax_ET", &jetGammaMax_ET, &b_jetGammaMax_ET);
//   fChain->SetBranchAddress("jetGammaMax_EM", &jetGammaMax_EM, &b_jetGammaMax_EM);
//   fChain->SetBranchAddress("jetGammaMax_Hadronic", &jetGammaMax_Hadronic, &b_jetGammaMax_Hadronic);
//   fChain->SetBranchAddress("jetGammaMax", &jetGammaMax, &b_jetGammaMax);
//   fChain->SetBranchAddress("jetPtAllTracks", &jetPtAllTracks, &b_jetPtAllTracks);
//   fChain->SetBranchAddress("jetPtAllPVTracks", &jetPtAllPVTracks, &b_jetPtAllPVTracks);
//   fChain->SetBranchAddress("jetMedianTheta2D", &jetMedianTheta2D, &b_jetMedianTheta2D);
//   fChain->SetBranchAddress("jetMedianIP", &jetMedianIP, &b_jetMedianIP);
//   fChain->SetBranchAddress("jetMinDeltaRAllTracks", &jetMinDeltaRAllTracks, &b_jetMinDeltaRAllTracks);
//   fChain->SetBranchAddress("jetMinDeltaRPVTracks", &jetMinDeltaRPVTracks, &b_jetMinDeltaRPVTracks);
//   fChain->SetBranchAddress("jet_sig_et1", &jet_sig_et1, &b_jet_sig_et1);
//   fChain->SetBranchAddress("jet_sig_et2", &jet_sig_et2, &b_jet_sig_et2);
//   fChain->SetBranchAddress("jet_energy_frac", &jet_energy_frac, &b_jet_energy_frac);
//   fChain->SetBranchAddress("jetAlphaMax_wp", &jetAlphaMax_wp, &b_jetAlphaMax_wp);
//   fChain->SetBranchAddress("jetBetaMax_wp", &jetBetaMax_wp, &b_jetBetaMax_wp);
//   fChain->SetBranchAddress("jetGammaMax_ET_wp", &jetGammaMax_ET_wp, &b_jetGammaMax_ET_wp);
//   fChain->SetBranchAddress("jetGammaMax_EM_wp", &jetGammaMax_EM_wp, &b_jetGammaMax_EM_wp);
//   fChain->SetBranchAddress("jetGammaMax_Hadronic_wp", &jetGammaMax_Hadronic_wp, &b_jetGammaMax_Hadronic_wp);
//   fChain->SetBranchAddress("jetGammaMax_wp", &jetGammaMax_wp, &b_jetGammaMax_wp);
//   fChain->SetBranchAddress("jetPtAllTracks_wp", &jetPtAllTracks_wp, &b_jetPtAllTracks_wp);
//   fChain->SetBranchAddress("jetPtAllPVTracks_wp", &jetPtAllPVTracks_wp, &b_jetPtAllPVTracks_wp);
//   fChain->SetBranchAddress("jetMedianTheta2D_wp", &jetMedianTheta2D_wp, &b_jetMedianTheta2D_wp);
//   fChain->SetBranchAddress("jetMedianIP_wp", &jetMedianIP_wp, &b_jetMedianIP_wp);
//   fChain->SetBranchAddress("jetMinDeltaRAllTracks_wp", &jetMinDeltaRAllTracks_wp, &b_jetMinDeltaRAllTracks_wp);
//   fChain->SetBranchAddress("jetMinDeltaRPVTracks_wp", &jetMinDeltaRPVTracks_wp, &b_jetMinDeltaRPVTracks_wp);
//   fChain->SetBranchAddress("jetNPFCands", &jetNPFCands, &b_jetNPFCands);
//   fChain->SetBranchAddress("jetPFCandIndex", &jetPFCandIndex, &b_jetPFCandIndex);
   fChain->SetBranchAddress("nFatJets", &nFatJets, &b_nFatJets);
//   fChain->SetBranchAddress("fatJetE", &fatJetE, &b_fatJetE);
   fChain->SetBranchAddress("fatJetPt", &fatJetPt, &b_fatJetPt);
//   fChain->SetBranchAddress("fatJetEta", &fatJetEta, &b_fatJetEta);
//   fChain->SetBranchAddress("fatJetPhi", &fatJetPhi, &b_fatJetPhi);
//   fChain->SetBranchAddress("fatJetCorrectedPt", &fatJetCorrectedPt, &b_fatJetCorrectedPt);
//   fChain->SetBranchAddress("fatJetPrunedM", &fatJetPrunedM, &b_fatJetPrunedM);
//   fChain->SetBranchAddress("fatJetTrimmedM", &fatJetTrimmedM, &b_fatJetTrimmedM);
//   fChain->SetBranchAddress("fatJetFilteredM", &fatJetFilteredM, &b_fatJetFilteredM);
//   fChain->SetBranchAddress("fatJetSoftDropM", &fatJetSoftDropM, &b_fatJetSoftDropM);
//   fChain->SetBranchAddress("fatJetCorrectedSoftDropM", &fatJetCorrectedSoftDropM, &b_fatJetCorrectedSoftDropM);
//   fChain->SetBranchAddress("fatJetUncorrectedSoftDropM", &fatJetUncorrectedSoftDropM, &b_fatJetUncorrectedSoftDropM);
//   fChain->SetBranchAddress("fatJetTau1", &fatJetTau1, &b_fatJetTau1);
//   fChain->SetBranchAddress("fatJetTau2", &fatJetTau2, &b_fatJetTau2);
//   fChain->SetBranchAddress("fatJetTau3", &fatJetTau3, &b_fatJetTau3);
//   fChain->SetBranchAddress("fatJetMaxSubjetCSV", &fatJetMaxSubjetCSV, &b_fatJetMaxSubjetCSV);
//   fChain->SetBranchAddress("fatJetPassIDLoose", &fatJetPassIDLoose, &b_fatJetPassIDLoose);
//   fChain->SetBranchAddress("fatJetPassIDTight", &fatJetPassIDTight, &b_fatJetPassIDTight);
//   fChain->SetBranchAddress("fatJetNPFCands", &fatJetNPFCands, &b_fatJetNPFCands);
//   fChain->SetBranchAddress("fatJetPFCandIndex", &fatJetPFCandIndex, &b_fatJetPFCandIndex);
   fChain->SetBranchAddress("HLTDecision", HLTDecision, &b_HLTDecision);
//   fChain->SetBranchAddress("HLTPrescale", HLTPrescale, &b_HLTPrescale);
//   fChain->SetBranchAddress("nGenJets", &nGenJets, &b_nGenJets);
//   fChain->SetBranchAddress("genJetE", &genJetE, &b_genJetE);
//   fChain->SetBranchAddress("genJetPt", &genJetPt, &b_genJetPt);
//   fChain->SetBranchAddress("genJetEta", &genJetEta, &b_genJetEta);
//   fChain->SetBranchAddress("genJetPhi", &genJetPhi, &b_genJetPhi);
//   fChain->SetBranchAddress("genMetPtCalo", &genMetPtCalo, &b_genMetPtCalo);
//   fChain->SetBranchAddress("genMetPhiCalo", &genMetPhiCalo, &b_genMetPhiCalo);
//   fChain->SetBranchAddress("genMetPtTrue", &genMetPtTrue, &b_genMetPtTrue);
//   fChain->SetBranchAddress("genMetPhiTrue", &genMetPhiTrue, &b_genMetPhiTrue);
//   fChain->SetBranchAddress("genVertexX", &genVertexX, &b_genVertexX);
//   fChain->SetBranchAddress("genVertexY", &genVertexY, &b_genVertexY);
//   fChain->SetBranchAddress("genVertexZ", &genVertexZ, &b_genVertexZ);
//   fChain->SetBranchAddress("genVertexT", &genVertexT, &b_genVertexT);
//   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
//   fChain->SetBranchAddress("genSignalProcessID", &genSignalProcessID, &b_genSignalProcessID);
//   fChain->SetBranchAddress("genQScale", &genQScale, &b_genQScale);
//   fChain->SetBranchAddress("genAlphaQCD", &genAlphaQCD, &b_genAlphaQCD);
//   fChain->SetBranchAddress("genAlphaQED", &genAlphaQED, &b_genAlphaQED);
//   fChain->SetBranchAddress("nGenParticle", &nGenParticle, &b_nGenParticle);
//   fChain->SetBranchAddress("gParticleMotherId", &gParticleMotherId, &b_gParticleMotherId);
//   fChain->SetBranchAddress("gParticleMotherIndex", &gParticleMotherIndex, &b_gParticleMotherIndex);
//   fChain->SetBranchAddress("gParticleId", &gParticleId, &b_gParticleId);
//   fChain->SetBranchAddress("gParticleStatus", &gParticleStatus, &b_gParticleStatus);
//   fChain->SetBranchAddress("gParticleE", &gParticleE, &b_gParticleE);
//   fChain->SetBranchAddress("gParticlePt", &gParticlePt, &b_gParticlePt);
//   fChain->SetBranchAddress("gParticleEta", &gParticleEta, &b_gParticleEta);
//   fChain->SetBranchAddress("gParticlePhi", &gParticlePhi, &b_gParticlePhi);
//   fChain->SetBranchAddress("gParticleProdVertexX", &gParticleProdVertexX, &b_gParticleProdVertexX);
//   fChain->SetBranchAddress("gParticleProdVertexY", &gParticleProdVertexY, &b_gParticleProdVertexY);
//   fChain->SetBranchAddress("gParticleProdVertexZ", &gParticleProdVertexZ, &b_gParticleProdVertexZ);
//   fChain->SetBranchAddress("gParticleDecayVertexX", &gParticleDecayVertexX, &b_gParticleDecayVertexX);
//   fChain->SetBranchAddress("gParticleDecayVertexY", &gParticleDecayVertexY, &b_gParticleDecayVertexY);
//   fChain->SetBranchAddress("gParticleDecayVertexZ", &gParticleDecayVertexZ, &b_gParticleDecayVertexZ);
   Notify();
}

Bool_t TrigEff::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TrigEff::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TrigEff::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TrigEff_cxx
