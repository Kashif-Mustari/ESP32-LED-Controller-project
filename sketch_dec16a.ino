#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Max Unity";
const char* password = "@01234567";

const int ledPin = 2;
bool ledState = false;

WebServer server(80);

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 20) {
      Serial.println("\nWiFi Failed!");
      return;
    }
  }

  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);

  server.begin();
  Serial.println("HTTP Server Started");
}

// ---------- LOOP ----------
void loop() {
  server.handleClient();
}

// ---------- WEB PAGE ----------
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 LED Control</title>

<style>
* {
  box-sizing: border-box;
}

body {
  margin: 0;
  height: 100vh;
  font-family: 'Segoe UI', Arial, sans-serif;
  background: linear-gradient(135deg, #667eea, #764ba2);
  display: flex;
  align-items: center;
  justify-content: center;
}

.card {
  background: rgba(255, 255, 255, 0.18);
  backdrop-filter: blur(12px);
  border-radius: 20px;
  padding: 30px 25px;
  width: 90%;
  max-width: 380px;
  text-align: center;
  color: white;
  box-shadow: 0 8px 32px rgba(0,0,0,0.25);
}

h1 {
  margin-top: 0;
  font-size: 26px;
  letter-spacing: 1px;
}

.status {
  margin: 20px 0;
  font-size: 18px;
}

.badge {
  display: inline-block;
  padding: 6px 18px;
  border-radius: 50px;
  font-weight: bold;
}

.badge.on {
  background: #2ecc71;
}

.badge.off {
  background: #e74c3c;
}

button {
  width: 100%;
  padding: 18px;
  margin-top: 25px;
  font-size: 22px;
  font-weight: bold;
  border: none;
  border-radius: 14px;
  color: white;
  cursor: pointer;
  transition: transform 0.15s ease, box-shadow 0.15s ease;
}

button.on {
  background: linear-gradient(135deg, #ff416c, #ff4b2b);
}

button.off {
  background: linear-gradient(135deg, #00c6ff, #0072ff);
}

button:active {
  transform: scale(0.97);
  box-shadow: 0 4px 12px rgba(0,0,0,0.3);
}

.footer {
  margin-top: 20px;
  font-size: 13px;
  opacity: 0.8;
}
</style>
</head>

<body>

<div class="card">
  <h1>ESP32 LED Controller</h1>

  <div class="status">
    Status:
    <span id="status" class="badge">--</span>
  </div>

  <button id="btn" onclick="toggleLED()">Loading...</button>

  <div class="footer">
    Control via WiFi
  </div>
</div>

<script>
function updateUI(state) {
  const btn = document.getElementById("btn");
  const status = document.getElementById("status");

  if (state === "ON") {
    status.innerText = "ON";
    status.className = "badge on";
    btn.innerText = "TURN OFF";
    btn.className = "on";
  } else {
    status.innerText = "OFF";
    status.className = "badge off";
    btn.innerText = "TURN ON";
    btn.className = "off";
  }
}

function toggleLED() {
  fetch("/toggle")
    .then(() => loadStatus());
}

function loadStatus() {
  fetch("/status")
    .then(res => res.text())
    .then(state => updateUI(state));
}

loadStatus();
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}


// ---------- TOGGLE ----------
void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  Serial.println(ledState ? "LED ON" : "LED OFF");
  server.send(200, "text/plain", "OK");
}

// ---------- STATUS ----------
void handleStatus() {
  server.send(200, "text/plain", ledState ? "ON" : "OFF");
}