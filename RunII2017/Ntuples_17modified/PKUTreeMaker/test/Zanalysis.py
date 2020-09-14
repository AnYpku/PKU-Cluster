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
   process.GlobalTag.globaltag = '94X_mc2017_realistic_v17'
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
#process.load("VAJets.PKUCommon.goodJets_cff")
process.load("VAJets.PKUCommon.goodPhotons_cff")
process.load("VAJets.PKUCommon.leptonicZ_cff")

#for egamma smearing
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
#		       applyEnergyCorrections= False,#True: calibratedPat*; False: slimmed*
#    		       applyVIDOnCorrectedEgamma=False,#EnergyCorrections and VIDOnCorrectedEgamma should be same
                       #isMiniAOD=True,
                       era="2017-Nov17ReReco",
		       #eleIDModules=['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff'],
		       #phoIDModules=['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff'],
		       runVID= True,
		       runEnergyCorrections=True#True: do egamma_modification
		      )

#for egamma smearing

# If Update
process.goodMuons.src = "slimmedMuons"
process.goodElectrons.src = "slimmedElectrons"
process.goodPhotons.src = "slimmedPhotons"

process.load("VAJets.PKUCommon.goodJets_cff") 
if chsorpuppi:
      process.goodAK4Jets.src = "slimmedJets"
#       process.goodAK4Jets.src = "selectedPatJetsPFlow"
else:
      process.goodAK4Jets.src = "slimmedJetsPuppi"

#process.goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
#                                       src = cms.InputTag("offlineSlimmedPrimaryVertices"),
#                                       cut = cms.string("chi2!=0 && ndof >= 4.0 && abs(z) <= 24.0 && abs(position.Rho) <= 2.0"),
#                                       filter = cms.bool(False)
#                                       )

ZBOSONCUT = "pt > 0.0"
#from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
#process.goodPatJetsPFlow = cms.EDFilter("PFJetIDSelectionFunctorFilter",
#                                                filterParams = pfJetIDSelector.clone(),
#                                                src = cms.InputTag("selectedPatJetsPFlow"),
#                                                filter = cms.bool(True)
#                                                )
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
                                      #process.egammaPostRecoSeq*process.slimmedElectrons*process.slimmedPhotons+
		                      process.egammaPostRecoSeq+
                                      process.eleSequence +
                                      process.leptonicVSequence +
                                      process.leptonicVSelector +
                                      process.leptonicVFilter )

process.jetSequence = cms.Sequence(process.NJetsSequence)
#process.jetSequence = cms.Sequence(process.goodPatJetsPFlow)

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

process.load("RecoEgamma/PhotonIdentification/photonIDValueMapProducer_cfi")
   
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
                                    #t1jetSrc = cms.InputTag("selectedPatJetsPFlow"),      
                                    t1muSrc = cms.InputTag("slimmedMuons"),       
                                    electrons = cms.InputTag("slimmedElectrons"),
                                    photonSrc = cms.InputTag("slimmedPhotons"),
				    #electrons = cms.InputTag("calibratedPatElectrons"),
				    #photons = cms.InputTag("calibratedPatPhotons"),
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
		#Meng
				    badMuonFilterSelection = cms.string('Flag_badMuons'),
				    duplicateMuonFilterSelection = cms.string('Flag_duplicateMuons'),
		#Lu
                                    full5x5SigmaIEtaIEtaMap   = cms.InputTag("photonIDValueMapProducer:phoFull5x5SigmaIEtaIEta"),
                                    phoChargedIsolation = cms.InputTag("photonIDValueMapProducer:phoChargedIsolation"),
                                    phoNeutralHadronIsolation = cms.InputTag("photonIDValueMapProducer:phoNeutralHadronIsolation"),
                                    phoPhotonIsolation = cms.InputTag("photonIDValueMapProducer:phoPhotonIsolation"),
                                    effAreaChHadFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Fall17/effAreaPhotons_cone03_pfChargedHadrons_90percentBased_V2.txt"),
                                    effAreaNeuHadFile= cms.FileInPath("RecoEgamma/PhotonIdentification/data/Fall17/effAreaPhotons_cone03_pfNeutralHadrons_90percentBased.txt"),
                                    effAreaPhoFile   = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Fall17/effAreaPhotons_cone03_pfPhotons_90percentBased.txt")
                                    )

