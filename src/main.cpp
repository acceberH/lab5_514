// #include <Arduino.h>
// #include <WiFi.h>
// #include <FirebaseClient.h>
// #include <WiFiClientSecure.h>

// // WiFi & Firebase 配置信息
// const char *ssid = "UW MPSK";
// const char *password = "ktEs67ktS.";
// #define DATABASE_SECRET "jdOiXI4pg89mGgLl1LxORqNrTl1EtbZAytWu17tU"
// #define DATABASE_URL "https://lab4-29771-default-rtdb.firebaseio.com/"

// // Firebase 相关对象
// WiFiClientSecure ssl;
// DefaultNetwork network;
// AsyncClientClass client(ssl, getNetwork(network));
// FirebaseApp app;
// RealtimeDatabase Database;
// AsyncResult result;
// LegacyToken dbSecret(DATABASE_SECRET);

// // 超声波传感器引脚
// #define TRIG_PIN 0
// #define ECHO_PIN 1

// // 计时变量
// unsigned long previousMillis = 0;
// const long wifiConnectTime = 30000;    // WiFi 连接 30 秒
// const long firebaseUploadTime = 30000; // Firebase 上传数据 30 秒
// const long ultrasonicTime = 12000;     // 仅超声波测距 12 秒
// const long idleTime = 12000;           // 空闲 12 秒
// const long deepSleepTime = 12000;      // 深度睡眠 12 秒

// // **提前声明 measureDistance()**
// float measureDistance();

// void setup()
// {
//   Serial.begin(115200);
//   pinMode(TRIG_PIN, OUTPUT);
//   pinMode(ECHO_PIN, INPUT);
//   Serial.println("Starting ESP32...");
// }

// void loop()
// {
//   unsigned long currentMillis = millis();

//   // **阶段 1：连接 WiFi（30 秒）**
//   previousMillis = currentMillis;
//   while (millis() - previousMillis < wifiConnectTime)
//   {
//     Serial.println("Connecting to WiFi...");
//     WiFi.begin(ssid, password);

//     int retry = 0;
//     while (WiFi.status() != WL_CONNECTED && retry < 10)
//     {
//       Serial.print(".");
//       delay(1000);
//       retry++;
//     }

//     if (WiFi.status() == WL_CONNECTED)
//     {
//       Serial.println("\nWiFi Connected!");
//       Serial.print("IP Address: ");
//       Serial.println(WiFi.localIP());
//     }
//     else
//     {
//       Serial.println("\nWiFi Connection FAILED!");
//     }
//   }

//   delay(100); // 小延时切换阶段

//   // **阶段 2：发送数据到 Firebase（30 秒）**
//   previousMillis = millis();
//   while (millis() - previousMillis < firebaseUploadTime)
//   {
//     Serial.println("Uploading data to Firebase...");

//     ssl.setInsecure();
//     initializeApp(client, app, getAuth(dbSecret));
//     app.getApp<RealtimeDatabase>(Database);
//     Database.url(DATABASE_URL);
//     client.setAsyncResult(result);

//     float distance = measureDistance(); // ✅ 现在 measureDistance() 可用了
//     bool status = Database.set<float>(client, "/sensor/distance", distance);
//     if (status)
//       Serial.println("Data uploaded to Firebase!");
//     else
//       Serial.println("Failed to upload data.");

//     delay(5000); // 每 5 秒上传一次数据
//   }

//   WiFi.disconnect(true); // true to disable auto-reconnect
//   WiFi.mode(WIFI_OFF);
//   Serial.println("WiFi Disconnected and turned OFF.");

//   delay(100);

//   // **阶段 3：超声波测距（12 秒）**
//   previousMillis = millis();
//   while (millis() - previousMillis < ultrasonicTime)
//   {
//     Serial.println("Measuring distance...");
//     float distance = measureDistance();
//     Serial.print("Measured Distance: ");
//     Serial.print(distance);
//     Serial.println(" cm");
//     delay(1000);
//   }

//   delay(100);

//   // **阶段 4：空闲（12 秒）**
//   previousMillis = millis();
//   while (millis() - previousMillis < idleTime)
//   {
//     Serial.println("Idle mode...");
//     delay(1000);
//   }

//   delay(100);

//   // **阶段 5：深度睡眠（12 秒）**
//   Serial.println("Entering Deep Sleep mode...");
//   esp_sleep_enable_timer_wakeup(deepSleepTime * 1000); // 12 秒后唤醒
//   esp_deep_sleep_start();
// }

// // **定义 measureDistance()**
// float measureDistance()
// {
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);

//   long duration = pulseIn(ECHO_PIN, HIGH);
//   return duration * 0.034 / 2; // 计算距离（单位：cm）
// }

// #include <Arduino.h>
// #include <WiFi.h>
// #include <FirebaseClient.h>
// #include <WiFiClientSecure.h>

