/*
Por su mes aniversario, una empresa que fabrica gaseosas está ofreciendo premios a sus clientes. Los
premios consisten en una botella de sus gaseosas en sus diferentes sabores. La empresa cuenta con 6
sabores de gaseosas. Los premios están marcados en las tapas de las gaseosas que compran los clientes.
Las opciones impresas en las tapas son las siguientes:

• 0: sigue comprando
• 1: ganaste una gaseosa del sabor 1.
• 2: ganaste una gaseosa del sabor 2.
• 3: ganaste una gaseosa del sabor 3.
• 4: ganaste una gaseosa del sabor 4.
• 5: ganaste una gaseosa del sabor 5.
• 6: ganaste una gaseosa del sabor 6.

La empresa necesita saber cuántas gaseosas deberán comprar los clientes para obtener como premio
los 6 sabores de las gaseosas.

Escribir un programa en C que realice la simulación de los premios obtenidos por los clientes. Se
deberán generar números aleatorios del 0 al 6. El programa deberá contar la cantidad de números que
se van generando. Cuando hayan aparecido todos los números desde el 1 hasta el 6 termina la
simulación considerando, que ya han aparecido los 6 sabores de las gaseosas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int aleatorio( int lim_inferior, int lim_sperior){
    if (lim_inferior == 0) lim_inferior = 0;
    return rand() % lim_sperior + lim_inferior;
}

int main() {
    int sabor1=0,sabor2=0,sabor3=0, sabor4=0,sabor5=0,sabor6=0;

    srand(time(NULL)); // Iniciamos la semilla

    while (sabor1 == 0 ||sabor2 == 0 ||sabor3 == 0 || 
        sabor4 == 0 || sabor5 == 0 || sabor6 == 0){

      switch (aleatorio(0,7)) {
        case 1:
            sabor1 += 1;
            break;

        case 2:

            sabor2 += 1;
            break;

        case 3:

            sabor3 += 1;
            break;

        case 4:

            sabor4 += 1;
            break;
        case 5:

            sabor5 += 1;
            break;
        case 6:

            sabor6 += 1;
            break;
        default:
            printf("Salio 0.\n");

        }
    }

    
  printf("La cantidad de sabor 1 es %d. \n", sabor1);
  printf("La cantidad de sabor 2 es %d. \n", sabor2);
  printf("La cantidad de sabor 3 es %d. \n", sabor3);
  printf("La cantidad de sabor 4 es %d. \n", sabor4);
  printf("La cantidad de sabor 5 es %d. \n", sabor5);
  printf("La cantidad de sabor 6 es %d. \n", sabor6);

return 0;
}
