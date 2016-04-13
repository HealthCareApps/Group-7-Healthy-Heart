/*
 *  eHealth sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi 
 *  users to perform biometric and medical applications by using 9 different 
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and 
 *  Patient Position (Accelerometer)." 
 *
 *  In this example we read the values of the pulsioximeter sensor 
 *  and we show this values in the serial monitor
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version 2.0
 *  Author: Ahmad Saad & Luis Martin
 */

String message; //string that stores the incoming message
#include <PinChangeInt.h>
#include <eHealth.h>


int cont = 0;

void setup() {
   
  eHealth.initPulsioximeter();

  //Attach the inttruptions for using the pulsioximeter.   
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
  
  Serial.begin(9600);
  
  
}
byte x = 0;
void loop() {
  int TotalBPM=0;
  int avgBPM=0;
  int TotalOX=0;
  int avgOX=0;
  int i=0;
  
  
  
  while(Serial.available())
  {//while there is data available on the serial monitor
    message+=char(Serial.read());//store string from serial command
  }
  //Serial.println(message);
   
  while(message=="r")
  {
  if(eHealth.getBPM()>30&&eHealth.getOxygenSaturation()>50)
  {
    for(i=0;i<5;i++)
    {
      if(eHealth.getBPM()>30&&eHealth.getOxygenSaturation()>50)
      {
      TotalBPM+=eHealth.getBPM();
      TotalOX+=eHealth.getOxygenSaturation();
      delay(1000);
      }
      else
      {
        break;
      }
      
    }
    avgBPM=TotalBPM/i;
    avgOX=TotalOX/i;
    
    

 
   
    
    Serial.print("PRbpm :"); 
    Serial.print(avgBPM);

    Serial.print("    %SPo2 :");
    Serial.print(avgOX);

    Serial.print("\n");  
   break;
    
    //Serial.println(message);
    
  }
  
  }
  
  message="";

  
  
   
}


//Include always this code when using the pulsioximeter sensor
//=========================================================================
void readPulsioximeter(){  

  cont ++;

  if (cont == 50) { //Get only of one 50 measures to reduce the latency
    eHealth.readPulsioximeter();  
    cont = 0;
  }
}


