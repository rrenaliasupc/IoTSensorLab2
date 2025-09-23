#include "_project_config.h"
#include "src/model/TestData.h"

typedef struct
{
    bool result;
    int type;
    float probability;
}sInferenceResult;


bool inference_init(void);
sInferenceResult NormalizeAndInfere(float inputSensorSample[NUM_ITEMS_PER_SAMPLE][NUM_CHANNELS]);

void TestModelFromModelInput(void);
void TestModelFromSensorData(void);

