from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName   = 'Z-STt'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFchs.txt','Fall17_17Nov2017_V32_MC_L2Relative_AK4PFchs.txt','Fall17_17Nov2017_V32_MC_L3Absolute_AK4PFchs.txt','Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFPuppi.txt','Fall17_17Nov2017_V32_MC_L2Relative_AK4PFPuppi.txt','Fall17_17Nov2017_V32_MC_L3Absolute_AK4PFPuppi.txt']
# Name of the CMSSW configuration file
config.JobType.psetName    = 'Zanalysis.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDataset ='/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.totalUnits = -1
config.Data.publication = False
config.Data.outputDatasetTag = 'Z-STt'

config.section_("Site")
config.Site.storageSite = 'T2_CN_Beijing'
#config.Site.storageSite = 'T3_US_FNALLPC'


