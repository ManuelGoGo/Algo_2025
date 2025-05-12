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

typedef struct {
  char carrera[100];
  int cantidadAprobados;
  int cantidadInscritos;
} CarreraEstadistica;

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
    Alumno *alu = &alumnos[contador];

    // Inicializar puntajes en -1
    alu->puntaje.primerParcial = -1;
    alu->puntaje.segundoParcial = -1;
    alu->puntaje.tercerParcial = -1;
    alu->puntaje.primerFinal = -1;
    alu->puntaje.segundoFinal = -1;
    // Exprecion regular que extrae los datos
    if (sscanf(linea, "%d, %[A-Za-z ] , %[^\n]", &alu->Id, nombreCompleto,
               alu->carrera) == 3) {
      // Separar nombre y apellido desde el último espacio
      char *apellidoPtr = strrchr(nombreCompleto, ' ');
      if (apellidoPtr != NULL) {
        *apellidoPtr = '\0'; // Termina el nombre
        apellidoPtr++;       // Apunta al inicio del apellido
        strcpy(alu->nombre, nombreCompleto);
        strcpy(alu->apellido, apellidoPtr);
      } else {
        strcpy(alu->nombre, nombreCompleto);
        alu->apellido[0] = '\0';
      }

      contador++;
      if (contador >= 100)
        break;
    }
  }

  fclose(fp);
  return contador; // Devuelve la cantidad de alumnos leidos
}

int obtener_tipos(char *archivo, Tipo tipos[], int max) {
  // Extraer los tipos de examenes
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
  // Extraer las nota de los examenes
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

  while (fgets(linea, sizeof(linea), fp) !=
         NULL) { // Carga las notas en cada uno de los alumnos
    int id, tipo, nota;
    char extra;

    // Validar que la línea tenga exactamente tres enteros y nada más
    if (sscanf(linea, "%d,%d,%d %c", &id, &tipo, &nota, &extra) != 3) {
      printf("Error: línea con formato inválido: %s", linea);
      exit(1);
    }

    if (nota < 0 || nota > 100) {
      printf(
          "Error: la nota del examen con ID %d está fuera de rango (0-100).\n",
          id);
      exit(1);
    }

    examen.id = id;
    examen.nota = nota;
    examen.idtipo = tipo;

    int encontrado = 0;
    for (int i = 0; i < totalTipo; i++) {
      if (tipos[i].id == tipo) {
        strcpy(examen.tipo, tipos[i].nombre);
        encontrado = 1;
        break;
      }
    }

    // Agrega tipo desconocido en el caso de que no exista el tipo
    if (!encontrado) {
      strcpy(examen.tipo, "Desconocido");
    }

    examenes[contador++] = examen;
    if (contador >= max)
      break;
  }

  fclose(fp);
  return contador;
}

