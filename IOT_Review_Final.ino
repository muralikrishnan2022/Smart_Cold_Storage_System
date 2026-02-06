#define BLYNK_TEMPLATE_ID "TMPL3RdpX7u9J"
#define BLYNK_TEMPLATE_NAME "Smart Cold Storage"
#define BLYNK_AUTH_TOKEN "bKzHUdwHeS3nwM2IhVDrq1OCIoUxK6tS"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ==================== WiFi Credentials ====================
char ssid[] = "MURALI";       // your WiFi SSID
char pass[] = "MURALIKRISHNAN";       // your WiFi password

// ==================== DHT CONFIG ====================
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ==================== LCD CONFIG ====================
LiquidCrystal_I2C lcd(0x27, 20, 4);

// ==================== MOTOR (FAN/PELTIER) CONFIG ====================
#define IN3 32
#define IN4 33
#define ENB 18
float setTemp = 22.0;  // Default threshold temperature

// ==================== BUZZER CONFIG ====================
#define BUZZER_PIN 25   // Signal pin for buzzer (3-pin buzzer OUT pin)

// ==================== Blynk Virtual Pins ====================
// V2 -> Temperature Display
// V3 -> Humidity Display
// V4 -> Set Temperature (Slider)
// V6 -> Cooling ON/OFF LED
// V7 -> Alarm LED (High Temp Alert)

// ==================== BLYNK SLIDER CONTROL ====================
BLYNK_WRITE(V4) {
  setTemp = param.asFloat(); // Update set temperature from Blynk slider
  Serial.print("📱 Set Temp updated from Blynk: ");
  Serial.print(setTemp);
  Serial.println(" °C");
}

// ==================== SETUP ====================
void setup() {
  Serial.begin(115200);
  Serial.println("Smart Cold Storage System Starting...");

  // Initialize components
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize states
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi...");

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cold Storage Ready");
  delay(2000);
}

// ==================== MAIN LOOP ====================
void loop() {
  Blynk.run();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(" DHT11 Sensor Error!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  // Display on Serial
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C |  Hum: ");
  Serial.print(humidity);
  Serial.print(" % | Target: ");
  Serial.println(setTemp);

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C  S:");
  lcd.print(setTemp, 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity, 1);
  lcd.print("%");

  // Send data to Blynk
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);

  // Cooling + Alarm + Buzzer control
  if (temperature >= setTemp) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 255);
    Serial.println("Cooling ON");
    lcd.setCursor(0, 2);
    lcd.print("Cooling: ON ");
    Blynk.virtualWrite(V6, 1);

    // 🔴 Turn ON Alarm LED + Buzzer
    Blynk.virtualWrite(V7, 255);
    lcd.setCursor(0, 3);
    lcd.print(" ALERT: HIGH TEMP!");
    digitalWrite(BUZZER_PIN, LOW); 
     
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    Serial.println(" Cooling OFF");
    lcd.setCursor(0, 2);
    lcd.print("Cooling: OFF");
    Blynk.virtualWrite(V6, 0);

    // 🟢 Turn OFF Alarm LED + Buzzer
    Blynk.virtualWrite(V7, 0);
    lcd.setCursor(0, 3);
    lcd.print("Temp Normal   ");
    digitalWrite(BUZZER_PIN, HIGH); 
      

  delay(2000);
}
}
