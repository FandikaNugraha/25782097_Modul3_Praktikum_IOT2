#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Ganti dengan SSID dan Password Hotspot Anda
const char* ssid = "TECNO POVA 5";
const char* password = "Fandik11";

ESP8266WebServer server(80);

const byte ldrPin = A0;

// Kerangka HTML dengan Meta Refresh setiap 5 detik
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="refresh" content="5">
  <title>IoT Dashboard LDR</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; background-color: #f4f4f9; }
    h1 { color: #333; }
    .sensor-box { font-size: 24px; color: #0275d8; background: #fff; display: inline-block; padding: 20px; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); }
  </style>
</head>
<body>
  <h1>Dashboard Praktikum IoT</h1>
  <div class="sensor-box">
    <p>Nilai Sensor LDR: <strong>%LDR_VAL%</strong></p>
  </div>
</body>
</html>
)rawliteral";

void handleRoot() {
  int ldrValue = analogRead(ldrPin);
  
  String s = index_html;
  s.replace("%LDR_VAL%", String(ldrValue));
  
  server.send(200, "text/html", s);
}

void setup() {
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Koneksi Wi-Fi Berhasil!");
  Serial.print("Alamat IP Web Server: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server telah aktif");
}

void loop() {
  server.handleClient();
}
