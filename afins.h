#ifndef SRC_AFINS_H_
#define SRC_AFINS_H_

#define NO_ERROR 0
#define COORD_MATR_ROWS 4
#define COORD_MATR_COLUMNS 1
#define TRANSFORM_MATR_SIZE 4
#define PI 3.14159265358979323846

typedef enum { X, Y, Z } coordinate;
typedef enum { POSITIVE = 1, NEGATIVE = -1 } direction;
double **moveTransMatrix(direction dir, coordinate xyz,
               double step);
double **getMatrix(int rows, int columns);
double **getTransMatr(coordinate xyz, direction dir, double step);
double **newCoords(double **oldCoords, double **transform);
void myTranslated(double **vertices, int vertexRows,
coordinate xyz, direction dir, double step);
void myRotated(double **vertex, int vertexRows, coordinate xyz, direction dir,
            double degree);
double **moveRotatMatrix(coordinate xyz, direction dir, double degree);
void myScaled(double **vertices, int vertexRows,
            double scale);
void freeMatrix(double **matrix, int rows);
void freeMatrixInt(int **matrix, int rows);

#endif  // SRC_AFINS_H_
