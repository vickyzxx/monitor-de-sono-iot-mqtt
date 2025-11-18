#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h> 
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// CONFIGURAÇÕES DE REDE E MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;

// DEFINIÇÃO DE PINOS
const int PIN_R = 27; 
const int PIN_G = 26; 
const int PIN_B = 25;  
const int PIN_POT = 34; 

// TÓPICOS MQTT
const char* topic_bpm = "sono/frequencia_cardiaca";
const char* topic_spo2 = "sono/spo2";
const char* topic_mov = "sono/movimento";
const char* topic_estado = "sono/estado";
const char* topic_cmd_led = "sono/comando_led";
const char* topic_time_report = "medidas/response_time";

unsigned long lastPublish = 0;
const unsigned long publishInterval = 1000;

// -------------------- FUNÇÕES AUXILIARES --------------------

void setLEDColor(int r, int g, int b) {
  digitalWrite(PIN_R, r > 0 ? LOW : HIGH);
  digitalWrite(PIN_G, g > 0 ? LOW : HIGH);
  digitalWrite(PIN_B, b > 0 ? LOW : HIGH);
}

int calcularNivelMovimento() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calcula a magnitude da aceleração (m/s²)
  float magnitude = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z
  );

  // Movimento é a diferença absoluta em relação à gravidade (9.81 m/s²)
  float movimentoBase = abs(magnitude - 9.81);

  // Mapeia o movimento para 0–100% (usando float para melhor precisão)
  float nivelMovFloat = (movimentoBase / 2.0) * 100.0;

  // Converte para int após calcular
  int nivelMov = (int)nivelMovFloat;

  // Limita entre 0 e 100
  if (nivelMov < 0) nivelMov = 0;
  if (nivelMov > 100) nivelMov = 100;

  return nivelMov;
}


String classificarEstado(int bpm, int mov, int spo2) {
  if (spo2 < 90) return "despertar";
  if (bpm < 45 || bpm > 100) return "despertar";
  if (mov > 60) return "despertar";

  if (bpm >= 80) return "agitado";
  if (mov > 30) return "agitado";

  return "estavel";
}

// -------------------- CALLBACK MQTT --------------------

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  if (String(topic) == topic_cmd_led) {
    int comma = msg.indexOf(',');
    if (comma > 0) {
      unsigned long sentTs = msg.substring(0, comma).toInt();
      String cmd = msg.substring(comma + 1);
      unsigned long receivedTs = millis();
      unsigned long delayMs = receivedTs - sentTs;

      if (cmd.indexOf("R") >= 0) setLEDColor(255, 0, 0);
      if (cmd.indexOf("G") >= 0) setLEDColor(0, 255, 0);
      if (cmd.indexOf("B") >= 0) setLEDColor(0, 0, 255);

      char buf[128];
      sprintf(buf, "{\"sent\":%lu,\"recv\":%lu,\"delay_ms\":%lu}",
              sentTs, receivedTs, delayMs);
      client.publish(topic_time_report, buf);
      Serial.println(buf);
    }
  }
}

// -------------------- RECONNECT MQTT --------------------

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP32_MonitorSono")) {
      Serial.println("Conectado ao broker HiveMQ!");
      client.subscribe(topic_cmd_led);
    } else {
      Serial.print("Erro MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2s...");
      delay(2000);
    }
  }
}

// -------------------- SETUP --------------------

void setup() {
  Serial.begin(115200);

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  setLEDColor(0, 0, 0);

  analogReadResolution(12);

  Serial.print("Conectando-se ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  unsigned long startWiFi = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startWiFi < 15000) {
    delay(300);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWi-Fi não conectado (simulação).");
  }

  Serial.println("Inicializando MPU6050...");
  if (!mpu.begin()) {
    Serial.println("Erro ao encontrar o MPU6050!");
    while (1) delay(10);
  }
  Serial.println("MPU6050 inicializado!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

// -------------------- LOOP --------------------

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastPublish > publishInterval) {
    lastPublish = now;

    int currentMOV = calcularNivelMovimento();

    int analogVal = analogRead(PIN_POT);
    int currentBPM = map(analogVal, 0, 4095, 45, 115);

    int currentSpO2 = 98;
    if (currentBPM > 90) currentSpO2 = 95;

    String estadoSono = classificarEstado(currentBPM, currentMOV, currentSpO2);

    client.publish(topic_estado, estadoSono.c_str());
    client.publish(topic_bpm, String(currentBPM).c_str());
    client.publish(topic_spo2, String(currentSpO2).c_str());
    client.publish(topic_mov, String(currentMOV).c_str());

    Serial.print("Estado: ");
    Serial.print(estadoSono);
    Serial.print(" | BPM: ");
    Serial.print(currentBPM);
    Serial.print(" | MOV: ");
    Serial.print(currentMOV);
    Serial.print(" | SpO2: ");
    Serial.println(currentSpO2);

    if (estadoSono == "estavel") {
      setLEDColor(0, 255, 0);
    } else if (estadoSono == "agitado") {
      setLEDColor(255, 255, 0);
    } else {
      setLEDColor(255, 0, 0);
    }
  }
}

