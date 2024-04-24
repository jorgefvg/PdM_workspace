## Proyecto Final de la materia Programación de Microcontroladores y Protocolos de Comunicacion
### Proyecto: Medidor de distancia utilizando un sensor ultrasónico HC-SR04 y una placa núcleo STM32F401RE
#### Autor: Jorge Fernando Vasquez Gonzalez

https://github.com/jorgefvg/PdM_workspace/assets/161152623/83e278d3-eb92-4fe0-ba42-8ff6ea7953ee

Cada vez que el sensor ultrasónico HC-SR04 realiza el cálculo de la distancia de un objeto se debe mostrar el valor de la distancia en cm a través de la UART y por medio de una pantalla LCD 16x2 utilizando el protocolo I2C.

### Perifericos
![image](https://github.com/jorgefvg/PdM_workspace/assets/161152623/5e658e90-fecf-4f10-80d3-5afeacf16ccd)


- GPIO: Para el manejo de los leds.
- I2C: Para el manejo de la comunicación con la pantalla LCD16X2.
- UART: Para el manejo de la comunicación serial entre el microcontrolador y la computadora.
- TIMER: Configurado para la implementación de un timer de 1 MHz en modo input capture, necesarios para el cálculo de la distancia que realiza la API_HCSR04.
