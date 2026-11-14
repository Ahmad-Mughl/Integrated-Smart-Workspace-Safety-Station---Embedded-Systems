#include <Wire.h>

// I2C Addresses
#define OPT3001_ADDR 0x44 
#define TMP006_ADDR  0x40

// Thresholds
const float LUX_DANGER_LOW    = 50.0;
const float TEMP_DANGER_HIGH  = 35.0;
const float LUX_CAUTION_LOW   = 200.0;
const float TEMP_CAUTION_HIGH = 30.0;

// Hardware Pins
const int LED_RED   = RED_LED;
const int LED_GREEN = GREEN_LED;
const int LED_BLUE  = BLUE_LED;
const int BUZZER    = 40;
const int S1_RESET  = PUSH1;
const int S2_MODE   = 2;

// State Variables
bool isMaintenance = false;
bool alarmLatched  = false;

// ─────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(LED_RED,   OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE,  OUTPUT);
  pinMode(BUZZER,    OUTPUT);
  pinMode(S1_RESET,  INPUT_PULLUP);
  pinMode(S2_MODE,   INPUT_PULLUP);

  initOPT3001();
  initTMP006();

  Serial.println("=== Smart Safety Station (Energia) ===");
}

// ─────────────────────────────────────────────
void loop() {

  // S2 — toggle maintenance mode
  if (digitalRead(S2_MODE) == LOW) {
    isMaintenance = !isMaintenance;
    delay(300);
  }

  // S1 — reset latched alarm
  if (digitalRead(S1_RESET) == LOW) {
    alarmLatched = false;
    Serial.println(">> Alarm Reset via S1");
  }

  float lux  = readLux();
  float temp = readTemp();

  String zone = "SAFE";
  if (lux < LUX_DANGER_LOW || temp > TEMP_DANGER_HIGH) {
    zone = "DANGER";
    alarmLatched = true;
  }
  
  else if (lux < LUX_CAUTION_LOW || temp > TEMP_CAUTION_HIGH) {
    zone = "CAUTION";
  }

  updateFeedback(zone);

  Serial.print("Mode: ");  Serial.print(isMaintenance ? "MAINT" : "ACTIVE");
  Serial.print(" | Lux: "); Serial.print(lux);
  Serial.print(" | Temp: "); Serial.print(temp);
  Serial.print(" | Zone: "); Serial.println(zone);

  delay(500);
}

// ─────────────────────────────────────────────
void initOPT3001() {
  Wire.beginTransmission(OPT3001_ADDR);
  Wire.write(0x01);
  Wire.write(0xCE);
  Wire.write(0x10);
  Wire.endTransmission();
}

float readLux() {
  Wire.beginTransmission(OPT3001_ADDR);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(OPT3001_ADDR, 2);
  uint16_t res      = (Wire.read() << 8) | Wire.read();
  uint16_t mantissa = res & 0x0FFF;
  uint16_t exponent = (res >> 12) & 0x000F;
  return 0.01 * (1 << exponent) * mantissa;
}

// ─────────────────────────────────────────────
void initTMP006() {
  Wire.beginTransmission(TMP006_ADDR);
  Wire.write(0x02);
  Wire.write(0x74);
  Wire.write(0x00);
  Wire.endTransmission();
}

float readTemp() {
  Wire.beginTransmission(TMP006_ADDR);
  Wire.write(0x01);
  Wire.endTransmission();

  Wire.requestFrom(TMP006_ADDR, 2);
  int16_t res = (Wire.read() << 8) | Wire.read();
  return (res >> 2) * 0.03125;
}

// ─────────────────────────────────────────────
void updateFeedback(String zone) {

  if (isMaintenance) {
    digitalWrite(LED_RED,   HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE,  HIGH);
    noTone(BUZZER);
    return;
  }

  if (zone == "DANGER") {
    digitalWrite(LED_RED,   (millis() / 250) % 2);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE,  LOW);
    if (alarmLatched) tone(BUZZER, 2500);

  } 
  
  else if (zone == "CAUTION") {
    digitalWrite(LED_BLUE,  HIGH);
    digitalWrite(LED_RED,   LOW);
    digitalWrite(LED_GREEN, LOW);
    tone(BUZZER, 1000, 100);

  }
  
  else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED,   LOW);
    digitalWrite(LED_BLUE,  LOW);
    noTone(BUZZER);
  }
}