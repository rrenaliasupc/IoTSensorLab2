#ifndef __IMU_H__
#define __IMU_H__
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


bool IMU_init(void);
ItemData IMU_UpdateAndGetItemData(void);

bool WaitForActivation(void);

#endif //__IMU_H__