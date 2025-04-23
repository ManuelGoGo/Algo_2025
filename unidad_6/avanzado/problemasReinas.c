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

    // Eliminar salto de línea si existe
    entrada[strcspn(entrada, "\n")] = '\0';

    if (!entero_valido(entrada)) {
      printf("❌ Error: entrada inválida, solo se permiten números enteros.\n");
    } else {
      numero = atoi(entrada);

      if (numero >= minimo && (maximo <= 0 || numero <= maximo)) {
        valido = 1;
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

// Función para pedir un número flotante dentro de un rango
float pedir_float(float minimo, float maximo) {
  float numero;
  int resultado;

  printf("Ingrese un número");
  if (maximo > 0) {
    printf(" entre %.2f y %.2f", minimo, maximo);
  } else {
    printf(" mayor o igual a %.2f", minimo);
  }
  printf(": ");

  while (1) {
    resultado = scanf("%f", &numero);

    if (resultado == 1) {
      if ((numero >= minimo) && (maximo <= 0 || numero <= maximo)) {
        return numero;
      } else {
        printf("❌ Error: número fuera del rango permitido.\n");
      }
    } else {
      printf("❌ Error: entrada inválida, debe ser un número decimal.\n");
    }

    if (maximo > 0) {
      printf("Ingrese un número entre %.2f y %.2f: ", minimo, maximo);
    } else {
      printf("Ingrese un número mayor o igual a %.2f: ", minimo);
    }

    limpiar_buffer(); // descarta entrada inválida
  }
}

void texto_de_lista(char texto[], int vector[], int longitud) {
  printf("%s", texto);
  for (int i = 0; i < longitud - 1; i++) {
    printf("%d, ", vector[i]);
  }
  printf("%d.", vector[longitud - 1]);
  printf("\n");
}

char tablero_respuesta(int fila, int columna, char tablero[][]) {
  for (int fil = 0; fil <= fila; fil++) {
    for (int col = 0; col <= columna; col++) {
      if (fila + columna == fil + col) {
        tablero[fil][col] = 'P';
      }
    }
  }

  return tablero;
}

int main() {
  int n;
  printf("Ingrese las dimenciones del tablero\n");
  n = pedir_numero(2, 0);
  int tablero[n][n];

  for (int fila = 0; fila < n; fila++) {
    for (int columna = 0; columna < n; columna++) {
      tablero[fila][columna] = fila + columna;
    }
  }

  for (int fila = 0; fila < n; fila++) {
    for (int columna = 0; columna < n; columna++) {
      printf("%d ", tablero[fila][columna]);
    }
    printf("\n");
  }

  return 0;
}
