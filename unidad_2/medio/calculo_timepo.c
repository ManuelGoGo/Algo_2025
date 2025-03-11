/*Escribir un programa que permita leer un número y determine cuántos años, meses y dı́as
contiene el número leı́do e.g. 465 posee 1 año, 3 meses y 10 dı́as. */


#include <stdio.h>


int main()
{
    int n,año, mes, dia;
    printf("Introdusca el numero que quere calcular en años, meses y días.\n Considerando que el año es de 365 días y el mes de 30: ");
    scanf("%d",&n); // solicitamos un entero sin signo ya que siempre va a ser positivo.

    año = n/365;
    mes = (n%365)/30;
    dia = (n%365)%30;

    printf("El número leído %d contiene %d años,%d meses y %d días.  \n",n, año,mes,dia);

    return 0;
}
