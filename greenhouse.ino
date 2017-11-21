// Demo code for Grove - Temperature Sensor V1.1/1.2
// Loovee @ 2015-8-26

#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11 
#define DHTPIN A0       // what pin we're connected to
#define DHT_ERR 255     // read fail from DHT sensor

//Temp variables
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A1;     // Grove - Temperature Sensor connect to A1,kemin modify from A5

//DHT11 variables
DHT dht(DHTPIN, DHTTYPE);

//LCD variables
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 255;
const int colorB = 255;

int getHumid()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h)) {
    Serial.println("Failed to read humidity from DHT sensor!");
    return DHT_ERR;
  }else{
    return (int)h;
  }
}

int getTemp()
{
   // Reading temperature or humidity takes about 250 milliseconds!
   // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
   // Read temperature as Celsius (the default)
   float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
      Serial.println("Failed to read temp from DHT sensor!");
      return DHT_ERR;
    }else{
      return (int)t;
    }
}

void print2LCD(int temp, int humid)
{
    // set the cursor to column 0, line 0
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 0);
    lcd.print("Temp(C):");
    lcd.setCursor(10, 0);
    lcd.print(temp);
    
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    lcd.print("Humid(%):");
    lcd.setCursor(10, 1);
    lcd.print(humid);
    
    delay(100);
}

void setup()
{
    // set up serial port
    Serial.begin(9600);

    // set up DHT11
    dht.begin();

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);

    delay(1000);
}

void loop()
{
    int temp_data = 0, humid_data = 0;
    
    //get temp data from Temp sensor via A1
    temp_data = getTemp();

    //get temp & humidy from DHT11 via A0
    humid_data = getHumid();

    //show temp data to LCD diplay via I2C
    print2LCD(temp_data,humid_data);

    //loop time period
    delay(1000);
}
