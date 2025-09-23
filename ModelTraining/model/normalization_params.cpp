#include "_project_config.h"
#include <stdint.h>

#include "normalization_params.h"

NormalizationParams normalization_params[NUM_FEATURES] = {
    {-0.328003, 0.244821, -1.040000, 0.390000}, // accelX
    {0.073373, 0.334189, -0.700000, 1.040000}, // accelY
    {-0.597767, 0.711377, -2.170000, 1.260000}, // accelZ
    {0.798380, 58.304769, -200.160000, 200.710000}, // gyroX
    {4.226353, 75.823288, -178.330000, 230.670000}, // gyroY
    {-1.564940, 144.684467, -438.390000, 368.800000}, // gyroZ
};
