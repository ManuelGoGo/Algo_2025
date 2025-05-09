#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int aleatorio(int lim_inferior, int lim_sperior) {
  if (lim_inferior == 0)
    lim_inferior = 0;
  return rand() % lim_sperior + lim_inferior;
}
void limpiar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

int entero_valido(const char *cadena) {
  if (cadena == NULL || *cadena == '\0')
    return 0;

  int i = 0;

  // Permitir signo negativo en la primera posición
  if (cadena[0] == '-')
    i++;

  for (; cadena[i] != '\0'; i++) {
    if (!isdigit(cadena[i]))
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
    entrada[strcspn(entrada, "\n")] = '\0'; // Quitar salto de línea

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

    if ((numero >= minimo) && (maximo <= 0 || numero <= maximo)) {
      limpiar_buffer();
      return numero;
    } else {
      printf("❌ Error: número fuera del rango permitido.\n");
    }

    if (maximo > 0) {
      printf("Ingrese un número entre %.2f y %.2f: ", minimo, maximo);
    } else {
      printf("Ingrese un número mayor o igual a %.2f: ", minimo);
    }

    limpiar_buffer(); // descarta entrada inválida
  }
}

// Función para validar si una cadena tiene solo caracteres alfabéticos (texto)
int texto_valido(char entrada[]) {
  for (int i = 0; entrada[i] != '\0'; i++) {
    if (!isalpha(entrada[i]) && entrada[i] != ' ') {
      return 0; // Si encuentra algo que no es letra o espacio, no es válido
    }
  }
  return 1;
}

// Función para pedir texto válido
void pedir_texto_valido(char texto[], int longitud_maxima) {
  char entrada[longitud_maxima];
  int valido = 0;

  printf("%s: ", texto);

  while (!valido) {
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // Eliminar salto de línea

    // Verificar si la entrada es válida
    if (!texto_valido(entrada)) {
      printf("❌ Error: solo se permiten letras y espacios.\n");
    } else {
      valido = 1;
    }

    if (!valido) {
      printf("%s: ", texto); // Repetir el mensaje si la entrada es inválida
    }
  }

  // Copiar la entrada validada a la variable de texto
  strncpy(texto, entrada, longitud_maxima);
}

int texto_alfanumerico(char entrada[]) {
  for (int i = 0; entrada[i] != '\0'; i++) {
    // Verificar si el carácter no es alfanumérico ni espacio
    if (!(isalnum(entrada[i]) || entrada[i] == ' ')) {
      return 0; // Si se encuentra un carácter especial, no es válido
    }
  }
  return 1; // Todos los caracteres son válidos
}

void pedir_texto_sin_caracteres_especiales(char texto[], int longitud_maxima) {
  char entrada[longitud_maxima];
  int valido = 0;

  printf("%s: ", texto);

  while (!valido) {
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // Eliminar salto de línea

    // Verificar si la entrada no contiene caracteres especiales
    if (!texto_alfanumerico(entrada)) {
      printf("❌ Error: solo se permiten letras, números y espacios. No se "
             "permiten caracteres especiales.\n");
    } else {
      valido = 1;
    }

    if (!valido) {
      printf("%s: ", texto); // Repetir el mensaje si la entrada es inválida
    }
  }

  // Copiar la entrada validada a la variable de texto
  strncpy(texto, entrada, longitud_maxima);
}
struct Fecha {
  int dia;
  int mes;
  int anio;
};
struct Movimiento {

  int movimiento; // 2 deposito, 1 extraccion
  float monto;
  struct Fecha fecha;
};

typedef struct {
  int numeroCuenta;
  int tipo; // 2 para ahorro, 1 para corriente
  float saldoInicial;
  // Datos calculados
  int numMovimientos;
  struct Movimiento movimiento[10];
  float saldoActual;
} Cuenta;

typedef struct {
  char nombre[50];
  char apellido[50];
  int documento;
  int telefono;
  int numCliente;
  Cuenta cuenta;
} Cliente;

// FUnciones principales

void registrar_cliente(Cliente clientes[], int *numClientes) {
  // Ejemplo: llenar el siguiente índice del arreglo
  if (*numClientes < 10) {
    printf("Ingrese nombre del cliente: ");
    pedir_texto_valido(clientes[*numClientes].nombre, 50);

    printf("Ingrese apellido del cliente: ");
    pedir_texto_valido(clientes[*numClientes].apellido, 50);

    printf("Ingrese documento del cliente(puede contener letras y numeros): ");
    clientes[*numClientes].documento = pedir_numero(1, 0);

    printf("Ingrese teléfono del cliente: ");
    clientes[*numClientes].telefono = pedir_numero(1, 0);

    clientes[*numClientes].numCliente = *numClientes;
    (*numClientes)++; // aumentar el número de clientes registrados
  } else {
    printf("❌ Límite de clientes alcanzado.\n");
  }
}

