/* ***************************************************************
 *
 * DwiWaveform.c
 *
 * Copyright (c) 2016-2025
 * Matthew Budde
 *
 * All Rights Reserved
 *
 *
 * ***************************************************************/
static const char resid[] = "$Id: DwiWaveform.c,v ";

#define DEBUG		1
#define DB_MODULE	1
#define DB_LINE_NR	0


#include "method.h"
#include "DwiWaveformTypes.h"

#define VersionTag "v8.0"

//Tolerance window for waveform gradient magnitude limit of gradient norm
//Often the gradient waveform files have limited decimal accuracy, so this gives some flexibility.
#define GradNormTol 1E-3
#define MAX_SHAPES 6

void DwiWaveformInit() 
{

  if(ParxRelsParHasValue("DwGradDur1") == No)
  {
  	DwGradDur1 = 1.0;
  }
  if(ParxRelsParHasValue("DwGradDur2") == No)
  {
  	DwGradDur2 = 1.0;
  }
  if(ParxRelsParHasValue("DwGradTsep") == No)
  {
  	DwGradTsep = 4.0;
  }

  ParxRelsMakeNonEditable("DwDelay1");
  ParxRelsMakeNonEditable("DwDelay2");
  ParxRelsMakeNonEditable("DwModuleDur");

  if(ParxRelsParHasValue("DwStatusString") == No)
  {
  	strcpy(DwStatusString," Not Loaded ");
  }
  
         
   PARX_change_dims("DwSeqFileFullPath",PATH_MAX);

  ParxRelsParSetStringValue("DwVersionTag",VersionTag);
  
  
  if(ParxRelsParHasValue("DwSeqNumEntries") == No)
  {
  	DwSeqNumEntries = 1;
  }
  if(ParxRelsParHasValue("DwSeqNumDirs") == No)
  {
  	DwSeqNumDirs = 1;
  }
  if(ParxRelsParHasValue("DwSeqNumShapes") == No)
  {
  	DwSeqNumShapes = 1;
  }
  if(ParxRelsParHasValue("DwSeqFileName") == No)
  {
  	strcpy(DwSeqFileName," empty ");
  }
}


void UpdateDwSeqList(void)
{
        char seqpath[100];/* seq directory path   */
        PvPathMkHomePv(seqpath, NULL);  //Create a string  PVINSTDIR/prog/curdir/USER/ParaVision.
        strcat(seqpath,"/exp/lists/dwseq/");
        
        //Update list of available files
        PTB_InitDynEnumWithRegFileNames("DwSeqFileDynEnum", seqpath);
        PTB_InitDynEnumWithRegFileNames("TempSeq", seqpath);
}


void UpdateDwSeq(void) {
        UpdateDwSeqList();
        int seqInd;
        int success = 0;
        TempSeq = DwSeqFileDynEnum;  
        ParxRelsParGetEnumValueAsInt("TempSeq", &seqInd);
        const char *seq_file = ParxRelsIntToEnumStr("TempSeq", seqInd);
        strcpy(DwSeqFileBase,seq_file);
        
        PvPathMkHomePv(DwSeqFileFullPath, NULL);
        strcat(DwSeqFileFullPath, "/exp/lists/dwseq/");      
        strcat(DwSeqFileFullPath, seq_file);      
    
}


// Update when the Seq selector is changed, doesn't load, just changes path.
void DwSeqFileHandler(void)
{
    DB_MSG(("-->Seq Handler1"));
    
        UpdateDwSeqList();  
        
        UT_SetRequest("DwSeqFileDynEnum");
        int reqIndex = UT_RequestIndex(0);
        
        
        int seqInd;
        TempSeq = DwSeqFileDynEnum;        
        
        int hasValSet = ParxRelsEnumHasDynamicValueSet("TempSeq");
        if (hasValSet == No)
        {
            UT_ClearRequest();
            return;
        }
        YesNo hasVal = ParxRelsParGetEnumValueAsInt("TempSeq", &seqInd);
        
        if (hasVal == No)
        {
            UT_ClearRequest();
            return;
        }
        
        const char *seq_file = ParxRelsIntToEnumStr("TempSeq", seqInd);

        
        char seqpath[PATH_MAX];/* directory path   */
        PvPathMkHomePv(seqpath, NULL);
        strcat(seqpath, "/exp/lists/dwseq/");      
        strcat(seqpath, seq_file);  
        // int success = DwSeqLoadFile(seqpath);
        
        // if ((success)) 
        // {
            strcpy(DwSeqFileBase,seq_file);
            strcpy(DwSeqFileFullPath,seqpath);
            //UT_RequestParOrigValue(TempShape);
        //}
            
        UT_ClearRequest();
        backbone();
        
    
    DB_MSG(("<--DwSeqFileHandler"));
}


