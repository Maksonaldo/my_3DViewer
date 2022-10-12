#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <fstream>
#include "qgifimage.h"
#include "widget.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../parsing.h"
#include "../afins.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  Widget *widget = nullptr;
  double scale, negScale, bufScale, scaleS;
  QColor background_Сolor;
  QColor line_Color;
  QColor point_Color;
  char *arr_tmp;
  std::string input;

 private slots:
  void on_x_rot_valueChanged(double arg1);

  void on_y_rot_valueChanged(double arg1);

  void on_z_rot_valueChanged(double arg1);

  void on_rightX_clicked();

  void on_topY_clicked();

  void on_downY_clicked();

  void on_scaleButton_clicked();

  void on_negScaleButton_clicked();

  void on_zTop_clicked();

  void on_zDown_clicked();

  void on_leftX_clicked();

  void on_newFile_clicked();

  void on_lineSize_valueChanged(int value);

  void on_pointSize_valueChanged(int value);

  void on_comboBox_currentTextChanged(const QString &arg1);

  void on_backgroundColor_clicked();

  void on_lineColor_clicked();

  void on_pointColor_clicked();

  void on_pointType_currentTextChanged(const QString &arg1);

  void on_projection_currentTextChanged(const QString &arg1);

  void saveSettings();
  void loadSettings();
  void on_cleanSettings_clicked();

  void on_gif_clicked();
  void Record();

  void on_animashin_clicked(bool checked);

  void on_screen_clicked();
  void buttonJPEG();
  void buttonBMP();

  void on_x_rot_2_valueChanged(double arg1);

  void on_y_rot_2_valueChanged(double arg1);

  void on_z_rot_2_valueChanged(double arg1);

private:
  Ui::MainWindow *ui;
  Data data;
  QSettings *settings;
  bool settingsBool = true;
  int count_frame;
  QTimer *timer;
  QFile *ptr_gif_file;
  QFile ptr_bmp_file;
  QGifImage *gif;
  QPushButton *butBMP, *butJPEG, *start, *stop;
  QTime time;
  bool screen = true;

};
#endif  // MAINWINDOW_H
