// PROJECT 23
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define sensorPin 0
#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer, outsideThermometer;

float temp_in_celsius = 0;
float temp_in_kelvin = 0;
float temp_in_fahrenheit = 0;
int sensorValue;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  Serial.println("Initializing...");
  lcd.begin(16, 2);
  
  sensors.begin();
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(outsideThermometer, 1)) Serial.println("Unable to find address for Device 1");
  
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(outsideThermometer);
  Serial.println();
}

void printAddress(DeviceAddress deviceAddress)
{
  for (int i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

void loop() {
  sensorValue = analogRead(sensorPin);
  temp_in_kelvin = (((float(sensorValue) / 1023) * 5) * 100);
  temp_in_celsius = temp_in_kelvin - 273.15; 
  temp_in_fahrenheit = (temp_in_celsius * 1.8) + 32;

  display();
  
  Serial.print("Requresting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
  printData(insideThermometer);
  printData(outsideThermometer);
  Serial.println();
  delay(1000);
}

void display() {
  Serial.print("Celsius: ");
  Serial.println(temp_in_celsius);
  Serial.print("Fahrenheit: ");
  Serial.println(temp_in_fahrenheit);
  Serial.println();

  lcd.clear();
  lcd.print(temp_in_fahrenheit);
  lcd.print(" Fahrenheit");
  lcd.setCursor(0, 1);
  lcd.print(temp_in_celsius);
  lcd.print(" Celsius");
  delay(500);
}
