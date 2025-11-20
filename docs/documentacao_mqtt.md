# Documentação das Interfaces MQTT

## 1. Tópicos de Publicação

- sono/frequencia_cardiaca  
  Publica BPM simulado pelo potenciômetro.

- sono/spo2  
  Publica SpO2 simulada pelo software.

- sono/movimento  
  Publica leitura do MPU6050.

- sono/estado  
  Publica: estável, agitado ou despertar.

- medidas/response_time  
  Publica tempos de resposta entre envio e ação.

---

## 2. Tópico de Assinatura

- sono/comando_led  
  Recebe comandos no formato:
  
<timestamp>,<cor>


Exemplos:
1699200000,G
1699200000,Y
1699200000,R

---

## 3. Formato das Mensagens Publicadas

### Exemplo de publicação de sensores

{
"sent": 1699200000,
"bpm": 78,
"mov": 0,
"spo2": 98
}

### Exemplo de resposta de tempo

{
"sent": 1699200000,
"recv": 44104,
"delay_ms": 2595811401
}

---

## 4. Broker Utilizado

- HiveMQ Public Broker  
- Servidor: broker.hivemq.com  
- Porta: 1883 
