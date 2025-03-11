/*
Manuel Gonzalez CI 7920913
Enzo Liuzzi CI 5159825
*/


#include <stdio.h>
#include <math.h>

int main(){
  // Declaramos las variables en flotante para aceptar dimensiones que no estén en números enteros 
  float a, h, area,bal;

  printf("Introduzca el largo y ancho de la superficie que se va a pintar en metros:\n");
  scanf("%f%f",&a,&h);

  //Cálculos correspondientes
  area = a*h;
  // dividimos el area entre 12 para encontrar la cantidad de litros y luego 18 para encontrar la cantidad de baldes
  bal = ceil(area/(12.0*18.0));

  printf("La cantidad de baldes de pintura que se usara para pintar la pared es de %d. \n", (int)bal);

  return 0;
}
