# Práctica 2
### Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes. 
### Punto 1
Implementar las funciones auxiliares necesarias para usar retardos no bloqueantes en un archivo fuente ```main.c``` con su correspondiente archivo de cabecera ```main.h```.
En ```main.h``` se deben ubicar los prototipos de las siguientes funciones y las declaraciones:
```javascript
  typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
  typedef bool bool_t;	  // Qué biblioteca se debe incluir para que esto compile?
  typedef struct{
      tick_t startTime;
      tick_t duration;
      bool_t running;
  } delay_t;
  void delayInit( delay_t * delay, tick_t duration );
  bool_t delayRead( delay_t * delay );
  void delayWrite( delay_t * delay, tick_t duration );
```

En main.c se debe ubicar la implementación de todas las funciones. 
Acontinuacion se muestra parte del codigo que se utilizo para cada enunciado. El archivo ```main.c``` se encuentra en la carpeta ```Core```, donde se encuentra el codigo completo.
### Implementacion en main.c
1. delayInit debe cargar el valor de duración del retardo en la estructura, en el campo correspondiente. 
No debe iniciar el conteo del retardo. Debe inicializar el flag running en `false´.
```javascript
  void delayInit(delay_t* delay, tick_t duration) {
  delay->duration = duration;
  delay->running = false;  //Inicializa el flag running en false
  }
 ```  
2. delayRead debe verificar el estado del flag running.
  - false, tomar marca de tiempo y cambiar running a ‘true’ 
  - true, hacer la cuenta para saber si el tiempo del retardo se cumplió o no: ‘marca de tiempo actual - marca de tiempo inicial es mayor o igual a duración del retardo’? 
  - devolver un valor booleano que indique si el tiempo se cumplió o no.
  - Cuando el tiempo se cumple se debe cambiar el flag running a false.
```javascript
  bool_t delayRead(delay_t* delay) {
  if (!delay->running) {                                   //Verificamos el estado de running
  delay->startTime = HAL_GetTick();                       //Toma una marca de tiempo
  delay->running = true;                                  //Cambia running a true
  return false;
  } else {
      tick_t currentTime = HAL_GetTick();
      tick_t elapsedTime = currentTime - delay->startTime;    //Saber si el tiempo de retardo se cumplio
        
      if (elapsedTime >= delay->duration) {                   //Si el tiempo se cumple devuelve
      delay->running = false;                                 //el flag de running a false
      return true;
      } else {
      return false;
      }
    }
  }
```

3. delayWrite debe permitir cambiar el tiempo de duración de un delay existente
```javascript
  void delayWrite(delay_t* delay, tick_t duration) {
  delay->duration = duration;
  }
```
### Punto 2
Sobre el código desarrollado para el punto 1 y sobre el mismo proyecto, 
implementar un programa que utilice retardos no bloqueantes y  haga parpadear el leds de la placa de desarrollo: 
- 100 ms encendido, 100 ms apagado, en forma periódica.
Acontinuacion se muestra parte del codigo que se utilizo. El archivo ```main.c``` se encuentra en la carpeta ```Core```, donde se encuentra el codigo completo. 
```javascript
  /* Inicializar los retardos para cada LED*/
  delayInit(&delayLED2, LED2_TIME);
```
```javascript
  while (1){
	  // Verificar los retardos y controlar el parpadeo del LED

      if (delayRead(&delayLED2)) {
         // El tiempo de retardo para LED2 (incluido en la placa) se ha cumplido, cambiar el estado del LED
         HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
      }

  }
}
```

https://github.com/jorgefvg/PdM_workspace/assets/161152623/a4ec8e55-185a-4cec-be4e-9eeabc36c8e0

