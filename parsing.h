#ifndef SRC_PARSING_H_
#define SRC_PARSING_H_

#define NO_ERROR 0

typedef struct Data Data;
struct Data {
  double **vertex;
  int vertexRows;
  int **index;
  int indexRows;
  int *vertexInIndex;
  int b;
};

Data createData();
int addFace(Data *data, char *line);
int addVertice(Data *data, char *line);
Data parsing(char *fileName);
void freeData(Data data);

#endif  // SRC_PARSING_H_
