#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include <PubSubClient.h>

const int buttonPin = 19; // Defina o pino do botão
int buttonState = HIGH; // Estado inicial do botão
int lastButtonState = HIGH; // Estado anterior do botão
unsigned long lastDebounceTime = 0; // Último momento em que o botão foi lido sem rebote
unsigned long debounceDelay = 30; // Atraso de debounce em milissegundos

//------------Buzzer-------------------------

const int buzzerPin = 14; 

EspMQTTClient client{
  "Wokwi-GUEST", // SSID do WiFi
  "",            // Senha do WiFi
  "mqtt.tago.io", // Endereço do servidor
  "Default",      // Usuário
  "d5f6b24a-6bf3-4cdd-ab60-37ef5069a21e", // Token do dispositivo
  "LifeStream",   // Nome do dispositivo
  1883            // Porta de comunicação
};

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT); // Configura o pino do botão como entrada
  pinMode(buzzerPin, OUTPUT); // Configura o pino do buzzer como saída

  Serial.println("Conectando WiFi");
  while (!client.isWifiConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("WiFi Conectado");
  
  Serial.println("Conectando com Servidor MQTT");
  while (!client.isMqttConnected()) {
    Serial.print('.');
    client.loop();
    delay(1000);
  }
  Serial.println("MQTT Conectado");

  // Inscrever-se ao tópico desejado
  mqttClient.setServer("mqtt.tago.io", 1883);
  mqttClient.setCallback(callback);
  mqttClient.subscribe("topicoTDSPI");
}

void onConnectionEstablished()
{}


void buzzer() {

  digitalWrite(buzzerPin, HIGH); // liga o buzzer
  delay(1000); // Mantém o buzzer acionado por 1 segundo 
  digitalWrite(buzzerPin, LOW); // Desliga o buzzer
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

char bufferJson[100];
int temperatura = 0;

void loop() {

  int reading = digitalRead(buttonPin); // Lê o estado do botão

  // Verifica se houve mudança no estado do botão
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Atualiza o momento do último estado sem rebote
  }

  // Verifica se o botão está em um novo estado após o período de debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Se o estado do botão mudou, atualiza o estado atual
    if (reading != buttonState) {
      buttonState = reading;

      // Se o novo estado do botão for HIGH, significa que o botão foi pressionado
      if (buttonState == HIGH) {
        Serial.println("Botão pressionado!");
        buzzer();
        // Adicione o código que deseja executar quando o botão é pressionado
      }
    }
  }

  // Atualiza o último estado do botão
  lastButtonState = reading;
 

}
