#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char tipo[100];
  int idtipo;
  int nota;
} Examen;

typedef struct {
  int id;
  char nombre[100];
} Tipo;

typedef struct {
  int primerParcial;
  int segundoParcial;
  int tercerParcial;
  int primerFinal;
  int segundoFinal;
} Puntaje;

typedef struct {
  int Id;
  char nombre[50];
  char apellido[50];
  char carrera[100];
  Puntaje puntaje;
} Alumno;

int leer_alumno(char *archivo, Alumno alumnos[]) {
  FILE *fp = fopen(archivo, "r");
  if (fp == NULL) {
    printf("No se pudo abrir el archivo.\n");
    return 0;
  }

  char linea[200];
  int contador = 0;

  while (fgets(linea, sizeof(linea), fp)) {
    linea[strcspn(linea, "\n")] = '\0'; // Eliminar el salto de línea

    char nombreCompleto[100];
    Alumno *a = &alumnos[contador];

    if (sscanf(linea, "%d, %[A-Za-z ] , %[^\n]", &a->Id, nombreCompleto,
               a->carrera) == 3) {
      // Separar nombre y apellido desde el último espacio
      char *apellidoPtr = strrchr(nombreCompleto, ' ');
      if (apellidoPtr != NULL) {
        *apellidoPtr = '\0'; // Termina el nombre
        apellidoPtr++;       // Apunta al inicio del apellido
        strcpy(a->nombre, nombreCompleto);
        strcpy(a->apellido, apellidoPtr);
      } else {
        strcpy(a->nombre, nombreCompleto);
        a->apellido[0] = '\0';
      }

      contador++;
      if (contador >= 100)
        break;
    }
  }

  fclose(fp);
  return contador;
}

int obtener_tipos(char *archivo, Tipo tipos[], int max) {
  FILE *fp = fopen(archivo, "r");
  if (fp == NULL) {
    printf("No se pudo abrir el archivo.\n");
    return 0;
  }

  Tipo tipoExamen;
  int contador = 0;

  while (fscanf(fp, "%d, %[^\n]\n", &tipoExamen.id, tipoExamen.nombre) == 2) {
    if (contador >= max)
      break;

    tipos[contador] = tipoExamen;
    contador++;
  }

  fclose(fp);
  return contador;
}

int leer_examene(char *archivo, Examen examenes[], int max) {
  FILE *fp = fopen(archivo, "r");
  if (fp == NULL) {
    printf("No se pudo abrir el archivo.\n");
    return 0;
  }
  Examen examen;
  char linea[200];
  int contador = 0;

  int idTipo;
  Tipo tipos[100];
  int totalTipo = obtener_tipos("tipo_examen.txt", tipos, 100);

  while (fscanf(fp, "%d,%d,%d\n", &examen.id, &idTipo, &examen.nota) == 3) {
    if (examen.nota > 100 || examen.nota < 0) {
      printf("Error: un examen tiene más de 100 puntos (ID: %d).\n", examen.id);
      exit(1);
    }
    //    printf("DEBUG - Cargado examen ID: %d, Tipo: %d, Nota: %d\n",
    //    examen.id,
    //          idTipo, examen.nota);

    // Buscar el nombre del tipo
    int encontrado = 0;
    for (int i = 0; i < totalTipo; i++) {
      if (tipos[i].id == idTipo) {
        strcpy(examen.tipo, tipos[i].nombre);
        encontrado = 1;
        break;
      }
    }

    if (!encontrado) {
      strcpy(examen.tipo, "Desconocido");
    }

    //  printf("DEBUG - Cargado examen desde el struct: %d, Tipo: %s, Nota:
    //  %d\n",
    //        examen.id, examen.tipo, examen.nota);
    examen.idtipo = idTipo;
    examenes[contador] = examen;
    contador++;
    if (contador >= max)
      break;
  }
  return contador;
}

void output_estadisticas(Alumno alumnos[], int totalAlumnos, char *archivo) {
  FILE *fp = fopen(archivo, "w"); // "w" crea el archivo si no existe
  if (fp == NULL) {
    printf("Error: No se pudo crear el archivo '%s'.\n", archivo);
    return;
  }

  fprintf(fp, "Estadisticas de la materia:\n");
  fprintf(fp, "Cantidad de alumnos: %d:\n",
          totalAlumnos); // Cantidad de alumnos

  int totalAplazados = 0;
  int totalPrimerFinal = 0;

  for (int a = 0; a < totalAlumnos; a++) {
    if (alumnos[a].puntaje.primerFinal >= 60) {
      printf("Alumno %d: %s aprobo el primer final\n", alumnos[a].Id,
             alumnos[a].nombre);
      totalPrimerFinal++;
    }
  }
  fprintf(fp, "Cantidad de alumnos que aprobaron en primer final: %d\n",
          totalPrimerFinal);
}
/*estadı́sticas de la materia:
Cantidad de alumnos que aprobaron en primer final: X
Cantidad de alumnos que aprobaron en segundo final: X
Cantidad de alumnos que no rindieron final, ni el primero, ni el segundo: X
Cantidad de alumnos que aprobaron la materia por carrera: X
Porcentaje de almunos aprobados: X
Porcentaje de almunos aplazados: X
Promedio general de calificaciones de la materia: X
*/

void cargar_notas(Alumno alumno[], int totalAlumnos, Examen examene[],
                  int totalExamenes) {
  for (int alu = 0; alu < totalAlumnos; alu++) {
    for (int ex = 0; ex < totalExamenes; ex++) {
      if (alumno[alu].Id == examene[ex].id) {
        switch (examene[ex].idtipo) {
        case 1:
          alumno[alu].puntaje.primerParcial = examene[ex].nota;
          break;
        case 2:
          alumno[alu].puntaje.segundoParcial = examene[ex].nota;
          break;
        case 3:
          alumno[alu].puntaje.tercerParcial = examene[ex].nota;
          break;
        case 4:
          alumno[alu].puntaje.primerFinal = examene[ex].nota;
          break;
        case 5:
          alumno[alu].puntaje.segundoFinal = examene[ex].nota;
          break;
        }
      }
    }
  }
}
int main() {
  Alumno alumnos[100];
  Examen examenes[100];
  int totalAlumnos = leer_alumno("alumnos.txt", alumnos);
  int totalExamenes = leer_examene("notas.txt", examenes, 100);

  cargar_notas(alumnos, totalAlumnos, examenes, totalExamenes);

  output_estadisticas(alumnos, totalAlumnos, "estadisticas.txt");
  // Ejemplo: imprimir todos los alumnos
  for (int i = 0; i < totalAlumnos; i++) {
    printf("Alumno #%d: %s %s - %s\n", alumnos[i].Id, alumnos[i].nombre,
           alumnos[i].apellido, alumnos[i].carrera);
  }

  for (int i = 0; i < totalExamenes; i++) {
    printf("Examen id %d: tipo %s, nota %d\n", examenes[i].id, examenes[i].tipo,
           examenes[i].nota);
  }

  return 0;
}
