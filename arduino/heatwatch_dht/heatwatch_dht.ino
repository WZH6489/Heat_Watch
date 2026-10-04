// HeatWatch sensor sketch
// Reads a DHT11 once per second and prints one JSON line per reading:
//   {"t":24.0,"h":45.0,"ms":12345}
// If the sensor stops answering, prints {"error":"sensor_timeout"} every 10 s.
// Requires the Elegoo "DHT_nonblocking" library (dht_nonblocking.h).

#include "dht_nonblocking.h"

#define DHT_SENSOR_TYPE DHT_TYPE_11   // change to DHT_TYPE_22 for a DHT22

static const int DHT_SENSOR_PIN = 2;
static const unsigned long BAUD_RATE           = 9600;   // pick the same rate in the dashboard
static const unsigned long MEASURE_INTERVAL_MS = 1000ul; // DHT11 max ~1 Hz; use 2000ul for a DHT22
static const unsigned long STALE_AFTER_MS      = 10000ul;

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
  Serial.begin(BAUD_RATE);
}

static bool measure_environment(float *temperature, float *humidity) {
  static unsigned long measurement_timestamp = millis();
  if (millis() - measurement_timestamp > MEASURE_INTERVAL_MS) {
    if (dht_sensor.measure(temperature, humidity)) {
      measurement_timestamp = millis();
      return true;
    }
  }
  return false;
}

void loop() {
  static unsigned long lastGood = millis();
  static unsigned long lastErr  = 0;
  float t, h;

  if (measure_environment(&t, &h)) {
    lastGood = millis();
    Serial.print(F("{\"t\":"));  Serial.print(t, 1);
    Serial.print(F(",\"h\":"));  Serial.print(h, 1);
    Serial.print(F(",\"ms\":")); Serial.print(millis());
    Serial.println(F("}"));
  } else if (millis() - lastGood > STALE_AFTER_MS &&
             millis() - lastErr  > STALE_AFTER_MS) {
    lastErr = millis();
    Serial.println(F("{\"error\":\"sensor_timeout\"}"));
  }
}
