#ifndef QTMATERIALTEXTFIELD_H
#define QTMATERIALTEXTFIELD_H

#include <QtWidgets/QLineEdit>
#include <QColor>
#include <QtUiPlugin/QDesignerExportWidget>

class QtMaterialTextFieldPrivate;

class QDESIGNER_WIDGET_EXPORT QtMaterialTextField : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(bool useThemeColors WRITE setUseThemeColors READ useThemeColors)
    Q_PROPERTY(bool showLabel WRITE setShowLabel READ hasLabel)
    Q_PROPERTY(QString label WRITE setLabel READ label)
    Q_PROPERTY(qreal labelFontSize WRITE setLabelFontSize READ labelFontSize)
    Q_PROPERTY(QColor labelColor WRITE setLabelColor READ labelColor)
    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor inputLineColor WRITE setInputLineColor READ inputLineColor)
    Q_PROPERTY(bool showInputLine WRITE setShowInputLine READ hasInputLine)

public:
    explicit QtMaterialTextField(QWidget *parent = 0);
    ~QtMaterialTextField();

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setShowLabel(bool value);
    bool hasLabel() const;

    void setLabelFontSize(qreal size);
    qreal labelFontSize() const;

    void setLabel(const QString &label);
    QString label() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setLabelColor(const QColor &color);
    QColor labelColor() const;

    void setInkColor(const QColor &color);
    QColor inkColor() const;

    void setInputLineColor(const QColor &color);
    QColor inputLineColor() const;

    void setShowInputLine(bool value);
    bool hasInputLine() const;

protected:
    QtMaterialTextField(QtMaterialTextFieldPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialTextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTextField)
    Q_DECLARE_PRIVATE(QtMaterialTextField)
};

#endif // QTMATERIALTEXTFIELD_H
