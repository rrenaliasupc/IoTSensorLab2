
#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#define EXAMPLE_PIN_NUM_LCD_SCLK 39
#define EXAMPLE_PIN_NUM_LCD_MOSI 38
#define EXAMPLE_PIN_NUM_LCD_MISO 40
#define EXAMPLE_PIN_NUM_LCD_DC 42
#define EXAMPLE_PIN_NUM_LCD_RST -1
#define EXAMPLE_PIN_NUM_LCD_CS 45
#define EXAMPLE_PIN_NUM_LCD_BL 1

#define EXAMPLE_LCD_ROTATION 2
#define EXAMPLE_LCD_H_RES 240
#define EXAMPLE_LCD_V_RES 320

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_ESP32SPI(
  EXAMPLE_PIN_NUM_LCD_DC /* DC */, EXAMPLE_PIN_NUM_LCD_CS /* CS */,
  EXAMPLE_PIN_NUM_LCD_SCLK /* SCK */, EXAMPLE_PIN_NUM_LCD_MOSI /* MOSI */, EXAMPLE_PIN_NUM_LCD_MISO /* MISOc:\Users\rrena\Documents\MERIT\21 - Iot Sensor Systems\Lab2\IoTSensorLab2\ESP32Arduino\lab2_data_capture\src\gfx\gfx.h */);

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_ST7789(
  bus, EXAMPLE_PIN_NUM_LCD_RST /* RST */, EXAMPLE_LCD_ROTATION /* rotation */, true /* IPS */,
  EXAMPLE_LCD_H_RES /* width */, EXAMPLE_LCD_V_RES /* height */);

/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

void GFX_Init(void)
{
#ifdef GFX_EXTRA_PRE_INIT
  GFX_EXTRA_PRE_INIT();
#endif

  // Init Display
  if (!gfx->begin())
  {
    Serial.println("gfx->begin() failed!");
  }
  gfx->fillScreen(BLACK);

#ifdef EXAMPLE_PIN_NUM_LCD_BL
  pinMode(EXAMPLE_PIN_NUM_LCD_BL, OUTPUT);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_BL, HIGH);
#endif
  gfx->setCursor(0, 20);
  gfx->setTextSize(2); // 1 to 6
  gfx->setTextColor(BLUE);

}

void Gfx_InitialScreen(bool IsCapture)
{
  // Set text parameters
  gfx->setCursor(0, 20);
  gfx->setTextSize(2); // 1 to 6
  gfx->setTextColor(BLUE);
  gfx->println("Gesture Recognition");
  gfx->println();
  if(IsCapture)
  {
    gfx->println(" - Capture -");
  }
  else
  {
    gfx->println(" - Inference -");
  }
  gfx->println();
  gfx->setTextSize(1.5); // 1 to 6
  gfx->println("By:");
  gfx->println(" Pedro Matheus Figueredo Cristaldo");
  gfx->println(" Ricard Renalias Zueras");
  
  gfx->setTextSize(2); // 1 to 6  
  gfx->println("");
  gfx->setTextColor(WHITE);
  gfx->println("Initializating ...");

  delay(5000); // 5 seconds
}

void Gfx_WaitingForGesture(void)
{
  gfx->fillScreen(BLACK);
  gfx->setTextColor(WHITE);
  gfx->setCursor(0, 60);
  gfx->setTextSize(2); // 1 to 6
  gfx->println("  Ready for next");
  gfx->println("     gesture");
}

void Gfx_Recording(void)
{
  gfx->fillScreen(WHITE);
  gfx->setTextColor(BLACK);
  gfx->setCursor(20, 60);
  gfx->setTextSize(2); // 1 to 6
  gfx->println("Recording movement");
}

void Gfx_Presenting_RecognitedType(int Type,float probability)
{
  switch(Type)
  {
    case 0:
      gfx->fillScreen(BLUE);
      gfx->setTextColor(WHITE);

      break;
    case 1:
      gfx->fillScreen(ORANGE);
      gfx->setTextColor(WHITE);
      break;
    default:
      gfx->fillScreen(BLACK);
      gfx->setTextColor(WHITE);

  }
  gfx->setTextSize(4); // 1 to 6
  gfx->setCursor(40, 100);
  gfx->print("Type ");  
  gfx->println(Type);

   gfx->setTextSize(2); // 1 to 6
   gfx->setCursor(20, 140);
   gfx->print("Probability: ");  
   gfx->println(probability);

}

void Gfx_RecordNewGesture(int Type, int Types, int CurrentSample,int TotalSamples)
{
  switch(Type)
  {
    case 0: gfx->fillScreen(BLUE); break;
    case 1: gfx->fillScreen(ORANGE); break;
    default: gfx->fillScreen(BLACK); break;
  }
  
  gfx->setTextColor(WHITE);
  gfx->setCursor(0, 30);
  gfx->setTextSize(2); // 1 to 6
  gfx->println("  Ready for next");
  gfx->println("     gesture");
  gfx->println("");
  gfx->print("SampleType: ");
  gfx->print(Type+1);
  gfx->print(" / ");
  gfx->println(Types);
  gfx->print("NumSample: ");
  gfx->print(CurrentSample+1);
  gfx->print(" / ");
  gfx->println(TotalSamples);
  gfx->println("");
  gfx->println("Press return to");
  gfx->println("start next sample");
}

void Gfx_EndDataCollection(void)
{
  gfx->fillScreen(GREEN);
  gfx->setTextColor(WHITE);
  gfx->setCursor(0, 30);
  gfx->setTextSize(2); // 1 to 6
  gfx->println("All data has been");
  gfx->println(" collected");
  gfx->println();
  gfx->println(" Press Return");
  gfx->println(" to send data"); 
  gfx->println("using serial port");
}

void Gfx_print(char* text)
{
  gfx->print(text);
}

void Gfx_println(char* text)
{
  gfx->println(text);
}

#ifdef __NODEF__
void loop()
{
  gfx->setCursor(random(gfx->width()), random(gfx->height()));
  gfx->setTextColor(random(0xffff), random(0xffff));
  gfx->setTextSize(random(6) /* x scale */, random(6) /* y scale */, random(2) /* pixel_margin */);
  gfx->println("Hello World!");

  delay(1000); // 1 second
}
#endif //__NODEF__