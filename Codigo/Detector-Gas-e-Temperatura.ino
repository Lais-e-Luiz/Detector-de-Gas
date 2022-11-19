
/************************************************************************************
* Projeto: Sensor de Gás                                                            * 
* Matéria: Objetos Inteligentes Conectados                                          *
* Professor: Wallace Rodrigues de Santana                                           *
*                                                                                   *
* Autores: Luiz Moura Tavares (Tia: 20200262)                                       *
*          Laís Arianne Monteiro Liberato (Tia: 20519141)                           *
*                                                                                   *   
* Descrição: Programa de monitoramento e controle residencial através de aplicativo *
* utilizando o protocolo MQTT Broker com o módulo NodeMCU ESP8266                   *
*************************************************************************************/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE (50)
#define buzzer 12
#define sensorGas 4

char msg[MSG_BUFFER_SIZE];

//const char* ssid = "dlink-0D6C";
const char* ssid = "Net-Virtua-6156";
const char* password = "2612140925";

//const char* mqtt_server = "broker.mqtt-dashboard.com";
//const char* mqtt_server = "mqtt.eclipseprojects.io";
const char* mqtt_server = "20.226.77.22";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
int value = 0;

bool sensor_gas;

void setup() {

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(1000);
  Serial.println("");
  Serial.print("Conectando com ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Aguardando conexão MQTT...");
    String clientId = "ESP8266Client";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
      client.subscribe("Sensor_Gas/publisher");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println("tentando conexão MQTT novamente em 5s");
      delay(5000);
    }
  }
}

void loop() {

  sensor_gas = digitalRead(sensorGas);

  if (sensor_gas == LOW) {
    Serial.print(F("Gas: "));
    Serial.println(sensor_gas);
    snprintf (msg, MSG_BUFFER_SIZE, "Gás Detectado");
 
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    Serial.println("Cuidado !!! Gás Detectado");

    client.publish("Sensor_Gas/gas", msg);
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

/************************ FIM DO PROGRAMA***************************/