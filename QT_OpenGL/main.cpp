#include <GLUT/glut.h>
#include <widget.h>

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  w.setWindowTitle("Вьювер Евлампий");
  return a.exec();
}
