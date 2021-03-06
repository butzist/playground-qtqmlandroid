#ifndef QQMLANDROIDCONTEXTWRAPPER_P_H
#define QQMLANDROIDCONTEXTWRAPPER_P_H

#include "qqmlandroidcontext_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidContextWrapper : public QQmlAndroidContext
{
    Q_OBJECT

public:
    explicit QQmlAndroidContextWrapper(QObject *parent = 0);
    explicit QQmlAndroidContextWrapper(QQmlAndroidContext *context, QObject *parent = 0);
};

QT_END_NAMESPACE

#endif // QQMLANDROIDCONTEXTWRAPPER_P_H
