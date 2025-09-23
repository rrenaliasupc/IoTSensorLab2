#include <Arduino.h>

#include "src/model/model.h"
#include "src/model/normalization_params.h"
// include the runtime specific for your board
// either tflm_esp32 or tflm_cortexm
#include <tflm_esp32.h>


// now you can include the eloquent tinyml wrapper
#include <eloquent_tinyml.h>

#include "src/model/TestData.h"

#include "inference.h"

// this is trial-and-error process
// when developing a new model, start with a high value
// (e.g. 10000), then decrease until the model stops
// working as expected
#define ARENA_SIZE 20000

Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;


sInferenceResult NormalizeAndInfere(float inputSensorSample[NUM_ITEMS_PER_SAMPLE][NUM_CHANNELS]);

bool inference_init(void)
{
    // configure input/output
    // (not mandatory if you generated the .h model
    // using the everywhereml Python package)
    tf.setNumInputs(300);
    tf.setNumOutputs(2);
    // add required ops
    // (not mandatory if you generated the .h model
    // using the everywhereml Python package)
    tf.resolver.AddFullyConnected();
    tf.resolver.AddSoftmax();

    Serial.println("tf.begin");
    if(!tf.begin(__model_model_tflite).isOk()) 
    {
      Serial.println(tf.exception.toString());
      while(1);
    }
    Serial.println("tf.begin finished properlly");
    return true;

}


#ifdef __TEST_MODEL__
void TestModelFromModelInput(void)
{
    Serial.println("-------------------------------------------------");
    Serial.println("Test from model input");
    Serial.println("-------------------------------------------------");
    
    for(int NumSample=0;NumSample<NUM_TEST_SAMPLES;NumSample++)
    {
        // classify class NumSample
        if (!tf.predict(inputTestData[NumSample]).isOk()) {
            Serial.println(tf.exception.toString());
            return;
        }
        
        Serial.print("expected class: ");
        Serial.print(expectedOutTestData[NumSample]);
        Serial.print(", predicted class: ");
        Serial.println(tf.classification);
    }        
    // how long does it take to run a single prediction?
    Serial.print("It takes ");
    Serial.print(tf.benchmark.microseconds());
    Serial.println("us for a single prediction");
}




void TestModelFromSensorData(void)
{
    Serial.println("-------------------------------------------------");
    Serial.println("Test from sensor data");    
    Serial.println("-------------------------------------------------");
    
  
    for(int NumSample=0, i=0;NumSample<NUM_TEST_SAMPLES;NumSample++, i++)
    {
        Serial.print("NumSample: ");
        Serial.print(NumSample);
        Serial.print(" - ");
        
        sInferenceResult inferenceResult=NormalizeAndInfere(inputSensorData[NumSample]);
        


        Serial.print("expected class: ");
        Serial.print(expectedOutTestData[NumSample]);
        Serial.print(", predicted class: ");
        Serial.print(inferenceResult.type);
        Serial.print(", probability: ");
        Serial.println("inferenceResult.probability");
    }        
    // how long does it take to run a single prediction?
    Serial.print("It takes ");
    Serial.print(tf.benchmark.microseconds());
    Serial.println("us for a single prediction");
}
#endif //__TEST_MODEL__



sInferenceResult NormalizeAndInfere(float inputSensorSample[NUM_ITEMS_PER_SAMPLE][NUM_CHANNELS])
{
    sInferenceResult inferenceResult;

    float inputModelData[NUM_MODEL_FEATURES];
    //1- normalize using Zscore and 
    for(int NumItem=0; NumItem<NUM_ITEMS_PER_SAMPLE; NumItem++)
    {
        //Normalize all values and assign it to the corresponding input feature.
        for(int feature=0;feature<NUM_FEATURES;feature++)
        {
            float ValueNorm=(inputSensorSample[NumItem][feature]-normalization_params[feature].mean)/normalization_params[feature].std;
            inputModelData[NumItem*NUM_FEATURES+feature]=ValueNorm;
            //Serial.print(ValueNorm);
            //Serial.print(" ")
        }                      
    }

    //Serial.println("");
    // classify class NumSample
    if (!tf.predict(inputModelData).isOk()) {
        Serial.println(tf.exception.toString());
        inferenceResult.result=0;
        return inferenceResult;
    }

    Serial.print("Probabilities: ");
    for(int i=0;i<TF_NUM_OUTPUTS;i++)
    {
        Serial.print(tf.out->data.f[i]);
        Serial.print(" ");
    }
    Serial.println("");

    inferenceResult.result=1;
    inferenceResult.type=tf.classification;
    inferenceResult.probability=tf.out->data.f[inferenceResult.type];

    return inferenceResult;
}
