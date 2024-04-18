## Maquina de estado implementada en el proyecto
![image](https://github.com/jorgefvg/PdM_workspace/assets/161152623/f23eafe4-7905-452d-8520-fca165191f95)

Dentro del archivo main.c se encuentra la MEF de tres estados posibles, los cuales son:
- INITIAL: Duración del estado -> 2 segundos.
  En un lapso de tiempo de 400ms (TIME_MESSAGE) se muestra un mensaje  “Iniciando, Sensor Ultrasónico” y comienza a parpadear el LED1 (led externo color blanco) con un tiempo de 200ms (TIME_LED1). Cuando se cumplen los 2 segundos de duración del estado INITIAL, se pasa al siguiente estado READ.
- READ: Duración del estado -> 2 segundos.
  En este estado se realiza la lectura de datos de la medición de la distancia, en un lapso de tiempo de 400ms (TIME_MESSAGE) se muestra un mensaje  “HC-SR04, Midiendo..” y comienza a parpadear el LED2 (led verde incluido en la placa) con un tiempo de 200ms (TIME_LED2). Cuando se cumplen los 2 segundos de duración del estado READ, se pasa al siguiente estado WRITE.
- WRITE: Duración del estado -> 2 segundos.
  En este estado se realiza la escritura de datos de la medición de la distancia en una pantalla LCD16x2, en un lapso de tiempo de 400ms (TIME_MESSAGE) se muestra un mensaje  “HC-SR04, Distancia: __ cm” y comienza a parpadear el LED3 (led externo color azul) con un tiempo de 200ms (TIME_LED3). Al mismo tiempo se imprimen los datos de medición de la distancia en el puerto UART, donde se muestra el mensaje “Distancia: __ cm”. Cuando se cumplen los 2 segundos de duración del estado WRITE, se pasa al estado anterior READ.
  Nota: Todos los retardos son no bloqueantes y se implementan en el archivo API_delay.c. 
