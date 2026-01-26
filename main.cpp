#include <Arduino.h>
#include <Wire.h>

#define SDA 21
#define SCL 22
#define RDY 23
#define EN 19

enum ERROR{
  SUCCESS = 0,
  DATA_TOO_LONG = 1,
  ADDR_NACK = 2,
  DATA_NACK = 3,
  OTHER = 4,
  TIMEOUT = 5
};

ERROR write_ADS1115(uint8_t addr, uint8_t data);

void setup() {

  //pinMode(EN, OUTPUT);
  //digitalWrite(EN, HIGH);

  pinMode(RDY, INPUT);

  Wire.begin(SDA, SCL);
  Serial.begin(9600);

  Serial.println("I2C ADC Test\n");  
}

void loop() {
  // put your main code here, to run repeatedly:
  byte error;

  Serial.println("Transmitting...");
  
  Wire.beginTransmission(0x48);

  Wire.write(0x48);
  Wire.write(0x00);
  Wire.write(0x49);
  error = Wire.endTransmission();

  Serial.printf("Error code: %d\n", error);

  byte b;

  // Wire.beginTransmission(0x48);

  Wire.requestFrom(0x48, 2);

  while (Wire.available()){
    Serial.println("Reading...");
    Serial.printf("Read status: %d\n", digitalRead(RDY));
    b = Wire.read();
    Serial.printf("Byte : %d\n", b);

  }

  //error = Wire.endTransmission();

  //Serial.printf("Error code: %d\n", error);

  delay(1000); 
}

ERROR write_ADS1115(uint8_t addr, uint8_t data){
  int error;
  Wire.beginTransmission(addr);

  Wire.write(0x48);
  Wire.write(data);

  error = Wire.endTransmission();

  switch (error){
    case 0:
    return SUCCESS;
    case 1:
    return DATA_TOO_LONG;
    case 2:
    return ADDR_NACK;
    case 3:
    return DATA_NACK;
    case 5:
    return TIMEOUT;
    default:
    return OTHER;
  }

}

ERROR read_ADS1115(uint8_t addr, uint8_t num_bytes){
  int error;
  Wire.beginTransmission(addr);

  Wire.write(0x49);

  error = Wire.endTransmission();

  switch (error){
    case 0:
    return SUCCESS;
    case 1:
    return DATA_TOO_LONG;
    case 2:
    return ADDR_NACK;
    case 3:
    return DATA_NACK;
    case 5:
    return TIMEOUT;
    default:
    return OTHER;
  }

}

