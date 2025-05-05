#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Balidacion

// Solicita un número entre mínimo y máximo, solo muestra mensajes si hay error
void limpiar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

int entero_valido(char entrada[]) {
  int i = 0;
  // Ignorar signo negativo al inicio
  if (entrada[0] == '-') {
    i = 1;
    if (entrada[1] == '\0')
      return 0; // solo "-" no es válido
  }

  for (; entrada[i] != '\0'; i++) {
    if (!isdigit(entrada[i]))
      return 0;
  }

  return 1;
}

// Función principal

int pedir_numero(int minimo, int maximo) {
  char entrada[50];
  int numero;
  int valido = 0;

  printf("Ingrese un número");
  if (maximo > 0)
    printf(" entre %d y %d", minimo, maximo);
  else
    printf(" mayor o igual a %d", minimo);
  printf(": ");

  while (!valido) {
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // Eliminar salto de línea

    if (!entero_valido(entrada)) {
      printf("❌ Error: entrada inválida, solo se permiten números enteros.\n");
    } else {
      numero = atoi(entrada);

      if (numero >= minimo && (maximo <= 0 || numero <= maximo)) {
        valido = 1; //  Número dentro del rango
      } else {
        printf("❌ Error: número fuera del rango permitido.\n");
      }
    }

    if (!valido) {
      if (maximo > 0)
        printf("Ingrese un número entre %d y %d: ", minimo, maximo);
      else
        printf("Ingrese un número mayor o igual a %d: ", minimo);
    }
  }

  return numero;
}

// Función para pintar el tablero
void tablero_respuesta(int fila_actual, int columna_actual, char **tablero,
                       int dim) {
  tablero[fila_actual][columna_actual] = 'R';

  for (int fila = 0; fila < dim; fila++) { // Recorrer el tablero
    for (int columna = 0; columna < dim; columna++) {

      if (fila != fila_actual ||
          columna !=
              columna_actual) { // Si no es la casilla ocupada por la reina

        if (fila + columna ==
                fila_actual + columna_actual && // Colocar las P en la diagonal
            tablero[fila][columna] != 'R') {
          tablero[fila][columna] = 'P';
        } else if ((fila == fila_actual ||
                    columna == columna_actual) && // colocar las P en las filas
                                                  // y columnas
                   tablero[fila][columna] != 'R') {
          tablero[fila][columna] = 'P';
        } else if ((fila - columna ==
                    fila_actual -
                        columna_actual) && // Colocar las P en la diagonal
                   tablero[fila][columna] != 'R') {
          tablero[fila][columna] = 'P';
        }
      }
    }
  }
}

char **crear_matriz(int dim,
                    char valor) { // Crear la matriz de n x n dimenciones y las
                                  // rellena con un valor
  char **matriz = malloc(dim * sizeof(char *));
  for (int i = 0; i < dim; i++) {
    matriz[i] = malloc(dim * sizeof(char));
  }

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      matriz[i][j] = valor;
    }
  }
  return matriz;
}

int main() {
  int cant_reinas = 0;
  printf("Ingrese las dimenciones del tablero\n");
  int n = pedir_numero(2, 0);

  char **tablero = crear_matriz(n, '*');
  int lugares_reinas = 1;
  while (lugares_reinas) {

    printf("\nIngrese la fila seleccionada\n");
    int fila_actual = pedir_numero(1, n) - 1;
    printf("\nIngrese la columna seleccionada\n");
    int columna_actual = pedir_numero(1, n) - 1;
    printf("\n");

    if (tablero[fila_actual][columna_actual] == 'R' ||
        tablero[fila_actual][columna_actual] == 'P') {

      printf("\nEl lugar seleccionado no es valido.\n\n");

    } else {

      tablero_respuesta(fila_actual, columna_actual, tablero, n);
      cant_reinas++;
    }
    lugares_reinas = 0;
    // Imprimir el tablero
    for (int fila = 0; fila < n; fila++) {
      printf("%d| ", fila + 1);

      for (int columna = 0; columna < n; columna++) {
        printf("%c ", tablero[fila][columna]);

        if (tablero[fila][columna] ==
            '*') { // verifica que existan casillas vacias
          lugares_reinas = 1;
        }
      }
      printf("\n");
    }

    printf("   ");
    for (int columna = 0; columna < n; columna++) {
      printf("%d ", columna + 1);
    }
    printf("\n");
  }
  printf("\nJuego Finalizado.\n Cantidad de reinas jugadas: %d\n", cant_reinas);
  return 0;
}
