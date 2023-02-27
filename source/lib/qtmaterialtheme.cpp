#include "lib/qtmaterialtheme.h"
#include "lib/qtmaterialtheme_p.h"
#include <QString>
#include <QStringBuilder>
#include <QDebug>

/*!material
 *  \class QtMaterialThemePrivate
 *  \internal
 */

QtMaterialThemePrivate::QtMaterialThemePrivate(QtMaterialTheme *q)
    : q_ptr(q)
{
}

QtMaterialThemePrivate::~QtMaterialThemePrivate()
{
}

QColor QtMaterialThemePrivate::rgba(int r, int g, int b, qreal a) const
{
    QColor color(r, g, b);
    color.setAlphaF(a);
    return color;
}

/*!
 *  \class QtMaterialTheme
 */

QtMaterialTheme::QtMaterialTheme(QObject *parent)
    : QObject(parent),
      d_ptr(new QtMaterialThemePrivate(this))
{
    setColor("primary1", Material::cyan500);
    setColor("primary2", Material::cyan700);
    setColor("primary3", Material::lightBlack);
    setColor("accent1", Material::pinkA200);
    setColor("accent2", Material::grey100);
    setColor("accent3", Material::grey500);
    setColor("text", Material::darkBlack);
    setColor("alternateText", Material::white);
    setColor("canvas", Material::white);
    setColor("border", Material::grey300);
    setColor("disabled", Material::minBlack);
    setColor("disabled2", Material::faintBlack);
    setColor("disabled3", Material::grey300);
}

QtMaterialTheme::~QtMaterialTheme()
{
}

QColor QtMaterialTheme::getColor(const QString &key) const
{
    Q_D(const QtMaterialTheme);

    if (!d->colors.contains(key)) {
        qWarning() << "A theme color matching the key '" << key << "' could not be found.";
        return QColor();
    }
    return d->colors.value(key);
}

void QtMaterialTheme::setColor(const QString &key, const QColor &color)
{
    Q_D(QtMaterialTheme);

    d->colors.insert(key, color);
}

