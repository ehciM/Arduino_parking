#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LED display
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Define the ultrasonic sensor pins
const int trigPin = 12;
const int echoPin = 11;

// Define the LED bulb pins
const int redLed = 7;
const int yellowLed = 6;
const int greenLed = 5;

void setup() {
  // Initialize the LED display
  lcd.init();
  lcd.backlight();
  
  // Set the LED bulb pins as output
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  // Set the ultrasonic sensor pins as input/output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Clear the LED display
  lcd.clear();
  
  // Display the initial message on the LED display
  lcd.setCursor(0, 0);
  lcd.print("Available slots:");
  lcd.setCursor(0, 1);
  lcd.print("3");
}

void loop() {
  // Send a 10us pulse to the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the ultrasonic pulse
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm
  int distance = duration * 0.034 / 2;
  
  // Display the distance on the LED display
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm   ");
  
  // Control the LED bulbs based on the distance
  if (distance <= 10) {
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
  } else if (distance > 10 && distance <= 20) {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  
  // Update the available parking slots on the LED display
  int availableSlots = 3;
  if (distance < 20) {
    availableSlots--;
  }
  lcd.setCursor(15, 1);
  lcd.print(availableSlots);
}