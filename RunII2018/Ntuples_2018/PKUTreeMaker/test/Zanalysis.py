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
#process.load("VAJets.PKUCommon.goodJets_cff")
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
process.goodMuons.src ="slimmedMuons" 
process.goodElectrons.src = cms.InputTag( "slimmedElectrons")
process.goodPhotons.src =cms.InputTag("slimmedPhotons")

process.load("VAJets.PKUCommon.goodJets_cff") 
if chsorpuppi:
      process.goodAK4Jets.src = "slimmedJets"
      #process.goodAK4Jets.src = "selectedPatJetsPFlow"
else:
      process.goodAK4Jets.src = "slimmedJetsPuppi"

ZBOSONCUT = "pt > 0.0"

process.leptonSequence = cms.Sequence(process.muSequence +
				      process.egammaPostRecoSeq*process.slimmedElectrons*process.slimmedPhotons+
                                      process.eleSequence+ 
                                      process.leptonicVSequence 
		                     )

process.jetSequence = cms.Sequence(process.NJetsSequence)

#begin------------JEC on the fly--------
if runOnMC:
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
                                    #ak4jetsSrc = cms.InputTag("goodAK4Jets"),      
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
                                    elPaths5     = cms.vstring("HLT_DoubleEle25_CaloIdL_MW_v*"),#add by Ying
                                    muPaths1 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*"),#B
                                    muPaths2 = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*"),#C-F
                                    muPaths3 = cms.vstring("HLT_IsoMu24_v*"),#B
				    muPaths4 = cms.vstring("HLT_IsoMu27_v*"),#C-F
				    muPaths5 = cms.vstring("HLT_IsoMu27_v*"),#B-F
                                    )

process.analysis = cms.Path(
                            process.leptonSequence +
                            process.jetSequence +
                            process.treeDumper
                           )

### Source
process.load("VAJets.PKUCommon.data.RSGravitonToWW_kMpl01_M_1000_Tune4C_13TeV_pythia8")
process.source.fileNames = [
#"/store/mc/RunIIAutumn18MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/90000/F6F754E3-9026-CC48-9018-FFBB087DADA5.root"
"/store/mc/RunIIAutumn18MiniAOD/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15_ext1-v2/2810000/D3FAC394-3321-A742-B9B2-A908E63F60F0.root"
]
                       
process.maxEvents.input = 1000

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("Ztest3.root")
                                   )

