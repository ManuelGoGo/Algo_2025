/*
Manuel Gonzalez CI 7920913
Enzo Liuzzi CI 5159825
*/


#include <stdio.h>
#include <math.h>

int main(){
  // Declaramos las variables en flotante para aceptar dimensiones que no estén en números enteros 
  float a, h, bal, litros;
  float nbalp,nbalm,nbalg,nbalx;
  
  printf("Introduzca el largo y ancho de la superficie que se va a pintar en metros:\n");
  scanf("%f%f",&a,&h);

  //Cálculos correspondientes
  litros = (a*h)/12;

  nbalx = (int)(litros/18);
  litros = litros%18;

  nbalg = (int)(litros/12);
  litros = litros%%12;

  nbalm = (int)(litros/3.6);
  litros = litros%3.6;

  nbalp = (int)(litros/3.6);
  litros = litros%3.6;


  printf("La cantidad de baldes de pintura que se usara para pintar la pared es de %d. \n", nbalm);

  return 0;
}
