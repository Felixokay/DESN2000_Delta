#include <SoftwareSerial.h>
SoftwareSerial unos(2, 3); // RX | TX
// defineing Off/On variables ******************************
int total_p;
int device_1;
int device_2;
int device_3;
int device_4;
int device_5;
int device_6;
int device_7;
int device_8;
int device_9;
int device_10;
int device_11;
int device_12;
int device_13;
int device_14;
float voltage_read;
float current_read;
float voltage_sense;
float beta = 0.277;
float offset = -0.00082;
// defining power vaiables ************************************
int power_d1 = 2; // L1 pin13
int power_d2 = 2; // L2 pin12
int power_d3 = 2; // L3 pin11
int power_d4 = 2; //L4 pin10
int power_d5 = 38; // HVAC1 pin9 
int power_d6 = 38; // HVAC2 pin8
int power_d7 = 38; // HVAC3 pin7
int power_d8 = 60; // WH pin6
int power_d9 = 1; // FF pin5
int power_d10 = 59; // SO pin4
int power_d11 = 7; // TV pinA0
int power_d12 = 3; // CO pinA1
int power_d13 = 3; // WM PinA2
int power_d14 = 0; // EMPTY 

void setup(void){

  // seting up digital  input pins
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  pinMode(10,INPUT);
  pinMode(9,INPUT);
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  //Start hardware Serial communication
  Serial.begin(9600);
  //Start the software serial for communication with the ESP8266 component
 unos.begin(9600);  
float power_max = 12370;
}

void loop(void){
int solar_check = unos.read();
device_1 = digitalRead(13);
device_2 = digitalRead(12);
device_3 = digitalRead(11);
device_4 = digitalRead(10);
device_5 = digitalRead(9);
device_6 = digitalRead(8);
device_7 = digitalRead(7);
device_8 = digitalRead(6);
device_9 = digitalRead(5);
device_10 = digitalRead(4);
device_11 = digitalRead(A0);
device_12 = digitalRead(A1);
device_13 = digitalRead(A2);
device_14 = digitalRead(A3);
current_read = analogRead(A4);
// current_read00 = analogRead(A5);


 
if (unos.available() >= 0) {
Serial.println("ESP connected !!!!");
Serial.print("Check bit is:  ");

Serial.println(solar_check);
}

  
float total_p = 0;
int panel_p = 0;
float solar_power = 0;
float panel_voltage;
float panel_current;
float current_sc = 0.3;
float insolation;
///// power calculations
panel_voltage = (5.0*voltage_read/1023);
voltage_sense = current_read *5.000/1023;
panel_current = voltage_sense*beta + offset;
insolation = panel_current/current_sc * 1000;


Serial.print(voltage_sense);
 if (device_1 == 0)
{
  total_p += power_d1;
}

 if (device_2 ==0)
{
  total_p += power_d2;
}

 if (device_3 == 0)
{
  total_p += power_d3;
}

 if (device_4 == 0)
{
  total_p += power_d4;
}

 if (device_5 == 0)
{
  total_p += power_d5;
}

 if (device_6 == 0)
{
  total_p += power_d6;
}


 if (device_7 == 0)
{
  total_p += power_d7;
}

 if (device_8 == 0)
{
  total_p += power_d8;
}

 if (device_9 == 0)
{
  total_p += power_d9;
}

 if (device_10 == 0)
{
  total_p += power_d10;
}

 if (device_11 == 0)
{
  total_p += power_d11;
}

 if (device_12 == 0)
{
  total_p += power_d12;
}

 if (device_13 == 0)
{
  total_p += power_d13;
}


if (solar_check == 0)
{
int data = 255 * 120/1544;
Serial.println(data);




unos.write(total_p);
Serial.print("total power is:  ");
Serial.print(total_p * 12370.0/255);
Serial.println ("mW");
Serial.print("Data sent = ");

Serial.println((total_p));
Serial.print("Resolution :");




}
else if  (solar_check == 1) ////  check if solar panel needs to be masured
{
int data2 =  insolation * 255/1000;
unos.write(data2 );
Serial.print("panel_current =  ");
Serial.println(panel_current );

}







}
