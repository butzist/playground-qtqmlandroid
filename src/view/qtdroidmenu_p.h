#ifndef QTDROIDMENU_P_H
#define QTDROIDMENU_P_H

#include "qtdroidobject_p.h"

QT_BEGIN_NAMESPACE

class QtAndroidMenuItem;

class QtAndroidMenu : public QtAndroidObject
{
    Q_OBJECT

public:
    explicit QtAndroidMenu(QObject *parent = 0);

    QList<QtAndroidMenuItem *> items() const;
};

QT_END_NAMESPACE

#endif // QTDROIDMENU_P_H
