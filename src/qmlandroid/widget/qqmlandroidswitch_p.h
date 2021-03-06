#ifndef QQMLANDROIDSWITCH_P_H
#define QQMLANDROIDSWITCH_P_H

#include "qqmlandroidcompoundbutton_p.h"

QT_BEGIN_NAMESPACE

class QQmlAndroidSwitch : public QQmlAndroidCompoundButton
{
    Q_OBJECT

public:
    explicit QQmlAndroidSwitch(QQmlAndroidView *parent = 0);

protected:
    QAndroidJniObject onCreate() Q_DECL_OVERRIDE;
    void onInflate(QAndroidJniObject &instance) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QQMLANDROIDSWITCH_P_H
