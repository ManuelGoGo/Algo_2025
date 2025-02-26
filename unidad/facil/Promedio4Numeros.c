#include <stdio.h>

int main(){
    int a,b,c,d;
    printf("Escriba 4 números \n");
    scanf("%d%d%d%d",&a,&b,&c,&d);
    float p;
    p = (a+b+c+d)/4.0;
    printf("El promedio es: %.2f", p);


    return 0;
}