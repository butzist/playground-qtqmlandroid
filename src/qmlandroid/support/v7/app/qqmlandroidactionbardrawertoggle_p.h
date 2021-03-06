#ifndef QQMLANDROIDACTIONBARDRAWERTOGGLE_P_H
#define QQMLANDROIDACTIONBARDRAWERTOGGLE_P_H

#include "qqmlandroidobject_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidActionBarDrawerToggle : public QQmlAndroidObject
{
    Q_OBJECT

public:
    explicit QQmlAndroidActionBarDrawerToggle(QObject *parent = 0);

    void onCreate(const QAndroidJniObject &activity, const QAndroidJniObject &drawer);
};

QT_END_NAMESPACE

#endif // QQMLANDROIDACTIONBARDRAWERTOGGLE_P_H
