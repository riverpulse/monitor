#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPIFFS.h>
#include <time.h>

// WiFi credentials
const char* ssid = "Test";
const char* password = "12348765";

// NTP server details
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;     // Adjust according to your timezone
const int daylightOffset_sec = 0; // Adjust for daylight savings

// TDS sensor configuration
const int tdsPin = 34;          // Pin where the TDS sensor is connected
const int numSamples = 10;      // Number of samples for averaging
const float tdsFactor = 0.5;    // Factor to convert voltage to TDS (ppm)
const float aref = 3.3;         // Reference voltage for the ESP32
const int adcRange = 4095;      // ADC resolution of the ESP32 (12 bits)
const float temperatureCoefficient = 0.02;  // 2% per degree Celsius

// DS18B20 temperature sensor configuration
const int oneWireBus = 13;  // Pin where the DS18B20 is connected (GPIO13, D13)

OneWire oneWire(oneWireBus);              // Set up a OneWire instance to communicate with DS18B20
DallasTemperature sensors(&oneWire);      // Pass OneWire reference to Dallas Temperature

// Global variables
int data_id = 1;                         // Initialize data ID
const char* device_id = "Device001";
const char* xrpl_wallet = "rYourXRPWalletAddress";
const char* gps_coordinates = "40.7128 N, 74.0060 W";  // Hardcoded coordinates
const char* additional_data = "";        // Additional data if any

bool NTP_sync = false;                   // Flag to indicate if timestamp is synchronized
wl_status_t prevWiFiStatus = WL_DISCONNECTED; // Variable to store previous WiFi status

void setup() {
  Serial.begin(115200);                    // Start serial communication
  sensors.begin();                         // Start the DS18B20 sensor
  analogSetPinAttenuation(tdsPin, ADC_11db);  // Configure ADC attenuation for tdsPin

  // Initialize SPIFFS and format it (erase all previous data)
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS initialized and formatted.");

  // Initialize WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  // Set the time to a default value (e.g., 2000-01-01 00:00:00)
  time_t now = 946684800; // Epoch time for 2000-01-01 00:00:00
  struct timeval tv = { now, 0 };
  settimeofday(&tv, NULL);
}

void loop() {
  // Get the current WiFi status
  wl_status_t currentWiFiStatus = WiFi.status();

  // Check for changes in WiFi connection status
  if (currentWiFiStatus != prevWiFiStatus) {
    if (currentWiFiStatus == WL_CONNECTED) {
      Serial.println("\nConnected to WiFi.");
      // Attempt to synchronize time with NTP
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      struct tm timeinfo;
      if (getLocalTime(&timeinfo)) {
        Serial.println("Time synchronized with NTP.");
        NTP_sync = true;
      } else {
        Serial.println("Failed to obtain NTP time.");
        NTP_sync = false;
      }
    } else {
      Serial.println("WiFi Disconnected");
      // NTP_sync remains unchanged as time remains valid until reset
    }
  }

  // Update previous WiFi status
  prevWiFiStatus = currentWiFiStatus;

  float totalVoltage = 0;  // Variable to store the sum of the voltages
  
  // Take multiple TDS readings and calculate the average voltage
  for (int i = 0; i < numSamples; i++) {
    int analogValue = analogRead(tdsPin);  // Read the analog value from the TDS sensor
    float voltage = analogValue * (aref / adcRange);  // Convert ADC value to voltage
    totalVoltage += voltage;  // Add the voltage to the total sum
    delay(100);  // Wait 100ms between readings
  }
  
  float averageVoltage = totalVoltage / numSamples;  // Calculate the average voltage

  // Read temperature from DS18B20 sensor
  sensors.requestTemperatures();  // Send the command to get temperatures
  float temperatureC = sensors.getTempCByIndex(0);

  // Check if temperature reading is valid
  if (temperatureC == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: Temperature sensor disconnected");
    return;  // Skip the rest of the loop if temperature reading fails
  }

  // Apply temperature compensation
  float compensationCoefficient = 1.0 + temperatureCoefficient * (temperatureC - 25.0);
  float compensatedVoltage = averageVoltage / compensationCoefficient;

  // Calculate TDS in ppm using the compensated voltage
  float tdsValue = (compensatedVoltage * tdsFactor) * 1000;  // Multiply by 1000 to convert to ppm

  // Get current time
  time_t now = time(NULL);
  struct tm timeinfo;
  localtime_r(&now, &timeinfo);


  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

  // Build JSON string manually
  String jsonString = "{";
  jsonString += "\"data_id\":";
  jsonString += String(data_id);
  jsonString += ",\"timestamp\":\"";
  jsonString += String(timestamp);
  jsonString += "\",\"NTP_sync\":";
  jsonString += NTP_sync ? "true" : "false";
  jsonString += ",\"device_id\":\"";
  jsonString += String(device_id);
  jsonString += "\",\"xrpl_wallet\":\"";
  jsonString += String(xrpl_wallet);
  jsonString += "\",\"gps_coordinates\":\"";
  jsonString += String(gps_coordinates);
  jsonString += "\",\"temperature\":";
  jsonString += String(temperatureC);
  jsonString += ",\"tds_value\":";
  jsonString += String(tdsValue);
  jsonString += ",\"additional_data\":\"";
  jsonString += String(additional_data);
  jsonString += "\"}";

  // Append the JSON string to a file in SPIFFS
  File file = SPIFFS.open("/data.txt", FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
  } else {
    file.println(jsonString);
    file.close();
  }

  // Display the entry on the Serial Monitor
  Serial.println(jsonString);

  // Increment data_id
  data_id++;

  delay(10000);  // Wait 1 second before taking the next reading
}
