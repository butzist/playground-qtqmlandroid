#ifndef QQMLANDROIDR_P_H
#define QQMLANDROIDR_P_H

#include <QtCore/qobject.h>
#include <QtQml/qqmlpropertymap.h>

QT_BEGIN_NAMESPACE

class QJSEngine;
class QQmlEngine;

class QQmlAndroidR : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlPropertyMap *anim READ anim CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *animator READ animator CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *array READ anim CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *attr READ attr CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *boolean READ boolean CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *color READ color CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *dimen READ dimen CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *drawable READ drawable CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *fraction READ fraction CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *id READ id CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *integer READ integer CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *interpolator READ interpolator CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *layout READ layout CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *menu READ menu CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *mipmap READ mipmap CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *plurals READ plurals CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *raw READ raw CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *string READ string CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *style READ style CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *styleable READ styleable CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *transition READ transition CONSTANT)
    Q_PROPERTY(QQmlPropertyMap *xml READ xml CONSTANT)

public:
    QQmlAndroidR();

    QQmlPropertyMap *anim();
    QQmlPropertyMap *animator();
    QQmlPropertyMap *array();
    QQmlPropertyMap *attr();
    QQmlPropertyMap *boolean();
    QQmlPropertyMap *color();
    QQmlPropertyMap *dimen();
    QQmlPropertyMap *drawable();
    QQmlPropertyMap *fraction();
    QQmlPropertyMap *id();
    QQmlPropertyMap *integer();
    QQmlPropertyMap *interpolator();
    QQmlPropertyMap *layout();
    QQmlPropertyMap *menu();
    QQmlPropertyMap *mipmap();
    QQmlPropertyMap *plurals();
    QQmlPropertyMap *raw();
    QQmlPropertyMap *string();
    QQmlPropertyMap *style();
    QQmlPropertyMap *styleable();
    QQmlPropertyMap *transition();
    QQmlPropertyMap *xml();

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

private:
    QQmlPropertyMap *m_anim;
    QQmlPropertyMap *m_animator;
    QQmlPropertyMap *m_array;
    QQmlPropertyMap *m_attr;
    QQmlPropertyMap *m_boolean;
    QQmlPropertyMap *m_color;
    QQmlPropertyMap *m_dimen;
    QQmlPropertyMap *m_drawable;
    QQmlPropertyMap *m_fraction;
    QQmlPropertyMap *m_id;
    QQmlPropertyMap *m_integer;
    QQmlPropertyMap *m_interpolator;
    QQmlPropertyMap *m_layout;
    QQmlPropertyMap *m_menu;
    QQmlPropertyMap *m_mipmap;
    QQmlPropertyMap *m_plurals;
    QQmlPropertyMap *m_raw;
    QQmlPropertyMap *m_string;
    QQmlPropertyMap *m_style;
    QQmlPropertyMap *m_styleable;
    QQmlPropertyMap *m_transition;
    QQmlPropertyMap *m_xml;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDR_P_H
