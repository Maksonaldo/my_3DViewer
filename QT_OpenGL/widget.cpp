#include "widget.h"
#include <GLUT/glut.h>
#include "QFileDialog"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent) {

  x_pos = y_pos = angle_x = angle_y = 0;
  timer.start(16);
  initializeArr();
}

void Widget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
}

void Widget::initializeArr() { data = parsing(""); }

void Widget::backgroundCol() {
  backgroundColor.getRgbF(&backgroundFirst, &backgroundSecond, &backgroundThird,
                          &backgroundFourth);
  glClearColor(backgroundFirst, backgroundSecond, backgroundThird,
               backgroundFourth);
  glClear(GL_COLOR_BUFFER_BIT);
  updateFrame();
}

void Widget::lineCol() {
  lineColor.getRgbF(&lineSecond, &lineThird, &lineFourth);
  glColor3d(lineSecond, lineThird, lineFourth);
  updateFrame();
}
void Widget::pointCol() {
  pointColor.getRgbF(&pointSecond, &pointThird, &pointFourth);
  glColor3d(pointSecond, pointThird, pointFourth);
  updateFrame();
}


void Widget::resizeGL(int w, int h) {
  glTranslated(XRight, YTop, ZTop);
  glTranslated(XLeft, -YDown, -ZDown);
  glRotated(XRot, 1, 0, 0);
  glRotated(YRot, 0, 1, 0);
  glRotated(ZRot, 0, 0, 1);
  glRotated(XRotNeg, 1, 0, 0);
  glRotated(YRotNeg, 0, 1, 0);
  glRotated(ZRotNeg, 0, 0, 1);
  glScalef(scaleS, scaleS, scaleS);
  backgroundCol();
}

void Widget::paintGL() {
  GLdouble ratio = (GLdouble)this->width() / (GLdouble)this->height();

  glMatrixMode(GL_PROJECTION);  //влияет на размер фигуры
  glLoadIdentity();             //единичная матрица
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //очистка экрана
  if (paralelPr == true) {
    glOrtho(-1.0 * ratio, 1.0 * ratio, -1.2, 1.2, 1, 20);
  } else {
    glFrustum(-0.1 * ratio, 0.1 * ratio, -0.1, 0.1, 0.1,
              50.0);  //Центральная проекция
  }

  glTranslatef(0, 0, -3);

  glRotatef(angle_x, 1, 0, 0);
  glRotatef(angle_y, 0, 1, 0);

  if (animashin) {
    myRotated(data.vertex, data.vertexRows, Y, POSITIVE, 0.4);
  }
  backgroundCol();
  movingObgect();
  drawObject();
}

