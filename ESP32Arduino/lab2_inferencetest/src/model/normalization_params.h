#include "_project_config.h"
#include <stdint.h>

typedef struct {
    float mean;
    float std;
    float min;
    float max;
} NormalizationParams;

#define NUM_FEATURES 6

extern NormalizationParams normalization_params[NUM_FEATURES];
