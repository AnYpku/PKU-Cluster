import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True),
				     SkipEvent = cms.untracked.vstring('ProductNotFound'))
corrJetsOnTheFly = True
runOnMC = True
chsorpuppi = True  # AK4Chs or AK4Puppi
#****************************************************************************************************#
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
process.load("RecoTracker.CkfPattern.CkfTrackCandidates_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
if runOnMC:
#   process.GlobalTag.globaltag = '94X_mc2017_realistic_v17'
   process.GlobalTag.globaltag = '102X_mc2017_realistic_v7'
elif not(runOnMC):
   process.GlobalTag.globaltag = '94X_dataRun2_v11'

##########					                                                             
hltFiltersProcessName = 'RECO'
if runOnMC:
   hltFiltersProcessName = 'PAT' #'RECO'
reducedConversionsName = 'RECO'
if runOnMC:
   reducedConversionsName= 'PAT' #'RECO'

process.load("VAJets.PKUCommon.goodMuons_cff")
process.load("VAJets.PKUCommon.goodElectrons_cff")
process.load("VAJets.PKUCommon.goodJets_cff")
process.load("VAJets.PKUCommon.goodPhotons_cff")
process.load("VAJets.PKUCommon.leptonicZ_cff")

#for egamma smearing
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
                       era="2017-Nov17ReReco",
		       runVID= False)
#for egamma smearing

# If Update
process.goodMuons.src = "slimmedMuons"
process.goodElectrons.src = "slimmedElectrons"
process.goodPhotons.src = "slimmedPhotons"

if chsorpuppi:
       process.goodAK4Jets.src = "slimmedJets"
else:
      process.goodAK4Jets.src = "slimmedJetsPuppi"

#from RecoJets.JetProducers.PileupJetID_cfi import _chsalgos_94x, _chsalgos_102x
#process.load("RecoJets.JetProducers.PileupJetID_cfi")
#process.pileupJetId.jets = cms.InputTag("goodAK4Jets")
#process.pileupJetId.inputIsCorrected = True
#process.pileupJetId.applyJec = False
#process.pileupJetId.vertexes = cms.InputTag("offlineSlimmedPrimaryVertices")
#process.pileupJetId.algos = cms.VPSet(_chsalgos_94x) # for 2017
#process.pileupJetId.algos = cms.VPSet(_chsalgos_102x) # for 2018

#from RecoJets.JetProducers.PileupJetID_cfi import _chsalgos_94x, _chsalgos_102x
#process.load("RecoJets.JetProducers.PileupJetID_cfi")
#process.pileupJetIdUpdated = pileupJetId.clone(
#		jets=cms.InputTag("slimmedJets"),
#		inputIsCorrected=True,
#		applyJec=False,
#		vertexes=cms.InputTag("offlineSlimmedPrimaryVertices")
#               algos = cms.VPSet(_chsalgos_94x)
#		)

ZBOSONCUT = "pt > 0.0"
process.leptonicVSelector = cms.EDFilter("CandViewSelector",
                                       src = cms.InputTag("leptonicV"),
                                       cut = cms.string( ZBOSONCUT ), 
                                       filter = cms.bool(False)
                                       )

process.leptonicVFilter = cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("leptonicV"),
                                       minNumber = cms.uint32(0)
#                                       filter = cms.bool(False)
                                       )

process.leptonSequence = cms.Sequence(process.muSequence +
                                      process.egammaPostRecoSeq*process.slimmedElectrons*process.slimmedPhotons+
                                      process.eleSequence +
                                      process.leptonicVSequence +
                                      process.leptonicVSelector +
                                      process.leptonicVFilter )

process.jetSequence = cms.Sequence(process.NJetsSequence)

process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.load("RecoMET.METFilters.BadChargedCandidateFilter_cfi")
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")
process.metfilterSequence = cms.Sequence(process.BadPFMuonFilter+process.BadChargedCandidateFilter)

#begin------------JEC on the fly--------
if runOnMC:
   jecLevelsAK4chs = [
          'Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFchs.txt',
          'Fall17_17Nov2017_V32_MC_L2Relative_AK4PFchs.txt',
          'Fall17_17Nov2017_V32_MC_L3Absolute_AK4PFchs.txt'
    ]
   jecLevelsAK4puppi = [
          'Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFPuppi.txt',
          'Fall17_17Nov2017_V32_MC_L2Relative_AK4PFPuppi.txt',
          'Fall17_17Nov2017_V32_MC_L3Absolute_AK4PFPuppi.txt'
    ]
else:
   jecLevelsAK4chs = [
          'Fall17_17Nov2017B_V32_DATA_L1FastJet_AK4PFchs.txt',
          'Fall17_17Nov2017B_V32_DATA_L2Relative_AK4PFchs.txt',
          'Fall17_17Nov2017B_V32_DATA_L3Absolute_AK4PFchs.txt',
	  'Fall17_17Nov2017B_V32_DATA_L2L3Residual_AK4PFchs.txt'
    ]
   jecLevelsAK4puppi = [
          'Fall17_17Nov2017B_V32_DATA_L1FastJet_AK4PFPuppi.txt',
          'Fall17_17Nov2017B_V32_DATA_L2Relative_AK4PFPuppi.txt',
          'Fall17_17Nov2017B_V32_DATA_L3Absolute_AK4PFPuppi.txt',
	  'Fall17_17Nov2017B_V32_DATA_L2L3Residual_AK4PFPuppi.txt'
    ]
