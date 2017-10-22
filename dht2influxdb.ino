#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266Influxdb.h>

#include <DHT.h>

// Report interval
const int sleepTime = 10000;

// WiFi details
const char* ssid = "Hindenburg";
const char* password = "*******";

// InfluxDB details
const char* influxHost = "insert.hostname.or.ip.here";
const char* influxDatabase = "templogger";

// DHT sensor details
const short dhtPin = 0; // Wemos pin D3 (10K pull-up)
const short dhtType = 21;

// Sensor location
const char* sensorLocation = "bedroom";

// InfluxDB client object
Influxdb influxdb(influxHost, 80);

// DHT client object
DHT dht(dhtPin, dhtType);

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  // Open InflxuDB database
  influxdb.opendb(influxDatabase);
}

void loop() {
  // Collect measurements
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Unable to read the DHT sensor!");

    delay(1000); return;
  } else {
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(", Humidity: ");
    Serial.print(h);
    Serial.println();
  }

  // Calculate head index
  float hic = dht.computeHeatIndex(t, h, false);

  // Create object to send to InfluxDB
  FIELD dataObj("dht_read");
  dataObj.addTag("location", sensorLocation);
  dataObj.addField("t", t);
  dataObj.addField("h", h);
  dataObj.addField("hic", hic);

  // Send data to InfluxDB
  if (influxdb.write(dataObj) == DB_SUCCESS) {
    Serial.println("Written data to InfluxDB");
  } else {
    Serial.println("Failed to write data to InfluxDB!");
  }

  // Clear data object
  dataObj.empty();

  // Sleep until we need to collect again
  delay(sleepTime);
}

