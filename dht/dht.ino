#include "DHT.h"
#include "WiFi.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "$_NAME_OF_WIFI_NETWORK";
const char* password =  "$_WIFI_PASSWORD";

void setup() {
  Serial.begin(9600);

  /*-------------------------------------------------WIFI Initializing --------------------------------------------------*/
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  if (WiFi.status() == WL_CONNECTED){
    digitalWrite(2, HIGH);
    delay(10000);
    digitalWrite(2, LOW);
    }
    /*-------------------------------------------------DHT Initializing --------------------------------------------------*/
  Serial.println(F("DHT11 test!"));
  dht.begin();
  Serial.println("  Done.");
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
/*------------------------------------------------- initializing temp,hemudity veriables -------------------------------*/
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
/* ------------------------------------------------------- checking temp,hemudity through DHT11 ------------------------------*/
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

    
}
