#define BLYNK_TEMPLATE_ID "TMPL3p7xOYjMR"
#define BLYNK_TEMPLATE_NAME "vinu"


#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
const int relayPin = 5;
float tempFloat1;
float tempFloat2;

BLYNK_WRITE(V0)
{
  if (param.asInt() == 1)
  {
    digitalWrite(relayPin, HIGH);
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  Blynk.virtualWrite(V1, tempFloat1);
  Blynk.virtualWrite(V2, tempFloat2);
}

void setup()
{
  pinMode(relayPin, OUTPUT); // Initialise digital pin 2 as an output pin
  Serial.begin(9600);
  delay(100);

  BlynkEdgent.begin();
}

void loop()
{
  // Check if there is data available to read from Serial
  if (Serial.available() > 0)
  {
    // Read the incoming line from Serial
    String serialData = Serial.readStringUntil('\n');

    // Parse the line into two float values separated by a comma
    int commaIndex = serialData.indexOf(',');
    if (commaIndex != -1)
    {
      tempFloat1 = serialData.substring(0, commaIndex).toFloat();
      tempFloat2 = serialData.substring(commaIndex + 1).toFloat();

      // Update Blynk with the received values
      Blynk.virtualWrite(V1, tempFloat1);
      Blynk.virtualWrite(V2, tempFloat2);
    }
  }

  BlynkEdgent.run();
}