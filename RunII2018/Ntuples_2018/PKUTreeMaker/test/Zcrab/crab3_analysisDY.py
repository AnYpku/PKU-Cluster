from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
#config.General.requestName   = 'Z-DY-1'
#config.General.requestName   = 'Z-DY-2'
config.General.requestName   = 'Z-DY-FX'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['Fall17_17Nov2017DE_V32_DATA_L1FastJet_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L2Relative_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L1FastJet_AK4PFpuppi.txt','Fall17_17Nov2017DE_V32_DATA_L2Relative_AK4PFpuppi.txt','Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK4PFpuppi.txt','Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK4PFpuppi.txt']
# Name of the CMSSW configuration file
config.JobType.psetName    = 'Zanalysis.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
#config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.totalUnits = -1
config.Data.publication = False
#config.Data.outputDatasetTag = 'Z-DY-1'
#config.Data.outputDatasetTag = 'Z-DY-2'
config.Data.outputDatasetTag = 'Z-DY-FX'

config.section_("Site")
config.Site.storageSite = 'T2_CN_Beijing'
#config.Site.storageSite = 'T3_US_FNALLPC'


