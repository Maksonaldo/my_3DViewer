#ifndef WIDGET_H
#define WIDGET_H

#include <qfile.h>
#include <qtextstream.h>

#include <QColorDialog>
#include <QDebug>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif
#include "../parsing.h"
#include "../afins.h"
#ifdef __cplusplus
}
#endif

class Widget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  double value = 0;
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void backgroundCol();
  void lineCol();
  void pointCol();
  void movingObgect();


  void initializeArr();

  //    ~Widget();
  void drawObject();
  void init_vertex();
  void init_fdata();
  float x, y, z;
  double xRight = 0, yTop = 0, zTop = 0;
  double xLeft = 0, yDown = 0, zDown = 0;
  double XRight = 0, XLeft = 0, YTop = 0, YLeft = 0, ZTop = 0, ZDown = 0,
         YDown = 0, XRot = 0, YRot = 0, ZRot = 0, XRotNeg = 0, YRotNeg = 0, ZRotNeg = 0;
  double xRot = 0, yRot = 0, zRot = 0, xRotNeg = 0, yRotNeg = 0, zRotNeg = 0;
  double scale, negScale, bufScale, scaleS = 1;
  Widget *widget = nullptr;



  Data data;
  double lineSize;
  double pointSize;
  bool lineType = true;

  QColor backgroundColor;
  QColor lineColor;
  QColor pointColor;

  float lineSecond = 1, lineThird = 0, lineFourth = 0;
  float pointSecond = 0, pointThird = 1, pointFourth = 1;

  float backgroundFirst = 0, backgroundSecond = 0, backgroundThird = 0,
        backgroundFourth = 0;

  bool pointType = true;
  bool pointZero = false;
  bool paralelPr = true;
  bool animashin = false;

 protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

 private:
  QPoint mPosition;
  QTimer timer;
  GLfloat y_pos, x_pos;
  GLfloat angle_x, angle_y;

  bool background = true;
  bool pointsColor = true;
  bool linesColor = true;
  bool linesColor2 = true;
  bool drawing = true;

 public slots:
 void updateFrame();

};

#endif  // WIDGET_H
