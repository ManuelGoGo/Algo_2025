#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int aleatorio( int lim_inferior, int lim_sperior){
    if (lim_inferior == 0) lim_inferior = 0;
    return rand() % lim_sperior + lim_inferior;
}

int main() {
  int repeticiones;

  srand(time(NULL)); // Iniciamos la semilla
  printf("Cuantas simulaciones queres hacer.");

  scanf("%d", &repeticiones);

  for(int simulaciones=1; simulaciones<repeticiones+1;simulaciones +=1){

    int un_confiesan=0, dos_confiesan=0, no_confiesan=0;

    for(int cont=0;cont < 50;cont += 1){

      switch (aleatorio(1,3)) {
        case 1:
            un_confiesan += 1;
            break;

        case 2:

            dos_confiesan += 1;
            break;

        case 3:

            no_confiesan  += 1;
            break;
      }

    }

  printf("---------------------------------------- \n");
  printf("Simulacion numero: %d. \n", simulaciones);
  printf("Uno confesaron: %d. \n", un_confiesan);
  printf("Dos confesaron: %d. \n", dos_confiesan);
  printf("Ninguno confesaron: %d. \n", no_confiesan);
}


  return 0;
}
