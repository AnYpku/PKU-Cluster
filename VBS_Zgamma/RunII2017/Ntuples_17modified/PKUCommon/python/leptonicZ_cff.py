import FWCore.ParameterSet.Config as cms

Ztomumu = cms.EDProducer("CandViewCombiner",
                         decay = cms.string("goodMuons@+ goodMuons@-"),
                         cut = cms.string("")
                         )

ZtomumuL = cms.EDProducer("CandViewCombiner",
                         decay = cms.string("looseMuons@+ looseMuons@-"),
                         cut = cms.string("")
                         )

Ztoee = cms.EDProducer("CandViewCombiner",
                       decay = cms.string("goodElectrons@+ goodElectrons@-"),
                       cut = cms.string("")
                       )
ZtoeeL = cms.EDProducer("CandViewCombiner",
                       decay = cms.string("vetoElectrons@+ vetoElectrons@-"),
                       cut = cms.string("")
                       )

leptonicV = cms.EDProducer("CandViewMerger",
                           src = cms.VInputTag( "ZtoeeL", "ZtomumuL"),
                           cut = cms.string("")
                           ) 

leptonicVSequence = cms.Sequence(ZtomumuL + ZtoeeL + leptonicV)
