#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Enter WiFi ssid";
const char* password = "Enter password";
const char* mqtt_server = ""; // Replace with your MQTT broker IP address
const int mqtt_port = 1883;
const char* subscribe_topic = "enter topic";
const char* publish_topic = "enter topic";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);

  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");

    // Print ESP32's IP address to the serial monitor
  Serial.println(WiFi.localIP());


  // Connect to MQTT broker
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    if (client.connect("ESP32_Client")) {
      client.subscribe(subscribe_topic);
      Serial.println("MQTT connected");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(1000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (message.equals("ON")) {
    digitalWrite(led_pin, HIGH);
    client.publish(publish_topic, "LED turned on");
  } else if (message.equals("OFF")) {
    digitalWrite(led_pin, LOW);
    client.publish(publish_topic, "LED turned off");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_Client")) {
      Serial.println("connected");
      client.subscribe(subscribe_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
