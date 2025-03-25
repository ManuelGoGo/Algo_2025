/*
Manuel Gonzalez CI 7920913
Enzo Liuzzi CI 5159825
*/

#include <stdio.h>
#include <ctype.h>

int main() {
    char texto[100], codigo[100];
    int ascii, posi;

    // Leer la cantidad de desplazamientos
    printf("Ingrese la cantidad de desplazamientos: ");
    scanf("%d", &posi);
    getchar();  // Limpiar el salto de línea del buffer
    posi = posi % 26;

    // Leer una cadena codificada del usuario
    printf("Ingrese una frase codificada: ");
    fgets(codigo, sizeof(codigo), stdin);

    // Decodificar
    int idx;
    for (idx = 0; codigo[idx] != '\0' && codigo[idx] != '\n'; idx++) {
        if (isalpha(codigo[idx])) {

            // Convertir a mayúsculas y aplicar el desplazamiento inverso
            ascii = toupper(codigo[idx]) - 'A';  // 0 a 25

            // Restar desplazamiento y asegurar que el resultado esté dentro del rango
            ascii = (ascii - posi + 26) % 26;

            // Volver a minúsculas para el resultado final
            texto[idx] = tolower(ascii + 'A');
        } else {
            // Mantener símbolos y espacios sin cambios
            texto[idx] = codigo[idx];
        }
    }

    texto[idx] = '\0';  // Asegurar que la cadena termine correctamente

    // Imprimir el texto decodificado
    printf("Texto decodificado es: %s\n", texto);

    return 0;
}

