#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Wi-Fi credentials
const char* ssid = "ESP32_Sensor";
const char* password = "12345678";

// TDS sensor configuration
const int tdsPin = 34;  // Pin where the TDS sensor is connected
const int numSamples = 10;  // Number of samples for averaging
const float tdsFactor = 0.5;  // Factor to convert voltage to TDS (ppm)
const float aref = 3.3;  // Reference voltage for the ESP32
const int adcRange = 4095;  // ADC resolution of the ESP32 (12 bits)

// DS18B20 temperature sensor configuration
const int oneWireBus = 13;  // Pin where the DS18B20 is connected (GPIO13, D13)
OneWire oneWire(oneWireBus);  // OneWire instance to communicate with DS18B20
DallasTemperature sensors(&oneWire);  // Pass OneWire reference to Dallas Temperature

WiFiServer server(80);  // Create a server on port 80 (HTTP)

void setup() {
  Serial.begin(115200);
  
  // Start DS18B20 sensor
  sensors.begin();
  
  // Set up Wi-Fi Access Point
  WiFi.softAP(ssid, password);

  // Start the server
  server.begin();

  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // Print IP address of the ESP32
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {  // If a client is connected
    Serial.println("New Client Connected");

    // Read the request from the client
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        currentLine += c;

        // Check if the client request is for sensor data
        if (currentLine.endsWith("GET /data")) {
          // Collect sensor readings
          float totalVoltage = 0;
          for (int i = 0; i < numSamples; i++) {
            int analogValue = analogRead(tdsPin);  // Read the analog value from TDS sensor
            float voltage = analogValue * (aref / adcRange);  // Convert ADC value to voltage
            totalVoltage += voltage;
            delay(100);
          }
          float averageVoltage = totalVoltage / numSamples;
          float tdsValue = (averageVoltage * tdsFactor) * 1000;

          // Read temperature from DS18B20
          sensors.requestTemperatures();
          float temperatureC = sensors.getTempCByIndex(0);

          // Send the sensor data in JSON format
          String jsonData = "{\"voltage\":" + String(averageVoltage) + 
                            ", \"tds\":" + String(tdsValue) + 
                            ", \"temperature\":" + String(temperatureC) + "}";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");
          client.println();
          client.println(jsonData);
          break;
        }

        // Serve the HTML page if requested
        if (currentLine.endsWith("GET / ")) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          // Send the HTML page content
          client.println("<!DOCTYPE html><html>");
          client.println("<head><title>Riverpulse Sensor Data</title>");
          client.println("<script>");
          client.println("function loadData() {");
          client.println("var xhttp = new XMLHttpRequest();");
          client.println("xhttp.onreadystatechange = function() {");
          client.println("if (this.readyState == 4 && this.status == 200) {");
          client.println("var data = JSON.parse(this.responseText);");
          client.println("document.getElementById('voltage').innerHTML = data.voltage;");
          client.println("document.getElementById('tds').innerHTML = data.tds;");
          client.println("document.getElementById('temperature').innerHTML = data.temperature;");
          client.println("}};");
          client.println("xhttp.open('GET', '/data', true);");
          client.println("xhttp.send();");
          client.println("}");
          client.println("setInterval(loadData, 1000);");  // Update every second
          client.println("</script>");
          client.println("</head>");
          client.println("<body><h1>RiverPulse Sensor Data</h1>");
          client.println("<p>Average Voltage: <span id='voltage'></span> V</p>");
          client.println("<p>TDS Value: <span id='tds'></span> ppm</p>");
          client.println("<p>Temperature: <span id='temperature'></span> &#8451;</p>");
          client.println("</body></html>");

          client.println();
          break;
        }
      }
    }

    // Clear the currentLine variable for the next client
    currentLine = "";
    client.stop();
    Serial.println("Client Disconnected");
  }