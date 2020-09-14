from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName   = 'Z-ZZ-1'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['Fall17_17Nov2017DE_V32_DATA_L1FastJet_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L2Relative_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L1FastJet_AK4PFpuppi.txt','Fall17_17Nov2017DE_V32_DATA_L2Relative_AK4PFpuppi.txt','Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK4PFpuppi.txt','Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK4PFpuppi.txt']
# Name of the CMSSW configuration file
config.JobType.psetName    = 'Zanalysis.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDataset = '/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = -1
config.Data.publication = False
config.Data.outputDatasetTag = 'Z-ZZ-1'

config.section_("Site")
config.Site.storageSite = 'T2_CN_Beijing'
#config.Site.storageSite = 'T3_US_FNALLPC'


