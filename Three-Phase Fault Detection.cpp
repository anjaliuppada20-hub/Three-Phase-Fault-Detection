# Three-Phase-Fault-Detection
// Three-Phase Fault Detection System

const int phaseR = A0;
const int phaseY = A1;
const int phaseB = A2;

const int relayPin = 8;

const float VREF = 5.0;
const float ADC_MAX = 1023.0;

// Example voltage limits
const float MIN_VOLTAGE = 180.0;
const float MAX_VOLTAGE = 250.0;

float readVoltage(int pin) {
  int adcValue = analogRead(pin);
  float sensorVoltage = (adcValue * VREF) / ADC_MAX;

  // Voltage sensor scaling
  return sensorVoltage * 100.0;
}

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  Serial.begin(9600);
}

void loop() {
  float R = readVoltage(phaseR);
  float Y = readVoltage(phaseY);
  float B = readVoltage(phaseB);

  Serial.println("===== THREE-PHASE FAULT DETECTION =====");

  Serial.print("Phase R: ");
  Serial.print(R);
  Serial.println(" V");

  Serial.print("Phase Y: ");
  Serial.print(Y);
  Serial.println(" V");

  Serial.print("Phase B: ");
  Serial.print(B);
  Serial.println(" V");

  bool fault = false;

  if (R < MIN_VOLTAGE || R > MAX_VOLTAGE) {
    Serial.println("FAULT: Phase R abnormal");
    fault = true;
  }

  if (Y < MIN_VOLTAGE || Y > MAX_VOLTAGE) {
    Serial.println("FAULT: Phase Y abnormal");
    fault = true;
  }

  if (B < MIN_VOLTAGE || B > MAX_VOLTAGE) {
    Serial.println("FAULT: Phase B abnormal");
    fault = true;
  }

  if (fault) {
    digitalWrite(relayPin, LOW);
    Serial.println("SYSTEM STATUS: FAULT - LOAD OFF");
  } else {
    digitalWrite(relayPin, HIGH);
    Serial.println("SYSTEM STATUS: NORMAL - LOAD ON");
  }

  Serial.println("----------------------------------------");
  delay(1000);
}
