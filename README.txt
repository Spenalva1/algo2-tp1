- Creo un arrecife en memoria guardandome el puntero a su dirección. En dicho arrecife guardaré todos los pokemons leídos del archivo cuya ruta recibo por parametros de consola. Luego creo un acuario también en memoria almacenando un puntero a su dirección. Realizo una serie de traslados con distintos filtros de pokemones del arrecife hacia el acuario. En cada traslado verifico que la cantidad de pokemones que cumplan una determinada condición sea mayor a la cantidad solicitada por el traspaso. En caso de que se cumpla, traspaso los pokemones pedidos y en caso contrario no se modifica el arrecife. El traslado consiste en eliminar los pokemones del arrecife para luego agregarlos en el acuario. Después de cada traslado (5 en total) imprimo en pantalla los pokemes restantes del arrecife. Al final de la ejecucion guardo en un archivo 'acuario.txt' los pokemones que quedaron en el acuario. Antes de terminar el programa la memoria utilizada para alojar las estructuras es liberada.

- Para compilarlo se ingresa la siguiente linea en consola (en el directorio del trabajo):
gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca
Y para ejecutarlo:
./evento_pesca arrecife.txt
En la ruta ingresada se encuentran los pokemones que pertenecerán al arrecife.

- Un puntero es una variable cuyo valor es una direccion de memoria. Del mismo se puede obtener el valor almacenado en dicha direccion.

- Es posible operar con punteros, ya sea sumándole o restándole un valor, para que el mismo apunte a una dirección de memoria nueva.

- Un puntero a función es una variable que contiene la dirección de memoria donde esta guardada una función, lo cual permite ejecutarla desde cualquier parte del programa.

- malloc recibe un valor size_t y reserva dicha cantidad en memoria y devuelve el puntero a la ubicación reservada.

- realloc recibe un puntero y un valor size_t y modificará el tamaño del bloque de memoria que se encuentre en la dirección contenida en el puntero. devuelve la dirección del bloque reservado en memoria, ya que en caso de que no entre el nuevo tamaño en la ubicacion original, se le asignará un nuevo sitio en la memoria.
