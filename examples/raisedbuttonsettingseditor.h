#ifndef RAISEDBUTTONSETTINGSEDITOR_H
#define RAISEDBUTTONSETTINGSEDITOR_H

#include <raisedbutton.h>
#include "flatbuttonsettingseditor.h"

using namespace md;

class RaisedButtonSettingsEditor : public FlatButtonSettingsEditor
{
    Q_OBJECT

public:
    explicit RaisedButtonSettingsEditor(QWidget *parent = 0);
    ~RaisedButtonSettingsEditor();
};

#endif // RAISEDBUTTONSETTINGSEDITOR_H