void Widget::movingObgect() {
  if (xRight) {
    xRight = 0.2;
    myTranslated(data.vertex, data.vertexRows, X, POSITIVE, xRight);
    XRight = xRight + XRight;
    xRight = 0;
  }

  if (xLeft) {
    xLeft = -0.2;
    myTranslated(data.vertex, data.vertexRows, X, POSITIVE, xLeft);
    XLeft = XLeft + xLeft;
    xLeft = 0;
  }

  if (yTop) {
    yTop = 0.2;
    myTranslated(data.vertex, data.vertexRows, Y, POSITIVE, yTop);
    YTop = YTop + yTop;
    yTop = 0;
  }

  if (zTop) {
    zTop = 0.2;
    myTranslated(data.vertex, data.vertexRows, Z, POSITIVE, zTop);
    ZTop = ZTop + zTop;
    zTop = 0;
  }

  if (yDown) {
    yDown = 0.2;
    myTranslated(data.vertex, data.vertexRows, Y, NEGATIVE, yDown);
    YDown = YDown + yDown;
    yDown = 0;
  }

  if (zDown) {
    zDown = 0.2;  // ИКСИРОВАННЫЙ ШАГ
    myTranslated(data.vertex, data.vertexRows, Z, NEGATIVE, zDown);
    ZDown = ZDown + zDown;
    zDown = 0;
  }

  if (xRot) {
    xRot = 10;
    myRotated(data.vertex, data.vertexRows, X, POSITIVE, xRot);
    XRot = XRot + xRot;
    xRot = 0;
  }

  if (yRot) {
    yRot = 10;
    myRotated(data.vertex, data.vertexRows, Y, POSITIVE, yRot);
    YRot = YRot + yRot;
    yRot = 0;
  }

  if (zRot) {
    zRot = 10;
    myRotated(data.vertex, data.vertexRows, Z, POSITIVE, zRot);
    ZRot = ZRot + zRot;
    zRot = 0;
  }
  if (xRotNeg) {
    xRotNeg = 10;
    myRotated(data.vertex, data.vertexRows, X, NEGATIVE, xRotNeg);
    XRotNeg = XRotNeg + xRotNeg;
    xRotNeg = 0;
  }
  if (yRotNeg) {
    yRotNeg = 10;
    myRotated(data.vertex, data.vertexRows, Y, NEGATIVE, yRotNeg);
    YRotNeg = YRotNeg + yRotNeg;
    yRotNeg = 0;
  }
  if (zRotNeg) {
    zRotNeg = 10;
    myRotated(data.vertex, data.vertexRows, Z, NEGATIVE, zRotNeg);
    ZRotNeg = ZRotNeg + zRotNeg;
    zRotNeg = 0;
  }

  if (scale) {
    myScaled(data.vertex, data.vertexRows, scale);
    scaleS = scaleS + 0.1;
    scale = 0;
  }

  if (negScale) {
    myScaled(data.vertex, data.vertexRows, negScale);
    scaleS = scaleS - 0.1;
    negScale = 0;
  }
}

void Widget::drawObject() {
  int maxVertexInIndex = 0;
  int edgeCounter = 0;

  glPointSize(pointSize);
  glLineWidth(lineSize);
  if (pointType == true) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  if (pointZero == false) {
    for (int i = 0; i < data.vertexRows; i++) {
      glBegin(GL_POINTS);
      pointCol();
      glVertex3d(data.vertex[i][0], data.vertex[i][1], data.vertex[i][2]);
      glEnd();
    }
  }
  for (int i = 0; i < data.indexRows; i++) {
    maxVertexInIndex = data.vertexInIndex[i];
    glEnable(GL_LINE_STIPPLE);
    if (lineType == true) {
      glLineStipple(1, 0xFFFF);  //  линии
    } else {
      glLineStipple(1, 0x00FF);  //  пунктиры
    }
    glBegin(GL_LINES);
    lineCol();
    for (int j = 0; j < maxVertexInIndex; j++) {
      glVertex3d(data.vertex[data.index[i][j] - 1][0],
                 data.vertex[data.index[i][j] - 1][1],
                 data.vertex[data.index[i][j] - 1][2]);
    }
    glEnd();
    for (int j = 0; j < maxVertexInIndex; j++) {
      int startInd = data.index[i][j];
      int endInd =
          (j == maxVertexInIndex - 1) ? data.index[i][0] : data.index[i][j + 1];
      glBegin(GL_LINES);
      lineCol();
      glVertex3d(data.vertex[startInd - 1][0], data.vertex[startInd - 1][1],
                 data.vertex[startInd - 1][2]);
      glVertex3d(data.vertex[endInd - 1][0], data.vertex[endInd - 1][1],
                 data.vertex[endInd - 1][2]);
      glEnd();
    }
  }
}

void Widget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    x_pos = event->x();
    y_pos = event->y();
  }
}
void Widget::mouseMoveEvent(QMouseEvent *event) {
  angle_x = 180 * (GLfloat(event->y()) - y_pos) / width();
  angle_y = 180 * (GLfloat(event->x()) - x_pos) / height();
  update();
}

void Widget::updateFrame() { update(); }


