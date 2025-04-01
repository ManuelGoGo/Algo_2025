

/*
Manuel Gonzalez CI 7920913
Enzo Liuzzi CI 5159825
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numero, nivel, respuesta, limite, cont = 0;

    srand(time(NULL)); // Iniciamos la semilla
    numero = rand() % 100 + 1; // Generamos el número aleatorio entre 1 y 100

    // Elección del nivel de dificultad
    do {
        printf("Escoja la dificultad con un número del 1 al 3: ");
        scanf("%d", &nivel);

        switch (nivel) {
            case 1:
                printf("Escogiste el Nivel 1: tienes 16 oportunidades.\n");
                limite = 16;
                break;
            case 2:
                printf("Escogiste el Nivel 2: tienes 10 oportunidades.\n");
                limite = 10;
                break;
            case 3:
                printf("Escogiste el Nivel 3: tienes 7 oportunidades.\n");
                limite = 7;
                break;
            default:
                printf("Número fuera de rango, intenta de nuevo.\n");
                limite = 0;
                break;
        }
    } while (limite == 0);

    // Juego de adivinanza con intentos limitados
    do {
        printf("Escoja un número entre 1 y 100: ");
        scanf("%d", &respuesta);

        cont++;

        if (respuesta < numero) {
            printf("El número es mayor.\n Este es tu intento %d.\n",cont);

        } else if (respuesta > numero) {
            printf("El número es menor.\n Este es tu intento %d.\n",cont);
        } else {
            printf("¡Felicidades! Adivinaste el número.\n");
            break;
        }

    } while (cont < limite);

    if (cont == limite && respuesta != numero) {
        printf("Lo siento, has agotado tus intentos. El número era %d.\n", numero);
    } else {
        printf("Te tomó %d intentos.\n", cont);
    }

    return 0;
}

