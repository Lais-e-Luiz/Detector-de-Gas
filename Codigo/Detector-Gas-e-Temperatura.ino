
/**************** Programa: Tutorial Casa Monitorada * 
Autor: Curto Circuito * 
Descrição: Programa de monitoramento e controle residencial através de aplicativo * 
em comunicação MQTT com o ESP8266 
******************************************************************************/

#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#define MSG_BUFFER_SIZE (50)                                                                          
#include <Adafruit_Sensor.h>
#include <DHT.h> 
#include <DHT_U.h>

#define DHTPIN 14
#define sensorGas 4
#define DHTTYPE DHT11

char msg[MSG_BUFFER_SIZE];  
char msg1[MSG_BUFFER_SIZE];  

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;    

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
  
  dht.begin();                                                                                    
  Serial.println(F("Sensor DHT11"));                                                              
  sensor_t sensor;                                                                                
  
  dht.temperature().getSensor(&sensor);                                                           
  Serial.println(F("------------------------------------"));                                      
  Serial.println(F("Temperatura"));                                                               
  Serial.print  (F("Sensor: ")); Serial.println(sensor.name);                                     
  Serial.print  (F("Valor máximo: ")); Serial.print(sensor.max_value); Serial.println(F("°C")); 
  Serial.print  (F("Valor mínimo: ")); Serial.print(sensor.min_value); Serial.println(F("°C")); 
  Serial.print  (F("Resolução: ")); Serial.print(sensor.resolution); Serial.println(F("°C"));    
  Serial.println(F("------------------------------------"));                                      
  
  dht.humidity().getSensor(&sensor);                                                              
  Serial.println(F("------------------------------------"));                                     
  Serial.println(F("Umidade"));                                                                   
  Serial.print  (F("Sensor: ")); Serial.println(sensor.name);                                     
  Serial.print  (F("Valor máximo: ")); Serial.print(sensor.max_value); Serial.println(F("%"));  
  Serial.print  (F("Valor mínimo: ")); Serial.print(sensor.min_value); Serial.println(F("%"));  
  Serial.print  (F("Resolução: ")); Serial.print(sensor.resolution); Serial.println(F("%"));     
  Serial.println(F("------------------------------------"));                                      
  
  delayMS = sensor.min_delay / 2000;        

  Serial.begin(9600);                                                                           
  
  setup_wifi();                                                                                   
  client.setServer(mqtt_server, 1883);                                                            
  client.setCallback(callback);                                                                   
}

void setup_wifi() {                                                                               

  delay(2000);                                                                                      
  Serial.println("");                                                                             
  Serial.print("Conectando com ");                                                                
  Serial.println(ssid);                                                                           

  WiFi.begin(ssid, password);                                                                     

  while (WiFi.status() != WL_CONNECTED) {                                                         
    delay(500);                                                                                   
    Serial.print(".");                                    
  }                  

  Serial.println("");                                                                             
  Serial.println("WiFi conectado");                                                               
  Serial.println("IP: ");                                                                         
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
      client.subscribe("10920500262/publisher");                                                         
    } else {                                                                                      
      Serial.print("falhou, rc=");                                                                
      Serial.print(client.state());                                                               
      Serial.println("tente novamente em 5s");                                                    
      delay(5000);                                                                                
    }
  }
}

void loop() {                                                                                     
  delay(2000);                                                                                 
  sensors_event_t event;   
  //sensor_gas event; 

  sensor_gas = digitalRead(sensorGas);
  if(sensor_gas == HIGH){
    snprintf (msg, MSG_BUFFER_SIZE,"Gas Não Detectado");
    Serial.println("Gas não detectado");
    Serial.println(sensor_gas);
  }
    else if(sensor_gas == LOW){
    //else{
    Serial.print(F("Gas: "));                                                             
    Serial.println(sensor_gas);                                                               
    snprintf (msg, MSG_BUFFER_SIZE,"Gás Detectado");
    //delay(5000);
    snprintf (msg1, MSG_BUFFER_SIZE,"");  
    Serial.println("Cuidado !!! Gás Detectado"); 
    //sprintf(msg,"%f", event.sensorGas);                                                                  
    //sprintf(msg,"%f",event.temperature);   
    //delay(1000);

    client.publish("10920500262/gas", msg);
  }
  
  
  dht.temperature().getEvent(&event);                                                             
  if (isnan(event.temperature)) {                                                                 
    Serial.println(F("Erro na leitura da temperatura!"));                                         
  }
  else if (event.temperature >= 40) {                                                                                      
    Serial.print(F("Temperatura: "));                                                             
    Serial.print(event.temperature);                                                              
    Serial.println(F("°C"));  
    snprintf (msg, MSG_BUFFER_SIZE,"Temperatura muito alta --> Cuidado");                                                                    
    sprintf(msg,"%f",event.temperature);   
    //delay(100);

    client.publish("10920500262/temperatura", msg);                                                      
  }
  else {
    Serial.print(""); 
    //sprintf(msg,"%f",event.temperature);                                                          
    //client.publish("casa/temperatura", msg);   
  }
  dht.humidity().getEvent(&event);                                                                
  if (isnan(event.relative_humidity)) {                                                           
    Serial.println(F("Erro na leitura da umidade!"));                                             
  }
  else {                                                                                          
    Serial.print(F("Umidade: "));                                                                 
    Serial.print(event.relative_humidity);                                                        
    Serial.println(F("%"));                                                                       
    sprintf(msg,"%f",event.relative_humidity);    
    //delay(1000);                                              
    client.publish("10920500262/umidade", msg);                                                          
  }
  if (!client.connected()) {                                                                      
    reconnect();                                                                                  
  }
  client.loop();                                                                                  
}

/************************ FIM DO PROGRAMA***************************/