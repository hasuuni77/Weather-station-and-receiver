#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

const char* ssid = "Ditt_WiFi_Namn";
const char* password = "Ditt_WiFi_Lösenord";

const int serverPort = 8080;
WiFiServer server(serverPort);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  
  Serial.print("Ansluter till WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi ansluten!");
  Serial.print("IP-adress: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Klient ansluten.");

    String jsonData = "";
    while (client.available()) {
      jsonData += (char)client.read();
    }

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonData);
    if (error) {
      Serial.println("Fel vid JSON-parsning.");
      return;
    }

    float temperature = doc["temperature"];
    float humidity = doc["humidity"];
    int lightLevel = doc["light_level"];
    int lightPercentage = map(lightLevel, 0, 1023, 0, 100);
    unsigned long timestamp = millis() / 1000;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: " + String(temperature, 1) + "C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: " + String(humidity, 1) + "%");
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Light: " + String(lightPercentage) + "%");
    lcd.setCursor(0, 1);
    lcd.print("Time: " + String(timestamp) + "s");
    delay(2000);
  }
}
