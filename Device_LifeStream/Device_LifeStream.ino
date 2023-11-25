#include <ArduinoJson.h>
#include <EspMQTTClient.h>

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
const int buttonPin = 19;

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 30;

int horasDigitadas = 0;
int minutosDigitados = 0;
int segundosDigitados = 0;
bool temporizadorAtivo = false;
unsigned long tempoInicio = 0;

char bufferJson[100];

void setup() {
  Serial.begin(9600);
  Serial.println("Conectando WiFi");

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

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

  client.subscribe("mytopic", onTestMessageReceived);
}

void onConnectionEstablished() {
  Serial.println("Subscribing mytopic");
}

void onTestMessageReceived(const String& message) {
  Serial.println("message received from mytopic: " + message);

  DynamicJsonDocument doc(300);
  deserializeJson(doc, message);

  horasDigitadas = doc["horas"].as<int>();
  minutosDigitados = doc["minutos"].as<int>();
  segundosDigitados = doc["segundos"].as<int>();

  if (horasDigitadas >= 0 && horasDigitadas < 24 && minutosDigitados >= 0 && minutosDigitados < 60 && segundosDigitados >= 0 && segundosDigitados < 60) {
    temporizadorAtivo = true;
    tempoInicio = millis();
    Serial.println("Temporizador iniciado!");
    Serial.print("Tempo configurado: ");
    Serial.print(horasDigitadas);
    Serial.print(" horas, ");
    Serial.print(minutosDigitados);
    Serial.print(" minutos e ");
    Serial.print(segundosDigitados);
    Serial.println(" segundos.");
  } else {
    Serial.println("Por favor, insira um tempo válido.");
  }
}

void buzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  delay(1000);
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);

  client.loop();
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != buttonState) {
    buttonState = reading;

    if (buttonState == HIGH) {
      buzzer();
      Serial.println("Botão pressionado!");

      lastButtonState = reading;

      DynamicJsonDocument documentoJson(300);
      documentoJson["variable"] = "Button";
      documentoJson["value"] = lastButtonState;
      documentoJson["unit"] = "status";

      serializeJson(documentoJson, bufferJson);

      client.publish("topicoEngSoft", bufferJson);
    }
  }

  if (temporizadorAtivo) {
    unsigned long tempoDecorrido = millis() - tempoInicio;
    unsigned long tempoDigitadoEmMillis = ((horasDigitadas * 3600) + (minutosDigitados * 60) + segundosDigitados) * 1000;

    if (tempoDecorrido >= tempoDigitadoEmMillis) {
      Serial.println("Temporizador concluído!");
      temporizadorAtivo = false;

      // Activate the buzzer when the timer reaches zero
      buzzer();
    }
  }
}
