from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName   = 'DMu18A_Ssmearing'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.inputFiles = ['Autumn18_RunA_V8_DATA_L1FastJet_AK4PFchs.txt','Autumn18_RunA_V8_DATA_L2Relative_AK4PFchs.txt','Autumn18_RunA_V8_DATA_L3Absolute_AK4PFchs.txt','Autumn18_RunA_V8_DATA_L2L3Residual_AK4PFchs.txt','Autumn18_RunA_V8_DATA_L1FastJet_AK4PFPuppi.txt','Autumn18_RunA_V8_DATA_L2Relative_AK4PFPuppi.txt','Autumn18_RunA_V8_DATA_L3Absolute_AK4PFPuppi.txt','Autumn18_RunA_V8_DATA_L2L3Residual_AK4PFPuppi.txt']
# Name of the CMSSW configuration file
config.JobType.psetName    = 'Zanalysis_data_A.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDataset = '/DoubleMuon/Run2018A-17Sep2018-v2/MINIAOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 80
config.Data.lumiMask = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
#config.Data.runRange = '246908-258750'
#config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'DMu18A'

config.section_("Site")
#config.Site.storageSite = 'T2_CN_Beijing'
config.Site.storageSite = 'T3_US_FNALLPC'


