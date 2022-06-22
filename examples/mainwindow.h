#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>

#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "checkboxsettingseditor.h"
#include "fabsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "progresssettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "slidersettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "togglesettingseditor.h"
#include "textfieldsettingseditor.h"
#include "tabssettingseditor.h"
#include "snackbarsettingseditor.h"
#include "dialogsettingseditor.h"
#include "drawersettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "menusettingseditor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