process.analysis = cms.Path(
#                            process.goodOfflinePrimaryVertex +
                            process.leptonSequence +
                            process.jetSequence +
                            process.metfilterSequence +
			    process.treeDumper
                           )

### Source
process.load("VAJets.PKUCommon.data.RSGravitonToWW_kMpl01_M_1000_Tune4C_13TeV_pythia8")
process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
                       #"/store/mc/RunIIFall17MiniAODv2/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/270000/F64D6117-F3D3-E811-93CA-0242AC1C0501.root"
                       #"/store/mc/RunIIFall17MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/40000/B06575F2-4642-E811-A124-A4BF01125848.root"
                       #"/store/mc/RunIIFall17MiniAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/70000/F2283B5C-6044-E811-B61D-0025905B859A.root"
                       #"/store/mc/RunIIFall17MiniAODv2/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/90000/0C16FF8C-E081-E811-B7E4-7845C4FB6238.root"
                       #"/store/mc/RunIIFall17MiniAODv2/WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/20000/3A851125-1E8E-E811-8D04-0CC47A7C35D2.root"
                       #"/store/mc/RunIIFall17MiniAODv2/TT_Mtt-700to1000_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/70000/FE424395-0F42-E811-8EFA-008CFAE452F4.root"
                       #"/store/mc/RunIIFall17MiniAODv2/TT_Mtt-1000toInf_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/30000/AE6AC49B-D2A6-E811-B1DD-90B11C4434EB.root"
                       #"/store/mc/RunIIFall17MiniAODv2/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/120000/FEED6629-6DD6-E811-8C28-E0071B745DC0.root"
		       #"/store/mc/RunIIFall17MiniAODv2/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/40000/FEBEB2B6-152E-E911-9E86-90B11CBCFF9C.root "
		       #"/store/mc/RunIIFall17MiniAODv2/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/40000/24EF20BF-A82D-E911-AB94-801844DEEFD8.root"
		       "/store/mc/RunIIFall17MiniAODv2/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/40000/766C7223-B52D-E911-92E0-1866DA85DFA0.root"
                       #"/store/mc/RunIIFall17MiniAODv2/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/50000/F4A78F89-84A4-E811-830E-AC1F6B23C594.root"
                       #"/store/mc/RunIIFall17MiniAODv2/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/710000/1CA3BF10-BA44-E811-B9B6-002590E7D7E2.root"
                       #"/store/mc/RunIIFall17MiniAODv2/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/70000/E8EAFEDF-34B1-E811-9514-FA163EA4DF9A.root"
                       #"/store/mc/RunIIFall17MiniAODv2/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/70000/FEC4FBDC-8BAC-E811-AF3B-002590DBE150.root"
                       #"/store/mc/RunIIFall17MiniAODv2/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/80000/FCE5387E-B4AE-E811-A03A-001E67792526.root"
                       #"/store/mc/RunIIFall17MiniAODv2/WW_TuneCP5_13TeV-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/70000/FE2F3D1C-3842-E811-BE71-0CC47A4D76AA.root"
                       #"/store/mc/RunIIFall17MiniAODv2/LLAJJ_EWK_MLL-50_MJJ-120_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/50000/FE3B7449-9FAB-E811-B2DC-B499BAABF37A.root"
                       #"/store/mc/RunIIFall17MiniAODv2/ZZ_TuneCP5_13TeV-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F269998D-2342-E811-8520-008CFAC93F08.root"
		),
#        eventsToProcess = cms.untracked.VEventRange('1:5041:10000793-1:5041:10000796'),
   )
         
                       
process.maxEvents.input = 1000

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 200
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string("Z2.root")
                                   )

