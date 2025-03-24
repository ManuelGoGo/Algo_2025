//Escribir un programa que solicite al usuario un número entero menor a 100 y retorne si el
//número es primo o no.

#include <stdio.h>
#include <math.h>

int main() {
  printf("Hola");


  int i,numero;

  printf("Ingrese en numero menor a 100 para saber si es primo o no.\n");
  scanf("%d",&numero);

  while(numero >= 100){

  printf("El dato de entrada tiene que ser un numero entero menor que 100.\n");
  scanf("%d",&numero);
  }

  int status = 1;
  int r = sqrt(numero);

  if(numero == 0){
    status = 0;
  }else if(numero%2 == 0 && numero !=2){
    status = 0;
  }else if(numero%3 == 0 && numero !=3){
    status = 0;
  }else{
    for(i=5;i<=r;i++){
      if(i%2 != 0 && i%3 != 0){
        if(numero % i == 0){
         status = 0;
         break;
        }
      }
    }
  }

  if(status){
    printf("EL numero %d es primo.\n",numero);
  }else{
    printf("EL numero %d no es primo.\n",numero);
  }
  return 0;
}