void DwUpdateTimings() 
{
  DB_MSG(("-->DwUpdateTimings\n"));


  DwGradDur1 = DwSeqShapeTable[DwSeqEntryTable.shape1_id[0]].duration * 1000; // to ms
  DwGradDur2 = DwSeqShapeTable[DwSeqEntryTable.shape2_id[0]].duration * 1000; // to ms

  double riseTime  = CFG_GradientRiseTime();
  //Delays and Durations
  double igwt = CFG_InterGradientWaitTime();
  
  DwGradTsep = MAX_OF(DwMinSep + igwt*2.0, DwGradTsep);
  DwDelay1 = (DwGradTsep - DwMinSep)/2.0;
  DwDelay2 = DwDelay1;
  DwModuleDur = riseTime + DwGradDur1 + riseTime + DwGradTsep + riseTime + DwGradDur2 + riseTime;
  //Baselevel delays get called from BaseLevelRelations
       
  DB_MSG(("<--DwUpdateTimings\n"));
  return;
}




void DwSeqLoadHandler(void)  
{
    DB_MSG(("-->DwSeqLoadHandler"));
    int success = 0;
    
    success = DwSeqLoadFile(DwSeqFileFullPath); 
    if (success) {
        success = DwSeqCheck();
    }
    

    DwUpdateTimings();

    BaseLevelCustomDwSeq();
    
    
    ParxRelsParSetStringValue("DwStatusString"," Loaded Successfully ");
    
    // for copying the dwseq file to the exp directory when scan is started.
    PARX_change_dims("ExpDwSeqFileFullPath",PATH_MAX);
    // exp pulse program location
    PvOvlUtilGetExpnoPath(ExpDwSeqFileFullPath, PATH_MAX, DwSeqFileBase);

    //return 0;
    DB_MSG(("<--DwSeqLoadHandler"));

    backbone();  /* we call the backbone here and should not infinite loop by using the handler callback */

}







/* CalcVecToVecMat
 function to calculate the rotation matrix from one unit vector A into another B 
 
 From algorithm by Moller & Hughes 1999 Journal of Graphics Tools v4(4)1-4:
 * Efficiently Building a Matrix to Rotate One Vector to Another  */

int CalcVecToVecMat(double Avec[3], double Bvec[3], double R[3][3])
{
 
    
    //printf("Avec vec: %f %f %f\n", Avec[0], Avec[1], Avec[2]);
    //printf("Bvec vec: %f %f %f\n", Bvec[0], Bvec[1], Bvec[2]);
  
                    
    double AvecS[3], BvecS[3];
    
    double Ascale = sqrt(Avec[0]*Avec[0] + Avec[1]*Avec[1] + Avec[2]*Avec[2]);
    if (Ascale == 0)
   	{ //avoid nan errors
            DB_MSG(("A Not a vector\n"));
           // return 0;
	} 
        AvecS[0] = Avec[0] / Ascale;
        AvecS[1] = Avec[1] / Ascale;
        AvecS[2] = Avec[2] / Ascale;
    
    double Bscale = sqrt(Bvec[0]*Bvec[0] + Bvec[1]*Bvec[1] + Bvec[2]*Bvec[2]);
    if (Bscale == 0)
   	{ //avoid nan errors
        DB_MSG(("B Not a vector\n"));
          //  return 0;
	} 
        BvecS[0] = Bvec[0] / Bscale;
        BvecS[1] = Bvec[1] / Bscale;
        BvecS[2] = Bvec[2] / Bscale;
    
    double v[3];
    VectorCrossProduct(AvecS, BvecS, v); 
    double c = ScalarDotProduct(AvecS, BvecS);
    
    // printf("CrosProd vec: %f %f %f\n", v[0], v[1], v[2]);
    //printf("DotProd: %f \n", c);
    
    if (fabs(c)<0.99)  //not close to parallel
    {
        double h = (1-c)/ScalarDotProduct(v,v);

        R[0][0] = c + h*v[0]*v[0];
        R[1][1] = c + h*v[1]*v[1];
        R[2][2] = c + h*v[2]*v[2];

        R[0][1] = h*v[0]*v[1] - v[2];
        R[0][2] = h*v[0]*v[2] + v[1];
        R[1][0] = h*v[0]*v[1] + v[2];
        R[1][2] = h*v[1]*v[2] - v[0];
        R[2][0] = h*v[0]*v[2] - v[1];
        R[2][1] = h*v[1]*v[2] + v[0];
    } else {
        double p[3] = {0.0, 0.0, 0.0};
        
        int vecmin = 0;
        if (fabs(AvecS[1]) < fabs(AvecS[0])) 
        {
            vecmin = 1;
        } 
        if ( fabs(AvecS[2]) < fabs(AvecS[vecmin]))
        {
            vecmin = 2;
        }   
        p[vecmin] = 1.0;
        //printf("pvecmin: %i \n", vecmin);
        
        double u[3], v[3], u4[3];
        for (int vv=0; vv<3; vv++) {
            u[vv] = p[vv] - AvecS[vv];
            v[vv] = p[vv] - BvecS[vv];
            u4[vv] = 4*u[vv];
        }
        
        double dotu = ScalarDotProduct(u, u);
        double dot4uv = ScalarDotProduct(u4, v);
        double dotv = ScalarDotProduct(v, v);
        //printf("DotProdu: %f \n", dotu);
        //printf("DotProdu: %f \n", dot4uv);
        //printf("DotProdu: %f \n", dotv);
        
        R[0][0] = 1 - (2/dotu)*u[0]*u[0] - (2/dotv)*v[0]*v[0] + (dot4uv)/(dotu*dotv)*v[0]*u[0];
        R[1][1] = 1 - (2/dotu)*u[1]*u[1] - (2/dotv)*v[1]*v[1] + (dot4uv)/(dotu*dotv)*v[1]*u[1];
        R[2][2] = 1 - (2/dotu)*u[2]*u[2] - (2/dotv)*v[2]*v[2] + (dot4uv)/(dotu*dotv)*v[2]*u[2];
        
        R[0][1] = 0 - (2/dotu)*u[0]*u[1] - (2/dotv)*v[0]*v[1] + (dot4uv)/(dotu*dotv)*v[0]*u[1];
        R[0][2] = 0 - (2/dotu)*u[0]*u[2] - (2/dotv)*v[0]*v[2] + (dot4uv)/(dotu*dotv)*v[0]*u[2];
        R[1][0] = 0 - (2/dotu)*u[1]*u[0] - (2/dotv)*v[1]*v[0] + (dot4uv)/(dotu*dotv)*v[1]*u[0];
        R[1][2] = 0 - (2/dotu)*u[1]*u[2] - (2/dotv)*v[1]*v[2] + (dot4uv)/(dotu*dotv)*v[1]*u[2];
        R[2][0] = 0 - (2/dotu)*u[2]*u[0] - (2/dotv)*v[2]*v[0] + (dot4uv)/(dotu*dotv)*v[2]*u[0];
        R[2][1] = 0 - (2/dotu)*u[2]*u[1] - (2/dotv)*v[2]*v[1] + (dot4uv)/(dotu*dotv)*v[2]*u[1];  
    }
                        
        //printf("R0: %.04f %.04f %.04f \n", R[0][0],R[0][1],R[0][2]);
        //printf("R1: %.04f %.04f %.04f \n", R[1][0],R[1][1],R[1][2]);
        //printf("R2: %.04f %.04f %.04f \n", R[2][0],R[2][1],R[2][2]);
    return 1;
}

