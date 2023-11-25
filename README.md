# Dispositivo de Controle de Medicamentos com ESP32

 > Este repositório contém o código e informações detalhadas para um dispositivo de controle de medicamentos, oferecendo funcionalidades avançadas para garantir uma gestão eficaz de medicamentos. Abaixo estão as principais características do dispositivo:

### Observa-se que o controle adequado de medicamentos é crucial para o paciente, uma vez que tanto a subdosagem quanto a superdosagem podem acarretar danos à saúde humana. Nesse sentido, a LiveSteam apresenta uma proposta para aprimorar o pós-atendimento, oferecendo suporte no monitoramento e controle de medicamentos.

Através da tecnologia LiveStream, os hospitais podem agora prescrever medicamentos online, proporcionando aos pacientes a conveniência de retirar seus medicamentos pessoalmente. Após a coleta, o paciente terá à disposição um sistema de controle de medicamentos, permitindo que verifiquem os horários corretos para a administração dos medicamentos prescritos pelo médico.

O aplicativo associado a essa tecnologia pode ser acessado de qualquer dispositivo conectado à internet, proporcionando facilidade de uso. Além disso, um dispositivo foi desenvolvido com a funcionalidade de efeitos sonoros para auxiliar o paciente a recordar o horário ideal de administração de seus medicamentos. Esse dispositivo está integrado a um sistema de pânico, permitindo que o paciente acione seus familiares.

Comprometida não apenas com os hospitais, nossa empresa visa aprimorar o processo de coleta de medicamentos, proporcionando uma maneira mais segura de obter atestados médicos e receitas. Isso não apenas garante a segurança na administração dos medicamentos, mas também reforça a certeza de que o paciente está seguindo corretamente as orientações prescritas.

<div align="center">

![image](https://github.com/GuilhermeSSantos2004/Edge-Computing/assets/107642647/f9db7846-2fcd-4725-a6c8-56abb277d7d7)

</div>
## Funcionalidades Técnicas Principais:

### 1. Lembrança de Horário:
  
  ###### Personalização dos Lembretes:

- Os usuários podem ajustar os horários de lembrete de acordo com sua programação diária.
- Oferece a opção de lembrete sonoro.


### 2. Conectividade Bluetooth/Wi-Fi:
  ###### Interface Intuitiva:

- **Interface Amigável:**
  - O dispositivo móvel possui uma interface fácil de usar, proporcionando uma experiência amigável para os usuários.

- **Sincronização Automática:**
  - Garante sincronização automática entre o dispositivo e o aplicativo, eliminando a necessidade de intervenção constante do usuário. 

## 3. Botão de SOS e Histórico de Uso:

- **Histórico Detalhado:**
  - No registro de uso, incluem-se informações detalhadas, como datas e horários precisos de cada dose, para um acompanhamento mais eficaz.

- **Alerta aos Familiares:**
  - O paciente pode acionar alertas para seus familiares tanto através do dispositivo quanto pelo aplicativo.

 ## Como Utilizar:

1. **Clone o Repositório:**
   - Clone este repositório em sua máquina local.
     
2. **Configuração do Hardware:**
   - Conecte os sensores, botão e o buzzer ao ESP32.
   - Acesse o link : https://wokwi.com/projects/382052543104418817 para executar o projeto.
     
3. **Intruções para configurar a plataforma Tago**
   - Acessar a plataforma: https://tago.io/
   - Cria um disipositivo MQTT
   - Após criar as duas actions. Você precisa que a primeira fique resposavél por inserir dados no bucket, então ela coleta os dados que vem do dispositivo e a outra com o nome LiveStream, ela deve enviar os dados para o topico MQTT que o dispositivo assina, e assim ele recebe o dado que o Tago envia.
     
## Para executar o projeto: 
   - Acessar a plataforma: [https://wokwi.com/](https://wokwi.com/projects/382052543104418817)

## Video Explicativo
   - Link do vídeo: https://drive.google.com/file/d/1a0Jrk7N-s1hXl_1rEDOwX6xssqXF-fZ-/view?usp=sharing
