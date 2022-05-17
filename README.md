# connect4-ci5437
Proyecto final CI5437

Busca soluciones óptimas para árboles de juego de Connect 4. Se implementaron los algoritmos Monte Carlo Tree Search y Negamax con poda alfa-beta y tablas de transposición. 

# Ejecución

Compilar el programa con el comando _make_. Luego ejecutar el programa con el
comando ./connect4 _opcion secuencia_
  
Se tienen 5 opciones posibles:
1. MCTS vs Negamax
2. MCTS vs MCTS
3. Negamax vs Jugador
4. MCTS vs Jugador
5. Negamax vs Negamax

Utilizar el número de la opción deseada.

El campo _secuencia_ indica la configuración inicial desde donde se comenzará el juego. Si se deja en
blanco se puede comenzar desde un tablero vacío, pero esto no se recomienda en caso de escoger
alguna opción con Negamax ya que puede tomar mucho tiempo.

Un ejemplo de una secuencia inicial es: 24617524315172127

Revisar el informe para ver otros ejemplos y los resultados obtenidos.
