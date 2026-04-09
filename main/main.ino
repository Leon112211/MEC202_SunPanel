// ESP32-S3 servo reciprocating test (no Servo library)
constexpr int PIN_RDS3115 = 4;  // RDS3115MG signal
constexpr int PIN_DS3218  = 5;  // DS3218 signal

constexpr int US_MIN = 1000;
constexpr int US_MAX = 2000;
constexpr int STEP_US = 5;
constexpr int STEP_DELAY_MS = 10;

constexpr uint32_t SERVO_FREQ_HZ = 50;
constexpr uint8_t LEDC_BITS = 14;  // ESP32-S3 supports up to 14-bit LEDC resolution
constexpr uint32_t SERVO_PERIOD_US = 1000000UL / SERVO_FREQ_HZ;  // 20000 us
constexpr uint32_t LEDC_MAX_DUTY = (1UL << LEDC_BITS) - 1UL;

uint32_t pulseUsToDuty(int pulseUs) {
  if (pulseUs < 500) pulseUs = 500;
  if (pulseUs > 2500) pulseUs = 2500;
  return (static_cast<uint32_t>(pulseUs) * LEDC_MAX_DUTY) / SERVO_PERIOD_US;
}

void writeServoUs(int pin, int pulseUs) {
  ledcWrite(pin, pulseUsToDuty(pulseUs));
}

void setup() {
  Serial.begin(115200);
  delay(800);

  // Use external 5V supply for servos and connect all grounds together.
  if (!ledcAttach(PIN_RDS3115, SERVO_FREQ_HZ, LEDC_BITS)) {
    Serial.println("ERROR: ledcAttach failed on GPIO4");
    while (true) delay(1000);
  }
  if (!ledcAttach(PIN_DS3218, SERVO_FREQ_HZ, LEDC_BITS)) {
    Serial.println("ERROR: ledcAttach failed on GPIO5");
    while (true) delay(1000);
  }

  writeServoUs(PIN_RDS3115, 1500);
  writeServoUs(PIN_DS3218, 1500);
  delay(1000);

  Serial.println("Reciprocating test started.");
  Serial.println("RDS3115MG -> GPIO4, DS3218 -> GPIO5");
}

void loop() {
  Serial.println("RDS3115 sweep");
  for (int pulseUs = US_MIN; pulseUs <= US_MAX; pulseUs += STEP_US) {
    writeServoUs(PIN_RDS3115, pulseUs);
    delay(STEP_DELAY_MS);
  }
  delay(200);

  for (int pulseUs = US_MAX; pulseUs >= US_MIN; pulseUs -= STEP_US) {
    writeServoUs(PIN_RDS3115, pulseUs);
    delay(STEP_DELAY_MS);
  }
  delay(400);

  Serial.println("DS3218 sweep");
  for (int pulseUs = US_MIN; pulseUs <= US_MAX; pulseUs += STEP_US) {
    writeServoUs(PIN_DS3218, pulseUs);
    delay(STEP_DELAY_MS);
  }
  delay(200);

  for (int pulseUs = US_MAX; pulseUs >= US_MIN; pulseUs -= STEP_US) {
    writeServoUs(PIN_DS3218, pulseUs);
    delay(STEP_DELAY_MS);
  }
  delay(400);
}
