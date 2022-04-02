#include <QtWidgets/QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(examples);
    Q_INIT_RESOURCE(material_res);

    MainWindow window;
    window.show();

    return a.exec();
}
