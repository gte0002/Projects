/*
 * This is the Arduino code for two or more DHT22 (or DHT11) module to read temprature and humidity

 * Watch the video https://youtu.be/oi_GPSLjgBY
  * Other Arduino libarary and videos http://robojax.com/learn/arduino/
 *  * 
 * Written/updated by Ahmad Shamshiri for Robojax.com Video
 * Date: Nov 21, in Ontario, Canada
Nejrabi
 * original source code : https://github.com/adafruit/DHT-sensor-library
 */

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
/*
* Get this code and other Arduino codes from Robojax.com
Learn Arduino step by step in structured course with all material, wiring diagram and library
all in once place. Purchase My course on Udemy.com http://robojax.com/L/?id=62

If you found this tutorial helpful, please support me so I can continue creating 
content like this. You can support me on Patreon http://robojax.com/L/?id=63

or make donation using PayPal http://robojax.com/L/?id=64

 *  * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#include "DHT.h"

#define DHT1_PIN 2     // for first DHT module
#define DHT2_PIN 3     // for 2nd DHT module and do the same for 3rd and 4th etc.

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)



// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht1(DHT1_PIN, DHTTYPE);//for first DHT module
DHT dht2(DHT2_PIN, DHTTYPE);// for 2nd DHT module and do the same for 3rd and 4th etc.

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx Robojax test!");

  dht1.begin();//for first DHT module
  dht2.begin();//for 2nd DHT module  and do the same for 3rd and 4th etc.
}

void loop() {
  // Wait a few seconds between measurements.
  delay(4000);


  // Robojax.com test video
  Serial.print("Temperature 1: ");
  Serial.print(getTemp("h", 1));// get DHT1 temperature in C 
  Serial.print(" H% ");
  
  Serial.print(getTemp("f", 1));// get DHT1 temperature in F
  Serial.println (" *F");
  Serial.println("-----------------");  


  Serial.print("Temperature 2: ");
  Serial.print(getTemp("h", 2));// get DHT2 temperature in C 
  Serial.print(" *H ");
  
  Serial.print(getTemp("f", 2));// get DHT2 temperature in F
  Serial.println (" *F");
  Serial.println("-----------------");  
}


/*
 * getTemp(String req, int dhtCount)
 * returns the temprature related parameters
 * req is string request
 dhtCount is 1 or 2 or 3 as you wish
 * This code can display temprature in:
 * getTemp("c", 1) is used to get Celsius for first DHT
 * getTemp("f", 2) is used to get fahrenheit for 2nd DHT
 * getTemp("k"m 1) is used for Kelvin for first DHT
 * getTemp("hif", 1) is used to get fahrenheit for first DHT
 * getTemp("hic", 2) is used to get Celsius for 2nd DHT
 * getTemp("f", 2) is used to get humidity for 2nd DHT
 */
float getTemp(String req, int dhtCount)
{

if(dhtCount ==1){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t1 = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f1 = dht1.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif1 = dht1.computeHeatIndex(f1, h1);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic1 = dht1.computeHeatIndex(t1, h1, false);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  

  // Compute heat index in Kelvin 
  float k1 = t1 + 273.15;
  if(req =="c"){
    return t1;//return Cilsus
  }else if(req =="f"){
    return f1;// return Fahrenheit
  }else if(req =="h"){
    return h1;// return humidity
  }else if(req =="hif"){
    return hif1;// return heat index in Fahrenheit
  }else if(req =="hic"){
    return hic1;// return heat index in Cilsus
  }else if(req =="k"){
    return k1;// return temprature in Kelvin
  }else{
    return 0.000;// if no reqest found, retun 0.000
  }
}// DHT1 end

float f1;
float h1;
if(dhtCount ==2){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h2 = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  float t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f2 = dht2.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif2 = dht2.computeHeatIndex(f1, h1);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic2 = dht2.computeHeatIndex(t2, h2, false);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  

  // Compute heat index in Kelvin 
  float k2 = t2 + 273.15;
  if(req =="c"){
    return t2;//return Cilsus
  }else if(req =="f"){
    return f2;// return Fahrenheit
  }else if(req =="h"){
    return h2;// return humidity
  }else if(req =="hif"){
    return hif2;// return heat index in Fahrenheit
  }else if(req =="hic"){
    return hic2;// return heat index in Cilsus
  }else if(req =="k"){
    return k2;// return temprature in Kelvin
  }else{
    return 0.000;// if no reqest found, retun 0.000
  }
}// DHT2 end

}//getTemp end
