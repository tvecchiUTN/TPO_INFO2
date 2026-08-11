# Avance del TPO

## 11/8/2026

Se tiene pensado hacer la clase Piso y la clase Ascensor. La idea del mismo es para tener un mayor realismo o mayor compresion a la hora de leer el codigo. Un ejemplo seria, 
`if (Ascensor == Piso2){}`
A continuacion lo que puede contener la clase Piso, mas adelante se haran cambios sean necesarios.

### Clase Piso

Contendra como atributos un objeto sensor, por ahora se utilizara un sensor optico. Para este se hara su respectiva clase. Tambien contendra un identificador de numero de piso. Puede ser tambien un booleano si el ascensor esta en ese piso. Si el asensor llego o se fue, osea saber su ultimo estado.

### Clase Ascensor

Contendra como atributos el objeto DriverStepper, este ya fue probado y funciona perfectamente. El mismo se puede seleccionar para que se mueva a un sentido o para otro, que abstaido seria que suba o que baje. Contiendra variables como el piso en el que esta, en el que tiene que ir. Si esta subiendo o bajando.
