import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True),
				     SkipEvent = cms.untracked.vstring('ProductNotFound'))
corrJetsOnTheFly = True
runOnMC = True #False
chsorpuppi = True  # AK4Chs or AK4Puppi
#****************************************************************************************************#
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("RecoTracker.CkfPattern.CkfTrackCandidates_cff")
process.load("TrackPropagation.SteppingHelixPropagator.SteppingHelixPropagatorAlong_cfi")
from Configuration.AlCa.GlobalTag import GlobalTag
if runOnMC:
   process.GlobalTag.globaltag = '102X_upgrade2018_realistic_v18'
elif not(runOnMC):
   process.GlobalTag.globaltag = '102X_dataRun2_Sep2018ABC_v2'

##########					                                                             
hltFiltersProcessName = 'RECO'
if runOnMC:
   hltFiltersProcessName = 'PAT' #'RECO'
reducedConversionsName = 'RECO'
if runOnMC:
   reducedConversionsName= 'PAT' #'RECO'

process.load("VAJets.PKUCommon.goodMuons_cff")
process.load("VAJets.PKUCommon.goodElectrons_cff")
process.load("VAJets.PKUCommon.goodPhotons_cff")
process.load("VAJets.PKUCommon.leptonicZ_cff")

#for egamma smearing
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
                       era="2018-Prompt",
                       runEnergyCorrections=False#True: do egamma_modification
                      )
#for egamma smearing

# If Update
process.goodMuons.src = "slimmedMuons"
process.goodElectrons.src = "slimmedElectrons"
process.goodPhotons.src = "slimmedPhotons"

# jerc uncer 2017/5/7
if chsorpuppi:
        jLabel = "slimmedJets"
        jetAlgo    = 'AK4PFchs'
else:
      jLabel = "slimmedJetsPuppi"
      jetAlgo    = 'AK4PFPuppi'

jer_era = "Autumn18_V8_MC"
triggerResultsLabel      = "TriggerResults"
triggerSummaryLabel      = "hltTriggerSummaryAOD"
hltProcess = "HLT"
jetUncSources = [
        'AbsoluteStat',
        'AbsoluteScale',
        'AbsoluteMPFBias',
        'AbsoluteSample',
        'Fragmentation',
        'SinglePionECAL',
        'SinglePionHCAL',
        'FlavorQCD',
        'TimePtEta',
        'RelativeJEREC1',
        'RelativeJEREC2',
        'RelativeJERHF',
        'RelativePtBB',
        'RelativePtEC1',
        'RelativePtEC2',
        'RelativePtHF',
        'RelativeBal',
        'RelativeSample',
        'RelativeFSR',
        'RelativeStatFSR',
        'RelativeStatEC',
        'RelativeStatHF',
        'PileUpDataMC',
        'PileUpPtRef',
        'PileUpPtBB',
        'PileUpPtEC1',
        'PileUpPtEC2',
        'PileUpPtHF',
        'Total',
          ]
#begin------------JEC on the fly--------
if runOnMC:
   jetUncFiles= "Autumn18_V8_MC_UncertaintySources_AK4PFchs.txt"
   jecLevelsAK4chs = [
          'Autumn18_V8_MC_L1FastJet_AK4PFchs.txt',
          'Autumn18_V8_MC_L2Relative_AK4PFchs.txt',
          'Autumn18_V8_MC_L3Absolute_AK4PFchs.txt'
    ]
   jecLevelsAK4puppi = [
          'Autumn18_V8_MC_L1FastJet_AK4PFPuppi.txt',
          'Autumn18_V8_MC_L2Relative_AK4PFPuppi.txt',
          'Autumn18_V8_MC_L3Absolute_AK4PFPuppi.txt'
    ]
else:
   jetUncFiles= "Autumn18_V8_MC_UncertaintySources_AK4PFchs.txt"
   jecLevelsAK4chs = [
          'Autumn18_RunB_V8_DATA_L1FastJet_AK4PFchs.txt',
          'Autumn18_RunB_V8_DATA_L2Relative_AK4PFchs.txt',
          'Autumn18_RunB_V8_DATA_L3Absolute_AK4PFchs.txt',
          'Autumn18_RunB_V8_DATA_L2L3Residual_AK4PFchs.txt'
    ]
   jecLevelsAK4puppi = [
          'Autumn18_RunB_V8_DATA_L1FastJet_AK4PFPuppi.txt',
          'Autumn18_RunB_V8_DATA_L2Relative_AK4PFPuppi.txt',
          'Autumn18_RunB_V8_DATA_L3Absolute_AK4PFPuppi.txt',
          'Autumn18_RunB_V8_DATA_L2L3Residual_AK4PFPuppi.txt'
    ]
#end------------JEC on the fly--------

process.JetUserData = cms.EDProducer(
   'JetUserData',
   jetLabel          = cms.InputTag(jLabel),
   rho               = cms.InputTag("fixedGridRhoFastjetAll"),
   coneSize          = cms.double(0.4),
   getJERFromTxt     = cms.bool(False),
   jetCorrLabel      = cms.string(jetAlgo),
   jerLabel          = cms.string(jetAlgo),
   resolutionsFile   = cms.string(jer_era+'_PtResolution_'+jetAlgo+'.txt'),
   scaleFactorsFile  = cms.string(jer_era+'_SF_'+jetAlgo+'.txt'),
   ### TTRIGGER ###
   triggerResults = cms.InputTag(triggerResultsLabel,"",hltProcess),
   triggerSummary = cms.InputTag(triggerSummaryLabel,"",hltProcess),
   hltJetFilter       = cms.InputTag("hltPFHT"),
   hltPath            = cms.string("HLT_PFHT800"),
   hlt2reco_deltaRmax = cms.double(0.2),
   candSVTagInfos         = cms.string("pfInclusiveSecondaryVertexFinder"), 
   jecAK4chsPayloadNames_jetUserdata = cms.vstring( jecLevelsAK4chs ),
   jecAK4chs_sources  = cms.vstring(jetUncSources),
   jecAK4chs_Uncfile  = cms.string(jetUncFiles),
   vertex_jetUserdata = cms.InputTag("offlineSlimmedPrimaryVertices")
   )
