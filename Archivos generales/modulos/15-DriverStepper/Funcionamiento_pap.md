# Funcionamiento del motor paso a paso

## Descripcion

El funcionamiento de un motor paso a paso es similar al de uno convencional, compuesto por un rotor y un estator. Mediante unas bobinas en el estator, comunmente 2 en posiciones opuestas y un rotor magnetizado puedo controlar con presicion el movimiento. Se alimenta una de las bobinas, produciendo un campo magnetico, y el rotor se mueve debido a la atraccion de polos opuestos. Esto me produjo un "paso". Para lograr un movimiento mas fluido, debo dejar de alimentar esa bobina y alimentar la siguiente. Asi consecutivamente.

Un motor como estos se utilizan, por ejemplo, en brazos roboticos porque me permite con presicion cuanto moverme. Ademas son utilizados por su torque. En este TPO se utiliza para mover con exactitud la cabina del ascensor. 

## Driver del motor: TB6600

El driver de un motor paso a paso es el encargado de enviarle las señales logicas a las bobinas del motor. De esta manera, se simplifica la tarea al usuario. Tiene 12 pines:

- 2 de alimentacion para el motor, como minimo 9V y maximo 48V.
- 4 para conectar los cables del motor, 2 indican una bobina y las otros 2 la otra.
- Pul+ y pul-, dependiendo como se configure. Si activo alto(Pul+) o activo bajo(Pul-). Es el encargado de recibir la señal logica. Se tiene que enviar pulsos logicos para lograr el movimiento.
- Dir+ y dir-, dependiendo como se configure. Si activo alto(Pul+) o activo bajo(Pul-). Se encarga de establecer la direccion de giro. Se tiene que enviar una señal constante para establecer la direccion. Por ejemplo, para que gire en sentido horario, enviar 1 logico y viceversa.
- En+ y en-, dependiendo como se configure. Si activo alto(Pul+) o activo bajo(Pul-). Se encarga de establecer el encendido y apagado del driver. Usualmente no se lo conecta porque siempre quiero que este encendido. Se tiene que enviar una señal constante para habilitar o no.

Supongamos un ejemplo de conexionado con un microcontrolador:

1) Conecto los cables del paso a paso al driver. Revisar el datasheet del mismo para saber el par de cables. Al conocerlos, conectar un par en A+ y A- y el otro en B+ y B-.
2) Conectar el pin Dir+ a un pin del microcontrolador.
3) Conectar el pin Pul+ a otro pin del microcontrolador.
4) Lo mismo para el pin En+.
5) Conectar Dir-, Pul- y En- al GND del microcontrolador.
6) Conectar el driver a una fuente de alimentacion correcta.

## Explicacion clase DriverStepper

El motivo que origino en crear esta clase es la complejidad que iba a tener a la hora de moverlo. Debido a que necesitaba enviarle pulsos al driver para mover el motor, use la clase "PerifericoTemporizado". Este me permite cada 1ms enviarle los pulsos necesarios al driver. En caso de girar muy rapido, hay una manera para carbiarlo.

### Metodos publicos de la clase

- Constructor de la clase: se le envia el puerto y bit de cada pin dle driver.
- getError: Si hubo un error de parametros, devuelve **TRUE**, sino **OK**.
- HandlerDelPeriferico: Metodo que ejecuta el systick. Se encarga de enviar las señales de movimiento.
- setTicks: Recibe la cantidad de ticks que tiene que esperar para mover un paso.
- freeMove: Se mueve libremente. Cada 1 ms se envia la señal, ya sea 1 o 0.
- ticksMove: Empieza a moverse cada ciertos ticks indicados por parametros.
- setStepDir: Establece la direccion de giro.
- toggleStepDir: Cambia la direccion de giro.
- startDriver: Inicia el driver o lo enciende.
- stopDriver: Apaga el driver o lo frena.