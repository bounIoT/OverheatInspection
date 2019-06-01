#include <SPI.h>
#include <YunClient.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <thermistor.h>
void callback(char* topic, byte* payload, unsigned int length);
float getTemp();
//Creating Sensor Pins
const int pinTemp1 = A0, pinRed = 5, pinGreen = 4, trigPin = 3, echoPin = 2, pinTemp2 = A1, pinTemp3 = A2,  pinTemp4 = A3;
//Global Variables
char message_buff[100];
//Prepare functions
void callback(char* topic, byte* payload, unsigned int length);
String buildClientName();
String buildJson();
float getDistance();
 
 
//IBM Watson IoT Platform Details
char orgName[] = "lm71ef";
char macstr[] = "cumhurahmo";
char server[] = "lm71ef.messaging.internetofthings.ibmcloud.com";
char type[] = "arduino";
char token[] = "wdBP-!lH(0X1QaU!1L";
int port = 1883;
String clientName = buildClientName();
//Default topic name of Watson IoT Platform
String topicName = String("iot-2/cmd/+/fmt/json");
 
//Objects for Arduino works
YunClient yunClient;
PubSubClient client(server, port, callback, yunClient);
//Initialize Arduino
void setup() {
  Serial.begin(9600);
  Bridge.begin();
  Serial.print("Trying to connect to: ");
  pinMode(pinTemp1, INPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinTemp2, INPUT);
  pinMode(pinTemp3, INPUT);
  pinMode(pinTemp4, INPUT);
  delay(3000);
}
 
//Running code
void loop() {
  delay(3000);
  char clientStr[34];
  clientName.toCharArray(clientStr, 34);
  char topicStr[26];
  topicName.toCharArray(topicStr, 26);
  if (!client.connected()) {
    digitalWrite(pinRed, HIGH); //Device could not connect
    digitalWrite(pinGreen, LOW);
    Serial.println(clientStr);
    client.connect(clientStr, "use-token-auth", token);
    if (client.connect(clientStr, "use-token-auth", token)) {
      client.setCallback(callback);
      Serial.println("Connection successful ...");
      if (client.subscribe("iot-2/cmd/cid/fmt/json", 0)) {
        Serial.println("Subscribed to iot-2/cmd/cid/fmt/json");
      } else {
        Serial.println("NOT Subscribed to iot-2/cmd/cid/fmt/json");
      }
    }
  }
  if (client.connected()) {
    digitalWrite(pinRed, LOW);
    digitalWrite(pinGreen, HIGH); //Successful connection
    //Serial.println("Online...Begin transmit...");
    // Build the JSON data to publish.
    String json = buildJson();
    char jsonStr[200];
    json.toCharArray(jsonStr, 200);
    Serial.println(jsonStr);
    // Publish the data.
    client.publish("iot-2/evt/status/fmt/json", jsonStr);
  }
}
 
// Builds the clientName
String buildClientName () {
  String data = "";
  data += "d:";
  data += orgName;
  data += ":";
  data += type;
  data += ":";
  data += macstr;
  return data;
}
 
// Builds the JSON
String buildJson() {
  char buffer[60];
  String data = "{\"d\":{\"Temperature\":";
  dtostrf(getTemp(), 1, 2, buffer);
  data += buffer;
  data += ",\"Temp2\":";
  dtostrf(getTemp2(), 1, 2, buffer);
  data += buffer;
  data += ",\"Temp3\":";
  dtostrf(getTemp3(), 1, 2, buffer);
  data += buffer;
  data += ",\"Temp4\":";
  dtostrf(getTemp4(), 1, 2, buffer);
  data += buffer;
  data += "}}";
  return data;
}
 
// Getting Temperature values from sensors.
void callback(char* topic, byte* payload, unsigned int length) {}
float getTemp() {
  float t = analogRead(pinTemp1);         //Read voltage value from potentiometer.
  float temp=Termistor(t);                //Calculate temperature from valtage.
  return temp;
}
float getTemp2() {
  float h = analogRead(pinTemp2);         //Read voltage value from potentiometer.
                                         //Calculate temperature from valtage.
  float temp2=Termistor(h);
  return temp2;
}
float getTemp3() {
  float h = analogRead(pinTemp3);          //Read voltage value from potentiometer.
  float temp3=Termistor(h);                 //Calculate temperature from valtage.
  return temp3;
}
float getTemp4() {
  float h = analogRead(pinTemp4); 
  float temp4=Termistor(h);
  return temp4;
}
double Termistor(float analogOkuma){            
  float Vo;
  float R1 = 6000;                               //Make potentiometer resistance 6000.
  float logR2, R2, T, Tc, Tf;
  double sicaklik;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  Vo = (analogOkuma*5/1024.0);                  //Read voltage from potentiometer.
  R2 = R1 * (5.0 / (float)Vo - 1.0)/10;         //Find the resistor value of the sensor.
  logR2 = log(R2);
  T = 1.0/(c1 + c2*logR2 + c3*logR2*logR2*logR2);  //calculate temperature with given information.
  Tc = T - 273.15;                            
  sicaklik = Tc;
  return sicaklik;
}
