#include <stdlib.h>
#include <string.h>
#include "parsing.h"
#include "afins.h"
#include <math.h>

double **getMatrix(int rows, int columns) {
  double **matrix = (double **)malloc(sizeof(double *) * rows);
  for (int i = 0; i < rows; i++) {
    matrix[i] = (double *)calloc(columns, sizeof(double));
  }
  return matrix;
}

double **moveTransMatrix(direction dir, coordinate xyz,
               double step) {
  double move = step * dir;
  double **matrix = getMatrix(TRANSFORM_MATR_SIZE, TRANSFORM_MATR_SIZE);
  matrix[0][0] = 1;
  matrix[1][1] = 1;
  matrix[2][2] = 1;
  matrix[3][3] = 1;
    switch (xyz) {
    case X:
      matrix[0][3] = move;
      break;
    case Y:
      matrix[1][3] = move;
      break;
    case Z:
      matrix[2][3] = move;
      break;
  }
  return matrix;
}


void myTranslated(double **vertices, int vertexRows, coordinate xyz, direction dir,
               double step) {
  double **trans = moveTransMatrix(dir, xyz, step);
  double **coords = getMatrix(COORD_MATR_ROWS, COORD_MATR_COLUMNS);
  double **res = NULL;

    for (int i = 0; i < vertexRows; i++) {
    coords[0][0] = vertices[i][0];
    coords[1][0] = vertices[i][1];
    coords[2][0] = vertices[i][2];
    coords[3][0] = 1;
    res = newCoords(trans, coords);
    vertices[i][0] = res[0][0];
    vertices[i][1] = res[1][0];
    vertices[i][2] = res[2][0];
    freeMatrix(res, COORD_MATR_ROWS);
  }
  freeMatrix(trans, TRANSFORM_MATR_SIZE);
  freeMatrix(coords, COORD_MATR_ROWS);
}

double **newCoords(double **transform, double **oldCoords) {
  double **res = getMatrix(COORD_MATR_ROWS, COORD_MATR_COLUMNS);

  for (int i = 0; i < TRANSFORM_MATR_SIZE; ++i) {
    for (int j = 0; j < COORD_MATR_COLUMNS; ++j) {
      for (int k = 0; k < TRANSFORM_MATR_SIZE; ++k) {
        res[i][j] += transform[i][k] * oldCoords[k][j];
      }
    }
  }

  return res;
}
void freeData(Data data) {
    freeMatrix(data.vertex, data.vertexRows);
    freeMatrixInt(data.index, data.indexRows);
    free(data.vertexInIndex);
}

void freeMatrix(double **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void freeMatrixInt(int **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

double **moveRotatMatrix(coordinate xyz, direction dir, double degree) {
  double radians = degree * -dir * PI / 180;
  double **matr = getMatrix(TRANSFORM_MATR_SIZE, TRANSFORM_MATR_SIZE);

  switch (xyz) {
    case X:
      matr[0][0] = 1;
      matr[3][3] = 1;
      matr[1][1] = cos(radians);
      matr[1][2] = -sin(radians);
      matr[2][1] = sin(radians);
      matr[2][2] = cos(radians);
      break;
    case Y:
      matr[0][0] = cos(radians);
      matr[0][2] = sin(radians);
      matr[1][1] = 1;
      matr[2][0] = -sin(radians);
      matr[2][2] = cos(radians);
      matr[3][3] = 1;
      break;
    case Z:
      matr[0][0] = cos(radians);
      matr[0][1] = -sin(radians);
      matr[1][0] = sin(radians);
      matr[1][1] = cos(radians);
      matr[2][2] = 1;
      matr[3][3] = 1;
      break;
  }

  return matr;
}

void myRotated(double **vertices, int vertexRows, coordinate xyz, direction dir,
            double degree) {
  double **trans = moveRotatMatrix(xyz, dir, degree);
  double **coords = getMatrix(COORD_MATR_ROWS, COORD_MATR_COLUMNS);
  double **res = NULL;
  for (int i = 0; i < vertexRows; i++) {
    coords[0][0] = vertices[i][0];
    coords[1][0] = vertices[i][1];
    coords[2][0] = vertices[i][2];
    coords[3][0] = 1;
    res = newCoords(trans, coords);
    vertices[i][0] = res[0][0];
    vertices[i][1] = res[1][0];
    vertices[i][2] = res[2][0];
    freeMatrix(res, COORD_MATR_ROWS);
  }
  freeMatrix(trans, TRANSFORM_MATR_SIZE);
  freeMatrix(coords, COORD_MATR_ROWS);
}

void myScaled(double **vertices, int vertexRows,
            double scale) {
  for (int i = 0; i <vertexRows; i++) {
      for (int j = 0; j < 3; j++) {
          vertices[i][j] = vertices[i][j] * scale;
      }
  }
}
