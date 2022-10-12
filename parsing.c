#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"

#include <math.h>

Data createData() {
  Data data;
  data.vertex = NULL;
  data.vertexRows = 0;
  data.index = NULL;
  data.indexRows = 0;
  data.vertexInIndex = NULL;
  return data;
}

int addFace(Data *data, char *line) {
  int error = NO_ERROR;
  int fRows = data->indexRows;

  data->index = (int **)realloc(data->index, sizeof(int *) * ++fRows);
  data->index[fRows - 1] = NULL;
  data->vertexInIndex =
      (int *)realloc(data->vertexInIndex, fRows * sizeof(int));
  char *save = NULL;
  char *token = strtok_r(line, " ", &save);
  int counter = 0;
  int num = 0;

  while ((token = strtok_r(NULL, " ", &save)) != NULL) {
    data->index[fRows - 1] =
        (int *)realloc(data->index[fRows - 1], ++counter * sizeof(int));
    sscanf(token, "%d", &num);
    data->index[fRows - 1][counter - 1] = num;
  }
  data->vertexInIndex[fRows - 1] = counter;
  data->indexRows = fRows;
  return error;
}

int addVertice(Data *data, char *line) {
  int error = NO_ERROR;
  int vRows = data->vertexRows;

  data->vertex =
      (double **)realloc(data->vertex, sizeof(double *) * ++vRows);
  data->vertex[vRows - 1] = (double *)malloc(3 * sizeof(double));

  char *save = NULL;
  strtok_r(line, " ", &save);
  for (int i = 0; i < 3; i++) {
    char *tok_tok = strtok_r(NULL, " ", &save);
       sscanf(tok_tok, "%lf", &data->vertex[vRows - 1][i]);
  }
  data->vertexRows = vRows;
  return error;
}

Data parsing(char *fileName) {
  Data data = createData();
  FILE *objFile;
  objFile = fopen(fileName, "r");
  if (objFile == NULL) {
    printf("Указанный .obj-файл не найден\n");
  } else {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, objFile)) != -1) {
      if (strstr(line, "v ") != NULL)
        addVertice(&data, line);
      else if (strstr(line, "f ") != NULL)
        addFace(&data, line);
    }
    free(line);
    fclose(objFile);
  }
  return data;
}
