#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define FLAP_LEVER_PIN 6

RF24 radio(7,8);
unsigned long int lastMessageTime;
const byte addresses[][6] = {"00001", "00002"};
int alieron;
int rudder;
int elevator;
int throttle;
int controlData[5];
int batteryVoltage = 1;
int flaps = 0;

#define RESET 4
#define ALIERON 0
#define RUDDER 1
#define ELEVATOR 2
#define THROTTLE 3
#define FLAPS 4


Adafruit_SSD1306 display(OLED_RESET);



void setup() {

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(1000); // Pause for 2 seconds
  display.clearDisplay();
  display.display();

  Serial.begin(115200);
  pinMode(12, OUTPUT);
  pinMode(RESET, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MAX);
  pinMode(FLAP_LEVER_PIN, INPUT_PULLUP);
  lastMessageTime = millis();

}

void loop() {
  delay(5);
  
  radio.stopListening();

  controlData[ALIERON] = analogRead(A3);
  controlData[RUDDER] = analogRead(A0);
  controlData[ELEVATOR] = analogRead(A2);
  controlData[THROTTLE] = analogRead(A1);

  Serial.println(controlData[THROTTLE]);

  if (digitalRead(FLAP_LEVER_PIN) == true) {
    controlData[FLAPS] = 100;
  }

  else{
    controlData[FLAPS] = 0;
  }
  
  if (radio.write(&controlData, sizeof(controlData))){
    delay(5);
    radio.startListening();
    while (!radio.available());
    radio.read(&batteryVoltage, sizeof(batteryVoltage));
    lastMessageTime = millis();
  }

  if ((millis() - lastMessageTime) > 500 ){
    Serial.println("Transmission failed! Reconecting...");
    //digitalWrite(RESET, LOW);

  }





  //display.clearDisplay();
  //display.setCursor(0,0);
  //display.setTextSize(2);  /*OLED screen text size defined*/
  //display.setTextColor(WHITE); /*OLED screen text color*/
  //display.print("V:  ");
  //display.print("test");
  //display.print("mV");
  //display.display();




}
