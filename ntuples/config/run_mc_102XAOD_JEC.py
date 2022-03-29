import FWCore.ParameterSet.Config as cms

##########################################################################################
# Setup

# this is the process run by cmsRun
process = cms.Process('LLDJ')

process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(4)
process.options.numberOfStreams=cms.untracked.uint32(0)
#process.options.SkipEvent = cms.untracked.vstring('ProductNotFound')
process.load("RecoTracker.TkNavigation.NavigationSchoolESProducer_cfi")

# log output
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )  ## number of events -1 does all
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# input files
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring(

#'root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18DRPremix/ZH_HToSSTobbbb_ZToLL_MH-125_TuneCP5_13TeV-powheg-pythia8/AODSIM/rp_102X_upgrade2018_realistic_v15-v1/70000/DE707F97-D109-6D4B-B733-AF2B0D53D26E.root'
'file:/afs/cern.ch/work/d/ddiaz/HLT_Run3/CMSSW_12_3_0_pre4/src/HLT_Run3/Eff/output_minimal.root'
 ),
)

# output name
process.TFileService = cms.Service('TFileService', fileName = cms.string('lldjntuple_mc_AOD.root'));


process.output = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    ),
    dropMetaData = cms.untracked.string('ALL'),
    eventAutoFlushCompressedSize = cms.untracked.int32(-900),
    fastCloning = cms.untracked.bool(False),
    fileName = cms.untracked.string('miniAOD-prod_PAT.root'),
    outputCommands = cms.untracked.vstring('keep *'),
)

# In EGamma POG PostRecoTools twiki, instead of two above
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")

# global tag
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = '102X_upgrade2018_realistic_v21'#2018 GT for MC


process.load('JetMETCorrections.Configuration.JetCorrectors_cff')


# Produce corrected jets collection
process.ak4CaloCorrectedJets   = cms.EDProducer('CorrectedCaloJetProducer',
    src         = cms.InputTag('ak4CaloJets'),
    #L1(PU), L2L3(MCTruth)
    correctors  = cms.VInputTag('ak4CaloL1FastL2L3Corrector')
    )

# pat for trigger
process.load( 'PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff' )

# pat for muons
process.load('PhysicsTools.PatAlgos.patSequences_cff')

##from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
#from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
#setupEgammaPostRecoSeq(process,
#                       runVID=True,
#                       era='2018-Prompt',
#		       isMiniAOD=False,
#		       eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff'],
#		       phoIDModules=['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
##		       phoIDModules=[]
#)

# For AOD Track variables
process.MaterialPropagator = cms.ESProducer('PropagatorWithMaterialESProducer',
    ComponentName = cms.string('PropagatorWithMaterial'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)

process.TransientTrackBuilderESProducer = cms.ESProducer('TransientTrackBuilderESProducer',
    ComponentName = cms.string('TransientTrackBuilder')
)


#NTuplizer
process.lldjNtuple = cms.EDAnalyzer('lldjNtuple',

 doAOD                     = cms.bool(True),
 doMiniAOD                 = cms.bool(False),
 is2016                    = cms.bool(False),

# electronSrc               = cms.InputTag('selectedElectrons','','LLDJ'),
# rhoLabel                  = cms.InputTag('fixedGridRhoFastjetAll'),
# eleHLTIdMap               = cms.InputTag('egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer17-V2'),
#
# rhoCentralLabel           = cms.InputTag('fixedGridRhoFastjetCentralNeutral'),
# pileupCollection          = cms.InputTag('slimmedAddPileupInfo'),
# AODpileupCollection       = cms.InputTag('addPileupInfo', '', 'HLT'),
# VtxLabel                  = cms.InputTag('offlineSlimmedPrimaryVertices'),
# triggerResults            = cms.InputTag('TriggerResults', '', 'HLT'),
#
 AODTriggerInputTag           = cms.InputTag("TriggerResults","","HLT"),
 AODTriggerEventInputTag      = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
#
# beamspotLabel_            = cms.InputTag('offlineBeamSpot'),
#
# AODak4CaloJetsSrc         = cms.InputTag('ak4CaloJets' , '', 'RECO'),
# AODak4CorrCaloJetsSrc     = cms.InputTag('ak4CaloCorrectedJets'),
# AODak4CorrectorLabelName  = cms.InputTag('ak4CaloL1FastL2L3Corrector'),
# AODVertexSrc              = cms.InputTag('offlinePrimaryVertices', '', 'RECO'),
# AODTrackSrc               = cms.InputTag('generalTracks', '', 'RECO'),
# vertexFitterConfig = cms.PSet(
#        finder = cms.string('avf'),
#        sigmacut = cms.double(10.),
#        Tini = cms.double(256.),
#        ratio = cms.double(0.25),
#        ),
#
# patTriggerResults         = cms.InputTag('TriggerResults', '', 'PAT'),
# BadChargedCandidateFilter = cms.InputTag('BadChargedCandidateFilter'),
# BadPFMuonFilter           = cms.InputTag('BadPFMuonFilter'),
# AODCaloMETlabel           = cms.InputTag('caloMet','','RECO'),
#
# muonSrc                   = cms.InputTag('slimmedMuons'),
# muonAODSrc                = cms.InputTag('selectedPatMuons'),
#
# photonAODSrc              = cms.InputTag('gedPhotons'),
#
# electronAODSrc = cms.InputTag("gedGsfElectrons"),
# AOD_eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-loose"),
# AOD_eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-medium"),
# AOD_eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-tight"),
# conversions  = cms.InputTag('allConversions'),
#
# genParticleSrc    = cms.InputTag("genParticles"),
#
 bits = cms.InputTag("TriggerResults","","HLT"),
 prescales = cms.InputTag("patTrigger"),
 objects = cms.InputTag("selectedPatTrigger"),

)

## Double check: this is to remove the OOT photons, which is causing a crash
#process.patCandidates.remove(process.patCandidateSummary)
#process.patCandidatesTask.remove(process.makePatOOTPhotonsTask)
#process.selectedPatCandidates.remove(process.selectedPatCandidateSummary)
#process.selectedPatCandidatesTask.remove(process.selectedPatOOTPhotons)


process.p = cms.Path(
        #process.egammaPostRecoSeq *
        #process.ak4CaloCorrectedJets *
        #process.ak4CaloL1FastL2L3CorrectorChain *
        #process.particleFlowPtrs *
        #process.patCandidates *
        #process.selectedPatCandidates *
        process.lldjNtuple
        )

process.schedule = cms.Schedule(process.p)



