//Enzo Martin Liuzzi Cáceres 5159825
//Manuel Gonzalez 7920913
#include <stdio.h>
int main() {
    int altura, space, num, rnum;// Declamación de variables

    printf("Ingrese un numero entre 1 y 10: ");//solicitud de variables
    scanf("%d", &altura);

    if(altura>10 || altura<1){//comprobamos si esta en el rango asignado
      printf("El numero tiene que ser menor o igual a 10 y mayor o igual a 1.\n");
      return 0;
    }

    //se hace la pirámide
    for (space = 1; space <= altura; space++) {
        for (num = 1; num <= altura - space; num++) {
            printf(" ");
        }
       for (rnum = space; rnum >= 1; rnum--) {
            printf("%d", rnum);
        }
       for (rnum = 2; rnum <= space; rnum++) {
            printf("%d", rnum);
        }

        printf("\n");
    }
    return 0;
}
