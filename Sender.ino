#include <DHT.h>
#include <ESP8266WiFi.h>

// DHT11-inställningar
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LDR-inställningar
#define LDRPIN A0

// WiFi-inställningar
const char* ssid = "Ditt_WiFi_Namn";
const char* password = "Ditt_WiFi_Lösenord";

// Serverinställningar
const char* serverIP = "192.168.1.100"; // Exempel: Serverns IP
const int serverPort = 8080;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.print("Ansluter till WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi ansluten!");
  Serial.print("IP-adress: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int lightLevel = analogRead(LDRPIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Kunde inte läsa från DHT-sensorn.");
    return;
  }

  String jsonData = "{";
  jsonData += "\"temperature\": " + String(temperature, 1) + ",";
  jsonData += "\"humidity\": " + String(humidity, 1) + ",";
  jsonData += "\"light_level\": " + String(lightLevel);
  jsonData += "}";

  if (client.connect(serverIP, serverPort)) {
    Serial.println("Ansluten till servern. Skickar data...");
    client.println("POST /data HTTP/1.1");
    client.println("Host: " + String(serverIP));
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(jsonData.length());
    client.println();
    client.println(jsonData);
    client.stop();
    Serial.println("Data skickades: " + jsonData);
  } else {
    Serial.println("Kunde inte ansluta till servern.");
  }

  delay(5000);
}
