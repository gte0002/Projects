/*
 * This is the Arduino code for  DHT22 module to read temprature and humidity
 * This code can display temprature in:
 * getTemp("c") is used to get Celsius
 * getTemp("f") is used to get fahrenheit
 * getTemp("k") is used for Kelvin
 * getTemp("hif") is used to get fahrenheit
 * getTemp("hic") is used to get Celsius
 * getTemp("f") is used to get humidity 
 * Watch the video https://youtu.be/oi_GPSLjgBY
  * Other Arduino libarary and videos http://robojax.com/learn/arduino/
 *  * 
 * Written/updated by Ahmad Shamshiri for Robojax.com Video
 * Date: Jan 08, 2018, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * 
 * original source code : https://github.com/adafruit/DHT-sensor-library
 */

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain


#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx Robojax test!");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);


  // Robojax.com test video
  Serial.print("Temperature: ");
  
  Serial.print(getTemp("c"));
  
  Serial.print(" *C ");
  Serial.print(getTemp("f"));
  Serial.println (" *F");
  Serial.println("-----------------");  
  Serial.print("Heat index: ");
  Serial.print(getTemp("hic"));
  Serial.print(" *C ");
  Serial.print(getTemp("hif"));
  Serial.println(" *F");
  Serial.print(getTemp("k"));
  Serial.println(" *K");
  Serial.println("-----------------");    
  Serial.print("Humidity: ");
  Serial.print(getTemp("h"));
  Serial.println(" % ");
  Serial.println("===========================");
}


/*
 * getTemp(String req)
 * returns the temprature related parameters
 * req is string request
 * This code can display temprature in:
 * getTemp("c") is used to get Celsius
 * getTemp("f") is used to get fahrenheit
 * getTemp("k") is used for Kelvin
 * getTemp("hif") is used to get fahrenheit
 * getTemp("hic") is used to get Celsius
 * getTemp("f") is used to get humidity 
 */
float getTemp(String req)
{

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Kelvin 
  float k = t + 273.15;
  if(req =="c"){
    return t;//return Cilsus
  }else if(req =="f"){
    return f;// return Fahrenheit
  }else if(req =="h"){
    return h;// return humidity
  }else if(req =="hif"){
    return hif;// return heat index in Fahrenheit
  }else if(req =="hic"){
    return hic;// return heat index in Cilsus
  }else if(req =="k"){
    return k;// return temprature in Kelvin
  }else{
    return 0.000;// if no reqest found, retun 0.000
  }
} 
