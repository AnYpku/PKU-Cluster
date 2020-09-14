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
   process.GlobalTag.globaltag = '94X_mcRun2_asymptotic_v3'
elif not(runOnMC):
   process.GlobalTag.globaltag = '94X_dataRun2_v10'

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
                       era="2016-Legacy",
                       runVID=True,
                       runEnergyCorrections=False,#True: do egamma_modification
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

jer_era = "Summer16_07Aug2017_V11_MC"
triggerResultsLabel      = "TriggerResults"
triggerSummaryLabel      = "hltTriggerSummaryAOD"
hltProcess = "HLT"
jetUncSources = [
            'AbsoluteStat',
            'AbsoluteScale',
            'AbsoluteMPFBias',
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
          ]
#begin------------JEC on the fly--------
if runOnMC:
   jetUncFiles= "Summer16_07Aug2017_V11_MC_UncertaintySources_AK4PFchs.txt"
   jecLevelsAK4chs = [
          'Summer16_07Aug2017_V11_MC_L1FastJet_AK4PFchs.txt',
          'Summer16_07Aug2017_V11_MC_L2Relative_AK4PFchs.txt',
          'Summer16_07Aug2017_V11_MC_L3Absolute_AK4PFchs.txt'
    ]
   jecLevelsAK4puppi = [
          'Summer16_07Aug2017_V11_MC_L1FastJet_AK4PFPuppi.txt',
          'Summer16_07Aug2017_V11_MC_L2Relative_AK4PFPuppi.txt',
          'Summer16_07Aug2017_V11_MC_L3Absolute_AK4PFPuppi.txt'
    ]
else:
   jetUncFiles= "Summer16_07Aug2017BCD_V11_DATA_UncertaintySources_AK4PFchs.txt"
   jecLevelsAK4chs = [
          'Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK4PFchs.txt',
          'Summer16_07Aug2017BCD_V11_DATA_L2Relative_AK4PFchs.txt',
          'Summer16_07Aug2017BCD_V11_DATA_L3Absolute_AK4PFchs.txt',
          'Summer16_07Aug2017BCD_V11_DATA_L2L3Residual_AK4PFchs.txt'
    ]
   jecLevelsAK4puppi = [
          'Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK4PFPuppi.txt',
          'Summer16_07Aug2017BCD_V11_DATA_L2Relative_AK4PFPuppi.txt',
          'Summer16_07Aug2017BCD_V11_DATA_L3Absolute_AK4PFPuppi.txt',
          'Summer16_07Aug2017BCD_V11_DATA_L2L3Residual_AK4PFPuppi.txt'
    ]
#end------------JEC on the fly--------
#from PhysicsTools.PatUtils.l1ECALPrefiringWeightProducer_cfi import l1ECALPrefiringWeightProducer
#process.prefiringweight = l1ECALPrefiringWeightProducer.clone(
#    DataEra = cms.string("2016BtoH"), #Use 2016BtoH for 2016
#    UseJetEMPt = cms.bool(False),
#    PrefiringRateSystematicUncty = cms.double(0.2),
#    SkipWarnings = False)
process.prefiringweight = cms.EDProducer("L1ECALPrefiringWeightProducer",
                                 ThePhotons = cms.InputTag("slimmedPhotons"),
	                         TheJets = cms.InputTag("slimmedJets"),
                                 L1Maps = cms.string("L1PrefiringMaps_new.root"), # update this line with the location of this file
                                 DataEra = cms.string("2016BtoH"), #Use 2016BtoH for 2016
                                 UseJetEMPt = cms.bool(False), #can be set to true to use jet prefiring maps parametrized vs pt(em) instead of pt
	                         PrefiringRateSystematicUncty = cms.double(0.2) #Minimum relative prefiring uncty per object
                                 )
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
   hlt2reco_deltaRmax = cms.double(0.2),
   candSVTagInfos         = cms.string("pfInclusiveSecondaryVertexFinder"), 
   jecAK4chsPayloadNames_jetUserdata = cms.vstring( jecLevelsAK4chs ),
   jecAK4chs_sources  = cms.vstring(jetUncSources),
   jecAK4chs_Uncfile  = cms.string(jetUncFiles),
   hltPath            = cms.string("HLT_PFHT800"),
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

#process.goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
#                                       src = cms.InputTag("offlineSlimmedPrimaryVertices"),
#                                       cut = cms.string("chi2!=0 && ndof >= 4.0 && abs(z) <= 24.0 && abs(position.Rho) <= 2.0"),
#                                       filter = cms.bool(False)
#                                       )

ZBOSONCUT = "pt > 0.0"

process.leptonicVSelector = cms.EDFilter("CandViewSelector",
                                       src = cms.InputTag("leptonicV"),
                                       cut = cms.string( ZBOSONCUT ), 
                                       filter = cms.bool(False)
                                       )

process.leptonicVFilter = cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("leptonicV"),
                                       minNumber = cms.uint32(0),
                                       filter = cms.bool(False)
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

