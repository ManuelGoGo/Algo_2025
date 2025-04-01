




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int aleatorio( int lim_inferior, int lim_sperior){
      if (lim_inferior == 0) lim_inferior = 0;
    return rand() % lim_sperior + lim_inferior;
}

int main() {
    srand(time(NULL)); // Iniciamos la semilla
    int  ;



    return 0;
}
