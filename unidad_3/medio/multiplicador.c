//Escribir un programa que solicite un número e imprima todos los números múltiplos de dicho
//número, menores a 171.

#include <stdio.h>


int main() {
  printf("Hola");


  int i,numero;

  printf("Ingrese en numero a que desea dividir.\n");
  scanf("%d",&numero);
  while(&numero != ){

  printf("El dato de entrada tiene que ser un numero entero.\n");
  scanf("%d",&numero);
  }

  for(i=1;i<=171;i++){

    if( numero%i == 0){

      printf("%d es divisible por %d \n",numero,i);

    }


  }

  return 0;
}