#jerc uncer Meng

process.load("VAJets.PKUCommon.goodJets_cff") 
if chsorpuppi:
#      process.goodAK4Jets.src = "slimmedJets"
	process.goodAK4Jets.src = "JetUserData"
	# jerc uncer Meng
else:
      process.goodAK4Jets.src = "slimmedJetsPuppi"

ZBOSONCUT = "pt > 0.0"

process.leptonSequence = cms.Sequence(process.muSequence +
                                      process.egammaPostRecoSeq*process.slimmedElectrons*process.slimmedPhotons+
                                      process.eleSequence +
                                      process.leptonicVSequence 
		                     )
process.jetSequence = cms.Sequence(process.NJetsSequence)

if chsorpuppi:
      ak4jecsrc = jecLevelsAK4chs
else:
      ak4jecsrc = jecLevelsAK4puppi

process.load("RecoEgamma/PhotonIdentification/photonIDValueMapProducer_cfi") 
process.treeDumper = cms.EDAnalyzer("ZPKUTreeMaker",
                                    originalNEvents = cms.int32(1),
                                    crossSectionPb = cms.double(1),
                                    targetLumiInvPb = cms.double(1.0),
                                    PKUChannel = cms.string("VW_CHANNEL"),
                                    isGen = cms.bool(False),
				    RunOnMC = cms.bool(runOnMC), 
                                    generator =  cms.InputTag("generator"),
				    genJet =  cms.InputTag("slimmedGenJets"),
                                    pileup  =   cms.InputTag("slimmedAddPileupInfo"),
                                    leptonicVSrc = cms.InputTag("leptonicV"),
                                    rho = cms.InputTag("fixedGridRhoFastjetAll"),   
                                    ak4jetsSrc = cms.InputTag("cleanAK4Jets"),      
                                    #photonSrc = cms.InputTag("calibratedPatPhotons"),
                                    photonSrc = cms.InputTag("slimmedPhotons"),
                                    genSrc =  cms.InputTag("prunedGenParticles"),       
                                    jecAK4chsPayloadNames = cms.vstring( jecLevelsAK4chs ),
                                    jecAK4PayloadNames = cms.vstring( ak4jecsrc ),
                                    jecAK4chs_sources = cms.vstring( jetUncSources ),
                                    metSrc = cms.InputTag("slimmedMETs"),
                                    vertex = cms.InputTag("offlineSlimmedPrimaryVertices"),  
                                    t1jetSrc_user = cms.InputTag("JetUserData"),
				    t1jetSrc = cms.InputTag("slimmedJets"),      
                                    t1muSrc = cms.InputTag("slimmedMuons"),       
                                    looseelectronSrc = cms.InputTag("vetoElectrons"),
                                    electrons = cms.InputTag("slimmedElectrons"),
                                    conversions = cms.InputTag("reducedEgamma","reducedConversions",reducedConversionsName),
                                    beamSpot = cms.InputTag("offlineBeamSpot","","RECO"),
                                    loosemuonSrc = cms.InputTag("looseMuons"),
				    goodmuonSrc = cms.InputTag("goodMuons"),# station2 retrieve, 2017/3/26
                                    hltToken    = cms.InputTag("TriggerResults","","HLT"),
				    elPaths1     = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*"),
                                    elPaths2     = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),
				    elPaths3     = cms.vstring("HLT_Ele35_WPTight_Gsf_v*"),#B-F
                                    elPaths4     = cms.vstring("HLT_Ele38_WPTight_Gsf_v*"),#add by Ying
                                    elPaths5     = cms.vstring("HLT_Ele40_WPTight_Gsf_v*"),#add by Ying
                                    muPaths1 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*"),#B
                                    muPaths2 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*"),#C-F
                                    muPaths3 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*"),#B
                                    muPaths4 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*"),#C-F
                                    muPaths5 = cms.vstring("HLT_IsoMu27_v*"),#B-F
                                    muPaths6 = cms.vstring("HLT_IsoMu24_eta2p1_v*"),#B-D
                                    )
process.options.numberOfThreads=cms.untracked.uint32(8)
process.options.numberOfStreams=cms.untracked.uint32(0)

process.analysis = cms.Path(
			    process.JetUserData +
                            process.leptonSequence +
                            process.jetSequence +
                            process.treeDumper)

### Source
process.load("VAJets.PKUCommon.data.RSGravitonToWW_kMpl01_M_1000_Tune4C_13TeV_pythia8")
process.source.fileNames = [
"/store/mc/RunIIAutumn18MiniAOD/LLAJJ_EWK_MLL-50_MJJ-120_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/50000/FFB5CFC2-5C22-204A-83AF-AF9B28B6C0E6.root"
]
                       
process.maxEvents.input = 500 

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 50
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("ZA-EWK_2.root")
                                   )
