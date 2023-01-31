#ifndef QTMATERIALTHEME_H
#define QTMATERIALTHEME_H

#include <QObject>
#include <QScopedPointer>
#include <QColor>
#include <QIcon>

namespace Material
{
    enum ButtonPreset {
        FlatPreset,
        CheckablePreset
    };

    enum RippleStyle {
        CenteredRipple,
        PositionedRipple,
        NoRipple
    };

    enum OverlayStyle {
        NoOverlay,
        TintedOverlay,
        GrayOverlay
    };

    enum Role {
        Default,
        Primary,
        Secondary
    };

    enum ButtonIconPlacement {
        LeftIcon,
        RightIcon
    };

    enum ProgressType {
        DeterminateProgress,
        IndeterminateProgress
    };

    enum AvatarType {
        ImageAvatar,
        IconAvatar,
        LetterAvatar
    };

    enum Color {
        red50,
        red100,
        red200,
        red300,
        red400,
        red500,
        red600,
        red700,
        red800,
        red900,
        redA100,
        redA200,
        redA400,
        redA700,
        pink50,
        pink100,
        pink200,
        pink300,
        pink400,
        pink500,
        pink600,
        pink700,
        pink800,
        pink900,
        pinkA100,
        pinkA200,
        pinkA400,
        pinkA700,
        purple50,
        purple100,
        purple200,
        purple300,
        purple400,
        purple500,
        purple600,
        purple700,
        purple800,
        purple900,
        purpleA100,
        purpleA200,
        purpleA400,
        purpleA700,
        deepPurple50,
        deepPurple100,
        deepPurple200,
        deepPurple300,
        deepPurple400,
        deepPurple500,
        deepPurple600,
        deepPurple700,
        deepPurple800,
        deepPurple900,
        deepPurpleA100,
        deepPurpleA200,
        deepPurpleA400,
        deepPurpleA700,
        indigo50,
        indigo100,
        indigo200,
        indigo300,
        indigo400,
        indigo500,
        indigo600,
        indigo700,
        indigo800,
        indigo900,
        indigoA100,
        indigoA200,
        indigoA400,
        indigoA700,
        blue50,
        blue100,
        blue200,
        blue300,
        blue400,
        blue500,
        blue600,
        blue700,
        blue800,
        blue900,
        blueA100,
        blueA200,
        blueA400,
        blueA700,
        lightBlue50,
        lightBlue100,
        lightBlue200,
        lightBlue300,
        lightBlue400,
        lightBlue500,
        lightBlue600,
        lightBlue700,
        lightBlue800,
        lightBlue900,
        lightBlueA100,
        lightBlueA200,
        lightBlueA400,
        lightBlueA700,
        cyan50,
        cyan100,
        cyan200,
        cyan300,
        cyan400,
        cyan500,
        cyan600,
        cyan700,
        cyan800,
        cyan900,
        cyanA100,
        cyanA200,
        cyanA400,
        cyanA700,
        teal50,
        teal100,
        teal200,
        teal300,
        teal400,
        teal500,
        teal600,
        teal700,
        teal800,
        teal900,
        tealA100,
        tealA200,
        tealA400,
        tealA700,
        green50,
        green100,
        green200,
        green300,
        green400,
        green500,
        green600,
        green700,
        green800,
        green900,
        greenA100,
        greenA200,
        greenA400,
        greenA700,
        lightGreen50,
        lightGreen100,
        lightGreen200,
        lightGreen300,
        lightGreen400,
        lightGreen500,
        lightGreen600,
        lightGreen700,
        lightGreen800,
        lightGreen900,
        lightGreenA100,
        lightGreenA200,
        lightGreenA400,
        lightGreenA700,
        lime50,
        lime100,
        lime200,
        lime300,
        lime400,
        lime500,
        lime600,
        lime700,
        lime800,
        lime900,
        limeA100,
        limeA200,
        limeA400,
        limeA700,
        yellow50,
        yellow100,
        yellow200,
        yellow300,
        yellow400,
        yellow500,
        yellow600,
        yellow700,
        yellow800,
        yellow900,
        yellowA100,
        yellowA200,
        yellowA400,
        yellowA700,
        amber50,
        amber100,
        amber200,
        amber300,
        amber400,
        amber500,
        amber600,
        amber700,
        amber800,
        amber900,
        amberA100,
        amberA200,
        amberA400,
        amberA700,
        orange50,
        orange100,
        orange200,
        orange300,
        orange400,
        orange500,
        orange600,
        orange700,
        orange800,
        orange900,
        orangeA100,
        orangeA200,
        orangeA400,
        orangeA700,
        deepOrange50,
        deepOrange100,
        deepOrange200,
        deepOrange300,
        deepOrange400,
        deepOrange500,
        deepOrange600,
        deepOrange700,
        deepOrange800,
        deepOrange900,
        deepOrangeA100,
        deepOrangeA200,
        deepOrangeA400,
        deepOrangeA700,
        brown50,
        brown100,
        brown200,
        brown300,
        brown400,
        brown500,
        brown600,
        brown700,
        brown800,
        brown900,
        blueGrey50,
        blueGrey100,
        blueGrey200,
        blueGrey300,
        blueGrey400,
        blueGrey500,
        blueGrey600,
        blueGrey700,
        blueGrey800,
        blueGrey900,
        grey50,
        grey100,
        grey200,
        grey300,
        grey400,
        grey500,
        grey600,
        grey700,
        grey800,
        grey900,
        black,
        white,
        transparent,
        fullBlack,
        darkBlack,
        lightBlack,
        minBlack,
        faintBlack,
        fullWhite,
        darkWhite,
        lightWhite
    };
}

class QtMaterialThemePrivate;

class QtMaterialTheme : public QObject
{
    Q_OBJECT

public:
    explicit QtMaterialTheme(QObject *parent = 0);
    ~QtMaterialTheme();

    QColor getColor(const QString &key) const;

    void setColor(const QString &key, const QColor &color);
    void setColor(const QString &key, Material::Color color);

    static QIcon icon(QString category, QString icon);

protected:
    const QScopedPointer<QtMaterialThemePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTheme)
    Q_DECLARE_PRIVATE(QtMaterialTheme)
};

#endif // QTMATERIALTHEME_H
