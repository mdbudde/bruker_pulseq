/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/initMeth.c */
void initMeth(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/loadMeth.c */
void loadMeth(const char *);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/parsRelations.c */
void ExcPulse1EnumRelation(void);
void ExcPulse1AmplRel(void);
void HandleRFPulseAmplitude(void);
void ExcPulse1Relation(void);
void ExcPulse1Range(void);
void NAveragesRange(void);
void NAveragesRels(void);
void EffSWhRange(void);
void EffSWhRel(void);
void InversionTimeRels(void);
void InversionTimeRange(void);
void ReadSpoilerRel(void);
void SliceSpoilerRel(void);
void RecoMethModeVisPar(void);
void MaskModeRel(void);
void GaussBroadRange(void);
void MaskWeightRange(void);
void MyRgInitRel(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/BaseLevelRelations.c */
void SetBaseLevelParam(void);
void SetBasicParameters(void);
void SetFrequencyParameters(void);
void SetGradientParameters(void);
void SetInfoParameters(void);
void SetMachineParameters(void);
void SetPpgParameters(void);
void SetACQ_obj_orderForMovie(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/RecoRelations.c */
void SetRecoParam(void);
void RecoDerive(void);
void SWIRecoRel(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/backbone.c */
void backbone(void);
void UpdateSequenceTiming(void);
void UpdateRepetitionTime(void);
void UpdateTotalTime(void);
void UpdateGeometryMinima(double *, double *);
void UpdateReadSliceGradients(void);
void UpdatePhaseGradients(void);
void UpdateFrequencyOffsets(void);
void UpdateRFPulses(void);
void ControlGradientLimits(YesNo);
void UpdateMovie(void);
void UpdateEchoTime(void);
double minLoopRepetitionTime(void);
void UpdateRFSpoiling(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/deriveVisu.c */
void deriveVisu(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/pulseqRelations.c */
void UpdatePulseq(void);
void UpdateSeqList(void);
void PulseqFileHandler(void);
