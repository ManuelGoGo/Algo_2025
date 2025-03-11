
/*Escribe un programa que pregunte el precio, el tanto por ciento de descuento, y te diga el
precio con descuento. Por ejemplo, si el precio que introduce el usuario es 300 y el descuento
20, el programa dirá que el precio final con descuento es de 240.*/


#include <stdio.h>

int main()
{
    float precio, descuento,final;
    // pedida de datos al usuario 
    printf("Introdusca el precio del producto\n");
    scanf("%f", &precio);
    printf("Introdisca el numero porcentual del descuento.(no es necesario %%)\n");
    scanf("%f", &descuento);
    // calculo de precio final 
    final = precio*(descuento/100);
    printf("El precio final con el descuento es de %f\n", final);
    
    return 0;
}
