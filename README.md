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

Toda a documentação completa está em:  
 `/docs/documentacao_mqtt.txt`

---

## Hardware Utilizado

- ESP32 DevKit V1  
- MPU6050 (acelerômetro + giroscópio)  
- Potenciômetro (simulação de BPM/SpO2)  
- LED RGB com resistores  
- Protoboard + jumpers  

Documentação detalhada em:  
 `/docs/hardware_detalhado.md`

---

##  Código-Fonte

O código-fonte do ESP32 está em:  
 `/src/sketch.ino`

---

## Diagramas do Projeto

 `/diagrams/diagram.json` — Arquivo Java do diagrama 
 `/diagrams/diagram.png` — Diagrama Wokwi  
 `/diagrams/fluxograma.png` — Fluxograma do sistema  

---

##  Resultados e Evidências

As principais imagens estão em:  
 `/imagens/`

Inclui:

- estado_estavel.png  
- estado_agitado.png  
- estado_despertar.png  
- simulador_conectado_ao_wifi.png  
- mqtt_explorer.png  

---

##  Vídeo da Demonstração

O vídeo apresentando:
- funcionamento completo  
- MQTT em tempo real  

 **https://youtu.be/WTWZORfzqeg**

---

##  Documentação Complementar

- Guia de execução: `/docs/guia_execucao.txt`
- Artigo final da disciplina: `/docs/artigo_final.pdf`

---

##  Autoria

Victoria Lopes  
Trabalho final da disciplina de **Objetos Inteligentes Conectados — Mackenzie**  
2025

