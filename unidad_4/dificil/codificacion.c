#include <stdio.h>
#include <ctype.h>

int main() {
    char texto[100], codigo[100];
    int ascii;
    // Leer una cadena del usuario
    printf("Ingrese una frase: ");
    fgets(texto, sizeof(texto), stdin);

    // Convertir a minúsculas y cifrar con desplazamiento de 3
    int idx;
    for (idx = 0; texto[idx] != '\0' && texto[idx] != '\n'; idx++) {
        // Convertir a mayúsculas y desplazar 3 posiciones en ASCII
        ascii = toupper(texto[idx]) + 3;

        if (ascii <= 90){
          codigo[idx] = (char)(ascii);
        }else{
          codigo[idx] = (char)(ascii - 26);
        }
    }
    for (int idx = 0; texto[idx] != '\0'; idx++) {
        codigo[idx] = tolower(codigo[idx]);
    }


    // Imprimir el texto cifrado
    printf("\nTexto en codigo: %s \n", codigo);


      return 0;
}
