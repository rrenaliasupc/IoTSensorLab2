#include "_project_config.h"
#include <stdint.h>

#include "normalization_params.h"

NormalizationParams normalization_params[NUM_FEATURES] = {
    {-0.241673, 0.323609, -0.970000, 0.280000}, // accelX
    {-0.063703, 0.190066, -0.900000, 0.790000}, // accelY
    {-0.811283, 0.427148, -2.190000, 0.390000}, // accelZ
    {2.140177, 27.021475, -135.470000, 131.660000}, // gyroX
    {-0.867703, 21.666769, -76.350000, 95.960000}, // gyroY
    {-14.733380, 85.907889, -294.270000, 214.290000}, // gyroZ
};