int selec_cliente(Cliente clientes[], int totalClientes) {
  printf("Seleccione un cliente: \n");
  for (int i = 0; i < totalClientes; i++) {
    printf("%d) %s %s\n", i + 1, clientes[i].nombre, clientes[i].apellido);
  }
  return pedir_numero(1, totalClientes) - 1;
}

void registrar_cuenta(Cliente clientes[], int selecCliente, int totalClientes) {

  printf("\nNombre de cliente seleccionado: %s %s\n",
         clientes[selecCliente].nombre, clientes[selecCliente].apellido);

  printf("Ingrese la denominación de la cuenta (1 para ahorro, 2 para "
         "corriente): ");

  clientes[selecCliente].cuenta.tipo = pedir_numero(1, 2);
  printf("Ingrese el saldo inicial de la cuenta: ");
  float saldoInicial = pedir_float(0.01, 0);

  clientes[selecCliente].cuenta.saldoInicial = saldoInicial;
  clientes[selecCliente].cuenta.saldoActual = saldoInicial;

  while (clientes[selecCliente].cuenta.numeroCuenta ==
         0) { // gneramos de manera aleatoria
              // un numero de cuenta que no se repita
    int numCuenta = aleatorio(1, 999999);
    for (int i = 0; i < totalClientes; i++) {
      if (numCuenta == clientes[i].cuenta.numeroCuenta) {
        numCuenta = aleatorio(1, 999999);
        i = 0;
      }
    }

    printf("\nSu numero de cuenta es: %d\n", numCuenta);
    clientes[selecCliente].cuenta.numeroCuenta = numCuenta;
  }
}