void QtMaterialTheme::setColor(const QString &key, Material::Color color)
{
    Q_D(QtMaterialTheme);

    static const QColor palette[] = {
        QColor("#ffebee"), QColor("#ffcdd2"), QColor("#ef9a9a"), QColor("#e57373"),
        QColor("#ef5350"), QColor("#f44336"), QColor("#e53935"), QColor("#d32f2f"),
        QColor("#c62828"), QColor("#b71c1c"), QColor("#ff8a80"), QColor("#ff5252"),
        QColor("#ff1744"), QColor("#d50000"), QColor("#fce4ec"), QColor("#f8bbd0"),
        QColor("#f48fb1"), QColor("#f06292"), QColor("#ec407a"), QColor("#e91e63"),
        QColor("#d81b60"), QColor("#c2185b"), QColor("#ad1457"), QColor("#880e4f"),
        QColor("#ff80ab"), QColor("#ff4081"), QColor("#f50057"), QColor("#c51162"),
        QColor("#f3e5f5"), QColor("#e1bee7"), QColor("#ce93d8"), QColor("#ba68c8"),
        QColor("#ab47bc"), QColor("#9c27b0"), QColor("#8e24aa"), QColor("#7b1fa2"),
        QColor("#6a1b9a"), QColor("#4a148c"), QColor("#ea80fc"), QColor("#e040fb"),
        QColor("#d500f9"), QColor("#aa00ff"), QColor("#ede7f6"), QColor("#d1c4e9"),
        QColor("#b39ddb"), QColor("#9575cd"), QColor("#7e57c2"), QColor("#673ab7"),
        QColor("#5e35b1"), QColor("#512da8"), QColor("#4527a0"), QColor("#311b92"),
        QColor("#b388ff"), QColor("#7c4dff"), QColor("#651fff"), QColor("#6200ea"),
        QColor("#e8eaf6"), QColor("#c5cae9"), QColor("#9fa8da"), QColor("#7986cb"),
        QColor("#5c6bc0"), QColor("#3f51b5"), QColor("#3949ab"), QColor("#303f9f"),
        QColor("#283593"), QColor("#1a237e"), QColor("#8c9eff"), QColor("#536dfe"),
        QColor("#3d5afe"), QColor("#304ffe"), QColor("#e3f2fd"), QColor("#bbdefb"),
        QColor("#90caf9"), QColor("#64b5f6"), QColor("#42a5f5"), QColor("#2196f3"),
        QColor("#1e88e5"), QColor("#1976d2"), QColor("#1565c0"), QColor("#0d47a1"),
        QColor("#82b1ff"), QColor("#448aff"), QColor("#2979ff"), QColor("#2962ff"),
        QColor("#e1f5fe"), QColor("#b3e5fc"), QColor("#81d4fa"), QColor("#4fc3f7"),
        QColor("#29b6f6"), QColor("#03a9f4"), QColor("#039be5"), QColor("#0288d1"),
        QColor("#0277bd"), QColor("#01579b"), QColor("#80d8ff"), QColor("#40c4ff"),
        QColor("#00b0ff"), QColor("#0091ea"), QColor("#e0f7fa"), QColor("#b2ebf2"),
        QColor("#80deea"), QColor("#4dd0e1"), QColor("#26c6da"), QColor("#00bcd4"),
        QColor("#00acc1"), QColor("#0097a7"), QColor("#00838f"), QColor("#006064"),
        QColor("#84ffff"), QColor("#18ffff"), QColor("#00e5ff"), QColor("#00b8d4"),
        QColor("#e0f2f1"), QColor("#b2dfdb"), QColor("#80cbc4"), QColor("#4db6ac"),
        QColor("#26a69a"), QColor("#009688"), QColor("#00897b"), QColor("#00796b"),
        QColor("#00695c"), QColor("#004d40"), QColor("#a7ffeb"), QColor("#64ffda"),
        QColor("#1de9b6"), QColor("#00bfa5"), QColor("#e8f5e9"), QColor("#c8e6c9"),
        QColor("#a5d6a7"), QColor("#81c784"), QColor("#66bb6a"), QColor("#4caf50"),
        QColor("#43a047"), QColor("#388e3c"), QColor("#2e7d32"), QColor("#1b5e20"),
        QColor("#b9f6ca"), QColor("#69f0ae"), QColor("#00e676"), QColor("#00c853"),
        QColor("#f1f8e9"), QColor("#dcedc8"), QColor("#c5e1a5"), QColor("#aed581"),
        QColor("#9ccc65"), QColor("#8bc34a"), QColor("#7cb342"), QColor("#689f38"),
        QColor("#558b2f"), QColor("#33691e"), QColor("#ccff90"), QColor("#b2ff59"),
        QColor("#76ff03"), QColor("#64dd17"), QColor("#f9fbe7"), QColor("#f0f4c3"),
        QColor("#e6ee9c"), QColor("#dce775"), QColor("#d4e157"), QColor("#cddc39"),
        QColor("#c0ca33"), QColor("#afb42b"), QColor("#9e9d24"), QColor("#827717"),
        QColor("#f4ff81"), QColor("#eeff41"), QColor("#c6ff00"), QColor("#aeea00"),
        QColor("#fffde7"), QColor("#fff9c4"), QColor("#fff59d"), QColor("#fff176"),
        QColor("#ffee58"), QColor("#ffeb3b"), QColor("#fdd835"), QColor("#fbc02d"),
        QColor("#f9a825"), QColor("#f57f17"), QColor("#ffff8d"), QColor("#ffff00"),
        QColor("#ffea00"), QColor("#ffd600"), QColor("#fff8e1"), QColor("#ffecb3"),
        QColor("#ffe082"), QColor("#ffd54f"), QColor("#ffca28"), QColor("#ffc107"),
        QColor("#ffb300"), QColor("#ffa000"), QColor("#ff8f00"), QColor("#ff6f00"),
        QColor("#ffe57f"), QColor("#ffd740"), QColor("#ffc400"), QColor("#ffab00"),
        QColor("#fff3e0"), QColor("#ffe0b2"), QColor("#ffcc80"), QColor("#ffb74d"),
        QColor("#ffa726"), QColor("#ff9800"), QColor("#fb8c00"), QColor("#f57c00"),
        QColor("#ef6c00"), QColor("#e65100"), QColor("#ffd180"), QColor("#ffab40"),
        QColor("#ff9100"), QColor("#ff6d00"), QColor("#fbe9e7"), QColor("#ffccbc"),
        QColor("#ffab91"), QColor("#ff8a65"), QColor("#ff7043"), QColor("#ff5722"),
        QColor("#f4511e"), QColor("#e64a19"), QColor("#d84315"), QColor("#bf360c"),
        QColor("#ff9e80"), QColor("#ff6e40"), QColor("#ff3d00"), QColor("#dd2c00"),
        QColor("#efebe9"), QColor("#d7ccc8"), QColor("#bcaaa4"), QColor("#a1887f"),
        QColor("#8d6e63"), QColor("#795548"), QColor("#6d4c41"), QColor("#5d4037"),
        QColor("#4e342e"), QColor("#3e2723"), QColor("#eceff1"), QColor("#cfd8dc"),
        QColor("#b0bec5"), QColor("#90a4ae"), QColor("#78909c"), QColor("#607d8b"),
        QColor("#546e7a"), QColor("#455a64"), QColor("#37474f"), QColor("#263238"),
        QColor("#fafafa"), QColor("#f5f5f5"), QColor("#eeeeee"), QColor("#e0e0e0"),
        QColor("#bdbdbd"), QColor("#9e9e9e"), QColor("#757575"), QColor("#616161"),
        QColor("#424242"), QColor("#212121"), QColor("#000000"), QColor("#ffffff"),
        d->rgba(0, 0, 0, 0),
        d->rgba(0, 0, 0, 1),
        d->rgba(0, 0, 0, 0.87),
        d->rgba(0, 0, 0, 0.54),
        d->rgba(0, 0, 0, 0.26),
        d->rgba(0, 0, 0, 0.12),
        d->rgba(255, 255, 255, 1),
        d->rgba(255, 255, 255, 0.87),
        d->rgba(255, 255, 255, 0.54)
    };

    d->colors.insert(key, palette[color]);
}

QIcon QtMaterialTheme::icon(QString category, QString icon)
{
    return QIcon(":/icons/icons/" % category % "/svg/production/ic_" % icon % "_24px.svg");
}