#end------------JEC on the fly--------

if chsorpuppi:
      ak4jecsrc = jecLevelsAK4chs
else:
      ak4jecsrc = jecLevelsAK4puppi

process.treeDumper = cms.EDAnalyzer("ZPKUTreeMaker",
                                    originalNEvents = cms.int32(1),
                                    crossSectionPb = cms.double(1),
                                    targetLumiInvPb = cms.double(1.0),
                                    PKUChannel = cms.string("VW_CHANNEL"),
                                    isGen = cms.bool(False),
				    RunOnMC = cms.bool(runOnMC), 
                                    generator =  cms.InputTag("generator"),
				    lhe =  cms.InputTag("externalLHEProducer"),
				    genJet =  cms.InputTag("slimmedGenJets"),
                                    pileup  =   cms.InputTag("slimmedAddPileupInfo"),
                                    leptonicVSrc = cms.InputTag("leptonicV"),
                                    rho = cms.InputTag("fixedGridRhoFastjetAll"),   
                                    ak4jetsSrc = cms.InputTag("cleanAK4Jets"),      
                                    genSrc =  cms.InputTag("prunedGenParticles"),       
                                    jecAK4chsPayloadNames = cms.vstring( jecLevelsAK4chs ),
                                    jecAK4PayloadNames = cms.vstring( ak4jecsrc ),
                                    metSrc = cms.InputTag("slimmedMETs"),
                                    vertex = cms.InputTag("offlineSlimmedPrimaryVertices"),  
                                    t1jetSrc = cms.InputTag("slimmedJets"),      
                                    t1muSrc = cms.InputTag("slimmedMuons"),       
                                    electrons = cms.InputTag("slimmedElectrons"),
                                    photonSrc = cms.InputTag("slimmedPhotons"),
                                    fakeelectronSrc = cms.InputTag("fakeElectrons"),
                                    looseelectronSrc = cms.InputTag("vetoElectrons"),
                                    conversions = cms.InputTag("reducedEgamma","reducedConversions",reducedConversionsName),
                                    beamSpot = cms.InputTag("offlineBeamSpot","","RECO"),
                                    loosemuonSrc = cms.InputTag("looseMuons"),
                                    loosetightmuonSrc = cms.InputTag("loosetightMuons"),
				    goodmuonSrc = cms.InputTag("goodMuons"),# station2 retrieve, 2017/3/26
				    goodeleSrc = cms.InputTag("goodElectrons"),# retreive electron sigma_ieie for shape correction
                                    hltToken    = cms.InputTag("TriggerResults","","HLT"),

                                    elPaths1     = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*"),#B-F
                                    elPaths2     = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),#B-F
                                    elPaths3     = cms.vstring("HLT_Ele35_WPTight_Gsf_v*"),#B-F
                                    elPaths4     = cms.vstring("HLT_Ele38_WPTight_Gsf_v*"),#add by Ying
                                    elPaths5     = cms.vstring("HLT_Ele40_WPTight_Gsf_v*"),#add by Ying
                                    muPaths1 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*"),#B
                                    muPaths2 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*"),#C-F
                                    muPaths3 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*"),#B
				    muPaths4 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*"),#C-F
				    muPaths5 = cms.vstring("HLT_IsoMu27_v*"),#B-F
				    muPaths6 = cms.vstring("HLT_IsoMu24_eta2p1_v*"),#B-D

				    noiseFilter = cms.InputTag('TriggerResults','', hltFiltersProcessName),
				    noiseFilterSelection_HBHENoiseFilter = cms.string('Flag_HBHENoiseFilter'),
                                    noiseFilterSelection_HBHENoiseIsoFilter = cms.string("Flag_HBHENoiseIsoFilter"),
                                    noiseFilterSelection_globalTightHaloFilter = cms.string('Flag_globalTightHalo2017Filter'),
                                    noiseFilterSelection_EcalDeadCellTriggerPrimitiveFilter = cms.string('Flag_EcalDeadCellTriggerPrimitiveFilter'),
				    noiseFilterSelection_goodVertices = cms.string('Flag_goodVertices'),
				    noiseFilterSelection_eeBadScFilter = cms.string('Flag_eeBadScFilter'),
                                    noiseFilterSelection_badMuon = cms.InputTag('BadPFMuonFilter'),
                                    noiseFilterSelection_badChargedHadron = cms.InputTag('BadChargedCandidateFilter'),
				    badMuonFilterSelection = cms.string('Flag_badMuons'),
				    duplicateMuonFilterSelection = cms.string('Flag_duplicateMuons'),
                                    )

process.analysis = cms.Path(
                            process.leptonSequence+ 
                            process.jetSequence +
                            process.metfilterSequence +
			    process.treeDumper
                           )

### Source
process.load("VAJets.PKUCommon.data.RSGravitonToWW_kMpl01_M_1000_Tune4C_13TeV_pythia8")
process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
		       "/store/mc/RunIIFall17MiniAODv2/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/40000/766C7223-B52D-E911-92E0-1866DA85DFA0.root"
		),
   )
         
                       
process.maxEvents.input = 100

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 20
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("Ztest.root")
                                   )