void RotateVector(double vec[3], double R[3][3], double *newVec)
{
    newVec[0] = vec[0]*R[0][0] + vec[1]*R[0][1] + vec[2]*R[0][2];
    newVec[1] = vec[0]*R[1][0] + vec[1]*R[1][1] + vec[2]*R[1][2];
    newVec[2] = vec[0]*R[2][0] + vec[1]*R[2][1] + vec[2]*R[2][2];
}

void VectorCrossProduct(double A[3], double B[3], double *vectOut)
{
    vectOut[0] = A[1]*B[2] - A[2]*B[1];
    vectOut[1] = A[2]*B[0] - A[0]*B[2];
    vectOut[2] = A[0]*B[1] - A[1]*B[0];    
}

double ScalarDotProduct(double A[3], double B[3])
{
    double dot = A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
    return dot;
}




void SetDwWaveformLabels( void )
{
  char buffer[200];
  
  DB_MSG(("-->SetDwImageLabels"));

  int bufsize = 20;  //this is an unmodifiable size for ACQ_movie_descr[][20]  

      ACQ_n_echo_images = 1;
      ACQ_n_movie_frames = DwSeqNumEntries;
      PARX_change_dims("ACQ_movie_descr",DwSeqNumEntries,bufsize);
      PARX_change_dims("ACQ_echo_descr",1,bufsize);      
     
        for (int i=0; i<DwSeqNumEntries; i++) 
        { 
            DwLabelToBuffer(buffer, i+1, DwSeqEntryTable.amp[i], DwSeqEntryTable.shape1_id[i], DwSeqEntryTable.shape2_id[i]);
            strncpy(ACQ_movie_descr[i],buffer,bufsize);
        }
  
      
  DB_MSG(("<--SetDwImageLabels"));
}


void DwLabelToBuffer( char * buffer, int dir, double gamp, int shape1, int shape2) 
{
    int bufsize = 20;  //this is fixed at 20.  
    sprintf(buffer,"D:%d,G:%.0f,S1:%d,S2:%d",dir, gamp, shape1, shape2);
    buffer[bufsize-1]='\0';
}

/* These two functions are used to avoid hardware level errors that occur with many slices/directions/shapes
 in which the gradient hardware boards throw an error of unknown cause  
 
 * 
 * The first takes ACQ_grad_matrix and stores it to a temp matrix Dw_acqgradmatrix_override
 and sets ACQ_grad_matrix to a single 1x3x3 matrix (single slice package and is called in the Baselevel
 
 * The second restores Dw_acqgradmatrix_override to ACQ_grad_matrix and is called before recon

 */
void Dw_StoreMinimize_ACQGradMatrix(void){
   
  int nslices;
  
  nslices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  PARX_change_dims("Dw_acqgradmatrix_override", nslices,3,3); 
  for (int jj=0; jj<nslices; jj++) {
    for (int rr=0; rr<3; rr++) {
        for (int cc=0; cc<3; cc++) {
            Dw_acqgradmatrix_override[jj][rr][cc] = ACQ_grad_matrix[jj][rr][cc];
        }
    }
  }
  
  nslices = 1;  
  PARX_change_dims("ACQ_grad_matrix", 1,3,3); 
    for (int rr=0; rr<3; rr++) {
        for (int cc=0; cc<3; cc++) {
            ACQ_grad_matrix[0][rr][cc] = ACQ_grad_matrix[0][rr][cc];
        }
    }
  ACQ_grad_matrix_size = 1;
}

