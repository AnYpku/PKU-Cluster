def custom_crab(config):
  print '>> Customising the crab config'
#  config.General.requestName   = 'fT9' 
  config.JobType.inputFiles =['wpwp_fT9_scaling_refined.root']
  config.Site.storageSite = 'T2_CN_Beijing'
#  config.Data.outputDatasetTag = 'fT9'
#  config.Site.blacklist = ['SOME_SITE', 'SOME_OTHER_SITE']
