#ifndef QTMATERIALTEXTFIELD_H
#define QTMATERIALTEXTFIELD_H

#include <QtWidgets/QLineEdit>
#include <QColor>

class QtMaterialTextFieldPrivate;

class QtMaterialTextField : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QColor textColor WRITE setTextColor READ textColor)
    Q_PROPERTY(QColor inkColor WRITE setInkColor READ inkColor)
    Q_PROPERTY(QColor underlineColor WRITE setUnderlineColor READ underlineColor)

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

    void setUnderlineColor(const QColor &color);
    QColor underlineColor() const;

    void setShowUnderline(bool value);
    bool hasUnderline() const;

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialTextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTextField)
    Q_DECLARE_PRIVATE(QtMaterialTextField)
};

#endif // QTMATERIALTEXTFIELD_H
