#include "qtmaterialcheckbox.h"
#include "qtmaterialcheckbox_p.h"
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include "lib/qtmaterialcheckable_internal.h"

/*!
 *  \class QtMaterialCheckBoxPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialCheckBoxPrivate::QtMaterialCheckBoxPrivate(QtMaterialCheckBox *q)
    : QtMaterialCheckablePrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialCheckBoxPrivate::~QtMaterialCheckBoxPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialCheckBoxPrivate::init()
{
    Q_Q(QtMaterialCheckBox);

    checkedState->assignProperty(checkedIcon, "iconSize", 24);
    uncheckedState->assignProperty(checkedIcon, "iconSize", 0);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(300);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "iconSize", q);
    animation->setDuration(1300);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(checkedIcon, "opacity", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "opacity", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(440);
    checkedTransition->addAnimation(animation);

    animation = new QPropertyAnimation(uncheckedIcon, "color", q);
    animation->setDuration(440);
    uncheckedTransition->addAnimation(animation);
}

/*!
 *  \class QtMaterialCheckBox
 */

QtMaterialCheckBox::QtMaterialCheckBox(QWidget *parent)
    : QtMaterialCheckable(*new QtMaterialCheckBoxPrivate(this), parent)
{
    d_func()->init();
}

QtMaterialCheckBox::~QtMaterialCheckBox()
{
}
