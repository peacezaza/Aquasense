#define drivo1 4
#define drivo2 17
#define drivo3 16
#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 13
#define L298IN1 21
#define L298IN2 22
#define oxygenQuailty 5
#define pHQuailty 7
#define turbidityQuailty 100
#define STEPS_PER_REV 1024
#define pHTopic "/pHSensor"
#define oxygenTopic "/OxygenSensor"
#define turbidityTopic "/TurbiditySensor"

#include <WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "40.81.22.116"
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME "ESP32_1"
WiFiClient client;
PubSubClient mqtt(client);

const char* ssid = "BBKK_2.4GHz";
const char* password = "0800536270";

float pHValue = 0;
float oxygenValue = 0;
float turbidity = 0;

int currentTime = 0;
int lastSaveTime = 0;

int stepDelay = 2;

void stepMotor(int step);
void connectWiFi();
void mqttConnect();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  Serial.begin(115200);
  pinMode(drivo1, OUTPUT);
  pinMode(drivo2, OUTPUT);
  pinMode(drivo3, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(L298IN1, OUTPUT);
  pinMode(L298IN2, OUTPUT);
  digitalWrite(drivo1, HIGH);
  digitalWrite(drivo2, HIGH);
  digitalWrite(drivo3, HIGH);

  connectWiFi();
}

void loop() {
  mqttConnect();
  mqtt.loop();


  currentTime = millis();
  if (currentTime - lastSaveTime > 1000) {
    for (int i = 0; i < STEPS_PER_REV; i++) {
      stepMotor(i);
      delay(stepDelay);
    }
    if (pHValue < pHQuailty - 1) {
      digitalWrite(drivo2, LOW);
      delay(300);
      digitalWrite(drivo2, HIGH);
    } else if (pHValue > pHQuailty + 1) {
      digitalWrite(drivo1, LOW);
      delay(300);
      digitalWrite(drivo1, HIGH);
    }
    for (int i = STEPS_PER_REV - 1; i >= 0; i--) {
      stepMotor(i);
      delay(stepDelay);
    }
    if (oxygenValue < oxygenQuailty) {
      digitalWrite(L298IN1, LOW);
      digitalWrite(L298IN2, HIGH);
    } else {
      digitalWrite(L298IN1, LOW);
      digitalWrite(L298IN2, LOW);
    }
    if (turbidity > turbidityQuailty) {
      digitalWrite(drivo3, LOW);
    } else {
      digitalWrite(drivo3, HIGH);
    }

    lastSaveTime = currentTime;
  }
}



void stepMotor(int step) {
  switch (step % 4) {
    case 0:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
  }
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);  //Optional
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt.setCallback(callback);
}

void mqttConnect() {
  if (mqtt.connected() == false) {
    Serial.print("MQTT connection... ");
    if (mqtt.connect(MQTT_NAME, MQTT_USERNAME,
                     MQTT_PASSWORD)) {
      Serial.println("connected");
      mqtt.subscribe("/OxygenSensor");
      mqtt.subscribe("/TurbiditySensor");
      mqtt.subscribe("/pHSensor");
    } else {
      Serial.println("failed");
      delay(5000);
    }
  } else {
    mqtt.loop();
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String topic_str = topic, payload_str = (char*)payload;
  // Serial.print("Payload is :");
  // Serial.println("[" + topic_str + "]: " + payload_str);
  int value = payload_str.toInt();
  if (topic_str == pHTopic) {
    pHValue = value;
    Serial.print("Payload is :");
    Serial.println("[" + topic_str + "]: " + payload_str);
  } else if (topic_str == oxygenTopic) {
    oxygenValue = value;
    Serial.print("Payload is :");
    Serial.println("[" + topic_str + "]: " + payload_str);
  } else if (topic_str == turbidityTopic) {
    turbidity = value;
    Serial.print("Payload is :");
    Serial.println("[" + topic_str + "]: " + payload_str);
  }
}

If I want to change my code to rtos 
what should i use like task or queue 
teach me don't do it for me
