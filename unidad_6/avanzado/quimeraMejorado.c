#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int aleatorio(int lim_inferior, int lim_superior) {
  return rand() % (lim_superior - lim_inferior + 1) + lim_inferior;
}

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

float calcular_ganancia(int aciertos, float monto_apostado) {
  float ganancia;

  switch (aciertos) {
  case 10:
    ganancia = monto_apostado * 50;
    break;
  case 9:
    ganancia = monto_apostado * 40;
    break;
  case 8:
    ganancia = monto_apostado * 30;
    break;
  case 7:
    ganancia = monto_apostado * 25;
    break;
  case 6:
    ganancia = monto_apostado * 20;
    break;
  case 5:
    ganancia = monto_apostado * 15;
    break;
  case 4:
    ganancia = monto_apostado * 10;
    break;
  case 3:
    ganancia = monto_apostado * 5;
    break;
  case 2:
    ganancia = monto_apostado * 2;
    break;
  case 1:
    ganancia = monto_apostado * 0.5;
    break;
  default:
    ganancia = 0;
    break;
  }

  return ganancia;
}
int main() {
  srand(time(NULL)); // Iniciamos la semilla

  int numeros_introducidos[10], numeros_aleatorio[10];
  int jugadas;
  float *ganancia;
  printf("Cuantas rondas quieres jugar.\n");
  jugadas = pedir_numero(1, 0);

  ganancia = (float *)malloc(jugadas * sizeof(float));
  for (int ronda = 1; ronda <= jugadas; ronda++) {
    int aciertos = 0;
    int apuesta;

    printf("\n======Ronda numero %d.======\n", ronda);
    printf("Cual es en monto que quieres apostar.\n");
    apuesta = pedir_float(1, 0);
    limpiar_buffer();
    // Se introsucen todos lo numeros.
    for (int value = 0; value < 10; value++) {
      numeros_aleatorio[value] = aleatorio(10, 99);

      printf("El numero aleatorio es %d\n", numeros_aleatorio[value]);
      numeros_introducidos[value] = pedir_numero(10, 99);

      if (numeros_aleatorio[value] == numeros_introducidos[value]) {
        aciertos++;
      }
    }
    printf("\n======La lista de numeros aleatorio es:======\n");
    texto_de_lista("La lista de los numeros aleatorios: ", numeros_aleatorio,
                   10);
    texto_de_lista("La lista de los numeros jugados   : ", numeros_introducidos,
                   10);
    printf("El numero de aciertos es %d\n", aciertos);
    if (aciertos == 0) {
      ganancia[ronda - 1] = -apuesta;
    } else {
      ganancia[ronda - 1] = calcular_ganancia(aciertos, apuesta);
    }
  }
  float total_ganancia = 0;
  for (int i = 0; i < jugadas; i++) {
    total_ganancia += ganancia[i];
  }
  printf("El total de ganancia es %.2f\n", total_ganancia * 0.9);
  return 0;
}
