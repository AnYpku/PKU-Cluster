from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName   = 'DEle17E'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['Fall17_17Nov2017DE_V32_DATA_L1FastJet_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L2Relative_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK4PFchs.txt','Fall17_17Nov2017DE_V32_DATA_L1FastJet_AK4PFPuppi.txt','Fall17_17Nov2017DE_V32_DATA_L2Relative_AK4PFPuppi.txt','Fall17_17Nov2017DE_V32_DATA_L3Absolute_AK4PFPuppi.txt','Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK4PFPuppi.txt']
# Name of the CMSSW configuration file
config.JobType.psetName    = 'Zanalysis_data_E.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDataset = '/DoubleEG/Run2017E-31Mar2018-v1/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 80
config.Data.lumiMask = 'Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
#config.Data.runRange = '246908-258750'
#config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'DEle17E-v2'

config.section_("Site")
#config.Site.storageSite = 'T2_CN_Beijing'
config.Site.storageSite = 'T3_US_FNALLPC'


