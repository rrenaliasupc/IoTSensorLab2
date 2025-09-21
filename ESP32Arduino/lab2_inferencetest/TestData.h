#ifndef TESTDATA_H
#define TESTDATA_H

#include "_project_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_TEST_SAMPLES 60
#define NUM_ITEMS_PER_SAMPLE 50
#define NUM_CHANNELS 6
#define NUM_MODEL_FEATURES 300

#ifdef __USE_INPUTSENSORTESTDATA__
extern float inputSensorData[NUM_TEST_SAMPLES][NUM_ITEMS_PER_SAMPLE][NUM_CHANNELS];
#endif

#ifdef __USE_MODEL_INPUT_NORMALIZED_TEST_DATA__
extern float inputTestData[NUM_TEST_SAMPLES][NUM_MODEL_FEATURES];
extern int expectedOutTestData[NUM_TEST_SAMPLES];
#endif

#ifdef __cplusplus
}
#endif

#endif // TESTDATA_H
