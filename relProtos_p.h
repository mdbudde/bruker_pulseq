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
void EffSWhRange(void);
void EffSWhRel(void);
void MyRgInitRel(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/BaseLevelRelations.c */
void SetBaseLevelParam(void);
void SetBasicParameters(void);
void SetFrequencyParameters(void);
void SetGradientParameters(void);
void SetMachineParameters(void);
void SetPpgParameters(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/RecoRelations.c */
void SetRecoParam(void);
void RecoDerive(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/backbone.c */
void backbone(void);
void UpdateTotalTime(void);
void UpdateRFPulses(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/deriveVisu.c */
void deriveVisu(void);
/* /opt/PV6.0.1/prog/curdir/budde/ParaVision/methods/src/pulseqV1/pulseqRelations.c */
void UpdatePulseq(void);
void UpdateSeqList(void);
void PulseqFileHandler(void);
void SetBeforeAcquisition(void);
int WriteExpPpgFile(void);
int CopyPPGScan(void);
