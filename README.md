# Projeto IoT - Detector para vazamento de gás

Este projeto foi desenvolvido para ser utilizado em residência. Ele será responsável de monitorar o vazamento de Gás e através de um protocolo MQTT enviar mensagem para um app(WhatsApp) através da mensagem de Alerta sobre o vazamento de Gás e automaticamente será emitido um som de alarme através de um hardware(buzzer) indicando que houve vazamento de gás.

## Hardwares utilizados no projeto:

#### 1. Módulo NodeMCU ESP8266
<div>
<img src="https://user-images.githubusercontent.com/118316951/202917171-b6cf72d3-080f-4da4-b7f5-9bc1502a27b7.png" width= "200px">
</div>

#### 2. Sensor de Gás modelo MQ-9
<div>
<img src="https://user-images.githubusercontent.com/118316951/203043123-4338a644-f9e2-4135-85ca-03e6510e724b.png" width= "80px">
</div>

#### 3. Buzzer ativo 3V
<div>
<img src="https://user-images.githubusercontent.com/118316951/203043156-3d666b5f-3552-4ae8-8227-a5b702ca5525.png" width= "50px">
</div>

#### 5. Fonte de energia 
<div>
<img src="https://user-images.githubusercontent.com/118316951/203613837-63277675-bc15-4a8f-966e-303381ddbe08.png" width= "180px">
</div>

## Funcionamento:
<div>
<img src="https://user-images.githubusercontent.com/118316951/203617307-38683b32-1bcd-4e6a-b79e-674d11ccf080.jpg" width= "350px">
</div>

1. Foi conectado o sensor de Gás MQ9 no pino 4 e o Atuador Buzzer no pino 12 no NodeMCU ESP8266 e utilizando um cabo com conector USB ao computador, foi elaborado uma codificação(Stech) através da IDE do Arduino, disponibilizado no projeto.

2. Depois do código ser compilado e sendo salvo para a placa NodeMCU ESP8266, foi desconectado do computador e ligado a uma rede de energia elétrica através de uma fonte com saída 5V. 

3. Através de uma máquina virtual (Microsoft Azure) criamos uma conta, foi colocado esta máquina para rodar e foi feito o acesso via desktop para a instalação dos softwares: Node-red e Mosquitto(MQTT Broker).

4. Foi aberto um terminal através do prompt de comando (Maquina Virtual) e executando o Node-red para que este ficasse em execução para conexão via HTTP(utilizando o IP público da Máquina Virtual) foi elabora o código para que o Node-red fizesse a comunicação para o Mosquitto(MQTT Broker) e gerasse mensagem atráves de um serviço na nuvem chamado CallMeBot API (https://www.callmebot.com/) incluindo o número disponbilidado na plataforma para o App WhatsApp, sendo fornecido um chave(key) única para ser inserida no Node-red.

Acessamdp o Node-red atravées do IP público fornecido pela Máquina Virtual são elaborados os nós(node) que executarão a lógica de funcionamento do sistema, tanto para receber os dados vindos do NodeMCU ESP8266 através do MQTT(broker) Mosquitto para ser processado e ficar escutando qualquer alteração no Sensor de Gás para envio da mensagem quando este detectar vazamento de gás e enviar sinal para o acionamento da buzzer(sinal sonoro).

