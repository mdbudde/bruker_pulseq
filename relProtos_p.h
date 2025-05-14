/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/initMeth.c */
void initMeth(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/loadMeth.c */
void loadMeth(const char *);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/parsRelations.c */
void ExcPulse1EnumRelation(void);
void ExcPulse1AmplRel(void);
void HandleRFPulseAmplitude(void);
void ExcPulse1Relation(void);
void ExcPulse1Range(void);
void EffSWhRange(void);
void EffSWhRel(void);
void MyRgInitRel(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/BaseLevelRelations.c */
void SetBaseLevelParam(void);
void SetBasicParameters(void);
void SetFrequencyParameters(void);
void SetGradientParameters(void);
void SetMachineParameters(void);
void SetPpgParameters(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/RecoRelations.c */
void SetRecoParam(void);
void RecoDerive(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/backbone.c */
void backbone(void);
void UpdateTotalTime(void);
void UpdateRFPulses(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/deriveVisu.c */
void deriveVisu(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/bruker_pulseq/pulseqRelations.c */
void UpdatePulseq(void);
void UpdateSeqList(void);
void PulseqFileHandler(void);
void SetBeforeAcquisition(void);
int WriteExpPpgFile(void);
int CopyPPGScan(void);