void Dw_RestoreResize_ACQGradMatrix(void){
   int nslices = GTB_NumberOfSlices( PVM_NSPacks, PVM_SPackArrNSlices );
  PARX_change_dims("ACQ_grad_matrix", nslices,3,3); 
  for (int jj=0; jj<nslices; jj++) {
    for (int rr=0; rr<3; rr++) {
        for (int cc=0; cc<3; cc++) {
            ACQ_grad_matrix[jj][rr][cc] = Dw_acqgradmatrix_override[jj][rr][cc];
        }
    }
  }
  
  ACQ_grad_matrix_size = nslices;
}


//Load the Rotation matrix values into the ppg baselevel variables
void RotMat2DwR(double RotMat[3][3], int currI, double GradAmp)
{
            DwR00[currI] = RotMat[0][0];
            DwR11[currI] = RotMat[1][1];
            DwR22[currI] = RotMat[2][2];
            DwR01[currI] = RotMat[0][1];
            DwR02[currI] = RotMat[0][2];
            DwR10[currI] = RotMat[1][0];
            DwR12[currI] = RotMat[1][2];
            DwR20[currI] = RotMat[2][0];
            DwR21[currI] = RotMat[2][1];
            
            DwGAmpRot00[currI] = RotMat[0][0]*GradAmp;
            DwGAmpRot11[currI] = RotMat[1][1]*GradAmp;
            DwGAmpRot22[currI] = RotMat[2][2]*GradAmp;
            DwGAmpRot01[currI] = RotMat[0][1]*GradAmp;
            DwGAmpRot02[currI] = RotMat[0][2]*GradAmp;
            DwGAmpRot10[currI] = RotMat[1][0]*GradAmp;
            DwGAmpRot12[currI] = RotMat[1][2]*GradAmp;
            DwGAmpRot20[currI] = RotMat[2][0]*GradAmp;
            DwGAmpRot21[currI] = RotMat[2][1]*GradAmp;
}

//Calculate the DW timing delays
void BaseLevelDwDelays(void) 
{
      double riseTime  = CFG_GradientRiseTime();
  
      DwD1 = riseTime/1000.0;
      DwD2 = DwDelay1 / 1000.0; //delay after first gradient waveform
      DwD3 = DwDelay2 / 1000.0; //delay after second gradient waveform
      DwD4 = DwGradDur1/1000.0;    
      DwD5 = DwGradDur2/1000.0;    
}



void trim(char* line) {
    char* p = strchr(line, '#');
    if (p) *p = '\0';
    size_t len = strlen(line);
    while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r' || line[len-1] == ' '))
        line[--len] = '\0';
}


int DwSeqLoadFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error loading file %s \n",filename);
        return -1;
    }
    DwSeqNumEntries = 0;
    DwSeqNumDirs = 0;
    DwSeqNumShapes = 0;

    int entrycounter = 0;
    int dirscounter = 0;
    int shapecounter = 0;
    
    int max_line = 512;
    char line[max_line];
    enum { NONE, DWITABLE, DIRECTIONS, SHAPES, DEFINITIONS } section = NONE;
    int shape_sample_idx = 0;
    DWSEQSHAPE current_shape;
    int in_shape = 0;
    int tempnum, tempdir, tempshape1, tempshape2;
    double tempx, tempy, tempz, tempamp;

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (strlen(line) == 0) continue;

        if (strcmp(line, "[DEFINITIONS]") == 0) {
            section = DEFINITIONS;
            printf("Loading DEFINITIONS \n");
            continue;
        } else if (strcmp(line, "[DWITABLE]") == 0) {
            section = DWITABLE;
            printf("Loading DWITABLE \n");
            continue;
        } else if (strcmp(line, "[DIRECTIONS]") == 0) {
            printf("Loading DIRECTIONS \n");
            section = DIRECTIONS;
            continue;
        } else if (strcmp(line, "[SHAPES]") == 0) {
            printf("Loading SHAPES \n");
            section = SHAPES;
            continue;
        } else if (line[0] == '[') {
            section = NONE;
            continue;
        }

        switch (section) {
            case DEFINITIONS: {
                if (strncmp(line, "name", 4) == 0) {
                    sscanf(line, "name %s", DwSeqDefinitions.name);
                }else if (strncmp(line, "GradientMax", 11) == 0) {
                    sscanf(line, "GradientMax %lf", &DwSeqDefinitions.GradientMax);
                }
                break;
            }
            case DWITABLE: {
                if (sscanf(line, "%d %d %d %d %lf", &tempnum, &tempshape1, &tempshape2, &tempdir, &tempamp) == 5) {
                    DwSeqEntryTable.num[entrycounter] = tempnum;
                    DwSeqEntryTable.shape1_id[entrycounter] = tempshape1;
                    DwSeqEntryTable.shape2_id[entrycounter] = tempshape2;
                    DwSeqEntryTable.dir_id[entrycounter] = tempdir;
                    DwSeqEntryTable.amp[entrycounter] = tempamp;
                    printf("DWI: #%d shape1=%d shape2=%d dir=%d amp=%lf\n", tempnum, tempshape1, tempshape2, tempdir, tempamp);
                    entrycounter++;
                } else {
                    printf("ERROR: %s \n",line);
                    fclose(file);
                    return -1;
                }
                if (entrycounter > MAX_ENTRIES) {
                    printf("ERROR: too many entries\n");
                    fclose(file);
                    return -1;
                }
                break;
            }
            case DIRECTIONS: {
                if (sscanf(line, "%d %lf %lf %lf", &tempnum, &tempx, &tempy, &tempz) == 4) {
                    printf("DIR: id=%d (%.1f %.1f %.1f)\n", tempnum, tempx, tempy, tempz);
                    DwSeqDirTable.dir_id[dirscounter] = tempnum;
                    DwSeqDirTable.x[dirscounter] = tempx;
                    DwSeqDirTable.y[dirscounter] = tempy;
                    DwSeqDirTable.z[dirscounter] = tempz;
                    dirscounter++;
                } else {
                    printf("ERROR: %s \n",line);
                    fclose(file);
                    return -1;
                }
                if (dirscounter > MAX_DIRECTIONS) {
                    printf("ERROR: too many directions\n");
                    fclose(file);
                    return -1;
                }
                break;
            }
            case SHAPES: {
                if (strncmp(line, "shape_id", 8) == 0) {
                    if (in_shape) {
                        printf("SHAPE %d (%s), %d samples\n", current_shape.shape_id, current_shape.shape_label, current_shape.num_samples);
                    }
                    sscanf(line, "shape_id %d", &current_shape.shape_id);
                    shape_sample_idx = 0;
                    in_shape = 1;
                } else if (strncmp(line, "shape_label", 11) == 0) {
                    sscanf(line, "shape_label %s", current_shape.shape_label);
                } else if (strncmp(line, "origin_vect", 11) == 0) {
                    sscanf(line, "origin_vect %lf %lf %lf", &current_shape.origin_vect[0], &current_shape.origin_vect[1], &current_shape.origin_vect[2]);
                } else if (strncmp(line, "duration", 8) == 0) {
                    sscanf(line, "duration %lf", &current_shape.duration);                
                } else if (strncmp(line, "num_samples", 11) == 0) {
                    sscanf(line, "num_samples %d", &current_shape.num_samples);
                } else {
                    if (shape_sample_idx > MAX_SHAPE_SAMPLES) {
                        printf("ERROR: too many shape samples for shape %d\n", current_shape.shape_id);
                        fclose(file);
                        return -1;
                    }
                    if (sscanf(line, "%lf %lf %lf", &tempx, &tempy, &tempz) == 3) {
                        current_shape.samples[shape_sample_idx][0] = tempx;
                        current_shape.samples[shape_sample_idx][1] = tempy;
                        current_shape.samples[shape_sample_idx][2] = tempz;
                        shape_sample_idx++;
                    }
                    if (shape_sample_idx >= current_shape.num_samples) {
                        printf("Storing shape with id: %d to %d\n", current_shape.shape_id, shapecounter);
                        DwSeqShapeTable[shapecounter] = current_shape;
                        shapecounter++;        
                        in_shape = 0;
                        shape_sample_idx = 0;
                    }
                }

                break;
            }
            default: break;
        }
             
    }

    fclose(file);    
    DwSeqNumEntries = entrycounter;
    DwSeqNumDirs = dirscounter;
    DwSeqNumShapes = shapecounter;
    strcpy(DwSeqFileName, DwSeqDefinitions.name);
    
    printf("File loaded successfully\n");
    DB_MSG(("Loaded %d entries, %d directions, %d shapes\n", entrycounter, dirscounter, shapecounter));
    ParxRelsParSetStringValue("DwStatusString"," File loaded ");
    return 0;
}

