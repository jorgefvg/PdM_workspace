## Módulos de software desarrollados en el proyecto
![image](https://github.com/jorgefvg/PdM_workspace/assets/161152623/bbec0087-87dd-45a8-87c0-b399a9225581)
![image](https://github.com/jorgefvg/PdM_workspace/assets/161152623/3ce7e850-4b46-4cde-b6b2-9b4064ff08e8)

Dentro de la carpeta API, se desarrollaron los siguientes módulos:
- API_state: Módulo de software que implementa las funciones de la MEF. Nota: La MEF se encuentra ubicada en el main.c, API_state se encarga de realizar la lógica de la MEF. 
- API_delay: Módulo de software para trabajar con retardos no bloqueantes. Este módulo es llamado por el main.c para comprobar si se ha cumplido el tiempo de duración de cada estado de la MEF.
- API_Init: Módulo de software que inicializa el hardware general. Contiene las funciones de configuración del reloj del sistema y el Error_Handler.
- API_gpio: Módulo de software que inicializa el gpio. Contienen las funciones de configuración de los pines GPIO para el manejo de los leds y del pin trigger del sensor ultrasónico.
- API_HCSR04: Módulo de software para el manejo del sensor ultrasónico. Este módulo devuelve el valor de la distancia, cada vez que es llamada por la API_state.
- API_timer: Módulo de software que inicializa el timer. Contienen las funciones de la HAL para configurar el timer3 que se utiliza en este módulo.
- API_lcd: Módulo de software para el manejo del lcd de alto nivel. Este módulo permite la comunicación entre el microcontrolador y la pantalla LCD16x2 utilizando I2C, permite a la API_state imprimir el valor de la distancia en la pantalla LCD.
- API_lcd_port: Módulo de software para el manejo del lcd de bajo nivel. Este módulo es llamado por la API_lcd cada vez que necesita transmitir un dato o un comando por I2C. 
- API_uart: Módulo de software que inicializa la uart. Contienen los parámetros de configuración de la UART, además de imprimir un mensaje de si se ha inicializado de forma correcta. Permite a la API_state imprimir el valor de la distancia por la UART.
