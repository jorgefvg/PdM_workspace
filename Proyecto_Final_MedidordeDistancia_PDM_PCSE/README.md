## Proyecto Final de la materia Programación de Microcontroladores y Protocolos de Comunicacion
### Proyecto: Medidor de distancia utilizando un sensor ultrasónico HC-SR04 y una placa núcleo STM32F401RE
#### Autor: Jorge Fernando Vasquez Gonzalez
![image](https://github.com/jorgefvg/PdM_workspace/assets/161152623/41751b0c-d6ca-4a3a-add7-ac4536fdf09c)

Cada vez que el sensor ultrasónico HC-SR04 realiza el cálculo de la distancia de un objeto se debe mostrar el valor de la distancia en cm a través de la UART y por medio de una pantalla LCD 16x2 utilizando el protocolo I2C.

### Perifericos
![image](https://github.com/jorgefvg/PdM_workspace/assets/161152623/4d7154a7-a182-4ff5-9b29-032cc4d96de9)

- GPIO: Para el manejo de los leds.
- I2C: Para el manejo de la comunicación con la pantalla LCD16X2.
- UART: Para el manejo de la comunicación serial entre el microcontrolador y la computadora.
- TIMER: Configurado para la implementación de un timer de 1 MHz en modo input capture, necesarios para el cálculo de la distancia que realiza la API_HCSR04.
