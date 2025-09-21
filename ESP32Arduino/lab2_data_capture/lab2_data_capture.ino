#include "FastIMU.h"
#include <Wire.h>

#include "src/imu/imu.h"
#include "src/gfx/gfx.h"


void setup() {
  Wire.begin(48, 47);
  Wire.setClock(400000); //400khz clock
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  GFX_Init();
  Gfx_InitialScreen(true);

  if(!IMU_init())
    {
        Serial.println("Error initialitztion IMU");
        while(1);
    }
    Serial.println("Setup finished");
}

#define NUM_TYPES 2
#define NUM_SAMPLES_FOR_TYPE 30
#define NUM_ITEMS_FOR_SAMPLE 50
int NumSample=0;
int SampleType=0;
ItemData SampleItems[NUM_TYPES][NUM_SAMPLES_FOR_TYPE][NUM_ITEMS_FOR_SAMPLE];

void loop() {

  char buffer[10];

  if(NumSample>=NUM_SAMPLES_FOR_TYPE)
  {
    SampleType++;
    NumSample=0;
    
    Serial.println("------------------------------------------");
  }
  if(SampleType>=NUM_TYPES)
  {
    Serial.println("------------------------------------------");
    Serial.println("------------------------------------------");
    Serial.println("All data has been collected");
    Serial.println("Press Return to send data using serial port.");
    Gfx_EndDataCollection();
    while(Serial.read(buffer,1)==0);
    PrintDataCollected(SampleItems);
    Gfx_println("");
    Gfx_println("  Process finished  ");
    while(1);
  }


  while(Serial.read(buffer,1)==1); //Remove all pendig returns;

  Serial.print("SampleType: ");
  Serial.print(SampleType+1);
  Serial.print(" / ");
  Serial.println(NUM_TYPES);
  Serial.print("NumSample: ");
  Serial.print(NumSample+1);
  Serial.print(" / ");
  Serial.println(NUM_SAMPLES_FOR_TYPE);
  Serial.println("Press return to start next sample");
  Gfx_RecordNewGesture(SampleType, NUM_TYPES, NumSample,NUM_SAMPLES_FOR_TYPE);
  while(Serial.read(buffer,1)==0);
  //Gfx_WaitingForGesture();
  //WaitForActivation();
  Serial.println("... Start Reading Sample ...");
  Gfx_Recording();
  
  

  for(int numItem=0; numItem<NUM_ITEMS_FOR_SAMPLE; numItem++)
  {
    ItemData itemData=IMU_UpdateAndGetItemData();
    SampleItems[SampleType][NumSample][numItem]=itemData;

    PrintItem(SampleType, NumSample, numItem, itemData);
    
    delay(20);
  }

  NumSample++;
}

void PrintDataCollected(ItemData SampleItems[NUM_TYPES][NUM_SAMPLES_FOR_TYPE][NUM_ITEMS_FOR_SAMPLE])
{
  PrintCaption();
  for(int SampleType=0;SampleType<NUM_TYPES;SampleType++)
  {
    for(int NumSample=0;NumSample<NUM_SAMPLES_FOR_TYPE;NumSample++)
    {
      for(int numItem=0; numItem<NUM_ITEMS_FOR_SAMPLE; numItem++)
      {
        PrintItem(SampleType, NumSample, numItem,SampleItems[SampleType][NumSample][numItem]);
      }
    }
  }
}

void PrintCaption(void)
{
    Serial.print("SampleType");
    Serial.print("\t");
    Serial.print("NumSample");
    Serial.print("\t");
    Serial.print("numItem");
    Serial.print("\t");
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
void PrintItem(int SampleType, int NumSample, int numItem, ItemData itemData) 
{
    Serial.print(SampleType);
    Serial.print("\t");
    Serial.print(NumSample);
    Serial.print("\t");
    Serial.print(numItem);
    Serial.print("\t");
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
