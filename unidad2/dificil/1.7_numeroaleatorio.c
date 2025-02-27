
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){

  int numero;
  
  srand(time(NULL));// iniciamos la semilla
  numero = rand() % 100;//generamos el numero seudoaleatorio

  printf("El numero es %d\n",numero);
  return 0;
}
