#include <QDebug>

#include <QtWidgets/QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  Q_INIT_RESOURCE(qt_material_widgets);

  MainWindow window;
  window.show();

  return a.exec();
}
