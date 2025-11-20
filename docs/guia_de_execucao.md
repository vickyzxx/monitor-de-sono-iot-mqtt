Guia de Execução do Projeto Monitor de Sono IoT

1. Abra o Wokwi no link: https://wokwi.com
2. Importe o código localizado em /src/sketchino.
3. Certifique-se de que o arquivo 'wokwi.toml' esteja na raiz do projeto.
4. Execute a simulação clicando em RUN.
5. Acompanhe as leituras no monitor serial (BPM, SpO2, movimento).
6. Verifique a publicação MQTT no MQTT Explorer conectado a:
       broker.hivemq.com — porta 1883
7. Envie comandos pelo tópico 'sono/comando_led'
   Exemplos:
       1699200000,G  → LED Verde
       1699200000,Y  → LED Amarelo
       1699200000,R  → LED Vermelho
8. Observe a resposta imediata do LED e o registro das mensagens MQTT.
