#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Balidacion

// Solicita un número entre mínimo y máximo, solo muestra mensajes si hay error

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

void limpiar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

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
// Función principal
struct temperatura {
  float max, min;
};

int main() {
  struct temperatura semana[7];

  for (int dia = 0; dia < 7; dia++) {
    printf("Ingrese la temperatura máxima del dia: %d\n", dia + 1);
    semana[dia].max = pedir_float(-273.15, 0);
    printf("Ingrese la temperatura minima del dia: %d\n", dia + 1);
    semana[dia].min = pedir_float(-273.15, 0);
  }

  // imprimir temperatura

  for (int dia = 0; dia < 7; dia++) {
    printf("La temperatura maxima del dia %d es: %.2f \n", dia + 1,
           semana[dia].max);
    printf("La temperatura minima del dia %d es: %.2f \n", dia + 1,
           semana[dia].min);
  }

  return 0;
}
