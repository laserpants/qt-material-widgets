#include "qtmaterialcheckbox.h"
#include "qtmaterialcheckbox_p.h"
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QState>
#include "lib/qtmaterialcheckable_internal.h"
namespace md
{

/*!
 *  \class QtMaterialCheckBoxPrivate
 *  \internal
 */

/*!
 *  \internal
 */
CheckBoxPrivate::CheckBoxPrivate(CheckBox *q)
    : CheckablePrivate(q)
{
}

/*!
 *  \internal
 */
CheckBoxPrivate::~CheckBoxPrivate()
{
}

/*!
 *  \internal
 */
void CheckBoxPrivate::init()
{
    Q_Q(CheckBox);

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

CheckBox::CheckBox(QWidget *parent)
    : Checkable(*new CheckBoxPrivate(this), parent)
{
    d_func()->init();
}

CheckBox::~CheckBox()
{
}

}
