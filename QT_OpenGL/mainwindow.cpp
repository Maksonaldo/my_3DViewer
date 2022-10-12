#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->bmp->hide();
  ui->jpeg->hide();

  settings = new QSettings("Viwer", "Settings", this);
  loadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_x_rot_valueChanged(double arg1) {
  double x = (arg1 * M_PI) / 180;
  ui->openGLWidget->xRot = x;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_y_rot_valueChanged(double arg1) {
  double y = arg1 * 1000;
  ui->openGLWidget->yRot = y;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_z_rot_valueChanged(double arg1) {
  double z = (arg1 * M_PI) / 180;
  ui->openGLWidget->zRot = z;
  ui->openGLWidget->updateFrame();
}


void MainWindow::on_rightX_clicked() {
  ui->openGLWidget->xRight = 0.2;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_topY_clicked() {
  ui->openGLWidget->yTop = 0.2;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_downY_clicked() {
  ui->openGLWidget->yDown = 0.2;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_scaleButton_clicked() {
  bufScale = 1;
  bufScale = bufScale + 0.1;
  scale = bufScale;
  ui->openGLWidget->scale = scale;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_negScaleButton_clicked() {
  bufScale = 1;
  bufScale = bufScale - 0.1;
  scale = bufScale;
  ui->openGLWidget->negScale = scale;

  ui->openGLWidget->updateFrame();
}

void MainWindow::on_zTop_clicked() {
  ui->openGLWidget->zTop = 0.2;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_zDown_clicked() {
  ui->openGLWidget->zDown = 0.2;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_leftX_clicked() {
  ui->openGLWidget->xLeft = 0.2;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_newFile_clicked() {
  input = QFileDialog::getOpenFileName().toStdString();
  arr_tmp = (char *)input.c_str();
  ui->openGLWidget->data = parsing(arr_tmp);
  qDebug() << "sdasd" << data.vertexRows;

  std::string fileName;
  fileName = input.substr(input.find_last_of("/\\") + 1);
  ui->FileName->setText(QString::fromStdString(fileName));


  QString new_label_vertex =
      "Vertices: " + QString::number(ui->openGLWidget->data.vertexRows);
  ui->vertexes->setText(new_label_vertex);
  QString new_label_index =
      "Edges: " + QString::number(ui->openGLWidget->data.indexRows);
  ui->facets->setText(new_label_index);
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_lineSize_valueChanged(int value) {
  ui->openGLWidget->lineSize = value;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_pointSize_valueChanged(int value) {
  ui->openGLWidget->pointSize = value;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1) {
  if (arg1 == "Solid") {
    ui->openGLWidget->lineType = true;
  } else {
    ui->openGLWidget->lineType = false;
  }
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_backgroundColor_clicked() {
  ui->openGLWidget->backgroundColor =
      QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_lineColor_clicked() {
  ui->openGLWidget->lineColor =
      QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_pointColor_clicked() {
  ui->openGLWidget->pointColor =
      QColorDialog::getColor(Qt::white, this, "Выбор цвета");
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_pointType_currentTextChanged(const QString &arg1) {
  if (arg1 == "Circle") {
    ui->openGLWidget->pointType = true;
    ui->openGLWidget->pointZero = false;
  } else if (arg1 == "Square") {
    ui->openGLWidget->pointType = false;
    ui->openGLWidget->pointZero = false;
  } else if (arg1 == "None") {
    ui->openGLWidget->pointZero = true;
  }
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_projection_currentTextChanged(const QString &arg1) {
  if (arg1 == "Parallel") {
    ui->openGLWidget->paralelPr = true;
  } else {
    ui->openGLWidget->paralelPr = false;
  }
  ui->openGLWidget->updateFrame();
}

void MainWindow::saveSettings() {
  settings->beginGroup("Color");
  settings->setValue("backgroundColor", ui->openGLWidget->backgroundColor);
  settings->setValue("lineColor", ui->openGLWidget->lineColor);

  settings->setValue("pointColor", ui->openGLWidget->pointColor);

  settings->setValue("lineSize", ui->openGLWidget->lineSize);
  settings->setValue("pointSize", ui->openGLWidget->pointSize);
  settings->setValue("lineType", ui->openGLWidget->lineType);
  settings->setValue("pointType", ui->openGLWidget->pointType);
  settings->setValue("pointZero", ui->openGLWidget->pointZero);

  settings->setValue("paralelPr", ui->openGLWidget->paralelPr);

  settings->setValue("XRight", ui->openGLWidget->XRight);
  settings->setValue("XLeft", ui->openGLWidget->XLeft);

  settings->setValue("YTop", ui->openGLWidget->YTop);
  settings->setValue("ZTop", ui->openGLWidget->ZTop);

  settings->setValue("YDown", ui->openGLWidget->YDown);
  settings->setValue("ZDown", ui->openGLWidget->ZDown);

  settings->setValue("XRot", ui->openGLWidget->XRot);
  settings->setValue("YRot", ui->openGLWidget->YRot);
  settings->setValue("ZRot", ui->openGLWidget->ZRot);

  settings->setValue("XRotNeg", ui->openGLWidget->XRotNeg);
  settings->setValue("YRotNeg", ui->openGLWidget->YRotNeg);
  settings->setValue("ZRotNeg", ui->openGLWidget->ZRotNeg);

  settings->setValue("scaleS", ui->openGLWidget->scaleS);
  settings->endGroup();
}

void MainWindow::loadSettings() {
  settings->beginGroup("Color");
  background_Сolor =
      settings->value("backgroundColor").toByteArray().constData();
  ui->openGLWidget->backgroundColor = background_Сolor;

  line_Color = settings->value("lineColor").toByteArray().constData();
  ui->openGLWidget->lineColor = line_Color;

  point_Color = settings->value("pointColor").toByteArray().constData();

  ui->openGLWidget->pointColor = point_Color;

  int line_size;
  line_size = settings->value("lineSize").toInt();
  ui->lineSize->setValue(line_size);
  ui->openGLWidget->lineSize = line_size;

  int point_size = settings->value("pointSize").toInt();
  ui->pointSize->setValue(point_size);
  ui->openGLWidget->pointSize = point_size;

  bool line_type = settings->value("lineType").toBool();

  qDebug() << line_type;

  if (line_type == true) {
    ui->comboBox->setCurrentIndex(0);
  } else {
    ui->comboBox->setCurrentIndex(1);
  }

  ui->openGLWidget->lineType = line_type;

  bool point_type = settings->value("pointType").toBool();
  if (point_type == true) {
    ui->pointType->setCurrentIndex(0);
  } else if (point_type == false) {
    ui->pointType->setCurrentIndex(1);
  }
  ui->openGLWidget->pointType = point_type;

  bool point_zero = settings->value("pointZero").toBool();
  if (point_zero == true) {
    ui->pointType->setCurrentIndex(2);
  }
  ui->openGLWidget->pointZero = point_zero;

  bool paralel_pr = settings->value("paralelPr").toBool();
  if (paralel_pr == true) {
    ui->projection->setCurrentIndex(0);
  } else {
    ui->projection->setCurrentIndex(1);
  }
  ui->openGLWidget->paralelPr = paralel_pr;

  float X_Right = settings->value("XRight").toDouble();

  ui->openGLWidget->XRight = X_Right;
  qDebug() << "save" << ui->openGLWidget->XRight;

  float X_Left = settings->value("XLeft").toDouble();
  ui->openGLWidget->XLeft = X_Left;

  float Y_Top = settings->value("YTop").toDouble();
  ui->openGLWidget->YTop = Y_Top;

  double Z_Top = settings->value("ZTop").toDouble();
  ui->openGLWidget->ZTop = Z_Top;

  qDebug() << "ZToop" << ui->openGLWidget->ZTop;

  float Y_Down = settings->value("YDown").toDouble();
  ui->openGLWidget->YDown = Y_Down;

  double Z_Down = settings->value("ZDown").toDouble();
  ui->openGLWidget->ZDown = Z_Down;

  double X_Rot = settings->value("XRot").toDouble();
  ui->x_rot->setValue(X_Rot/10);
  qDebug() << "X_Rot ====" << X_Rot / 1000;

  ui->openGLWidget->XRot = X_Rot;

  double Y_Rot = settings->value("YRot").toDouble();
  ui->y_rot->setValue(Y_Rot / 10);
  ui->openGLWidget->YRot = Y_Rot;

  double Z_Rot = settings->value("ZRot").toDouble();
  ui->z_rot->setValue(Z_Rot / 10);
  ui->openGLWidget->ZRot = Z_Rot;
//
  double X_RotNeg = settings->value("XRotNeg").toDouble();
  ui->x_rot_2->setValue(X_RotNeg / 10);
  ui->openGLWidget->XRotNeg = X_RotNeg;
  qDebug() << "------------"<<ui->openGLWidget->XRotNeg ;

  double Y_RotNeg = settings->value("YRotNeg").toDouble();
  ui->y_rot_2->setValue(Y_RotNeg / 10);
  ui->openGLWidget->YRotNeg = Y_RotNeg;

  double Z_RotNeg = settings->value("ZRotNeg").toDouble();
  ui->z_rot_2->setValue(Z_RotNeg / 10);
  ui->openGLWidget->ZRotNeg = Z_RotNeg;
 //

  double scale_S = settings->value("scaleS").toDouble();
  ui->openGLWidget->scaleS = scale_S;
  qDebug() << "update" << ui->openGLWidget->scaleS;
  settings->endGroup();
}

void MainWindow::on_cleanSettings_clicked() {
  ui->openGLWidget->lineSize = 1;
  ui->lineSize->setValue(0);
  ui->openGLWidget->pointSize = 1;
  ui->pointSize->setValue(0);
  ui->openGLWidget->lineType = true;
  ui->comboBox->setCurrentIndex(0);
  ui->openGLWidget->pointType = true;
  ui->pointType->setCurrentIndex(0);
  ui->openGLWidget->pointZero = false;
  ui->openGLWidget->paralelPr = true;
  ui->projection->setCurrentIndex(0);
  ui->openGLWidget->XRight = 0;
  ui->openGLWidget->XLeft = 0;
  ui->openGLWidget->YTop = 0;
  ui->openGLWidget->ZTop = 0;
  ui->openGLWidget->YDown = 0;
  ui->openGLWidget->ZDown = 0;
  ui->openGLWidget->XRot = 0;
  ui->x_rot->setValue(0);
  ui->openGLWidget->YRot = 0;
  ui->y_rot->setValue(0);
  ui->openGLWidget->ZRot = 0;
  ui->z_rot->setValue(0);

  ui->openGLWidget->XRotNeg = 0;
  ui->x_rot_2->setValue(0);
  ui->openGLWidget->YRotNeg = 0;
  ui->y_rot_2->setValue(0);
  ui->openGLWidget->ZRotNeg = 0;
  ui->z_rot_2->setValue(0);

  ui->openGLWidget->scaleS = 1;
  ui->openGLWidget->updateFrame();
}

void MainWindow::Record() {
  ++count_frame;
  gif->addFrame(ui->openGLWidget->grabFramebuffer(), 100);
  if (count_frame == 70) {
    timer->stop();
    gif->save(ptr_gif_file);
    ptr_gif_file->close();
    ptr_gif_file = nullptr;
    delete gif;
    gif = nullptr;
  }
}

void MainWindow::on_gif_clicked() {
  QString path_name =
      QFileDialog::getSaveFileName(this, tr(" "), "", tr("help(*.gif)"));
  ptr_gif_file = new QFile(path_name);
  ptr_gif_file->open(QIODevice::WriteOnly);
  gif = new QGifImage();
  count_frame = 0;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(Record()));
  timer->start(100);
}

void MainWindow::on_animashin_clicked(bool checked) {
  ui->openGLWidget->animashin = checked;
  ui->openGLWidget->updateFrame();
}

void MainWindow::on_screen_clicked() {
  if (screen == true) {
    ui->bmp->show();
    ui->jpeg->show();
    connect(ui->bmp, SIGNAL(clicked()), this, SLOT(buttonBMP()));
    connect(ui->jpeg, SIGNAL(clicked()), this, SLOT(buttonJPEG()));
    screen = false;
  } else {
    screen = true;
    ui->bmp->hide();
    ui->jpeg->hide();
  }
}

void MainWindow::buttonBMP() {
  QString screenFile = QFileDialog::getSaveFileName(this);
  ui->openGLWidget->grabFramebuffer().save(screenFile + ".bmp", NULL, 100);
}

void MainWindow::buttonJPEG() {
  QString screenFile = QFileDialog::getSaveFileName(this);
  ui->openGLWidget->grabFramebuffer().save(screenFile + ".jpeg", NULL, 100);
}

void MainWindow::on_x_rot_2_valueChanged(double arg1)
{
    double x = (arg1 * M_PI) / 180;
    ui->openGLWidget->xRotNeg = x;
    ui->openGLWidget->updateFrame();
}


void MainWindow::on_y_rot_2_valueChanged(double arg1)
{

    double y = arg1 * 1000;
    ui->openGLWidget->yRotNeg = y;
    ui->openGLWidget->updateFrame();
}


void MainWindow::on_z_rot_2_valueChanged(double arg1)
{
    double z = (arg1 * M_PI) / 180;
    ui->openGLWidget->zRotNeg = z;
    ui->openGLWidget->updateFrame();
}