int DwSeqCheck() {
    DB_MSG(("Checking...\n"));
    int success = 1;

    /* check contents of loaded */
    int shape1pts = DwSeqShapeTable[DwSeqEntryTable.shape1_id[0]].num_samples;
    int shape2pts = DwSeqShapeTable[DwSeqEntryTable.shape2_id[0]].num_samples;
    double shape1dur = DwSeqShapeTable[DwSeqEntryTable.shape1_id[0]].duration;
    double shape2dur = DwSeqShapeTable[DwSeqEntryTable.shape2_id[0]].duration;
    int shapeind = 0;
    for (int i = 0; i < DwSeqNumEntries; i++) {
        if (DwSeqEntryTable.shape1_id[i] > DwSeqNumShapes) {
            printf("ERROR: shape1_id %d exceeds number of shapes %d\n", DwSeqEntryTable.shape1_id[i], DwSeqNumShapes);
            success = 0;
        }
        if (DwSeqEntryTable.shape2_id[i] > DwSeqNumShapes) {
            printf("ERROR: shape2_id %d exceeds number of shapes %d\n", DwSeqEntryTable.shape2_id[i], DwSeqNumShapes);
            success = 0;
        }
        if (DwSeqEntryTable.dir_id[i] > DwSeqNumDirs) {
            printf("ERROR: dir_id %d exceeds number of directions %d\n", DwSeqEntryTable.dir_id[i], DwSeqNumDirs);
            success = 0;
        }
        if (DwSeqEntryTable.amp[i] < 0) {
            printf("ERROR: amp %lf is negative\n", DwSeqEntryTable.amp[i]);
            success = 0;
        }
        if (DwSeqEntryTable.amp[i] > 100) {
            printf("ERROR: amp %lf exceeds maximum value\n", DwSeqEntryTable.amp[i]);
            success = 0;
        }

        if (i > 0)
            shapeind = DwSeqEntryTable.shape1_id[i]-1;
        if ( DwSeqShapeTable[shapeind].num_samples != shape1pts ) {
            printf("ERROR: all shapes1 must have same number of points shape: %d  samples: %d\n",i, DwSeqShapeTable[shapeind].num_samples);
            success = 0;
        } 
        if ( DwSeqShapeTable[shapeind].duration != shape1dur ) {
            printf("ERROR: all shapes1 must have same duration shape: %d  dur: %lf\n",i, DwSeqShapeTable[shapeind].duration);
            success = 0;
        }
        shape1pts = DwSeqShapeTable[shapeind].num_samples;
        shape1dur = DwSeqShapeTable[shapeind].duration;

        
        if (i > 0)
            shapeind = DwSeqEntryTable.shape2_id[i]-1;
        if ( DwSeqShapeTable[shapeind].num_samples != shape2pts ) {
            printf("ERROR: all shapes2 must have same number of points shape: %d  samples: %d\n",i, DwSeqShapeTable[shapeind].num_samples);
            success = 0;
        }
        if ( DwSeqShapeTable[shapeind].duration != shape2dur ) {
            printf("ERROR: all shapes2 must have same duration shape: %d  dur: %lf\n",i, DwSeqShapeTable[shapeind].duration);    
            success = 0;
        }
        shape2pts = DwSeqShapeTable[shapeind].num_samples;
        shape2dur = DwSeqShapeTable[shapeind].duration;

    }


    for (int i = 0; i < DwSeqNumDirs; i++) {
        if (DwSeqDirTable.x[i] < -1.0 || DwSeqDirTable.x[i] > 1.0 ||
            DwSeqDirTable.y[i] < -1.0 || DwSeqDirTable.y[i] > 1.0 ||
            DwSeqDirTable.z[i] < -1.0 || DwSeqDirTable.z[i] > 1.0) {
            printf("WARNING: direction vector |values| > 1: %d\n", DwSeqDirTable.dir_id[i]);
        }
        double norm = sqrt(DwSeqDirTable.x[i] * DwSeqDirTable.x[i] + 
                     DwSeqDirTable.y[i] * DwSeqDirTable.y[i] + 
                     DwSeqDirTable.z[i] * DwSeqDirTable.z[i]);
        if (norm < -1.0 || norm > 1.0 ) {
            printf("WARNING: direction vector exceeds norm 1: %d  norm: %lf\n", DwSeqDirTable.dir_id[i], norm);
        }
    }

    for (int i = 0; i < DwSeqNumShapes; i++) {
        if (DwSeqShapeTable[i].shape_id > MAX_SHAPES) {
            printf("ERROR: shape_id %d exceeds number of max shapes %d\n", DwSeqShapeTable[i].shape_id, DwSeqNumShapes);
            success = 0;
        }

        for (int j = 0; j < DwSeqShapeTable[i].num_samples; j++) {
            if (DwSeqShapeTable[i].samples[j][0] < -1.0 || DwSeqShapeTable[i].samples[j][0] > 1.0 ||
                DwSeqShapeTable[i].samples[j][1] < -1.0 || DwSeqShapeTable[i].samples[j][1] > 1.0 ||
                DwSeqShapeTable[i].samples[j][2] < -1.0 || DwSeqShapeTable[i].samples[j][2] > 1.0) {
                printf("ERROR: shape sample values out of range\n");
                success = 0;
            }
            
            double norm = sqrt(DwSeqShapeTable[i].samples[j][0] * DwSeqShapeTable[i].samples[j][0] + 
                     DwSeqShapeTable[i].samples[j][1] * DwSeqShapeTable[i].samples[j][1] + 
                     DwSeqShapeTable[i].samples[j][2] * DwSeqShapeTable[i].samples[j][2]);
            if (norm < -1.0 - GradNormTol || norm > 1.0 + GradNormTol) {
                printf("WARNING: shape vector exceeds norm 1: shape %d sample: %d norm: %lf\n", i, j, norm);
                success = 0;
            }
            
            if (CheckShapeforErrors(DwSeqShapeTable[i].samples, DwSeqShapeTable[i].num_samples, DwSeqShapeTable[i].duration) == 0) {
                success = 0;
            }
        }
    }

    if (success)
    {
        printf("Seq File Checks completed\n");
        ParxRelsParSetStringValue("DwStatusString"," Checks Complete ");
    }
    return success;
}



