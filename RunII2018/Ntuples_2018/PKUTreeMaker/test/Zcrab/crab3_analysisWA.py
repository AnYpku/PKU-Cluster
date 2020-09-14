from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
#config.General.requestName   = 'Z-WA-2'
config.General.requestName   = 'Z-WA_smearing'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['Autumn18_V8_MC_L1FastJet_AK4PFchs.txt','Autumn18_V8_MC_L2Relative_AK4PFchs.txt','Autumn18_V8_MC_L3Absolute_AK4PFchs.txt','Autumn18_V8_MC_L1FastJet_AK4PFPuppi.txt','Autumn18_V8_MC_L2Relative_AK4PFPuppi.txt','Autumn18_V8_MC_L3Absolute_AK4PFPuppi.txt']
# Name of the CMSSW configuration file
config.JobType.psetName    = 'Zanalysis.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
#config.Data.inputDataset = '/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'
config.Data.inputDataset = '/WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = -1
config.Data.publication = False
#config.Data.outputDatasetTag = 'Z-WA-2'
config.Data.outputDatasetTag = 'Z-WA'

config.section_("Site")
#config.Site.storageSite = 'T2_CN_Beijing'
config.Site.storageSite = 'T3_US_FNALLPC'


