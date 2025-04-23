
#include <stdio.h>

int main() {

  int a, b, c;
  printf("Introdisca un valor para encontrar el resto\n");
  scanf("%d", &a);
  printf("Introdisca un valor para dividir\n");
  scanf("%d", &b);
  c = a % b;

  printf("El resto es  %d.\n", (int)a);

  return 0;
}
