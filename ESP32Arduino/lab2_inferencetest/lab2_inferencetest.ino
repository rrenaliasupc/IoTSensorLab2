#include "_project_config.h"

#include "imu.h"
#include "inference.h"

#include "TestData.h"



/**
 * 
 */
void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("__LAB2 GESTURE DETECTION__");

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
    WaitForActivation();
    Serial.println("... Start Reading Sample ...");
    for(int numItem=0; numItem<NUM_ITEMS_PER_SAMPLE; numItem++)
    {
        
        ItemData itemData=IMU_UpdateAndGetItemData();
        Items[numItem][0]=itemData.accelX;
        Items[numItem][1]=itemData.accelY;
        Items[numItem][2]=itemData.accelZ;
        Items[numItem][3]=itemData.gyroX;
        Items[numItem][4]=itemData.gyroY;
        Items[numItem][5]=itemData.gyroZ;

        //Read every 20 ms
        delay(20);
    }
    int PredictedType=NormalizeAndInfere(Items);

    Serial.print("Predicted Type: ");
    Serial.println(PredictedType);
    delay(3000);
}



