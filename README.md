# Monitor de Sono com IoT e Protocolo MQTT — ESP32 

Este repositório contém o projeto completo do **Monitor de Sono IoT** desenvolvido para a disciplina de **Objetos Inteligentes Conectados**.  
O sistema realiza monitoramento de **frequência cardíaca (simulada)**, **nível de movimento (MPU6050)** e **saturação de oxigênio (simulada)**, classificando o sono em:

- Sono Estável  
- Sono Agitado  
- Despertar  

Toda a comunicação é feita via **MQTT**, utilizando o broker público **HiveMQ**.

---

## Tecnologias Utilizadas

- **ESP32 DevKit V1**
- **MPU6050 (sensor de movimento)**
- **Potenciômetro (simulação de BPM)**
- **LED RGB (atuador)**
- **Protocolo MQTT**
- **Broker:** `broker.hivemq.com`
- **Wokwi Simulator**
- **Python (opcional para medições de tempo)**

---

## Arquitetura e Tópicos MQTT

### **Publicações**
```
sono/frequencia_cardiaca
sono/spo2
sono/movimento
sono/estado
```

### **Assinatura**
```
sono/comando_led
```

### **Medição de tempo**
```
medidas/response_time
```

---

## Funcionamento Resumido

1. ESP32 conecta ao Wi-Fi e ao broker MQTT.  
2. Lê BPM (potenciômetro), movimento (MPU6050) e simula SpO2.  
3. Classifica o estado do sono.  
4. Aciona o LED RGB conforme estado:  
   - **Verde:** Sono estável  
   - **Amarelo:** Sono agitado  
   - **Vermelho:** Despertar  
5. Publica dados nos tópicos MQTT.  
6. Recebe comandos MQTT para acionar o LED e mede tempo de resposta.

---

## Estrutura do Repositório

```
monitor-de-sono-iot-mqtt/
│
├── src/                 # Código do ESP32
│   └── codigo_esp32.ino
│
├── diagrams/            # Diagramas do projeto
│   ├── fritzing_monitor_sono.fzz
│   ├── fritzing_monitor_sono.png
│   └── fluxograma_monitor_sono.png
│
├── imagens/             # Evidências, capturas de tela e gráficos
│   ├── montagem_wokwi.png
│   ├── mqtt_explorer.png
│   ├── console_serial.png
│   ├── grafico_bpm.png
│   ├── grafico_movimento.png
│   └── grafico_tempo_atuador.png
│
├── docs/                # Artigo final e guias
│   ├── artigo_final.pdf
│   └── guia_execucao.txt
│
└── README.md            # Este arquivo
```

---

## Como Executar no Wokwi

1. Abra o Wokwi: https://wokwi.com  
2. Importe o código do diretório `/src`.  
3. O arquivo **wokwi.toml** deve conter:

```toml
[wokwi]
version = 1
firmware = "codigo_esp32.ino"

[simulation]
version = 1

[[net.interfaces]]
type = "wifi"
ssid = "Wokwi-GUEST"
password = ""
```

4. Clique em **Run**.

---

## Medições de Tempo (Atuador e Sensores)

Para cada sensor e atuador, faça **4 medições** e calcule a média.  
Os resultados devem ser colocados no artigo e aqui na pasta `/imagens`.

---

## Vídeo Demonstrativo

O vídeo apresentará:
- Funcionamento do protótipo  
- MQTT em tempo real  
- Seu rosto e identificação  
- Explicação do código  

> Link do vídeo será inserido após gravação.

---

## Artigo Final

O PDF final estará em:  
`/docs/artigo_final.pdf`

---

## Autora

Victoria Lopes  
Trabalho final da disciplina de **Internet das Coisas — Mackenzie**  
2025

