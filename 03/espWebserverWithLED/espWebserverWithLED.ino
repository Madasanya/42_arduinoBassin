#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "test";
const char* password = "test_pw-test";

#define PIN 4            // GPIO4 (D2)
#define NUMPIXELS 64     // 8x8 matrix

ESP8266WebServer server(80);
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool pixels[8][8] = {false}; // LED state map


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("Connected. IP:");
  Serial.println(WiFi.localIP());

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/reset", handleReset);
  server.on("/animate", handleAnimate);
  server.begin();
}

int getIndex(int x, int y) {
  return (y % 2 == 0) ? y * 8 + x : y * 8 + (7 - x);
}

void handleRoot() {
  String page = "<html><head><style>";
  page += "button{width:30px;height:30px;margin:1px;}";
  page += "</style></head><body><h2>LED Matrix</h2>";
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      String color = pixels[y][x] ? "#0f0" : "#333";
      page += "<button style='background:" + color + "' ";
      page += "<button style='background:" + color + "' ";
      page += "onclick=\"location.href='/toggle?x=" + String(x) + "&y=" + String(y) + "'\">";
      page += "</button>";

    }
    page += "<br>";
  }
  page += "<button onclick=\"location.href='/reset'\" style='width:100px;height:50px;margin-bottom:10px;padding:5px 10px;'>Reset Matrix</button><br>";
  page += "<button onclick=\"location.href='/animate'\" style='width:100px;height:50px;margin:5px;padding:5px 10px;'>Run Animation</button><br><br>";
  page += "</body></html>";
  server.send(200, "text/html", page);
}

void handleToggle() {
  if (!server.hasArg("x") || !server.hasArg("y")) {
    server.send(400, "text/plain", "Missing x or y");
    return;
  }
  int x = server.arg("x").toInt();
  int y = server.arg("y").toInt();
  if (x < 0 || x >= 8 || y < 0 || y >= 8) {
    server.send(400, "text/plain", "Invalid coordinates");
    return;
  }

  pixels[y][x] = !pixels[y][x]; // Toggle state
  int idx = getIndex(x, y);
  if (pixels[y][x]) {
    strip.setPixelColor(idx, strip.Color(0, 255, 0)); // ON = green
  } else {
    strip.setPixelColor(idx, 0); // OFF
  }
  strip.show();
  handleRoot(); // refresh page
}

void handleReset() {
  // Clear pixel states
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      pixels[y][x] = false;
      int idx = getIndex(x, y);
      strip.setPixelColor(idx, 0); // Turn off LED
    }
  }
  strip.show();

  // Redirect back to main page
  server.sendHeader("Location", "/");
  server.send(303);  // 303 See Other for redirect
}

void handleAnimate() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.clear();
    uint32_t color = strip.Color(random(100, 255), random(100, 255), random(100, 255));
    strip.setPixelColor(i, color);
    strip.show();
    delay(100);
  }

  // After animation, clear everything
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();

  // Redirect back to the main page
  server.sendHeader("Location", "/");
  server.send(303);
}


void loop() {
  server.handleClient();
}
