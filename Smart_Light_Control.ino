/* Smart Lighting Control System */

// Include the library files
#define BLYNK_TEMPLATE_ID "TMPL680hnGYYI"  // Your Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Control LED"  // Your Blynk Template Name
#define BLYNK_AUTH_TOKEN "xMpIrBstcQrvjy_FFrlhCzXH5vGWC3H2" // Your Blynk Auth Token

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define LED pins
#define LED1 D1
#define LED2 D2
#define LED3 D3
#define wifiLed D0
#define IR_SENSOR D5 // Define the Active Infrared Sensor pin

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SK 360";    // WiFi SSID
char pass[] = "ilham@456"; // WiFi Password

bool isAutomaticMode = false; // Flag to determine the current mode
bool led1State = false;       // Track LED1 state from the Blynk app
bool led2State = false;       // Track LED2 state from the Blynk app
bool led3State = false;       // Track LED3 state from the Blynk app
bool motionDetected = false;  // Track if motion was detected

// Get the mode switch values
BLYNK_WRITE(V3) {
  isAutomaticMode = param.asInt(); // Read the value from Switch Widget (V3)
}

// Get the button values for LED1
BLYNK_WRITE(V0) {
  led1State = (param.asInt() == 0); // Blynk ON = 1, OFF = 0
  if (!isAutomaticMode) { // If in Remote Mode, control the LED directly
    digitalWrite(LED1, led1State ? HIGH : LOW); // LOW = ON, HIGH = OFF
  }
}

// Get the button values for LED2
BLYNK_WRITE(V1) {
  led2State = (param.asInt() == 0); // Blynk ON = 1, OFF = 0
  if (!isAutomaticMode) { // If in Remote Mode, control the LED directly
    digitalWrite(LED2, led2State ? HIGH : LOW); // LOW = ON, HIGH = OFF
  }
}

// Get the button values for LED3
BLYNK_WRITE(V2) {
  led3State = (param.asInt() == 0); // Blynk ON = 1, OFF = 0
  if (!isAutomaticMode) { // If in Remote Mode, control the LED directly
    digitalWrite(LED3, led3State ? HIGH : LOW); // LOW = ON, HIGH = OFF
  }
}

void setup() {
  Serial.begin(9600);
  delay(100);

  // Set the LED pins as output pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(wifiLed, OUTPUT);
  pinMode(IR_SENSOR, INPUT); // Set the IR sensor as input

  // Turn OFF the LEDs initially
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(wifiLed, HIGH);

  // Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  // Run the Blynk library
  Blynk.run();

  // Check the IR sensor value only in Automatic Mode
  if (isAutomaticMode) {
    motionDetected = digitalRead(IR_SENSOR); // Read the IR sensor

    if (motionDetected == HIGH) {
      // Motion detected: Turn ON only the LEDs with their app state set to ON
      if (led1State) {
        digitalWrite(LED1, LOW); // Turn ON LED1
      }
      if (led2State) {
        digitalWrite(LED2, LOW); // Turn ON LED2
      }
      if (led3State) {
        digitalWrite(LED3, LOW); // Turn ON LED3
      }
    } else {
      // Motion not detected: Wait for 3 seconds before turning OFF the LEDs
      delay(3000);
      if (led1State) {
        digitalWrite(LED1, HIGH); // Turn OFF LED1
      }
      if (led2State) {
        digitalWrite(LED2, HIGH); // Turn OFF LED2
      }
      if (led3State) {
        digitalWrite(LED3, HIGH); // Turn OFF LED3
      }
    }
  }
}




