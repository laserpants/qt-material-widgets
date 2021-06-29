greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets designer
}

lessThan(QT_MAJOR_VERSION, 5) {
    CONFIG += designer
}

CONFIG += plugin release
TEMPLATE = lib
TARGET = $$qtLibraryTarget(qt-material-widget)
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
INCLUDEPATH += .

SOURCES = \
    plugin/materialtoggleplugin.cpp \
    plugin/qtmaterialplugins.cpp \
    qtmaterialavatar.cpp \
    lib/qtmaterialstyle.cpp \
    lib/qtmaterialtheme.cpp \
    qtmaterialbadge.cpp \
    lib/qtmaterialoverlaywidget.cpp \
    qtmaterialcheckbox.cpp \
    lib/qtmaterialcheckable_internal.cpp \
    lib/qtmaterialcheckable.cpp \
    lib/qtmaterialripple.cpp \
    lib/qtmaterialrippleoverlay.cpp \
    qtmaterialfab.cpp \
    qtmaterialraisedbutton.cpp \
    qtmaterialflatbutton_internal.cpp \
    qtmaterialflatbutton.cpp \
    lib/qtmaterialstatetransition.cpp \
    qtmaterialiconbutton.cpp \
    qtmaterialprogress_internal.cpp \
    qtmaterialprogress.cpp \
    qtmaterialcircularprogress_internal.cpp \
    qtmaterialcircularprogress.cpp \
    qtmaterialslider_internal.cpp \
    qtmaterialslider.cpp \
    qtmaterialsnackbar_internal.cpp \
    qtmaterialsnackbar.cpp \
    qtmaterialradiobutton.cpp \
    qtmaterialtoggle_internal.cpp \
    qtmaterialtoggle.cpp \
    qtmaterialtextfield_internal.cpp \
    qtmaterialtextfield.cpp \
    qtmaterialtabs_internal.cpp \
    qtmaterialtabs.cpp \
    qtmaterialscrollbar_internal.cpp \
    qtmaterialscrollbar.cpp \
    qtmaterialdialog_internal.cpp \
    qtmaterialdialog.cpp \
    qtmaterialdrawer_internal.cpp \
    qtmaterialdrawer.cpp \
    qtmaterialappbar.cpp \
    qtmaterialautocomplete.cpp \
    qtmaterialpaper.cpp \
    qtmaterialtable.cpp \
    layouts/qtmaterialsnackbarlayout.cpp \
    qtmaterialautocomplete_internal.cpp \
    qtmaterialmenu.cpp \
    qtmaterialmenu_internal.cpp \
    qtmateriallist.cpp \
    qtmateriallistitem.cpp
HEADERS = \
    plugin/materialtoggleplugin.h \
    plugin/qtmaterialplugins.h \
    qtmaterialavatar_p.h \
    qtmaterialavatar.h \
    lib/qtmaterialstyle_p.h \
    lib/qtmaterialstyle.h \
    lib/qtmaterialtheme_p.h \
    lib/qtmaterialtheme.h \
    qtmaterialbadge_p.h \
    qtmaterialbadge.h \
    lib/qtmaterialoverlaywidget.h \
    qtmaterialcheckbox_p.h \
    qtmaterialcheckbox.h \
    lib/qtmaterialcheckable_internal.h \
    lib/qtmaterialcheckable_p.h \
    lib/qtmaterialripple.h \
    lib/qtmaterialrippleoverlay.h \
    lib/qtmaterialcheckable.h \
    qtmaterialfab_p.h \
    qtmaterialfab.h \
    qtmaterialraisedbutton_p.h \
    qtmaterialraisedbutton.h \
    qtmaterialflatbutton_internal.h \
    qtmaterialflatbutton_p.h \
    qtmaterialflatbutton.h \
    lib/qtmaterialstatetransition.h \
    lib/qtmaterialstatetransitionevent.h \
    qtmaterialiconbutton_p.h \
    qtmaterialiconbutton.h \
    qtmaterialprogress_internal.h \
    qtmaterialprogress_p.h \
    qtmaterialprogress.h \
    qtmaterialcircularprogress_internal.h \
    qtmaterialcircularprogress_p.h \
    qtmaterialcircularprogress.h \
    qtmaterialslider_internal.h \
    qtmaterialslider_p.h \
    qtmaterialslider.h \
    qtmaterialsnackbar_internal.h \
    qtmaterialsnackbar_p.h \
    qtmaterialsnackbar.h \
    qtmaterialradiobutton_p.h \
    qtmaterialradiobutton.h \
    qtmaterialtoggle_internal.h \
    qtmaterialtoggle_p.h \
    qtmaterialtoggle.h \
    qtmaterialtextfield_internal.h \
    qtmaterialtextfield_p.h \
    qtmaterialtextfield.h \
    qtmaterialtabs_internal.h \
    qtmaterialtabs_p.h \
    qtmaterialtabs.h \
    qtmaterialscrollbar_internal.h \
    qtmaterialscrollbar_p.h \
    qtmaterialscrollbar.h \
    qtmaterialdialog_internal.h \
    qtmaterialdialog_p.h \
    qtmaterialdialog.h \
    qtmaterialdrawer_internal.h \
    qtmaterialdrawer_p.h \
    qtmaterialdrawer.h \
    qtmaterialappbar.h \
    qtmaterialappbar_p.h \
    qtmaterialautocomplete.h \
    qtmaterialautocomplete_p.h \
    qtmaterialpaper.h \
    qtmaterialpaper_p.h \
    qtmaterialtable.h \
    qtmaterialtable_p.h \
    layouts/qtmaterialsnackbarlayout.h \
    layouts/qtmaterialsnackbarlayout_p.h \
    qtmaterialautocomplete_internal.h \
    qtmaterialmenu.h \
    qtmaterialmenu_p.h \
    qtmaterialmenu_internal.h \
    qtmateriallist.h \
    qtmateriallist_p.h \
    qtmateriallistitem.h \
    qtmateriallistitem_p.h
RESOURCES += \
    material_res.qrc
