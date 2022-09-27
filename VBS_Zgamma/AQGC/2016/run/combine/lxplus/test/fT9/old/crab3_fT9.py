from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.requestName = 'fT9'
config.section_('JobType')
config.JobType.psetName = '/afs/cern.ch/work/y/yian/work/PKU-Cluster/aQGC/CMSSW_8_1_0/src/CombineHarvester/CombineTools/scripts/do_nothing_cfg.py'
config.JobType.pluginName = 'PrivateMC'
config.JobType.inputFiles = ['wpwp_fT9_scaling_refined.root']
config.JobType.outputFiles = ['combine_output.tar']
config.JobType.scriptExe = 'crab_grid-fT9.sh'
config.section_('Data')
config.Data.outputDatasetTag = 'fT9'
config.Data.publication = False
config.Data.unitsPerJob = 1
config.Data.splitting = 'EventBased'
config.Data.outputPrimaryDataset = 'Combine'
config.Data.totalUnits = 1
config.section_('User')
config.section_('Site')
config.Site.blacklist = ['T3_IT_Bologna', 'T3_US_UMiss']
config.Site.storageSite = 'T2_CN_Beijing'
