#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


#define ALIERON 0
#define RUDDER 1
#define ELEVATOR 2
#define THROTTLE 3
#define FLAPS 4


RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
Servo alieron;
Servo rudder;
Servo elevator;
Servo flaps;
Servo motor;

unsigned long int lastMessageTime;
int alieronAngle;
int rudderAngle;
int elevatorAngle;
int flapsAngle;
int motorAngle;
int rudderTest;

int controlData[5];
int batteryVoltage = 1115;

void setup() {
  Serial.begin(115200);
  motor.attach(6);
  alieron.attach(9);
  flaps.attach(10);
  rudder.attach(3);
  elevator.attach(4);

  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MAX);
  lastMessageTime = millis();

}

void loop() {
  delay(5);
  radio.startListening();

  if ( radio.available()) {
 
    while (radio.available()) {

      radio.read(&controlData, sizeof(controlData));
      lastMessageTime = millis();


      alieronAngle = map(controlData[ALIERON],113,880,30,180);
      rudderAngle = map(controlData[RUDDER],100,837,55,120);
      elevatorAngle = map(controlData[ELEVATOR],282,913,20,116);
      motorAngle = map(controlData[THROTTLE],20,1023,0,180);
      flapsAngle = map(controlData[FLAPS],0,100,90,180);

      motor.write(motorAngle);
      alieron.write(alieronAngle);
      //rudder.write(rudderAngle);
      elevator.write(elevatorAngle);
      flaps.write(flapsAngle);


      //Serial.print(motorAngle);
      //Serial.print(",");
      //Serial.print(alieronAngle);
      //Serial.print(",");
      //Serial.print(rudderAngle);
      //Serial.print(",");
      //Serial.print(elevatorAngle);
      //Serial.print("-----");



    }
      delay(5);
    radio.stopListening();
    radio.write(&batteryVoltage, sizeof(batteryVoltage));
  }

    if (0) {
      Serial.print( millis() - lastMessageTime);
      Serial.print(", ");
      Serial.print(millis());
      Serial.print(", ");
      Serial.println(lastMessageTime);
    }
    if ((millis() - lastMessageTime) > 30) {
      Serial.println("ARGHHHH signal dropped! Motor speed set to 0");
      motor.write(0);
    }
    else{
      Serial.print(motorAngle);
      Serial.print(",");
      Serial.print(rudderAngle);
      Serial.print(",");
      Serial.print(elevatorAngle);
      Serial.print(",");
      Serial.print(alieronAngle);
      Serial.print(",");
      Serial.print(flapsAngle);
      Serial.print("\n");

    }





}
