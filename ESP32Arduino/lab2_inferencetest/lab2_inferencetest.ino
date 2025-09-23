#include "_project_config.h"

#include "src/imu/imu.h"
#include "inference.h"

#include "src/model/TestData.h"

#include "src/gfx/gfx.h"


/**
 * 
 */
void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("__LAB2 GESTURE DETECTION__");

    GFX_Init();
    Gfx_InitialScreen(false);

    inference_init();
    Serial.println("Initialization finished.");

#ifdef __TEST_MODEL__
    TestModelFromModelInput();
    TestModelFromSensorData();
#endif //__TEST_MODEL__    


    if(!IMU_init())
    {
        Serial.println("Error initialitztion IMU");
        while(1);
    }
    Serial.println("Setup finished");
}


void loop() {
    
    float Items[NUM_ITEMS_PER_SAMPLE][NUM_CHANNELS];
    
    Serial.println("... Ready for next gesture ...");
    Gfx_WaitingForGesture();

    WaitForActivation();
    Serial.println("... Start Reading Sample ...");
    Gfx_Recording();
    
    PrintItemCaption();
    for(int numItem=0; numItem<NUM_ITEMS_PER_SAMPLE; numItem++)
    {
        
        ItemData itemData=IMU_UpdateAndGetItemData();
        Items[numItem][0]=itemData.accelX;
        Items[numItem][1]=itemData.accelY;
        Items[numItem][2]=itemData.accelZ;
        Items[numItem][3]=itemData.gyroX;
        Items[numItem][4]=itemData.gyroY;
        Items[numItem][5]=itemData.gyroZ;
        PrintSimplifiedItem(itemData);
        //Read every 20 ms
        delay(20);
    }
    sInferenceResult inferenceResult=NormalizeAndInfere(Items);


    Serial.print("Predicted Type: ");
    Serial.println(inferenceResult.type);
    Serial.print("Probability: ");
    Serial.println(inferenceResult.probability);

    Gfx_Presenting_RecognitedType(inferenceResult.type,inferenceResult.probability);

    
    delay(3000);
}


void PrintItemCaption(void)
{
    Serial.print("accelX");
    Serial.print("\t"); 
    Serial.print("accelY");
    Serial.print("\t");
    Serial.print("accelZ");
    Serial.print("\t");
    Serial.print("gyroX");
    Serial.print("\t");
    Serial.print("gyroY");
    Serial.print("\t");
    Serial.print("gyroZ");
    Serial.println();
}
void PrintSimplifiedItem(ItemData itemData) 
{
    Serial.print(itemData.accelX);
    Serial.print("\t"); 
    Serial.print(itemData.accelY);
    Serial.print("\t");
    Serial.print(itemData.accelZ);
    Serial.print("\t");
    Serial.print(itemData.gyroX);
    Serial.print("\t");
    Serial.print(itemData.gyroY);
    Serial.print("\t");
    Serial.print(itemData.gyroZ);
    Serial.println();
}

