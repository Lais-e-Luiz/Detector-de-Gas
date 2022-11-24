# Projeto IoT - Detector para vazamento de gás

Este projeto foi desenvolvido para ser utilizado em residência. Ele será responsável de monitorar o vazamento de Gás e através de um protocolo MQTT enviar mensagem para um app(WhatsApp) através da mensagem de Alerta sobre o vazamento de Gás e automaticamente será emitido um som de alarme através de um hardware(buzzer) indicando que houve vazamento de gás.

## Hardwares utilizados no projeto:

#### 1. Protoboard 400 pontos


<img src="https://user-images.githubusercontent.com/118316951/203629033-753cafba-746d-4aa6-95e2-84dee97130e3.png" width= "350px">


#### 1. Módulo NodeMCU ESP8266

<img src="https://user-images.githubusercontent.com/118316951/202917171-b6cf72d3-080f-4da4-b7f5-9bc1502a27b7.png" width= "200px">


#### 2. Sensor de Gás modelo MQ-9

<img src="https://user-images.githubusercontent.com/118316951/203043123-4338a644-f9e2-4135-85ca-03e6510e724b.png" width= "80px">


#### 3. Buzzer ativo 3V

<img src="https://user-images.githubusercontent.com/118316951/203043156-3d666b5f-3552-4ae8-8227-a5b702ca5525.png" width= "50px">


#### 5. Fonte de energia 

<img src="https://user-images.githubusercontent.com/118316951/203613837-63277675-bc15-4a8f-966e-303381ddbe08.png" width= "180px">


## Funcionamento:

<img src="https://user-images.githubusercontent.com/118316951/203617307-38683b32-1bcd-4e6a-b79e-674d11ccf080.jpg" width= "350px">


1. Esquema de ligação na Protobord: Foi conectado o sensor de Gás MQ9 no pino 4 e o Atuador Buzzer no pino 12 no NodeMCU ESP8266 e utilizando um cabo com conector USB ao computador, foi elaborado uma codificação(Stech) através da IDE do Arduino, disponibilizado no projeto.

2. Depois do código ser compilado e salvo na placa NodeMCU ESP8266, será desconectado o cabo USB do computador e conectado a uma rede de energia elétrica através de uma fonte com saída 5V. 

3. Através de uma máquina virtual (Microsoft Azure) criamos uma conta, foi colocado esta máquina para rodar e foi feito o acesso via desktop para a instalação dos softwares: Node-red e Mosquitto(MQTT Broker).

<img src="https://user-images.githubusercontent.com/118316951/203662829-f2194f6f-19c5-4b80-b04e-0a8e16ace9d4.jpg" width="400px">


4. Foi aberto um terminal através do prompt de comando (Maquina Virtual) e executando o Node-red para que este ficasse em execução para conexão via HTTP(utilizando o IP público da Máquina Virtual) foi elabora o código para que o Node-red fizesse a comunicação para o Mosquitto(MQTT Broker) e gerasse mensagem atráves de um serviço na nuvem chamado CallMeBot API (https://www.callmebot.com/) incluindo o número disponbilidado na plataforma para o App WhatsApp, sendo fornecido um chave(key) única para ser inserida no Node-red.

<img src="https://user-images.githubusercontent.com/118316951/203662537-94c5908a-a14f-4a5d-bb65-678a212288ff.png" width="400px">

5. Acessando o Node-red atravées do IP público fornecido pela Máquina Virtual são elaborados os nós(node) que executarão a lógica de funcionamento do sistema, tanto para receber os dados vindos do NodeMCU ESP8266 através do MQTT(broker) Mosquitto para ser processado e ficar escutando qualquer alteração no Sensor de Gás para envio da mensagem para o App WhatsApp quando este detectar vazamento de gás e também enviar um sinal para o acionamento do dispositivo buzzer(sinal sonoro).

<img src="https://user-images.githubusercontent.com/118316951/203775343-13727667-1e35-47a1-859b-54dd78144560.jpg" width="400px">


