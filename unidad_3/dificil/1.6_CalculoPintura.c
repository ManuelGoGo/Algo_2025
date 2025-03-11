/*
Manuel Gonzalez CI 7920913
Enzo Liuzzi CI 5159825
*/



#include <stdio.h>

int main(){
  // Declaramos las variables en flotante para aceptar dimensiones que no estén en números enteros 
  float a, h, litros;
  int nbalp,nbalm,nbalg,nbalx;

  printf("Introduzca el largo y ancho de la superficie que se va a pintar en metros:\n");
  scanf("%f%f",&a,&h);

  //Cálculos correspondientes
  litros = (a*h)/12;

  nbalx = (int)(litros/18);
  litros -= nbalx*18;

  printf("la cantidad de baldes de 18 es %d. \n", nbalx);

  nbalg = (int)(litros/12);
  litros -= nbalg*12;

  printf("la cantidad de baldes de 12 es %d. \n", nbalg);

  nbalm = (int)(litros/3.6);
  litros -= nbalm/3.6;


  nbalp = (int)(litros/1.5);
  litros -= nbalp/1.5;

  // Escojemos si combiene mas si usar dos de 1.5 o uno de 3.5 dependiendo del resto 
  if(litros <= 1.5){
    nbalp ++;
  }else if(litros > 1.5 && litros <3.6){
    nbalp +=2;
  }else{
    nbalm ++;
  }

  printf("la cantidad de baldes de 3.6 es %d. \n", nbalm);

  printf("la cantidad de baldes de 1.5 es %d. \n", nbalp);

  


  printf("La cantidad de baldes de pintura que se usara para pintar la pared es de %f. \n", litros);

  return 0;
}