void cargar_notas(Alumno alumno[], int totalAlumnos, Examen examene[],
                  int totalExamenes) {
  // Cargar las notas en cada uno de los alumnos. En caso de que no existan el
  // alumno la nota no se carga
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

float puntaje(Alumno alumno) {
  // Calcula el puntaje ponderado de cada alumno con la formula de la facultad
  int cantidad = 0;
  float promedioParcial = 0;
  int sumaParciales = 0;

  if (alumno.puntaje.primerParcial > 0) {
    cantidad++;
  }
  if (alumno.puntaje.segundoParcial > 0) {
    cantidad++;
  }
  if (alumno.puntaje.tercerParcial > 0) {
    cantidad++;
  }

  // verifica cuantos parciales rindio el alumno
  if (cantidad == 3) {
    if (alumno.puntaje.primerParcial <=
        alumno.puntaje.segundoParcial) { // toma los 2 mayores de los 3
                                         // parciales y los promedia
      promedioParcial = (float)(alumno.puntaje.tercerParcial +
                                alumno.puntaje.segundoParcial) /
                        2;
    } else {
      promedioParcial = (float)(alumno.puntaje.segundoParcial +
                                alumno.puntaje.tercerParcial) /
                        2;
    }
  } else if (cantidad == 2) {
    // verifica cuales fueron los dos parciales que rindio el alumno y los
    // promedia.
    if (alumno.puntaje.primerParcial > 0) {
      sumaParciales += alumno.puntaje.primerParcial;
    }

    if (alumno.puntaje.segundoParcial > 0) {
      sumaParciales += alumno.puntaje.segundoParcial;
    }

    if (alumno.puntaje.tercerParcial > 0) {
      sumaParciales += alumno.puntaje.tercerParcial;
    }

    promedioParcial = (float)sumaParciales / 2;
  } else {
    return 0;
  }

  if (alumno.puntaje.primerFinal >=
      50) { // Hace el promedio ponderado de los parciales y el final

    return promedioParcial * 0.4f + (float)alumno.puntaje.primerFinal * 0.6f;

  } else if (alumno.puntaje.segundoFinal >= 50) {

    return promedioParcial * 0.4f + (float)alumno.puntaje.segundoFinal * 0.6f;
  } else {
    return 0;
  }
}

int alumnos_aprobados_por_carrera(Alumno alumnos[], int totalAlumnos,
                                  CarreraEstadistica estadisticas[]) {
  int totalCarreras = 0;

  for (int i = 0; i < totalAlumnos; i++) {
    int encontrada = 0;
    for (int j = 0; j < totalCarreras; j++) {
      if (strcmp(estadisticas[j].carrera, alumnos[i].carrera) == 0) {
        estadisticas[j].cantidadInscritos++;
        if (puntaje(alumnos[i]) >= 60) {
          estadisticas[j].cantidadAprobados++;
        }
        encontrada = 1;
        break;
      }
    }
    if (!encontrada && totalCarreras < 100) {
      strcpy(estadisticas[totalCarreras].carrera, alumnos[i].carrera);
      estadisticas[totalCarreras].cantidadInscritos = 1;
      estadisticas[totalCarreras].cantidadAprobados =
          (puntaje(alumnos[i]) >= 60) ? 1 : 0;
      totalCarreras++;
    }
  }

  return totalCarreras;
}

void output_estadisticas(Alumno alumnos[], int totalAlumnos, char *archivo) {
  FILE *fp = fopen(archivo, "w"); // "w" crea el archivo si no existe
  if (fp == NULL) {
    printf("Error: No se pudo crear el archivo '%s'.\n", archivo);
    return;
  }

  fprintf(fp, "Estadisticas de la materia:\n");

  int totalPrimerFinal = 0;
  int totalSegundoFinal = 0;
  int noRindieronFinal = 0;
  int totalpasaron = 0;

  for (int a = 0; a < totalAlumnos; a++) {
    printf("Alumno %d: %s hizo: %f \n", alumnos[a].Id, alumnos[a].nombre,
           puntaje(alumnos[a]));
    if (alumnos[a].puntaje.primerFinal >= 50 && puntaje(alumnos[a]) >= 60) {
      totalPrimerFinal++;
    }

    if (alumnos[a].puntaje.segundoFinal >= 50 && puntaje(alumnos[a]) >= 60) {
      totalSegundoFinal++;
    }
    if (puntaje(alumnos[a]) >= 60) {
      totalpasaron++;
    }
    if (alumnos[a].puntaje.segundoFinal == -1 &&
        alumnos[a].puntaje.segundoFinal == -1) {
      noRindieronFinal++;
    }
  }

  fprintf(fp, "Cantidad de alumnos: %d:\n",
          totalAlumnos); // Cantidad de alumnos
  fprintf(
      fp, "Cantidad de alumnos que aprobaron en primer final: %d\n",
      totalPrimerFinal); // Cantidad de alumnos que aprobaron en primer final: X

  fprintf(fp, "Cantidad de alumnos que aprobaron en segundo final: %d\n",
          totalSegundoFinal); // Cantidad de alumnos que aprobaron en segundo
                              // final: X

  fprintf(fp,
          "Cantidad de alumnos que no rindieron final, ni el primero, ni el "
          "segundo: %d\n",
          noRindieronFinal); // Cantidad de alumnos que no rindieron final, ni

  CarreraEstadistica estadisticas[100];
  int totalCarreras =
      alumnos_aprobados_por_carrera(alumnos, totalAlumnos, estadisticas);

  fprintf(fp, "Cantidad de alumnos que aprobaron la materia por carrera:\n");
  for (int i = 0; i < totalCarreras; i++) {
    fprintf(fp, "- %s: %d\n", estadisticas[i].carrera,
            estadisticas[i].cantidadAprobados);
  }
  fprintf(fp, "Porcentaje de almunos aprobados: %0.2f%\n",
          (float)totalpasaron / totalAlumnos * 100);
  fprintf(fp, "Porcentaje de almunos aplazados: %0.2f%\n",
          (1 - (float)totalpasaron / totalAlumnos) * 100);

  fprintf(fp, "Promedio de alumnos que aprobaron la materia por carrera:\n");
  for (int i = 0; i < totalCarreras; i++) {
    fprintf(fp, "- %s: %0.2f%\n", estadisticas[i].carrera,
            (float)(estadisticas[i].cantidadAprobados * 100) /
                estadisticas[i].cantidadInscritos);
  }
}

int Nota_final(float promedio) {
  if (promedio >= 90) {
    return 5;
  } else if (promedio >= 80) {
    return 4;
  } else if (promedio >= 70) {
    return 3;
  } else if (promedio >= 60) {
    return 2;
  } else {
    return 1;
  }
}
void generar_calificaciones_txt(Alumno alumnos[], int totalAlumnos,
                                const char *archivo) {
  FILE *fp = fopen(archivo, "w");
  if (fp == NULL) {
    printf("Error al crear el archivo '%s'\n", archivo);
    return;
  }

  fprintf(fp, "Alumnos que aprobaron la materia:\n");

  // --- Primer Final ---
  fprintf(fp, "\nPrimer Final\n");
  fprintf(fp, "Nombre Alumno     Prom Ponderado     Examen Final     "
              "Calificación\n");

  for (int i = 0; i < totalAlumnos; i++) {
    int calificacion = Nota_final(puntaje(alumnos[i]));

    if (alumnos[i].puntaje.primerFinal >= 50 && puntaje(alumnos[i]) >= 60) {
      fprintf(fp, "%s %s         %.2f             %d                  %d\n",
              alumnos[i].nombre, alumnos[i].apellido, puntaje(alumnos[i]),
              alumnos[i].puntaje.primerFinal, calificacion);
    }
  }

  fprintf(fp, "\n--------------------------------------------------------\n");
  // --- Segundo Final ---
  fprintf(fp, "\nSegundo Final\n");
  fprintf(fp, "Nombre Alumno     Prom Ponderado     Examen Final     "
              "Calificación\n");

  for (int i = 0; i < totalAlumnos; i++) {
    int calificacion = Nota_final(puntaje(alumnos[i]));

    if (alumnos[i].puntaje.segundoFinal >= 50 && puntaje(alumnos[i]) >= 60) {
      fprintf(fp, "%s %s         %0.2f             %d                  %d\n",
              alumnos[i].nombre, alumnos[i].apellido, puntaje(alumnos[i]),
              alumnos[i].puntaje.segundoFinal, Nota_final(puntaje(alumnos[i])));
    }
  }
  fprintf(fp, "\n--------------------------------------------------------\n ");
  // --- No Aprobados ---
  fprintf(fp, "\nAlumnos que no aprobaron la materia:\n");
  fprintf(fp, "Nombre Alumno   1erParcial   2doParcial    3erParcial    "
              "1erFinal    2do Final\n");

  for (int i = 0; i < totalAlumnos; i++) {
    float calificacion = puntaje(alumnos[i]);
    if (calificacion < 60) {
      fprintf(fp, "%s %s         ", alumnos[i].nombre, alumnos[i].apellido);

      if (alumnos[i].puntaje.primerParcial != -1) {
        fprintf(fp, "%d         ", alumnos[i].puntaje.primerParcial);
      } else {
        fprintf(fp, "X         ");
      }

      if (alumnos[i].puntaje.segundoParcial != -1) {
        fprintf(fp, "%d         ", alumnos[i].puntaje.segundoParcial);
      } else {
        fprintf(fp, "X         ");
      }

      if (alumnos[i].puntaje.tercerParcial != -1) {
        fprintf(fp, "%d         ", alumnos[i].puntaje.tercerParcial);
      } else {
        fprintf(fp, "X         ");
      }

      if (alumnos[i].puntaje.primerFinal != -1) {
        fprintf(fp, "%d         ", alumnos[i].puntaje.primerFinal);
      } else {
        fprintf(fp, "X         ");
      }

      if (alumnos[i].puntaje.segundoFinal != -1) {
        fprintf(fp, "%d         \n", alumnos[i].puntaje.segundoFinal);
      } else {
        fprintf(fp, "X         \n");
      }
    }
  }

  fclose(fp);
}

int main() {
  Alumno alumnos[100];
  Examen examenes[100];
  int totalAlumnos = leer_alumno("alumnos.txt", alumnos);
  int totalExamenes = leer_examene("notas.txt", examenes, 100);

  cargar_notas(alumnos, totalAlumnos, examenes, totalExamenes);

  output_estadisticas(alumnos, totalAlumnos, "estadisticas.txt");
  generar_calificaciones_txt(alumnos, totalAlumnos, "calificaciones.txt");

  return 0;
}
