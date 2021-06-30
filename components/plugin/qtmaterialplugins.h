#ifndef QTMATERIALPLUGINS_H
#define QTMATERIALPLUGINS_H

#include <QDesignerCustomWidgetCollectionInterface>
#include "plugintemplate.h"
#include "qtmaterialappbar.h"
#include "qtmaterialautocomplete.h"
#include "qtmaterialavatar.h"
#include "qtmaterialbadge.h"
#include "qtmaterialcheckbox.h"
#include "qtmaterialcircularprogress.h"
#include "qtmaterialdialog.h"
#include "qtmaterialdrawer.h"
#include "qtmaterialfab.h"
#include "qtmaterialflatbutton.h"
#include "qtmaterialiconbutton.h"
#include "qtmateriallist.h"
#include "qtmateriallistitem.h"
#include "qtmaterialmenu.h"
#include "qtmaterialpaper.h"
#include "qtmaterialprogress.h"
#include "qtmaterialradiobutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialscrollbar.h"
#include "qtmaterialslider.h"
#include "qtmaterialsnackbar.h"
#include "qtmaterialtable.h"
#include "qtmaterialtabs.h"
#include "qtmaterialtextfield.h"
#include "qtmaterialtoggle.h"

QT_DESIGN_PLUGIN(MaterialAppBarPlugin          , "qtmaterialappbar.h"          , QtMaterialAppBar          )
QT_DESIGN_PLUGIN(MaterialAutoCompletePlugin    , "qtmaterialautocomplete.h"    , QtMaterialAutoComplete    )
QT_DESIGN_PLUGIN(MaterialAvatarPlugin          , "qtmaterialavatar.h"          , QtMaterialAvatar          )
QT_DESIGN_PLUGIN(MaterialBadgePlugin           , "qtmaterialbadge.h"           , QtMaterialBadge           )
QT_DESIGN_PLUGIN(MaterialCheckBoxPlugin        , "qtmaterialcheckbox.h"        , QtMaterialCheckBox        )
QT_DESIGN_PLUGIN(MaterialCircularProgressPlugin, "qtmaterialcircularprogress.h", QtMaterialCircularProgress)
QT_DESIGN_PLUGIN(MaterialDialogPlugin          , "qtmaterialdialog.h"          , QtMaterialDialog          )
QT_DESIGN_PLUGIN(MaterialDrawerPlugin          , "qtmaterialdrawer.h"          , QtMaterialDrawer          )
QT_DESIGN_PLUGIN(MaterialFabPlugin             , "qtmaterialfab.h"             , QtMaterialFloatingActionButton)
QT_DESIGN_PLUGIN(MaterialFlatButtonPlugin      , "qtmaterialflatbutton.h"      , QtMaterialFlatButton      )
QT_DESIGN_PLUGIN(MaterialIconButtonPlugin      , "qtmaterialiconbutton.h"      , QtMaterialIconButton      )
//QT_DESIGN_PLUGIN(MaterialListPlugin            , "qtmateriallist.h"            , QtMaterialList            )
//QT_DESIGN_PLUGIN(MaterialListItemPlugin        , "qtmateriallistitem.h"        , QtMaterialListItem        )
QT_DESIGN_PLUGIN(MaterialMenuPlugin            , "qtmaterialmenu.h"            , QtMaterialMenu            )
//QT_DESIGN_PLUGIN(MaterialPaperPlugin           , "qtmaterialpaper.h"           , QtMaterialPaper           )
QT_DESIGN_PLUGIN(MaterialProgressPlugin        , "qtmaterialprogress.h"        , QtMaterialProgress        )
QT_DESIGN_PLUGIN(MaterialRadioButtonPlugin     , "qtmaterialradiobutton.h"     , QtMaterialRadioButton     )
QT_DESIGN_PLUGIN(MaterialRaisedButtonPlugin    , "qtmaterialraisedbutton.h"    , QtMaterialRaisedButton    )
QT_DESIGN_PLUGIN(MaterialScrollbarPlugin       , "qtmaterialscrollbar.h"       , QtMaterialScrollBar       )
QT_DESIGN_PLUGIN(MaterialSliderPlugin          , "qtmaterialslider.h"          , QtMaterialSlider          )
QT_DESIGN_PLUGIN(MaterialSnackbarPlugin        , "qtmaterialsnackbar.h"        , QtMaterialSnackbar        )
//QT_DESIGN_PLUGIN(MaterialTablePlugin           , "qtmaterialtable.h"           , QtMaterialTable           )
QT_DESIGN_PLUGIN(MaterialTabsPlugin            , "qtmaterialtabs.h"            , QtMaterialTabs            )
QT_DESIGN_PLUGIN(MaterialTextFieldPlugin       , "qtmaterialtextfield.h"       , QtMaterialTextField       )
QT_DESIGN_PLUGIN(MaterialTogglePlugin          , "qtmaterialtoggle.h"          , QtMaterialToggle          )

class QtMaterialPlugins : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.meta-vi.QDesignerCustomWidgetCollectionInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    explicit QtMaterialPlugins(QObject *parent = nullptr);
    QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface *> m_plugins;

};

#endif // QTMATERIALPLUGINS_H