int CheckShapeforErrors(double  gradshape[][3], int num_samples, double duration)
{
    
  double rampTime  = CFG_GradientRampTime();
  double gmax = CFG_MaxGradientStrength();
  double minDwell = CFG_GradientShapeResolution(); //in ms
  
  if (duration<0.001)
  {
    printf("No duration specified.  Min dwell time is %f\n",minDwell);
    return 0;
  }
  
  double dwell = (duration*1000)/num_samples;  //not sure if this should be NP or NP-1?
  if (dwell < minDwell) {            
      printf("Min Dwell error. Too many points or duration too short.");
      //sprintf(PVM_ErrorMessage, "dwell time %.6f below limit of %.6f", dwell, minDwell);
      //UT_ReportError(PVM_ErrorMessage);
      return 0;
  }
  
  double maxSlew = (1.0*gmax)/rampTime;  //in T/m/s  max of 3440 is quoted for BGA12S
  double slewRate;
  
  for (int ss=1; ss<=num_samples; ss++){
      for (int gg=0; gg<3; gg++) {
        slewRate = fabs(gradshape[ss][gg] - gradshape[ss-1][gg])*gmax/dwell;
        if ( slewRate > maxSlew){
            printf("Slew Rate error.  Durations too short or Amplitude too high.");
            //sprintf(PVM_ErrorMessage, "Shape slew rate %f exceeds limit %f at point %i", slewRate, maxSlew, ss);
            //UT_ReportError(PVM_ErrorMessage);
        }
      }
      
  }
  return 1;
  
  printf("No shape errors.");
}





