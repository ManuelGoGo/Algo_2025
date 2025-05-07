#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char tipo[50];
  int nota;
  int id;
} Examen;

typedef struct {
  int codigo;
  int tipo;
  int puntaje;
} Nota;

typedef struct {
  int Id;
  char nombre[50];
} Carrera;

typedef struct {
  int Id;
  char nombre[50];
  char apellido[50];
  Carrera carrera;
  Examen examen[10];
  int numExamen;
} Alumno;

Alumno *agregar_alumno(Alumno *lista, int *capacidad, int *total,
                       Alumno nuevo) {
  if (*total >= *capacidad) {
    *capacidad = (*capacidad == 0)
                     ? 2
                     : (*capacidad * 2); // Soporta capacidad inicial cero
    Alumno *nueva_lista = realloc(lista, (*capacidad) * sizeof(Alumno));
    if (!nueva_lista) {
      printf("❌ Error al redimensionar la lista\n");
      exit(EXIT_FAILURE);
    }
    lista = nueva_lista;
  }

  lista[*total] = nuevo;
  (*total)++;
  return lista;
}

int leer_alumnos(const char *archivo, Alumno **lista, int *capacidad) {
  FILE *f = fopen(archivo, "r");
  if (!f) {
    printf("❌ Error al abrir el archivo.\n");
    return 0;
  }

  char linea[256];
  int total = 0;

  while (fgets(linea, sizeof(linea), f)) {
    Alumno nuevo;
    char *token;

    // ID
    token = strtok(linea, ",");
    if (!token)
      continue;
    nuevo.Id = atoi(token);

    // Nombre y apellido
    token = strtok(NULL, ",");
    if (!token)
      continue;
    sscanf(token, " %49s %49s", nuevo.nombre, nuevo.apellido);

    // Carrera
    token = strtok(NULL, "\n");
    if (!token)
      continue;
    strncpy(nuevo.carrera.nombre, token, sizeof(nuevo.carrera.nombre) - 1);
    nuevo.carrera.nombre[sizeof(nuevo.carrera.nombre) - 1] = '\0';

    *lista = agregar_alumno(*lista, capacidad, &total, nuevo);
  }

  fclose(f);
  return total;
}

void cargar_examenes(const char *archivo, Alumno *alumnos, int total) {
  Nota nota;
  FILE *f = fopen(archivo, "r");
  if (!f) {
    printf("❌ Error al abrir el archivo.\n");
    return;
  }

  while (fscanf(f, "%d %d %d", &nota.codigo, &nota.tipo, &nota.puntaje) == 3) {
    for (int i = 0; i < total; i++) {
      if (alumnos[i].Id == nota.codigo) {
        int idx = alumnos[i].numExamen;
        if (idx < 10) { // evitar desbordamiento
          alumnos[i].examen[idx].id = nota.codigo;
          alumnos[i].examen[idx].nota = nota.puntaje;
          alumnos[i].examen[idx].tipo = nota.tipo;
          alumnos[i].numExamen++;
        }
        break;
      }
    }
  }

  fclose(f);
}
int main() {
  Alumno *lista = NULL;
  int capacidad = 0;

  int total = leer_alumnos("alumnos.txt", &lista, &capacidad);

  printf("Se leyeron %d alumnos:\n\n", total);

  for (int i = 0; i < total; i++) {
    printf("• %s %s - %s\n", lista[i].nombre, lista[i].apellido,
           lista[i].carrera.nombre);
  }

  cargar_examenes("nota.txt", lista, total);

  free(lista);
  return 0;
}
