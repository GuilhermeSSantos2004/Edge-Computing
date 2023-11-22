#include "ArduinoJson.h"
#include "EspMQTTClient.h"

EspMQTTClient client{
  "Wokwi-GUEST", // SSID do WiFi
  "",            // Senha do WiFi
  "mqtt.tago.io", // Endereço do servidor
  "Default",      // Usuário
  "d5f6b24a-6bf3-4cdd-ab60-37ef5069a21e", // Token do dispositivo
  "LifeStream",   // Nome do dispositivo
  1883            // Porta de comunicação
};

const int buzzerPin = 14;

const int buttonPin = 19; // Defina o pino do botão
int buttonState = HIGH; // Estado inicial do botão
int lastButtonState = HIGH; // Estado anterior do botão
unsigned long lastDebounceTime = 0; // Último momento em que o botão foi lido sem rebote
unsigned long debounceDelay = 30; // Atraso de debounce em milissegundos


void setup() {
  Serial.begin(9600);
  Serial.println("Conectando WiFi");


  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  digitalWrite(buzzerPin, LOW); // Ensure the buzzer is initially off

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
}

void onConnectionEstablished(){
   Serial.println("Subscribing mytopic");
   client.subscribe("mytopic", onTestMessageReceived);
}

void onTestMessageReceived(const String& message) {
  Serial.println("message received from mytopic: " + message);
}

char bufferJson[100];
int temperatura = 0;


void buzzer() {

  digitalWrite(buzzerPin, HIGH); // liga o buzzer
  delay(1000); // Mantém o buzzer acionado por 1 segundo 
  digitalWrite(buzzerPin, LOW); // Desliga o buzzer
  delay(1000); // Mantém o buzzer acionado por 1 segundo
  digitalWrite(buzzerPin, HIGH); 
  delay(1000);  
  digitalWrite(buzzerPin, LOW); 

  client.loop();
}


void loop() {


  int reading = digitalRead(buttonPin); // Lê o estado do botão

  
  if (reading != buttonState) {
      buttonState = reading;

      // Se o novo estado do botão for HIGH, significa que o botão foi pressionado
      if (buttonState == HIGH) {

        buzzer();
        Serial.println("Botão pressionado!");

        lastButtonState = reading;

        StaticJsonDocument<300> documentoJson;
        documentoJson["variable"] = "Button";
        documentoJson["value"] = lastButtonState;
        documentoJson["unit"] = "status";
        serializeJson(documentoJson, bufferJson);
        Serial.println(bufferJson);
        client.publish("topicoEngSoft", bufferJson);
        
        
        
        
        // Adicione o código que deseja executar quando o botão é pressionado
      }
    }
  

  // Atualiza o último estado do botão

}
