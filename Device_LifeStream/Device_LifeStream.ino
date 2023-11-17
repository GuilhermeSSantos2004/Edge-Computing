//--------Criar a conexão com o Wi-Fi-------------
// 
// 
//-----------------------------------------------

const int buttonPin = 19; // Defina o pino do botão
int buttonState = HIGH; // Estado inicial do botão
int lastButtonState = HIGH; // Estado anterior do botão
unsigned long lastDebounceTime = 0; // Último momento em que o botão foi lido sem rebote
unsigned long debounceDelay = 50; // Atraso de debounce em milissegundos

//------------Buzzer-------------------------

const int buzzerPin = 14; 


void setup() {
  pinMode(buttonPin, INPUT); // Configura o pino do botão como entrada
  Serial.begin(9600); // Inicia a comunicação serial para depuração (opcional)
  pinMode(buzzerPin, OUTPUT); // Configura o pino do buzzer como saída
  
}

void buzzer() {

  digitalWrite(buzzerPin, HIGH); // liga o buzzer
  delay(1000); // Mantém o buzzer acionado por 1 segundo 
  digitalWrite(buzzerPin, LOW); // Desliga o buzzer
}

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
