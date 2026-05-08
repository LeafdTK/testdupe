#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define WIFI_SSID  " "
#define WIFI_PASS  " "

static AsyncWebServer srv(80);

enum class Endpoint : uint8_t { ROOT, SYSTEM };

static size_t buildPayload(Endpoint ep, char* buf, size_t n) {
  switch (ep) {
    case Endpoint::ROOT:
      return snprintf(buf, n,
        "{\n"
        "  \"status\": \"online\",\n"
        "  \"device\": \"Qein X1A Pro S3\",\n"
        "  \"message\": \"System is operational!\"\n"
        "}");
    case Endpoint::SYSTEM: {
      uint32_t f = ESP.getFlashChipSize() / (1U << 20);
      uint32_t p = ESP.getPsramSize()    / (1U << 20);
      uint32_t u = millis() / 1000U;
      return snprintf(buf, n,
        "{\n"
        "  \"chip\": \"ESP32-S3\",\n"
        "  \"flash_mb\": %u,\n"
        "  \"psram_mb\": %u,\n"
        "  \"uptime_seconds\": %u\n"
        "}", f, p, u);
    }
  }
  return 0;
}

static void send(AsyncWebServerRequest* req, int code, const char* body) {
  req->send(code, "application/json", body);
}

static void wifiBlockUntilUp() {
  Serial.printf("Connecting to Wi-Fi: %s ", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  do { delay(500); Serial.print('.'); } while (WiFi.status() != WL_CONNECTED);
  Serial.println("\nWi-Fi Connected!");
  Serial.printf("API is hosted at: http://%s\n", WiFi.localIP().toString().c_str());
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("starting..");

  wifiBlockUntilUp();

  srv.on("/", HTTP_GET, [](AsyncWebServerRequest* r) {
    char buf[160];
    buildPayload(Endpoint::ROOT, buf, sizeof(buf));
    send(r, 200, buf);
  });

  srv.on("/system", HTTP_GET, [](AsyncWebServerRequest* r) {
    char buf[192];
    buildPayload(Endpoint::SYSTEM, buf, sizeof(buf));
    send(r, 200, buf);
  });

  srv.onNotFound([](AsyncWebServerRequest* r) {
    send(r, 404, "{ \"error\": \"404\", \"message\": \"Endpoint not found\" }");
  });

  srv.begin();
  Serial.println("HTTP Server started.");
  Serial.println("=========================================\n");
}

void loop() { /* async server has no polling */ }
