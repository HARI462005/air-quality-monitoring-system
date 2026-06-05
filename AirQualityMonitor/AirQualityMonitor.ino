#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>

// ================= WIFI =================
const char* ssid = "IOT";
const char* password = "7693853647";

// ================= FIREBASE =================
#define API_KEY "AIzaSyClOp1PivNudD7aFK1ihk1LRWmXPTURZRU"

#define DATABASE_URL "https://air-quality-monitoring-s-3fc81-default-rtdb.firebaseio.com/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK  18
#define OLED_DC   2
#define OLED_CS   5
#define OLED_RESET 4

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  OLED_MOSI,
  OLED_CLK,
  OLED_DC,
  OLED_RESET,
  OLED_CS
);

// ================= DHT11 =================
#define DHTPIN 15
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ================= MQ Sensors =================
#define MQ135_PIN 34
#define MQ7_PIN   35
#define MQ5_PIN   32

// ================= OUTPUT =================
#define LED1 19
#define LED2 21
#define BUZZER 22

void setup()
{
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();

  // OLED START
  display.begin(SSD1306_SWITCHCAPVCC);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(20,20);
  display.println("START");
  display.display();

  // ================= WIFI CONNECT =================

  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi Connected");

  // ================= FIREBASE CONFIG =================

  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);

  delay(2000);
}

void loop()
{
  // ================= SENSOR READ =================

  int mq135 = analogRead(MQ135_PIN);

  int mq7 = analogRead(MQ7_PIN);

  int mq5 = analogRead(MQ5_PIN);

  float temp = dht.readTemperature();

  float humidity = dht.readHumidity();

  // ================= STATUS =================

  String status = "SAFE";

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(BUZZER, LOW);

  // SAFE

  if(temp >= 0 && temp <= 34 &&
     mq135 < 1200 &&
     mq7 < 1200 &&
     mq5 < 1200)
  {
    status = "SAFE";
  }

  // WARNING

  else if((temp >= 35 && temp <= 40) ||
          (mq135 >= 1200 && mq135 <= 2500) ||
          (mq7 >= 1200 && mq7 <= 2500) ||
          (mq5 >= 1200 && mq5 <= 2500))
  {
    status = "WARNING";

    digitalWrite(LED1, HIGH);

    digitalWrite(BUZZER, HIGH);
    delay(200);

    digitalWrite(BUZZER, LOW);
    delay(1000);
  }

  // DANGER

  else
  {
    status = "DANGER";

    digitalWrite(LED2, HIGH);

    digitalWrite(BUZZER, HIGH);
  }

  // ================= SERIAL MONITOR =================

  Serial.println("------ DATA ------");

  Serial.print("Temperature: ");
  Serial.println(temp);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("MQ135: ");
  Serial.println(mq135);

  Serial.print("MQ7: ");
  Serial.println(mq7);

  Serial.print("MQ5: ");
  Serial.println(mq5);

  Serial.print("Status: ");
  Serial.println(status);

  // ================= FIREBASE UPLOAD =================

  Firebase.RTDB.setFloat(&fbdo, "/AirQuality/Temperature", temp);

  Firebase.RTDB.setFloat(&fbdo, "/AirQuality/Humidity", humidity);

  Firebase.RTDB.setInt(&fbdo, "/AirQuality/MQ135", mq135);

  Firebase.RTDB.setInt(&fbdo, "/AirQuality/MQ7", mq7);

  Firebase.RTDB.setInt(&fbdo, "/AirQuality/MQ5", mq5);

  Firebase.RTDB.setString(&fbdo, "/AirQuality/Status", status);

  // ================= OLED DISPLAY =================

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("AIR QUALITY");

  display.setCursor(0,10);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.setCursor(0,20);
  display.print("Hum: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0,30);
  display.print("MQ135: ");
  display.println(mq135);

  display.setCursor(0,40);
  display.print("MQ7: ");
  display.println(mq7);

  display.setCursor(0,50);
  display.print("MQ5: ");
  display.println(mq5);

  display.display();

  delay(2000);
}
