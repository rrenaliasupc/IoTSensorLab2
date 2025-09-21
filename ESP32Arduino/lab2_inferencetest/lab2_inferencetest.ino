#include "inference.h"
#include "_project_config.h"

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

}


void loop() {

        

    delay(1000);
}



