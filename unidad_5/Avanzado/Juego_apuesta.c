#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Solicita un número entre mínimo y máximo, solo muestra mensajes si hay error
int pedir_numero_en_rango(int minimo, int maximo) {
    int numero;
    int resultado;

    while (1) {
        resultado = scanf("%d", &numero);

        if (resultado == 1) {
            if (numero >= minimo && numero <= maximo) {
                return numero;
            } else {
                printf("❌ Error: número fuera del rango permitido.\n");
                printf("Ingrese un número entre %d y %d: ", minimo, maximo);
            }
        } else {
            printf("❌ Error: entrada inválida, debe ser un número.\n");
            printf("Ingrese un número entre %d y %d: ", minimo, maximo);
        }

        limpiar_buffer(); // limpia lo que quedó en el buffer
    }
}
int aleatorio( int lim_inferior, int lim_sperior){
    if (lim_inferior == 0) lim_inferior = 0;
    return rand() % lim_sperior + lim_inferior;
}

int menor(int num1, int num2) {
    if (num1 == 0 && num2 == 0) return 0;        // Si ambos son 0, retorna 0
    else if (num1 == 0) return num2;             // Si num1 es 0, retorna num2
    else if (num2 == 0) return num1;             // Si num2 es 0, retorna num1
    else return (num1 < num2) ? num1 : num2;     // Ambos distintos de 0, retorna el menor
}


int main() {

    srand(time(NULL)); // Iniciamos la semilla

    int player1 =100000, player2 =100000,player3 =100000;
    int num1,num2,num3,num_ran;
    while(player1 > 0 && player2 >0 && player3 >0){

      int valu1=0,valu2=0,valu3=0;

      printf("Jugador 1 ingresa el numero: ");
      num1 = pedir_numero_en_rango(1, 10);

      printf("Jugador 2 ingresa el numero: ");
      num2 = pedir_numero_en_rango(1, 10);

      printf("Jugador 3 ingresa el numero: ");
      num3 = pedir_numero_en_rango(1, 10);


      int con = 1;
      for (con ; con <= 10; con++){

        num_ran = aleatorio(1,10);
        printf("Numero: %d.\n", num_ran);

        if(num1 == num_ran){
          valu1 = menor(con,valu1);
        }

        if(num2 == num_ran){
          valu2 = menor(con,valu2);
        }

        if(num3 == num_ran){
          valu3 = menor(con,valu3);
        }
      }

      if(valu1 == 0 && valu2 == 0 && valu3 == 0){
        printf("Todos fallaron. \n");
      }else if(valu1 == valu2 && valu2 == valu3){
        printf("Todos acertaron. \n");
      }else {
        int min = menor(menor(valu1, valu2), valu3);

       // Jugadores que acertaron en la menor posición
       int ganadores = 0;
       if (valu1 == min && min != 0) ganadores++;
       if (valu2 == min && min != 0) ganadores++;
       if (valu3 == min && min != 0) ganadores++;


       player1 -= 10000;
       player2 -= 10000;
       player3 -= 10000;

       int ganancia = 30000 / ganadores;

       if (valu1 == min && min != 0) {
          player1 += ganancia;
          printf("Jugador 1 gana %d Gs.\n", ganancia);
       }
       if (valu2 == min && min != 0) {
          player2 += ganancia;
          printf("Jugador 2 gana %d Gs.\n", ganancia);
       }
       if (valu3 == min && min != 0) {
          player3 += ganancia;
          printf("Jugador 3 gana %d Gs.\n", ganancia);
       }
     }
  }

  printf("\n--- JUEGO FINALIZADO ---\n");
  if (player1 = 0){
    printf("Jugador 1 se quedó sin dinero.\n");
  }else if(player1 < 0){
    printf("Jugador 1 una deuda de %d Gs.\n", player1);
  }else{
    printf("Jugador 1 tiene %d Gs.\n", player1);
  }

  if (player2 <= 0){
    printf("Jugador 2 se quedó sin dinero.\n");
  }else if(player1 < 0){
    printf("Jugador 2 una deuda de %d Gs.\n", player1);
  }else{
    printf("Jugador 2 tiene %d Gs.\n", player2);
  }

  if (player3 <= 0){
    printf("Jugador 3 se quedó sin dinero.\n");
  }else if(player1 < 0){
    printf("Jugador 3 una deuda de %d Gs.\n", player1);
  }else{
    printf("Jugador 3 tiene %d Gs.\n", player3);
  }

  return 0;
}
