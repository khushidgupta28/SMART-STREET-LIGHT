// Pin Definitions
const int mq135Pin = A0; // MQ135 Analog output connected to A0
const int ledPin = 9; // LED connected to PWM pin 9

// Variables
int sensorValue = 0; // Variable to store raw sensor data
int brightness = 0; // Variable to store calculated brightness

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Initialize serial monitor for debugging
  
  // Note: MQ135 requires a "warm-up" period (usually 24-48 hours for 
  // stable readings, but a few minutes is okay for basic testing).
  Serial.println("Warming up sensor...");
}

void loop() {
  // 1. Read the smoke level
  sensorValue = analogRead(mq135Pin);
  
  // 2. Map the sensor value to LED brightness.
  // Standard MQ135 idle reading is usually around 100-200.
  // We map from 200 (dim) to 800 (bright) to avoid flickering at low levels.
  brightness = map(sensorValue, 50,800,0,255);
  
  // Constrain the value so it stays within 0-255 range
  brightness = constrain(brightness, 0, 255);
  
  // 3. Set the LED brightness
  analogWrite(ledPin, brightness);
  
  // Debugging: Print values to Serial Monitor
  Serial.print("Smoke Level: ");
  Serial.print(sensorValue);
  Serial.print(" | LED Brightness: ");
  Serial.println(brightness);
  
  delay(100); // Small delay for stability
}

