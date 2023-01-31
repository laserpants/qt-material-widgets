#include <QtWidgets/QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(resources);

    MainWindow window;
    window.show();

    return a.exec();
}
