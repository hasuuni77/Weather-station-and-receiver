# Väderstation & Mottagarserver – ESP8266-projekt

Detta projekt är skapat av **Hassan, Hussein, Mohamed och Liban** som en IoT-lösning där en väderstation sänder sensordata via WiFi till en mottagarenhet med LCD-display.

## Funktion

Projektet består av två enheter:

1. **Sändare (väderstation)**  
   - Läser av:
     - Temperatur och luftfuktighet via DHT11
     - Ljusnivå via LDR
   - Skickar data i JSON-format via WiFi till en specifik IP/port.

2. **Mottagare (server/LCD-enhet)**  
   - Tar emot JSON-data via en TCP-server.
   - Visar:
     - Temperatur
     - Luftfuktighet
     - Ljusnivå (i %)
     - Uppmätt tid (sekunder sedan start)
   - Allt presenteras på en I2C LCD-skärm (16x2).

## Hårdvarukrav

### Sändare:
- ESP8266 (t.ex. NodeMCU)
- DHT11-sensor (kopplad till GPIO2)
- LDR + spänningsdelare (kopplad till A0)
- WiFi-anslutning

### Mottagare:
- ESP8266 (t.ex. NodeMCU)
- I2C LCD-skärm (adress: 0x27)
- WiFi-anslutning

## Bibliotek som krävs

- ESP8266WiFi
- DHT
- LiquidCrystal_I2C
- ArduinoJson

## Användning

1. Uppdatera båda koderna med ert WiFi-namn och lösenord.
2. Uppdatera IP-adressen till mottagaren i sändarkoden.
3. Ladda upp koderna till respektive ESP8266-enhet.
4. Öppna Serial Monitor och kontrollera att allt fungerar.

## Projektteam

**Hassan, Hussein, Mohamed, Liban**

## Licens

MIT-licens
