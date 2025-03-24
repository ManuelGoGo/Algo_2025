 #include <stdio.h>
#include <ctype.h>

int main() {
  char texto[100], codigo[100];
  int ascii;
  // Leer una cadena del usuario
  printf("Ingrese una frase codificada: ");
  fgets(texto, sizeof(texto), stdin);

  // Convertir a minúscula
  int idx;
  for ( idx = 0; texto[idx] != '\0'; idx++) {

      ascii = tolower(texto[idx] - 3);

      if (97 <= ascii){
          codigo[idx] = (char)(ascii);
        }else{
          codigo[idx] = (char)(ascii + 26);
        }
  }


  printf("Texto decodificado es: %s.\n ", codigo);


  return 0;
}
