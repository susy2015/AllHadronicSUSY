import FWCore.ParameterSet.Config as cms

trackIsolationFilter = cms.EDFilter("TrackIsolationFilter",
                                     pfCandidatesTag     = cms.InputTag("particleFlow"),
                                     vertexInputTag      = cms.InputTag("goodVertices"),
                                     dR_ConeSize         = cms.double(0.3),
                                     dz_CutValue         = cms.double(0.05),
                                     minPt_PFCandidate   = cms.double(15.0),
                                     isoCut              = cms.double(0.1),
                                     doTrkIsoVeto        = cms.bool(True),
                                     doFillTree          = cms.bool(False),
                                     evtWeightInput      = cms.InputTag("weightProducer:weight"),
)