// **WiFi & Firebase**
// const char *ssid = "UW MPSK";
// const char *password = "ktEs67ktS.";
// const char *ssid = "CenturyLink0590";
// const char *password = "7vx5an7pk6zb8p";
// #define DATABASE_SECRET "jdOiXI4pg89mGgLl1LxORqNrTl1EtbZAytWu17tU"
// #define DATABASE_URL "https://lab4-29771-default-rtdb.firebaseio.com"

// // **Firebase**
// WiFiClientSecure ssl;
// DefaultNetwork network;
// AsyncClientClass client(ssl, getNetwork(network));
// FirebaseApp app;
// RealtimeDatabase Database;
// AsyncResult result;
// LegacyToken dbSecret(DATABASE_SECRET);

// // pin
// #define TRIG_PIN 0
// #define ECHO_PIN 1

// // rate
// #define DATA_RATE 0.25 //  2、1、0.5、0.333、0.25

// unsigned long previousMillis = 0;
// const long interval = 1000 / DATA_RATE;

// // **measure distance**
// float measureDistance()
// {
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);

//   long duration = pulseIn(ECHO_PIN, HIGH);
//   return duration * 0.034 / 2;
// }

// // **WiFi connection**
// void connectWiFi()
// {
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi");
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(500);
//   }
//   Serial.println("\nConnected to WiFi!");
// }

// // **Firebase connection**
// void connectFirebase()
// {
//   ssl.setInsecure();
//   initializeApp(client, app, getAuth(dbSecret));
//   app.getApp<RealtimeDatabase>(Database);
//   Database.url(DATABASE_URL);
//   client.setAsyncResult(result);
// }

// void setup()
// {
//   Serial.begin(115200);
//   pinMode(TRIG_PIN, OUTPUT);
//   pinMode(ECHO_PIN, INPUT);

//   connectWiFi();
//   connectFirebase();
// }

// void loop()
// {
//   unsigned long currentMillis = millis();

//   if (currentMillis - previousMillis >= interval)
//   {
//     previousMillis = currentMillis;

//     float distance = measureDistance();
//     Serial.print("Distance: ");
//     Serial.print(distance);
//     Serial.println(" cm");

//     // send data to Firebase
//     bool status = Database.set<float>(client, "/sensor/distance", distance);
//     if (status)
//     {
//       Serial.println("Data uploaded to Firebase!");
//       Serial.println(currentMillis / 1000);
//     }
//     else
//     {
//       Serial.println("Failed to upload data.");
//     }
//   }
// }

#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

const char *ssid = "CenturyLink0590";
const char *password = "7vx5an7pk6zb8p";
#define DATABASE_SECRET "jdOiXI4pg89mGgLl1LxORqNrTl1EtbZAytWu17tU"
#define DATABASE_URL "https://lab4-29771-default-rtdb.firebaseio.com"

const int trigPin = D2;
const int echoPin = D3;

WiFiClientSecure ssl;
DefaultNetwork network;
AsyncClientClass client(ssl, getNetwork(network));
FirebaseApp app;
RealtimeDatabase Database;
AsyncResult result;
LegacyToken dbSecret(DATABASE_SECRET);

float lastDistance = 0.0;
const float distanceThreshold = 5.0;   // Threshold to trigger data upload (5cm change)
const float silentThreshold = 50.0;    // Silent mode threshold (object >50cm)
const int activeSleep = 30 * 1000000;  // Active mode sleep duration (30s, object detected)
const int silentSleep = 300 * 1000000; // Silent mode sleep duration (5min, no object)

void connectToWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
}

void setupFirebase()
{
  ssl.setInsecure();
  initializeApp(client, app, getAuth(dbSecret));
  app.getApp<RealtimeDatabase>(Database);
  Database.url(DATABASE_URL);
  client.setAsyncResult(result);
}

float measureDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void uploadToFirebase(float distance)
{
  String path = "/ultrasonic/distance";
  if (Database.set<float>(client, path, distance))
  {
    Serial.println("Data uploaded successfully!");
  }
  else
  {
    Serial.println("Data upload failed.");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  float distance = measureDistance();
  Serial.print("Measured Distance: ");
  Serial.println(distance);

  // Strategy 1: Adjust sleep time based on object presence
  uint64_t sleepTime = activeSleep; // Default: Active mode (30s)
  if (distance > silentThreshold)
  {
    sleepTime = silentSleep; // Silent mode (5min)
  }

  // Strategy 2: Upload data only if distance changes significantly
  if (abs(distance - lastDistance) > distanceThreshold)
  {
    connectToWiFi();
    setupFirebase();
    uploadToFirebase(distance);
    lastDistance = distance;
    WiFi.disconnect(true); // Disconnect WiFi immediately after upload
  }

  // Enter deep sleep (original logic preserved)
  esp_deep_sleep(sleepTime);
}