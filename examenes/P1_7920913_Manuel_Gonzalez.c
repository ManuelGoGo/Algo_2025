#include <stdio.h>

int main() {
  // delcaracion de las variables utilizadas
  float resultado = 0, balance_ant, ingreso = 0, egreso = 0, valor;
  int contador_in = 0, contador_out = 0;
  char caracter = 0;

  printf("Ingrese balance anterior: ");
  scanf("%f", &balance_ant);
  getchar();
  // Hacemos un while para que el usuario introsuza todas las facturas que
  // quiera
  while (caracter != '=') {

    printf("Ingrese una operación (+, - o = para finalizar): ");
    caracter = getchar();
    getchar();

    // salimos del while (arcaico pero funciona)
    if (caracter == '=') {
      printf("Ha finalizado.\n");
      break;
    }

    printf("Ingrese un número: ");
    scanf("%f", &valor);
    getchar();

    // comrovamos que caracter pertenece para poder saber si es un ingreso o un
    // egreso
    switch (caracter) {
    case '+':
      // Se añadimos 1 al contador para luego usarlo en el promedio
      contador_in++;

      printf("Factura de ingreso numero: %d\n ", contador_in);
      ingreso += valor;
      break;

    case '-':

      contador_out++;
      printf("Factura de egreso numero: %d \n", contador_out);
      egreso += valor;
      break;

    default:
      printf("Valor no valido.\n");
      break;
    };
  }

  printf("****************************************************************\n");
  printf("Resumen: \n");
  // operaciones para saber todos los resultados

  resultado = balance_ant + ingreso - egreso;
  printf("Resultado final:: %0.2f\n", resultado);

  printf("Total ingresos: %0.2f\n", ingreso);
  printf("Promedio ingresos: %0.2f\n", ingreso / contador_in);

  printf("Total egresos: %0.2f\n", egreso);
  printf("Promedio egresos: %0.2f\n", egreso / contador_out);

  printf("Total balance: %0.2f\n", balance_ant);

  return 0;
}
