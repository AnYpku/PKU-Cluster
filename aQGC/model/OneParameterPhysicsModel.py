from HiggsAnalysis.CombinedLimit.AnomalousCouplingModel import *
import ROOT as r
import os

#this model is in the equal couplings scenario of HISZ or something similar
#it does the old style limits of setting the other parameter to zero
class OneParameterPhysicsModel(AnomalousCouplingModel):
    def __init__(self):
        AnomalousCouplingModel.__init__(self)
        self.channels = ['channel_name']
        self.processes = ['WWewk']
        self.pois = ['param']

    def buildScaling(self,process,channel):        
        scalerName = process
	print self.scaling_filename
#        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_WWewk_wwssll8TeV2(param,"'+self.scaling_filename+'","aQGC_scaling3")')
        
        #self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_WWewk_ch1(param,"'+self.scaling_filename+'","aQGC_scaling1")')
        #self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_WWewk_ch2(param,"'+self.scaling_filename+'","aQGC_scaling2")')
        #self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_WWewk_ch3(param,"'+self.scaling_filename+'","aQGC_scaling3")')
        #self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_WWewk_ch4(param,"'+self.scaling_filename+'","aQGC_scaling4")')

        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch1(param,"'+self.scaling_filename+'","aqgc_scaling_bin_1")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch2(param,"'+self.scaling_filename+'","aqgc_scaling_bin_2")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch3(param,"'+self.scaling_filename+'","aqgc_scaling_bin_3")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch4(param,"'+self.scaling_filename+'","aqgc_scaling_bin_4")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch5(param,"'+self.scaling_filename+'","aqgc_scaling_bin_5")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch6(param,"'+self.scaling_filename+'","aqgc_scaling_bin_6")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch7(param,"'+self.scaling_filename+'","aqgc_scaling_bin_7")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch8(param,"'+self.scaling_filename+'","aqgc_scaling_bin_8")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch9(param,"'+self.scaling_filename+'","aqgc_scaling_bin_9")')
        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_sig_ch10(param,"'+self.scaling_filename+'","aqgc_scaling_bin_10")')
#        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_WWjj_ch3(param,"'+self.scaling_filename+'","aqgc_scaling_bin_3")')
#        self.modelBuilder.factory_('RooOneParameterModelScaling::Scaling_WWjj_ch4(param,"'+self.scaling_filename+'","aqgc_scaling_bin_4")')


        return scalerName
        

my_1d_model = OneParameterPhysicsModel()