void BaseLevelCustomDwSeq(void)
{
    DB_MSG(("-->BaseLevelCustomDwSeq\n"));
    
     
     //Gradient rotation vectors
     double RotMat[3][3];
     PARX_change_dims("DwR00",DwSeqNumEntries);
     PARX_change_dims("DwR11",DwSeqNumEntries);
     PARX_change_dims("DwR22",DwSeqNumEntries);
     PARX_change_dims("DwR01",DwSeqNumEntries);
     PARX_change_dims("DwR02",DwSeqNumEntries);
     PARX_change_dims("DwR10",DwSeqNumEntries);
     PARX_change_dims("DwR12",DwSeqNumEntries);
     PARX_change_dims("DwR20",DwSeqNumEntries);
     PARX_change_dims("DwR21",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot00",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot11",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot22",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot01",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot02",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot10",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot12",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot20",DwSeqNumEntries);
     PARX_change_dims("DwGAmpRot21",DwSeqNumEntries);
     PARX_change_dims("DwShape1IndArray", DwSeqNumEntries); 
     PARX_change_dims("DwShape2IndArray", DwSeqNumEntries); 
    
     float currAmp;
     int currShape1;
     int currShape2;
     int currDir;
     for (int currI = 0; currI<DwSeqNumEntries; currI++)
     {
            currAmp = DwSeqEntryTable.amp[currI];
            currShape1 = DwSeqEntryTable.shape1_id[currI] - 1;
            currShape2 = DwSeqEntryTable.shape2_id[currI] - 1;
            currDir = DwSeqEntryTable.dir_id[currI] - 1;  //1 indexed in seq, 0 indexed in arrays
            

            double dirvec[3] = {DwSeqDirTable.x[currDir], DwSeqDirTable.y[currDir], DwSeqDirTable.z[currDir]};
            
            CalcVecToVecMat(DwSeqShapeTable[currShape1].origin_vect, dirvec, RotMat);  
            CalcVecToVecMat(DwSeqShapeTable[currShape2].origin_vect, dirvec, RotMat);  
            RotMat2DwR(RotMat, currI, currAmp);
            DwShape1IndArray[currI] = currShape1;
            DwShape2IndArray[currI] = currShape2;

     }
    
        
        // reset all shaped arrays and set to 0; rebuild as needed
        PARX_change_dims("DW1GS0R", 1);
        PARX_change_dims("DW1GS0P", 1);
        PARX_change_dims("DW1GS0S", 1);
        PARX_change_dims("DW1GS1R", 1);
        PARX_change_dims("DW1GS1P", 1);
        PARX_change_dims("DW1GS1S", 1);
        PARX_change_dims("DW1GS2R", 1);
        PARX_change_dims("DW1GS2P", 1);
        PARX_change_dims("DW1GS2S", 1);
        PARX_change_dims("DW1GS3R", 1);
        PARX_change_dims("DW1GS3P", 1);
        PARX_change_dims("DW1GS3S", 1);
        PARX_change_dims("DW1GS4R", 1);
        PARX_change_dims("DW1GS4P", 1);
        PARX_change_dims("DW1GS4S", 1);
        PARX_change_dims("DW1GS5R", 1);
        PARX_change_dims("DW1GS5P", 1);
        PARX_change_dims("DW1GS5S", 1);
        DW1GS0R[0] = 0;
        DW1GS0P[0] = 0;
        DW1GS0S[0] = 0;
        DW1GS1R[0] = 0;
        DW1GS1P[0] = 0;
        DW1GS1S[0] = 0;
        DW1GS2R[0] = 0;
        DW1GS2P[0] = 0;
        DW1GS2S[0] = 0;
        DW1GS3R[0] = 0;
        DW1GS3P[0] = 0;
        DW1GS3S[0] = 0;
        DW1GS4R[0] = 0;
        DW1GS4P[0] = 0;
        DW1GS4S[0] = 0;
        DW1GS5R[0] = 0;
        DW1GS5P[0] = 0;
        DW1GS5S[0] = 0;
        
   
        int ci = 0; 
        int shapepoints = DwSeqShapeTable[ci].num_samples;
        //Store Gradient Shapes into baselevel parameters
        // Not sure if there is a mechanism to call a shape with all 3 gradients (R, P, S)
        //Instead store the R, P, S grads for each shape separately.

        PARX_change_dims("DW1GS0R", shapepoints);
        PARX_change_dims("DW1GS0P", shapepoints);
        PARX_change_dims("DW1GS0S", shapepoints);
        for (int np=0; np<shapepoints; np++){
            DW1GS0R[np] = DwSeqShapeTable[ci].samples[np][0];
            DW1GS0P[np] = DwSeqShapeTable[ci].samples[np][1];
            DW1GS0S[np] = DwSeqShapeTable[ci].samples[np][2];
        }
        
        if (DwSeqNumShapes > 1) {
            ci = 1;
            shapepoints = DwSeqShapeTable[ci].num_samples;
            PARX_change_dims("DW1GS1R", shapepoints);
            PARX_change_dims("DW1GS1P", shapepoints);
            PARX_change_dims("DW1GS1S", shapepoints);  
            for (int np=0; np<shapepoints; np++){
                DW1GS1R[np] = DwSeqShapeTable[ci].samples[np][0];
                DW1GS1P[np] = DwSeqShapeTable[ci].samples[np][1];
                DW1GS1S[np] = DwSeqShapeTable[ci].samples[np][2];
            }
        }

        if (DwSeqNumShapes > 2) {
            ci = 2;
            shapepoints = DwSeqShapeTable[ci].num_samples;
            PARX_change_dims("DW1GS2R", shapepoints);
            PARX_change_dims("DW1GS2P", shapepoints);
            PARX_change_dims("DW1GS2S", shapepoints);  
            for (int np=0; np<shapepoints; np++){
                DW1GS2R[np] = DwSeqShapeTable[ci].samples[np][0];
                DW1GS2P[np] = DwSeqShapeTable[ci].samples[np][1];
                DW1GS2S[np] = DwSeqShapeTable[ci].samples[np][2];
            }
        }

        if (DwSeqNumShapes > 3) {
            ci = 3;
            shapepoints = DwSeqShapeTable[ci].num_samples;
            PARX_change_dims("DW1GS3R", shapepoints);
            PARX_change_dims("DW1GS3P", shapepoints);
            PARX_change_dims("DW1GS3S", shapepoints);  
            for (int np=0; np<shapepoints; np++){
                DW1GS3R[np] = DwSeqShapeTable[ci].samples[np][0];
                DW1GS3P[np] = DwSeqShapeTable[ci].samples[np][1];
                DW1GS3S[np] = DwSeqShapeTable[ci].samples[np][2];
            }
        }

        if (DwSeqNumShapes > 4) {
            ci = 4;
            shapepoints = DwSeqShapeTable[ci].num_samples;
            PARX_change_dims("DW1GS4R", shapepoints);
            PARX_change_dims("DW1GS4P", shapepoints);
            PARX_change_dims("DW1GS4S", shapepoints);  
            for (int np=0; np<shapepoints; np++){
                DW1GS4R[np] = DwSeqShapeTable[ci].samples[np][0];
                DW1GS4P[np] = DwSeqShapeTable[ci].samples[np][1];
                DW1GS4S[np] = DwSeqShapeTable[ci].samples[np][2];
            }
        }

        if (DwSeqNumShapes > 5) {
            ci = 5;
            shapepoints = DwSeqShapeTable[ci].num_samples;
            PARX_change_dims("DW1GS5R", shapepoints);
            PARX_change_dims("DW1GS5P", shapepoints);
            PARX_change_dims("DW1GS5S", shapepoints);  
            for (int np=0; np<shapepoints; np++){
                DW1GS5R[np] = DwSeqShapeTable[ci].samples[np][0];
                DW1GS5P[np] = DwSeqShapeTable[ci].samples[np][1];
                DW1GS5S[np] = DwSeqShapeTable[ci].samples[np][2];
            }
        }
     
          
  DB_MSG(("<--BaseLevelDwShapes\n"));
}



/* set parameters just before acquisition */
void SetBeforeAcquisition( void )
{
  DB_MSG(("-->SetBeforeAcquisition"));

  int success = 0;
  if (PVM_AcqScanHandler == Scan_Experiment) 
  {
    PvUtilCopyFile(DwSeqFileFullPath, ExpDwSeqFileFullPath); // note this is (dest, source))
   }

  

  DB_MSG(("<--SetBeforeAcquisition"));
}