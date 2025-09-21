#include "FastIMU.h"
#include <Wire.h>

#include "src/gfx/gfx.h"

#define IMU_ADDRESS 0x6B    //Change to the address of the IMU
#define PERFORM_CALIBRATION //Comment to disable startup calibration
QMI8658 IMU;               //Change to the name of any supported IMU! 

// Currently supported IMUS: MPU9255 MPU9250 MPU6886 MPU6500 MPU6050 ICM20689 ICM20690 BMI055 BMX055 BMI160 LSM6DS3 LSM6DSL QMI8658

calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data
GyroData gyroData;
MagData magData;

void setup() {
  Wire.begin(48, 47);
  Wire.setClock(400000); //400khz clock
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  GFX_Init();
  Gfx_InitialScreen(true);

  int err = IMU.init(calib, IMU_ADDRESS);
  if (err != 0) {
    Serial.print("Error initializing IMU: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
  
#ifdef PERFORM_CALIBRATION
  Serial.println("FastIMU calibration & data example");
  if (IMU.hasMagnetometer()) {
    delay(1000);
    Serial.println("Move IMU in figure 8 pattern until done.");
    delay(3000);
    IMU.calibrateMag(&calib);
    Serial.println("Magnetic calibration done!");
  }
  else {
    delay(5000);
  }

  delay(5000);
  Serial.println("Keep IMU level.");
  Gfx_println("Calibrating IMU");
  Gfx_println("Keep IMU level");
  delay(5000);
  IMU.calibrateAccelGyro(&calib);
  Serial.println("Calibration done!");
  Serial.println("Accel biases X/Y/Z: ");
  Serial.print(calib.accelBias[0]);
  Serial.print(", ");
  Serial.print(calib.accelBias[1]);
  Serial.print(", ");
  Serial.println(calib.accelBias[2]);
  Serial.println("Gyro biases X/Y/Z: ");
  Serial.print(calib.gyroBias[0]);
  Serial.print(", ");
  Serial.print(calib.gyroBias[1]);
  Serial.print(", ");
  Serial.println(calib.gyroBias[2]);
  if (IMU.hasMagnetometer()) {
    Serial.println("Mag biases X/Y/Z: ");
    Serial.print(calib.magBias[0]);
    Serial.print(", ");
    Serial.print(calib.magBias[1]);
    Serial.print(", ");
    Serial.println(calib.magBias[2]);
    Serial.println("Mag Scale X/Y/Z: ");
    Serial.print(calib.magScale[0]);
    Serial.print(", ");
    Serial.print(calib.magScale[1]);
    Serial.print(", ");
    Serial.println(calib.magScale[2]);
  }
  delay(5000);
  IMU.init(calib, IMU_ADDRESS);
#endif

  //err = IMU.setGyroRange(500);      //USE THESE TO SET THE RANGE, IF AN INVALID RANGE IS SET IT WILL RETURN -1
  //err = IMU.setAccelRange(2);       //THESE TWO SET THE GYRO RANGE TO ±500 DPS AND THE ACCELEROMETER RANGE TO ±2g
  
  if (err != 0) {
    Serial.print("Error Setting range: ");
    Serial.println(err);
    while (true) {
      ;
    }
  }
}



typedef struct
{
  int numItem;
  float accelX;
  float accelY;
  float accelZ;
  float gyroX;
  float gyroY;
  float gyroZ;
}ItemData;

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
    PrintDataCollected();
    Gfx_println("");
    Gfx_println("  Process finished  ");
    while(1);
  }

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
    IMU.update();
    IMU.getAccel(&accelData);  
    IMU.getGyro(&gyroData);
    SampleItems[SampleType][NumSample][numItem].numItem=numItem;
    SampleItems[SampleType][NumSample][numItem].accelX=accelData.accelX;
    SampleItems[SampleType][NumSample][numItem].accelY=accelData.accelY;
    SampleItems[SampleType][NumSample][numItem].accelZ=accelData.accelZ;
    SampleItems[SampleType][NumSample][numItem].gyroX=gyroData.gyroX;
    SampleItems[SampleType][NumSample][numItem].gyroY=gyroData.gyroZ;
    SampleItems[SampleType][NumSample][numItem].gyroZ=gyroData.gyroY;
    
    PrintItem(SampleType, NumSample, numItem);
    
    delay(20);
  }

  NumSample++;
}

void PrintDataCollected(void)
{
  PrintCaption();
  for(int SampleType=0;SampleType<NUM_TYPES;SampleType++)
  {
    for(int NumSample=0;NumSample<NUM_SAMPLES_FOR_TYPE;NumSample++)
    {
      for(int numItem=0; numItem<NUM_ITEMS_FOR_SAMPLE; numItem++)
      {
        PrintItem(SampleType, NumSample, numItem);
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
void PrintItem(int SampleType, int NumSample, int numItem)
{
    Serial.print(SampleType);
    Serial.print("\t");
    Serial.print(NumSample);
    Serial.print("\t");
    Serial.print(numItem);
    Serial.print("\t");
    Serial.print(SampleItems[SampleType][NumSample][numItem].accelX);
    Serial.print("\t"); 
    Serial.print(SampleItems[SampleType][NumSample][numItem].accelY);
    Serial.print("\t");
    Serial.print(SampleItems[SampleType][NumSample][numItem].accelZ);
    Serial.print("\t");
    Serial.print(SampleItems[SampleType][NumSample][numItem].gyroX);
    Serial.print("\t");
    Serial.print(SampleItems[SampleType][NumSample][numItem].gyroY);
    Serial.print("\t");
    Serial.print(SampleItems[SampleType][NumSample][numItem].gyroZ);
    Serial.println();
}
