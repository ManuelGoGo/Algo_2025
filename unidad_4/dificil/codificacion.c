/*
Manuel Gonzalez CI 7920913
Enzo Liuzzi CI 5159825
*/
#include <stdio.h>
#include <ctype.h>

int main() {
    char texto[100], codigo[100];
    int ascii,posi;


    printf("Ingrese la cantidad de desplazamientos: ");
    scanf("%d", &posi);
    getchar();

    // Leer una cadena del usuario
    printf("Ingrese una frase: ");
    fgets(texto, sizeof(texto), stdin);

    // Convertir a minúsculas y cifrar con desplazamiento de posi
    int idx;
    for (idx = 0; texto[idx] != '\0' && texto[idx] != '\n'; idx++) {

      if (isalpha(texto[idx])) { 
            // Convertir a mayúsculas y desplazar en ASCII
            ascii = toupper(texto[idx]) - 'A'; // 0 a 25
            ascii = (ascii + posi) % 26;       // Mantener dentro de 0-25
            codigo[idx] = tolower(ascii + 'A'); // Convertir de vuelta a char
        } else {
            // Mantener espacios y otros caracteres sin cifrar
            codigo[idx] = texto[idx];
        }
    }

    texto[idx] = '\0';  // Asegurar que la cadena termine correctamente

    // Imprimir el texto cifrado
    printf("\nTexto en codigo: %s \n", codigo);

    return 0;
}