if chsorpuppi:
      ak4jecsrc = jecLevelsAK4chs
else:
      ak4jecsrc = jecLevelsAK4puppi

#process.load("RecoEgamma/PhotonIdentification/PhotonIDValueMapProducer_cfi")
   
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
                                    photonSrc = cms.InputTag("slimmedPhotons"),
                                    genSrc =  cms.InputTag("prunedGenParticles"),       
                                    jecAK4chsPayloadNames = cms.vstring( jecLevelsAK4chs ),
                                    jecAK4chs_sources = cms.vstring( jetUncSources ),
                                    jecAK4PayloadNames = cms.vstring( ak4jecsrc ),
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
                                    elPaths1     = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*"),#B-F
                                    elPaths2     = cms.vstring("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"),#B-F
                                    elPaths3     = cms.vstring("HLT_Ele35_WPTight_Gsf_v*"),#B-F
                                    elPaths4     = cms.vstring("HLT_Ele38_WPTight_Gsf_v*"),#add by Ying
                                    elPaths5     = cms.vstring("HLT_Ele40_WPTight_Gsf_v*"),#add by Ying

                                    muPaths1     = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*"),#B
                                    muPaths2    = cms.vstring("HLT_IsoMu24_eta2p1_v*"),#B-D
                                    muPaths3     = cms.vstring("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_3p8_v*"),#C-F
                                    muPaths4     = cms.vstring("HLT_IsoMu27_v*"),#B-F
                                    muPaths5     = cms.vstring("HLT_IsoMu20_v*"),# add by Ying
                                    muPaths6     = cms.vstring("HLT_IsoMu24_v*"),# add by Ying
				    noiseFilter = cms.InputTag('TriggerResults','', hltFiltersProcessName),
				    noiseFilterSelection_HBHENoiseFilter = cms.string('Flag_HBHENoiseFilter'),
                                    noiseFilterSelection_HBHENoiseIsoFilter = cms.string("Flag_HBHENoiseIsoFilter"),
                                    noiseFilterSelection_globalTightHaloFilter = cms.string('Flag_globalTightHalo2016Filter'),
                                    noiseFilterSelection_EcalDeadCellTriggerPrimitiveFilter = cms.string('Flag_EcalDeadCellTriggerPrimitiveFilter'),
				    noiseFilterSelection_goodVertices = cms.string('Flag_goodVertices'),
				    noiseFilterSelection_eeBadScFilter = cms.string('Flag_eeBadScFilter'),
                                    noiseFilterSelection_badMuon = cms.InputTag('BadPFMuonFilter'),
                                    noiseFilterSelection_badChargedHadron = cms.InputTag('BadChargedCandidateFilter'),
                #Meng
                                    badMuonFilterSelection = cms.string('Flag_badMuons'),
                                    duplicateMuonFilterSelection = cms.string('Flag_duplicateMuons'),
                #Lu
				    full5x5SigmaIEtaIEtaMap   = cms.InputTag("photonIDValueMapProducer:phoFull5x5SigmaIEtaIEta"),
                                    phoChargedIsolation = cms.InputTag("photonIDValueMapProducer:phoChargedIsolation"),
                                    phoNeutralHadronIsolation = cms.InputTag("photonIDValueMapProducer:phoNeutralHadronIsolation"),
                                    phoPhotonIsolation = cms.InputTag("photonIDValueMapProducer:phoPhotonIsolation"),
#                                    effAreaChHadFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Fall17/effAreaPhotons_cone03_pfChargedHadrons_90percentBased_V2.txt"),
#                                    effAreaNeuHadFile= cms.FileInPath("RecoEgamma/PhotonIdentification/data/Fall17/effAreaPhotons_cone03_pfNeutralHadrons_90percentBased.txt"),
#                                    effAreaPhoFile   = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Fall17/effAreaPhotons_cone03_pfPhotons_90percentBased.txt")
                                    )


process.analysis = cms.Path(
			    process.JetUserData +
                            process.leptonSequence +
                            process.jetSequence +
                            process.metfilterSequence +
                            process.prefiringweight*process.treeDumper)

### Source
process.load("VAJets.PKUCommon.data.RSGravitonToWW_kMpl01_M_1000_Tune4C_13TeV_pythia8")
process.source.fileNames = [
#"file:/eos/uscms/store/mc/RunIISummer16MiniAODv2/TprimeTprimeToTHTH_HToGammaGamma_M-600_TuneCUETP8M2T4_13TeV-madgraph-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/60000/641784F0-2BD8-E611-ABC5-02163E013616.root"
#"/store/mc/RunIISummer16MiniAODv3/ZGToLLG_01J_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v1/70000/8A1C2443-5764-E911-920A-001E67444E66.root"
"file:./8A1C2443-5764-E911-920A-001E67444E66.root"
]
                       
process.maxEvents.input = 100

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("ZtreePKU.root")
                                   )
