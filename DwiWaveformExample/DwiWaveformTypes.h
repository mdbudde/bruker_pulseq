

#define MAX_ENTRIES 512
#define MAX_DIRECTIONS 256
#define MAX_SHAPE_SAMPLES 10000


typedef dynenum DYNDWSEQFILE;

typedef struct {
    char name[64];
    double GradientMax;
} DWSEQDEFS;

typedef struct {
    int num[MAX_ENTRIES];
    int shape1_id[MAX_ENTRIES];
    int shape2_id[MAX_ENTRIES];
    int dir_id[MAX_ENTRIES];
    double amp[MAX_ENTRIES];
} DWSEQENTRYTABLE;

typedef struct {
    int dir_id[MAX_DIRECTIONS];
    double x[MAX_DIRECTIONS];
    double y[MAX_DIRECTIONS];
    double z[MAX_DIRECTIONS];
} DWSEQDIRTABLE;

typedef struct {
    int shape_id;
    char shape_label[64];
    double origin_vect[3];
    int num_samples;
    double duration;
    double samples[MAX_SHAPE_SAMPLES][3];
} DWSEQSHAPE;