int es_bisiesto(int anio) {
  return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

// Devuelve el número de días del mes
int dias_del_mes(int mes, int anio) {
  switch (mes) {
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 10:
  case 12:
    return 31;
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  case 2:
    return es_bisiesto(anio) ? 29 : 28;
  default:
    return 0;
  }
}

// Pide una fecha válida al usuario
struct Fecha pedir_fecha() {
  struct Fecha fecha;
  int diasMes;

  while (1) {
    printf("Ingrese la fecha (DD MM AAAA): ");
    fecha.dia = pedir_numero(1, 31);
    fecha.mes = pedir_numero(1, 12);
    fecha.anio = pedir_numero(1000, 9999);

    if (fecha.anio < 1 || fecha.mes < 1 || fecha.mes > 12) {
      printf("❌ Fecha inválida. Intente de nuevo.\n");
      continue;
    }

    diasMes = dias_del_mes(fecha.mes, fecha.anio);

    if (fecha.dia < 1 || fecha.dia > diasMes) {
      printf("❌ Día inválido para ese mes. Intente de nuevo.\n");
      continue;
    }

    break; // fecha válida
  }

  return fecha;
}

void registrar_movimiento(Cliente clientes[], int selecCliente) {
  int indice = clientes[selecCliente].cuenta.numMovimientos;

  printf("\nNombre de cliente seleccionado: %s %s\n",
         clientes[selecCliente].nombre, clientes[selecCliente].apellido);

  printf("Ingrese el movimiento (2 para deposito, 1 para extraccion): ");
  int movimiento = pedir_numero(1, 2);
  clientes[selecCliente].cuenta.movimiento[indice].movimiento = movimiento;

  // Pide la fecha
  clientes[selecCliente].cuenta.movimiento[indice].fecha = pedir_fecha();

  printf("Ingrese el monto: ");
  float monto = pedir_float(0.01, 0);

  if (movimiento == 2) {
    clientes[selecCliente].cuenta.saldoActual += monto;
  } else if (monto <= clientes[selecCliente].cuenta.saldoActual) {
    clientes[selecCliente].cuenta.saldoActual -= monto;
  } else {
    printf("❌ Saldo insuficiente para la extracción.\n");
    return; // no se registra el movimiento
  }

  clientes[selecCliente].cuenta.movimiento[indice].monto = monto;
  clientes[selecCliente].cuenta.numMovimientos++;
  printf("Movimiento registrado con éxito. Nuevo saldo: %.2f\n",
         clientes[selecCliente].cuenta.saldoActual);
};

void imprimir_extracto(Cliente clientes[], int selecCliente) {
  printf("\nNombre de cliente seleccionado: %s %s\n",
         clientes[selecCliente].nombre, clientes[selecCliente].apellido);

  printf("Extracto de cuenta:\n");
  for (int i = 0; i < clientes[selecCliente].cuenta.numMovimientos; i++) {
    struct Movimiento mov = clientes[selecCliente].cuenta.movimiento[i];

    printf("Movimiento %d - Fecha: %02d/%02d/%04d: ", i + 1, mov.fecha.dia,
           mov.fecha.mes, mov.fecha.anio);

    if (mov.movimiento == 2) {
      printf("Depósito de %.2f\n", mov.monto);
    } else {
      printf("Extracción de %.2f\n", mov.monto);
    }
  }
}

int main() {
  Cliente clientes[10];
  int totalClientes = 0;
  srand(time(NULL)); // Iniciamos la semilla

  while (1) {
    printf("\nSeleccione una opcion:\n"
           "1. Registrar cliente\n"
           "2. Registrar cuenta\n"
           "3. Registrar movimiento\n"
           "4. Imprimir saldo\n"
           "5. Imprimir extracto de cuenta\n"
           "6. Salir\n");

    int opcion = pedir_numero(1, 6);

    switch (opcion) {
    case 1: // Registrar cliente
      printf("Registrar cliente.\n");
      registrar_cliente(clientes, &totalClientes);
      break;
    case 2: // Registrar cuenta
      if (totalClientes != 0) {
        printf("\nRegistrar cuenta.\n");
        int selecCliente = selec_cliente(clientes, totalClientes);
        if (clientes[selecCliente].cuenta.tipo == 0) {
          registrar_cuenta(clientes, selecCliente, totalClientes);
          printf("\nSe a guardado con exito la cuenta.\n");
        } else {
          printf("\n❌ El cliente seleccionado ya tiene una cuenta.\n");
        }
      } else {
        printf("❌ No hay clientes registrados.\n");
      }

      break;
    case 3: // Registrar Movimiento
      printf("Registrar Movimiento\n");
      if (totalClientes != 0) {

        printf(
            "Seleccione el cliente en el que desea registrar el movimiento.\n");
        int selecCliente = selec_cliente(clientes, totalClientes);

        if (clientes[selecCliente].cuenta.tipo == 1 ||
            clientes[selecCliente].cuenta.tipo == 2) {
          if (clientes[selecCliente].cuenta.numMovimientos < 10) {
            registrar_movimiento(clientes, selecCliente);
          } else {
            printf(
                "El cliente seleccionado alcanzo el limite de movimientos.\n");
          }
        } else {
          printf("\n❌ El cliente seleccionado no tiene una cuenta.\n");
        }

      } else {
        printf("❌ No hay clientes registrados.\n");
      }

      break;
    case 4: // Imprimir Saldo
      printf("Imprimir Saldo\n");
      if (totalClientes != 0) {

        printf("Seleccione el cliente en el que desea consultar el saldo.\n");
        int selecCliente = selec_cliente(clientes, totalClientes);

        if (clientes[selecCliente].cuenta.tipo == 1 ||
            clientes[selecCliente].cuenta.tipo == 2) {
          printf("\nCliente: %s %s\n", clientes[selecCliente].nombre,
                 clientes[selecCliente].apellido);

          printf("Saldo actual de la cuenta: $%.2f\n\n",
                 clientes[selecCliente].cuenta.saldoActual);
        } else {
          printf("❌ El cliente seleccionado no tiene una cuenta.\n");
        }

      } else {
        printf("❌ No hay clientes registrados.\n");
      }
      break;
    case 5: // Imprimir extracto de cuenta

      printf("Imprimir extractos de cuenta\n");
      if (totalClientes != 0) {
        printf("Seleccione el cliente en el que desea consultar el saldo.\n");
        int selecCliente = selec_cliente(clientes, totalClientes);

        if (clientes[selecCliente].cuenta.tipo == 1 ||
            clientes[selecCliente].cuenta.tipo == 2) {
          if (clientes[selecCliente].cuenta.numMovimientos > 0) {
            imprimir_extracto(clientes, selecCliente);
          } else {
            printf("📭 El cliente seleccionado aún no tiene movimientos "
                   "registrados.\n");
          }
        } else {
          printf("❌ El cliente seleccionado no tiene una cuenta.\n");
        }
      } else {
        printf("❌ No hay clientes registrados.\n");
      }
      break;
    case 6: // Salir
      printf("Salir del sistema\n");
      return 0;
      break;
    }
  }

  return 0;
}
